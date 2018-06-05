#include <stdlib.h>

typedef struct{
    int width;
    int height;
}image_size;

int get_image_size(char *filename, image_size *size);
//int read_JPEG_file(char *filename, size_t size, unsigned char *buffer);
int extract_rgb(char *filename, size_t size, unsigned char *buffer);
//int read_JPEG_file(char *filename, size_t size, unsigned char (*data)[size]);
