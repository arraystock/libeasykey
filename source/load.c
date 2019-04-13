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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"
#include "easykey/extras.h"
#include "easykey/types.h"

void iniLoad(const char *Filename, ek_ini *Ini) {

  // Clear out structure.
  for (int i = 0; i <= EK_MAX_KEYS; i++) {
    Ini->Keys[i].Section = NULL;
    Ini->Keys[i].Name = NULL;
    Ini->Keys[i].Data = NULL;
  }

  FILE *File = rwopen(Filename);
  if (File != NULL) {
    char *Section = NULL;
    char *Line = NULL;
    size_t Len;
    for (int i = 0; getline(&Line, &Len, File) != -1 && i <= EK_MAX_KEYS;) {
      // Strip trailing newline/whitespaces.
      while (Line[strlen(Line) - 1] == '\n' || Line[strlen(Line) - 1] == '\r' ||
             Line[strlen(Line) - 1] == ' ')
        Line[strlen(Line) - 1] = '\0';

      if (isSection(Line)) {
        Line = strtok(&Line[1], "]");
        Section = realloc(Section, strlen(Line));
        strcpy(Section, Line);
      }

      else if (isKey(Line)) {
        Ini->Keys[i].Section = malloc(strlen(Section));
        strcpy(Ini->Keys[i].Section, Section);

        Ini->Keys[i].Data = malloc(strlen(&Line[strcspn(Line, "=") + 1]));
        strcpy(Ini->Keys[i].Data, &Line[strcspn(Line, "=") + 1]);

        Ini->Keys[i].Name = malloc(strlen(strtok(Line, "=")));
        strcpy(Ini->Keys[i].Name, Line);

        i++;
      }
    }
    fclose(File);
  }
}