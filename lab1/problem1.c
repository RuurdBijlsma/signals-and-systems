#include <stdio.h>
#include "utils.h"

int main() {

    int x, y;
    scanf("%i %i", &x, &y);
    double r, theta;

    cartesianToPolar(x, y, &r, &theta);

    printf("%.2lf %.2lf", r, theta);

    return 0;
}
