#include <stdio.h>
#include <tgmath.h>
#include "utils.h"

int main() {

    float r, theta;
    scanf("%f %f", &r, &theta);
//    float
//            x = 1.00,
//            y = 1.57;
    float y = r * sin(theta);
    float x = r * cos(theta);

    printf("%.2f %.2f", x, y);

    return 0;
}
