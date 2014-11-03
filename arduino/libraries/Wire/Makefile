# ;
# Makefile:
#   arduinoPi - Wire core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=/usr
PREFIX=/local

STATIC=libWire.a
DYNAMIC=libWire.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= g++
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) -pipe -fPIC

LIBS    =

# Should not alter anything below this line
###############################################################################

SRC	=	 Wire.cpp

OBJ	= $(SRC:.cpp=.o)

all:		$(DYNAMIC)

static:		$(STATIC)

$(STATIC):	$(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $(STATIC) $(OBJ)
	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]" 
	@$(CC) -shared -Wl,-soname,libWire.so -o libWire.so.$(VERSION) -lpthread -lArduino $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libWire.*

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
install:	$(DYNAMIC) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libWire.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libWire.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libWire.so.$(VERSION)	$(DESTDIR)/lib/libWire.so
	@ldconfig

.PHONEY:	install-static
install-static:	$(STATIC) install-headers
	@echo "[Install Static Lib]"
	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libWire.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/Wire.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libWire.*
	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE
Wire.o: Wire.h
