/* -- errors.h
 *
 * Error handling and reporting.
 */

typedef enum {
  // default OK
  ERR_OK,

  // initialization errors
  ERR_INIT_SDL,
  ERR_INIT_WINDOW,

  // drawing errors
  ERR_SET_SCREEN,
  ERR_DRAW_POINT,
  ERR_DRAW_POINTS,
  ERR_DRAW_LINE,
  ERR_DRAW_TRIANGLE,
  ERR_DRAW_RENDER,
} Error;
