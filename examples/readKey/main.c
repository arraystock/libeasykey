// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>

int main() {
  printf("Key 'NAME' contains: %s\n", readKey("../example.kf", "NAME"));
  return 0;
}