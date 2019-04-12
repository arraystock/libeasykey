// readKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function reads the value of a key into a buffer. It also trims off trailing
newlines and spaces.
*/
void readKey(const char *Filename, ek_key Key) {
  long int Pos = findKey(Filename, Key);

  // If the key exists, then we continue.
  if (Pos >= 0) {
    // Open the file.
    FILE *File;
    if (access(Filename, F_OK) != -1)
      File = fopen(Filename, "r+");
    else
      File = fopen(Filename, "w+");

    // Read in the line, then close the file.
    fseek(File, Pos, SEEK_SET);
    size_t Len;
    getline(&Key.Data, &Len, File);
    fclose(File);

    // Move past key name.
    strcpy(Key.Data, Key.Data + strlen(Key.Name) + 1);

    // Strip trailing newline/whitespaces.
    while (Key.Data[strlen(Key.Data) - 1] == '\r' ||
           Key.Data[strlen(Key.Data) - 1] == '\n' ||
           Key.Data[strlen(Key.Data) - 1] == ' ')
      Key.Data[strlen(Key.Data) - 1] = '\0';
  }
}