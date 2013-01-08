#include <stdio.h>
#include <stdlib.h>

#include "decodage.h"

int extract_byte(unsigned char pixdata[], int n, int *p_pos,
		 unsigned char *p_b, char bitParPixel)
{

	int k = *p_pos;
	int i, l, j = 0;

	l = atoi(&bitParPixel);

	unsigned char p = 0;

	while (k < n && j < 7) {
		for (i = l - 1; i >= 0; i--) {
			//      p |= mask; // on modifie le bit en "l'allumant"
			p |= (((pixdata[k] >> i) & 0x1) << (7 - j));
			// on décale les bits du  pixel de i pour prendre le bit qui nous intéresse, 
			// puis on allume le bit de p à la position voulue.
			j++;
		}
		k++;
	}

	*p_pos = k;
	*p_b = p;

	if (j < 6) {
		return 1;
	};

	return 0;
}

int extract_file(char *fileName, IMAGE_T * p_img, char bitParPixel)
{
	int i;

	FILE *fileout;
	fileout = fopen(fileName, "w");
	if (fileout == NULL) {
		fprintf(stderr,
			"Erreur: impossible de creer le fichier\n");
		return 1;
	}

	int n;
	n = p_img->nbl * p_img->nbc;

	int p_pos = 0;

	unsigned char p_b = 0;

	int nb_octet = 0;
	for (i = 0; i < 4; i++) {
		extract_byte(*(p_img->data), n, &p_pos, &p_b, bitParPixel);
		nb_octet |= (p_b << (24 - i * 8));
	}
	//un int codé sur 4 octets, représentant le nb d'octets du fichier à cacher  
	printf("Nb d'octets a extraire: %d \n", nb_octet);

	int nw;

	for (i = 0; i < nb_octet; i++) {
		nw = extract_byte(*(p_img->data), n, &p_pos, &p_b,
				  bitParPixel);
		if (nw < 0) {
			return 1;
		};
		nw = fwrite(&p_b, sizeof(unsigned char), 1, fileout);
		//on ecrit octet par octet le nouveau fichier
		if (nw < 0) {
			return 1;
		};
	}

	fclose(fileout);
	return 0;
}
