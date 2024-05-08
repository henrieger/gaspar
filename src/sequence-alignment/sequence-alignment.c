#include "sequence-alignment.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequenceSize;  // Global amount of characters in a sequence
int alignmentSize; // Global amount of taxa in the alignment
float *weights;    // Array of weights of characters

// Get the global amount of characters in a sequence
inline int getSequenceSize() { return sequenceSize; }

// Get the global amount of taxa in the alignment
inline int getAlignmentSize() { return alignmentSize; }

// Get weight of character c
float getCharacterWeight(int i) {
  if (i >= getSequenceSize() || i < 0)
    return 0;
  return weights[i];
}

// Set the value of the global amount of characters in a sequence
inline void setSequenceSize(int size) { sequenceSize = size; }

// Set the value of the global amount of taxa in the alignment
inline void setAlignmentSize(int size) { alignmentSize = size; }

// Set weight of character c as w
inline void setCharacterWeight(int i, float w) { weights[i] = w; }

// Size of an allowed states array
inline unsigned long allowedArraySize() {
  return (getSequenceSize() + (sizeof(allowed_t *) * CHAR_STATES) - 1) /
         (CHAR_STATES * sizeof(allowed_t *));
}

// Allocate space for a new array of allowed states
allowed_t *newAllowedStates() {
  return calloc(allowedArraySize(), sizeof(allowed_t));
}

// Allocate space for a sequence
sequence_t *newSequence() {
  sequence_t *s = malloc(sizeof(sequence_t));
  for (int i = 0; i < CHAR_STATES; i++)
    s->allowed[i] = newAllowedStates();

  return s;
}

// Allocate space for a sequence array
sequence_t *newSequenceArray(unsigned int taxa) {
  sequence_t *sa = malloc(taxa * sizeof(sequence_t));
  for (int i = 0; i < taxa; i++)
    for (int j = 0; j < CHAR_STATES; j++)
      sa[i].allowed[j] = newAllowedStates();

  return sa;
}

// Allocate space for an aligment
alignment_t *newAlignment(unsigned int taxa, char **labels) {
  alignment_t *a = malloc(sizeof(alignment_t));
  a->taxa = taxa;
  a->sequences = newSequenceArray(taxa);
  a->labels = labels;
  return a;
}

// Return a pointer to a complete copy of the sequence
sequence_t *copySequence(sequence_t *src) {
  sequence_t *copy = newSequence();
  memcpy(copy->allowed, src->allowed, CHAR_STATES * sizeof(allowed_t *));
  for (int i = 0; i < CHAR_STATES; i++) {
    memcpy(&(copy->allowed[i]), &(src->allowed[i]),
           allowedArraySize() * sizeof(allowed_t));
  }
  return copy;
}

// Return a pointer to a complete copy of the alignment, pointing to the same
// labels
alignment_t *copyAlignment(alignment_t *src) {
  alignment_t *copy = newAlignment(src->taxa, src->labels);
  for (int i = 0; i < src->taxa; i++)
    for (int j = 0; j < CHAR_STATES; j++) {
      for (int k = 0; k < allowedArraySize(); k++)
        copy->sequences[i].allowed[j][k] = src->sequences[i].allowed[j][k];
    }
  return copy;
}

// Allocate space for character weights and assign all as 1
void createCharacterWeights() {
  weights = malloc(getSequenceSize() * sizeof(float));
  for (int i = 0; i < getSequenceSize(); i++)
    weights[i] = 1;
}

#define stateInPosition(j)                                                     \
  ((sequence->allowed[j][position] >> i) & ((allowed_t)1))

// Print a single character
void printCharacters(sequence_t *sequence, int position) {
  for (int i = 0; i < 64; i++) {
    int possibleStates = 0;

    for (int j = 0; j < CHAR_STATES; j++)
      possibleStates += stateInPosition(j);

    // printf("Possible states: %d ", possibleStates);

    if (possibleStates == CHAR_STATES) {
      printf("?");
      continue;
    }

    if (possibleStates == 0) {
      printf("-");
      continue;
    }

    if (possibleStates > 1)
      printf("[");

    for (int j = 0; j < CHAR_STATES; j++)
      if (stateInPosition(j))
        printf("%d", j);

    if (possibleStates > 1)
      printf("]");
  }
}

// Print information about a sequence
void printSequence(sequence_t *sequence) {
#ifdef DEBUG
  printf("(%p)\t", sequence);
#endif /*ifdef DEBUG */

  for (int i = 0; i < allowedArraySize(); i++)
    printCharacters(sequence, i);
  printf(";\n");
}

// Print information about an alignment
void printAlignment(alignment_t *alignment) {
  printf("Taxa: %d\nCharacters: %d\n\n", getAlignmentSize(), getSequenceSize());

#ifdef DEBUG
  printf("Alignment address: %p\n", alignment);
  printf("Sequences address: %p\n", alignment->sequences);
  for (int i = 0; i < getAlignmentSize(); i++) {
    printf("\tSequence %d address: %p\n", i,
           &(alignment->sequences[i].allowed));
    for (int j = 0; j < CHAR_STATES; j++) {
      printf("\t\tAllowed %ds in sequence %d: %p\n", j, i,
             alignment->sequences[i].allowed[j]);
    }
  }
#endif /* ifdef DEBUG */

  for (int i = 0; i < getAlignmentSize(); i++) {
    printf("%s:\t", alignment->labels[i]);
    printSequence(&(alignment->sequences[i]));
  }

#ifdef DEBUG
  printf("\nSequences in memory:\n");
  for (int i = 0; i < getAlignmentSize(); i++) {
    printf("%s:\t", alignment->labels[i]);
    for (int j = 0; j < CHAR_STATES; j++)
      for (int k = 0; k < allowedArraySize(); k++)
        printf("%d:0x%016lx\t", j, alignment->sequences[i].allowed[j][k]);
    printf("\n");
  }
#endif /* ifdef DEBUG */
}

// Print character weights
void printCharacterWeights() {
  printf("Weights: [ ");
  for (int i = 0; i < getSequenceSize(); i++)
    printf("%.2f ", weights[i]);
  printf("]\n");
}

// Destroy alignment
void destroyAlignment(alignment_t *alignment) {
  if (!alignment)
    return;

  for (int i = 0; i < alignment->taxa; i++) {
    for (int j = 0; j < CHAR_STATES; j++) {
      free(alignment->sequences[i].allowed[j]);
    }
  }

  free(alignment->sequences);
  free(alignment);
}

// Destroy sequence
void destroySequence(sequence_t *sequence) {
  if (!sequence)
    return;

  for (int i = 0; i < CHAR_STATES; i++) {
    free(sequence->allowed[i]);
  }

  free(sequence);
}

// Destroy array of weights
void destroyCharacterWeights() {
  free(weights);
  weights = NULL;
}

// Reset array of weights with new size
void resetCharacterWeights() {
  if (weights)
    destroyCharacterWeights();
  createCharacterWeights();
}
