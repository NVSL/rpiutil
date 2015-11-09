# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_LiquidCrystal', [dirname(__file__)])
        except ImportError:
            import _LiquidCrystal
            return _LiquidCrystal
        if fp is not None:
            try:
                _mod = imp.load_module('_LiquidCrystal', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _LiquidCrystal = swig_import_helper()
    del swig_import_helper
else:
    import _LiquidCrystal
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


_STDINT_H = _LiquidCrystal._STDINT_H
INT8_MIN = _LiquidCrystal.INT8_MIN
INT16_MIN = _LiquidCrystal.INT16_MIN
INT32_MIN = _LiquidCrystal.INT32_MIN
INT64_MIN = _LiquidCrystal.INT64_MIN
INT8_MAX = _LiquidCrystal.INT8_MAX
INT16_MAX = _LiquidCrystal.INT16_MAX
INT32_MAX = _LiquidCrystal.INT32_MAX
INT64_MAX = _LiquidCrystal.INT64_MAX
UINT8_MAX = _LiquidCrystal.UINT8_MAX
UINT16_MAX = _LiquidCrystal.UINT16_MAX
UINT32_MAX = _LiquidCrystal.UINT32_MAX
UINT64_MAX = _LiquidCrystal.UINT64_MAX
INT_LEAST8_MIN = _LiquidCrystal.INT_LEAST8_MIN
INT_LEAST16_MIN = _LiquidCrystal.INT_LEAST16_MIN
INT_LEAST32_MIN = _LiquidCrystal.INT_LEAST32_MIN
INT_LEAST64_MIN = _LiquidCrystal.INT_LEAST64_MIN
INT_LEAST8_MAX = _LiquidCrystal.INT_LEAST8_MAX
INT_LEAST16_MAX = _LiquidCrystal.INT_LEAST16_MAX
INT_LEAST32_MAX = _LiquidCrystal.INT_LEAST32_MAX
INT_LEAST64_MAX = _LiquidCrystal.INT_LEAST64_MAX
UINT_LEAST8_MAX = _LiquidCrystal.UINT_LEAST8_MAX
UINT_LEAST16_MAX = _LiquidCrystal.UINT_LEAST16_MAX
UINT_LEAST32_MAX = _LiquidCrystal.UINT_LEAST32_MAX
UINT_LEAST64_MAX = _LiquidCrystal.UINT_LEAST64_MAX
INT_FAST8_MIN = _LiquidCrystal.INT_FAST8_MIN
INT_FAST16_MIN = _LiquidCrystal.INT_FAST16_MIN
INT_FAST32_MIN = _LiquidCrystal.INT_FAST32_MIN
INT_FAST64_MIN = _LiquidCrystal.INT_FAST64_MIN
INT_FAST8_MAX = _LiquidCrystal.INT_FAST8_MAX
INT_FAST16_MAX = _LiquidCrystal.INT_FAST16_MAX
INT_FAST32_MAX = _LiquidCrystal.INT_FAST32_MAX
INT_FAST64_MAX = _LiquidCrystal.INT_FAST64_MAX
UINT_FAST8_MAX = _LiquidCrystal.UINT_FAST8_MAX
UINT_FAST16_MAX = _LiquidCrystal.UINT_FAST16_MAX
UINT_FAST32_MAX = _LiquidCrystal.UINT_FAST32_MAX
UINT_FAST64_MAX = _LiquidCrystal.UINT_FAST64_MAX
INTPTR_MIN = _LiquidCrystal.INTPTR_MIN
INTPTR_MAX = _LiquidCrystal.INTPTR_MAX
UINTPTR_MAX = _LiquidCrystal.UINTPTR_MAX
INTMAX_MIN = _LiquidCrystal.INTMAX_MIN
INTMAX_MAX = _LiquidCrystal.INTMAX_MAX
UINTMAX_MAX = _LiquidCrystal.UINTMAX_MAX
PTRDIFF_MIN = _LiquidCrystal.PTRDIFF_MIN
PTRDIFF_MAX = _LiquidCrystal.PTRDIFF_MAX
SIG_ATOMIC_MIN = _LiquidCrystal.SIG_ATOMIC_MIN
SIG_ATOMIC_MAX = _LiquidCrystal.SIG_ATOMIC_MAX
SIZE_MAX = _LiquidCrystal.SIZE_MAX
WINT_MIN = _LiquidCrystal.WINT_MIN
WINT_MAX = _LiquidCrystal.WINT_MAX
DEC = _LiquidCrystal.DEC
HEX = _LiquidCrystal.HEX
OCT = _LiquidCrystal.OCT
BIN = _LiquidCrystal.BIN
class Print(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Print, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Print, name)
    def __init__(self, *args, **kwargs): raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    def getWriteError(self): return _LiquidCrystal.Print_getWriteError(self)
    def clearWriteError(self): return _LiquidCrystal.Print_clearWriteError(self)
    def write(self, *args): return _LiquidCrystal.Print_write(self, *args)
    def _print(self, *args): return _LiquidCrystal.Print__print(self, *args)
    def println(self, *args): return _LiquidCrystal.Print_println(self, *args)
    __swig_destroy__ = _LiquidCrystal.delete_Print
    __del__ = lambda self : None;
Print_swigregister = _LiquidCrystal.Print_swigregister
Print_swigregister(Print)

class LiquidCrystal(Print):
    __swig_setmethods__ = {}
    for _s in [Print]: __swig_setmethods__.update(getattr(_s,'__swig_setmethods__',{}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, LiquidCrystal, name, value)
    __swig_getmethods__ = {}
    for _s in [Print]: __swig_getmethods__.update(getattr(_s,'__swig_getmethods__',{}))
    __getattr__ = lambda self, name: _swig_getattr(self, LiquidCrystal, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _LiquidCrystal.new_LiquidCrystal(*args)
        try: self.this.append(this)
        except: self.this = this
    def init(self, *args): return _LiquidCrystal.LiquidCrystal_init(self, *args)
    def begin(self, *args): return _LiquidCrystal.LiquidCrystal_begin(self, *args)
    def clear(self): return _LiquidCrystal.LiquidCrystal_clear(self)
    def home(self): return _LiquidCrystal.LiquidCrystal_home(self)
    def noDisplay(self): return _LiquidCrystal.LiquidCrystal_noDisplay(self)
    def display(self): return _LiquidCrystal.LiquidCrystal_display(self)
    def noBlink(self): return _LiquidCrystal.LiquidCrystal_noBlink(self)
    def blink(self): return _LiquidCrystal.LiquidCrystal_blink(self)
    def noCursor(self): return _LiquidCrystal.LiquidCrystal_noCursor(self)
    def cursor(self): return _LiquidCrystal.LiquidCrystal_cursor(self)
    def scrollDisplayLeft(self): return _LiquidCrystal.LiquidCrystal_scrollDisplayLeft(self)
    def scrollDisplayRight(self): return _LiquidCrystal.LiquidCrystal_scrollDisplayRight(self)
    def leftToRight(self): return _LiquidCrystal.LiquidCrystal_leftToRight(self)
    def rightToLeft(self): return _LiquidCrystal.LiquidCrystal_rightToLeft(self)
    def autoscroll(self): return _LiquidCrystal.LiquidCrystal_autoscroll(self)
    def noAutoscroll(self): return _LiquidCrystal.LiquidCrystal_noAutoscroll(self)
    def createChar(self, *args): return _LiquidCrystal.LiquidCrystal_createChar(self, *args)
    def setCursor(self, *args): return _LiquidCrystal.LiquidCrystal_setCursor(self, *args)
    def command(self, *args): return _LiquidCrystal.LiquidCrystal_command(self, *args)
    def write(self, *args): return _LiquidCrystal.LiquidCrystal_write(self, *args)
    __swig_destroy__ = _LiquidCrystal.delete_LiquidCrystal
    __del__ = lambda self : None;
LiquidCrystal_swigregister = _LiquidCrystal.LiquidCrystal_swigregister
LiquidCrystal_swigregister(LiquidCrystal)

# This file is compatible with both classic and new-style classes.


