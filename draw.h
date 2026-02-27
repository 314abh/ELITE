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

#define color_new(r, g, b, a) ((Color){r, g, b, a})

Error set_screen(GameWindow* gw, Color c);

Error Point_draw(GameWindow* gw, Point p);
Error Points_draw(GameWindow* gw, Point* p_arr, size_t count);
Error Line_draw(GameWindow* gw, Line a);

Error draw(GameWindow* gw);

#endif /* ELITE_DRAW_H */
