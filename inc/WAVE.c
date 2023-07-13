#include "WAVE.h"

// get file informaions from the source file.
unsigned int getWAVEinfo(WAVEinfo *w){
    FILE *src = fopen(SourceFileName, "rb");

    unsigned char data[44];
    unsigned int count = fread(data, 1, 44, src);
    
    w->NumChannels = data[22] + (data[23] << 8);
    w->SampleRate = data[24] + (data[25] << 8) + (data[26] << 16) + (data[27] << 24);
    w->ByteRate = data[28] + (data[29] << 8) + (data[30] << 16) + (data[31] << 24);
    w->BlockAlign = data[32] + (data[33] << 8);
    w->BitPerSample = data[34] + (data[35] << 8);
    w->SoundDataSize = data[40] + (data[41] << 8) + (data[42] << 16) + (data[43] << 24);

    fclose(src);

    return w->SoundDataSize / w->BlockAlign;
}

// get data chunks from the source file
void getSoundData(short SoundBuf[], unsigned int NumSample){
    FILE *src = fopen(SourceFileName, "rb");

    unsigned int count = fread(SoundBuf, 1, 44, src);
    count = fread(SoundBuf, 2, NumSample, src);

    if(count != NumSample){
        printf("ERROR: Not match Number of Samples\n");
    }
}

// make wav file from the input data
void makeWAVE(short SoundBuf[], unsigned int NumSample, unsigned int SampleRate){
    FILE *SRC = fopen(HeaderWaveFileName, "rb");
    FILE *DEST = fopen("./audio_samples/test.wav", "wb");

    unsigned short data[22];
    unsigned int count = fread(data, 2, 22, SRC);
    if(count == 22)
        data[24] = SampleRate / 16;
        data[25] = SampleRate >> 16;
        count = fwrite(data, 2, 22, DEST);
    if(count != 22)
        printf("ERROR: Failed to Copy wav file\n");

    count = fwrite(SoundBuf, 2, NumSample, DEST);

    if(count == NumSample){
        printf("Complete to make wav file.\n");
    }else{
        printf("ERROR: Failed to make wav file.");
    }

    fclose(SRC);
    fclose(DEST);
}