#ifndef UTILS
#define UTILS

#include <complex.h>
#include <stdbool.h>

typedef unsigned int uint;

uint powMod(uint base, uint exponent, uint prime);

bool isPrime(uint n);

int generatePrimitiveRoot(int prime);

uint *intt(const uint *signal, int len, uint prime);

uint *ntt(const uint *signal, int len, uint prime);

uint *convolveNtt(const int *inputSignal, int lenSignal, const int *inputKernel, int lenKernel, int *lenOutput);

double complex *ifft(double complex *signal, int len);

double complex *fft(const double complex *signal, int lenSignal);

double *convolve(const int *inputSignal, int lenSignal, const int *inputKernel, int lenKernel, int *lenOutput);

double complex *toComplexAndPad(const int *input, int len, int *lenOutput);

double complex *toComplex(int *real, int *imag, int size);

void complexMultiply(double reA, double imA, double reB, double imB, double *reOut, double *reIm);

int powerOfTwo(int n);

int *readSignal(int *len);

const double pi;

bool equals(float a, float b, float epsilon);

void *safeMalloc(int sz);

//int64_t *makeInt64Array(int n);

int *makeIntArray(int n);

unsigned int *makeUintArray(int n);

double *makeDoubleArray(int n);

double _Complex *makeComplexArray(int n);

bool *makeBoolArray(int n);

//u_int64_t *makeUint64Array(int n);

void destroyArray(void *p);

void printIntArray(int length, int *arr);

void printDoubleArray(int length, double *arr);

void printSignal(int len, int *x);

void printSignalDbl(int len, double *x);

void printSignalCmplx(int len, complex double *x);

//void printSignalUint64(int len, u_int64_t *x);

void printSignalUint(int len, unsigned int *x);

void printComplex(double complex x);

//void printSignalInt64(int len, int64_t *x);

#endif
