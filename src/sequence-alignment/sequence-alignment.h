#ifndef __SEQUENCE_ALIGNMENT_H__
#define __SEQUENCE_ALIGNMENT_H__

#include <stdbool.h>
#include <stdint.h>

#define LABEL_SIZE 1025

#define stateAllowedMask_t uint8_t

typedef struct alignment {
  uint32_t taxa, characters, states;
  double *weights;
  bool *ordered;
  stateAllowedMask_t ***sequenceMasks;
  const char **labels;
} alignment_t;

#if AVX2_CHARACTERS == 1
#include <immintrin.h>
#define MIN_SEQ_CHUNK_SIZE sizeof(__m256i_u)
#elif AVX512_CHARACTERS == 1
#include <immintrin.h>
#define MIN_SEQ_CHUNK_SIZE sizeof(__m512i_u)
#else
#define MIN_SEQ_CHUNK_SIZE sizeof(uint64_t)
#endif

// Amount of bytes needed to store a mask of characters
unsigned long allowedArraySize(uint32_t characters);

// Allocate space for a sequence
stateAllowedMask_t **newSequence(uint32_t characters, uint32_t states);

// Allocate space for a sequence array
stateAllowedMask_t ***newSequenceArray(uint32_t sequences, uint32_t characters,
                                       uint32_t states);

// Allocate space for an aligment
alignment_t *newAlignment(uint32_t taxa, uint32_t characters, uint32_t states,
                          const char **labels);

// Copy sequenceSrc to sequenceDst inplace
void copySequence(stateAllowedMask_t **sequenceSrc,
                  stateAllowedMask_t **sequenceDst, uint32_t characters,
                  uint32_t states);

void copyAlignment(alignment_t *alignSrc, alignment_t *alignDst);

// Print information about a sequence
void printSequence(stateAllowedMask_t **sequence, uint32_t characters,
                   uint32_t states);

// Print information about an alignment
void printAlignment(alignment_t *alignment);

// Print character weights
void printCharacterWeights(alignment_t *alignment);

// Destroy alignment
void destroyAlignment(alignment_t *alignment);

// Destroy sequence
void destroySequence(stateAllowedMask_t **sequence);

#endif // !__SEQUENCE_ALIGNMENT_H__
