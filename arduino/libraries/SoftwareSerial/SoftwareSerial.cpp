/*
SoftwareSerial.cpp (formerly NewSoftSerial.cpp) - 
Multi-instance software serial library for Arduino/Wiring
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.
*/

// When set, _DEBUG co-opts pins 11 and 13 for debugging with an
// oscilloscope or logic analyzer.  Beware: it also slightly modifies
// the bit times, so don't rely on it too much at high baud rates

// 
// Includes
// 
//#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
#include <wiringPi.h>

//#define DEBUG_SOFTWARESERIAL

static const int BAUDRATE[] = {115200, 57600, 38400, 31250, 28800, 19200, 14400,
                               9600, 4800, 2400, 1200, 600, 300};

//
// Statics
//
uint64_t SoftwareSerial::_clock_base = 0L;
SoftwareSerial *SoftwareSerial::active_object = 0;
char SoftwareSerial::_receive_buffer[_SS_MAX_RX_BUFF]; 
volatile uint8_t SoftwareSerial::_receive_buffer_tail = 0;
volatile uint8_t SoftwareSerial::_receive_buffer_head = 0;

//
// Private methods
//

/* static */ 
inline void SoftwareSerial::tunedDelay(unsigned int delay, bool reset ) {
    if(reset){
        _clock_base = tick();
    }
    while(tick() < _clock_base + delay);
}

// This function sets the current object as the "listening"
// one and returns true if it replaces another 
bool SoftwareSerial::listen()
{
  if (active_object != this)
  {
    _buffer_overflow = false;
    _receive_buffer_head = _receive_buffer_tail = 0;
    active_object = this;
    return true;
  }

  return false;
}

//
// The receive routine called by the interrupt handler
//
void SoftwareSerial::recv()
{
  uint8_t d = 0;

  // If RX line is high, then we don't see any start bit
  // so interrupt is probably not for us
  if (_inverse_logic ? digitalReadQuick(_receivePin) : !digitalReadQuick(_receivePin))
  {
    // Wait approximately 1/2 of a bit width to "center" the sample
    tunedDelay(halfbit / baud, true);

    uint8_t bit = 0;
    // Read each of the 8 bits
    for (uint8_t i=0x1; i; i <<= 1)
    {
      ++bit;
      tunedDelay((halfbit + fullbit * bit) / baud);
      uint8_t noti = ~i;
      if (digitalReadQuick(_receivePin))
        d |= i;
      else // else clause added to ensure function timing is ~balanced
        d &= noti;
    }
    ++bit;

    // skip the stop bit
    tunedDelay((halfbit + fullbit * bit) / baud);

    if (_inverse_logic)
      d = ~d;

    // if buffer full, set the overflow flag and return
    if ((_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF != _receive_buffer_head) 
    {
      // save new data in buffer: tail points to where byte goes
      _receive_buffer[_receive_buffer_tail] = d; // save new byte
      _receive_buffer_tail = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
    } 
    else 
    {
      _buffer_overflow = true;
    }
#ifdef DEBUG_SOFTWARESERIAL
    printf("recv 0x%02X\n", d);
#endif
  }
}

//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */) : 
  baud(0),
  _buffer_overflow(false),
  _inverse_logic(inverse_logic)
{
#ifdef DEBUG_SOFTWARESERIAL
    printf("SoftwareSerial rx: pin %d, tx: pin %d\n", receivePin, transmitPin);
#endif
  setTX(transmitPin);
  setRX(receivePin);
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial()
{
  end();
}

void SoftwareSerial::setTX(uint8_t tx)
{
  pinMode(tx, OUTPUT);
  digitalWriteQuick(tx, HIGH);
  _transmitPin = tx;
}

void SoftwareSerial::setRX(uint8_t rx)
{
  pinMode(rx, INPUT);
  if (!_inverse_logic)
    digitalWrite(rx, HIGH);  // pullup for normal logic!
  else
    digitalWrite(rx, LOW);   // else pulldown?
  _receivePin = rx;
}

//
// Public methods
//

void SoftwareSerial::begin(long speed)
{
  baud = 0;

  for (unsigned i=0; i<sizeof(BAUDRATE)/sizeof(BAUDRATE[0]); ++i)
  {
    if(BAUDRATE[i] == speed){
        baud = speed;
    }
  }

  // Set up RX interrupts, but only if we have a valid RX baud rate
  if (baud)
  {
    wiringPiISR(_receivePin, INT_EDGE_BOTH, handle_interrupt);
    tunedDelay(fullbit / baud, true); // if we were low this establishes the end
  }

  listen();
}

void SoftwareSerial::end()
{
    // Remove the ISR thread.
    wiringPiISR(_receivePin, INT_EDGE_BOTH, NULL);
}


// Read data from buffer
int SoftwareSerial::read()
{
  if (!isListening())
    return -1;

  // Empty buffer?
  if (_receive_buffer_head == _receive_buffer_tail)
    return -1;

  // Read from "head"
  uint8_t d = _receive_buffer[_receive_buffer_head]; // grab next byte
  _receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
  return d;
}

int SoftwareSerial::available()
{
  if (!isListening())
    return 0;

  return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head) % _SS_MAX_RX_BUFF;
}

size_t SoftwareSerial::write(uint8_t b)
{
  // Write the start bit
  digitalWriteQuick(_transmitPin, _inverse_logic ? HIGH : LOW);
  tunedDelay(fullbit / baud, true);

  int bit = 1;
  // Write each of the 8 bits
  if (_inverse_logic)
  {
    for (byte mask = 0x01; mask; mask <<= 1)
    {
      ++bit;
      if (b & mask) // choose bit
        digitalWriteQuick(_transmitPin, LOW); // send 1
      else
        digitalWriteQuick(_transmitPin, HIGH); // send 0
    
      tunedDelay(bit * fullbit / baud);
    }

    digitalWriteQuick(_transmitPin, LOW); // restore pin to natural state
  }
  else
  {
    for (byte mask = 0x01; mask; mask <<= 1)
    {
      ++bit;
      if (b & mask) // choose bit
        digitalWriteQuick(_transmitPin, HIGH); // send 1
      else
        digitalWriteQuick(_transmitPin, LOW); // send 0
    
      tunedDelay(bit * fullbit / baud);
    }

    digitalWriteQuick(_transmitPin, HIGH); // restore pin to natural state
  }

  tunedDelay(bit * fullbit / baud, true);
#ifdef DEBUG_SOFTWARESERIAL
    printf("write 0x%02X - %c\n", b, b);
#endif
  
  return 1;
}

void SoftwareSerial::flush()
{
  if (!isListening())
    return;

  _receive_buffer_head = _receive_buffer_tail = 0;
}

int SoftwareSerial::peek()
{
  if (!isListening())
    return -1;

  // Empty buffer?
  if (_receive_buffer_head == _receive_buffer_tail)
    return -1;

  // Read from "head"
  return _receive_buffer[_receive_buffer_head];
}
