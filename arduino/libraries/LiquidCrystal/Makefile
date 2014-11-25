# ;
# Makefile:
#   arduinoPi - LiquidCrystal core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=$(GADGETRON_RASPI_PATH)
PREFIX=

STATIC=libLiquidCrystal.a
DYNAMIC=libLiquidCrystal.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= g++
INCLUDE	= -I. -I$(GADGETRON_RASPI_PATH)/include
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Winline $(INCLUDE) $(LIBS) -pipe -fPIC

LIBS    = -L$(GADGETRON_RASPI_PATH)/lib

# Should not alter anything below this line
###############################################################################

SRC	=	 LiquidCrystal.cpp

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
	@$(CC) -shared -Wl,-soname,libLiquidCrystal.so -o libLiquidCrystal.so.$(VERSION) -lpthread -lArduino $(LIBS) $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libLiquidCrystal.*

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


.PHONEY:	install-headers
install-headers:
	@echo "[Install Headers]"
	@install -m 0755 -d		    	$(DESTDIR)$(PREFIX)/include
	@install -m 0644 LiquidCrystal.h		$(DESTDIR)$(PREFIX)/include

.PHONEY:	install
install:	$(DYNAMIC) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libLiquidCrystal.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libLiquidCrystal.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libLiquidCrystal.so.$(VERSION)	$(DESTDIR)/lib/libLiquidCrystal.so
#	@ldconfig

.PHONEY:	install-static
install-static:	$(STATIC) install-headers
	@echo "[Install Static Lib]"
	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libLiquidCrystal.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/LiquidCrystal.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libLiquidCrystal.*
#	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE
LiquidCrystal.o: LiquidCrystal.h
