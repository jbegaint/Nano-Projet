#ifndef _ENCODAGE_H_
#define _ENCODAGE_H_
 
#include "image.h"
int hide_byte(unsigned char pixdata[], int n, int *p_pos, unsigned char b,
	       char bitParPixel);
 IMAGE_T * hide_file(char *fileName, IMAGE_T * p_img, char bitParPixel);
 
#endif
