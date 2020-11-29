#include <stdio.h>
#include <tgmath.h>
#include "utils.h"

int main() {

    int fs, n;
    double A, f, phi;
    scanf("%i %i %lf %lf %lf", &fs, &n, &A, &f, &phi);

    printf("[");

    for (int i = 0; i < n; ++i) {
        double t = (double) i * (1 / (double) fs);
        double result = A * cos(2 * pi * f * t + phi);
        printf("%i", (int) result);
        if (i < n - 1)
            printf(",");
    }

    printf("]");

    return 0;
}