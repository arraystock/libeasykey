// section.c
// Copyright (c) 2019 Jonathan Archer

#include <string.h>

#include "easykey.h"

/*
Checks a line to see if it contains a section.
*/
bool isSection(const char *Line) {
  return (Line[0] == '[' && strchr(Line, ']') != NULL);
}

/*
Checks a line to see if it is a specific section.
*/
bool isSectionNamed(const char *Line, const char *Section) {
  if (isSection(Line))
    return (strncmp(&Line[1], Section, strlen(Section)) == 0 &&
            strchr(Line, ']') != NULL);
  return false;
}