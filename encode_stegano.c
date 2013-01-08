#include <stdio.h>

#include "image.h"
#include "pgm_file.h"
#include "encodage.h"

int main( int argc, char *argv[]) 
{
	if ( argc != 5 ) {

		printf("Usage: encode <imageIn.pgm> <fileToHide> <imageOut.pgm> <nbbitsparpixel>\n");
		return 1;
	}
	else {

		IMAGE_T* img = NULL;

		img = read_pgm_file(argv[1]);

		if(img==NULL) return 1;

		img = hide_file( argv[2], img, *argv[4]);

		if(img==NULL) return 1;

		write_pgm_file(argv[3], img, "Gen By Barbosa");

		free_image(img);

		return 0;
	}
}