// writeKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function writes a value to a key. First it checks if the key already
exists, and if the new key is smaller or the same size as the old one, it will
overwrite it. Otherwise it will clear the existing key and create the key again
at the end of the file with the new value.
*/
void writeKey(const char *Filename, const char *Key, const char *Value) {
  long int Pos = findKey(Filename, Key);

  // Open the file.
  FILE *File;
  if (access(Filename, F_OK) != -1)
    File = fopen(Filename, "r+");
  else
    File = fopen(Filename, "w+");

  if (Pos >= 0) {
    // Set our position.
    fseek(File, Pos, SEEK_SET);

    // Read in the line.
    char *Line = (char *)malloc(255 * sizeof(char));
    size_t Len = 0;
    getline(&Line, &Len, File);

    // If the new key value is larger than the old, we clear out the old one and
    // write the new key + value to the end of the file. Otherwise, we just
    // overwrite the old key.

    // TODO: If the new key is bigger than the old one, then read everything
    // after the key into memory, write the key, and rewrite the rest of the
    // file after the key to avoid whitespace buildup.
    if (strlen(Line) < strlen(Key) + strlen(Value) + 3) {
      // printf("Bigger!\n");
      // Re-set our position, as getline() has changed it.
      fseek(File, Pos, SEEK_SET);
      // Set the line to all whitespace with a newline at the end before writing
      // it back to the file.
      memset(Line, ' ', strlen(Line));
      Line[strlen(Line) - 1] = '\n';
      fputs(Line, File);

      // Create the key.
      fseek(File, 0, SEEK_END);
      fprintf(File, "\n%s = %s", Key, Value);
    } else {
      // Set our position and overwrite the existing value.
      fseek(File, Pos + strlen(Key) + 3, SEEK_SET);
      fputs(Value, File);
      // Fill the rest of the line with blank characters.
      for (int i = 0; i + strlen(Key) + strlen(Value) + 3 < strlen(Line) - 1;
           i++)
        fputc(' ', File);
      // Add newline.
      fputc('\n', File);
    }
    free(Line);
  } else {
    // Create the key.
    fseek(File, 0, SEEK_END);
    fprintf(File, "\n%s = %s", Key, Value);
  }
  fclose(File);
  return;
}