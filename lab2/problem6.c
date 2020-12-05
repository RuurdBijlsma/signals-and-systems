#include <stdlib.h>
#include "utils.h"

int main() {
    int lenInput, *input, lenTemplate, *template, lenOutput;
    template = readSignal(&lenTemplate);
    input = readSignal(&lenInput);

    double *output = pearsonCorrelation(lenTemplate, template, lenInput, input, &lenOutput);
    printSignalDbl(lenOutput, output);

    free(input);
    free(template);
    free(output);
    return 0;
}
