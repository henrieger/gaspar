#include <gaspar/sequence-alignment/sequence-alignment.h>

#include <gaspar/utils/math.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Test allowedArraySize
  assert(allowedArraySize(44) == 8);
  assert(allowedArraySize(64) == 8);
  assert(allowedArraySize(65) == 16);
  assert(allowedArraySize(128) == 16);

#define TAXA 4
  const uint64_t characters = 80;
  const uint64_t states = 8;

  // Test newSequence
  stateAllowedMask_t **sequence = newSequence(characters, states);
  assert(sequence != 0);
  assert(sequence[0] != 0);
  assert((uint64_t)sequence[0] % MIN_SEQ_CHUNK_SIZE == 0);
  for (int i = 0; i < states; i++) {
    assert(sequence[i] == sequence[0] + i * allowedArraySize(characters));
    for (int j = 0; j < allowedArraySize(characters); j++)
      assert(sequence[i][j] == 0);
  }
  destroySequence(sequence);

  // Test newSequenceArray
  stateAllowedMask_t ***sequenceArray =
      newSequenceArray(TAXA, characters, states);
  assert(sequenceArray != NULL);
  assert(sequenceArray[0][0] != NULL);
  assert((uint64_t)sequenceArray[0][0] % MIN_SEQ_CHUNK_SIZE == 0);
  for (int i = 0; i < TAXA; i++) {
    assert(sequenceArray[i] == sequenceArray[0] + i * states);
    for (int j = 0; j < states; j++) {
      assert(sequenceArray[i][j] ==
             sequenceArray[0][0] + (i * states * allowedArraySize(characters) +
                                    j * allowedArraySize(characters)));
      assert((uint64_t)sequenceArray[0][0] % MIN_SEQ_CHUNK_SIZE == 0);
      for (int k = 0; k < allowedArraySize(characters); k++)
        assert(sequenceArray[i][j][k] == 0);
    }
  }
  destroySequence(sequenceArray[0]);
  free(sequenceArray);

  // Test newAlignment
  char *labels[TAXA] = {
      "test_1",
      "test_2",
      "test_3",
      "test_4",
  };
  alignment_t *alignment = newAlignment(TAXA, characters, states, labels);
  for (int i = 0; i < characters; i++) {
    alignment->weights[i] = i + 1;
    alignment->ordered[i] = i % 2;
  }
  assert(alignment != NULL);
  assert(alignment->taxa == TAXA);
  assert(alignment->characters == characters);
  assert(alignment->states == states);
  assert(alignment->labels == labels);
  assert(alignment->weights != NULL);
  assert(alignment->ordered != NULL);
  assert(alignment->sequenceMasks != NULL);
  assert(alignment->cumulativeWeights != NULL);
  assert(alignment->cumulativeWeights[0] != NULL);

  // Test calculateCumulativeWeights
  calculateCumulativeWeights(alignment);
  for (int i = 0; i < ceilDiv(alignment->characters, 8); i++) {
    for (int j = 0; j < 256; j++) {
      assert(alignment->cumulativeWeights[i][j] ==
             ((((8 * i + 1) * ((j >> 0) & 1))) +
              ((8 * i + 2) * ((j >> 1) & 1)) + ((8 * i + 3) * ((j >> 2) & 1)) +
              ((8 * i + 4) * ((j >> 3) & 1)) + ((8 * i + 5) * ((j >> 4) & 1)) +
              ((8 * i + 6) * ((j >> 5) & 1)) + ((8 * i + 7) * ((j >> 6) & 1)) +
              ((8 * i + 8) * ((j >> 7) & 1))));
    }
  }

  // Test copySequence
  stateAllowedMask_t **sequenceCopy = newSequence(characters, states);
  copySequence(alignment->sequenceMasks[0], sequenceCopy, characters, states);
  for (int i = 0; i < states; i++)
    for (int j = 0; j < allowedArraySize(characters); j++)
      assert(alignment->sequenceMasks[0][i][j] == sequenceCopy[i][j]);
  destroySequence(sequenceCopy);

  // Test copyAlignment
  alignment_t *alignmentCopy = newAlignment(TAXA, characters, states, NULL);
  copyAlignment(alignment, alignmentCopy);
  assert(alignment->taxa == alignmentCopy->taxa);
  assert(alignment->characters == alignmentCopy->characters);
  assert(alignment->states == alignmentCopy->states);
  assert(alignment->labels == alignmentCopy->labels);
  for (int i = 0; i < TAXA; i++)
    for (int j = 0; j < states; j++)
      for (int k = 0; k < allowedArraySize(characters); k++)
        assert(alignment->sequenceMasks[i][j][k] ==
               alignmentCopy->sequenceMasks[i][j][k]);
  for (int i = 0; i < characters; i++) {
    assert(alignment->weights[i] == alignmentCopy->weights[i]);
    assert(alignment->ordered[i] == alignmentCopy->ordered[i]);
  }
  destroyAlignment(alignmentCopy);

  // Test printSequence
  // First: all 0s
  for (int i = 0; i < allowedArraySize(characters); i++)
    alignment->sequenceMasks[0][0][i] = 255;
  printSequence(alignment->sequenceMasks[0], characters, states);

  // Second: all 1s
  for (int i = 0; i < allowedArraySize(characters); i++) {
    alignment->sequenceMasks[1][0][i] = 0;
    alignment->sequenceMasks[1][1][i] = 255;
  }
  printSequence(alignment->sequenceMasks[1], characters, states);

  // Third: all ?s
  for (int i = 0; i < states; i++)
    for (int j = 0; j < allowedArraySize(characters); j++)
      alignment->sequenceMasks[2][i][j] = 255;
  printSequence(alignment->sequenceMasks[2], 64, 8);

  // Last: half [012], half [67]
  for (int i = 0; i < states; i++) {
    for (int j = 0; j < allowedArraySize(characters); j++) {
      if (i <= 2 && j < allowedArraySize(characters) / 2)
        alignment->sequenceMasks[3][i][j] = 255;
      else if (i <= 2 && j >= allowedArraySize(characters) / 2)
        alignment->sequenceMasks[3][i][j] = 0;
      else if (i >= 6 && j < allowedArraySize(characters) / 2)
        alignment->sequenceMasks[3][i][j] = 0;
      else if (i >= 6 && j >= allowedArraySize(characters) / 2)
        alignment->sequenceMasks[3][i][j] = 255;
      else
        alignment->sequenceMasks[3][i][j] = 0;
    }
  }
  printSequence(alignment->sequenceMasks[3], characters, states);

  // Test printAlignment
  printAlignment(alignment);

  // Test printCharacterWeights
  printCharacterWeights(alignment);

  destroyAlignment(alignment);
}
