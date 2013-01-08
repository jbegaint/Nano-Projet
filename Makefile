CFLAGS= -g -Wall 
LDFLAGS=

all: decode

encode:encodage.o pgm_file.o encode_stegano.o image.o
	gcc -o $@ $^ $(LDFLAGS)	

decode:decodage.o pgm_file.o decode_stegano.o estimation.o image.o
	gcc -o $@ $^ $(LDFLAGS) -lm

test_write:image.o test_write.o pgm_file.o
	gcc -o $@ $^ $(LDFLAGS)

%.o:%.c
	gcc -c $(CFLAGS) $<

clean:
	rm *.o
