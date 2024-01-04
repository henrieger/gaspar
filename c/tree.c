#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

node_t *newNode() {
  node_t *n = malloc(sizeof(node_t));
  n->next = NULL;
  n->out = NULL;
  return n;
}

info_t *newInfo() {
  info_t *info = malloc(sizeof(info_t));
  return info;
}

// Create a new node and its predecessor. Returns pointer to predecessor.
node_t *nodeWithPredecessor(const char *name) {
  node_t *tip = newNode();
  node_t *ancestor = newNode();

  tip->info = newInfo();
  tip->info->name = name;

  tip->out = ancestor;
  ancestor->out = tip;

  return ancestor;
}

tree_t *smallUnrootedTree(const char *a, const char *b, const char *c) {
  node_t *ancestorA = nodeWithPredecessor(a);
  node_t *ancestorB = nodeWithPredecessor(b);
  node_t *ancestorC = nodeWithPredecessor(c);

  ancestorA->next = ancestorB;
  ancestorB->next = ancestorC;
  ancestorC->next = ancestorA;

  info_t *ancestorInfo = newInfo();
  ancestorA->info = ancestorInfo;
  ancestorB->info = ancestorInfo;
  ancestorC->info = ancestorInfo;

  return ancestorA;
}

uint8_t isLeaf(node_t *node) { return node->next == 0; }

void addChild(node_t *node, const char *name) {
  node_t *oldNext = node->next;
  node->next = nodeWithPredecessor(name);
  node->next->info = node->info;
  node->next->next = oldNext;
}

void addBrother(node_t *node, const char *name) {
  node_t *oldOut = node->out;
  node->out = newNode();
  oldOut->out = newNode();

  node->out->next = nodeWithPredecessor(name);
  node->out->next->next = oldOut->out;
  oldOut->out->next = node->out;

  info_t *newNodeInfo = newInfo();
  node->out->next->info = newNodeInfo;
  node->out->next->next->info = newNodeInfo;
  oldOut->out->next->info = newNodeInfo;

  node->out->out = node;
  oldOut->out->out = oldOut;
}

void deleteInfo(info_t *info) { free(info); }

void deleteNode(node_t *node) { free(node); }

// Delete subtrees recursevely, keeping track of origin of call.
void deleteRecursive(node_t *node) {
  if (!node)
    return;

  if (!isLeaf(node)) {
    node_t *next = node->next;
    while (next != node) {
      deleteRecursive(next->out);
      node_t *oldNext = next;
      next = next->next;
      deleteNode(oldNext);
    }
  }

  deleteInfo(node->info);
  deleteNode(node);
}

void deleteTree(tree_t *tree) {
  if (tree->out)
    deleteRecursive(tree->out);
  deleteRecursive(tree);
}

// Print a node, keeping track of origin of call.
void printNode(node_t *node) {
  if (node->info->name)
    printf("%s", node->info->name);

  if (!isLeaf(node)) {
    printf("(");
    node_t *next = node->next;
    while (next != node) {
      printNode(next->out);
      next = next->next;
      if (next != node)
        printf(",");
    }
    printf(")");
  }
}

void printTree(tree_t *tree) {
  if (tree->out) {
    printf("(");
    printNode(tree->out);
    printf(",");
    printNode(tree);
    printf(");");
  } else {
    printNode(tree);
    printf(";");
  }
}

tree_t *rootTree(node_t *node) {
  node_t *root = newNode();
  node_t *oldOut = node->out;

  root->next = newNode();
  root->next->out = oldOut;
  oldOut->out = root->next;

  root->next->next = newNode();
  root->next->next->out = node;
  node->out = root->next->next;
  root->next->next->next = root;

  info_t *rootInfo = newInfo();
  root->info = rootInfo;
  root->next->info = rootInfo;
  root->next->next->info = rootInfo;

  return root;
}
