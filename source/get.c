// get.c

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
Retrieves a key's value.
*/
char *iniGetKey(const ek_ini Ini, ek_key *Key) {
  for (int i = 0; i <= EK_MAX_KEYS && Ini.Keys[i].Data != NULL; i++)
    if (!strcmp(Ini.Keys[i].Section, Key->Section) &&
        !strcmp(Ini.Keys[i].Name, Key->Name)) {
      Key->Data = realloc(Key->Data, strlen(Ini.Keys[i].Data));
      strcpy(Key->Data, Ini.Keys[i].Data);
      break;
    }
  return Key->Data;
}