//#include "extract_rgb.h"

#define PIXEL_COMPONENTS 3

enum FREQ_LEVLS {                                                                         
    FREQ_1, 
    FREQ_2 = 3,
    FREQ_3,
    FREQ_4,                                                                               
    FREQ_5,                                                                               
    FREQ_6,
    FREQ_7,
    FREQ_8,
    FREQ_9,                                                                               
    FREQ_10,                                                                              
    FREQ_11,
    FREQ_12,
	FREQ_13,
	FREQ_14 = 18,
};

//int rgb_to_hsb( int red, int green, int blue, float *hue, float *sat, float *bright);
int rgb_to_freq(unsigned char *pixel_data, float *freq_data, image_size size);
