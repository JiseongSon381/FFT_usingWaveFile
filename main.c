#include "FFT.h"
#include "WAVE.h"

int main(){
    WAVEinfo w;
// get file informations
    int NumSample = getWAVEinfo(&w);

// Checking Information
#ifdef DEBUG
    printf("== File Informations =================\n");
    printf("NumChannels: %d\n", w.NumChannels);
    printf("SampleRate: %d\n", w.SampleRate);
    printf("ByteRate: %d\n", w.ByteRate);
    printf("BlockAlign: %d\n", w.BlockAlign);
    printf("BitPerSample: %d\n", w.BitPerSample);
    printf("SoundDataSize: %d\n\n", w.SoundDataSize);
    printf("NumSample: %d\n\n", NumSample);
    printf("======================================\n");
#endif

// get sound wave data
    short *SoundBuffer = (short *)malloc(sizeof(short) * NumSample);
    getSoundData(SoundBuffer, NumSample);

// make SoundData.csv file
#ifdef DEBUG
    FILE *SoundData_CSV_dest = fopen("SoundData.csv", "w+");

    for(int i = 0; i < NumSample; i++)
        fprintf(SoundData_CSV_dest, "%d\n", SoundBuffer[i]);

    fclose(SoundData_CSV_dest);
#endif

// get transformed array
    double XR[SampleResol];
    double XI[SampleResol];

    double *Result = (double *)malloc(sizeof(double) * 4096);
    

    // int count = 0;
    for(int i = 1; i <= 4096; i+=1024){
        for(int j = 0; j < SampleResol; j++)
            XR[j] = (double) SoundBuffer[j];
        
        int n = FFT(SampleResol, XR, XI);
        n = FFT_magnitude(SampleResol, XR, XI, Result + (i - 1));
    }

    printf("Copy Complete\n");

// make FFT_Result.csv file
#ifdef DEBUG
    FILE *FFT_CSV_dest = fopen("FFT_Result.csv", "w+");

    for(int i = 0; i < 4096; i++)
        fprintf(FFT_CSV_dest, "%f\n", Result[i]);

    fclose(FFT_CSV_dest);
#endif

    free(SoundBuffer);
    free(Result);
    return 0;
}