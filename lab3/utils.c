#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include "utils.h"

double complex *ifft(double complex *signal, int len) {
    double complex *result = makeComplexArray(len);
    for (int i = 0; i < len; ++i)
        result[i] = conj(signal[i]);
    result = fft(result, len);
    for (int i = 0; i < len; ++i)
        result[i] = conj(result[i]) / len;
    return result;
}

double complex *fft(const double complex *signal, int len) {
    double complex *result = makeComplexArray(len);
    if (len == 1) {
        result[0] = signal[0];
        return result;
    }

    int halfLen = len / 2;
    double complex *evens = makeComplexArray(halfLen);
    double complex *odds = makeComplexArray(halfLen);
    for (int i = 0; i < len; ++i) {
        if (i % 2 == 0)evens[i / 2] = signal[i];
        else odds[i / 2] = signal[i];
    }
    double complex *even = fft(evens, halfLen);
    double complex *odd = fft(odds, halfLen);

    for (int i = 0; i < halfLen; ++i) {
        double complex expt = cexp(-2 * pi * I * i / len) * odd[i];
        result[i] = even[i] + expt;
        result[i + halfLen] = even[i] - expt;
    }

    return result;
}

double *convolve(const int *inputSignal, int lenSignal, const int *inputKernel, int lenKernel, int *lenOutput) {
    *lenOutput = lenSignal + lenKernel - 1;
    int size = powerOfTwo(*lenOutput);
    double complex *kernel = makeComplexArray(size);
    double complex *signal = makeComplexArray(size);
    for (int i = 0; i < size; ++i) {
        kernel[i] = i < lenKernel ? inputKernel[i] : 0;
        signal[i] = i < lenSignal ? inputSignal[i] : 0;
    }

    double complex *kFft = fft(kernel, size);
    double complex *sFft = fft(signal, size);

    for (int i = 0; i < size; ++i)
        sFft[i] *= kFft[i];

    double complex *iFft = ifft(sFft, size);

    double *result = makeDoubleArray(size);
    for (int i = 0; i < size; ++i)
        result[i] = creal(iFft[i]);
    return result;
}

double complex *toComplexAndPad(const int *input, int len, int *lenOutput) {
    *lenOutput = powerOfTwo(len);
    double complex *result = makeComplexArray(*lenOutput);
    for (int i = 0; i < len; ++i)
        result[i] = i < len ? input[i] : 0;
    return result;
}

double complex *toComplex(int *real, int *imag, int size) {
    double complex *result = makeComplexArray(size);
    for (int i = 0; i < size; ++i)
        result[i] = real[i] + imag[i] * I;
    return result;
}

int powerOfTwo(int n) {
    int p2;
    p2 = 1;
    while (p2 < n) {
        p2 *= 2;
    }
    return p2;
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

int64_t *makeInt64Array(int n) {
    /* allocates dynamic int array of size/length n */
    return safeMalloc(n * sizeof(int64_t));
}

u_int64_t *makeUint64Array(int n) {
    /* allocates dynamic int array of size/length n */
    return safeMalloc(n * sizeof(u_int64_t));
}

bool *makeBoolArray(int n) {
    /* allocates dynamic int array of size/length n */
    return safeMalloc(n * sizeof(bool));
}

unsigned int *makeUintArray(int n) {
    /* allocates dynamic int array of size/length n */
    return safeMalloc(n * sizeof(unsigned int));
}

double *makeDoubleArray(int n) {
    /* allocates dynamic double array of size/length n */
    return safeMalloc(n * sizeof(double));
}

double complex *makeComplexArray(int n) {
    /* allocates dynamic double array of size/length n */
    return safeMalloc(n * sizeof(double complex));
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

void printComplex(complex double x) {
    printf("%.3lf+%.3lfi\n", creal(x), cimag(x));
}

void printSignalCmplx(int len, complex double *x) {
    printf("%d: [", len);
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(",");
        printf("%.1lf+%.1lfi", creal(x[i]), cimag(x[i]));
    }
    printf("]\n");
}

void printSignalUint(int len, unsigned int *x) {
    printf("%d: [", len);
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(",");
        printf("%u", x[i]);
    }
    printf("]\n");
}

void printSignalUint64(int len, u_int64_t *x) {
    printf("%d: [", len);
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(",");
        printf("%lu", x[i]);
    }
    printf("]\n");
}

void printSignalInt64(int len, int64_t *x) {
    printf("%d: [", len);
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(",");
        printf("%ld", x[i]);
    }
    printf("]\n");
}