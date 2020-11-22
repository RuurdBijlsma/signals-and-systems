#include <stdio.h>
#include <tgmath.h>
#include "utils.h"

int main() {

    float f, a1, phi1, a2, phi2;
    scanf("%f %f %f %f %f", &f, &a1, &phi1, &a2, &phi2);
//    float
//            x = 1.00,
//            y = 1.57;
    float A = sqrt(2 * pow(a1, 2) * (1 + cos(phi1) * cos(phi2) + sin(phi1) * sin(phi2)));
    float phi = atan((sin(phi1)+sin(phi2)) / (cos(phi1)+cos(phi2)));

    if(A == 0){
        printf("x(t)=%.2f", A);
    }else{
        printf("x(t)=%.2f*cos(2*pi*%.2f+%.2f)", A, f, phi);
    }

    return 0;
}
