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

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <threads.h>

#if !defined(ASL_REALLOC) && !defined(ASL_FREE)
#include <stdlib.h>
#define ASL_REALLOC(p, s) realloc(p, s)
#define ASL_MALLOC(s) ASL_REALLOC(NULL, s)
#define ASL_FREE(s) free(s)
#endif
#if defined(ASL_REALLOC) && !defined(ASL_FREE) || \
    !defined(ASL_REALLOC) && defined(ASL_FREE)
#error "You must defined both, ASL_REALLOC and ASL_FREE."
#endif

#ifndef ARENA_DEF_SIZE
#define ARENA_DEF_SIZE 2048
#endif

#ifndef MAX_ARENA_STACK
#define MAX_ARENA_STACK 16
#endif

typedef struct Arena {
  void *_pos, *_data;
  size_t _size;
} Arena;

Arena* Arena_new(size_t size);
void* Arena_alloc_aligned(Arena* ar, size_t size, size_t align);
void Arena_del(Arena* ar);
size_t Arena_used(Arena* ar);
size_t Arena_available(Arena* ar);

int Arena_push(Arena* ar);  // returns negative number if it's a stack overflow
Arena* Arena_local(void);
void Arena_pop(void);

#define Arena_alloc(a, s) (Arena_alloc_aligned(a, s, alignof(max_align_t)))
#define DO_SCRATCH(a) \
  for (size_t _i = (Arena_push(a), 0); _i < 1; ++_i, Arena_pop())

#endif /* ARENA_H_ */

#ifdef ARENA_IMPLEMENT

size_t Arena_used(Arena* ar) {
  if (ar == NULL) return 0;

  const char* head = (const char*)ar->_data;
  const char* tail = (const char*)ar->_pos;

  size_t used = (size_t)(tail - head);
  return used;
}

size_t Arena_available(Arena* ar) {
  if (ar == NULL) return 0;

  const char* head = (const char*)ar->_data;
  const char* tail = (const char*)ar->_pos;

  size_t size = ar->_size;
  size_t used = (size_t)(tail - head);
  size_t available = size - used;
  return available;
}

Arena* Arena_new(size_t size) {
  size = (size ? size : ARENA_DEF_SIZE);

  Arena* ar = ASL_MALLOC(sizeof(*ar));
  if (ar == NULL) return NULL;

  void* data = ASL_MALLOC(size);
  if (data == NULL) {
    ASL_FREE(ar);
    return NULL;
  }

  ar->_pos = data;
  ar->_data = data;
  ar->_size = size;
  return ar;
}

void* Arena_alloc_aligned(Arena* ar, size_t size, size_t align) {
  if (ar == NULL) return NULL;

  if (size == 0 || align == 0) return NULL;

  // if align is not a multiple of 2, return NULL
  if ((align & (align - 1)) != 0) return NULL;

  uintptr_t current = (uintptr_t)ar->_pos;
  if (current > UINTPTR_MAX - (align - 1)) return NULL;  // check for overflow

  uintptr_t aligned = (current + align - 1) & ~(uintptr_t)(align - 1);
  uintptr_t end = (uintptr_t)ar->_data + ar->_size;

  if (size > end - aligned) {
    assert(false && "net allocation exceeded space.");
    return NULL;
  }

  ar->_pos = (void*)(aligned + size);
  return (void*)aligned;
}

void Arena_wipe(Arena* ar) {
  if (ar == NULL) return;

  ar->_pos = ar->_data;
}

void Arena_del(Arena* ar) {
  if (ar == NULL) return;

  ASL_FREE(ar->_data);
  ASL_FREE(ar);
}

static thread_local Arena* ARENA__STACK__[MAX_ARENA_STACK];
static thread_local int ARENA_STACK_TOP_INDEX__ = -1;

#define Arena_Stack ARENA__STACK__
#define Arena_Top ARENA_STACK_TOP_INDEX__

int Arena_push(Arena* ar) {
  if (Arena_Top < MAX_ARENA_STACK - 1) {
    Arena_Stack[++Arena_Top] = ar;
    return Arena_Top;
  }

  return -1;
}

Arena* Arena_local(void) {
  return (Arena_Top >= 0) ? Arena_Stack[Arena_Top] : NULL;
}

void Arena_pop(void) {
  // optional: arena_del(arena_local());
  if (Arena_Top >= 0) Arena_Top--;
}

#undef Arena_Top
#undef Arena_Stack

#endif /* ARENA_IMPLEMENT */
