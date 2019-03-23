// readKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function reads in the value of a given key. It calls findKey() first to get
the key's position (and make sure it exists), then trims off a newline if it
exists (which should always be the case AFAIK).
*/
const char *readKey(const char *Filename, const char *Key) {
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
    char *Line;
    size_t Len = 0;
    getline(&Line, &Len, File);

    // Move past key name.
    Line += strlen(Key) + 3;

    // Strip newLine.
    if (Line[strlen(Line) - 1] == '\n')
      Line[strlen(Line) - 1] = 0;

    fclose(File);
    return Line;
  }
  // Return an empty string if the key does not exist.
  return "";
}