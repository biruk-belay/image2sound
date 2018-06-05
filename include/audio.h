#include "extract_rgb.h"
#include "portaudio.h"

#define SAMPLE_RATE         8000
#define FRAMES_PER_BUFFER   64
#define FREQ                80.0
//#define FREQ_2 587.0

#ifndef M_PI
#define M_PI                3.14159265
#endif

#define TABLE_SIZE          800 
#define NUM_SECONDS         20

typedef struct{
    float sine[TABLE_SIZE];
    float *freq_ptr;
    image_size size;
    int *left_phase;
    int *right_phase;
    char message[20];
}paTestData;
/*
int patestCallback( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData );
*/
void StreamFinished(void* userData);
