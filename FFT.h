#include <stdio.h>
#include <math.h>

#define PI 3.141593
#define SampleResol 1024

int FFT(long N, double XR[], double XI[]);
int FFT_magnitude(long N, double XR[], double XI[], double Magnitude[]);