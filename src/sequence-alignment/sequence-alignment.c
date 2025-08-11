#include "sequence-alignment.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/math.h>

// Amount of bytes needed to store a mask of characters
inline size_t allowedArraySize(uint32_t characters) {
  return ceilDiv(characters, MIN_SEQ_CHUNK_SIZE) * MIN_SEQ_CHUNK_SIZE / 8;
}

// Allocate space for a sequence
stateAllowedMask_t **newSequence(uint32_t characters, uint32_t states) {
  stateAllowedMask_t **sequence = malloc(states * sizeof(stateAllowedMask_t *));
  sequence[0] =
      aligned_alloc(MIN_SEQ_CHUNK_SIZE, states * allowedArraySize(characters));

  for (int i = 1; i < states; i++)
    sequence[i] = sequence[0] + allowedArraySize(characters);

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
                          const char **labels) {
  alignment_t *a = malloc(sizeof(alignment_t));
  a->taxa = taxa;
  a->characters = characters;
  a->states = states;
  a->sequenceMasks = newSequenceArray(taxa, characters, states);
  a->labels = labels;
  a->weights = malloc(characters * sizeof(double));
  a->ordered = malloc(characters * sizeof(bool));
  return a;
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
    unsigned int charMask = i / sizeof(stateAllowedMask_t);
    stateAllowedMask_t positionInCharMask = 1
                                            << (i % sizeof(stateAllowedMask_t));
    unsigned int possibleStates = 0;

    for (int state = 0; state < states; state++)
      possibleStates += ((sequence[state][charMask] & positionInCharMask) ==
                         positionInCharMask);

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
      if ((sequence[state][charMask] & positionInCharMask) ==
          positionInCharMask)
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
    printf("\tSequence %d address: %p\n", i, &(alignment->sequenceMasks[i]));
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
