#ifndef AC_STRINGS_H
#define AC_STRINGS_H

#include <stddef.h>

typedef struct {
  // cap is total bytes allocated.
  // len is the total readable ASCII characters.
  size_t len, cap;
  char* _data;
} String;

String* String_new(const char* str);
char* String_view(String* s);

#endif
