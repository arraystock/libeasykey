// extras.c
// Copyright (c) 2019 Jonathan Archer

#include <unistd.h>

#include "easykey.h"

/*
Returns the size of a file.
*/
long fsize(FILE *File) {
  long Pos = ftell(File);
  fseek(File, 0, SEEK_END);
  long Size = ftell(File);
  fseek(File, Pos, SEEK_SET);
  return Size;
}

/*
Opens a file for reading and writing, or creates it if it does not exist.
*/
FILE *rwopen(const char *Filename) {
  if (access(Filename, F_OK) != -1)
    return fopen(Filename, "r+");
  else
    return fopen(Filename, "w+");
}