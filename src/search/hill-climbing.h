#ifndef __HILL_CLIMBING_H__
#define __HILL_CLIMBING_H__

#include <answer/answer.h>
#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

// Perform a search using a hill climbing optimization algorithm
answer_t *hillClimbingSearch(alignment_t *alignment, config_t *config);

#endif // !__HILL_CLIMBING_H__
