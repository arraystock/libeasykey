// types.h
// Copyright (c) 2019 Jonathan Archer

#ifndef EASYKEY_TYPES_H
#define EASYKEY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ek_key {
  const char *Name;
  char *Data;
} ek_key;

#ifdef __cplusplus
}
#endif

#endif