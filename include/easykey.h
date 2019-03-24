// easykey.h
// Copyright (c) 2019 Jonathan Archer

#include <stdbool.h>
#include <stdio.h>

#ifndef EASYKEY_H
#define EASYKEY_H

// #define EK_VER "0.01"

#define EK_KEY_NO_EXIST -1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ek_key {
  const char *Name;
  char *Data;
} ek_key;

bool lineHasKey(const char *Line, const char *Key);

long findKey(const char *Filename, const char *Key);

void readKey(const char *Filename, ek_key Key);
void writeKey(const char *Filename, const ek_key Key);

long fsize(FILE *File);

#ifdef __cplusplus
}
#endif

#endif