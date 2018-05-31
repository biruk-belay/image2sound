#include <stdio.h>
#include <stdlib.h>

#include "jpeglib.h"

#define PIXEL_COMPONENTS 3

typedef struct{
    int width;
    int height;
}image_size;

int read_JPEG_file (char *filename, unsigned char *buffer);
void copy_to_buffer(unsigned char *buffer, int row, unsigned char *data);

/*This function reads the size of the image from the header and copies 
  the value in an image_size struct which is passed as a parameter
 */
int get_image_size(char *filename, image_size *size)
{

    FILE *image;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
    if((image = fopen(filename, "rb")) == NULL){
        fprintf(stderr, "get_image_size: can't open %s \n", filename);
        return 0;
    }

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo); /*initialize decompression object*/
    jpeg_stdio_src(&cinfo, image); /*specify data source (eg, a file)*/
    (void) jpeg_read_header(&cinfo, TRUE); /*read JPEG header*/
    (void) jpeg_start_decompress(&cinfo); /* start decompressor */
    
    /*Return the size of the image from the header info*/
    size->width = cinfo.output_width;
    size->height = cinfo.output_height;

    /*when done clean up and leave*/
    jpeg_destroy_decompress(&cinfo);
    fclose(image);

    return 1;
}

/* This function decompresses a jpg file (pointed to by the filename parameter)
   and copies the extracted RGB into the input buffer passed as a parameter.
*/

int extract_rgb(char *filename, unsigned char *buffer)
{
    int ret_val;


    if((ret_val = read_JPEG_file(filename, buffer) != 1)) {
        fprintf(stderr, "RGB not extracted \n");
        return 0;
    }
            
    return 1;
}

int read_JPEG_file (char *filename, unsigned char *data)
{
  /* This struct contains the JPEG decompression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   */
  
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

  /* More variables */
    FILE * infile;         	/* source file */
    JSAMPARRAY img_buffer;        /* Output row buffer */
    int row_stride;       	/* physical row width in output buffer */
 
    if ((infile = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "read_JPEG_FILE: can't open %s\n", filename);
        return 0;
    }
  
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    printf("everything well \n");
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo); /* start decompressor */
    printf("rows is %i and column is %i \n", cinfo.output_width, cinfo.output_height); 

    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    img_buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo.output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */
  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    (void) jpeg_read_scanlines(&cinfo, img_buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
	copy_to_buffer(img_buffer[0], row_stride, data);
  }
  
   // printf("rows is %i and column is %i \n", cinfo.output_width, cinfo.output_height); 
    (void) jpeg_finish_decompress(&cinfo);/* Step 7: Finish decompression */
    jpeg_destroy_decompress(&cinfo); /*Release JPEG decompression object */
    fclose(infile);
    return 1;
}


void copy_to_buffer(unsigned char *buffer, int row, unsigned char *data)
{
    int i;
    for(i = 0; i<row; i++)
      *data++ = buffer[i];
}
/*
void main()
{
    image_size img_size;
    unsigned int buff_size;

    get_image_size("input.jpg", &img_size);
    buff_size = img_size.width * img_size.height * PIXEL_COMPONENTS;
    
    unsigned char buffer [buff_size];

    read_JPEG_file("input.jpg", buffer);

    //printf(" width is %i and height is %i \n", size.width, size.height);
}*/
