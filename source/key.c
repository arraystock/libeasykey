// key.c

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
This function checks if a key exists in a given file, and returns the position
if it exists. If the key does not exist, then the function returns
EK_KEY_NO_EXIST (-1).
*/
long findKey(const char *Filename, const ek_key Key) {
  long Pos = findSection(Filename, Key.Section);
  long RetVal = EK_KEY_NO_EXIST;
  if (Pos != EK_SECTION_NO_EXIST) {
    FILE *File = rwopen(Filename);

    // Read in every line until we find the key.
    char *Line = NULL;
    size_t Len;
    fseek(File, Pos, SEEK_SET);
    while (getline(&Line, &Len, File) != -1) {
      // Make sure we don't read into the next section.
      if (isSection(Line) && !isSectionNamed(Line, Key.Section))
        break;
      // If it is the key, then we store the value and break.
      if (isKeyNamed(Line, Key)) {
        RetVal = ftell(File) - strlen(Line);
        break;
      }
    }
    free(Line); // Memory was allocated by getline().
    fclose(File);
  }
  return RetVal;
}

/*
This function reads the beginning of a line and checks if it starts with the key
name and if the key name has a proper assignment.
*/
bool isKey(const char *Line) { return (strchr(Line, '=') != NULL); }

/*
This function reads the beginning of a line and checks if it starts with the key
name and if the key name has a proper assignment.
*/
bool isKeyNamed(const char *Line, const ek_key Key) {
  return (strncmp(Key.Name, Line, strlen(Key.Name)) == 0 &&
          Line[strlen(Key.Name)] == '=');
}