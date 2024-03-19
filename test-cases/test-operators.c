#include <tree/tree.h>
#include <operators/nni.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Smallest unrooted tree: ");
  tree_t *tree = smallUnrootedTree("A", "B", "C");
  printTree(tree);
  printf("\n");

  printf("Adding a brother D to A: ");
  addBrother(tree, "D");
  printTree(tree);
  printf("\n");

  printf("Adding a brother E to (D,A): ");
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

  node_t *root1 = searchNodeByName(copy, "B");
  root1 = root1->out->next->next;
  printf("Node chosen as root of NNI: %s\n", root1->info->name);
  nni(root1, 0);
  printTree(copy);
  printf("\n");

  node_t *root2 = searchNodeByName(copy, "A");
  root2 = root2->out->next;
  printf("Node chosen as root of NNI: %s\n", root2->info->name);
  nni(root2, 1);
  printTree(copy);
  printf("\n");

  destroyTree(copy);
  destroyTree(tree);

  return 0;
}
