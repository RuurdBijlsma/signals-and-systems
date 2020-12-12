#ifndef UTILS
#define UTILS

#include <stdbool.h>

double *pearsonCorrelation(int lenTemplate, int *template, int lenInput, int *input, int *lenOutput);

int *correlator(int lenTemplate, const int *template, int lenInput, const int *input, int *lenOutput);

int *applyFilter(int lenInput, const int *input, int lenKernel, const int *kernel, int *lenOutput);

int *readSignal(int *len);

void printSignal(int len, int *x);

void printSignalDbl(int len, double *x);

const double pi;

int gcd(int a, int b);

int lcm(int a, int b);

void polarToCartesian(double r, double theta, double *x, double *y);

void cartesianToPolar(double x, double y, double *r, double *theta);

bool equals(float a, float b, float epsilon);

void *safeMalloc(int sz);

int *makeIntArray(int n);

double *makeDoubleArray(int n);

void destroyArray(void *p);

void printIntArray(int length, int *arr);

void printDoubleArray(int length, double *arr);

void demo();

#endif
