#include "pearson2D.h"

int main(void) {
    GrayImage image;
    GrayImage mask;
    double **corr;

    /* read input image */
    if (readPGM("emmius.pgm", &image) == -1) {
        fprintf(stderr, "Error: opening image file 'emmius.pgm' failed\n");
        return EXIT_FAILURE;
    }

    /* read mask image */
    if (readPGM("M.pgm", &mask) == -1) {
        fprintf(stderr, "Error: opening mask image file 'M.pgm' failed\n");
        return EXIT_FAILURE;
    }

    /* create correlation image */
    int corrWidth = image.width + mask.width - 1;
    int corrHeight = image.height + mask.height - 1;
    corr = allocDoubleArr2D(corrWidth, corrHeight);

    /* correlate */
    pearsonCorrelator(image, mask, corrWidth, corrHeight, corr);

    /* output image and print number of matches */
    int cnt = match(THRESHOLD, mask.width, mask.height, corr, image);
    printf("%d\n", cnt);
    writePGM("match.pgm", image);

    /* deallocate images */
    free(corr[0]);
    free(corr);
    freeImage(mask);
    freeImage(image);

    return EXIT_SUCCESS;
}
