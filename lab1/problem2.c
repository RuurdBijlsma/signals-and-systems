#include <stdio.h>
#include "utils.h"

int main() {

    double r, theta;
    scanf("%lf %lf", &r, &theta);

    double x, y;
    polarToCartesian(r, theta, &x, &y);

    printf("%.2lf %.2lf", x, y);

    return 0;
}
