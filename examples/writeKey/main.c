// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  ek_key MyKey;
  MyKey.Name = "FRUITS";
  MyKey.Data = (char *)malloc(255 * sizeof(char));

  readKey("../example.kf", &MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);

  strcpy(MyKey.Data, "Pears Oranges");
  writeKey("../example.kf", MyKey);

  readKey("../example.kf", &MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);

  strcpy(MyKey.Data, "Grapes");
  writeKey("../example.kf", MyKey);

  readKey("../example.kf", &MyKey);
  printf("Key '%s' contains: %s\n", MyKey.Name, MyKey.Data);

  free(MyKey.Data);
  return 0;
}