// writeKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

/*
This function writes a value to a key. First it checks if the key already
exists, and if the new key is smaller or the same size as the old one, it will
overwrite it. Otherwise it will overwrite the existing key and recreate it at
the end of the file.
*/
void writeKey(const char *Filename, const ek_key Key) {
  long int Pos = findKey(Filename, Key.Name);

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

    // If the new key value is larger than the old, we overwrite the old one and
    // write the new key + value to the end of the file. Otherwise, we just
    // overwrite the old key (and pad the difference with whitespace).

    // If the new key value is larger...else if it is smaller.
    if (strlen(Line) < strlen(Key.Name) + strlen(Key.Data) + 3) {
      // Get the size for how large our buffer should be.
      long BufferSize = fsize(File) + strlen(Line) - Pos;

      // Read in the rest of the file.
      char *Buffer = malloc(BufferSize);
      fread(Buffer, BufferSize, 1, File);

      // Re-set our position.
      fseek(File, Pos, SEEK_SET);

      // Overwrite.
      fputs(Buffer, File);

      // Create the key.
      fprintf(File, "\n%s = %s", Key.Name, Key.Data);
    } else {
      // Set our position and overwrite the existing value.
      fseek(File, Pos + strlen(Key.Name) + 3, SEEK_SET);
      fputs(Key.Data, File);

      // Fill the rest of the line with blank characters.
      for (int i = 0;
           i + strlen(Key.Name) + strlen(Key.Data) + 3 < strlen(Line) - 1; i++)
        fputc(' ', File);

      // Add newline.
      fputc('\n', File);
    }
    free(Line);
  } else {
    // Create the key at the end of the file since it does not exist.
    fseek(File, 0, SEEK_END);
    fprintf(File, "\n%s = %s", Key.Name, Key.Data);
  }
  fclose(File);
}