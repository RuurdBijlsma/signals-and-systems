#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"


int main(void) {
    int length;
    int *intSig = readSignal(&length);
    uint n = (uint) length;
    uint *signal = makeUintArray(length);
    for (int i = 0; i < n; ++i)
        signal[i] = (uint) intSig[i];

//    uint w = 243;
//    uint N = 8192;
    uint prime = 40961;
    uint *r = intt(signal, n, prime);
    printSignalUint(length, r);
}