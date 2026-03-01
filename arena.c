/* arena.c */

#include "arena.h"

size_t arena_used(Arena* ar) {
  if (ar == NULL) return 0;

  const char* head = (const char*)ar->_data;
  const char* tail = (const char*)ar->_pos;

  size_t used = (size_t)(tail - head);
  return used;
}

size_t arena_available(Arena* ar) {
  if (ar == NULL) return 0;

  const char* head = (const char*)ar->_data;
  const char* tail = (const char*)ar->_pos;

  size_t size = ar->_size;
  size_t used = (size_t)(tail - head);
  size_t available = size - used;
  return available;
}

Arena* arena_new(size_t size) {
  size = (size ? size : ARENA_DEF_SIZE);

  Arena* ar = ARENA_MALLOC(sizeof(*ar) + size);
  if (ar == NULL) return NULL;

  ar->_pos = ar->_data;
  ar->_size = size;
  return ar;
}

void* arena_alloc_aligned(Arena* ar, size_t size, size_t align) {
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

void arena_wipe(Arena* ar) {
  if (ar == NULL) return;
  ar->_pos = ar->_data;
}

void arena_del(Arena* ar) {
  if (ar == NULL) return;
  ARENA_FREE(ar);
}

static thread_local Arena* ARENA__STACK__[MAX_ARENA_STACK];
static thread_local int ARENA_STACK_TOP_INDEX__ = -1;

#define arena_Stack ARENA__STACK__
#define arena_Top ARENA_STACK_TOP_INDEX__

int arena_push(Arena* ar) {
  if (arena_Top < MAX_ARENA_STACK - 1) {
    arena_Stack[++arena_Top] = ar;
    return arena_Top;
  }

  return -1;
}

Arena* arena_local(void) {
  return (arena_Top >= 0) ? arena_Stack[arena_Top] : NULL;
}

void arena_pop(void) {
  if (arena_Top >= 0) arena_Top--;
}

#undef arena_Top
#undef arena_Stack


