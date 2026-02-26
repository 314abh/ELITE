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
  Arena* gw_arena = Arena_new(1 << 12);
  Arena_push(gw_arena);

  GameWindow* gw = Arena_alloc(gw_arena, sizeof(*gw));
  err = window_init(gw, WIDTH, HEIGHT);

  if (err) {
    fprintf(stderr, "Couldn't create window. Exiting...\n");
    exit_code = err;
    goto cleanup;
  }

  window_loop(gw);

cleanup:
  window_close(gw);
  Arena_pop();
  Arena_del(gw_arena);
  return exit_code;
}
