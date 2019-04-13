// extras.c

/*
MIT License

Copyright (c) 2019 Jonathan Archer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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