#include <Python.h>
#include <dlfcn.h>

typedef float (*AddFloatFunc)(float, float);
typedef int (*AddIntFunc)(int, int);

void* libHandle = NULL;
AddFloatFunc add_float = NULL;
AddIntFunc add_int = NULL;

static PyObject* example_add(PyObject* self, PyObject* args) {
    PyObject* arg1;
    PyObject* arg2;
    if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {
        return NULL;
    }

    if (PyLong_Check(arg1) && PyLong_Check(arg2)) {
        int a = PyLong_AsLong(arg1);
        int b = PyLong_AsLong(arg2);
        int result = add_int(a, b);
        return PyLong_FromLong(result);
    } else if (PyFloat_Check(arg1) && PyFloat_Check(arg2)) {
        float a = PyFloat_AsDouble(arg1);
        float b = PyFloat_AsDouble(arg2);
        float result = add_float(a, b);
        return PyFloat_FromDouble(result);
    }

    PyErr_SetString(PyExc_TypeError, "Invalid argument types. Expected int or float.");
    return NULL;
}

static PyMethodDef example_methods[] = {
    {"add", example_add, METH_VARARGS, "Add two integers or two floats."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef example_module = {
    PyModuleDef_HEAD_INIT,
    "pythoncapi_example",
    NULL,
    -1,
    example_methods
};

PyMODINIT_FUNC PyInit_pythoncapi_example(void) {
    libHandle = dlopen("libtest.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "Failed to load the library: %s\n", dlerror());
        return NULL;
    }

    add_float = (AddFloatFunc)dlsym(libHandle, "add_float");
    add_int = (AddIntFunc)dlsym(libHandle, "add_int");

    return PyModule_Create(&example_module);
}
