// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *Val = (char *)malloc(255 * sizeof(char));
  readKey("../example.kf", "NAME", Val);
  printf("Key 'NAME' contains: %s\n", Val);
  return 0;
}