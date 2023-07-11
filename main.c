#include "FFT.h"
#include "WAVE.h"

#define DEBUG

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
    double XR[1024];
    double XI[1024];

    double Result[1024][NumSample];

    int count = 0;
    for(int i = 0; i < NumSample; ){
        for(int j = 0; j < 1024; j++)
            XR[j] = (double) SoundBuffer[j];
            int n = FFT(1024, XR, XI);
            
    }

    printf("Copy Complete\n");



    

#ifdef DEBUG
    FILE *FFT_CSV_dest = fopen("FFT_Result.csv", "w+");

    for(int i = 0; i < NumSample; i++)
        fprintf(FFT_CSV_dest, "%f\n", XR[i]);

    fclose(FFT_CSV_dest);
#endif
    free(SoundBuffer);
    return 0;
}