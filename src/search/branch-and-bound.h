#ifndef __BRANCH_AND_BOUND_H__
#define __BRANCH_AND_BOUND_H__

#include <sequence-alignment/sequence-alignment.h>
#include <answer/answer.h>

// Performs a branch and bound search with given alignment and eval function
answer_t *branchAndBoundSearch(alignment_t *alignment, int evalFn(tree_t *));

#endif // ! __BRANCH_AND_BOUND_H__
