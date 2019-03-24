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
void readKey(const char *Filename, ek_key Key) {
  long int Pos = findKey(Filename, Key.Name);

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
    size_t Len = sizeof(Key.Data);
    getline(&Key.Data, &Len, File);
    fclose(File);

    // Move past key name.
    memmove(Key.Data, Key.Data + strlen(Key.Name) + 3, strlen(Key.Data));
    // Strip trailing newline.
    if (Key.Data[strlen(Key.Data) - 1] == '\n')
      Key.Data[strlen(Key.Data) - 1] = 0;
    // Strip trailing whitespace.
    while (Key.Data[strlen(Key.Data) - 1] == ' ')
      Key.Data[strlen(Key.Data) - 1] = '\0';
  }
}