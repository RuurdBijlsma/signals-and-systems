#include <stdio.h>
#include <tgmath.h>
#include "utils.h"
#include "float.h"

int main() {
    double A, f, phi;
    int x0, x1, x2;
    scanf_s("%lf %lf %lf", &A, &f, &phi);
    scanf_s("%i %i %i", &x0, &x1, &x2);

    double soundSpeed = 343;
    int dist0 = abs(x2 - x0);
    int dist1 = abs(x2 - x1);
    double p0 = 2 * pi * f * dist0 / soundSpeed;
    double p1 = 2 * pi * f * dist1 / soundSpeed;
    double cx0, cy0, cx1, cy1, result, theta;
    polarToCartesian(A, phi + p0, &cx0, &cy0);
    polarToCartesian(A, phi + p1, &cx1, &cy1);
    cartesianToPolar(cx0 + cx1, cy0 + cy1, &result, &theta);

    printf("%.2lf", result);
    return 0;
}