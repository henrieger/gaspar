#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>

uint32_t calculateSize(uint32_t characters);

void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t size);

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t size);

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t size);
