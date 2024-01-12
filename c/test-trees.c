#include "tree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Smallest unrooted tree: ");
  tree_t *tree = smallUnrootedTree("A", "B", "C");
  printTree(tree);
  printf("\n");

  printf("Adding child D: ");
  addChild(tree, "D");
  printTree(tree);
  printf("\n");

  printf("Adding a brother E to A: ");
  addBrother(tree->out, "E");
  printTree(tree);
  printf("\n");

  node_t *a = searchNodeByName(tree, "A");
  node_t *b = searchNodeByName(tree, "B");
  node_t *c = searchNodeByName(tree, "C");
  node_t *d = searchNodeByName(tree, "D");
  node_t *e = searchNodeByName(tree, "E");

  printf("Nodes: %s, %s, %s, %s, %s\n", a->info->name, b->info->name,
         c->info->name, d->info->name, e->info->name);

  tree_t *copy = copyTree(tree);
  printf("Copied tree: ");
  printTree(copy);
  printf("\n");

  node_t *ancestorAE = a->out->next->next;
  node_t *newTree = prune(ancestorAE);
  printf("Tree after pruning: ");
  printTree(newTree);
  printf("\nPruned subtree: ");
  printTree(ancestorAE);
  printf("\n");

  graft(b->out, ancestorAE);
  printf("Regrafted tree:");
  printTree(newTree);
  printf("\n");

  node_t *copiedB = searchNodeByName(copy, "B");
  printf("Node chosen as root of copy: %s\n", copiedB->info->name);

  printf("Rooted tree: ");
  node_t *rootedTree = rootTree(copiedB);
  printTree(rootedTree);
  printf("\n");

  deleteTree(rootedTree);
  deleteTree(newTree);

  return 0;
}
