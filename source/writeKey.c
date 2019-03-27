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

    // First, we read in the rest of the file after the key about to be written.
    // Then we overwrite the old key and write the new key + value to the same
    // location. Thirdly, we write back the old data after the new key. And
    // lastly, we pad the remainder of the file with whitespace.

    // TODO: After doing what's described above, rename the file to
    // 'Filename.tmp', and use it to rebuild 'Filename' without the trailing
    // whitespace.

    // Get the size for how large our buffer should be.
    long BufferSize = fsize(File) + strlen(Line) - Pos;

    // Read in the rest of the file.
    char *Buffer = malloc(BufferSize);
    fread(Buffer, BufferSize, 1, File);

    // Re-set our position.
    fseek(File, Pos, SEEK_SET);

    // Create the key.
    fprintf(File, "%s = %s\n", Key.Name, Key.Data);

    // Overwrite the remaining data.
    fputs(Buffer, File);

    // Fill the rest of the file with whitespace.
    while (ftell(File) < fsize(File))
      fputc(' ', File);

    free(Buffer);
    free(Line);
  } else {
    // Create the key at the end of the file since it does not exist.
    fseek(File, 0, SEEK_END);
    fprintf(File, "\n%s = %s", Key.Name, Key.Data);
  }
  fclose(File);
}