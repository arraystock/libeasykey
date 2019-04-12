// section.c
// Copyright (c) 2019 Jonathan Archer

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"
#include "easykey/extras.h"

/*
This function checks if a section exists in a given file, and returns the
position if it exists. If the section does not exist, then the function returns
EK_SECTION_NO_EXIST (-2).
*/
long findSection(const char *Filename, const char *Section) {
  long Pos = EK_SECTION_NO_EXIST;
  FILE *File = rwopen(Filename);

  // Read in every line until we find the section.
  char *Line = NULL;
  size_t Len;
  while (getline(&Line, &Len, File) != -1)
    if (isSectionNamed(Line, Section)) {
      // Set the position.
      Pos = ftell(File) - strlen(Line);
      break;
    }
  free(Line); // Memory was allocated by getline().
  fclose(File);
  return Pos;
}

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
            Line[strlen(Section) + 1] == ']');
  return false;
}