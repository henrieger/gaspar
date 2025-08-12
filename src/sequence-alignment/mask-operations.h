#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>

void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2, uint32_t characters);

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2, uint32_t characters);

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask,
             uint32_t characters);
