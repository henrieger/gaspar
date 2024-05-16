#include "genetic-algorithm.h"

#include <answer/answer.h>
#include <math.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>

// TODO: create proper answer size
#define ANSWER_SIZE 30

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
void geneticAlgorithmGeneration(int evalFn(tree_t *), void op(tree_t *),
                                tree_t **population, tree_t **newPopulation,
                                unsigned int *scores, double *probabilities,
                                int populationSize) {
  // Evaluate all individuals
  for (int i = 0; i < populationSize; i++) {
    scores[i] = evalFn(population[i]);
  }

  // Find the best individual
  int bestPosition = 0;
  int bestScore = scores[0];
  for (int i = 1; i < populationSize; i++) {
    if (scores[i] < bestScore) {
      bestScore = scores[i];
      bestPosition = i;
    }
  }

#ifdef DEBUG
  printf("Best tree: ");
  printTree(population[bestPosition]);
  printNewick(population[bestPosition]);
  printf(";\n");
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
    tree_t *t = sampleRandomTree(population, probabilities, populationSize);
    newPopulation[i] = copyTree(t);
    op(newPopulation[i]);
  }
}

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, int evalFn(tree_t *),
                                 void op(tree_t *), int populationSize,
                                 int generations) {
  answer_t *answer = initializeAnswer(ANSWER_SIZE);
  tree_t **population = malloc(populationSize * sizeof(tree_t *));
  tree_t **newPopulation = malloc(populationSize * sizeof(tree_t *));
  unsigned int *scores = malloc(populationSize * sizeof(unsigned int));
  double *probabilities = malloc(populationSize * sizeof(double));

  // Generate initial population from single random tree
  for (int i = 0; i < populationSize; i++) {
    population[i] = randomTree(alignment);
  }

  for (int i = 0; i < generations; i++) {
#ifdef DEBUG
    printf("=== Generation %d ===\n", i + 1);
#endif /* ifdef DEBUG */
    geneticAlgorithmGeneration(evalFn, op, population, newPopulation, scores,
                               probabilities, populationSize);
    // Swap populations
    tree_t **aux = population;
    population = newPopulation;
    newPopulation = aux;

    // Clear previous population
    for (int j = 0; j < populationSize; j++)
      destroyTree(newPopulation[j]);
  }

  // Calculate scores one last time
  for (int i = 0; i < populationSize; i++)
    scores[i] = evalFn(population[i]);

  // Put all relevant trees in answer
  for (int i = 0; i < populationSize; i++)
    updateAnswer(answer, population[i], scores[i]);

  // Clear all data structures
  for (int i = 0; i < populationSize; i++) {
    destroyTree(population[i]);
  }
  free(population);
  free(newPopulation);
  free(scores);
  free(probabilities);

  return answer;
}
