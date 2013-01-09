#ifndef _DECODAGE_H_
#define _DECODAGE_H_


#include "pgm_file.h"

int extract_byte(unsigned char pixdata[], int n, int *p_pos,
		 unsigned char *p_b, char bitParPixel);

int extract_file(char *fileName, IMAGE_T * p_img, char bitParPixel);

#endif
