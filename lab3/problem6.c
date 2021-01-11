#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"


int main(void) {
    int lenKernel, lenSignal, lenOutput;

    int *kernel = readSignal(&lenKernel);
    int *signal = readSignal(&lenSignal);
    uint *output = convolveNtt(signal, lenSignal, kernel, lenKernel, &lenOutput);

    printSignalUint(lenOutput, output);
}