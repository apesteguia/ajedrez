#include "tablero.h"
#include "pieza.h"
#include "vec.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void movimientosPosibles(Tablero *, Vec *, Vector2);

void iniciarTablero(Tablero *t) {
    t->turnos = t->valorNegras = t->valorBlancas = 0;

    // Inicializar el tablero con todas las piezas vacías
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Vector2 v = {i, j};
            nuevaPiezaVacia(&t->piezas[i][j],
                            &v); // Inicializa cada posición vacía
        }
    }

    Vector2 v;
    TipoPieza tipo;
    ColorPieza color;

    // Peones
    tipo = Peon;
    for (int i = 0; i < N; i++) {
        // Peones blancos
        v = (Vector2){i, 1};
        color = Blanca;
        nuevaPiezaViva(&t->piezas[i][1], &tipo, &color, &v);

        // Peones negros
        v = (Vector2){i, 6};
        color = Negra;
        nuevaPiezaViva(&t->piezas[i][6], &tipo, &color, &v);
    }

    // Alfiles
    tipo = Alfil;
    // Alfiles blancos
    v = (Vector2){2, 0};
    color = Blanca;
    nuevaPiezaViva(&t->piezas[2][0], &tipo, &color, &v);
    v = (Vector2){5, 0};
    nuevaPiezaViva(&t->piezas[5][0], &tipo, &color, &v);

    // Alfiles negros
    v = (Vector2){2, 7};
    color = Negra;
    nuevaPiezaViva(&t->piezas[2][7], &tipo, &color, &v);
    v = (Vector2){5, 7};
    nuevaPiezaViva(&t->piezas[5][7], &tipo, &color, &v);

    // Caballos
    tipo = Caballo;
    // Caballos blancos
    v = (Vector2){1, 0};
    color = Blanca;
    nuevaPiezaViva(&t->piezas[1][0], &tipo, &color, &v);
    v = (Vector2){6, 0};
    nuevaPiezaViva(&t->piezas[6][0], &tipo, &color, &v);

    // Caballos negros
    v = (Vector2){1, 7};
    color = Negra;
    nuevaPiezaViva(&t->piezas[1][7], &tipo, &color, &v);
    v = (Vector2){6, 7};
    nuevaPiezaViva(&t->piezas[6][7], &tipo, &color, &v);

    // Torres
    tipo = Torre;
    // Torres blancas
    v = (Vector2){0, 0};
    color = Blanca;
    nuevaPiezaViva(&t->piezas[0][0], &tipo, &color, &v);
    v = (Vector2){7, 0};
    nuevaPiezaViva(&t->piezas[7][0], &tipo, &color, &v);

    // Torres negras
    v = (Vector2){0, 7};
    color = Negra;
    nuevaPiezaViva(&t->piezas[0][7], &tipo, &color, &v);
    v = (Vector2){7, 7};
    nuevaPiezaViva(&t->piezas[7][7], &tipo, &color, &v);

    // Damas
    tipo = Reina;
    // Dama blanca
    v = (Vector2){3, 0};
    color = Blanca;
    nuevaPiezaViva(&t->piezas[3][0], &tipo, &color, &v);

    // Dama negra
    v = (Vector2){3, 7};
    color = Negra;
    nuevaPiezaViva(&t->piezas[3][7], &tipo, &color, &v);

    // Reyes
    tipo = Rey;
    // Rey blanco
    v = (Vector2){4, 0};
    color = Blanca;
    nuevaPiezaViva(&t->piezas[4][0], &tipo, &color, &v);

    // Rey negro
    v = (Vector2){4, 7};
    color = Negra;
    nuevaPiezaViva(&t->piezas[4][7], &tipo, &color, &v);
}

