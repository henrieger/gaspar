#ifndef __BRANCH_AND_BOUND_H__
#define __BRANCH_AND_BOUND_H__

#include <answer/answer.h>
#include <config.h>
#include <sequence-alignment/sequence-alignment.h>

// Performs a branch and bound search with given alignment and eval function
answer_t *branchAndBoundSearch(alignment_t *alignment, config_t *config);

#endif // ! __BRANCH_AND_BOUND_H__
