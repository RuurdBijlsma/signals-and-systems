#ifndef UTILS
#define UTILS
#include <stdbool.h>

const double pi;

bool equals(float a, float b, float epsilon);

void *safeMalloc(int sz);

int *makeIntArray(int n);

double *makeDoubleArray(int n);

void destroyArray(void *p);

void printIntArray(int length, int *arr);

void printDoubleArray(int length, double *arr);

void demo();

#endif
