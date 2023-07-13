#include "WAVE.h"

unsigned int getWAVEinfo(WAVEinfo *w){
    FILE *src = fopen(WaveFileName, "rb");

    // 1. get informations of the wave file
    char data[44];
    unsigned int count = fread(data, 1, 44, src);
    
    unsigned short *NumChannels = &data[22];
    unsigned int *SampleRate = &data[24];
    unsigned int *ByteRate = &data[28];
    unsigned short *BlockAlign = &data[32];
    unsigned short *BitPerSample = &data[34];
    unsigned int *SoundDataSize = &data[40];
    
    w->NumChannels = *NumChannels;
    w->SampleRate = *SampleRate;
    w->ByteRate = *ByteRate;
    w->BlockAlign = *BlockAlign;
    w->BitPerSample = *BitPerSample;
    w->SoundDataSize = *SoundDataSize;

    fclose(src);

    return w->SoundDataSize / w->BlockAlign;
}

void getSoundData(short SoundBuf[], int NumSample){
    FILE *src = fopen(WaveFileName, "rb");

    int count = fread(SoundBuf, 1, 44, src);
    count = fread(SoundBuf, 2, NumSample, src);

    if(count != NumSample){
        printf("Error: Not match Number of Samples\n");
    }
}

void writeWAVE(short SoundBuf[], int NumSample, short Offset){
    
}