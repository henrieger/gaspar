#ifndef __SEQUENCE_ALIGNMENT_H__
#define __SEQUENCE_ALIGNMENT_H__

#include <stdint.h>

#define LABEL_SIZE 1025
#define CHAR_STATES 8

#define stateAllowedMask_t uint8_t

typedef struct sequence {
  stateAllowedMask_t *stateAllowedMask[CHAR_STATES];
} sequence_t;

typedef struct alignment {
  unsigned int taxa;
  sequence_t *sequences;
  char **labels;
} alignment_t;

extern int sequenceSize;  // Global amount of characters in a sequence
extern int alignmentSize; // Global amount of taxa in the alignment
extern int *weights;      // Array of weights of characters
extern int *
    *cumulativeWeights; // Array of weights of characters summed in bytes

#if AVX2_CHARACTERS == 1
#include <immintrin.h>
#define MIN_SEQ_CHUNK_SIZE sizeof(__m256i_u)
#elif AVX512_CHARACTERS == 1
#include <immintrin.h>
#define MIN_SEQ_CHUNK_SIZE sizeof(__m512i_u)
#else
#define MIN_SEQ_CHUNK_SIZE sizeof(uint64_t)
#endif

// Get the global amount of characters in a sequence
int getSequenceSize();

// Get the global amount of taxa in the alignment
int getAlignmentSize();

// Get weight of character c
int getCharacterWeight(int i);

// Set the value of the global amount of characters in a sequence
void setSequenceSize(int size);

// Set the value of the global amount of taxa in the alignment
void setAlignmentSize(int size);

// Set weight of character c as w
void setCharacterWeight(int i, float w);

// Increment weight of character c by one
void incrementCharacterWeight(int i);

// Size of an allowed states array
unsigned long allowedArraySize();

// Get number of characters as determined by the underlying struct
uint64_t charactersInMemory();

// Allocate space for a new array of allowed states
stateAllowedMask_t *newAllowedStates();

// Allocate space for a sequence
sequence_t *newSequence();

// Allocate space for a sequence array
sequence_t *newSequenceArray(unsigned int taxa);

// Allocate space for an aligment
alignment_t *newAlignment(unsigned int taxa, char **labels);

// Return a pointer to a complete copy of the sequence
sequence_t *copySequence(sequence_t *src);

// Return a pointer to a complete copy of the alignment, pointing to the same
// labels
alignment_t *copyAlignment(alignment_t *src);

// Allocate space for character weights and assign all as 1
void createCharacterWeights();

// Allocate space for character weights summed for each byte
void createCumulativeCharacterWeights();

// Aggregate character weights by byte
void calculateCumulativeWeights();

// Return value of sum of weights given byte and mask value
int getCumulativeWeights(int i, int byteValue);

// Print information about a sequence
void printSequence(sequence_t *sequence);

// Print information about an alignment
void printAlignment(alignment_t *alignment);

// Print character weights
void printCharacterWeights();

// Destroy alignment
void destroyAlignment(alignment_t *alignment);

// Destroy sequence
void destroySequence(sequence_t *sequence);

// Destroy array of weights
void destroyCharacterWeights();

// Reset array of weights with new size
void resetCharacterWeights();

#endif // !__SEQUENCE_ALIGNMENT_H__
