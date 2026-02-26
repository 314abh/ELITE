#include "strings.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "arena.h"

String* String_new(const char* str) {
  Arena* ctx = Arena_local();
  if (ctx == NULL) {
    assert(false && "arena stack is empty.");
    return NULL;
  }

  size_t len = strlen(str);
  size_t cap = len + 1;

  char* data = Arena_alloc(ctx, sizeof(char) * cap);
  String* s = Arena_alloc(ctx, sizeof(String));

  memcpy(data, str, len);
  data[len] = '\0';

  s->_data = data;
  s->cap = cap;
  s->len = len;

  return s;
}

const char* const String_view(String* s) { return s->_data; }
