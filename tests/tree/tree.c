#include <assert.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <string.h>
#include <tree/tree.h>

void unbalancedTree(tree_t *tree) {
  tree->left[0] = firstLeaf(tree);
  tree->right[0] = 1;
  tree->parent[0] = NULL_EDGE;

  for (int i = 1; i < firstLeaf(tree) - 1; i++) {
    tree->left[i] = firstLeaf(tree) + i;
    tree->right[i] = i + 1;
    tree->parent[i] = i - 1;
  }

  tree->left[tree->alignment->taxa - 2] =
      firstLeaf(tree) + tree->alignment->taxa - 2;
  tree->right[tree->alignment->taxa - 2] =
      firstLeaf(tree) + tree->alignment->taxa - 1;
  tree->parent[tree->alignment->taxa - 2] = tree->alignment->taxa - 3;

  for (int i = firstLeaf(tree); i < treeNodes(tree) - 1; i++) {
    tree->parent[i] = i - firstLeaf(tree);
  }

  tree->parent[treeNodes(tree) - 1] = treeNodes(tree) - firstLeaf(tree) - 2;
}

void balancedTree(tree_t *tree) {
  tree->parent[0] = NULL_EDGE;
  tree->left[0] = firstLeaf(tree);
  tree->right[0] = 1;

  for (int i = 0; i < treeNodes(tree); i++) {
    tree->left[i] = 2 * i < firstLeaf(tree) ? 2 * i : 2 * i + 1;
    tree->right[i] = 2 * i + 1 < firstLeaf(tree) ? 2 * i + 1 : 2 * i + 2;
  }
  for (int i = 0; i < treeNodes(tree); i++) {
  }
}

