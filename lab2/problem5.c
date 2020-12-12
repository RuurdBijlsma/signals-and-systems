#include <stdlib.h>
#include "utils.h"

int main() {
    int lenInput, *input, lenTemplate, *template, lenOutput;
    template = readSignal(&lenTemplate);
    input = readSignal(&lenInput);

    int *output = correlator(lenTemplate, template, lenInput, input, &lenOutput);
    printSignal(lenOutput, output);

    free(input);
    free(template);
    free(output);
    return 0;
}
