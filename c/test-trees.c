#include <stdio.h>
#include "tree.h"

int main(int argc, char *argv[]) {
  tree_t *t = smallUnrootedTree("A", "B", "C");
  printTree(t);
  printf("\n");

  addChild(t, "D");
  printTree(t);
  printf("\n");

  addBrother(t->out, "E");
  printTree(t);
  printf("\n");

  printf("Node chosen as root: %s\n", t->out->info->name);

  node_t *rootedTree = rootTree(t->out);
  printTree(rootedTree);
  printf("\n");

  deleteTree(t);

  return 0;
}
