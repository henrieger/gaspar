#include "sequence-alignment.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequenceSize;        // Global amount of characters in a sequence
int alignmentSize;       // Global amount of taxa in the alignment
int *weights;            // Array of weights of characters
int **cumulativeWeights; // Array of weights of characters summed in bytes
int allowedArraySizeVar; // Global size of allowed states array

#define CEIL_DIV(n, q) (((n) + (q) - 1) / (q))

// Get the global amount of characters in a sequence
inline int getSequenceSize() { return sequenceSize; }

// Get the global amount of taxa in the alignment
inline int getAlignmentSize() { return alignmentSize; }

// Get weight of character c
inline int getCharacterWeight(int i) { return weights[i]; }

// Get size of character state mask in bytes, according to size of struct for
// calculations
void setAllowedArraySize(int seqSize) {
  const int bytesInMask = CEIL_DIV(seqSize, 8);
  const int numberOfChunks = CEIL_DIV(bytesInMask, MIN_SEQ_CHUNK_SIZE);
  allowedArraySizeVar = numberOfChunks * MIN_SEQ_CHUNK_SIZE;
}

// Set the value of the global amount of characters in a sequence
inline void setSequenceSize(int size) {
  sequenceSize = size;
  setAllowedArraySize(size);
}

// Set the value of the global amount of taxa in the alignment
inline void setAlignmentSize(int size) { alignmentSize = size; }

// Set weight of character c as w
inline void setCharacterWeight(int i, float w) { weights[i] = w; }

// Increment weight of character c by one
inline void incrementCharacterWeight(int i) { weights[i]++; }

// Size of an allowed states array
inline unsigned long allowedArraySize() { return allowedArraySizeVar; }

// Allocate space for a new mask of character state
allowedStateMask_t *newAllowedStates() {
  allowedStateMask_t *a = aligned_alloc(MIN_SEQ_CHUNK_SIZE, allowedArraySize());
  for (int i = 0; i < allowedArraySize(); i++)
    a[i] = 0;
  return a;
}

// Allocate space for a sequence
sequence_t *newSequence() {
  sequence_t *s = malloc(sizeof(sequence_t));

  s->allowedStateMask[0] =
      aligned_alloc(MIN_SEQ_CHUNK_SIZE, CHAR_STATES * allowedArraySize());
  for (int i = 0;
       i < CHAR_STATES * allowedArraySize() / sizeof(allowedStateMask_t); i++)
    s->allowedStateMask[0][i] = 0;

  for (int i = 1; i < CHAR_STATES; i++)
    s->allowedStateMask[i] =
        s->allowedStateMask[0] +
        i * allowedArraySize() / sizeof(allowedStateMask_t);

  return s;
}

// Allocate space for a sequence array
sequence_t *newSequenceArray(unsigned int taxa) {
  sequence_t *sa = malloc(taxa * sizeof(sequence_t));
  int allowedAbsoluteSize = taxa * CHAR_STATES * allowedArraySize();

  sa[0].allowedStateMask[0] =
      aligned_alloc(MIN_SEQ_CHUNK_SIZE, allowedAbsoluteSize);
  for (int i = 0; i < allowedAbsoluteSize / sizeof(allowedStateMask_t); i++) {
    sa[0].allowedStateMask[0][i] = 0;
  }

  for (int i = 0; i < taxa; i++)
    for (int j = 0; j < CHAR_STATES; j++)
      sa[i].allowedStateMask[j] = sa[0].allowedStateMask[0] +
                                  allowedArraySize() * (i * CHAR_STATES + j) /
                                      sizeof(allowedStateMask_t);

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
  memcpy(copy->allowedStateMask, src->allowedStateMask,
         CHAR_STATES * sizeof(allowedStateMask_t *));
  for (int i = 0; i < CHAR_STATES; i++) {
    memcpy(&(copy->allowedStateMask[i]), &(src->allowedStateMask[i]),
           allowedArraySize() * sizeof(allowedStateMask_t));
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
        copy->sequences[i].allowedStateMask[j][k] =
            src->sequences[i].allowedStateMask[j][k];
    }
  return copy;
}

