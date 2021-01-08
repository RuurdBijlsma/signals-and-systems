#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a)>(b) ? (a) : (b))
#define MIN(a, b) ((a)<(b) ? (a) : (b))

#define FORWARD  1
#define REVERSE -1

/* The following threshold should be tweaked for the application */
#define THRESHOLD 0.9

/** Dynamic 2D arrays *******************************/
int **allocIntArr2D(int width, int height);

void freeIntArr2D(int **arr);

double **allocDoubleArr2D(int width, int height);

void freeDoubleArr2D(double **arr);

/*********** images *********/

struct GrayImage {
    int width, height;
    int **im;
};

typedef struct GrayImage GrayImage;

int allocImage(int width, int height, GrayImage *image);

void freeImage(GrayImage image);

int readPGM(char *filename, GrayImage *image);

int writePGM(char *filename, GrayImage image);

/*************************************/

void mirror(GrayImage image);

int powerOfTwo(int n);

/*-------------------------------------------------------------------------
   This computes an in-place complex-to-complex FFT
   x and y are the real and imaginary arrays of 2^m points.
   dir =  FORWARD gives forward transform
   dir =  REVERSE gives reverse transform
*/

void fft1D(int direction, int len, double *re, double *im);

/*-------------------------------------------------------------------------
   Perform a 2D FFT inplace given a complex 2D array
   The direction dir can be FORWARD or REVERSE.
*/

void fft2D(int direction, int width, int height, double **re, double **im);

void fftCorrelator(GrayImage image, GrayImage mask, int corrWidth, int corrHeight, double **corr);

/***********************************************/

int **prefSum(int width, int height, int **im);

int **prefSquaredSum(int width, int height, int **im);

int sum(int row0, int col0, int row1, int col1, int **prefsum);

int sum0(int row0, int col0, int row1, int col1, int **im);

int sqsum(int row0, int col0, int row1, int col1, int **im);

int pearsonCorrelator(GrayImage image, GrayImage mask, int corrWidth, int corrHeight, double **corr);

int drawbox(int y0, int x0, int y1, int x1, int **im);

int match(double p, int mw, int mh, double **pcorr, GrayImage image);
