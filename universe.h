#ifndef ELITE_DRAW_UNIVERSE_H
#define ELITE_DRAW_UNIVERSE_H

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "arena.h"
#include "shapes.h"

Point* plot_stars(size_t stars_count) {
    Arena* ctx = arena_local();
    printf("LOOP_ARENA: %p", ctx);
    Point* stars_arr = arena_alloc(ctx, sizeof(*stars_arr) * stars_count);
    static thread_local bool initialized = false;
    if (!initialized) {
        srand(time(NULL));
        initialized = true;
    }

    float x, y;
    for (size_t i = 0; i < stars_count; ++i) {
        x = ((float)rand() / RAND_MAX) * 2 - 1;
        y = ((float)rand() / RAND_MAX) * 2 - 1;
        printf("STAR %zu => (%f, %f)\n", i, x, y);
        stars_arr[i] = point_new(x, y);
    }

    return stars_arr;
}

#endif /* ELITE_DRAW_UNIVERSE_H */
