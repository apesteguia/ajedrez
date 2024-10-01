#include "tablero.h"
#include "pieza.h"
#include <raylib.h>
#include <stdio.h>
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
        for (int j = 0; j < N; j++) {
            Vector2 v;
            v.x = i;
            v.y = j;
            nuevaPiezaVacia(&t->piezas[i][j], &v);
        }
    }

    Vector2 v2;
    ColorPieza cl;
    TipoPieza ti = Peon;
    for (int i = 0; i < N; i++) {
        cl = Blanca;
        v2.y = 2;
        v2.x = i;
        nuevaPiezaViva(&t->piezas[i][1], &ti, &cl, &v2);
        cl = Negra;
        v2.y = 6;
        nuevaPiezaViva(&t->piezas[i][6], &ti, &cl, &v2);
    }
}

void iniciarTexturas(Tablero *t) {
    const char *nombresBlancas[N] = {"alfil_blanco.png", "caballo_blanco.png",
                                     "torre_blanca.png", "dama_blanca.png",
                                     "rey_blanco.png",   "peon_blanco.png"};

    const char *nombresNegras[N] = {"alfil_negro.png", "caballo_negro.png",
                                    "torre_negra.png", "dama_negra.png",
                                    "rey_negro.png",   "peon_negro.png"};

    char workingDir[512];
    strcpy(workingDir, GetWorkingDirectory());

    for (int i = 0; i < N; i++) {
        char pathBlancas[512], pathNegras[512];

        snprintf(pathBlancas, sizeof(pathBlancas), "%s/static/%s", workingDir,
                 nombresBlancas[i]);
        snprintf(pathNegras, sizeof(pathNegras), "%s/static/%s", workingDir,
                 nombresNegras[i]);

        t->texturas.blancas[i] = LoadTexture(pathBlancas);
        t->texturas.negras[i] = LoadTexture(pathNegras);

        if (t->texturas.blancas[i].id == 0 || t->texturas.negras[i].id == 0) {
            printf("Error al cargar las texturas para %s o %s\n",
                   nombresBlancas[i], nombresNegras[i]);
        } else {
            printf("Texturas cargadas con éxito para %s y %s\n",
                   nombresBlancas[i], nombresNegras[i]);
        }
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
            DrawText(TextFormat("%d %d %d", i + 1, j + 1, t->piezas[i][j].tipo),
                     x, y, 17, GREEN);
            if (t->piezas[i][j].tipo == Peon) {
                if (t->piezas[i][j].color == Blanca) {
                    DrawTexture(t->texturas.blancas[0], x, y, WHITE);
                } else {
                    DrawTexture(t->texturas.negras[0], x, y, WHITE);
                }
            }
        }
    }
}

void vaciarTexturas(Tablero *t) {
    for (int i = 0; i < N; i++) {
        UnloadTexture(t->texturas.negras[i]);
        UnloadTexture(t->texturas.blancas[i]);
    }
}
