// readKey.c

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
This function reads the value of a key into a buffer. It also trims off trailing
newlines and spaces.
*/
void readKey(const char *Filename, ek_key Key) {
  long int Pos = findKey(Filename, Key);

  // If the key exists, then we continue.
  if (Pos >= 0) {
    FILE *File = rwopen(Filename);

    // Read in the line, then close the file.
    fseek(File, Pos, SEEK_SET);
    size_t Len;
    getline(&Key.Data, &Len, File);
    fclose(File);

    // Move past key name.
    strcpy(Key.Data, Key.Data + strlen(Key.Name) + 1);

    // Strip trailing newline/whitespaces.
    while (Key.Data[strlen(Key.Data) - 1] == '\r' ||
           Key.Data[strlen(Key.Data) - 1] == '\n' ||
           Key.Data[strlen(Key.Data) - 1] == ' ')
      Key.Data[strlen(Key.Data) - 1] = '\0';
  }
}