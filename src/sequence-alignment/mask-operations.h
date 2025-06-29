#include <sequence-alignment/sequence-alignment.h>

void maskUnion(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
               stateAllowedMask_t *mask2);

void maskIntersection(stateAllowedMask_t *result, stateAllowedMask_t *mask1,
                      stateAllowedMask_t *mask2);

void maskNot(stateAllowedMask_t *result, stateAllowedMask_t *mask);
