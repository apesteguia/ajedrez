#ifndef MAG_TABLERO
#define MAG_TABLERO

#include "pieza.h"
#include "raylib.h"
#include "vec.h"

#define HEIGHT 800
#define WIDTH 800
#define N 8
#define TAMANIO_PIEZA WIDTH / N

typedef struct {
    Pieza piezas[N][N];
    int turnos;
    bool ganador;
    int valorBlancas, valorNegras;
} Tablero;

void iniciarTablero(Tablero *);
void dibujarTablero(Tablero *);;

#endif
