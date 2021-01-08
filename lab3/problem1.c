#include "pearson2D.h"
#include "utils.h"

int main() {
    int lenKernel, lenSignal, lenOutput;

    int *kernel = readSignal(&lenKernel);
    int *signal = readSignal(&lenSignal);
    double *reOutput = convolve(signal, lenSignal, kernel, lenKernel, &lenOutput);


    int *rounded = makeIntArray(lenOutput);
    for (int i = 0; i < lenOutput; ++i)
        rounded[i] = (int) round(reOutput[i]);

    printSignal(lenOutput, rounded);

    return 0;
}
