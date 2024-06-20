#include "genetic-algorithm.h"

#include <answer/answer.h>
#include <config.h>
#include <math.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>

int *generationBest; // Array with the best score in each generation

// Allocate array of generation bests
void createGenerationBests(config_t *config) {
  generationBest = malloc(config->ga_generations * sizeof(int));
  resetGenerationBests(config);
}

// Reset array of generation bests
void resetGenerationBests(config_t *config) {
  for (int i = 0; i < config->ga_generations; i++)
    generationBest[i] = -1;
}

// Destroy array of generation bests
void destroyGenerationBests(config_t *config) { free(generationBest); }

double fitnessFunction(int individualScore, int bestScore) {
  return exp(bestScore - individualScore);
}

double sampleProb() { return (double)rand() / (double)(RAND_MAX); }

// Sample a random tree based on its fitness
tree_t *sampleRandomTree(tree_t **population, double *probabilities,
                         int populationSize) {
  double sample = sampleProb();
  for (int pos = 0; pos < populationSize; pos++) {
    if (sample < probabilities[pos])
      return population[pos];
  }
  return population[populationSize - 1];
}

// Run a single generation from the genetic algorithm search
void geneticAlgorithmGeneration(config_t *config, tree_t **population,
                                tree_t **newPopulation, unsigned int *scores,
                                double *probabilities, answer_t *answer,
                                unsigned int *noChangeGenerations) {
  // Evaluate all individuals
  for (int i = 0; i < config->ga_populationSize; i++) {
    scores[i] = config->evalFn(population[i], config);
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

  // Verify generation cutoff
  if (bestScore < getScore(answer))
    *noChangeGenerations = 0;
  else
    (*noChangeGenerations)++;

  // Update answer with relevant results
  for (int i = 0; i < config->ga_populationSize; i++) {
    updateAnswer(answer, population[i], scores[i]);
  }

#ifdef DEBUG
  printf("Best tree: ");
  printTree(population[bestPosition]);
  printNewick(population[bestPosition], NULL);
  printf(";\n");
  printf("\tScore: %d\n", bestScore);
#endif /* ifdef DEBUG */

  // Calculate sum of prefixes of probabilities for all individuals
  probabilities[0] = fitnessFunction(scores[0], bestScore);
  for (int i = 1; i < config->ga_populationSize; i++)
    probabilities[i] =
        probabilities[i - 1] + fitnessFunction(scores[i], bestScore);
  for (int i = 0; i < config->ga_populationSize; i++)
    probabilities[i] /= probabilities[config->ga_populationSize - 1];

  // Preserve best individual
  newPopulation[0] = copyTree(population[bestPosition]);

  // Select other individuals and apply mutations
  for (int i = 1; i < config->ga_populationSize; i++) {
    tree_t *t =
        sampleRandomTree(population, probabilities, config->ga_populationSize);
    newPopulation[i] = copyTree(t);
    config->ga_mutationOperator(newPopulation[i], config);
  }
}

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, config_t *config) {
  answer_t *answer = initializeAnswer(config->answer_size);
  tree_t **population = malloc(config->ga_populationSize * sizeof(tree_t *));
  tree_t **newPopulation = malloc(config->ga_populationSize * sizeof(tree_t *));
  unsigned int *scores =
      malloc(config->ga_populationSize * sizeof(unsigned int));
  double *probabilities = malloc(config->ga_populationSize * sizeof(double));

  // Generate initial population from random trees
  for (int i = 0; i < config->ga_populationSize; i++) {
    population[i] = randomTree(alignment);
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
    tree_t **aux = population;
    population = newPopulation;
    newPopulation = aux;

    // Clear previous population
    for (int j = 0; j < config->ga_populationSize; j++)
      destroyTree(newPopulation[j]);

    // Save score in array of best of each generation
    generationBest[i] = scores[0];
  }

  // Calculate scores one last time
  for (int i = 0; i < config->ga_populationSize; i++)
    scores[i] = config->evalFn(population[i], config);

  // Update answer with relevant results one last time
  for (int i = 0; i < config->ga_populationSize; i++)
    updateAnswer(answer, population[i], scores[i]);

  // Clear all data structures
  for (int i = 0; i < config->ga_populationSize; i++) {
    destroyTree(population[i]);
  }
  free(population);
  free(newPopulation);
  free(scores);
  free(probabilities);

  return answer;
}
