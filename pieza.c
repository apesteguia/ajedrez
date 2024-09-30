#include "pieza.h"

void nuevaPiezaViva(Pieza *p, const TipoPieza *tipo, const ColorPieza *color,
                    const Vector2 *pos) {
    p->pos = *pos;
    p->color = *color;
    p->tipo = *tipo;
    p->viva = true;
    p->vacia = false;
}

void nuevaPiezaVacia(Pieza *p, const Vector2 *pos) {
    p->vacia = true;
    p->pos = *pos;
}
