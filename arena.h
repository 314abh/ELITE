/* -- arena.h
 * Single header-file implementation of `arenas' or
 * region-based memory allocaters.
 *
 * Copyright 2025-26 Abhigyan Kumar <314abh+source@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Arenas are stacks under the hood. They are large chunks of memory in
 * heap in the form of a stack. You keep allocating memory within an
 * arena until it is full, and then release the arena altogether. This
 * destroys all the allocated structures within the arena at once,
 * preventing memory leaks.
 */

#ifndef ARENA_H_
#define ARENA_H_

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <threads.h>

#if !defined(ASL_REALLOC) && !defined(ASL_FREE)
#include <stdlib.h>
#define ARENA_REALLOC(p, s) realloc(p, s)
#define ARENA_MALLOC(s) ARENA_REALLOC(NULL, s)
#define ARENA_FREE(s) free(s)
#endif 
#if defined(ASL_REALLOC) && !defined(ASL_FREE) || \
    !defined(ASL_REALLOC) && defined(ASL_FREE)
#error "You must defined both, ASL_REALLOC and ASL_FREE."
#endif /* ASL_REALLOC && ASL_FREE */

#ifndef ARENA_ASSERT
#include <assert.h>
#define ARENA_ASSERT(x) assert(x)
#endif /* ARENA_ASSERT */

#ifndef ARENA_DEF_SIZE
#define ARENA_DEF_SIZE 2048
#endif

#ifndef MAX_ARENA_STACK
#define MAX_ARENA_STACK 16
#endif

typedef struct Arena {
  void* _pos;
  size_t _size;
  char _data[];
} Arena;

Arena* arena_new(size_t size);
void* arena_alloc_aligned(Arena* ar, size_t size, size_t align);
void arena_del(Arena* ar);
size_t arena_used(Arena* ar);
size_t arena_available(Arena* ar);

int arena_push(Arena* ar);  // returns negative number if it's a stack overflow
Arena* arena_local(void);
void arena_pop(void);

#define arena_alloc(a, s) (arena_alloc_aligned(a, s, alignof(max_align_t)))
#define DO_SCRATCH(a) \
  for (size_t _i = (arena_push(a), 0); _i < 1; ++_i, arena_pop())

#endif /* ARENA_H_ */

