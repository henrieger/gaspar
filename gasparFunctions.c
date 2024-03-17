#include "eval/parsimony.h"
#include "gaspar.h"
#include "sequence-alignment/sequence-alignment.h"

#include <stdarg.h>
#include <stdlib.h>

char token[TOKEN_SIZE];
alignment_t alignment;
int taxon = 0;
int character = 0;

sequence_t *unionSequence, *intersectionSequence, *mask;

// Prints errors and exits
void yyerror(const char *s) {
  fprintf(stderr, "Error on line %d - %s\n", lineNumber, s);
  exit(-1);
}

// Sofisticated error print function
void printError(const char *format, ...) {
  char errorText[ERROR_SIZE];
  va_list args;
  va_start(args, format);
  vsprintf(errorText, format, args);
  va_end(args);
  yyerror(errorText);
}

// Initialize global alignment and weights based on provided dimensions
void initializeAlignment() {
  alignment = newAlignment();
  createCharacterWeights();
}

// Transforms numbers read from input to current sequence
void addNumbersToSequence() {
  for (int i = 0; token[i]; i++) {
    char charValue = token[i] - '0';
    if (charValue < 0 || charValue > 7)
      printError("Char values must be between 0-7. Found %d\n", charValue);
    alignment[taxon].charsets[character] = 1 << charValue;
    character++;
  }
}

// Adds a missing data to current sequence
void addMissingData() {
  alignment[taxon].charsets[character] = CHARSET_FULL;
  character++;
}

// Adds a charset to current sequence
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

// Check if number of parsed taxa corresponds with assigned taxa
void checkNumberOfTaxa() {
  if (taxon != getAlignmentSize())
    printError(
        "Wrong number of taxa in file: expected %d but alignment has %d\n",
        getAlignmentSize(), taxon);
}

// Check if number of parsed characters in taxon corresponds with assigned
// amount
void checkNumberOfCharacters() {
  if (character != getSequenceSize())
    printError("Wrong number of characters in taxon %d: expected %d but "
               "sequence has %d\n",
               taxon, getSequenceSize(), character);
}

void createAuxSequences() {
  unionSequence = newSequence(NULL);
  intersectionSequence = newSequence(NULL);
  mask = newSequence(NULL);
}

void destroyAuxSequences() {
  destroySequence(unionSequence);
  destroySequence(intersectionSequence);
  destroySequence(mask);
}
