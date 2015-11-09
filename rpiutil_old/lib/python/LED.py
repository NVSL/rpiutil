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
            fp, pathname, description = imp.find_module('_LED', [dirname(__file__)])
        except ImportError:
            import _LED
            return _LED
        if fp is not None:
            try:
                _mod = imp.load_module('_LED', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _LED = swig_import_helper()
    del swig_import_helper
else:
    import _LED
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


class LED(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, LED, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, LED, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _LED.new_LED(*args)
        try: self.this.append(this)
        except: self.this = this
    def blink(self, *args): return _LED.LED_blink(self, *args)
    def isBlinking(self): return _LED.LED_isBlinking(self)
    def toggle(self): return _LED.LED_toggle(self)
    def turnOn(self): return _LED.LED_turnOn(self)
    def update(self): return _LED.LED_update(self)
    def turnOff(self): return _LED.LED_turnOff(self)
    def setup(self): return _LED.LED_setup(self)
    def loop(self): return _LED.LED_loop(self)
    __swig_destroy__ = _LED.delete_LED
    __del__ = lambda self : None;
LED_swigregister = _LED.LED_swigregister
LED_swigregister(LED)

# This file is compatible with both classic and new-style classes.


