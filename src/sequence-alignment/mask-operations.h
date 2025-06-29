#include <sequence-alignment/sequence-alignment.h>

void maskUnion(allowedStateMask_t *result, allowedStateMask_t *mask1,
               allowedStateMask_t *mask2);

void maskIntersection(allowedStateMask_t *result, allowedStateMask_t *mask1,
                      allowedStateMask_t *mask2);

void maskNot(allowedStateMask_t *result, allowedStateMask_t *mask);
