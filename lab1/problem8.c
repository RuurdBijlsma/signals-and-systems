#include <stdio.h>
#include <tgmath.h>
#include "utils.h"
#include "float.h"

int main() {
    int n;
    scanf_s("%i", &n);
    double *A = makeDoubleArray(n);
    int *T = makeIntArray(n);
    double *phi = makeDoubleArray(n);
    for (int i = 0; i < n; ++i) {
        scanf_s("%lf %i %lf", &A[i], &T[i], &phi[i]);
    }
    int prev = T[0];
    for (int i = 0; i < n; ++i) {
        prev = lcm(prev, T[i]);
    }
    printf("%i", prev);
    return 0;
}