// section.c

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

#include <unistd.h>

#include "easykey.h"
#include "easykey/extras.h"

/*
This function checks if a section exists in a given file, and returns the
position if it exists. If the section does not exist, then the function returns
EK_SECTION_NO_EXIST (-2).
*/
long findSection(const char *Filename, const char *Section) {
  long Pos = EK_SECTION_NO_EXIST;
  FILE *File = rwopen(Filename);

  // Read in every line until we find the section.
  char *Line = NULL;
  size_t Len;
  while (getline(&Line, &Len, File) != -1)
    if (isSectionNamed(Line, Section)) {
      // Set the position.
      Pos = ftell(File) - strlen(Line);
      break;
    }
  free(Line); // Memory was allocated by getline().
  fclose(File);
  return Pos;
}

/*
Checks a line to see if it contains a section.
*/
bool isSection(const char *Line) {
  return (Line[0] == '[' && strchr(Line, ']') != NULL);
}

/*
Checks a line to see if it is a specific section.
*/
bool isSectionNamed(const char *Line, const char *Section) {
  if (isSection(Line))
    return (strncmp(&Line[1], Section, strlen(Section)) == 0 &&
            Line[strlen(Section) + 1] == ']');
  return false;
}