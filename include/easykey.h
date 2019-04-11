// easykey.h

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

#include <stdbool.h>
#include <stdio.h>

#include "easykey/types.h"

#ifndef EASYKEY_H
#define EASYKEY_H

#define EK_VER "v0.02"

enum { EK_KEY_NO_EXIST = -1, EK_SECTION_NO_EXIST = -2 };

#ifdef __cplusplus
extern "C" {
#endif

bool isSection(const char *Line);
bool isSectionNamed(const char *Line, const char *Section);
long findSection(const char *Filename, const char *Section);

bool isKeyNamed(const char *Line, ek_key Key);
long findKey(const char *Filename, ek_key Key);

void readKey(const char *Filename, ek_key Key);
void writeKey(const char *Filename, const ek_key Key);

#ifdef __cplusplus
}
#endif

#endif