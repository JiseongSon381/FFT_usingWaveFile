#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979
#define SampleResol 32768

int FFT(long N, double XR[], double XI[], double WINDOW[]);
int FFT_magnitude(long N, double XR[], double XI[], double Magnitude[]);