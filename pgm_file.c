#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "image.h"
#include "pgm_file.h"

#include "string.h"


/* ICI : ecrire votre fonction read_pgm_file() */

/**
 * Lit un fichier image en niveau de gris au format PGM P5.
 * et retourne l’image stockée dans le fichier.
 * L’allocation mémoire est dynamique la zone allouée est contiguë
 * Seul le format P5 est géré. De plus, la valeur maximale des pixels dans
 * le fichier doit être 255 (<=> un octet) ou une erreur se produit.
 * Le commentaire (ligne commençant par ‘#’ dans le fichier) est ignoré.
 * PARAMETRES :
 * 	fileName : nom du fichier PGM à lire
 * RETOUR : pointeur vers l’IMAGE_T lue, ou NULL en cas d’erreur
 */
IMAGE_T *read_pgm_file(char *fileName)
{
	FILE *filein;
	filein = fopen(fileName, "rb");

	int nbc, nbl;

	if (filein == NULL) {
		fprintf(stderr,
			"Erreur: impossible d'ouvrir le fichier '%s'\n",
			fileName);
	}

	char line[256];

	/*lecture de la première ligne */
	if (fgets(line, sizeof(line), filein) != NULL) {
		if (strcmp(line, "P5\n") != 0) {
			fprintf(stderr, "Erreur pas un fichier P5");
			return NULL;
		}
	}

	/*affichage du commentaire */
	if (fgets(line, sizeof(line), filein) != NULL) {
		printf("Commmentaire: %s", line);
	}

	/*Pour récupérer nbc et nbl */
	if (fgets(line, sizeof(line), filein) != NULL) {

 		/*calcul du nombre de chiffre de nbc */
		int nbc_len = 0;
		do {
			nbc_len++;
		} while (line[nbc_len] != ' ');

		nbc = atoi(line);
		nbl = atoi(line + nbc_len);

	} else {
		return NULL;
	}

	/*on vérifie si la valeur max dépasse pas 255 */
	if (fgets(line, sizeof(line), filein) != NULL) {
		int len = atoi(line);
		if (len > 255) {
			fprintf(stderr,
				"Erreur: sur la valeur max d'un pixel\n");
		}
	} else {
		return NULL;
	}

	IMAGE_T *img;
	img = alloc_image(nbl, nbc);


	int nr;
	nr = fread(*(img->data), sizeof(unsigned char),
		   img->nbc * img->nbl, filein);
	if (nr != img->nbc * img->nbl) {
		fprintf(stderr, "Erreur : erreur de lecture du fichier\n");
		return NULL;
	}

	fclose(filein);
	return img;
}



/* Ecrit l’image passée en paramètre dans un fichier au format PGM P5.
 * PARAMETRES :
 * 	fileName : nom du fichier PGM à créer
 * 	p_img : pointeur vers l’image à sauver dans le fichier
 * 	comment : commentaire, optionnel. Ignoré si comment == NULL.
 *		Sinon, sur la seconde ligne ‘#’ est écrit, suivi de "comment".
 * RETOUR : 0 si tout se passe bien ; autre chose en cas d’erreur.
 */
int write_pgm_file(char *fileName, IMAGE_T * p_img, char *comment)
{
	assert(p_img && p_img->data && *(p_img->data));
	FILE *fileout;
	int nb;

	fileout = fopen(fileName, "wb");
	if (fileout == NULL) {
		/* echec : gestion d'erreur */
		fprintf(stderr,
			"ERREUR : Impossible d'ouvrir le fichier '%s' !\n",
			fileName);
		return 1;
	}
	/* ecriture de la cle identifiant les fichier PPM P5 */
	nb = fprintf(fileout, "P5\n");
	if (nb <= 0) {
		fprintf(stderr,
			"ERREUR : erreur d'ecriture fichier (cas 1)\n");
		return 1;
	}
	/* ecriture du commentaire optionnel */
	if (comment) {
		nb = fprintf(fileout, "# %s\n", comment);
		if (nb <= 0) {
			fprintf(stderr,
				"ERREUR : erreur d'ecriture fichier (cas 2)\n");
			return 1;
		}
	}
	/* nbm, nbc et max value des pixels */
	nb = fprintf(fileout, "%d %d\n", p_img->nbc, p_img->nbl);
	if (nb <= 0) {
		fprintf(stderr,
			"ERREUR : erreur d'ecriture fichier (cas 3)\n");
		return 1;
	}
	nb = fprintf(fileout, "255\n");
	if (nb <= 0) {
		fprintf(stderr,
			"ERREUR : erreur d'ecriture fichier (cas 4)\n");
		return 1;
	}
	/* data : les pixels, en binaire */
	nb = fwrite(*(p_img->data), sizeof(unsigned char),
		    p_img->nbc * p_img->nbl, fileout);
	if (nb != p_img->nbc * p_img->nbl) {
		fprintf(stderr,
			"ERREUR : erreur d'ecriture fichier (cas 5)\n");
		return 1;
	}
	fclose(fileout);
	return 0;
}
