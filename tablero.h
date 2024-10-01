#ifndef MAG_TABLERO
#define MAG_TABLERO

#include "pieza.h"
#include "raylib.h"
#include "vec.h"

#define HEIGHT 800
#define WIDTH 800
#define N 8
#define TAMANIO_PIEZA WIDTH / N

#define START_PEON_BLANCO 6
#define START_PEON_NEGRO 1

typedef struct {
    Texture2D blancas[N];
    Texture2D negras[N];
} Texturas;

typedef struct {
    Pieza piezas[N][N];
    int turnos;
    bool ganador;
    int valorBlancas, valorNegras;
    Texturas texturas;
    Vec *movimientosPosibles;
} Tablero;

void iniciarTablero(Tablero *);
void dibujarTablero(Tablero *, const char *);
void iniciarTexturas(Tablero *);
void vaciarTexturas(Tablero *);
void movimientosPosibles(Tablero *, Vector2);

#endif
