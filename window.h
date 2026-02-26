/* -- window.h
 *
 * GameWindow.
 */

#ifndef ELITE_GAME_WINDOW_H
#define ELITE_GAME_WINDOW_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>

#include "errors.h"

typedef struct {
  size_t width, height;
  SDL_Window* window;
  SDL_Renderer* renderer;
} GameWindow;

// Creates a new game window with the default settings.
Error window_init(GameWindow* gw, size_t width, size_t height);
void window_loop(GameWindow* gw);
void window_close(GameWindow* gw);

#endif /* ELITE_GAME_WINDOW_H */
