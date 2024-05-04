#ifndef __SEQUENCE_ALIGNMENT_H__
#define __SEQUENCE_ALIGNMENT_H__

#include <stdint.h>

#define LABEL_SIZE 512
#define CHAR_STATES 8

#define allowed_t unsigned long

typedef struct sequence {
  allowed_t *allowed[CHAR_STATES];
} sequence_t;

typedef struct alignment {
  unsigned int taxa;
  sequence_t *sequences;
  const char **labels;
} alignment_t;

extern int sequenceSize;  // Global amount of characters in a sequence
extern int alignmentSize; // Global amount of taxa in the alignment
extern float *weights;    // Array of weights of characters

// Get the global amount of characters in a sequence
int getSequenceSize();

// Get the global amount of taxa in the alignment
int getAlignmentSize();

// Get weight of character c
float getCharacterWeight(int i);

// Set the value of the global amount of characters in a sequence
void setSequenceSize(int size);

// Set the value of the global amount of taxa in the alignment
void setAlignmentSize(int size);

// Set weight of character c as w
void setCharacterWeight(int i, float w);

// Size of an allowed states array
unsigned long allowedArraySize();

// Allocate space for a new array of allowed states
allowed_t *newAllowedStates();

// Allocate space for a sequence
sequence_t *newSequence();

// Allocate space for a sequence array
sequence_t *newSequenceArray(unsigned int taxa);

// Allocate space for an aligment
alignment_t *newAlignment(unsigned int taxa, const char **labels);

// Return a pointer to a complete copy of the sequence
sequence_t *copySequence(sequence_t *src);

// Return a pointer to a complete copy of the alignment, pointing to the same
// labels
alignment_t *copyAlignment(alignment_t *src);

// Allocate space for character weights and assign all as 1
void createCharacterWeights();

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
