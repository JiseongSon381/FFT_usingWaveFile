#include ".\inc\FFT.h"
#include ".\inc\WAVE.h"

#define Data_FILE "sample.csv"

int main(){
    WAVEinfo w;
// get file informations
    int NumSample = getWAVEinfo(&w);

// #ifdef DATA_TXT
    FILE *INPUT_DATA = fopen(Data_FILE, "r");
    
    short SoundBuffer[FFT_SIZE];
    short temp = 0;

    for(int i = 0; i<32768; i++){
        fscanf(INPUT_DATA, "%hd", &temp);
        SoundBuffer[i] = temp;
    }
    printf("COMPLETE: TXT file\n");
// #endif

// Checking Informations
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

// get transformed array
    static double XR[FFT_SIZE];
    static double XI[FFT_SIZE];

    for(int i = 0; i < FFT_SIZE; i++)
        if(i < FFT_SIZE){
            XR[i] = (double) SoundBuffer[i];
        }else{
            XR[i] = 0;
        }

// make SoundData.csv file
#ifdef DEBUG
    FILE *SoundData_CSV_dest = fopen("RawSoundData.csv", "w+");

    for(int i = 0; i < FFT_SIZE; i++)
        fprintf(SoundData_CSV_dest, "%d\n", SoundBuffer[i]);

    fclose(SoundData_CSV_dest);
#endif


    printf("Generate Function Complete\n\n");

    static double Result[FFT_SIZE];
    static double Window[FFT_SIZE];

    int n = FFT(FFT_SIZE, XR, XI, Window);
    printf("FFT result: %d\n\n", n);

    if(n < -1) printf("ERROR: FFT not complete");
    else{
        FFT_magnitude(FFT_SIZE, XR, XI, Result);
        printf("Copy Complete\n");
    }

// make FFT_Result.csv file
#ifdef DEBUG
    FILE *FFT_CSV_dest = fopen("FFT_Result.csv", "w+");

    for(int i = 0; i < FFT_SIZE; i++)
        fprintf(FFT_CSV_dest, "%f, %f\n", 44100 * ((double)i/(double)FFT_SIZE), Result[i]);

    fclose(FFT_CSV_dest);
#endif

    fclose(INPUT_DATA);

    return 0;
}