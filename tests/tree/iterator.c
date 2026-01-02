#include "sequence-alignment/sequence-alignment.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <tree/iterator.h>
#include <tree/tree.h>

int main(int argc, char *argv[]) {
  const int taxa = 6;
  const int characters = 20;
  const int states = 2;
  char *labels[] = {"test_1", "test_2", "test_3", "test_4"};

  alignment_t *alignment = newAlignment(taxa, characters, states, labels);

  tree_t *tree = newTree(alignment);
  int32_t parent[] = {-1, 0, 1, 1, 2, 0, 2, 3, 3, 4, 4};
  int32_t left[] = {5, 2, 4, 7, 9, -1, -1, -1, -1, -1, -1};
  int32_t right[] = {1, 3, 6, 8, 10, -1, -1, -1, -1, -1, -1};
  memcpy(tree->parent, parent, sizeof parent);
  memcpy(tree->left, left, sizeof left);
  memcpy(tree->right, right, sizeof right);

  // test newSubtreeIterator
  treeIterator *it = newSubtreeIterator(tree, 1);
  assert(it->tree == tree);
  assert(it->root == 1);
  assert(it->next == it->root);
  assert(it->visited != NULL);
  for (int i = 0; i < treeNodes(tree); i++) {
    assert(it->visited[i] == 0);
  }

  // test newTreeIterator
  treeIterator *it2 = newTreeIterator(tree);
  assert(it2->tree == tree);
  assert(it2->root == 0);
  assert(it2->next == it2->root);
  assert(it2->visited != NULL);
  for (int i = 0; i < treeNodes(tree); i++) {
    assert(it->visited[i] == 0);
  }

  // test nextTreeIterator
  uint32_t correctOrder[] = {1, 2, 4, 9, 10, 6, 3, 7, 8};
  int i = 0;
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it), i++) {
    assert(node == correctOrder[i]);
  }
  assert(i == 9);

  int32_t completeCorrectOrder[] = {0, 5, 1, 2, 4, 9, 10, 6, 3, 7, 8};
  i = 0;
  for (int32_t node = nextTreeIterator(it2); node != NULL_EDGE;
       node = nextTreeIterator(it2), i++) {
    assert(node == completeCorrectOrder[i]);
  }
  assert(i == 11);

  // Test resetTreeIterator
  assert(it->next == NULL_EDGE);
  for (int i = 0; i < treeNodes(tree); i++) {
    if (i == 0 || i == 5)
      assert(it->visited[i] == 0);
    else if (isLeaf(it->tree, i))
      assert(it->visited[i] == 1);
    else
      assert(it->visited[i] == 3);
  }
  resetTreeIterator(it);
  assert(it->next == it->root);
  for (int i = 0; i < treeNodes(tree); i++) {
    assert(it->visited[i] == 0);
  }

  destroyIterator(it);
  destroyIterator(it2);
  destroyTree(tree);
  destroyAlignment(alignment);
  return 0;
}
