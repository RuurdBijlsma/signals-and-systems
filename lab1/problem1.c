#include <stdio.h>
#include <tgmath.h>
#include "utils.h"

int main() {

    int x, y;
    scanf("%i %i", &x, &y);
//    int
//            x = -2,
//            y = 0;
    double r = sqrt(pow(x, 2) + pow(y, 2));
    double theta = atan2(y, x);
    if (pi - theta < 0.0001) {
        theta -= pi * 2;
    }

    printf("%.2f %.2f", r, theta);

    return 0;
}
