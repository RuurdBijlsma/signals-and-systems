#ifndef UTILS
#define UTILS

#include <complex.h>
#include <stdbool.h>

double complex *ifft(double complex *signal, int len);

double complex *fft(const double complex *signal, int lenSignal);

double *convolve(const int *inputSignal, int lenSignal, const int *inputKernel, int lenKernel, int *lenOutput);

double complex *toComplexAndPad(const int *input, int len, int *lenOutput);

double complex *toComplex(int *real, int *imag, int size);

void complexMultiply(double reA, double imA, double reB, double imB, double *reOut, double *reIm);

int *readSignal(int *len);

void printSignal(int len, int *x);

void printSignalDbl(int len, double *x);

void printComplex(double complex x);

void printSignalCmplx(int len, complex double *x);

const double pi;

bool equals(float a, float b, float epsilon);

void *safeMalloc(int sz);

int *makeIntArray(int n);

double *makeDoubleArray(int n);

double _Complex *makeComplexArray(int n);

void destroyArray(void *p);

void printIntArray(int length, int *arr);

void printDoubleArray(int length, double *arr);

#endif
