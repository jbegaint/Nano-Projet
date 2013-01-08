#ifndef _IMAGE_H_
#define _IMAGE_H_


typedef struct {
	int nbl;		/* nombre de ligne de l'image */
	int nbc;		/* nombre de colonnes de l’image */
	unsigned char **data;	/* tableau bidim des pixels de l’image */
} IMAGE_T;


/**
 * Alloue une structure IMAGE_T pour une image de nbl*nbc pixels.
 * La zone de donnée de l’image, dans le champ img, est contiguë en mémoire. 
 * La zone de donnée est initialisée à 0.
 * PARAMETRES :
 * 	nbl : nombre de lignes de l’image à allouer
 * 	nbc : nombre de colonnes de l’image à allouer
 * RETOUR : pointeur vers l’IMAGE_T allouée, ou NULL en cas d’erreur
 */
IMAGE_T *alloc_image(int nbl, int nbc);
	

/**
 * Libère la mémoire préalablement allouée pour une image de nbl*nbc pixels.
 * PARAMETRES : p_img : l’image à libérer
 */
void free_image(IMAGE_T * p_img);

#endif
