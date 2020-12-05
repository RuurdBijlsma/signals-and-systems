#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    int n;
    scanf("%i", &n);

    int lenInput, *input;
    int lenKernel;
    int *kernel = readSignal(&lenKernel);
    for (int i = 0; i < n - 1; ++i) {
        int lenTempKernel;
        int *tempKernel = readSignal(&lenTempKernel);
        kernel = applyFilter(lenKernel, kernel, lenTempKernel, tempKernel, &lenKernel);
    }
    input = readSignal(&lenInput);
    int lenOutput;
    int *output = applyFilter(lenInput, input, lenKernel, kernel, &lenOutput);

    printSignal(lenOutput, output);

    free(input);
    return 0;
}
