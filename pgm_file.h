#ifndef _PGM_FILE_H_
#define _PGM_FILE_H_

#include "image.h"

/**
 * Lit un fichier image en niveau de gris au format PGM P5.
 * et retourne l’image stockée dans le fichier. 
 * L’allocation mémoire est dynamique la zone allouée est contiguë 
 * Seul le format P5 est géré. De plus, la valeur maximale des pixels dans 
 * le fichier doit être 255 (<=> un octet) ou une erreur se produit.
 * Tout commentaire (ligne commençant par ‘#’ dans le fichier) est ignoré.
 * PARAMETRES :
 * 	fileName : nom du fichier PGM à lire
 * RETOUR : pointeur vers l’IMAGE_T lue, ou NULL en cas d’erreur
 */
IMAGE_T *read_pgm_file(char *fileName);


/* Ecrit l’image passée en paramètre dans un fichier au format PGM P5.
 * PARAMETRES :
 * 	fileName : nom du fichier PGM à créer
 * 	p_img : pointeur vers l’image à sauver dans le fichier
 * 	comment : commentaire, optionnel. Ignoré si comment == NULL.
 *		Sinon, sur la seconde ligne ‘#’ est écrit, suivi de "comment".
 * RETOUR : 0 si tout se passe bien ; autre chose en cas d’erreur.
 */
int write_pgm_file(char *fileName, IMAGE_T * p_img, char *comment);


#endif
