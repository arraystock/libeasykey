// flush.c

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

#include <stdlib.h>
#include <string.h>

#include "easykey.h"

void iniFlush(const char *Filename, ek_ini Ini) {
  FILE *File = fopen(Filename, "w+");
  if (File != NULL) {
    char Section[32] = "default";
    for (int i = 0; i < Ini.Count; i++) {
      if (strcmp(Ini.Keys[i].Section, Section)) {
        strcpy(Section, Ini.Keys[i].Section);
        fprintf(File, "[%s]\n", Section);
      }
      fprintf(File, "%s=%s\n", Ini.Keys[i].Name, Ini.Keys[i].Data);
    }
    fclose(File);
  }
}