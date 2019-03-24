// main.c
// Copyright (c) 2019 Jonathan Archer

#include <easykey.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *Val = (char *)malloc(255 * sizeof(char));
  readKey("../example.kf", "FRUITS", Val);
  printf("Key 'FRUITS' contains: %s\n", Val);
  // printf("Using writeKey() to update the key 'FRUITS'...\n");
  writeKey("../example.kf", "FRUITS", "Pears Oranges");
  readKey("../example.kf", "FRUITS", Val);
  printf("Key 'FRUITS' contains: %s\n", Val);
  // printf("Using writeKey() to update the key 'FRUITS'...\n");
  writeKey("../example.kf", "FRUITS", "Grapes");
  readKey("../example.kf", "FRUITS", Val);
  printf("Key 'FRUITS' contains: %s\n", Val);
  return 0;
}