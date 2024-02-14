#include "sequence-alignment.h"

#include <stdio.h>
#include <stdlib.h>

int sequenceSize;  // Global amount of characters in a sequence
int alignmentSize; // Global amount of taxa in the alignment
float *weights;      // Array of weights of characters

// Get the global amount of characters in a sequence
inline int getSequenceSize() { return sequenceSize; }

// Get the global amount of taxa in the alignment
inline int getAlignmentSize() { return alignmentSize; }

// Get weight of character c
inline float getCharacterWeight(int i) { return weights[i]; }

// Set the value of the global amount of characters in a sequence
inline void setSequenceSize(int size) { sequenceSize = size; }

// Set the value of the global amount of taxa in the alignment
inline void setAlignmentSize(int size) { alignmentSize = size; }

// Set weight of character c as w
inline void setCharacterWeight(int i, float w) { weights[i] = w; }

// Allocate space for a sequence
sequence_t *newSequence(char *name) {
  charset_t *charsets = malloc(getSequenceSize() * sizeof(charset_t));
  sequence_t *sequence = malloc(sizeof(sequence_t));
  sequence->name = name;
  sequence->charsets = charsets;

  return sequence;
}

// Allocate space for an aligment
alignment_t newAlignment() {
  alignment_t alignment = malloc(getAlignmentSize() * sizeof(sequence_t));   
  alignment->name = malloc(getAlignmentSize() * NAMESIZE);
  alignment->charsets = malloc(getAlignmentSize() * getSequenceSize() * sizeof(charset_t));
  for (int i = 1; i < getAlignmentSize(); i++) {
    alignment[i].name = alignment[0].name+(i*NAMESIZE);
    alignment[i].charsets = alignment[0].charsets+(i*getSequenceSize());
  }
  return alignment;
}

// Allocate space for character weights and assign all as 1
void createCharacterWeights() {
  weights = malloc(getSequenceSize() * sizeof(float));
  for (int i = 0; i < getSequenceSize(); i++)
    weights[i] = 1;
}

// Print a single character
void printCharacter(charset_t character) {
  if (!character) {
    printf("-");
    return;
  }
  
  if (character == 0b11111111) {
    printf("?");
    return;
  }

  int multipleCharacters = character & (character - 1); // Check if not power of 2 (aka multistate)

  if (multipleCharacters)
    printf("[");
  
  for (int i = 0; i < 8*sizeof(charset_t); i++) {
    int mask = 1 << i;
    if (mask & character)
      printf("%d", i);
  }

  if (multipleCharacters)
    printf("]");
}

// Print information about a sequence
void printSequence(sequence_t *sequence) {
  printf("%s: ", sequence->name);
  for (int i = 0; i < getSequenceSize(); i++)
    printCharacter(sequence->charsets[i]);
  printf(";\n");
}

// Print information about an alignment
void printAlignment(alignment_t alignment) {
  printf("%d %d\n", getAlignmentSize(), getSequenceSize());
  for (int i = 0; i < getAlignmentSize(); i++)
    printSequence(alignment+i);
}

// Print character weights
void printCharacterWeights() {
  printf("Weights: [ ");
  for (int i = 0; i < getSequenceSize(); i++)
    printf("%.2f ", weights[i]);
  printf("]\n");
}

// Destroy alignment
void destroyAlignment(alignment_t alignment) {
  free(alignment->name);
  destroySequence(alignment);
}

// Destroy sequence
void destroySequence(sequence_t *sequence) {
  free(sequence->charsets);
  free(sequence);
}

// Destroy array of weights
void destroyCharacterWeights() {
  free(weights);
}

// Reset array of weights with new size
void resetCharacterWeights() {
  destroyCharacterWeights();
  createCharacterWeights();
}
