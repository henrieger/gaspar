#include <assert.h>
#include <sequence-alignment/mask-operations.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>

#define CHARACTERS 1024

void resetMask(stateAllowedMask_t *mask) {
  for (int i = 0; i < allowedArraySize(CHARACTERS); i++) {
    mask[i] = 0;
  }
}

int main(int argc, char *argv[]) {
  stateAllowedMask_t mask1[CHARACTERS], mask2[CHARACTERS], result[CHARACTERS];

  for (int i = 0; i < allowedArraySize(CHARACTERS); i++) {
    mask1[i] = i % 256;
    mask2[i] = 255 - i % 256;
  }

  // test calculateSize
  uint32_t size = calculateSize(CHARACTERS);
  assert(size == 16);

  // test maskUnion
  resetMask(result);
  maskUnion(result, mask1, mask2, size);
  for (int i = 0; i < allowedArraySize(CHARACTERS); i++) {
    assert(result[i] == (mask1[i] | mask2[i]));
  }

  // test maskIntersection
  resetMask(result);
  maskIntersection(result, mask1, mask2, size);
  for (int i = 0; i < allowedArraySize(CHARACTERS); i++) {
    assert(result[i] == (mask1[i] & mask2[i]));
  }

  // test maskNot
  resetMask(result);
  maskNot(result, mask1, size);
  for (int i = 0; i < allowedArraySize(CHARACTERS); i++) {
    assert(result[i] == (stateAllowedMask_t)~mask1[i]);
  }
  resetMask(result);
  maskNot(result, mask2, size);
  for (int i = 0; i < allowedArraySize(CHARACTERS); i++) {
    assert(result[i] == (stateAllowedMask_t)~mask2[i]);
  }
}
