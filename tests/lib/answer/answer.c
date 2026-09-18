#include <gaspar/answer/answer.h>

#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/tree.h>

#include <assert.h>
#include <math.h>
#include <stdint.h>

int main() {
  // Tree topolpgies for this test are taken from the book
  // Inferring Phylogenies (Felsenstein, 2004)

  const uint64_t nTrees = 8;
  const uint64_t taxa = 5;
  const uint64_t characters = 6;
  const uint64_t states = 2;
  char *labels[] = {"A", "B", "C", "D", "E"};

  alignment_t *alignment = newAlignment(taxa, characters, states, labels);

  // Initialize a new answer
  answer_t *answer = initializeAnswer(nTrees, alignment);
  assert(answer->numTrees == nTrees);
  assert(answer->currTree == 0);
  assert(answer->trees != NULL);
  assert(answer->score == INFINITY);

  // No trees should be in this answer
  assert(getNumberOfTrees(answer) == 0);

  // (A,(D,(C,(B,E))))
  tree_t *tree = newTree(alignment);
  int32_t treeParent[] = {-1, 0, 1, 2, 0, 3, 2, 1, 3};
  int32_t treeLeft[] = {4, 7, 6, 5, -1, -1, -1, -1, -1};
  int32_t treeRight[] = {1, 2, 3, 8, -1, -1, -1, -1, -1};
  for (int i = 0; i < treeNodes(tree); i++) {
    tree->parent[i] = treeParent[i];
    tree->left[i] = treeLeft[i];
    tree->right[i] = treeRight[i];
  }

  // Simulate insertion of the first tree
  updateAnswer(answer, tree, 9);
  assert(answer->currTree == 1);
  assert(areEqual(tree, answer->trees));

  // Score should be that of the new tree
  assert(getScore(answer) == 9);

  // Inserting another equal tree should NOT increase the amount of trees in the
  // answer
  updateAnswer(answer, tree, 9);
  assert(answer->currTree == 1);

  // Introducing another tree with same score but different topology should
  // insert a new tree in the answer
  // (A,(C,(D,(B,E))))
  tree->parent[7] = 2;
  tree->parent[6] = 1;
  tree->left[1] = 6;
  tree->left[2] = 7;
  updateAnswer(answer, tree, 9);
  assert(answer->currTree == 2);
  assert(areEqual(tree, answer->trees + 1));

  // Putting a new tree with lower score should delete everything
  int32_t tree8Parent[] = {-1, 0, 1, 1, 0, 3, 2, 2, 3};
  int32_t tree8Left[] = {4, 2, 7, 5, -1, -1, -1, -1, -1};
  int32_t tree8Right[] = {1, 3, 6, 8, -1, -1, -1, -1, -1};
  for (int i = 0; i < treeNodes(tree); i++) {
    tree->parent[i] = tree8Parent[i];
    tree->left[i] = tree8Left[i];
    tree->right[i] = tree8Right[i];
  }
  updateAnswer(answer, tree, 8);
  assert(answer->currTree == 1);
  assert(areEqual(tree, answer->trees));

  // Test printAnswer
  char buffer[1024];
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);

  destroyAnswer(answer);
  destroyTree(tree);
  destroyAlignment(alignment);
}
