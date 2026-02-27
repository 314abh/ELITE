#include "draw.h"

#include <SDL3/SDL_render.h>

#include "window.h"

SDL_FPoint ndc_to_screen(GameWindow* window, Point p) {
  return (SDL_FPoint){
      (float)window->width / 2 * (p.x + 1),
      (float)window->height / 2 * (1 - p.y),
  };
}

Error set_screen(GameWindow* gw, Color c) {
  bool ok;
  ok = SDL_SetRenderDrawColor(gw->renderer, c.r, c.g, c.b, c.a);
  if (!ok) return ERR_SET_SCREEN;

  SDL_RenderClear(gw->renderer);
  if (!ok) return ERR_SET_SCREEN;

  return ERR_OK;
}

Error Point_draw(GameWindow* gw, Point p) {
  SDL_FPoint coords = ndc_to_screen(gw, p);
  bool ok = SDL_RenderPoints(gw->renderer, &coords, 1);
  if (!ok) return ERR_DRAW_POINT;
  return ERR_OK;
}

Error Line_draw(GameWindow* gw, Line l) {
  SDL_FPoint a = ndc_to_screen(gw, l.a);
  SDL_FPoint b = ndc_to_screen(gw, l.b);
  SDL_FPoint line[] = {a, b};

  bool ok = SDL_RenderLines(gw->renderer, line, 2);
  if (!ok) return ERR_DRAW_LINE;
  return ERR_OK;
}

Error draw(GameWindow* gw) {
  bool ok = SDL_RenderPresent(gw->renderer);
  if (!ok) return ERR_DRAW_RENDER;
  return ERR_OK;
}
