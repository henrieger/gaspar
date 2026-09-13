#include <gaspar/search/genetic-algorithm.h>

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/random.h>
#include <gaspar/tree/tree.h>

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

double *generationBest; // Array with the best score in each generation

// Allocate array of generation bests
void createGenerationBests(config_t *config) {
  generationBest = malloc(config->ga_generations * sizeof(double));
  resetGenerationBests(config);
}

// Reset array of generation bests
void resetGenerationBests(config_t *config) {
  for (int i = 0; i < config->ga_generations; i++)
    generationBest[i] = -1;
}

// Destroy array of generation bests
void destroyGenerationBests(config_t *config) { free(generationBest); }

double fitnessFunction(double individualScore, double bestScore, double s) {
  return exp(s * (bestScore - individualScore));
}

double sampleProb() { return (double)rand() / (double)(RAND_MAX); }

// Sample a random tree based on its fitness
tree_t *sampleRandomTree(tree_t *population, double *probabilities,
                         int populationSize) {
  double sample = sampleProb();
  for (int pos = 0; pos < populationSize; pos++) {
    if (sample < probabilities[pos])
      return population + pos;
  }
  return population + (populationSize - 1);
}

// Run a single generation from the genetic algorithm search
void geneticAlgorithmGeneration(config_t *config, tree_t *population,
                                tree_t *newPopulation, double *scores,
                                double *probabilities, answer_t *answer,
                                uint32_t *noChangeGenerations) {
  // Evaluate all individuals
  for (int i = 0; i < config->ga_populationSize; i++) {
    scores[i] = config->evalFn(population + i, config);
  }

  // Find the best individual
  int bestPosition = 0;
  int bestScore = scores[0];
  for (int i = 1; i < config->ga_populationSize; i++) {
    if (scores[i] < bestScore) {
      bestScore = scores[i];
      bestPosition = i;
    }
  }

  // Verify generation cutoff and update best answer
  if (bestScore < getScore(answer)) {
    *noChangeGenerations = 0;
    updateAnswer(answer, population, scores[0]);
  } else
    (*noChangeGenerations)++;

  // Update answer with relevant results
  for (int i = 1; i < config->ga_populationSize; i++) {
    updateAnswer(answer, population + i, scores[i]);
  }

#ifdef DEBUG
  printf("Best tree: ");
  printTree(population + bestPosition);
  printf(";\n");
  printf("\tScore: %d\n", bestScore);
#endif /* ifdef DEBUG */

  // Calculate sum of prefixes of probabilities for all individuals
  probabilities[0] =
      fitnessFunction(scores[0], bestScore, config->ga_selectionStrength);
  for (int i = 1; i < config->ga_populationSize; i++)
    probabilities[i] =
        probabilities[i - 1] +
        fitnessFunction(scores[i], bestScore, config->ga_selectionStrength);
  for (int i = 0; i < config->ga_populationSize; i++)
    probabilities[i] /= probabilities[config->ga_populationSize - 1];

  // Preserve best individual
  copyTree(population + bestPosition, newPopulation);

  // Select other individuals and apply mutations
  for (int i = 1; i < config->ga_populationSize; i++) {
    tree_t *t =
        sampleRandomTree(population, probabilities, config->ga_populationSize);
    copyTree(t, newPopulation + i);
    config->ga_mutationOperator(newPopulation + i, config);
  }
}

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, config_t *config) {
  answer_t *answer = initializeAnswer(config->answer_size, alignment);
  tree_t *population = newTreeArray(config->ga_populationSize, alignment);
  tree_t *newPopulation = newTreeArray(config->ga_populationSize, alignment);
  double *scores = malloc(config->ga_populationSize * sizeof(double));
  double *probabilities = malloc(config->ga_populationSize * sizeof(double));

  // Generate initial population from random trees
  for (int i = 0; i < config->ga_populationSize; i++) {
    randomTree(population + i);
  }

  unsigned int noChangeGenerations = 0;

  for (int i = 0; i < config->ga_generations &&
                  noChangeGenerations < config->ga_generationCuttof;
       i++) {
#ifdef DEBUG
    printf("=== Generation %d ===\n", i + 1);
#endif /* ifdef DEBUG */
    geneticAlgorithmGeneration(config, population, newPopulation, scores,
                               probabilities, answer, &noChangeGenerations);
    // Swap populations
    tree_t *aux = population;
    population = newPopulation;
    newPopulation = aux;

    // Save score in array of best of each generation
    generationBest[i] = scores[0];
  }

  // Calculate scores one last time
  for (int i = 0; i < config->ga_populationSize; i++)
    scores[i] = config->evalFn(population + i, config);

  // Update answer with relevant results one last time
  for (int i = 0; i < config->ga_populationSize; i++)
    updateAnswer(answer, population + i, scores[i]);

  destroyTreeArray(population);
  destroyTreeArray(newPopulation);
  free(scores);
  free(probabilities);

  return answer;
}
