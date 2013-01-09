#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "encodage.h"

// Barbossa
// int hide_byte_1(unsigned char pixdata[], int n, int *p_pos, unsigned char b,
// 	      char bitParPixel)
// {
// 	if (bitParPixel != 1 || bitParPixel != 2 || bitParPixel != 4
// 	    || bitParPixel != 8)
// 		return 1;
// 	int m = 8 / bitParPixel;
// 	if (*p_pos + m >= n)
// 		return 1;
// 	int j;
// 	unsigned char mask = 0x00;
// 	if (bitParPixel == 1)
// 		mask = mask | 0x80;
// 	else if (bitParPixel == 2)
// 		mask = mask | 0xC0;
// 	else if (bitParPixel == 4)
// 		mask = mask | 0xF0;
// 	else if (bitParPixel == 8)
// 		mask = mask | 0xFF;
// 	unsigned char c;
// 	for (j = 0; j < m; j++) {
// 		c = (b & mask);
// 		c = c >> ((m - 1 - j) * bitParPixel);
// 		pixdata[*p_pos] = pixdata[*p_pos] >> bitParPixel;
// 		pixdata[*p_pos] = pixdata[*p_pos] << bitParPixel;
// 		pixdata[*p_pos] = pixdata[*p_pos] | c;
// 		*p_pos++;
// 		mask = mask >> bitParPixel;
// 	}
// 	return 0;
// }

void brint(unsigned char a)
{
	int k;
	for (k=7; k>=0; k--) {
		printf("%d", (a>>k) & 0x1);
	}
	printf("\n");
}

int hide_byte(unsigned char pixdata[], int n, int *p_pos, unsigned char b,
		char bitParPixel)
{
	int k = *p_pos;
	int l, i;
	int j=0;

	l = atoi(&bitParPixel);

	while (k < n && j<7) {
		for (i = l-1; i>=0; i--) {
			pixdata[k] &= ~(1 << i); //clear i bit
			pixdata[k] |= ((b >> (7-j)) & 0x1) << i; //set i bit
			j++;
		}

		k++;
	}
	
	*p_pos = k;
	if (j < 6)
		return 1;

	return 0;
}

IMAGE_T *hide_file(char *fileName, IMAGE_T * p_img, char bitParPixel)
{
	int p_pos = 0;

	int n;
	n = p_img->nbl * p_img->nbc;

	unsigned char pixdata[n];
	unsigned char b;

	int i;
	for (i = 0; i < n; i++) {
		pixdata[i] = (*p_img->data)[i];
	}

	FILE *fileout;
	fileout = fopen(fileName, "r");
	if (fileout == NULL) {
		printf("Erreur: impossible de créer le fichier\n");
		return NULL;
	}


	int l = 0;
	int nw;
	while (fscanf(fileout, "%c", &b) != EOF) {
		l++;
	}
	printf("Nombre de caractères à encoder: %d\n", l);

	for (i = 0; i < 4; i++) {
		b = l >> (24 - 8 * i) ;

		nw = hide_byte(pixdata, n, &p_pos, b, bitParPixel);
		if (nw != 0)
			return NULL;
	}

	fseek(fileout, 0, 0);
	while(fscanf(fileout, "%c", &b) != EOF)
	   {
	     nw = hide_byte(pixdata, n, &p_pos, b, bitParPixel);
	     if (nw != 0)
	     	return NULL;
	}

	for (i = 0; i < n; i++) {
		(*p_img->data)[i] = pixdata[i];
	}

	fclose(fileout);

	return p_img;
}
