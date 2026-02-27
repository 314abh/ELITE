#include "strings.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "arena.h"

String* string_new(const char* str) {
  Arena* ctx = arena_local();
  if (ctx == NULL) {
    assert(false && "arena stack is empty.");
    return NULL;
  }

  size_t len = strlen(str);
  size_t cap = len + 1;

  char* data = arena_alloc(ctx, sizeof(char) * cap);
  String* s = arena_alloc(ctx, sizeof(String));

  memcpy(data, str, len);
  data[len] = '\0';

  s->_data = data;
  s->cap = cap;
  s->len = len;

  return s;
}

char* string_view(String* s) { return s->_data; }
