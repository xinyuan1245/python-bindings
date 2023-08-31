import cffi
import pathlib
ffi = cffi.FFI()
this_dir = pathlib.Path().resolve()
h_file_name = this_dir /"test.h"
with open(h_file_name) as h_file:
    lns = h_file.read().splitlines()
    flt = filter(lambda ln: not ln.strip().startswith("#"), lns)
    ffi.cdef("\n".join(flt))
# Load the shared library in ABI mode
lib = ffi.dlopen("libtest.so")
# Wrap C functions as Python functions with type checks
def add_float(a, b):
    return lib.add_float(a,b)
def add_int(a, b):
    return lib.add_int(a, b)
def add(a, b):
    if isinstance(a, float) or isinstance(b, float):
        return add_float(a, b)
    elif isinstance(a, int) and isinstance(b, int):
        return add_int(a, b)
    else:
        raise ValueError("Unsupported argument types for add function.")
