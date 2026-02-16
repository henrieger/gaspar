#include <assert.h>
#include <operators/nni.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <tree/iterator.h>
#include <tree/tree.h>

int main() {
  srand(time(NULL));

  const uint64_t taxa = 4;
  const uint64_t characters = 64;
  const uint64_t states = 2;
  char *labels[] = {"A", "B", "C", "D"};

  alignment_t *alignment = newAlignment(taxa, characters, states, labels);
  tree_t *tree = newTree(alignment);

  int32_t *oldTreeParent = tree->parent;
  int32_t *oldTreeLeft = tree->left;
  int32_t *oldTreeRight = tree->right;

  int32_t treeParent[] = {-1, 0, 1, 0, 1, 2, 2};
  int32_t treeLeft[] = {3, 4, 5, -1, -1, -1, -1};
  int32_t treeRight[] = {1, 2, 6, -1, -1, -1, -1};
  tree->parent = treeParent;
  tree->left = treeLeft;
  tree->right = treeRight;

  // Test if an NNI will work, by performing a tree search and verifying all
  // nodes that should have changed
  nni(tree, 1, 2, 0);
  treeIterator *it = newTreeIterator(tree);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(tree->left[1] == 5);
  assert(tree->left[2] == 4);
  assert(tree->parent[5] == 1);
  assert(tree->parent[4] == 2);

  // Redoing the same process should return the original tree
  nni(tree, 1, 2, 0);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(tree->left[1] == 4);
  assert(tree->left[2] == 5);
  assert(tree->parent[5] == 2);
  assert(tree->parent[4] == 1);

  // Now, try the other join
  nni(tree, 1, 2, 1);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(tree->left[1] == 6);
  assert(tree->left[2] == 5);
  assert(tree->parent[6] == 1);
  assert(tree->parent[5] == 2);

  // Now do some random ones!
  for (int i = 0; i < 100; i++) {
    resetTreeIterator(it);
    randomNNI(tree, NULL);
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

  return 0;
}
