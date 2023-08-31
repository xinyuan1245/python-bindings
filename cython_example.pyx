# distutils: language = c++
# test_wrapper.pyx

cdef extern from "dlfcn.h":
    void* dlopen(const char*, int)
    void* dlsym(void *, const char *)
    int dlclose(void*)

cdef extern from "test.h":
    float add_float(float a, float b)
    int add_int(int a, int b)

cdef void* handle = dlopen("./libtest.so", 1)
cdef void* add_float_func = dlsym(handle, "add_float")
cdef void* add_int_func = dlsym(handle, "add_int")

cpdef add(a, b):
    if isinstance(a, int) and isinstance(b, int):
        return <int>(<int(*)(int, int)>add_int_func)(a, b)
    elif isinstance(a, float) and isinstance(b, float):
        return <float>(<float(*)(float, float)>add_float_func)(a, b)
    else:
        raise ValueError("Unsupported data types. Only int and float are allowed.")
