// writeKey.c
// Copyright (c) 2019 Jonathan Archer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "easykey.h"
#include "easykey/extras.h"

/*
Writes a value to a key. First it checks if the key already
exists, and if the key does, the function will overwrite it. Otherwise, the
function will create the key at the end of the file.
*/
void writeKey(const char *Filename, const ek_key Key) {
  long int SectionPos = findSection(Filename, Key.Section);
  long int KeyPos = findKey(Filename, Key);

  FILE *File = rwopen(Filename);

  // If the section does not exist, then create it.
  if (SectionPos == EK_SECTION_NO_EXIST) {
    fseek(File, 0, SEEK_END);
    // Write the section.
    fprintf(File, "[%s]\n", Key.Section);
    SectionPos = ftell(File);
  }

  // Set our position.
  if (KeyPos != EK_KEY_NO_EXIST)
    fseek(File, KeyPos, SEEK_SET);
  else
    fseek(File, SectionPos, SEEK_SET);

  // Read in the line to get its length.
  char *Line = NULL;
  size_t Len;
  getline(&Line, &Len, File);
  Len = strlen(Line);
  free(Line); // Memory was allocated by getline().

  // If the key does not exist, then create it at the start of the section.
  if (KeyPos == EK_KEY_NO_EXIST)
    KeyPos = SectionPos + Len;

  // Read the remainder of the file into a buffer.
  long BufferSize = fsize(File) + Len - KeyPos;
  char *Buffer = malloc(BufferSize);
  fread(Buffer, BufferSize, 1, File);

  // Create the key.
  fseek(File, KeyPos, SEEK_SET);
  fprintf(File, "%s=%s\n", Key.Name, Key.Data);

  // Overwrite the remaining data and free the buffer.
  fputs(Buffer, File);
  free(Buffer);

  // Store our current position, close the file, and truncate to our new length.
  int NewSize = ftell(File);
  fclose(File);
  truncate(Filename, NewSize); // Trims off any garbage.
}