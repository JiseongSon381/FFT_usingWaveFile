#include <stdio.h>
#include <stdlib.h>

#define SourceFileName "./audio_samples/440Hz.wav"
#define HeaderWaveFileName "./audio_samples/none.wav"

typedef struct {
    unsigned short NumChannels;
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned short BlockAlign;
    unsigned short BitPerSample;
    unsigned int SoundDataSize;
} WAVEinfo;

/*
    NumChannels: The number of Sound Track (1: Mono, 2: Stereo)
    SampleRate: The number of sampling per second
    ByteRate: Bytes of sound data per second
    BlockAlign: Bytes of sound data per Sample
    BirPerSample: Bits of a track sound data per Sample
    SoundDataSize: Data Size except information datas (Whole Size - Information Part Size)

    getWAVEinfo returns the number of bytes per sample
*/

unsigned int getWAVEinfo(WAVEinfo *w);
void getSoundData(short SoundBuf[], unsigned int NumSample);
void makeWAVE(short SoundBuf[], unsigned int NumSample, unsigned int SampleRate);