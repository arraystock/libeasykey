// lineHasKey.c
// Copyright (c) 2019 Jonathan Archer

#include <string.h>

#include "easykey.h"

bool lineHasKey(const char *Line, const char *Key) {
  return (strncmp(Key, Line, strlen(Key)) == 0) &&
         (strncmp(&Line[strlen(Key)], " = ", 3) == 0);
}