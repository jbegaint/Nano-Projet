#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "estimation.h"

int lsb_used(IMAGE_T * img, int *p_nb_used, int *p_size_msg)
{
	// p_nb_used pointeur vers le nb de bit utilisés estimé
	// p_size_msg pointeur vers la taille estimé du message

	int i, j;

	unsigned char u, v;

	double b, d;
	double r1, r2;
	double r_estime[8];

	printf("(Nombre de pixels: %d)\n", img->nbc * img->nbl);

	double W, X, Y, Z;

	for (i = 0; i < 8; i++) {
		//les 8 décalages de bit possibles
		W = X = Y = Z = 0;
		for (j = 0; j < img->nbl * img->nbc - 1; j++) {

			u = (*img->data)[j] >> i;
			v = (*img->data)[j + 1] >> i;

			if (u == v) {
				Z++;
			}
			if ((v % 2 == 0 && u < v) || (v % 2 == 1 && u > v)) {
				X++;
			}
			if ((v % 2 == 0 && u > v) || (v % 2 == 1 && u < v)) {
				Y++;
			}
			if (abs(u - v) == 1) {
				W++;
			}
		}

		b = X - Y - Z;
		d = b * b + 2 * (W + Z) * X;
		if (d > 0) {
			r1 = (-b - sqrt(d)) / (W + Z);
			r2 = (-b + sqrt(d)) / (W + Z);

			r_estime[i] = ((r1 < r2) ? r1 : r2);
			//min de r1, r2
		} else {
			r_estime[i] = 0;
		}
	}
	printf("Racines:\n");
	for (i = 0; i < 8; i++) {
		printf("%d %lf\n", i, r_estime[i]);
	}

	double pp = 0;
	// double tmp;
	// int l;
	// for (i=1; i<8; i++) {
	//      tmp=0;
	//      for (l=0; l<i; l++) {
	//              tmp += r_estime[l];
	//      }
	//      tmp = r_estime[i] - tmp/i; //division par zéro??

	//      if (tmp > pp) {pp=tmp;}
	//      printf("%d %lf\n", i, tmp);
	// }


	*p_nb_used = pp;
	*p_size_msg = *p_nb_used * (img->nbc) * (img->nbl) / 8;

	return 0;
}
