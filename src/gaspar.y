%{

#include "gaspar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sequence-alignment/sequence-alignment.h"
#include "tree/random.h"
#include "answer/answer.h"
#include "search/branch-and-bound.h"
#include "search/hill-climbing.h"
#include "search/genetic-algorithm.h"
#include "operators/nni.h"
#include "eval/parsimony.h"

%}

//TOKENS
%token MIMETYPE
%token OPEN_BRACKET CLOSE_BRACKET COLON
%token NUMBER IDENT MISSING_DATA
%token TAXA_TOKEN CHAR_TOKEN

%%

file:
  MIMETYPE alignment_sizes { initializeAlignment(); }
  alignment { checkNumberOfTaxa(); }
  commands
;

alignment_sizes:
  taxa characters
  | characters taxa
;

taxa:
  TAXA_TOKEN COLON NUMBER { setAlignmentSize(atoi(token)); }
;

characters:
  CHAR_TOKEN COLON NUMBER { setSequenceSize(atoi(token)); }
;

alignment:
  alignment sequence { checkNumberOfCharacters(); }
  | sequence { checkNumberOfCharacters(); }
;

sequence:
  IDENT
  { strncpy(alignment->labels[taxon], token, TOKEN_SIZE); character = 0; }
  sequence_chars
  { taxon++; }
;

sequence_chars:
  sequence_chars char_seq
  | char_seq
;

char_seq:
  NUMBER { addNumbersToSequence(); }
  | charset
;

charset:
  OPEN_BRACKET NUMBER { addMultistateChar(); } CLOSE_BRACKET
  | MISSING_DATA { addMissingData(); }
;

commands:
;

%%

int main(int argc, char **argv) {
  // Seed for RNG
  srand(time(NULL));

  FILE *fp;
  extern FILE *yyin;

  if (argc == 1)
    fp = stdin;
  else if (argc != 2) {
    printf("Usage: %s <arq>b\n", argv[0]);
    return -1;
  } else {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Usage: %s <arq>\n", argv[0]);
      return -1;
    }
  }

  taxon = 0;

  yyin = fp;
  yyparse();

  if (argc != 1)
    fclose(fp);

#ifdef DEBUG
  printf("Alignment size: %d\nSequence size: %d\n", getAlignmentSize(), getSequenceSize());
# endif

  printAlignment(alignment);

#ifdef DEBUG
  printf("Taxa parsed: %d\nCharacters parsed in last taxon: %d\n", taxon, character);
#endif

  tree_t *tree = randomTree(alignment);
  printf("Tree score: %d\n", fitchParsimony(tree));
  printTree(tree);
  printNewick(tree);
  printf(";\n");
  destroyTree(tree);
  // answer_t *answer = branchAndBoundSearch(alignment, fitch_parsimony);
  // answer_t *answer = hillClimbingSearch(alignment, 3, nni, fitch_parsimony);
  // answer_t *answer = geneticAlgorithmSearch(alignment, 8, 100, randomNNI, fitch_parsimony);
  // printAnswer(answer);
  // destroyAnswer(answer);

  if (alignment)
    destroyAlignment(alignment);

  if (weights)
    destroyCharacterWeights();

  if (labels) {
    free(labels[0]);
    free(labels);
  }
}
