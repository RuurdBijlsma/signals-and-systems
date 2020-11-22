#include <stdio.h>
#include <tgmath.h>
#include "utils.h"
#include "float.h"

int main() {
    int fs;
    double A1, A2, f1, f2, phi1, phi2;
    scanf("%i", &fs);
    scanf("%lf %lf %lf", &A1, &f1, &phi1);
    scanf("%lf %lf %lf", &A2, &f2, &phi2);

    int n = 10000;

    for (int i = 0; i < n; ++i) {
        double t = (double) i * (1 / (double) fs);
        double result1 = A1 * (double)cos(2 * pi * f1 * t + phi1);
        double result2 = A2 * (double)cos(2 * pi * f2 * t + phi2);
        if (!equals((float)result1, (float)result2, FLT_EPSILON)){
            printf("NO");
            return 0;
        }
    }

    printf("YES");
    return 0;
}