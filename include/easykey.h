// easykey.h
// Copyright (c) 2019 Jonathan Archer

#include <stdbool.h>
#include <stdio.h>

#include "easykey/types.h"

#ifndef EASYKEY_H
#define EASYKEY_H

// #define EK_VER "0.01"

enum { EK_KEY_NO_EXIST = -1, EK_SECTION_NO_EXIST = -2 };

#ifdef __cplusplus
extern "C" {
#endif

bool isSection(const char *Line);
bool isSectionNamed(const char *Line, const char *Section);
long findSection(const char *Filename, const char *Section);

bool isKey(const char *Line, const char *KeyName);

long findKey(const char *Filename, ek_key Key);

void readKey(const char *Filename, ek_key Key);
void writeKey(const char *Filename, const ek_key Key);

#ifdef __cplusplus
}
#endif

#endif