int main(int argc, char *argv[]) {
  const uint64_t trees = 5;
  const uint64_t taxa = 6;
  const uint64_t characters = 20;
  const uint64_t states = 2;

  char *labels[6] = {"test_1", "test_2", "test_3",
                     "test_4", "test_5", "test_6"};
  alignment_t *alignment = newAlignment(taxa, characters, states, labels);
  for (int i = 0; i < taxa; i++) {
    for (int j = 0; j < states; j++) {
      for (int k = 0; k < allowedArraySize(characters); k++) {
        alignment->sequenceMasks[i][j][k] = 255 & (255 * j);
      }
    }
  }
  printAlignment(alignment);

  // test newTree
  tree_t *tree = newTree(alignment);
  assert(tree != NULL);
  assert(tree->alignment == alignment);
  assert(tree->parent != NULL);
  assert(tree->left == tree->parent + 2 * taxa - 1);
  assert(tree->right == tree->left + 2 * taxa - 1);
  for (int i = 0; i < 4 * taxa - 2; i++) {
    assert(tree->parent[i] == NULL_EDGE);
  }
  assert(tree->internalSequences != NULL);

  // test treeNodes
  assert(treeNodes(tree) == 2 * taxa - 1);

  // test treeLeaves
  assert(treeLeaves(tree) == taxa);

  // test treeInternalNodes
  assert(treeInternalNodes(tree) == taxa - 1);

  // test firstLeaf
  assert(firstLeaf(tree) == taxa - 1);

  // test isLeaf
  for (int i = 0; i < 2 * taxa - 1; i++) {
    assert(isLeaf(tree, i) == (i >= taxa - 1));
  }

  destroyTree(tree);

  // test newTreeArray
  tree_t *treeArray = newTreeArray(trees, alignment);
  assert(treeArray != NULL);
  for (int i = 0; i < trees; i++) {
    assert(treeArray[i].alignment == alignment);
    assert(treeArray[i].parent == treeArray[0].parent + 3 * i * (2 * taxa - 1));
    assert(treeArray[i].left ==
           treeArray[0].parent + (3 * i + 1) * (2 * taxa - 1));
    assert(treeArray[i].right ==
           treeArray[0].parent + (3 * i + 2) * (2 * taxa - 1));
    assert(treeArray[i].internalSequences != NULL);
  }
  for (int i = 0; i < 3 * trees * treeNodes(&treeArray[0]); i++) {
    assert(treeArray[0].parent[i] == NULL_EDGE);
  }

  // test areEqual
  // t1 == t2
  unbalancedTree(&treeArray[0]);
  unbalancedTree(&treeArray[1]);
  assert(areEqual(&treeArray[0], &treeArray[1]));

  // t1,t2 != t3
  int32_t balancedLeft[] = {5, 2, 4, 7, 9, -1, -1, -1, -1, -1, -1};
  int32_t balancedRight[] = {1, 3, 6, 8, 10, -1, -1, -1, -1, -1, -1};
  int32_t balancedParent[] = {-1, 0, 1, 1, 2, 0, 2, 3, 3, 4, 4};
  treeArray[2].left = balancedLeft;
  treeArray[2].right = balancedRight;
  treeArray[2].parent = balancedParent;
  assert(!areEqual(&treeArray[0], &treeArray[2]));
  assert(!areEqual(&treeArray[1], &treeArray[2]));

  // t3 != t4 (semantically equal, undetected by current algorithm)
  // TODO: improve this comparison algorithm such that t3 == t4
  int32_t otherBalancedLeft[] = {5, 3, 8, 6, 10, -1, -1, -1, -1, -1, -1};
  int32_t otherBalancedRight[] = {1, 2, 7, 4, 9, -1, -1, -1, -1, -1, -1};
  int32_t otherBalancedParent[] = {-1, 0, 1, 1, 3, 0, 3, 2, 2, 6, 6};
  treeArray[3].left = otherBalancedLeft;
  treeArray[3].right = otherBalancedRight;
  treeArray[3].parent = otherBalancedParent;
  assert(!areEqual(&treeArray[2], &treeArray[3]));

  // test searchNodeByLabel
  int32_t successfulSearch = searchNodeByLabel(&treeArray[0], "test_1");
  int32_t failedSearch = searchNodeByLabel(&treeArray[0], "non_existing_label");
  assert(successfulSearch == firstLeaf(&treeArray[0]));
  assert(failedSearch == NULL_EDGE);

  // test smallestTree
  smallestTree(&treeArray[4]);
  int32_t smallestTreeParent[11] = {-1, 0, -1, -1, -1, 0, 1, 1, -1, -1, -1};
  int32_t smallestTreeLeft[11] = {5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  int32_t smallestTreeRight[11] = {1, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  for (int i = 0; i < treeNodes(&treeArray[4]); i++) {
    assert(treeArray[4].parent[i] == smallestTreeParent[i]);
    assert(treeArray[4].left[i] == smallestTreeLeft[i]);
    assert(treeArray[4].right[i] == smallestTreeRight[i]);
  }

  // test printTree
  for (int i = 0; i < trees; i++) {
    printTree(&treeArray[i]);
  }

  // test printNewick
  char tree01Newick[] = "(test_1,(test_2,(test_3,(test_4,(test_5,test_6)))))";
  char tree2Newick[] = "(test_1,(((test_5,test_6),test_2),(test_3,test_4)))";
  char tree3Newick[] = "(test_1,((test_2,(test_6,test_5)),(test_4,test_3)))";
  char tree4Newick[] = "(test_1,(test_2,test_3))";
  char tree0Res[LABEL_SIZE], tree1Res[LABEL_SIZE], tree2Res[LABEL_SIZE],
      tree3Res[LABEL_SIZE], tree4Res[LABEL_SIZE];
  printNewick(&treeArray[0], tree0Res);
  assert(!strcmp(tree0Res, tree01Newick));
  printNewick(&treeArray[1], tree1Res);
  assert(!strcmp(tree1Res, tree01Newick));
  printNewick(&treeArray[2], tree2Res);
  assert(!strcmp(tree2Res, tree2Newick));
  printNewick(&treeArray[3], tree3Res);
  assert(!strcmp(tree3Res, tree3Newick));
  printNewick(&treeArray[4], tree4Res);
  assert(!strcmp(tree4Res, tree4Newick));

  // test copyTree
  assert(!areEqual(&treeArray[0], &treeArray[4]));
  copyTree(&treeArray[0], &treeArray[4]);
  assert(areEqual(&treeArray[0], &treeArray[4]));
  assert(treeArray[0].alignment == treeArray[4].alignment);
  for (int i = 0; i < treeInternalNodes(&treeArray[0]); i++) {
    for (int j = 0; j < states; j++) {
      for (int k = 0; k < allowedArraySize(characters); k++) {
        assert(treeArray[0].internalSequences[i][j][k] ==
               treeArray[4].internalSequences[i][j][k]);
      }
    }
  }

  destroyTreeArray(treeArray);
  destroyAlignment(alignment);
}
