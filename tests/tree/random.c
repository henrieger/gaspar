#include <assert.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <tree/iterator.h>
#include <tree/random.h>
#include <tree/tree.h>

int main(int argc, char *argv[]) {
  const uint64_t taxa = 6;
  const uint64_t characters = 5;
  const uint64_t states = 2;

  char *labels[] = {"test_1", "test_2", "test_3", "test_4", "test_5", "test_6"};
  alignment_t *alignment = newAlignment(taxa, characters, states, labels);
  tree_t *tree = newTree(alignment);

  // Test randomTree
  for (int i = 0; i < 5; i++) {
    randomTree(tree);
    treeIterator_t *it = newTreeIterator(tree);
    uint64_t j = 0;
    for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
         j++, node = nextTreeIterator(it))
      ;
    assert(j == treeNodes(tree));
    destroyIterator(it);
  }

  // Test randomNode
  for (int i = 0; i < treeNodes(tree); i++) {
    int32_t node = randomNode(tree);
    assert(node >= 0);
    assert(node < treeNodes(tree));
  }

  // Test randomInternalNode
  for (int i = 0; i < treeNodes(tree); i++) {
    int32_t node = randomInternalNode(tree);
    assert(node >= 0);
    assert(node < firstLeaf(tree));
  }

  destroyTree(tree);
  destroyAlignment(alignment);
  return 0;
}
