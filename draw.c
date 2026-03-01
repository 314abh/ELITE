#include "draw.h"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "arena.h"
#include "shapes.h"
#include "window.h"

SDL_FPoint ndc_to_screen(GameWindow* gw, Vec2 ndc) {
  float width = (float)gw->width;
  float height = (float)gw->height;
  float aspect_ratio = width / height;
  float x_correction = ndc.x / aspect_ratio;

  return (SDL_FPoint){
    width * (x_correction + 1.0f) / 2.0f,
    ((1.0f - ndc.y) / 2.0f) * height
  };
}

Error set_screen(GameWindow* gw, SDL_Color c) {
  bool ok;
  ok = SDL_SetRenderDrawColor(gw->renderer, c.r, c.g, c.b, c.a);
  if (!ok) return ERR_SET_SCREEN;

  SDL_RenderClear(gw->renderer);
  if (!ok) return ERR_SET_SCREEN;

  return ERR_OK;
}

Error point_draw(GameWindow* gw, Vec2 p) {
  SDL_FPoint coords = ndc_to_screen(gw, p);
  bool ok = SDL_RenderPoints(gw->renderer, &coords, 1);
  if (!ok) return ERR_DRAW_POINT;
  return ERR_OK;
}

Error points_draw(GameWindow* gw, Vec2* p_arr, size_t count) {
  Arena* ctx = arena_new(1 << 13);
  SDL_FPoint* coords_arr = arena_alloc(ctx, sizeof(*coords_arr) * count);

  for (size_t i = 0; i < count; ++i) {
    coords_arr[i] = ndc_to_screen(gw, p_arr[i]);
  }

  bool ok = SDL_RenderPoints(gw->renderer, coords_arr, count);
  if (!ok) return ERR_DRAW_POINTS;

  arena_del(ctx);
  return ERR_OK;
}

Error line_draw(GameWindow* gw, Line l) {
  SDL_FPoint a = ndc_to_screen(gw, l.a);
  SDL_FPoint b = ndc_to_screen(gw, l.b);
  SDL_FPoint line[] = {a, b};

  bool ok = SDL_RenderLines(gw->renderer, line, 2);
  if (!ok) return ERR_DRAW_LINE;
  return ERR_OK;
}

Error triangle_draw(GameWindow* gw, Triangle t, SDL_FColor fill) {
  bool ok =
      SDL_SetRenderDrawColor(gw->renderer, fill.r, fill.g, fill.b, fill.a);
  if (!ok) return ERR_DRAW_TRIANGLE;

  SDL_Vertex vertices[3] = {0};
  for (size_t i = 0; i < 3; ++i) {
    vertices[i] = (SDL_Vertex){
        .position = ndc_to_screen(gw, t.vertices[i]),
        .color = fill,
    };
  }
  ok = SDL_RenderGeometry(gw->renderer, NULL, vertices, 3, NULL, 0);
  if (!ok) return ERR_DRAW_TRIANGLE;
  return ERR_OK;
}
// TODO
Error ring_draw(GameWindow* gw, Circle c) { return ERR_OK; }

Error circle_draw(GameWindow* gw, Circle c, SDL_FColor fill) {
  size_t SIDES_COUNT = 32;
  Vec2 center = c.center;
  Vec2 radius = point_add(center, point_new(0, c.radius));
  ;

  bool ok =
      SDL_SetRenderDrawColor(gw->renderer, fill.r, fill.g, fill.b, fill.a);
  if (!ok) return ERR_DRAW_CIRCLE;

  Arena* ctx = arena_new(1 << 12);
  Vec2* vertices = arena_alloc(ctx, sizeof(*vertices) * SIDES_COUNT);
  SDL_Vertex* sdl_vertices =
      arena_alloc(ctx, sizeof(*sdl_vertices) * (SIDES_COUNT + 1));
  float angle_per_vertex = 2 * SDL_PI_F / SIDES_COUNT;

  vertices[0] = radius;

  sdl_vertices[0] =
      (SDL_Vertex){.position = ndc_to_screen(gw, center), .color = fill};
  sdl_vertices[1] =
      (SDL_Vertex){.position = ndc_to_screen(gw, radius), .color = fill};

  for (size_t i = 1; i < SIDES_COUNT; ++i) {
    vertices[i] = rotate_point(vertices[i - 1], center, angle_per_vertex);
    sdl_vertices[i + 1] = (SDL_Vertex){
        .position = ndc_to_screen(gw, vertices[i]),
        .color = fill,
    };
  }

  int sdl_indices[] = {
      0,  1,  2,  0,  2,  3,  0,  3,  4,  0,  4,  5,  0,  5,  6,  0,
      6,  7,  0,  7,  8,  0,  8,  9,  0,  9,  10, 0,  10, 11, 0,  11,
      12, 0,  12, 13, 0,  13, 14, 0,  14, 15, 0,  15, 16, 0,  16, 17,
      0,  17, 18, 0,  18, 19, 0,  19, 20, 0,  20, 21, 0,  21, 22, 0,
      22, 23, 0,  23, 24, 0,  24, 25, 0,  25, 26, 0,  26, 27, 0,  27,
      28, 0,  28, 29, 0,  29, 30, 0,  30, 31, 0,  31, 32, 0,  32, 1,
  };

  ok = SDL_RenderGeometry(gw->renderer, NULL, sdl_vertices, SIDES_COUNT + 1,
                          sdl_indices, sizeof(sdl_indices) / sizeof(*sdl_indices));
  if (!ok) return ERR_DRAW_CIRCLE;

  arena_del(ctx);
  return ERR_OK;
}

Error draw(GameWindow* gw) {
  bool ok = SDL_RenderPresent(gw->renderer);
  if (!ok) return ERR_DRAW_RENDER;
  return ERR_OK;
}
