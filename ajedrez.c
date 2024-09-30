#include "raylib.h"
#include "tablero.h"

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Ajedrez - Mikel Apesteguia");

    SetTargetFPS(10);

    Tablero t;
    iniciarTexturas(&t);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        dibujarTablero(&t);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
