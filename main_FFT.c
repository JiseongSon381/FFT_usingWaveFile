#include ".\inc\FFT.h"
#include ".\inc\WAVE.h"

#define TXT_FILE "sample.csv"

int main(){
    // WAVEinfo w;
// get file informations
    // int NumSample = getWAVEinfo(&w);

// #ifdef DATA_TXT
    FILE *INPUT_TXT = fopen(TXT_FILE, "r");
    
    short SoundBuffer[SampleResol];
    short temp = 0;

    for(int i = 0; i<32768; i++){
        fscanf(INPUT_TXT, "%hd", &temp);
        SoundBuffer[i] = temp;
    }
    printf("COMPLETE: TXT file\n");
// #endif

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
    // short *SoundBuffer = (short *)malloc(sizeof(short) * NumSample);
    // getSoundData(SoundBuffer, NumSample);

// get transformed array
    static double XR[SampleResol];
    static double XI[SampleResol];

    for(int i = 0; i < SampleResol; i++)
        if(i < SampleResol){
            XR[i] = (double) SoundBuffer[i];
        }else{
            XR[i] = 0;
        }

// make SoundData.csv file
// #ifdef DEBUG
    FILE *SoundData_CSV_dest = fopen("SoundData.csv", "w+");

    for(int i = 0; i < SampleResol; i++)
        fprintf(SoundData_CSV_dest, "%d\n", SoundBuffer[i]);

    fclose(SoundData_CSV_dest);
// #endif


    printf("Generate Function Complete\n\n");

    static double Result[SampleResol];


    int n = FFT(SampleResol, XR, XI);
    printf("FFT result: %d\n\n", n);

    if(n < -1) printf("ERROR: FFT not complete");
    else{
        FFT_magnitude(SampleResol, XR, XI, Result);
        printf("Copy Complete\n");
    }

// make FFT_Result.csv file
// #ifdef DEBUG
    FILE *FFT_CSV_dest = fopen("FFT_Result.csv", "w+");

    for(int i = 0; i < SampleResol; i++)
        fprintf(FFT_CSV_dest, "%f, %f\n", 44100 * ((double)i/(double)SampleResol), Result[i]);

    fclose(FFT_CSV_dest);
// #endif

    fclose(INPUT_TXT);

    return 0;
}