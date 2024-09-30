#include "tablero.h"
#include "pieza.h"
#include <raylib.h>

void iniciarTablero(Tablero *t) {
    t->turnos = t->valorNegras = t->valorBlancas = 0;

    // Peones
    Vector2 v;
    ColorPieza color;
    TipoPieza tipo;
    tipo = Peon;
    for (int i = 0; i < N; i++) {
        v.y = i;
        v.x = 6;
        color = Blanca;
        nuevaPiezaViva(&t->piezas[6][i], &tipo, &color, &v);
        v.x = 1;
        color = Negra;
        nuevaPiezaViva(&t->piezas[6][i], &tipo, &color, &v);
    }
}

void dibujarTablero(Tablero *t) {
    Color color;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            const int x = i * TAMANIO_PIEZA;
            const int y = j * TAMANIO_PIEZA;
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    color = WHITE;
                } else {
                    color = GRAY;
                }
            } else {
                if (j % 2 == 0) {
                    color = GRAY;
                } else {
                    color = WHITE;
                }
            }
            DrawRectangle(x, y, TAMANIO_PIEZA, TAMANIO_PIEZA, color);
        }
    }
}
