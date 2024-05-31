#include "bootstrap.h"

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generate a new set of random weights by bootstrapping.
void bootstrapCharWeights() {
  for (int i = 0; i < getSequenceSize(); i++)
    setCharacterWeight(i, 0);
  for (int i = 0; i < getSequenceSize(); i++) {
    int randomPos = rand() % getSequenceSize();
    incrementCharacterWeight(randomPos);
  }
  calculateWeightsByByte();
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
  // Ensure characters begin set to 1
  resetCharacterWeights();

  // Generate name of output file
  char filename[LABEL_SIZE];
  if (strlen(config->name) == 0)
    strcpy(filename, "intree");
  else {
    strncpy(filename, config->name, LABEL_SIZE);
    strcat(filename, ".intree");
  }

  // Open output file
  FILE *fp = fopen(filename, "w");

  // Perform 1 analysis with equal weights
  answer_t *answer = config->searchMethod(alignment, config);
  double treeWeight = (double)1 / (getNumberOfTrees(answer));
  printReplicate(answer, treeWeight, fp);
  printf("\nOriginal Analysis:\n\n");
  printAnswer(answer, NULL);
  printf("\nGenerating %d bootstrap replicates...\n", config->bs_replicates);

  // Generate n replicates with bootstrapped weights
  for (int i = 0; i < config->bs_replicates; i++) {
    printf("- Replicate %d\n", i + 1);
    destroyAnswer(answer);
    bootstrapCharWeights();
    answer = config->searchMethod(alignment, config);
    treeWeight = (double)1 / (getNumberOfTrees(answer));
    printReplicate(answer, treeWeight, fp);
  }

  // Close file and destroy leftover structures
  printf("Done. Check file '%s' for complete analysis.\n", filename);
  destroyAnswer(answer);
  fclose(fp);
}
