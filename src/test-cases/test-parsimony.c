#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>
#include <eval/parsimony.h>

int main(int argc, char **argv) {
  setSequenceSize(6);
  setAlignmentSize(5);
  createCharacterWeights();
  
  alignment_t alignment = newAlignment();
  alignment_t auxAlignment = newAlignment();

  strncpy(alignment[0].label, "Alpha", LABEL_SIZE);
  alignment[0].charsets[0] = 0b00000010;
  alignment[0].charsets[1] = 0b00000001;
  alignment[0].charsets[2] = 0b00000001;
  alignment[0].charsets[3] = 0b00000010;
  alignment[0].charsets[4] = 0b00000010;
  alignment[0].charsets[5] = 0b00000001;

  strncpy(alignment[1].label, "Beta", LABEL_SIZE);
  alignment[1].charsets[0] = 0b00000001;
  alignment[1].charsets[1] = 0b00000001;
  alignment[1].charsets[2] = 0b00000010;
  alignment[1].charsets[3] = 0b00000001;
  alignment[1].charsets[4] = 0b00000001;
  alignment[1].charsets[5] = 0b00000001;

  strncpy(alignment[2].label, "Gamma", LABEL_SIZE);
  alignment[2].charsets[0] = 0b00000010;
  alignment[2].charsets[1] = 0b00000010;
  alignment[2].charsets[2] = 0b00000001;
  alignment[2].charsets[3] = 0b00000001;
  alignment[2].charsets[4] = 0b00000001;
  alignment[2].charsets[5] = 0b00000001;

  strncpy(alignment[3].label, "Delta", LABEL_SIZE);
  alignment[3].charsets[0] = 0b00000010;
  alignment[3].charsets[1] = 0b00000010;
  alignment[3].charsets[2] = 0b00000001;
  alignment[3].charsets[3] = 0b00000010;
  alignment[3].charsets[4] = 0b00000010;
  alignment[3].charsets[5] = 0b00000010;

  strncpy(alignment[4].label, "Epsilon", LABEL_SIZE);
  alignment[4].charsets[0] = 0b00000001;
  alignment[4].charsets[1] = 0b00000001;
  alignment[4].charsets[2] = 0b00000010;
  alignment[4].charsets[3] = 0b00000010;
  alignment[4].charsets[4] = 0b00000010;
  alignment[4].charsets[5] = 0b00000001;

  tree_t *tree = smallUnrootedTree("Alpha", "Beta", "Gamma");
  tree->info->sequence = &(auxAlignment[0]);
  
  node_t *alpha = searchNodeByName(tree, "Alpha");
  node_t *beta  = searchNodeByName(tree, "Beta");
  node_t *gamma = searchNodeByName(tree, "Gamma");

  if (argc >= 2 && argv[1][0] == '8')
    addBrother(gamma, "Delta");
  else
    addBrother(alpha, "Delta");
  node_t *delta = searchNodeByName(tree, "Delta");
  delta->out->info->sequence = &(auxAlignment[1]);

  addBrother(beta, "Epsilon");
  node_t *epsilon = searchNodeByName(tree, "Epsilon");
  epsilon->out->info->sequence = &(auxAlignment[2]);

  alpha->info->sequence   = copySequence(alignment+0);
  beta->info->sequence    = copySequence(alignment+1);
  gamma->info->sequence   = copySequence(alignment+2);
  delta->info->sequence   = copySequence(alignment+3);
  epsilon->info->sequence = copySequence(alignment+4);

  printf("Parsimony of tree ");
  printTree(tree);
  printf(" : %d\n", fitch_parsimony(tree));

  destroyTree(tree);
  destroyAlignment(alignment);
  destroyCharacterWeights();
}
