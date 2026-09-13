#ifndef __BRANCH_AND_BOUND_H__
#define __BRANCH_AND_BOUND_H__

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>

// Performs a branch and bound search with given alignment and eval function
answer_t *branchAndBoundSearch(alignment_t *alignment, config_t *config);

#endif // ! __BRANCH_AND_BOUND_H__
