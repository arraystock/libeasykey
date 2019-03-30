// findKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function checks if a key exists in a given file, and returns the position
if it exists. If the key does not exist, then the function returns
EK_KEY_NO_EXIST (-1).
*/
long findKey(const char *Filename, ek_key Key) {
  long Pos = findSection(Filename, Key.Section);
  if (Pos != EK_SECTION_NO_EXIST) {
    FILE *File;
    if (access(Filename, F_OK) != -1)
      File = fopen(Filename, "r+");
    else
      File = fopen(Filename, "w+");

    char *Line = (char *)malloc(255 * sizeof(char));
    size_t Len = 0;

    fseek(File, Pos, SEEK_SET);

    // Read in every line until we find the key.
    while (getline(&Line, &Len, File) != -1) {
      // Make sure we don't read into the next section.
      if (isSection(Line) && !isSectionNamed(Line, Key.Section))
        return EK_KEY_NO_EXIST;
      if (isKey(Line, Key))
        return ftell(File) - strlen(Line);
    }
    free(Line);
    fclose(File);
  } else
    return EK_SECTION_NO_EXIST;
  return EK_KEY_NO_EXIST;
}