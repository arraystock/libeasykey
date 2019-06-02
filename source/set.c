// set.c

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

/*
Sets a key's value. Note that if the key to be set does not already exist, then
the data may be out of sort. Doesn't really matter to the program, but the ini
file will become segmented.
*/
void iniSetKey(ek_ini *Ini, const ek_key Key) {
  int i;
  for (i = 0; i < Ini->Count; i++)
    // Get to the key.
    if (!strcmp(Ini->Keys[i].Section, Key.Section) &&
        !strcmp(Ini->Keys[i].Name, Key.Name)) {
      strcpy(Ini->Keys[i].Data, Key.Data);
      return;
    }
  // If we get this far, then the key does not exist. Add it to the last entry.
  // NOTE: This assumes there is space in the 'Keys' array for the new key.
  Ini->Keys = realloc(Ini->Keys, sizeof(ek_key) * (Ini->Count + 1));
  Ini->Keys[Ini->Count].Section = strdup(Key.Section);
  Ini->Keys[Ini->Count].Name = strdup(Key.Name);
  Ini->Keys[Ini->Count].Data = strdup(Key.Data);
  (Ini->Count)++;
  // TODO: Sort?
}