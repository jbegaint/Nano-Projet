#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "pgm_file.h"

/**
 * cree une image 10x10,
 * La remplit en gris
 * Ecrit un fichier PGM pour cet image

 * ATTENTION : pour compiler, ce programme necessite
 *			les fonctions d'allocation d'IMAGE_T,
 *			alloc_image() et free_image(), dans image.c
 *			Vous devez donc écrire ces fonction dans le fichier image.c
 *			avant de pouvoir compiler ce programme.
 * ! */
int main(int argc, char *argv[])
{
	int errCode;
	int i;
	if (argc != 2) {
		printf("%s usage :\n", argv[0]);
		printf("%s <fileout.pgm> :\n", argv[0]);
		return 1;
	}
	IMAGE_T *im = alloc_image(11, 100);

	/* remplit en gris */
	for (i = 0; i < im->nbl * im->nbc; i++) {
		(*im->data)[i] = 180;	/* 180 => gris */
	}

	/*
	 * on met un commentaire dans le fichier Pour ne pas mettre de
	 * commentaire, passer NULL en troisième argument
	 */
	errCode =
	    write_pgm_file(argv[1], im,
			   "created by Phelma prg testwrite.");
	if (errCode) {
		printf("error 2\n");
		return 1;
	}
	free_image(im);
	return 0;
}
