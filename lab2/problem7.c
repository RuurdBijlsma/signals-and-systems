#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "float.h"

int main() {
    double t;
    scanf("%lf", &t);

    int lenInput, *input, lenTemplate, *template, lenOutput;
    template = readSignal(&lenTemplate);
    input = readSignal(&lenInput);

    double *output = pearsonCorrelation(lenTemplate, template, lenInput, input, &lenOutput);

    for (int i = 0; i < lenOutput; ++i) {
        if (output[i] >= t - DBL_EPSILON) {
            printf("%i %.5lf\n", i, output[i]);
        }
    }

    free(input);
    free(template);
    free(output);
    return 0;
}
