#ifndef UTILS
#define UTILS

#include <stdbool.h>

double *convolve(const int *inputSignal, int lenSignal, const int *inputKernel, int lenKernel, int *lenOutput);

void complexMultiply(double reA, double imA, double reB, double imB, double *reOut, double *reIm);

int *readSignal(int *len);

void printSignal(int len, int *x);

void printSignalDbl(int len, double *x);

const double pi;

bool equals(float a, float b, float epsilon);

void *safeMalloc(int sz);

int *makeIntArray(int n);

double *makeDoubleArray(int n);

void destroyArray(void *p);

void printIntArray(int length, int *arr);

void printDoubleArray(int length, double *arr);

#endif
