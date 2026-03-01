/* -- draw.h
 *
 * Compatibility/Utility functions to translate in-game objects to
 * draw-able SDL3 objects (and execute them too).
 */

#ifndef ELITE_DRAW_H
#define ELITE_DRAW_H

#include <SDL3/SDL.h>

#include "shapes.h"
#include "window.h"

typedef struct Color {
  uint8_t r, g, b, a;
} Color;

#define color_new(r, g, b, a) ((SDL_Color){r, g, b, a})

Error set_screen(GameWindow* gw, SDL_Color c);

Error point_draw(GameWindow* gw, Point p);
Error points_draw(GameWindow* gw, Point* p_arr, size_t count);
Error line_draw(GameWindow* gw, Line a);

Error triangle_draw(GameWindow* gw, Triangle t, SDL_FColor fill);

Error ring_draw(GameWindow* gw, Circle c);
Error circle_draw(GameWindow* gw, Circle c, SDL_FColor fill);

Error draw(GameWindow* gw);

#endif /* ELITE_DRAW_H */
