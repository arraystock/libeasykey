// writeKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"
#include "easykey/extras.h"

/*
This function writes a value to a key. First it checks if the key already
exists, and if the key does, the function will overwrite it. Otherwise, the
function will create the key at the end of the file.
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
    // Rewrite the key in the same location. Involves reading the rest of the
    // file after the key into memory, writing the new key, and writing back the
    // rest of the file.

    // Set our position.
    fseek(File, Pos, SEEK_SET);

    // Read in the line to get its length.
    char *Line = (char *)malloc(255 * sizeof(char));
    size_t Len = 0;
    getline(&Line, &Len, File);
    int LineLen = strlen(Line);
    free(Line);

    // Get the size for how large our buffer should be.
    long BufferSize = fsize(File) + LineLen - Pos;

    // Read in the rest of the file.
    char *Buffer = malloc(BufferSize);
    fread(Buffer, BufferSize, 1, File);

    // Re-set our position.
    fseek(File, Pos, SEEK_SET);

    // Create the key.
    fprintf(File, "%s=%s\n", Key.Name, Key.Data);

    // Overwrite the remaining data and free the buffer.
    fputs(Buffer, File);
    free(Buffer);

    // Store our current position and close the file.
    int FilePos = ftell(File);
    fclose(File);

    // Truncate the file, trimming off any garbage left (if the new key's value
    // takes up fewer characters).
    truncate(Filename, FilePos);
  } else {
    // Create the key at the end of the file since it does not exist.

    // Check if there's a newline, and make one if there isn't.
    fseek(File, -1, SEEK_END);
    if (getc(File) != '\n')
      fputc('\n', File);

    // Write the key.
    fprintf(File, "%s=%s", Key.Name, Key.Data);
    fclose(File);
  }
}