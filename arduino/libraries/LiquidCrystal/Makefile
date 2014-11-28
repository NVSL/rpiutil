# ;
# Makefile:
#   arduinoPi - LiquidCrystal core library for RaspberryPi
###############################################################################
DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=$(GADGETRON_RASPI_PATH)
PREFIX=

#STATIC=libLiquidCrystal.a
DYNAMIC=libLiquidCrystal.so.$(VERSION)
PYTHON=_LiquidCrystal.so LiquidCrystal.py

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

all:		$(DYNAMIC) $(PYTHON)

#static:		$(STATIC)

#$(STATIC):	$(OBJ)
#	@echo "[Link (Static)]"
#	@ar rcs $(STATIC) $(OBJ)
#	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]" 
	@$(CC) -shared -Wl,-soname,libLiquidCrystal.so -o libLiquidCrystal.so.$(VERSION) -lpthread -lArduino $(LIBS) $(OBJ)

.cpp.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

$(PYTHON): $(DYNAMIC) LiquidCrystal.i
	@echo [Making python binding]
	@swig -c++ -python -I/usr/include -I$(GADGETRON_RASPI_PATH)/include LiquidCrystal.i
	@$(CC) -shared -fPIC -I/usr/include/python2.7 -I$(GADGETRON_RASPI_PATH)/include -I. libLiquidCrystal.so.$(VERSION) LiquidCrystal_wrap.cxx -o _LiquidCrystal.so 

.PHONEY:	clean
clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags Makefile.bak libLiquidCrystal.* LiquidCrystal.py* LiquidCrystal_wrap.* _LiquidCrystal.so

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
install:	$(DYNAMIC) $(PYTHON) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 _LiquidCrystal.so			$(DESTDIR)$(PREFIX)/lib/python/_LiquidCrystal.so
	@install -m 0755 LiquidCrystal.py				$(DESTDIR)$(PREFIX)/lib/python/LiquidCrystal.py
	@install -m 0755 libLiquidCrystal.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libLiquidCrystal.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libLiquidCrystal.so.$(VERSION)	$(DESTDIR)/lib/libLiquidCrystal.so
#	@ldconfig

#.PHONEY:	install-static
#install-static:	$(STATIC) install-headers
#	@echo "[Install Static Lib]"
#	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
#	@install -m 0755 libLiquidCrystal.a		$(DESTDIR)$(PREFIX)/lib

.PHONEY:	uninstall
uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/LiquidCrystal.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libLiquidCrystal.*
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/_LiquidCrystal.so
	@rm -f $(DESTDIR)$(PREFIX)/lib/python/LiquidCrystal.py*
#	@ldconfig

.PHONEY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE
LiquidCrystal.o: LiquidCrystal.h
