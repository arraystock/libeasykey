// main.c

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

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IniFile "../example.ini"

ek_key Key = {"section1", "FRUITS", NULL};
char *Value = "Pears Oranges";

int main() {
  // Load the ini file to memory.
  ek_key Ini[64];
  int Count = iniLoad(IniFile, Ini);

  // Get the key.
  iniGetKey(Ini, Count, &Key);

  printf("Key '%s' contains: '%s'...\n", Key.Name, Key.Data);

  // Set the key.
  Key.Data = Value;

  iniSetKey(Ini, &Count, Key);

  iniGetKey(Ini, Count, &Key);
  printf("And now key '%s' contains: '%s'.\n", Key.Name, Key.Data);

  iniFlush(IniFile, Ini, Count);

  // Free up our memory to avoid any leaks.
  iniFree(Ini, Count);

  return 0;
}