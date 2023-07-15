#include <time.h>
#include "./inc/WAVE.h"
#include "./inc/FFT.h"

int main(){
    WAVEinfo w;
// get file informations
    int NumSample = getWAVEinfo(&w);

#ifdef TEST_WAVE
// Checking Informations
    printf("== File Informations =================\n");
    printf("NumChannels: %d\n", w.NumChannels);
    printf("SampleRate: %d\n", w.SampleRate);
    printf("ByteRate: %d\n", w.ByteRate);
    printf("BlockAlign: %d\n", w.BlockAlign);
    printf("BitPerSample: %d\n", w.BitPerSample);
    printf("SoundDataSize: %d\n\n", w.SoundDataSize);
    printf("NumSample: %d\n", NumSample);
    printf("======================================\n");
#endif

// get sound wave data
    short *SoundBuffer = (short *)malloc(sizeof(short) * NumSample);
    getSoundData(SoundBuffer, NumSample);

#ifdef TEST_WAVE
// make SoundData.csv file
    FILE *SoundData_CSV_DEST = fopen("./data_csv/test_SoundData.csv", "w+");

    for(int i = 0; i < NumSample; i++)
        fprintf(SoundData_CSV_DEST, "%d\n", SoundBuffer[i]);

    fclose(SoundData_CSV_DEST);

    free(SoundBuffer);
#endif

#ifdef TEST_FFT
// Checking Informaions
    printf("== File Informations =================\n");
    printf("SampleRate: %d\n", w.SampleRate);
    printf("FFT Size: %d\n", FFT_SIZE);
    printf("======================================\n");

    int n = 0;
    static double Data_Real[FFT_SIZE];
    static double Data_Imaginary[FFT_SIZE];
    static double Data_Result[FFT_SIZE];
    
    n = FFT(FFT_SIZE, Data_Real, Data_Imaginary);

    if(n == -1)
        printf("ERROR: Failed to compute FFT. FFT Size should be 2^n");
    else
        n = FFT_magnitude(FFT_SIZE, Data_Real, Data_Imaginary, Data_Result);

    FILE *FFT_CSV_DEST = fopen("./data_csv/test_FFT_RESULT.csv");
    
    for(int i = 0; i < FFT_SIZE; i++)
        fprintf(FFT_CSV_DEST, "%f\n", Data_Result[i]);

    fclose(FFT_CSV_DEST);
#endif

    return 0;
}