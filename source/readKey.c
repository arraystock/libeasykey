// readKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function reads in the value of a given key. It calls findKey() first to get
the key's position (and make sure it exists), then trims off a newline if it
exists (which should always be the case AFAIK).
*/
void readKey(const char *Filename, const char *Key, char *Value) {
  long int Pos = findKey(Filename, Key);

  // If the key exists, then we continue.
  if (Pos >= 0) {
    // Open the file.
    FILE *File;
    if (access(Filename, F_OK) != -1)
      File = fopen(Filename, "r+");
    else
      File = fopen(Filename, "w+");

    // Set our position.
    fseek(File, Pos, SEEK_SET);

    // Read in the line.
    size_t Len = sizeof(Value);
    getline(&Value, &Len, File);
    fclose(File);

    // Move past key name.
    memmove(Value, Value + strlen(Key) + 3, strlen(Value));
    // Strip trailing newline.
    if (Value[strlen(Value) - 1] == '\n')
      Value[strlen(Value) - 1] = 0;
    // Strip trailing whitespace.
    while (Value[strlen(Value) - 1] == ' ')
      Value[strlen(Value) - 1] = '\0';
  }
}