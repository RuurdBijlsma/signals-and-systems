#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

uint powmod(uint base, uint exponent, uint prime) {
    /* This function computes: base raised to the power exponent modulus prime
     * in math notation: (base^exponent) mod prime
     */
    uint pm = 1;
    base = base % prime;
    while (exponent > 0) {
        if (exponent % 2 == 1) { /* exponent is odd */
            pm = (pm * base) % prime;
        }
        exponent /= 2;
        base = (base * base) % prime;
    }
    return pm;
}

int main(int argc, char *argv[]) {
    int i;
    for (i = 0; i < 14; i++) {
        /* note the uint (not int) */
        uint N = table[i][0], p = table[i][1], w = table[i][2];
        printf("N=%4u: p=%5u, w=%5u, w^N=%u\n", N, p, w, powmod(w, N, p));
    };

    return EXIT_SUCCESS;
}