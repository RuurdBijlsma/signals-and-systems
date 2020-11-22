#include <stdio.h>
#include <tgmath.h>
#include "utils.h"

int main() {

    int fs, n, m;
    scanf("%i %i", &fs, &n);
    scanf("%i", &m);
    double *A = makeDoubleArray(m);
    double *f = makeDoubleArray(m);
    double *phi = makeDoubleArray(m);
    for (int i = 0; i < m; ++i) {
        scanf("%lf %lf %lf", &A[i], &f[i], &phi[i]);
    }

    printf("[");
    for (int i = 0; i < n; ++i) {
        double t = (double) i * (1 / (double) fs);
        double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += A[j] * cos(2 * pi * f[j] * t + phi[j]);
        }
        printf("%i", (int) sum);
        if (i < n - 1)
            printf(",");
    }
    printf("]");


    return 0;
}