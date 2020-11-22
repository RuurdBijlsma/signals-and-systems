#include <stdio.h>
#include <tgmath.h>
#include "utils.h"
#include "float.h"
#include <stdbool.h>

int main() {

    int fs;
    double A, f, phi, x0, x1, x2;
    scanf("%lf %lf %lf", &A, &f, &phi);
    scanf("%lf %lf %lf", &x0, &x1, &x2);

    int n = 100;

    for (int i = 0; i < n; ++i) {
        double t = (double) i * (1 / (double) fs);
        double result1 = A1 * cos(2 * pi * f1 * t + phi1);
        double result2 = A2 * cos(2 * pi * f2 * t + phi2);
        if (!equals((float) result1, (float) result2, FLT_EPSILON)){
            printf("NO");
            return 0;
        }
    }

    printf("YES");
    return 0;
}