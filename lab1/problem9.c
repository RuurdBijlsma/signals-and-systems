#include <stdio.h>
#include <math.h>

int main() {
    int f0, f1;
    scanf("%i %i", &f0, &f1);

    double f2 = (double) (f0 - f1) / 2;
    double f3 = (double) (f0 + f1) / 2;

    printf("%.2lf %.2lf", fabs(f2), fabs(f3));
    return 0;
}