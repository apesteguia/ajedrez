#include "tablero.h"
#include "pieza.h"
#include <raylib.h>
#include <string.h>
#include <unistd.h>

void iniciarTablero(Tablero *t) {
    t->turnos = t->valorNegras = t->valorBlancas = 0;

    iniciarTexturas(t);
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

void iniciarTexturas(Tablero *t) {
    char workingDir[512];
    strcpy(workingDir, GetWorkingDirectory());

    char pathBlancas[512];
    snprintf(pathBlancas, sizeof(pathBlancas), "%s/static/alfil_blanco.png",
             workingDir);

    char pathNegras[512];
    snprintf(pathNegras, sizeof(pathNegras), "%s/static/alfil_negro.png",
             workingDir);

    t->texturas.blancas[0] = LoadTexture(pathBlancas);
    t->texturas.negras[0] = LoadTexture(pathNegras);
    if (t->texturas.blancas[0].id == 0 || t->texturas.negras[0].id == 0) {
        printf("Error al cargar las texturas\n");
    } else {
        printf("Texturas cargadas con éxito\n");
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
            if (t->piezas[i][j].tipo == Peon) {
                if (t->piezas[i][j].color == Blanca) {
                    DrawTexture(t->texturas.blancas[0], x, y, MAROON);
                } else {
                    DrawTexture(t->texturas.negras[0], x, y, MAROON);
                }
            }
        }
    }
}
