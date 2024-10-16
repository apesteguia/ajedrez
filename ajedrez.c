#include "raylib.h"
#include "tablero.h"

int main(int argc, char **argv) {
    InitWindow(WIDTH, HEIGHT, "Ajedrez - Mikel Apesteguia");

    SetTargetFPS(10);
    const char POSICIONES[N] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    Vector2 posicionCursor;
    Tablero t;
    iniciarTexturas(&t);
    iniciarTablero(&t);

    while (!WindowShouldClose()) {
        posicionCursor = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            movimientosPosibles(&t, posicionCursor);
        }

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
