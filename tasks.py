from invoke import task 
@task
def clean(c):
    c.run(" rm -rf cffi_example.c cffi_example.o cffi_example.cpython-38-x86_64-linux-gnu.so pythoncapi_example.so")
    c.run("rm -rf pybind11_example.so")
    c.run("rm -rf cython_example.c cython_example.cpp cython_example.cpython-38-x86_64-linux-gnu.so")
@task
def build_test_c(c):
    c.run("gcc -c -Wall -Werror -fPIC test.c")
    c.run("gcc -shared  -o libtest.so test.o")

@task
def build_pythoncapi(c):
    c.run("gcc -shared -o pythoncapi_example.so pythoncapi_example.c -I ~/miniconda3/envs/python-bdings/include/python3.8 -ldl -fPIC")

@task
def build_pybind11(ctx):
    ctx.run("c++ -O3 -Wall -shared -std=c++11 -fPIC `python -m pybind11 --include` pybind11_example.cpp -o pybind11_example.so")

@task
def build_cython(c):
    c.run("python setup.py build_ext --inplace")

@task(build_test_c,build_cython,build_pybind11,build_pythoncapi)
def compare(c):
    print("this is ctypes_results")
    c.run("python ctypes_test.py")
    print()
    print("this is CFFI_results")
    c.run("python cffi_test.py") 
    print()
    print("this is pythoncapi_results")
    c.run("python pythoncapi_test.py")
    print()
    print("this is pybind11_results")
    c.run("python pybind11_test.py")
    print()
    print("this is cython_results")
    c.run("python cython_test.py")