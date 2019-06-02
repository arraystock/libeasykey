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

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "easykey.h"

int readLine(char **, FILE *);

/*
Removes leading whitespace from a string. Moves pointer, so be careful when
using on an allocated string.
*/
char *trimLeft(char *s) {
  while (*s == ' ')
    s++;
  return s;
}

/*
Loads data from an ini file into an array of keys *Keys'. Return value is the
number of keys read and allocated for.
*/
void iniLoad(const char *Filename, ek_ini *Ini) {
  int n = 16;
  Ini->Keys = calloc(n, sizeof(ek_key));
  Ini->Count = 0;
  FILE *File = fopen(Filename, "r+");
  if (File != NULL) {
    char *Section = strdup("default");
    char *Line = NULL;
    while (readLine(&Line, File) != -1) {
      if (Ini->Count >= n) {
        n += 16;
        Ini->Keys = realloc(Ini->Keys, n * sizeof(ek_key));
      }
      // Cut off any existing comment.
      char *Str;
      Str = strchr(Line, ';');
      if (Str != NULL)
        Line[Str - Line] = '\0';
      Str = strstr(Line, "//");
      if (Str != NULL)
        Line[Str - Line] = '\0';
      // Strip trailing newline/whitespaces.
      while (Line[strlen(Line) - 1] == '\n' || Line[strlen(Line) - 1] == '\r' ||
             Line[strlen(Line) - 1] == ' ')
        Line[strlen(Line) - 1] = '\0';
      // If section... else if key...
      if (Line[0] == '[' && strchr(Line, ']') != NULL) {
        // Set the current section.
        free(Section);
        Section = strdup(strtok(&Line[1], "]"));
      } else if (strchr(Line, '=') != NULL) {
        // Copy in the key.
        Ini->Keys[Ini->Count].Section = strdup(Section);
        Ini->Keys[Ini->Count].Data = strdup(trimLeft(strchr(Line, '=') + 1));
        Ini->Keys[Ini->Count].Name = strdup(strtok(strtok(Line, "="), " "));
        Ini->Count++;
      } else if (strchr(Line, ':') != NULL) {
        // Copy in the key.
        Ini->Keys[Ini->Count].Section = strdup(Section);
        Ini->Keys[Ini->Count].Data = strdup(trimLeft(strchr(Line, ':') + 1));
        Ini->Keys[Ini->Count].Name = strdup(strtok(strtok(Line, ":"), " "));
        Ini->Count++;
      }
    }
    free(Line);
    free(Section);
    fclose(File);
  }
}