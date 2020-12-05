#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    int lenInput, *input, lenOutput, *output;
    input = readSignal(&lenInput);
    output = readSignal(&lenOutput);

    int lenKernel = lenOutput - lenInput + 1;

    double *kernelDoubles = makeDoubleArray(lenKernel);
    for (int n = 0; n < lenKernel; ++n) {
        kernelDoubles[n] = output[n];
        int lower = 0;
        if (n >= lenInput) {
            lower = n - lenInput + 1;
        }
        for (int i = lower; i < n; ++i) {
            kernelDoubles[n] -= kernelDoubles[i] * input[n - i];
        }
        kernelDoubles[n] /= input[0];
    }

    int *kernel = makeIntArray(lenKernel);
    for (int i = 0; i < lenKernel; ++i) {
        kernel[i] = (int) kernelDoubles[i];
    }
    int lenTestOutput, *testOutput;
    testOutput = applyFilter(lenInput, input, lenKernel, kernel, &lenTestOutput);
    bool noFir = false;
    for (int i = 0; i < lenTestOutput; ++i) {
        if (output[i] != testOutput[i]) {
            noFir = true;
            break;
        }
    }
    if (noFir) {
        printf("NO FIR");
    } else {
        printSignal(lenKernel, kernel);
    }

    free(input);
    free(output);
    free(kernelDoubles);
    return 0;
}
