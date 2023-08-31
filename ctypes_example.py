import ctypes

lib = ctypes.CDLL('./libtest.so')

lib.add_float.restype = ctypes.c_float
lib.add_float.argtypes = [ctypes.c_float,ctypes.c_float]
lib.add_int.restype = ctypes.c_int
lib.add_int.argtypes = [ctypes.c_int,ctypes.c_int]

def add(a,b):
    if isinstance(a,float) and isinstance(b,float):
        return lib.add_float(a,b)
    elif isinstance(a,int) and isinstance(b,int):
        return lib.add_int(a,b)
    else:
        raise ValueError("Unsupported argument types")
    
__all__ = ['add']