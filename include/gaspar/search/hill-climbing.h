#ifndef __HILL_CLIMBING_H__
#define __HILL_CLIMBING_H__

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/tree.h>

// Perform a search using a hill climbing optimization algorithm
answer_t *hillClimbingSearch(alignment_t *alignment, config_t *config);

#endif // !__HILL_CLIMBING_H__
