#include <stdio.h>

#include "decodage.h"
#include "pgm_file.h"
#include "estimation.h"

int main(int argc, char *argv[])
{
	/*3 arguments, dont 1 fac. argv[0]: nom du programme, donc on commence a 3 */
	if (argc < 2 || argc > 4) {
		printf
		    ("Usage: decode <imageIn.pgm> <fileToRecreate> [ <nbbitsparpixel> ]\n");
		return 1;
	} else {

		char bitparpixel;

		IMAGE_T *img = NULL;
		img = read_pgm_file(argv[1]);
		if (img == NULL) {
			return 1;
		};

		if (argc == 4) {
			bitparpixel = *argv[3];
		} else {
			int p_nb_used, p_size_msg;
			lsb_used(img, &p_nb_used, &p_size_msg);
			printf("p_nb_used: %d\n", p_nb_used);
			bitparpixel = (unsigned char) p_nb_used;
		}

		int n;
		n = extract_file(argv[2], img, bitparpixel);
		if (n != 0) {
			return 1;
		};

		free_image(img);
	}
	return 0;
}
