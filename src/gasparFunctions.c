#include "config.h"
#include "gaspar.h"
#include "sequence-alignment/sequence-alignment.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

char token[TOKEN_SIZE];
int globalTaxa, globalCharacters;
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
  labels = malloc(globalTaxa * sizeof(char *));
  labels[0] = malloc(globalTaxa * LABEL_SIZE * sizeof(char));
  for (int i = 1; i < globalTaxa; i++)
    labels[i] = *labels + (i * LABEL_SIZE);
  alignment = newAlignment(globalTaxa, globalCharacters, 8, labels);
}

// Transforms numbers read from input to current sequence
void addNumbersToSequence() {
  for (int i = 0; token[i]; i++) {
    int charValue = token[i] - '0';
    if (charValue < 0 || charValue >= alignment->states)
      printError("Char values must be between 0-%d. Found %d\n",
                 alignment->states - 1, charValue);

    int index = character / (8 * sizeof(stateAllowedMask_t));
    int shiftAmount = character % (8 * sizeof(stateAllowedMask_t));
    alignment->sequenceMasks[taxon][charValue][index] |= 1 << shiftAmount;

    character++;
  }
}

// Adds a missing data to current sequence
void addMissingData() {
  int index = character / (8 * sizeof(stateAllowedMask_t));
  int shiftAmount = character % (8 * sizeof(stateAllowedMask_t));
  for (int i = 0; i < alignment->states; i++) {
    alignment->sequenceMasks[taxon][i][index] |= 1 << shiftAmount;
  }
  character++;
}

// Adds a charset to current sequence
void addMultistateChar() {
  for (int i = 0; token[i]; i++) {
    int charValue = token[i] - '0';
    if (charValue < 0 || charValue >= alignment->states)
      printError("Char values must be between 0-%d. Found %d\n",
                 alignment->states - 1, charValue);

    stateAllowedMask_t *sequence = alignment->sequenceMasks[taxon][charValue];
    int index = character / (8 * sizeof(stateAllowedMask_t));
    int shiftAmount = character % (8 * sizeof(stateAllowedMask_t));
    sequence[index] |= 1 << shiftAmount;
  }
  character++;
}

// Check if number of parsed taxa corresponds with assigned taxa
void checkNumberOfTaxa() {
  if (taxon != alignment->taxa)
    printError(
        "Wrong number of taxa in file: expected %d but alignment has %d\n",
        alignment->taxa, taxon);
}

// Check if number of parsed characters in taxon corresponds with assigned
// amount
void checkNumberOfCharacters() {
  if (character != alignment->characters)
    printError("Wrong number of characters in taxon %d: expected %d but "
               "sequence has %d\n",
               taxon, alignment->characters, character);
}
