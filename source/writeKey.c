// writeKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"

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
    // Set our position.
    fseek(File, Pos, SEEK_SET);

    // Read in the line to get its length.
    char *Line = (char *)malloc(255 * sizeof(char));
    size_t Len = 0;
    getline(&Line, &Len, File);
    int LineLen = strlen(Line);
    free(Line);

    // First, we read in the rest of the file after the key about to be written.
    // Then we overwrite the old key and write the new key + value to the same
    // location. Thirdly, we write back the old data after the new key. And
    // lastly, we truncate the file to remove possible garbage.

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
    fseek(File, 0, SEEK_END);
    fprintf(File, "\n%s = %s", Key.Name, Key.Data);
    fclose(File);
  }
}