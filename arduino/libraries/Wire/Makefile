# ;
# Makefile:
#   arduinoPi - Wire core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=$(GADGETRON_RASPI_PATH)
PREFIX=

#STATIC=libWire.a
DYNAMIC=libWire.so.$(VERSION)
PYTHON=_Wire.so Wire.py

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= g++
INCLUDE	= -I. -I$(GADGETRON_RASPI_PATH)/include
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) $(LIBS) -pipe -fPIC

LIBS    = -L$(GADGETRON_RASPI_PATH)/lib

# Should not alter anything below this line
###############################################################################

SRC	=	 Wire.cpp

OBJ	= $(SRC:.cpp=.o)

all:		$(DYNAMIC) $(PYTHON)

#static:		$(STATIC)

#$(STATIC):	$(OBJ)
#	@echo "[Link (Static)]"
#	@ar rcs $(STATIC) $(OBJ)
#	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]" 
	@$(CC) -shared -Wl,-soname,libWire.so -o libWire.so.$(VERSION) -lpthread -lArduino $(LIBS) $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(PYTHON): $(DYNAMIC) Wire.i
	@echo [Making python binding]
	@swig -c++ -python -I/usr/include Wire.i
	@$(CC) -shared -fPIC -I/usr/include/python2.7 -I$(GADGETRON_RASPI_PATH)/include -I. libWire.so.$(VERSION) -o _Wire.so Wire_wrap.cxx

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libWire.* Wire.py* Wire_wrap.* _Wire.so

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


.PHONEY:	install-headers
install-headers:
	@echo "[Install Headers]"
	@install -m 0755 -d		    	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 Wire.h		$(DESTDIR)$(PREFIX)/include

.PHONEY:	install
install:	$(DYNAMIC) $(PYTHON) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 _Wire.so			$(DESTDIR)$(PREFIX)/lib/python/_Wire.so
	@install -m 0755 Wire.py				$(DESTDIR)$(PREFIX)/lib/python/Wire.py
	@install -m 0755 libWire.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libWire.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libWire.so.$(VERSION)	$(DESTDIR)/lib/libWire.so
#	@ldconfig

#.PHONEY:	install-static
#install-static:	$(STATIC) install-headers
#	@echo "[Install Static Lib]"
#	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
#	@install -m 0755 libWire.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/Wire.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libWire.*
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/_Wire.so
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/Wire.py*
#	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE
Wire.o: Wire.h
