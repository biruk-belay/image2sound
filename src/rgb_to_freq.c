#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "extract_rgb.h"
#include "rgb_to_freq.h"

#define PIXEL_COMPONENTS 3
#define MAX(x, y, z) x>y ? x>z ? x : z : y>z ? y : z
#define MIN(x, y, z) x<y ? x<z ? x : z : y<z ? y : z

int rgb_to_hsb( int red, int green, int blue, float *hue, float *sat, float *bright);

int rgb_to_freq(unsigned char *pixel_data, float *freq_data, image_size size)
{
    unsigned char *rgb_pixel = pixel_data;
    float *freq_amp_map = freq_data;
    int i, j, k;
    float hue, saturation, brightness;
    
    for(i=0, k=0; i<(size.width*size.height * 3); i+=3, k+=2) {
        rgb_to_hsb(*(rgb_pixel+i), *(rgb_pixel+i+1), *(rgb_pixel+i+2),
                &hue, &saturation, &brightness);
       
        if(hue == -1)
            *(freq_amp_map+k) = FREQ_1;

        else if(hue == -2)
           *(freq_amp_map+k) = FREQ_14;

        if(hue > 0 && hue <= 0.5) 
           *(freq_amp_map+k) = FREQ_2;
        
        else if(hue > 0.5 && hue <= 1)
           *(freq_amp_map+k) = FREQ_3;
        
        else if(hue > 1.0 && hue <= 1.5)
            *(freq_amp_map+k) = FREQ_4;
        
        else if(hue > 1.5 && hue <= 2.0)
            *(freq_amp_map+k) = FREQ_5; 
        
        else if(hue > 1.0 && hue <= 2.5)
            *(freq_amp_map+k) = FREQ_6;
        
        else if(hue > 2.5 && hue <= 3.0)
            *(freq_amp_map+k) = FREQ_7;
        
        else if(hue > 3.0 && hue <= 3.5)
            *(freq_amp_map+k) = FREQ_8;
        
        else if(hue > 3.5 && hue <= 4.0)
            *(freq_amp_map+k) = FREQ_9;
        
        else if(hue > 4.0 && hue <= 4.5)
            *(freq_amp_map+k) = FREQ_10;
        
        else if(hue > 4.5 && hue <= 5.0)
            *(freq_amp_map+k) = FREQ_11;
        
        else if(hue > 5.0 && hue <= 5.5)
            *(freq_amp_map+k) = FREQ_12;
        else 
            *(freq_amp_map+k) = FREQ_13;

        *(freq_amp_map+k+1) = brightness * saturation;
        
            //printf("freq and amplitude equal %i\n", i);    
       printf("in rgb to freq %f %f \n", hue, brightness * saturation);
    }
    return 1;
}

int rgb_to_hsb( int red, int green, int blue, float *hue, float *sat, float *bright)
{
    float min, max, delta;
    
    assert((red <= 255)  || (red >= 0)   || 
          (green <= 255) || (green >= 0) || 
          (blue <= 255)  || (blue >= 0));
    
    float r = (float) red/255.0;
    float b = (float) blue/255.0;
    float g = (float) green/255.0;

    min = MIN(r, b, g);
    max = MAX(r, b, g);
    
    //printf("max and min %f %f \n", max, min);
    *bright = max;
    delta = max - min;
   
    if(delta == 0 && max != 0){
        *hue = -2;
        *sat = max;       // s
        return 0;
    }
    else if(delta == 0 && max == 0) {
        // r = g = b = 0        // s = 0, v is undefined
        *sat = 1;
        *bright = 1;
        *hue = -1;
        return 0;
    }
    else
        *sat = delta / max;

    if(r == max)
        *hue = ( g - b ) / delta;     // between yellow & magenta
    else if(g == max)
        *hue = 2 + ( b - r ) / delta; // between cyan & yellow
    else if (b == max)
        *hue = 4 + ( r - g ) / delta; // between magenta & cyan 
    else 
        *hue = -2; 
    
        //*hue*= 60;               // degrees
    //if( *hue < 0 )
      //  *hue += 360;
    
    printf("in rgb to hsb %f %i %f %i %f %i %f %f  \n", r,red ,b ,blue,g ,green, min, max);    
    return 1;
}
/*
void main()                                                                               
{
    image_size img_size;
    unsigned int pixel_buff_size, freq_buff_size;
    unsigned int i;

    get_image_size("input_9.jpg", &img_size);
    pixel_buff_size = img_size.width * img_size.height * PIXEL_COMPONENTS;
    freq_buff_size = img_size.height * img_size.width * 2;

    printf(" width is %i and height is %i \n", img_size.width, img_size.height);      
    printf("here \n"); 
    printf(" pixel size is %i \n", pixel_buff_size);      

    unsigned char buffer [pixel_buff_size];
    unsigned char *buff_ptr = buffer;
    float freq_mapping[freq_buff_size];
    
    printf("ptr is %p \n", buff_ptr);
    extract_rgb("input_9.jpg", pixel_buff_size, buff_ptr);
   
    rgb_to_freq(buffer, freq_mapping, img_size);
} 
*/
