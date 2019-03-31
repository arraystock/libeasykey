// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ek_key MyKey;

int main() {
  MyKey.Section = "section1";
  MyKey.Name = "FRUITS";
  MyKey.Data = (char *)malloc(255 * sizeof(char));

  readKey("../example.ini", MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);

  strcpy(MyKey.Data, "Pears Oranges");
  writeKey("../example.ini", MyKey);

  readKey("../example.ini", MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);

  strcpy(MyKey.Data, "Grapes");
  writeKey("../example.ini", MyKey);

  readKey("../example.ini", MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);

  free(MyKey.Data);
  return 0;
}