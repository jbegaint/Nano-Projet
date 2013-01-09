#include <stdio.h>
#include <stdlib.h>

#include "image.h"

int hide_byte(unsigned char pixdata[], int n, int *p_pos, unsigned char b,
	      char bitParPixel)
{
	if (bitParPixel != 1 || bitParPixel != 2 || bitParPixel != 4
	    || bitParPixel != 8)
		return 0;
	int m = 8 / bitParPixel;
	if (*p_pos + m >= n)
		return 0;
	int j;
	unsigned char mask = 0x00;
	if (bitParPixel == 1)
		mask = mask | 0x80;
	else if (bitParPixel == 2)
		mask = mask | 0xC0;
	else if (bitParPixel == 4)
		mask = mask | 0xF0;
	else if (bitParPixel == 8)
		mask = mask | 0xFF;
	unsigned char c;
	for (j = 0; j < m; j++) {
		c = (b & mask);
		c = c >> ((m - 1 - j) * bitParPixel);
		pixdata[*p_pos] = pixdata[*p_pos] >> bitParPixel;
		pixdata[*p_pos] = pixdata[*p_pos] << bitParPixel;
		pixdata[*p_pos] = pixdata[*p_pos] | c;
		*p_pos++;
		mask = mask >> bitParPixel;
	}
	return 1;
}

IMAGE_T *hide_file(char *fileName, IMAGE_T * p_img, char bitParPixel)
{
	int p_pos = 0;

	int n;
	n = p_img->nbl * p_img->nbc;
	unsigned char pixdata[n];
	int i;

	for (i = 0; i < n; i++) {
		pixdata[i] = (*p_img->data)[i];
	}

	FILE *fileout;
	fileout = fopen(fileName, "r");
	if (fileout == NULL) {
		printf("Erreur: impossible de creer le fichier\n");
		return NULL;
	}


	int l = 0;
	int nw;
	while (fscanf(fileout, "%c", &b) != EOF) {
		l++;
	}

	unsigned char b;

	for (i = 0; i < 4; i++) {
		b = 0;
		b |= l >> (24 - 8 * i);

		nw = hide_byte(pixdata, n, &p_pos, b, bitParPixel);
	}

	// fseek(fileout,0,0);
	// while(fscanf(fileout,"%c",&b) !=EOF)
	//    {
	//      nw = hide_byte(pixdata,n,&p_pos,b,bitParPixel);
	// }

	for (i = 0; i < n; i++) {
		(*p_img->data)[i] = pixdata[i];
	}

	return p_img;
}
