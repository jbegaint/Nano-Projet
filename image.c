#include <stdlib.h>
#include <assert.h>

#include "image.h"

IMAGE_T *alloc_image(int nbl, int nbc)
{
	int i, j;

	IMAGE_T *img = NULL;

	img = calloc(1, sizeof(*img));

	img->nbl = nbl;		/* (*img).nbl ; */
	img->nbc = nbc;

	unsigned char **data = NULL;

	data = (unsigned char **) calloc(nbl, sizeof(*data));
	if (data != NULL) {
		*data =
		    (unsigned char *) calloc(nbc * nbl, sizeof(**data));
		if (*data == NULL) {
			free(data);
			return NULL;
		} else {
			for (i = 1; i < nbl; i++)
				data[i] = data[i - 1] + nbc;
		}

		for (i = 0; i < nbl; i++) {
			for (j = 0; j < nbc; j++) {
				data[i][j] = 0;	/*on met tout a zero */
			}
		}

	} else {
		return NULL;
	}

	img->data = data;

	return img;
}

void free_image(IMAGE_T * p_img)
{
	free(*(p_img->data));
	free(p_img->data);
	free(p_img);
}
