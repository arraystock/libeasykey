// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  ek_key MyKey;
  MyKey.Name = "NAME";
  MyKey.Data = (char *)malloc(255 * sizeof(char));
  readKey("../example.ini", MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);
  return 0;
}