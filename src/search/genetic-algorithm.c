#include "genetic-algorithm.h"

#include <answer/answer.h>
#include <math.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>

double fitnessFunction(int individualScore, int bestScore) {
  return exp(bestScore - individualScore);
}

double sampleProb() { return (double)rand() / (double)(RAND_MAX); }

// Sample a random tree based on its fitness
tree_t *sampleRandomTree(tree_t **population, double *probabilities,
                         int populationSize) {
  double sample = sampleProb();
  int pos;
  for (pos = 0; pos < populationSize; pos++) {
    if (probabilities[pos] >= sample)
      break;
  }
  return population[pos];
}

// Run a single generation from the genetic algorithm search
void geneticAlgorithmGeneration(tree_t **population, tree_t **newPopulation,
                                unsigned int *scores, double *probabilities,
                                int populationSize,
                                void mutationOperator(node_t *),
                                int eval_fn(tree_t *)) {
  // Clear previous population
  for (int i = 0; i < populationSize; i++)
    destroyTree(newPopulation[i]);

  // Find the best individual
  int bestPosition = 0;
  unsigned int bestScore = (unsigned int)-1;
  for (int i = 0; i < populationSize; i++) {
    if (scores[i] < bestScore) {
      bestScore = scores[i];
      bestPosition = i;
    }
  }

#ifdef DEBUG
  printf("Best tree: ");
  printTree(population[bestPosition]);
  printf("\tScore: %d\n", bestScore);
#endif /* ifdef DEBUG */

  // Calculate sum of prefixes of probabilities for all individuals
  probabilities[0] = fitnessFunction(scores[0], bestScore);
  for (int i = 1; i < populationSize; i++)
    probabilities[i] =
        probabilities[i - 1] + fitnessFunction(scores[i], bestScore);

  for (int i = 0; i < populationSize; i++)
    probabilities[i] /= probabilities[populationSize - 1];

  // Preserve best individual
  newPopulation[0] = copyTree(population[bestPosition]);

  // Select other individuals and apply mutations
  for (int i = 1; i < populationSize; i++) {
    tree_t *randomTree =
        sampleRandomTree(population, probabilities, populationSize);
    newPopulation[i] = copyTree(randomTree);
    mutationOperator(newPopulation[i]);
  }

  // Evaluate all new individuals
  for (int i = 0; i < populationSize; i++) {
    scores[i] = eval_fn(newPopulation[i]);
  }

  // Swap populations
  tree_t **aux = population;
  population = newPopulation;
  newPopulation = aux;
}

answer_t *geneticAlgorithmSearch(alignment_t alignment, int populationSize,
                                 int generations,
                                 void mutationOperator(node_t *),
                                 int eval_fn(tree_t *)) {
  answer_t *answer = initializeAnswer(30);
  tree_t **population = malloc(populationSize * sizeof(tree_t *));
  tree_t **newPopulation = calloc(populationSize, sizeof(tree_t *));
  alignment_t auxAlignment = newAlignment();
  unsigned int *scores = malloc(populationSize * sizeof(unsigned int));
  double *probabilities = malloc(populationSize * sizeof(double));

  // Generate initial population from single random tree
  tree_t *randomTree = randomUnrootedBinaryTree(alignment, auxAlignment);
  int randomTreeScore = eval_fn(randomTree);
  for (int i = 0; i < populationSize; i++) {
    population[i] = copyTree(randomTree);
    scores[i] = randomTreeScore;
  }
  destroyTree(randomTree);

  for (int i = 0; i < generations; i++) {
#ifdef DEBUG
    printf("=== Generation %d ===\n", i + 1);
#endif /* ifdef DEBUG */
    geneticAlgorithmGeneration(population, newPopulation, scores, probabilities,
                               populationSize, mutationOperator, eval_fn);
  }

  // Put all relevant trees in answer
  for (int i = 0; i < populationSize; i++)
    updateAnswer(answer, population[i], scores[i]);

  // Clear all data structures
  for (int i = 0; i < populationSize; i++) {
    destroyTree(newPopulation[i]);
    destroyTree(population[i]);
  }
  destroyAlignment(auxAlignment);
  free(population);
  free(newPopulation);
  free(scores);
  free(probabilities);

  return answer;
}
