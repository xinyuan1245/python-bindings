#include <pybind11/pybind11.h>
#include <dlfcn.h>

namespace py = pybind11;

typedef float (*AddFloatFunc)(float, float);
typedef int (*AddIntFunc)(int, int);

static AddFloatFunc add_float = nullptr;
static AddIntFunc add_int = nullptr;
static void* libHandle = nullptr;

float add_float_wrapper(float a, float b) {
    if (!add_float) {
        throw std::runtime_error("add_float function pointer is not initialized.");
    }
    return add_float(a, b);
}

int add_int_wrapper(int a, int b) {
    if (!add_int) {
        throw std::runtime_error("add_int function pointer is not initialized.");
    }
    return add_int(a, b);
}

PYBIND11_MODULE(pybind11_example, m) {
    m.doc() = "pybind11 example build";

    libHandle = dlopen("libtest.so", RTLD_LAZY);
    if (!libHandle) {
        throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
    }

    add_float = (AddFloatFunc)dlsym(libHandle, "add_float");
    if (!add_float) {
        dlclose(libHandle);
        throw std::runtime_error("Failed to find the symbol: add_float");
    }

    add_int = (AddIntFunc)dlsym(libHandle, "add_int");
    if (!add_int) {
        dlclose(libHandle);
        throw std::runtime_error("Failed to find the symbol: add_int");
    }

    // 在 lambda 函数中通过引用捕获 add_float 和 add_int 函数指针
    m.def("add", [](py::object arg1, py::object arg2) -> py::object {
        if (py::isinstance<py::float_>(arg1) && py::isinstance<py::float_>(arg2)) {
            float a = arg1.cast<float>();
            float b = arg2.cast<float>();
            return py::cast(add_float_wrapper(a, b)); // 使用 add_float_wrapper 函数
        } else if (py::isinstance<py::int_>(arg1) && py::isinstance<py::int_>(arg2)) {
            int a = arg1.cast<int>();
            int b = arg2.cast<int>();
            return py::cast(add_int_wrapper(a, b)); // 使用 add_int_wrapper 函数
        } else {
            throw std::runtime_error("Unsupported data types for 'add'.");
        }
    }, "Add either two floats or two integers");

    // 在模块销毁时关闭共享库
    m.add_object("___cleanup", py::capsule(libHandle, [](void* handle) {
        dlclose(handle);
    }));
}
