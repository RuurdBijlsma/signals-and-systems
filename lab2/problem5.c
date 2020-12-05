#include <stdlib.h>
#include "utils.h"

int main() {
    int lenInput, *input, lenTemplate, *template, lenOutput, *output;
    template = readSignal(&lenTemplate);
    input = readSignal(&lenInput);

    lenOutput = lenInput - lenTemplate + 1;
    output = makeIntArray(lenOutput);

    for (int d = 0; d < lenOutput; ++d) {
        int ySum = 0;
        for (int i = 0; i < lenTemplate; ++i) {
            ySum += input[i + d] * template[i];
        }
        output[d] = ySum;
    }

    printSignal(lenOutput, output);

    free(input);
    free(template);
    free(output);
    return 0;
}
