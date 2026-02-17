#include "bootstrap.h"
#include "config.h"
#include "eval/parsimony.h"
#include "search/genetic-algorithm.h"

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generate a new set of random weights by bootstrapping.
void bootstrapCharWeights(alignment_t *alignment) {
  for (int i = 0; i < alignment->characters; i++)
    alignment->weights[i] = 0;
  for (int i = 0; i < alignment->characters; i++) {
    int randomPos = rand() % alignment->characters;
    alignment->weights[randomPos]++;
  }
}

// Print the trees generated in the replicate with their respective weights.
void printReplicate(answer_t *answer, double treeWeight, FILE *fp) {
  char newickBuffer[LABEL_SIZE * LABEL_SIZE];
  for (int i = 0; i < getNumberOfTrees(answer); i++) {
    printNewick(answer->trees + i, newickBuffer);
    fprintf(fp, "%s[%lf];\n", newickBuffer, treeWeight);
  }
}

// Print best score of each GA generation
void printGenerationBests(FILE *fp, config_t *config) {
  for (int i = 0; i < config->ga_generations && generationBest[i] > 0; i++)
    fprintf(fp, "%lf\n", generationBest[i]);
}

// Perform bootstrap analysis by the giving method and number of replicates.
void bootstrap(alignment_t *alignment, config_t *config) {
  // Ensure characters begin set to 1
  for (int i = 0; i < alignment->characters; i++) {
    alignment->weights[i] = 1;
  }

  // Generate name of output files
  char treeFilename[LABEL_SIZE], datFilename[LABEL_SIZE];
  if (strlen(config->name) == 0) {
    strcpy(treeFilename, "intree");
    strcpy(datFilename, "dat");
  } else {
    strncpy(treeFilename, config->name, LABEL_SIZE);
    strcat(treeFilename, ".intree");

    strncpy(datFilename, config->name, LABEL_SIZE);
    strcat(datFilename, ".dat");
  }

  // Open output files
  FILE *treeFp = fopen(treeFilename, "w");
  FILE *datFp = fopen(datFilename, "w");

  // Perform 1 analysis with equal weights
  createGenerationBests(config);
  answer_t *answer = config->searchMethod(alignment, config);
  double treeWeight = (double)1 / (getNumberOfTrees(answer));
  printReplicate(answer, treeWeight, treeFp);
  printf("\nOriginal Analysis:\n\n");
  char answerBuffer[LABEL_SIZE * LABEL_SIZE];
  printAnswer(answer, answerBuffer, LABEL_SIZE * LABEL_SIZE);
  printf("%s\n", answerBuffer);
  fprintf(datFp, "%lf\n", getScore(answer));
  printf("\nGenerating %d more bootstrap replicates...\n",
         config->bs_replicates - 1);

  // Output and reset number of parsimony calls
  fprintf(datFp, "%ld\n", getParsimonyCalls());
  resetParsimonyCalls();
  printGenerationBests(datFp, config);
  resetGenerationBests(config);
  fclose(datFp);

  // Generate n-1 replicates with bootstrapped weights
  for (int i = 1; i < config->bs_replicates; i++) {
    printf("- Replicate %d\n", i);
    destroyAnswer(answer);
    bootstrapCharWeights(alignment);
    answer = config->searchMethod(alignment, config);
    treeWeight = (double)1 / (getNumberOfTrees(answer));
    printReplicate(answer, treeWeight, treeFp);
  }

  // Close files and destroy leftover structures
  printf("Done. Check file '%s' for complete analysis.\n", treeFilename);
  destroyAnswer(answer);
  destroyGenerationBests(config);
  fclose(treeFp);
}
