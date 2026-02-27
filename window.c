/* -- window.c */

#include "window.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>

#include "arena.h"
#include "draw.h"
#include "shapes.h"
#include "universe.h"

Error window_init(GameWindow* gw, size_t width, size_t height) {
  bool sdl_err;

  // initialize SDL3
  sdl_err = SDL_Init(SDL_INIT_VIDEO);
  if (!sdl_err) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL3: %s",
                 SDL_GetError());
    return ERR_INIT_SDL;
  }

  // initialize window and renderer
  SDL_Window* window;
  SDL_Renderer* renderer;
  sdl_err = SDL_CreateWindowAndRenderer("ELITE", width, height, 0, &window,
                                        &renderer);
  if (!sdl_err) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create window and renderer: %s", SDL_GetError());
    return ERR_INIT_WINDOW;
  }

  // enable adaptive VSync
  SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

  gw->width = width;
  gw->height = height;
  gw->window = window;
  gw->renderer = renderer;
  return ERR_OK;
}

Error window_loop(GameWindow* gw) {
  Error err;
  SDL_Event event;

  Arena* loop_arena = arena_new(1 << 12);
  arena_push(loop_arena);
  printf("LOOP_ARENA: %p", loop_arena);

  size_t stars_count = gw->width * gw->height * (5.0f * 1e-4);
  Point* stars = plot_stars(stars_count);
  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) break;

    // clear screen
    err = set_screen(gw, color_new(0x16, 0x16, 0x16, 0xFF));
    if (err) goto cleanup;

    // draw stars
    bool success = SDL_SetRenderDrawColor(gw->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    if (!success) goto cleanup;

    err = Points_draw(gw, stars, stars_count);
    if (err) goto cleanup;

    draw(gw);
  }

cleanup:
  arena_pop();
  arena_del(loop_arena);
  return err;
}

void window_close(GameWindow* gw) {
  SDL_DestroyRenderer(gw->renderer);
  SDL_DestroyWindow(gw->window);
  SDL_Quit();
}
