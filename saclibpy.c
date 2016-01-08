#include "Python.h"
#include <numpy/arrayobject.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sac.h"
#include "sacio.h"
#include <math.h>

#define NPY_NO_DEPRECATED_API NPY_1_10_API_VERSION

static char module_docstring[] = "An python interface for using SAC library";
static char sacxapiir_docstring[] = "Filtering seismic data";
static PyObject *saclibpy_sacxapiir(PyObject *self, PyObject *args);
static PyMethodDef module_methods[] = {{"sacxapiir", saclibpy_sacxapiir, METH_VARARGS, sacxapiir_docstring}, {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC initsaclibpy(void) {
    PyObject *m = Py_InitModule3("saclibpy", module_methods, module_docstring);
    if (m==NULL)
        return;
    import_array();
}

static PyObject *saclibpy_sacxapiir(PyObject *self, PyObject *args)
{
    PyObject *yarray_obj;
    double low, high, attenuation, transition_bandwidth;
    int order, passes;
    double delta_d;
    
    if (!PyArg_ParseTuple(args, "Oddidddi", &yarray_obj, &transition_bandwidth, &attenuation, &order, &low, &high, &delta_d, &passes))
    {
        return NULL;
    }
    PyObject *yarray = PyArray_FROM_OTF(yarray_obj, NPY_FLOAT, NPY_IN_ARRAY);
    if (yarray==NULL) {
        Py_XDECREF(yarray);
        return NULL;
    }
    int nlen = (int)PyArray_DIM(yarray, 0);
    float *y = (float *)PyArray_DATA(yarray);
    //float sn[30], sd[30];
    //int nsects;
    //design(4, "BP", "BU", 0.0, 0.0, 0.01, 0.1, 0.02, sn, sd, &nsects);
    //printf("%i\n", nsects); fflush(stdout);
    //apply(y, nlen, 0, sn, sd, nsects);
    xapiir(y, nlen, SAC_BUTTERWORTH, transition_bandwidth, attenuation, order, SAC_BANDPASS, low, high, delta_d, passes);
    //printf("%i %f %f %f %f %i\n", nlen, yy[200], low, high, delta_d, passes); fflush(stdout);
    /*PyObject *filt_yarray = PyList_New(nlen);
    if (!filt_yarray)
        return NULL;
    for (i=0; i<nlen; i++) {
        PyObject *ydata = PyFloat_FromDouble(y[i]);
        if (!ydata) {
            Py_DECREF(filt_yarray);
            return NULL;
        }
        PyList_SET_ITEM(filt_yarray, i, ydata);
    }*/
    npy_intp dims[1] = {nlen};
    PyObject *filt_yarray = PyArray_SimpleNewFromData(1, dims, NPY_FLOAT, y);
    Py_DECREF(yarray);
    return filt_yarray;
}
