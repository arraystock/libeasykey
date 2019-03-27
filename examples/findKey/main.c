// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>

int main() {
  printf("Key 'EXAMPLE_KEY' fpos: %ld\n", findKey("../example.ini", "EXAMPLE_KEY"));
  return 0;
}