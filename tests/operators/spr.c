#include <assert.h>
#include <config.h>
#include <operators/spr.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdlib.h>
#include <time.h>
#include <tree/iterator.h>
#include <tree/tree.h>

int main() {
  srand(time(NULL));

  const uint64_t taxa = 5;
  const uint64_t characters = 64;
  const uint64_t states = 2;

  char *labels[] = {"A", "B", "C", "D", "E"};
  alignment_t *alignment = newAlignment(taxa, characters, states, labels);

  tree_t *tree = newTree(alignment);
  int32_t *oldTreeParent = tree->parent;
  int32_t *oldTreeLeft = tree->left;
  int32_t *oldTreeRight = tree->right;

  // Create the structure of the tree
  // (A,((D,C),(B,E)))
  int32_t treeParent[] = {-1, 0, 1, 1, 0, 3, 2, 2, 3};
  int32_t treeLeft[] = {4, 2, 7, 5, -1, -1, -1, -1, -1};
  int32_t treeRight[] = {1, 3, 6, 8, -1, -1, -1, -1, -1};
  tree->parent = treeParent;
  tree->left = treeLeft;
  tree->right = treeRight;

  // Prune D and graft it on E
  // (A,(C,(B,(D,E))))
  subtreePrune(tree, 2, 7);
  subtreeGraft(tree, 2, 7, 3, 8);
  treeIterator *it = newTreeIterator(tree);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(tree->parent[2] == 3);
  assert(tree->parent[6] == 1);
  assert(tree->parent[8] == 2);
  assert(tree->left[1] == 6);
  assert(tree->right[2] == 8);
  assert(tree->right[3] == 2);

  // Prune D and graft it on B
  // (A,(C,((D,B),E)))
  subtreePrune(tree, 2, 7);
  subtreeGraft(tree, 2, 7, 3, 5);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(tree->parent[5] == 2);
  assert(tree->parent[8] == 3);
  assert(tree->left[3] == 2);
  assert(tree->right[2] == 5);
  assert(tree->right[3] == 8);

  // Prune E, regraft onto B
  // (A,(C,(D,(B,E))))
  subtreePrune(tree, 3, 8);
  subtreeGraft(tree, 3, 8, 2, 5);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(tree->parent[2] == 1);
  assert(tree->parent[3] == 2);
  assert(tree->parent[5] == 3);
  assert(tree->left[3] == 5);
  assert(tree->right[1] == 2);
  assert(tree->right[2] == 3);

  // Now do some random ones!
  config_t config = {.spr_probability = 0.4};
  for (int i = 0; i < 100; i++) {
    resetTreeIterator(it);
    randomSPR(tree, &config);
    for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
         node = nextTreeIterator(it))
      ;
  }
  destroyIterator(it);

  tree->parent = oldTreeParent;
  tree->left = oldTreeLeft;
  tree->right = oldTreeRight;
  destroyTree(tree);
  destroyAlignment(alignment);
}
