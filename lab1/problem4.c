#include <stdio.h>
#include <tgmath.h>
#include "utils.h"

int main() {

    int fs, n;
    float A, f, phi;
    scanf("%i %i %f %f %f", &fs, &n, &A, &f, &phi);

    printf("[");

    for (int i = 0; i < n; ++i) {
        float t = (float) i * (1 / (float) fs);
        float result = A * cos(2 * pi * f * t + phi);
        printf("%i", (int) result);
        if (i < n - 1)
            printf(",");
    }

    printf("]");

    return 0;
}