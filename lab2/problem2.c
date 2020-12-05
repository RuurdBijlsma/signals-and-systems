#include <stdlib.h>
#include "utils.h"

int main() {
    int lenInput, *input, lenKernel1, *kernel1, lenKernel2, *kernel2, lenOutput1, *output1, lenOutput, *output;

    kernel1 = readSignal(&lenKernel1);
    kernel2 = readSignal(&lenKernel2);
    input = readSignal(&lenInput);

    output1 = applyFilter(lenInput, input, lenKernel1, kernel1, &lenOutput1);
    output = applyFilter(lenOutput1, output1, lenKernel2, kernel2, &lenOutput);

    printSignal(lenOutput, output);

    free(input);
    free(kernel1);
    free(kernel2);
    free(output1);
    free(output);
    return 0;
}
