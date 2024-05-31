#include "sequence-alignment.h"

#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequenceSize;        // Global amount of characters in a sequence
int alignmentSize;       // Global amount of taxa in the alignment
int *weights;            // Array of weights of characters
int **weightsByByte;     // Array of weights of characters summed in bytes
int allowedArraySizeVar; // Global size of allowed states array

#define AVX2_ALIGN 32

// Get the global amount of characters in a sequence
inline int getSequenceSize() { return sequenceSize; }

// Get the global amount of taxa in the alignment
inline int getAlignmentSize() { return alignmentSize; }

// Get weight of character c
inline int getCharacterWeight(int i) { return weights[i]; }

void setAllowedArraySize(int seqSize) {
  allowedArraySizeVar = (seqSize + (sizeof(allowed_t) * CHAR_STATES) - 1) /
                        (CHAR_STATES * sizeof(allowed_t));
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

// Allocate space for a new array of allowed states
allowed_t *newAllowedStates() {
  allowed_t *a =
      aligned_alloc(AVX2_ALIGN, allowedArraySize() * sizeof(allowed_t));
  for (int i = 0; i < allowedArraySize(); i++)
    a[i] = _mm256_setzero_si256();
  return a;
}

// Allocate space for a sequence
sequence_t *newSequence() {
  sequence_t *s = malloc(sizeof(sequence_t));

  s->allowed[0] = aligned_alloc(AVX2_ALIGN, CHAR_STATES * allowedArraySize() *
                                                sizeof(allowed_t));
  for (int i = 0; i < CHAR_STATES * allowedArraySize(); i++)
    s->allowed[0][i] = _mm256_setzero_si256();

  for (int i = 1; i < CHAR_STATES; i++)
    s->allowed[i] = s->allowed[0] + i * allowedArraySize();

  return s;
}

// Allocate space for a sequence array
sequence_t *newSequenceArray(unsigned int taxa) {
  sequence_t *sa = malloc(taxa * sizeof(sequence_t));
  int allowedAbsoluteSize =
      taxa * CHAR_STATES * allowedArraySize() * sizeof(allowed_t);

  sa[0].allowed[0] = aligned_alloc(AVX2_ALIGN, allowedAbsoluteSize);
  for (int i = 0; i < allowedAbsoluteSize / sizeof(allowed_t); i++) {
    sa[0].allowed[0][i] = _mm256_setzero_si256();
  }

  for (int i = 0; i < taxa; i++)
    for (int j = 0; j < CHAR_STATES; j++)
      sa[i].allowed[j] =
          sa[0].allowed[0] + allowedArraySize() * (i * CHAR_STATES + j);

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
  weights = malloc(256 * allowedArraySize() * sizeof(int));
  resetCharacterWeights();
}

// Allocate space for character weights summed for each byte
void createCharacterWeightsByByte() {
  int bytesInSequence = (7 + getSequenceSize() / 8);

  weightsByByte = malloc(bytesInSequence * sizeof(int *));
  weightsByByte[0] = malloc(bytesInSequence * 256 * sizeof(int));
  for (int i = 1; i < bytesInSequence; i++)
    weightsByByte[i] = weightsByByte[0] + 256 * i;
}

// Aggregate character weights by byte
void calculateWeightsByByte() {
  int bytesInSequence = (7 + getSequenceSize()) / 8;
  for (int i = 0; i < bytesInSequence; i++) {
    for (int j = 0; j < 256; j++) {
      weightsByByte[i][j] = 0;
      for (int k = 0; k < 8; k++)
        weightsByByte[i][j] += weights[i * 8 + k] * ((j >> k) & 1);
    }
  }
}

// Return value of sum of weights given byte and mask value
inline int getWeightsByByte(int i, int byteValue) {
  return weightsByByte[i][byteValue];
}

// Print a single character
void printCharacters(sequence_t *sequence, int position) {}

// Print information about a sequence
void printSequence(sequence_t *sequence) {
#ifdef DEBUG
  printf("(%p)\t", sequence);
#endif /*ifdef DEBUG */

#define stateInPosition(charValue)                                             \
  ((sequence->allowed[charValue][i][j] >> k) & 1L)

  int bitsCounted = 0;

  for (int i = 0; i < allowedArraySize(); i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 64 && bitsCounted < getSequenceSize();
           k++, bitsCounted++) {
        long possibleStates = 0;

        for (int charValue = 0; charValue < CHAR_STATES; charValue++)
          possibleStates += stateInPosition(charValue);

        // printf("Possible states: %ld ", possibleStates);

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
    }
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
        for (int l = 0; l < 4; l++)
          printf("%d-%d-%d:0x%016llx\t", j, k, l,
                 alignment->sequences[i].allowed[j][k][l]);
    printf("\n");
  }
#endif /* ifdef DEBUG */
}

// Print character weights
void printCharacterWeights() {
  printf("Weights: [ ");
  for (int i = 0; i < getSequenceSize(); i++)
    printf("%d ", weights[i]);
  printf("]\n");

  printf("Weights by byte: [\n");
  for (int i = 0; i < (7 + getSequenceSize()) / 8; i++) {
    printf("\t%d: [ ", i);
    for (int j = 0; j < 256; j++)
      printf("%d ", weightsByByte[i][j]);
    printf("]\n");
  }
  printf("]\n");
}

// Destroy alignment
void destroyAlignment(alignment_t *alignment) {
  if (!alignment)
    return;

  free(alignment->sequences[0].allowed[0]);
  free(alignment->sequences);
  free(alignment);
}

// Destroy sequence
void destroySequence(sequence_t *sequence) {
  if (!sequence)
    return;

  free(sequence->allowed[0]);
  free(sequence);
}

// Destroy array of weights
void destroyCharacterWeights() { free(weights); }

// Reset array of weights with new size
void resetCharacterWeights() {
  for (int i = 0; i < getSequenceSize(); i++)
    weights[i] = 1;
  for (int i = getSequenceSize(); i < 256 * allowedArraySize(); i++)
    weights[i] = 0;
  calculateWeightsByByte();
}
