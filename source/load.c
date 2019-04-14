// load.c

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

#define Key Ini->Keys[Ini->Count]

/*
Loads data from an ini file into 'ek_ini *Ini'.
*/
void iniLoad(const char *Filename, ek_ini *Ini) {
  Ini->Count = 0;
  FILE *File = fopen(Filename, "r+");
  if (File != NULL) {
    char Section[32] = "default";
    char *Line = NULL;
    size_t Len;
    for (; getline(&Line, &Len, File) != -1 && Ini->Count < EK_MAX_KEYS;) {
      // Strip trailing newline/whitespaces.
      while (Line[strlen(Line) - 1] == '\n' || Line[strlen(Line) - 1] == '\r' ||
             Line[strlen(Line) - 1] == ' ')
        Line[strlen(Line) - 1] = '\0';
      // If section... else if key...
      if (Line[0] == '[' && strchr(Line, ']') != NULL) {
        // Set the current section.
        strcpy(Section, strtok(&Line[1], "]"));
      } else if (strchr(Line, '=') != NULL) {
        // Copy in the key.
        strcpy(Key.Section, Section);
        strcpy(Key.Data, &Line[strcspn(Line, "=") + 1]);
        strcpy(Key.Name, strtok(Line, "="));
        Ini->Count++;
      }
    }
    fclose(File);
  }
}