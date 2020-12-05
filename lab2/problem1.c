#include <stdlib.h>
#include "utils.h"

int main() {
    int lenInput, *input, lenKernel, *kernel, lenOutput, *output;

    kernel = readSignal(&lenKernel);
    input = readSignal(&lenInput);

    output = applyFilter(lenInput, input, lenKernel, kernel, &lenOutput);

    printSignal(lenOutput, output);

    free(input);
    free(kernel);
    free(output);
    return 0;
}
