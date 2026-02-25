#include <assert.h>
#include <eval/parsimony.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <tree/tree.h>

int main(int argc, char *argv[]) {
  // Alignment data for this test is taken from the book
  // Inferring Phylogenies (Felsenstein, 2004)
  // Alignment:
  // Alpha    100110
  // Beta     001000
  // Gamma    110000
  // Delta    110111
  // Epsilon  001110

  const uint64_t taxa = 5;
  const uint64_t characters =
      64; // Artifically augment the size to test effects of big arrays
  const uint64_t states = 2;

  char *labels[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon"};
  alignment_t *alignment = newAlignment(taxa, characters, states, labels);

  for (int i = 0; i < allowedArraySize(characters); i++) {
    // Alpha
    alignment->sequenceMasks[0][0][i] = 0xe6;
    alignment->sequenceMasks[0][1][i] = 0x19;

    // Beta
    alignment->sequenceMasks[1][0][i] = 0xfb;
    alignment->sequenceMasks[1][1][i] = 0x04;

    // Gamma
    alignment->sequenceMasks[2][0][i] = 0xfc;
    alignment->sequenceMasks[2][1][i] = 0x03;

    // Delta
    alignment->sequenceMasks[3][0][i] = 0xc4;
    alignment->sequenceMasks[3][1][i] = 0x3b;

    // Epsilon
    alignment->sequenceMasks[4][0][i] = 0xe3;
    alignment->sequenceMasks[4][1][i] = 0x1c;
  }
  printAlignment(alignment);

  resetParsimonyCalls();
  assert(getParsimonyCalls() == 0);

  tree_t *tree = newTree(alignment);
  int32_t *oldTreeParent = tree->parent;
  int32_t *oldTreeLeft = tree->left;
  int32_t *oldTreeRight = tree->right;

  // Create the structure of a tree with score 8
  // (Alpha,((Delta,Gamma),(Beta,Epsilon)))
  int32_t tree8Parent[] = {-1, 0, 1, 1, 0, 3, 2, 2, 3};
  int32_t tree8Left[] = {4, 2, 7, 5, -1, -1, -1, -1, -1};
  int32_t tree8Right[] = {1, 3, 6, 8, -1, -1, -1, -1, -1};
  tree->parent = tree8Parent;
  tree->left = tree8Left;
  tree->right = tree8Right;

  // Test localParsimony for two internal simulated nodes
  for (int i = 0; i < allowedArraySize(characters); i++) {
    // (Delta,Gamma)
    tree->internalSequences[2][0][i] = 0xfc;
    tree->internalSequences[2][1][i] = 0x3b;
    // (Beta, Epsilon)
    tree->internalSequences[3][0][i] = 0xfb;
    tree->internalSequences[3][1][i] = 0x1c;
  }
  double result = localParsimony(tree, 1);
  assert(result == 3 * allowedArraySize(characters));

  // Test localParsimony for two of the leaves (Delta, Gamma)
  result = localParsimony(tree, 2);
  assert(result == 3 * allowedArraySize(characters));

  // Test localParsimony for the other two leaves (Beta, Epsilon)
  result = localParsimony(tree, 3);
  assert(result == 2 * allowedArraySize(characters));

  // Test parsimony on complete tree
  result = fitchParsimony(tree, NULL);
  assert(result == 8 * allowedArraySize(characters));

  // Switch some nodes so that the parsimony score is now 9
  // (Alpha,(Delta,(Gamma,(Beta,Epsilon))))
  tree->left[1] = 7;
  tree->right[1] = 2;
  tree->parent[7] = 1;
  tree->left[2] = 6;
  tree->right[2] = 3;
  tree->parent[3] = 2;

  result = fitchParsimony(tree, NULL);
  assert(result == 9 * allowedArraySize(characters));

  tree->parent = oldTreeParent;
  tree->left = oldTreeLeft;
  tree->right = oldTreeRight;
  destroyTree(tree);

  destroyAlignment(alignment);
}
