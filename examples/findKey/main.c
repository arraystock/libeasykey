// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>

ek_key MyKey;

int main() {
  MyKey.Section = "section0";
  MyKey.Name = "EXAMPLE_KEY";
  printf("Key '%s' fpos: %ld\n", MyKey.Name, findKey("../example.ini", MyKey));
  return 0;
}