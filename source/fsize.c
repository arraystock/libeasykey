// fsize.c
// Copyright (c) 2019 Jonathan Archer

#include "easykey.h"

long fsize(FILE *File) {
  long Pos = ftell(File);
  fseek(File, 0, SEEK_END);
  long Size = ftell(File);
  fseek(File, Pos, SEEK_SET);
  return Size;
}