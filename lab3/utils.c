#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "pearson2D.h"
#include <stdbool.h>

double *convolve(const int *inputSignal, int lenSignal, const int *inputKernel, int lenKernel, int *lenOutput) {
    *lenOutput = lenSignal + lenKernel - 1;
    int size = powerOfTwo(*lenOutput);
    double *reKernel = makeDoubleArray(size);
    double *imKernel = makeDoubleArray(size);
    double *reSignal = makeDoubleArray(size);
    double *imSignal = makeDoubleArray(size);
    for (int i = 0; i < size; ++i) {
        if (i < lenKernel)
            reKernel[i] = inputKernel[i];
        if (i < lenSignal)
            reSignal[i] = inputSignal[i];
        imKernel[i] = 0;
        imSignal[i] = 0;
    }

    fft1D(FORWARD, size, reSignal, imSignal);
    fft1D(FORWARD, size, reKernel, imKernel);

    for (int i = 0; i < size; ++i) {
        double re, im;
        complexMultiply(reSignal[i], imSignal[i], reKernel[i], imKernel[i], &re, &im);
        imSignal[i] = im;
        reSignal[i] = re;
    }

    fft1D(REVERSE, size, reSignal, imSignal);
    return reSignal;
}

void complexMultiply(double reA, double imA, double reB, double imB, double *reOut, double *reIm) {
    double k1 = reB * (reA + imA);
    double k2 = reA * (imB - reB);
    double k3 = imA * (reB + imB);
    *reOut = k1 - k3;
    *reIm = k1 + k2;
}

int *readSignal(int *len) {
    int *x;
    char c;
    scanf("%d:", len);
    x = calloc(*len, sizeof(int));
    do c = (char) getchar(); while (c != '[');
    if (*len > 0) {
        scanf("%d", &x[0]);
        for (int i = 1; i < *len; i++) scanf(",%d", &x[i]);
    }
    do c = (char) getchar(); while (c != ']');
    return x;
}

void printSignal(int len, int *x) {
    printf("%d: [", len);
    if (len > 0) {
        printf("%d", x[0]);
        for (int i = 1; i < len; i++) printf(",%d", x[i]);
    }
    printf("]\n");
}

void printSignalDbl(int len, double *x) {
    printf("%d: [", len);
    if (len > 0) {
        printf("%.5lf", x[0]);
        for (int i = 1; i < len; i++) printf(",%.5lf", x[i]);
    }
    printf("]\n");
}

const double pi = 3.141592653589793238462643383279502884;

bool equals(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}

void *safeMalloc(int sz) {
    void *p = calloc(sz, 1);
    if (p == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", sz);
        exit(EXIT_FAILURE);
    }
    return p;
}

int *makeIntArray(int n) {
    /* allocates dynamic int array of size/length n */
    return safeMalloc(n * sizeof(int));
}

double *makeDoubleArray(int n) {
    /* allocates dynamic double array of size/length n */
    return safeMalloc(n * sizeof(double));
}

void destroyArray(void *p) {
    free(p);
}

void printIntArray(int length, int *arr) {
    printf("[");
    if (length > 0) {
        printf("%d", arr[0]);
        for (int i = 1; i < length; i++) {
            printf(",%d", arr[i]);
        }
    }
    printf("]\n");
}

void printDoubleArray(int length, double *arr) {
    printf("[");
    if (length > 0) {
        printf("%.2lf", arr[0]);
        for (int i = 1; i < length; i++) {
            printf(",%.2lf", arr[i]);
        }
    }
    printf("]\n");
}