#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"

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

bool isPrime(int n) {
    for (int i = 2; i <= n / 2; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int generate_primitive_root(int q) {
    if (q == pow(2, 64) - pow(2, 32) + 1) {
        return 7;
    }
    for (int i = 0; i < q; ++i) {
        if (isPrime(i)) {
            uint *s = makeUintArray(q);
            int sIndex = 0;
            for (int j = 0; j < q; ++j) {
                s[sIndex++] = powmod(i, j, q);
            }
            int val = 0;
            bool allIncreasing = true;
            for (int j = 0; j < q; ++j) {
                if (s[j] != ++val) {
                    allIncreasing = false;
                }
            }
            if (allIncreasing)
                return i;
        }
    }
    return -1;
}

uint *ntt(uint *x, int n, uint q, bool flag_inverse) {
//    assert (q-1) % N == 0 # If this is not true, we won't find a proper k

//    # Compute wN at each step
    uint k = (q - 1) / n;
    int r = generate_primitive_root(q);
    int wN = powmod(r, k, q);
//    assert powmod(wN, N, q) == 1

//    if flag_inverse: # INTT
//            wN = invMod(wN, q)

//    # End recursion
    if (n <= 1)
        return x;

    int halfLen = n / 2;
    uint *evens = makeUintArray(halfLen);
    uint *odds = makeUintArray(halfLen);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0)evens[i / 2] = x[i];
        else odds[i / 2] = x[i];
    }
    uint *even = ntt(evens, halfLen, q, flag_inverse);
    uint *odd = ntt(odds, halfLen, q, flag_inverse);

    uint *result = makeUintArray(n);
    for (int i = 0; i < halfLen; ++i) {
        uint t = powmod(wN, i, q) * odd[i] % q;
        result[i] = (even[i] + t) % q;
        result[i + halfLen] = (even[i] - t) % q;
    }

    return result;
}

int getProperPrime(int N) {
    int k = 1;
    while (!isPrime(k * N + 1)) {
        k++;
    }
    return k * N + 1;
}

int main(void) {
    const int n = 8;
    uint *input = makeUintArray(n);

    uint q = getProperPrime((int) pow(2, 4));
    input[0] = 6;
    input[1] = 0;
    input[2] = 10;
    input[3] = 7;
    input[4] = 2;
    input[5] = 0;
    input[6] = 0;
    input[7] = 0;
    uint *result = ntt(input, n, q, false);
    printSignalUint(n, result);

}

//int main(void) {
//    uint table[14][3] = {
//            8192, 40961, 243,
//            4, 2, 3,
//            7, 2, 3,
//            12, 2, 3,
//            14, 2, 3,
//            15, 2, 3,
//            16, 2, 3,
//            17, 2, 3,
//            18, 2, 3,
//            11, 2, 3,
//            123, 2, 3,
//            134, 2, 3,
//            145, 2, 3,
//            156, 2, 3,
//    };
//    int i;
//    for (i = 0; i < 14; i++) {
//        /* note the uint (not int) */
//        uint N = table[i][0],
//                p = table[i][1],
//                w = table[i][2];
//        printf("N=%4u: p=%5u, w=%5u, w^N=%u\n", N, p, w, powmod(w, N, p));
//    }
//
//    return EXIT_SUCCESS;
//}