all: rm vec pieza tablero ajedrez clean

rm:
	rm -f ajedrez
clean:
	rm -f *.o

ajedrez:
	gcc ajedrez.c -o ajedrez tablero.o pieza.o vec.o -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
tablero:
	gcc -c tablero.c pieza.o vec.o -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
pieza:
	gcc -c pieza.c -Wall vec.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
vec:
	gcc -c vec.c -Wall

