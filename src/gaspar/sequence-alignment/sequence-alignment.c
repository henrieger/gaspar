#include <gaspar/sequence-alignment/sequence-alignment.h>

#include <gaspar/utils/math.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Amount of bytes needed to store a mask of characters
inline size_t allowedArraySize(uint32_t characters) {
  return ceilDiv(characters, MIN_SEQ_CHUNK_SIZE * 8) * MIN_SEQ_CHUNK_SIZE;
}

// Allocate space for a sequence
stateAllowedMask_t **newSequence(uint32_t characters, uint32_t states) {
  stateAllowedMask_t **sequence = malloc(states * sizeof(stateAllowedMask_t *));
  sequence[0] =
      aligned_alloc(MIN_SEQ_CHUNK_SIZE, states * allowedArraySize(characters));

  for (int i = 0; i < states * allowedArraySize(characters); i++)
    sequence[0][i] = 0;

  for (int i = 1; i < states; i++)
    sequence[i] = sequence[0] + i * allowedArraySize(characters);

  return sequence;
}

// Allocate space for a sequence array
stateAllowedMask_t ***newSequenceArray(uint32_t sequences, uint32_t characters,
                                       uint32_t states) {
  stateAllowedMask_t ***sequenceArray =
      malloc(sequences * sizeof(stateAllowedMask_t **));

  sequenceArray[0] = malloc(sequences * states * sizeof(stateAllowedMask_t *));
  sequenceArray[0][0] = aligned_alloc(
      MIN_SEQ_CHUNK_SIZE, sequences * states * allowedArraySize(characters));
  for (int i = 0; i < sequences * states * allowedArraySize(characters); i++)
    sequenceArray[0][0][i] = 0;
  for (int i = 0; i < sequences; i++) {
    sequenceArray[i] = sequenceArray[0] + states * i;
    for (int j = 0; j < states; j++) {
      sequenceArray[i][j] = sequenceArray[0][0] +
                            states * i * allowedArraySize(characters) +
                            allowedArraySize(characters) * j;
    }
  }

  return sequenceArray;
}

// Allocate space for an aligment
alignment_t *newAlignment(uint32_t taxa, uint32_t characters, uint32_t states,
                          char **labels) {
  alignment_t *a = malloc(sizeof(alignment_t));
  a->taxa = taxa;
  a->characters = characters;
  a->states = states;
  a->sequenceMasks = newSequenceArray(taxa, characters, states);
  a->labels = labels;
  a->weights = malloc(characters * sizeof(double));

  int64_t bytesInMask = ceilDiv(characters, 8);
  a->cumulativeWeights = malloc(bytesInMask * sizeof(double *));
  a->cumulativeWeights[0] = malloc(bytesInMask * 256 * sizeof(double));
  for (int i = 1; i < bytesInMask; i++) {
    a->cumulativeWeights[i] = a->cumulativeWeights[0] + i * 256;
  }
  a->ordered = malloc(characters * sizeof(bool));
  return a;
}

// Calculate accumulated weights for alignment based on all possible byte
// configurations
void calculateCumulativeWeights(alignment_t *alignment) {
  int64_t bytesInMask = alignment->characters / 8;
  for (int i = 0; i < bytesInMask; i++) {
    for (int j = 0; j < 256; j++) {
      alignment->cumulativeWeights[i][j] =
          (alignment->weights[8 * i] * (j & 1) +
           alignment->weights[8 * i + 1] * ((j >> 1) & 1) +
           alignment->weights[8 * i + 2] * ((j >> 2) & 1) +
           alignment->weights[8 * i + 3] * ((j >> 3) & 1) +
           alignment->weights[8 * i + 4] * ((j >> 4) & 1) +
           alignment->weights[8 * i + 5] * ((j >> 5) & 1) +
           alignment->weights[8 * i + 6] * ((j >> 6) & 1) +
           alignment->weights[8 * i + 7] * ((j >> 7) & 1));
    }
  }

  if (alignment->characters % 8 != 0) {
    for (int i = 0; i < alignment->characters - 8 * bytesInMask; i++) {
      for (int j = 0; j < 256; j++) {
        alignment->cumulativeWeights[bytesInMask][j] +=
            alignment->weights[8 * bytesInMask + i] * ((j >> i) & 1);
      }
    }
  }
}

