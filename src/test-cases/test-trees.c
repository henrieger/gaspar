#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tree/random.h>
#include <tree/tree.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));

  setSequenceSize(6);
  setAlignmentSize(5);

  static const char alpha[] = "Alpha";
  static const char beta[] = "Beta";
  static const char gamma[] = "Gamma";
  static const char delta[] = "Delta";
  static const char epsilon[] = "Epsilon";

  static const char *labels[5] = {alpha, beta, gamma, delta, epsilon};

  alignment_t *alignment = newAlignment(getAlignmentSize(), labels);

  // Alpha: 100110
  alignment->sequences[0].allowed[0][0] = (allowed_t)0b00100110;
  alignment->sequences[0].allowed[1][0] = (allowed_t)0b00011001;
  alignment->sequences[0].allowed[2][0] = (allowed_t)0b00000000;
  alignment->sequences[0].allowed[3][0] = (allowed_t)0b00000000;
  alignment->sequences[0].allowed[4][0] = (allowed_t)0b00000000;
  alignment->sequences[0].allowed[5][0] = (allowed_t)0b00000000;
  alignment->sequences[0].allowed[6][0] = (allowed_t)0b00000000;
  alignment->sequences[0].allowed[7][0] = (allowed_t)0b00000000;

  // Beta: 001000
  alignment->sequences[1].allowed[0][0] = (allowed_t)0b00111011;
  alignment->sequences[1].allowed[1][0] = (allowed_t)0b00000100;
  alignment->sequences[1].allowed[2][0] = (allowed_t)0b00000000;
  alignment->sequences[1].allowed[3][0] = (allowed_t)0b00000000;
  alignment->sequences[1].allowed[4][0] = (allowed_t)0b00000000;
  alignment->sequences[1].allowed[5][0] = (allowed_t)0b00000000;
  alignment->sequences[1].allowed[6][0] = (allowed_t)0b00000000;
  alignment->sequences[1].allowed[7][0] = (allowed_t)0b00000000;

  // Gamma: 110000
  alignment->sequences[2].allowed[0][0] = (allowed_t)0b00111100;
  alignment->sequences[2].allowed[1][0] = (allowed_t)0b00000011;
  alignment->sequences[2].allowed[2][0] = (allowed_t)0b00000000;
  alignment->sequences[2].allowed[3][0] = (allowed_t)0b00000000;
  alignment->sequences[2].allowed[4][0] = (allowed_t)0b00000000;
  alignment->sequences[2].allowed[5][0] = (allowed_t)0b00000000;
  alignment->sequences[2].allowed[6][0] = (allowed_t)0b00000000;
  alignment->sequences[2].allowed[7][0] = (allowed_t)0b00000000;

  // Delta: 110111
  alignment->sequences[3].allowed[0][0] = (allowed_t)0b00000100;
  alignment->sequences[3].allowed[1][0] = (allowed_t)0b00111011;
  alignment->sequences[3].allowed[2][0] = (allowed_t)0b00000000;
  alignment->sequences[3].allowed[3][0] = (allowed_t)0b00000000;
  alignment->sequences[3].allowed[4][0] = (allowed_t)0b00000000;
  alignment->sequences[3].allowed[5][0] = (allowed_t)0b00000000;
  alignment->sequences[3].allowed[6][0] = (allowed_t)0b00000000;
  alignment->sequences[3].allowed[7][0] = (allowed_t)0b00000000;

  // Epsilon: 001110
  alignment->sequences[4].allowed[0][0] = (allowed_t)0b00100011;
  alignment->sequences[4].allowed[1][0] = (allowed_t)0b00011100;
  alignment->sequences[4].allowed[2][0] = (allowed_t)0b00000000;
  alignment->sequences[4].allowed[3][0] = (allowed_t)0b00000000;
  alignment->sequences[4].allowed[4][0] = (allowed_t)0b00000000;
  alignment->sequences[4].allowed[5][0] = (allowed_t)0b00000000;
  alignment->sequences[4].allowed[6][0] = (allowed_t)0b00000000;
  alignment->sequences[4].allowed[7][0] = (allowed_t)0b00000000;

  printf("Smallest unrooted tree:\n");
  tree_t *smallTree = smallestTree(alignment);
  printTree(smallTree);
  printNewick(smallTree);
  printf(";\n");

  printf("\nRandom tree:\n");
  tree_t *random = randomTree(alignment);
  printTree(random);
  printNewick(random);
  printf(";\n");

  int nodeSearched = -1;
  nodeSearched = searchNodeByLabel(random, alpha);
  printf("\nLocation of alpha node in random: %d\n", nodeSearched);

  tree_t *copy = copyTree(random);
  printf("\nCopied tree:\n");
  printTree(copy);
  printNewick(copy);
  printf(";\n");

  destroyTree(smallTree);
  int alphaParent = random->nodes[nodeSearched].edge1;
  int oldEdge = random->nodes[alphaParent].edge1;
  changeEdge(random, alphaParent, oldEdge, random->nodes[alphaParent].edge2);
  printf("\nTree after edge changes:\n");
  printTree(random);
  printNewick(random);
  printf(";\n");

  destroyTree(random);
  destroyTree(copy);
  destroyAlignment(alignment);
}
