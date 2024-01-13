#include "tree-traversal.h"
#include "tree.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

traversal_t *newTraversalNode(node_t *node) {
    traversal_t *t = malloc(sizeof(traversal_t));
    t->next = NULL;
    t->info = node->info;
    return t;
}

traversal_t *link(traversal_t *a, traversal_t *b) {
  if (!a)
    return b;
  if (!b)
    return a;

  traversal_t *endA; 
  for(endA = a; endA->next != NULL; endA = endA->next);
  endA->next = b;

  return a;
}

traversal_t *reverseBfs(node_t *node, uint8_t flags) {
  return NULL;
}

traversal_t *bfs(node_t *node, uint8_t flags) {
  if (flags & POSTORDER)
    return reverseBfs(node, flags);
  
  // BFS
  return NULL;
}

traversal_t *traverse(node_t *node, uint8_t flags) {
  if (flags & BREADTH_FIRST)
    return bfs(node, flags);

  if (!node->next)
    return newTraversalNode(node);

  traversal_t *t = NULL;
  for (node_t *n = node->next; n != node; n = n->next) {
    t = link(t, traverse(n, flags));
  }

  if (flags & POSTORDER)
    return link(t, newTraversalNode(node));
  return link(newTraversalNode(node), t);
}

void print_traversal(traversal_t *traversal) {
  for (traversal_t *t; t != NULL; t = t->next) {
    printf("%s", t->info->name);
    if (t->next != NULL)
      printf(" ->");
  }
  printf("\n");
}

void deleteTraversal(traversal_t *traversal) {
  traversal_t *start, *next;
  while(start)
  {
    next = start->next;
    free(start);
    start = next;
  }
}
