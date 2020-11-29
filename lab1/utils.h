#ifndef UTILS
#define UTILS

#include <stdbool.h>

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
