#ifndef MAG_PIEZA
#define MAG_PIEZA

#include "raylib.h"
#include "vec.h"
#include <stdbool.h>

typedef enum {
    Vacio = 0,
    Peon,
    Alfil,
    Caballo,
    Torre,
    Rey,
    Reina,
} TipoPieza;

typedef enum {
    Blanca,
    Negra,
} ColorPieza;

typedef struct {
    TipoPieza tipo;
    ColorPieza color;
    Vector2 pos;
    bool viva, vacia;
} Pieza;

void nuevaPiezaViva(Pieza *, const TipoPieza *, const ColorPieza *,
                    const Vector2 *);
void nuevaPiezaVacia(Pieza *, const Vector2 *);

#endif
