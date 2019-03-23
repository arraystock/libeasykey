// lineHasKey.c
// Copyright (c) 2019 Jonathan Archer

#include <string.h>

#include "easykey.h"

/*
This function reads the beginning of a line and checks if it starts with the key
name and if the key name is followed by " = ".
*/
bool lineHasKey(const char *Line, const char *Key) {
  return (strncmp(Key, Line, strlen(Key)) == 0) &&
         (strncmp(&Line[strlen(Key)], " = ", 3) == 0);
}