#include <stdio.h>
#include "WAVE.h"

int main()
{
    WAVEinfo w;
    int NumSample = getWAVEinfo(&w);

    printf("NumChannels: %d\n", w.NumChannels);
    printf("SampleRate: %d\n", w.SampleRate);
    printf("ByteRate: %d\n", w.ByteRate);
    printf("BlockAlign: %d\n", w.BlockAlign);
    printf("BitPerSample: %d\n", w.BitPerSample);
    printf("SoundDataSize: %d\n\n", w.SoundDataSize);
    printf("NumSample: %d\n\n", NumSample);

    short *SoundBuffer = (short *)malloc(sizeof(short) * NumSample);
    // unsigned *L_DATA = (unsigned *)malloc(sizeof(unsigned) * NumSample);
    // unsigned *R_DATA = (unsigned *)malloc(sizeof(unsigned) * NumSample);

    getSoundData(SoundBuffer, NumSample);

    // for(int i = 0; i < NumSample; i++){
    //     L_DATA[i] = SoundBuffer[i] % 16;
    //     R_DATA[i] = SoundBuffer[i] / 16;
    // }

    FILE *fp = fopen("test.csv", "w+");

    for(int i = 0; i < NumSample; i++){
        fprintf(fp, "%d\n", SoundBuffer[i]);
    }

    free(SoundBuffer);
    // free(L_DATA);
    // free(R_DATA);

    fclose(fp);

    return 0;
}