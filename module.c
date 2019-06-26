#include <Python.h>
#include "block_cipher.h"

static PyObject *py_encrypt_ecb(PyObject *self, PyObject *args) {
   unsigned char *ciphertext = NULL;
   char *         plaintext, *hex_key;
   int            len;

   if (!PyArg_ParseTuple(args, "z#s", &plaintext, &len, &hex_key)) {
      return(NULL);
   }

   encrypt_ecb(plaintext, len, hex_key, &ciphertext);
   if (ciphertext == NULL) {
      return(NULL);
   }

   PyObject *res = PyBytes_FromString((char *)ciphertext);
   free(ciphertext);
   return(res);
}

static PyObject *py_decrypt_ecb(PyObject *self, PyObject *args) {
   unsigned char *plaintext = NULL;
   char *         ciphertext, *hex_key;
   int            len;

   if (!PyArg_ParseTuple(args, "z#s", &ciphertext, &len, &hex_key)) {
      return(NULL);
   }

   decrypt_ecb(ciphertext, len, hex_key, &plaintext);
   if (plaintext == NULL) {
      return(NULL);
   }
   PyObject *res = PyBytes_FromString((char *)plaintext);
   free(plaintext);
   return(res);
}

// Module's Function Definition struct
static PyMethodDef present80Methods[] = {
   { "encrypt_ecb", py_encrypt_ecb, METH_VARARGS, "Encrypt a string using PRESENT-80 with the ECB mod eof operation" },
   { "decrypt_ecb", py_decrypt_ecb, METH_VARARGS, "Decrypt a string using PRESENT-80 with the ECB mod eof operation" },
   { NULL,          NULL,                      0, NULL                                                               }
};

// Module Definition struct
static struct PyModuleDef present80Module = {
   PyModuleDef_HEAD_INIT,
   "present_80_module",
   "PRESENT-80 Module",
   -1,
   present80Methods
};

// Initializes module using our above struct
PyMODINIT_FUNC PyInit_present_80_module(void) {
   return(PyModule_Create(&present80Module));
}
