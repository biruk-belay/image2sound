#include <stdio.h>
#include <stdlib.h>

#include "portaudio.h"
#include "audio.h"

/*
#define SAMPLE_RATE         800
#define FRAMES_PER_BUFFER   64
#define FREQ                80.0
#define FREQ_2              587.0

#ifndef M_PI 
#define M_PI  (3.14159265)
#endif

#define TABLE_SIZE   (800)


typedef struct                                                                            
{                                                                                         
	float sine[TABLE_SIZE];                                                               
    float *freq_ptr;
    int   left_phase;
    int right_phase;
    char message[20];
}paTestData;
*/

int patestCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
{
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;

    static long column_time = 0;
    int freq_offset_left, freq_offset_right;
    int amp_offset_left = 0, amp_offset_right = 0;
    static int k = 0;
    int i, j;
    
    //printf("in call back \n");
 
    //printf(" ptr in callback %p %p \n", data->left_phase, data->right_phase);
    for( i = 0; i < framesPerBuffer; i++ ) {
	
        column_time = (++column_time) % SAMPLE_RATE / 10;

        for(j = 0; j < (data->size).height; j++) {
            amp_offset_left  = (2 * j + 1) + ((data->size).height * k);
            freq_offset_left = (2 * j)     + ((data->size).height * k);
            
            *out = data->sine[*((data->left_phase) + j)] * (*(data->freq_ptr + amp_offset_left));
            *((data->left_phase) + j) += *((data->freq_ptr) + freq_offset_left);

            if(*((data->left_phase) + j) >= TABLE_SIZE) *((data->left_phase) + j) -= TABLE_SIZE;
            *out /= 1;
        }

        out++;
        //same thing for right phase
        for(j = 0; j < (data->size).height; j++) {
            amp_offset_right  = (2*j + 1) + ((data->size).height * k);
            freq_offset_right = (2*j)     + ((data->size).height * k);
            
            *out = data->sine[*((data->right_phase) + j)] * (*(data->freq_ptr + amp_offset_right));
            *((data->right_phase) +j) += (*(data->freq_ptr + freq_offset_right));

            if(*((data->right_phase) + j) >= TABLE_SIZE) *((data->right_phase) +j) -= TABLE_SIZE;
            *out /= 1;
        }
        
        out++;

        //calculate the timing here 
        k = (++k) % data->size.width;
		if(column_time == 0)
			for(j == 0; j < (data->size).height; j++) {
                *((data->right_phase) +j) = 0;
                *((data->left_phase) +j)  = 0;
			}
        }

        return paContinue;    
}

void StreamFinished( void* userData )
{
       paTestData *data = (paTestData *) userData;
          printf( "Stream Completed: %s\n", data->message );
}
