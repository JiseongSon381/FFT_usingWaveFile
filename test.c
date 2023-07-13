#include "./inc/WAVE.h"
#include "./inc/FFT.h"

int main(){

    WAVEinfo w;
// get file informations
    int NumSample = getWAVEinfo(&w);

#ifdef TEST_WAVE
// Checking Information
    printf("== File Informations =================\n");
    printf("NumChannels: %d\n", w.NumChannels);
    printf("SampleRate: %d\n", w.SampleRate);
    printf("ByteRate: %d\n", w.ByteRate);
    printf("BlockAlign: %d\n", w.BlockAlign);
    printf("BitPerSample: %d\n", w.BitPerSample);
    printf("SoundDataSize: %d\n\n", w.SoundDataSize);
    printf("NumSample: %d\n", NumSample);
    printf("======================================\n");

// get sound wave data
    short *SoundBuffer = (short *)malloc(sizeof(short) * NumSample);
    getSoundData(SoundBuffer, NumSample);

    makeWAVE(SoundBuffer, NumSample);

// make SoundData.csv file
    FILE *SoundData_CSV_DEST = fopen("./data_CSV/SoundData.csv", "w+");

    for(int i = 0; i < NumSample; i++)
        fprintf(SoundData_CSV_DEST, "%d\n", SoundBuffer[i]);

    fclose(SoundData_CSV_DEST);

    free(SoundBuffer);
#endif

#ifdef TEST_FFT
    static double Data_Re[SampleResol];
    static double Data_Im[SampleResol];

    int n = FFT(SampleResol, XR, XI);

    FILE *FFT_CSV_DEST = fopen("FFT_RESULT.csv");
    
    for(int i = 0; i < SampleResol; i++)
        fprintf(FFT_CSV_DEST, "%d\n", XI[i]);

    fclose(FFT_CSV_DEST);
#endif

    return 0;
}