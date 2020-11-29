#include <stdio.h>
#include <tgmath.h>
#include "utils.h"
#include "float.h"

int main() {
    int f0, f1;
    scanf_s("%i %i", &f0, &f1);

    double f2 = (double)(f0 - f1) / 2;
    double f3 = (double)(f0 + f1) / 2;


    printf("%.2lf %.2lf", f2, f3);
    return 0;
}