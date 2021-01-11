#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"

typedef unsigned int uint;

int64_t powmod(int64_t base, int64_t exponent, int64_t prime) {
    /* This function computes: base raised to the power exponent modulus prime
     * in math notation: (base^exponent) mod prime
     */
    int64_t pm = 1;
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
    if (n <= 2)
        return false;
    for (int i = 2; i <= n / 2; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int generate_primitive_root(int prime) {
    if (prime == pow(2, 64) - pow(2, 32) + 1)
        return 7;

    for (int i = 0; i < prime; ++i) {
        if (isPrime(i)) {
            bool *s = makeBoolArray(prime + 1);
            for (int j = 0; j < prime; ++j)
                s[j] = false;
            for (int j = 0; j < prime; ++j) {
                uint res = powmod(i, j, prime);
                s[res] = true;
                if (res == 0) // Not allowed
                    break;
            }
            if (s[0])
                continue;

            bool allTrue = true;
            for (int j = 1; j < prime; ++j)
                if (!s[j]) {
                    allTrue = false;
                    break;
                }
            if (allTrue)
                return i;
        }
    }
    return -1;
}

int64_t *_nttOld(const int64_t *x, int n, int64_t q, int64_t r, bool flag_inverse) {
    int64_t *result = makeInt64Array(n);
    if (n <= 1) {
        result[0] = x[0];
        return result;
    }

    int64_t k = (q - 1) / n;
    int64_t wN = powmod(r, k, q);
    printf("should be 1: %ld\n", powmod(wN, n, q));

    int halfLen = n / 2;
    int64_t *evens = makeInt64Array(halfLen);
    int64_t *odds = makeInt64Array(halfLen);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) evens[i / 2] = x[i];
        else odds[i / 2] = x[i];
    }
    int64_t *even = _nttOld(evens, halfLen, q, r, flag_inverse);
    int64_t *odd = _nttOld(odds, halfLen, q, r, flag_inverse);

    for (int i = 0; i < halfLen; ++i) {
        int64_t t = (powmod(wN, i, q) * odd[i]) % q;
        result[i] = (even[i] + t) % q;
        result[i + halfLen] = (even[i] + q - t) % q;
    }

    return result;
}


int64_t *nttOld(const int64_t *x, int n, int64_t q, bool flag_inverse) {
    int64_t r = generate_primitive_root(q);
    return _nttOld(x, n, q, r, flag_inverse);
}
//bool isPrime(int n) {
//    for (int i = 2; i <= n / 2; ++i)
//        if (n % i == 0)
//            return false;
//    return true;
//}

int64_t *ntt(const int64_t *signal, int64_t len, int64_t root, int64_t prime) {
    int64_t *result = makeInt64Array(len);
    if (len == 1) {
        result[0] = signal[0];
        return result;
    }

    int64_t halfLen = len / 2;
    int64_t *evens = makeInt64Array(halfLen);
    int64_t *odds = makeInt64Array(halfLen);
    for (int i = 0; i < len; ++i) {
        if (i % 2 == 0) evens[i / 2] = signal[i];
        else odds[i / 2] = signal[i];
    }
    int64_t *even = ntt(evens, halfLen, root, prime);
    int64_t *odd = ntt(odds, halfLen, root, prime);

    for (int i = 0; i < halfLen; ++i) {
        int64_t oddValue = odd[i];
        int64_t powValue = powmod(root, i, prime);
        int64_t t = (oddValue * powValue) % prime;
        result[i] = (even[i] + t) % prime;
        int64_t temp;
        if (t > even[i]) {
            int64_t a = prime - t;
            temp = even[i] + a;
        } else {
            temp = even[i] - t;
        }
        result[i + halfLen] = temp % prime;
    }

    return result;
}


//# Returns the forward number-theoretic transform of the given vector with
//# respect to the given primitive nth root of unity under the given modulus.
int64_t *transform(const int64_t *invec, int64_t n, int64_t root, int64_t mod) {
    if (n >= mod) {
        exit(0);
    }
    if (1 <= root >= mod) {
        exit(0);
    }

    int64_t *result = makeInt64Array(n);
    for (int i = 0; i < n; ++i) {
        int64_t temp = 0;
        for (int j = 0; j < n; ++j) {
            temp += invec[j] * powmod(root, i * j, mod);
            temp %= mod;
        }
        result[i] = temp;
    }
    return result;
}

int main(void) {
    int length;
    int *intSig = readSignal(&length);
    int64_t n = (int64_t) length;
    int64_t *signal = makeInt64Array(length);
    for (int i = 0; i < n; ++i) {
        signal[i] = (int64_t) intSig[i];
    }

    int64_t w = 243;
//    int64_t N = 8192;
    int64_t prime = 40961;

//    int64_t owo = powmod(w, (prime - 1) / n, prime);
//    int64_t *r = transform(signal, length, owo, prime);
//    int64_t *r = ntt(signal, n, owo, prime);
    int64_t prim_root = generate_primitive_root(prime);
    printf("prim root: %ld\n", prim_root);
    int64_t *r = nttOld(signal, n, prime, false);

    printSignalInt64(length, r);
}

//int main(void) {
//    int64_t table[14][3] = {
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
//        /* note the int64_t (not int) */
//        int64_t N = table[i][0],
//                p = table[i][1],
//                w = table[i][2];
//        printf("N=%4u: p=%5u, w=%5u, w^N=%u\n", N, p, w, powmod(w, N, p));
//    }
//
//    return EXIT_SUCCESS;
//}