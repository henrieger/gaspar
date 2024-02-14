#include "inputfile.h"

#include <stdarg.h>
#include <stdlib.h>

char token[TOKEN_SIZE];
alignment_t alignment;
int taxon = 0;
int character = 0;

void yyerror(const char *s) {
  fprintf(stderr, "Error on line %d - %s\n", lineNumber, s);
  exit(-1);
}

void printError(const char *format, ...) {
  char errorText[ERROR_SIZE];
  va_list args;
  va_start(args, format);
  vsprintf(errorText, format, args);
  va_end(args);
  yyerror(errorText);
}

void convertNumberToSequence() {
  for (int i = 0; token[i]; i++) {
    char charValue = token[i] - '0';
    if (charValue < 0 || charValue > 7)
      printError("Char values must be between 0-7. Found %d\n", charValue);
    alignment[taxon].charsets[character] = 1 << charValue;
    character++;
  }
}

void addMissingData() {
  alignment[taxon].charsets[character] = CHARSET_FULL;
  character++;
}

void addCharset() {
  alignment[taxon].charsets[character] = CHARSET_EMPTY;
  for (int i = 0; token[i]; i++) {
    char charValue = token[i] - '0';
    if (charValue < 0 || charValue > 7)
      printError("Char values must be between 0-7. Found %d\n", charValue);
    alignment[taxon].charsets[character] |= 1 << charValue;
  }
  character++;
}

void checkNumberOfTaxa() {
  if (taxon != getAlignmentSize())
    printError("Wrong number of taxa in file: expected %d but alignment has %d\n", getAlignmentSize(), taxon);
}

void checkNumberOfCharacters() {
  if (character != getSequenceSize())
    printError("Wrong number of characters in taxon %d: expected %d but sequence has %d\n", taxon, getSequenceSize(), character);
}
