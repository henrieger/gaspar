#include "bootstrap.h"

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>

// Generate a new set of random weights by bootstrapping.
void bootstrapCharWeights(float *weights) {
  for (int i = 0; i < getSequenceSize(); i++)
    setCharacterWeight(i, 0);
  for (int i = 0; i < getSequenceSize(); i++) {
    int randomPos = rand() % getSequenceSize();
    incrementCharacterWeight(randomPos);
  }
}

// Print the trees generated in the replicate with their respective weights.
void printReplicate(answer_t *answer, double treeWeight, FILE *fp) {
  for (int i = 0; i < getNumberOfTrees(answer); i++) {
    printNewick(answer->trees[i], fp);
    fprintf(fp, "[%lf];\n", treeWeight);
  }
}

// Perform bootstrap analysis by the giving method and number of replicates.
void bootstrap(alignment_t *alignment, config_t *config) {
  FILE *fp = fopen("intree", "w");
  
  answer_t *answer = config->searchMethod(alignment, config);
  double treeWeight = (double)1 / (getNumberOfTrees(answer));
  printReplicate(answer, treeWeight, fp);
  printf("\nOriginal Analysis:\n\n");
  printAnswer(answer, NULL);
  printf("\nGenerating %d bootstrap replicates...\n", config->bs_replicates);

  for (int i = 0; i < config->bs_replicates; i++) {
    printf("- Replicate %d\n", i+1);
    destroyAnswer(answer);
    bootstrapCharWeights(weights);
    answer = config->searchMethod(alignment, config);
    treeWeight = (double)1 / (getNumberOfTrees(answer));
    printReplicate(answer, treeWeight, fp);
  }

  printf("Done. Check file 'intree' for complete analysis.\n");
  destroyAnswer(answer);
  fclose(fp);
}
