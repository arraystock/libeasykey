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
  long int SectionPos = findSection(Filename, Key.Section);
  long int KeyPos = findKey(Filename, Key);

  // Open the file.
  FILE *File;
  if (access(Filename, F_OK) != -1)
    File = fopen(Filename, "r+");
  else
    File = fopen(Filename, "w+");

  // If the section does not exist, then we must create it at the end of the
  // file.
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
  size_t Len = 0;
  getline(&Line, &Len, File);
  Len = strlen(Line);
  free(Line); // Memory was allocated by getline().

  // If the key does not exist, then we must create it at the start of the
  // section.
  if (KeyPos == EK_KEY_NO_EXIST)
    KeyPos = SectionPos + Len;

  // Get the size for how large our buffer should be.
  long BufferSize = fsize(File) + Len - KeyPos;

  // Read in the rest of the file.
  char *Buffer = malloc(BufferSize);
  fread(Buffer, BufferSize, 1, File);

  // Re-set our position.
  fseek(File, KeyPos, SEEK_SET);

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
}