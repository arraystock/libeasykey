// findKey.c
// Copyright (c) 2019 Jonathan Archer

#ifndef EASYKEY_H
#define EASYKEY_H

#define EK_KEY_NO_EXIST -1

#ifdef __cplusplus
extern "C" {
#endif

long int findKey(const char *Filename, const char *Key);

#ifdef __cplusplus
}
#endif

#endif