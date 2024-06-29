#include "hybrid.h"

#include "nni.h"
#include "spr.h"
#include <stdlib.h>


// Random NNI or SPR
void hybridOp(tree_t *tree, config_t *config) {
  double prob = (double)rand() / RAND_MAX;
  if (prob < config->hybrid_nniProb)
    randomNNI(tree, config);
  else
    randomSPR(tree, config);
}
