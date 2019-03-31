// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>

ek_key MyKey;

int main() {
  MyKey.Section = "section2";
  MyKey.Name = "NAME";
  MyKey.Data = (char *)malloc(255 * sizeof(char));
  readKey("../example.ini", MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);
  free(MyKey.Data);
  return 0;
}