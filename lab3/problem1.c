#include "utils.h"
#include <math.h>

int main(void) {
    int lenKernel, lenSignal, lenOutput;

    int *kernel = readSignal(&lenKernel);
    int *signal = readSignal(&lenSignal);
    double *output = convolve(signal, lenSignal, kernel, lenKernel, &lenOutput);

    int *rounded = makeIntArray(lenOutput);
    for (int i = 0; i < lenOutput; ++i)
        rounded[i] = (int) round(output[i]);
    printSignal(lenOutput, rounded);

    return 0;
}
