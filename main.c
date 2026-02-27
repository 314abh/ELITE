/* -- main.c */
#include <stdio.h>

#define ARENA_IMPLEMENT
#include "arena.h"
#include "window.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
  Error err;
  int exit_code = 0;
  Arena* gw_arena = arena_new(1 << 12);
  arena_push(gw_arena);

  GameWindow* gw = arena_alloc(gw_arena, sizeof(*gw));
  err = window_init(gw, WIDTH, HEIGHT);
  if (err) {
    fprintf(stderr, "Couldn't create window. Exiting...\n");
    exit_code = err;
    goto cleanup;
  }

  err = window_loop(gw);

cleanup:
  window_close(gw);
  arena_pop();
  arena_del(gw_arena);
  return exit_code;
}
