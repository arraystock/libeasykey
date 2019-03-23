// findKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function checks if a key exists in a given file, and returns the position
if it exists. An example call would be findKey(myFile, "MY_KEY"), and the
function will scan for a line starting with "MY_KEY = ". If the key does not
exist, then the function returns EK_KEY_NO_EXIST (-1).
*/
long int findKey(const char *Filename, const char *Key) {
  long int Pos = EK_KEY_NO_EXIST;
  FILE *File;

  if (access(Filename, F_OK) != -1)
    File = fopen(Filename, "r+");
  else
    File = fopen(Filename, "w+");

  char *Line;
  size_t Len = 0;

  // Read in every line until we find the key.
  while (getline(&Line, &Len, File) != -1)
    if ((strncmp(Key, Line, strlen(Key)) == 0) &&
        (strncmp(&Line[strlen(Key)], " = ", 3) == 0)) {
      // Set the position.
      fseek(File, -strlen(Line), SEEK_CUR);
      Pos = ftell(File);
      break;
    }
  fclose(File);
  return Pos;
}