// Allocate space for character weights and assign all as 1
void createCharacterWeights() {
  weights = malloc(allowedArraySize() * 8 * sizeof(int));
  resetCharacterWeights();
}

// Allocate space for character weights summed for each byte combination
void createCumulativeCharacterWeights() {
  cumulativeWeights = malloc(allowedArraySize() * 8 * sizeof(int *));
  cumulativeWeights[0] = malloc(allowedArraySize() * 8 * 256 * sizeof(int));
  for (int i = 1; i < allowedArraySize() * 8; i++)
    cumulativeWeights[i] = cumulativeWeights[0] + 256 * i;
}

// Aggregate character weights by byte
void calculateCumulativeWeights() {
  int bytesInSequence = CEIL_DIV(getSequenceSize(), 8);
  for (int i = 0; i < bytesInSequence; i++) {
    for (int j = 0; j < 256; j++) {
      cumulativeWeights[i][j] = 0;
      for (int k = 0; k < 8; k++)
        cumulativeWeights[i][j] += weights[i * 8 + k] * ((j >> k) & 1);
    }
  }
}

// Return value of sum of weights given byte and mask value
inline int getCumulativeWeights(int bytePos, int byteValue) {
  return cumulativeWeights[bytePos][byteValue];
}

// Print a single character
void printCharacters(sequence_t *sequence, int position) {}

// Print information about a sequence
void printSequence(sequence_t *sequence) {
#ifdef DEBUG
  printf("(%p)\t", sequence);
#endif /*ifdef DEBUG */

#define stateInPosition(charValue)                                             \
  ((sequence->allowedStateMask[charValue][i / 8] >> (i % 8)) & 1)

  for (int i = 0; i < getSequenceSize(); i++) {
    int possibleStates = 0;

    for (int charValue = 0; charValue < CHAR_STATES; charValue++)
      possibleStates += stateInPosition(charValue);

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

    for (int charValue = 0; charValue < CHAR_STATES; charValue++)
      if (stateInPosition(charValue))
        printf("%d", charValue);

    if (possibleStates > 1)
      printf("]");
  }
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
           &(alignment->sequences[i].allowedStateMask));
    for (int j = 0; j < CHAR_STATES; j++) {
      printf("\t\tAllowed %ds in sequence %d: %p\n", j, i,
             alignment->sequences[i].allowedStateMask[j]);
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
        printf("%d %d: %x\t", j, k,
               alignment->sequences[i].allowedStateMask[j][k]);
    printf("\n");
  }
#endif /* ifdef DEBUG */
}

// Print character weights
void printCharacterWeights() {
  printf("Weights: [ ");
  for (int i = 0; i < 8 * allowedArraySize(); i++)
    printf("%d ", weights[i]);
  printf("]\n");

  printf("Weights by byte: [\n");
  for (int i = 0; i < CEIL_DIV(getSequenceSize(), 8); i++) {
    printf("\t%d: [ ", i);
    for (int j = 0; j < 256; j++)
      printf("%d ", cumulativeWeights[i][j]);
    printf("]\n");
  }
  printf("]\n");
}

// Destroy alignment
void destroyAlignment(alignment_t *alignment) {
  if (!alignment)
    return;

  free(alignment->sequences[0].allowedStateMask[0]);
  free(alignment->sequences);
  free(alignment);
}

// Destroy sequence
void destroySequence(sequence_t *sequence) {
  if (!sequence)
    return;

  free(sequence->allowedStateMask[0]);
  free(sequence);
}

// Destroy array of weights
void destroyCharacterWeights() {
  free(weights);
  free(cumulativeWeights[0]);
  free(cumulativeWeights);
}

// Reset array of weights with new size
void resetCharacterWeights() {
  for (int i = 0; i < getSequenceSize(); i++)
    weights[i] = 1;
  for (int i = getSequenceSize(); i < 8 * allowedArraySize(); i++)
    weights[i] = 0;
  calculateCumulativeWeights();
}
