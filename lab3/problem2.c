#include <math.h>
#include "utils.h"

int *correlator(const int *signal, int lenSignal, const int *kernel, int lenKernel, int *lenOutput) {
    int *reversed = makeIntArray(lenKernel);
    for (int i = 0; i < lenKernel; ++i)
        reversed[i] = kernel[lenKernel - i - 1];

    int lenConvOutput;
    double *output = convolve(signal, lenSignal, reversed, lenKernel, &lenConvOutput);

    *lenOutput = lenConvOutput - (lenKernel - 1) * 2;
    int start = (lenConvOutput - *lenOutput) / 2;
    int end = *lenOutput + start;

    int *rounded = makeIntArray(*lenOutput);
    for (int i = start; i < end; ++i)
        rounded[i - start] = (int) round(output[i]);

    return rounded;

}

double *pearson1D(const int *signal, int lenSignal, const int *kernel, int lenKernel, int *lenOutput) {
    int *correlation = correlator(signal, lenSignal, kernel, lenKernel, lenOutput);
    double *output = makeDoubleArray(*lenOutput);

    double meanH = 0;
    for (int i = 0; i < lenKernel; ++i)
        meanH += kernel[i];
    meanH /= lenKernel;

    for (int d = 0; d < *lenOutput; ++d) {
        double meanX = 0;
        for (int i = 0; i < lenKernel; ++i)
            meanX += signal[i + d];
        meanX /= lenKernel;

        double topPart = correlation[d];
        for (int i = 0; i < lenKernel; ++i)
            topPart -= signal[i + d] * meanH - meanX * kernel[i] + meanX * meanH;

        double inputDistance = 0;
        for (int i = 0; i < lenKernel; ++i)
            inputDistance += pow(signal[i + d] - meanX, 2);

        double kernelDistance = 0;
        for (int i = 0; i < lenKernel; ++i)
            kernelDistance += pow(kernel[i] - meanH, 2);

        double bottomPart = sqrt(inputDistance) * sqrt(kernelDistance);
        output[d] = topPart / bottomPart;
    }
    return output;
}

int main() {
    int lenKernel, lenSignal, lenOutput;

    int *kernel = readSignal(&lenKernel);
    int *signal = readSignal(&lenSignal);

    double *correlated = pearson1D(signal, lenSignal, kernel, lenKernel, &lenOutput);
    printSignalDbl(lenOutput, correlated);

    return 0;
}