// Copy sequenceSrc to sequenceDst inplace
void copySequence(stateAllowedMask_t **sequenceSrc,
                  stateAllowedMask_t **sequenceDst, uint32_t characters,
                  uint32_t states) {
  memcpy(sequenceDst[0], sequenceSrc[0], states * allowedArraySize(characters));
}

// Copy alignSrc to alignDst inplace. Label strings also point to the same
// addresses
void copyAlignment(alignment_t *alignSrc, alignment_t *alignDst) {
  alignDst->taxa = alignSrc->taxa;
  alignDst->characters = alignSrc->characters;
  alignDst->states = alignSrc->states;
  alignDst->labels = alignSrc->labels;

  for (int i = 0; i < alignDst->taxa; i++) {
    copySequence(alignSrc->sequenceMasks[i], alignDst->sequenceMasks[i],
                 alignDst->characters, alignDst->states);
  }

  memcpy(alignDst->weights, alignSrc->weights,
         alignDst->characters * sizeof(double));
  memcpy(alignDst->ordered, alignSrc->ordered,
         alignDst->characters * sizeof(bool));
}

// Print information about a sequence
void printSequence(stateAllowedMask_t **sequence, uint32_t characters,
                   uint32_t states) {
#ifdef DEBUG
  printf("(%p)\t", sequence);
#endif /*ifdef DEBUG */

  for (int i = 0; i < characters; i++) {
    uint64_t index = i / (8 * sizeof(stateAllowedMask_t));
    uint64_t shiftAmount = i % (8 * sizeof(stateAllowedMask_t));

    uint64_t possibleStates = 0;
    for (int j = 0; j < states; j++) {
      possibleStates += (sequence[j][index] >> shiftAmount) & 1;
    }
    if (possibleStates == states) {
      printf("?");
      continue;
    }

    if (possibleStates == 0) {
      printf("-");
      continue;
    }

    if (possibleStates > 1)
      printf("[");

    for (int state = 0; state < states; state++)
      if ((sequence[state][index] >> shiftAmount) & 1)
        printf("%d", state);

    if (possibleStates > 1)
      printf("]");
  }
  printf(";\n");
}

// Print information about an alignment
void printAlignment(alignment_t *alignment) {
  printf("Taxa: %d\nCharacters: %d\n\n", alignment->taxa,
         alignment->characters);

#ifdef DEBUG
  printf("Alignment address: %p\n", alignment);
  printf("Sequences address: %p\n", alignment->sequenceMasks);
  for (int i = 0; i < alignment->taxa; i++) {
    printf("\tSequence %d address: %p\n", i, (alignment->sequenceMasks[i]));
    for (int j = 0; j < alignment->states; j++) {
      printf("\t\tAllowed %ds in sequence %d: %p\n", j, i,
             alignment->sequenceMasks[i][j]);
    }
  }
#endif /* ifdef DEBUG */

  for (int i = 0; i < alignment->taxa; i++) {
    printf("%s:\t", alignment->labels[i]);
    printSequence(alignment->sequenceMasks[i], alignment->characters,
                  alignment->states);
  }

#ifdef DEBUG
  printf("\nSequences in memory:\n");
  for (int i = 0; i < alignment->taxa; i++) {
    printf("%s:\t", alignment->labels[i]);
    for (int j = 0; j < alignment->states; j++)
      for (int k = 0; k < allowedArraySize(alignment->characters); k++)
        printf("%d %d: %x\t", j, k, alignment->sequenceMasks[i][j][k]);
    printf("\n");
  }
#endif /* ifdef DEBUG */
}

// Print character weights
void printCharacterWeights(alignment_t *alignment) {
  printf("Weights: [ ");
  for (int i = 0; i < alignment->characters; i++)
    printf("%lf ", alignment->weights[i]);
  printf("]\n");
}

// Destroy alignment
void destroyAlignment(alignment_t *alignment) {
  if (!alignment)
    return;

  free(alignment->sequenceMasks[0][0]);
  free(alignment->sequenceMasks[0]);
  free(alignment->sequenceMasks);
  free(alignment->cumulativeWeights[0]);
  free(alignment->cumulativeWeights);
  free(alignment->weights);
  free(alignment->ordered);
  free(alignment);
}

// Destroy sequence
void destroySequence(stateAllowedMask_t **sequence) {
  if (!sequence)
    return;

  free(sequence[0]);
  free(sequence);
}
