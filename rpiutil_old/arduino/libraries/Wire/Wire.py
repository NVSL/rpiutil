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
            fp, pathname, description = imp.find_module('_Wire', [dirname(__file__)])
        except ImportError:
            import _Wire
            return _Wire
        if fp is not None:
            try:
                _mod = imp.load_module('_Wire', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _Wire = swig_import_helper()
    del swig_import_helper
else:
    import _Wire
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


_STDINT_H = _Wire._STDINT_H
INT8_MIN = _Wire.INT8_MIN
INT16_MIN = _Wire.INT16_MIN
INT32_MIN = _Wire.INT32_MIN
INT64_MIN = _Wire.INT64_MIN
INT8_MAX = _Wire.INT8_MAX
INT16_MAX = _Wire.INT16_MAX
INT32_MAX = _Wire.INT32_MAX
INT64_MAX = _Wire.INT64_MAX
UINT8_MAX = _Wire.UINT8_MAX
UINT16_MAX = _Wire.UINT16_MAX
UINT32_MAX = _Wire.UINT32_MAX
UINT64_MAX = _Wire.UINT64_MAX
INT_LEAST8_MIN = _Wire.INT_LEAST8_MIN
INT_LEAST16_MIN = _Wire.INT_LEAST16_MIN
INT_LEAST32_MIN = _Wire.INT_LEAST32_MIN
INT_LEAST64_MIN = _Wire.INT_LEAST64_MIN
INT_LEAST8_MAX = _Wire.INT_LEAST8_MAX
INT_LEAST16_MAX = _Wire.INT_LEAST16_MAX
INT_LEAST32_MAX = _Wire.INT_LEAST32_MAX
INT_LEAST64_MAX = _Wire.INT_LEAST64_MAX
UINT_LEAST8_MAX = _Wire.UINT_LEAST8_MAX
UINT_LEAST16_MAX = _Wire.UINT_LEAST16_MAX
UINT_LEAST32_MAX = _Wire.UINT_LEAST32_MAX
UINT_LEAST64_MAX = _Wire.UINT_LEAST64_MAX
INT_FAST8_MIN = _Wire.INT_FAST8_MIN
INT_FAST16_MIN = _Wire.INT_FAST16_MIN
INT_FAST32_MIN = _Wire.INT_FAST32_MIN
INT_FAST64_MIN = _Wire.INT_FAST64_MIN
INT_FAST8_MAX = _Wire.INT_FAST8_MAX
INT_FAST16_MAX = _Wire.INT_FAST16_MAX
INT_FAST32_MAX = _Wire.INT_FAST32_MAX
INT_FAST64_MAX = _Wire.INT_FAST64_MAX
UINT_FAST8_MAX = _Wire.UINT_FAST8_MAX
UINT_FAST16_MAX = _Wire.UINT_FAST16_MAX
UINT_FAST32_MAX = _Wire.UINT_FAST32_MAX
UINT_FAST64_MAX = _Wire.UINT_FAST64_MAX
INTPTR_MIN = _Wire.INTPTR_MIN
INTPTR_MAX = _Wire.INTPTR_MAX
UINTPTR_MAX = _Wire.UINTPTR_MAX
INTMAX_MIN = _Wire.INTMAX_MIN
INTMAX_MAX = _Wire.INTMAX_MAX
UINTMAX_MAX = _Wire.UINTMAX_MAX
PTRDIFF_MIN = _Wire.PTRDIFF_MIN
PTRDIFF_MAX = _Wire.PTRDIFF_MAX
SIG_ATOMIC_MIN = _Wire.SIG_ATOMIC_MIN
SIG_ATOMIC_MAX = _Wire.SIG_ATOMIC_MAX
SIZE_MAX = _Wire.SIZE_MAX
WINT_MIN = _Wire.WINT_MIN
WINT_MAX = _Wire.WINT_MAX
BUFFER_LENGTH = _Wire.BUFFER_LENGTH
class TwoWire(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TwoWire, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TwoWire, name)
    __repr__ = _swig_repr
    def __init__(self): 
        this = _Wire.new_TwoWire()
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _Wire.delete_TwoWire
    __del__ = lambda self : None;
    def begin(self, *args): return _Wire.TwoWire_begin(self, *args)
    def beginTransmission(self, *args): return _Wire.TwoWire_beginTransmission(self, *args)
    def endTransmission(self, *args): return _Wire.TwoWire_endTransmission(self, *args)
    def requestFrom(self, *args): return _Wire.TwoWire_requestFrom(self, *args)
    def available(self): return _Wire.TwoWire_available(self)
    def read(self): return _Wire.TwoWire_read(self)
    def peek(self): return _Wire.TwoWire_peek(self)
    def flush(self): return _Wire.TwoWire_flush(self)
    def onReceive(self, *args): return _Wire.TwoWire_onReceive(self, *args)
    def onRequest(self, *args): return _Wire.TwoWire_onRequest(self, *args)
TwoWire_swigregister = _Wire.TwoWire_swigregister
TwoWire_swigregister(TwoWire)

# This file is compatible with both classic and new-style classes.

cvar = _Wire.cvar