void iniciarTexturas(Tablero *t) {
    const char *nombresBlancas[N] = {"peon_blanco.png",    "alfil_blanco.png",
                                     "caballo_blanco.png", "torre_blanco.png",
                                     "reina_blanco.png",   "rey_blanco.png"};

    const char *nombresNegras[N] = {"peon_negro.png",    "alfil_negro.png",
                                    "caballo_negro.png", "torre_negro.png",
                                    "reina_negro.png",   "rey_negro.png"};

    char workingDir[512];
    strcpy(workingDir, GetWorkingDirectory());

    for (int i = 0; i < 6; i++) {
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

void dibujarTablero(Tablero *t, const char *posiciones) {
    Color color;
    Vec v;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            const int x = i * TAMANIO_PIEZA;
            const int y = j * TAMANIO_PIEZA;

            if ((i + j) % 2 == 0) {
                color = WHITE;
            } else {
                color = GRAY;
            }
            DrawRectangle(x, y, TAMANIO_PIEZA, TAMANIO_PIEZA, color);
            DrawText(TextFormat("%c%d", posiciones[i], N - j), x + 5, y + 5, 15,
                     BLACK);

            Pieza pieza = t->piezas[i][j];
            if (pieza.tipo != Vacio) {
                int indiceTextura = -1;
                switch (pieza.tipo) {
                case Peon:
                    indiceTextura = 0;
                    break;
                case Alfil:
                    indiceTextura = 1;
                    break;
                case Caballo:
                    indiceTextura = 2;
                    break;
                case Torre:
                    indiceTextura = 3;
                    break;
                case Reina:
                    indiceTextura = 4;
                    break;
                case Rey:
                    indiceTextura = 5;
                    break;
                default:
                    break;
                }

                if (indiceTextura >= 0) {
                    if (pieza.color == Blanca) {
                        DrawTexture(t->texturas.blancas[indiceTextura],
                                    x + TAMANIO_PIEZA / 4,
                                    y + TAMANIO_PIEZA / 4, WHITE);
                    } else if (pieza.color == Negra) {
                        DrawTexture(t->texturas.negras[indiceTextura],
                                    x + TAMANIO_PIEZA / 4,
                                    y + TAMANIO_PIEZA / 4, WHITE);
                    }
                }
            }
        }
    }
    Vector2 adf;
    adf.x = 1;
    adf.y = 1;
    printf("Hsdfafasdfsadfas\n");
    movimientosPosibles(t, &v, adf);
    printf("HOLA\n");
    Vector2 *ai = (Vector2 *)&v.array[0];
    adf.x = ai->x;
    // printf("\n%f %f\n\n", ai->x, ai->y);
}

void vaciarTexturas(Tablero *t) {
    for (int i = 0; i < N; i++) {
        UnloadTexture(t->texturas.negras[i]);
        UnloadTexture(t->texturas.blancas[i]);
    }
}

bool esPosible(Tablero *t, Vector2 *current, Vector2 *dest) {
    Pieza *cur = &t->piezas[(int)current->x][(int)current->y];
    Pieza *des = &t->piezas[(int)dest->x][(int)dest->y];

    if (cur->color == des->color)
        return false;

    return true;
}

void movimientosPosibles(Tablero *t, Vec *v, Vector2 pos) {
    // Asegúrate de inicializar el vector
    vec_init(v, sizeof(Vector2));

    // Comprobar que pos.x y pos.y están dentro de los límites
    if (pos.x < 0 || pos.x >= N || pos.y < 0 || pos.y >= N) {
        printf("Posición fuera de límites\n");
        return; // Salir si la posición no es válida
    }

    Pieza *p = &t->piezas[(int)pos.x][(int)pos.y];

    if (p->tipo == Peon) {
        Vector2 pasar;
        if (p->color == Blanca) {
            pasar = p->pos;
            pasar.y++; // Mueve el peón hacia arriba
            vec_push(v, &pasar);
            if (esPosible(t, &p->pos, &pasar)) {
                printf("DSFASFASDF\n");
                vec_push(v, &pasar);
            }
        } else if (p->color == Negra) {
            pasar = p->pos;
            pasar.y--; // Mueve el peón hacia abajo
            if (esPosible(t, &p->pos, &pasar)) {
                vec_push(v, &pasar);
            }
        }
    }
    printf("DS1!!!!!!!!!F\n");
    // Manejo para otras piezas puede ir aquí...

    // No olvides hacer un break en los casos si se añade más lógica
}
