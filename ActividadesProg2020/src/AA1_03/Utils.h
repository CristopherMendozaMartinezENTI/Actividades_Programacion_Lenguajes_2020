#include "Types.h"

static SDL_Rect MyRect2SDL(const Rect* r) { return { r->x, r->y, r->w, r->h }; }