/* -- window.c */

#include "window.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include "arena.h"
#include "draw.h"

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

  gw->window = window;
  gw->renderer = renderer;
  return ERR_OK;
}

void window_loop(GameWindow* gw) {
  SDL_Event event;
  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) break;

    set_screen(gw, color_new(0x00, 0xFF, 0x00, 0x00));
    draw(gw);
  }
}

void window_close(GameWindow* gw) {
  SDL_DestroyRenderer(gw->renderer);
  SDL_DestroyWindow(gw->window);
  SDL_Quit();
}
