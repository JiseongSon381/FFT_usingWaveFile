#include "FFT.h"

int FFT(long N, double XR[], double XI[]){
// 1. check 2^n count -> if else then return -1
    if ((N !=0) && ((N & (N-1)) != 0) ) return -1;

// 2. calculate Twiddle factor
    long N2 = N >> 1;
    double WR[N2], WI[N2]; /* Real and Imaginary part */
    double T = 2 * PI / N; 
    for(long i=0;i<N2;++i){
        WR[i] = cos(T*i);
        WI[i] = -sin(T*i);
    }

// 3. shuffle input array index to calculate bottom-up style FFT
    int log2N = (int)log2(N);
    double tmp;    
    for(long n = 1; n < N-1; ++n){
        long m = 0; /* reversed num of n*/
        for(int i = 0; i < log2N; ++i){
            m |= ((n >> i) & 1) << (log2N-i-1); /* reverse the bits */
        }
        if(n<m){ /* exchange */
            tmp = XR[n];
            XR[n] = XR[m];
            XR[m] = tmp;
        }
    }

 // 4. execute fft 
    for(int loop=0; loop<log2N; ++loop){
        long regionSize = 1 << (loop+1);      /* if N=8: 2 -> 4 -> 8 */
        long kJump = 1 << (log2N - loop - 1); /* if N=8: 4 -> 2 -> 1 */
        long half = regionSize >> 1;
        for(register long i=0; i<N; i += regionSize){
            long blockEnd = i + half -1;
            long k=0;
            double TR, TI;
            for(register long j=i; j<=blockEnd; ++j){ /* j start from i */
                TR = WR[k] * XR[j+half] - WI[k] * XI[j+half];
                TI = WI[k] * XR[j+half] + WR[k] * XI[j+half];
                
                XR[j+half] = XR[j] - TR;
                XI[j+half] = XI[j] - TI;
                
                XR[j] = XR[j] + TR;
                XI[j] = XI[j] + TI;					
                
                k += kJump;	
            }
        }
    } 
    return 0;
}

int FFT_magnitude(long N, double XR[], double XI[], double Magnitude[]){
    for(int i = 0; i < N; i++){
        double XR_2 = pow(XR[i], 2);
        double XI_2 = pow(XI[i], 2);
        Magnitude[i] = sqrt(XR_2 + XI_2);
    }

    return 0;
}