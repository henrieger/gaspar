#ifndef __BOOTSTRAP_H__

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

#define ANSWER_SIZE 30

// Perform bootstrap analysis by the giving method and number of replicates.
void bootstrap(answer_t *method(alignment_t *, int evalFn(tree_t *)),
               alignment_t *alignment, int evalFn(tree_t *), int replicates);

#endif // !__BOOTSTRAP_H__
