/* -- window.c */

#include "window.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
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
  size_t width = gw->width;
  size_t height = gw->height;

  Arena* loop_arena = arena_new(1 << 12);
  arena_push(loop_arena);
  printf("LOOP_ARENA: %p", loop_arena);

  size_t stars_count = width * height * (5.0f * 1e-4);
  Point* stars = plot_stars(stars_count);

  Triangle tri = {0};
  SDL_FColor fill = {0xff, 0xff, 0x00, 0xff};
  tri.vertices[0] = (Point){0.0f, 0.0f};
  tri.vertices[1] = (Point){0.3f, 0.0f};
  tri.vertices[2] = (Point){0.3f, -0.3f};

  // handle timings.
  float speed = 3.0f / width;
  Uint64 current_time, last_time = SDL_GetTicks();

  // TODO: implement error logging.
  bool running = true;
  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_EVENT_QUIT) break;

    // handle timings.
    current_time = SDL_GetTicks();
    float dt = (current_time - last_time) / (float)1e3;
    last_time = current_time;

    // clear screen
    err = set_screen(gw, color_new(0x16, 0x16, 0x16, 0xFF));
    if (err) goto cleanup;

    // draw stars
    bool success = SDL_SetRenderDrawColor(gw->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    if (!success) goto cleanup;

    err = points_draw(gw, stars, stars_count);
    if (err) goto cleanup;

    err = triangle_draw(gw, tri, fill);
    tri.vertices[0].y += speed * dt;
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
