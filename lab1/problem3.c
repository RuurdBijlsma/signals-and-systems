#include <stdio.h>
#include <tgmath.h>
#include "float.h"

int main() {

    double f, a1, phi1, a2, phi2;
    scanf("%lf %lf %lf %lf %lf", &f, &a1, &phi1, &a2, &phi2);

    double A = sqrt(
            pow(a1 * cos(phi1) + a2 * cos(phi2), 2) +
            pow(a1 * sin(phi1) + a2 * sin(phi2), 2)
    );
    double phi = atan2(
            a1 * sin(phi1) + a2 * sin(phi2),
            a1 * cos(phi1) + a2 * cos(phi2)
    );

    if (fabs(A) < 0.003) {
        printf("x(t)=%.2f", A);
    } else if (phi < 0) {
        printf("x(t)=%.2f*cos(2*pi*%.2f*t%.2f)", A, f, phi);
    } else {
        printf("x(t)=%.2f*cos(2*pi*%.2f*t+%.2f)", A, f, phi);
    }

    return 0;
}
