// easykey.h
// Copyright (c) 2019 Jonathan Archer

#include <stdbool.h>

#ifndef EASYKEY_H
#define EASYKEY_H

#define EK_KEY_NO_EXIST -1

#ifdef __cplusplus
extern "C" {
#endif

bool lineHasKey(const char *Line, const char *Key);

long int findKey(const char *Filename, const char *Key);

const char *readKey(const char *Filename, const char *Key);

#ifdef __cplusplus
}
#endif

#endif