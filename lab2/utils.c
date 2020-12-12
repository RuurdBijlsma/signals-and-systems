#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include <stdbool.h>

double *pearsonCorrelation(int lenTemplate, int *template, int lenInput, int *input, int *lenOutput) {
    int *correlation = correlator(lenTemplate, template, lenInput, input, lenOutput);
    double *output = makeDoubleArray(*lenOutput);
    double meanH = 0;
    for (int i = 0; i < lenTemplate; ++i) {
        meanH += template[i];
    }
    meanH /= lenTemplate;

    for (int d = 0; d < *lenOutput; ++d) {
        double meanX = 0;
        for (int i = 0; i < lenTemplate; ++i) {
            meanX += input[i + d];
        }
        meanX /= lenTemplate;

        double topPart = correlation[d];
        for (int i = 0; i < lenTemplate; ++i) {
            topPart -= input[i + d] * meanH - meanX * template[i] + meanX * meanH;
        }

        double inputDistance = 0;
        for (int i = 0; i < lenTemplate; ++i) {
            inputDistance += pow(input[i + d] - meanX, 2);
        }

        double templateDistance = 0;
        for (int i = 0; i < lenTemplate; ++i) {
            templateDistance += pow(template[i] - meanH, 2);
        }

        double bottomPart = sqrt(inputDistance) * sqrt(templateDistance);
        output[d] = topPart / bottomPart;
    }
    return output;
}

int *correlator(int lenTemplate, const int *template, int lenInput, const int *input, int *lenOutput) {
    *lenOutput = lenInput - lenTemplate + 1;
    int *output = makeIntArray(*lenOutput);

    for (int d = 0; d < *lenOutput; ++d) {
        int ySum = 0;
        for (int i = 0; i < lenTemplate; ++i) {
            ySum += input[i + d] * template[i];
        }
        output[d] = ySum;
    }
    return output;
}

int *applyFilter(int lenInput, const int *input, int lenKernel, const int *kernel, int *lenOutput) {
    *lenOutput = lenInput + lenKernel - 1;
    int l = 0, *output = makeIntArray(*lenOutput);
    for (int i = 0; i < lenInput + (lenKernel - 1); ++i) {
        int ySum = 0;

        for (int j = 0; j < lenKernel; ++j) {
            int xIndex = i - j;

            if (xIndex >= 0 && xIndex < lenInput) {
                ySum += kernel[j] * input[xIndex];
            }
        }
        output[l++] = ySum;
    }
    return output;
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

int gcd(int a, int b) {
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

void polarToCartesian(double r, double theta, double *x, double *y) {
    *y = r * sin(theta);
    *x = r * cos(theta);
}

void cartesianToPolar(double x, double y, double *r, double *theta) {
    *r = sqrt(pow(x, 2) + pow(y, 2));
    double _theta = atan2(y, x);
    if (pi - _theta < 0.0001) {
        _theta -= pi * 2;
    }
    *theta = _theta;
}

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

void demo() {
    int n = 10;
    int *intArray;
    double *dblArray;

    intArray = makeIntArray(n);
    dblArray = makeDoubleArray(n);
    for (int i = 0; i < n; i++) {
        intArray[i] = i;
        dblArray[i] = 1.0 / (i + 1);
    }
    printf("intArray=");
    printIntArray(n, intArray);
    printf("dblArray=");
    printDoubleArray(n, dblArray);
    destroyArray(dblArray);
    destroyArray(intArray);
}
