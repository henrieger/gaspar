#ifndef __SEQUENCE_ALIGNMENT_H__
#define __SEQUENCE_ALIGNMENT_H__

#include <stdint.h>

#define charset_t uint8_t
#define CHARSET_EMPTY 0b00000000
#define CHARSET_FULL  0b11111111
#define LABEL_SIZE 512

typedef struct sequence {
  char *label;
  charset_t *charsets;
} sequence_t;

#define alignment_t sequence_t *

extern int sequenceSize;  // Global amount of characters in a sequence
extern int alignmentSize; // Global amount of taxa in the alignment
extern float *weights;    // Array of weights of characters

// Get the global amount of characters in a sequence
#define getSequenceSize() (sequenceSize)
#define getPaddedSequenceSize() ((sequenceSize+31)&~31)

// Get the global amount of taxa in the alignment
#define getAlignmentSize() (alignmentSize)

// Get weight of character c
#define getCharacterWeight(index) (weights[index])

// Set the value of the global amount of characters in a sequence
void setSequenceSize(int size);

// Set the value of the global amount of taxa in the alignment
void setAlignmentSize(int size);

// Set weight of character c as w
void setCharacterWeight(int i, float w);

// Allocate space for a sequence
sequence_t *newSequence(char *label);

// Return a pointer to a complete copy of the sequence
sequence_t *copySequence(sequence_t *src);

// Allocate space for an aligment
alignment_t newAlignment();

// Allocate space for character weights and assign all as 1
void createCharacterWeights();

// Print information about a sequence
void printSequence(sequence_t *sequence);

// Print information about an alignment
void printAlignment(alignment_t alignment);

// Print character weights
void printCharacterWeights();

// Destroy alignment
void destroyAlignment(alignment_t alignment);

// Destroy sequence
void destroySequence(sequence_t *sequence);

// Destroy array of weights
void destroyCharacterWeights();

// Reset array of weights with new size
void resetCharacterWeights();

#endif // !__SEQUENCE_ALIGNMENT_H__
