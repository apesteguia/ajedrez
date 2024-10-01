#include "raylib.h"
#include "tablero.h"

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Ajedrez - Mikel Apesteguia");

    SetTargetFPS(10);
    const char POSICIONES[N] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    Tablero t;
    iniciarTexturas(&t);
    iniciarTablero(&t);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        dibujarTablero(&t, POSICIONES);

        EndDrawing();
    }

    for (int i = 0; i < N; i++) {
        UnloadTexture(t.texturas.blancas[i]);
        UnloadTexture(t.texturas.negras[i]);
    }

    CloseWindow();

    return 0;
}
