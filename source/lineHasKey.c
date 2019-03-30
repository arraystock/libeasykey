// isKey.c
// Copyright (c) 2019 Jonathan Archer

#include <string.h>

#include "easykey.h"

/*
This function reads the beginning of a line and checks if it starts with the key
name and if the key name has a proper assignment.
*/
bool isKey(const char *Line, const char *KeyName) {
  if (strncmp(KeyName, Line, strlen(KeyName)) == 0) {
    // Probably safe to assume it's a proper key if it has the key name and
    // either a '=' or ':'.
    // TODO: Do some sort of strnstr to check just the bounds of the assignment.
    return (strstr(&Line[strlen(KeyName)], "=") == NULL ||
            strstr(&Line[strlen(KeyName)], ":") == NULL);
  }
  return false;
}