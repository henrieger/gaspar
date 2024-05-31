#include "config.h"
#include "gaspar.h"
#include "sequence-alignment/sequence-alignment.h"

#include <stdarg.h>
#include <stdlib.h>

char token[TOKEN_SIZE];
alignment_t *alignment;
int taxon = 0;
int character = 0;
char **labels;
config_t config;

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
  labels = malloc(getAlignmentSize() * sizeof(char *));
  labels[0] = malloc(getAlignmentSize() * LABEL_SIZE * sizeof(char));
  for (int i = 1; i < getAlignmentSize(); i++)
    labels[i] = *labels + (i * LABEL_SIZE);
  alignment = newAlignment(getAlignmentSize(), labels);
  createCharacterWeights();
}

// Transforms numbers read from input to current sequence
void addNumbersToSequence() {
  for (int i = 0; token[i]; i++) {
    int charValue = token[i] - '0';
    if (charValue < 0 || charValue >= CHAR_STATES)
      printError("Char values must be between 0-%d. Found %d\n",
                 CHAR_STATES - 1, charValue);

    int allowedTIndex = character / (8 * sizeof(allowed_t));
    int positionInAllowedT = (character / (8 * sizeof(long long))) % 4;
    int shiftAmount = character % (8 * sizeof(long long));

    alignment->sequences[taxon]
        .allowed[charValue][allowedTIndex][positionInAllowedT] |=
        1LL << shiftAmount;
    character++;
  }
}

// Adds a missing data to current sequence
void addMissingData() {
  for (int i = 0; i < CHAR_STATES; i++) {
    int allowedTIndex = character / (8 * sizeof(allowed_t));
    int positionInAllowedT = (character / (8 * sizeof(long long))) % 4;
    int shiftAmount = character % (8 * sizeof(long long));

    alignment->sequences[taxon].allowed[i][allowedTIndex][positionInAllowedT] |=
        1LL << shiftAmount;
  }
  character++;
}

// Adds a charset to current sequence
void addMultistateChar() {
  for (int i = 0; token[i]; i++) {
    int charValue = token[i] - '0';
    if (charValue < 0 || charValue >= CHAR_STATES)
      printError("Char values must be between 0-%d. Found %d\n",
                 CHAR_STATES - 1, charValue);

    int allowedTIndex = character / (8 * sizeof(allowed_t));
    int positionInAllowedT = (character / (8 * sizeof(long long))) % 4;
    int shiftAmount = character % (8 * sizeof(long long));

    alignment->sequences[taxon]
        .allowed[charValue][allowedTIndex][positionInAllowedT] |=
        1LL << shiftAmount;
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
