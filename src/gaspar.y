%{

#include "config.h"
#include "gaspar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sequence-alignment/sequence-alignment.h"
#include "answer/answer.h"
#include "search/branch-and-bound.h"
#include "search/hill-climbing.h"
#include "search/genetic-algorithm.h"
#include "eval/parsimony.h"
#include "tree/tree.h"
#include "tree/random.h"
#include "operators/nni.h"
#include "operators/spr.h"
#include "support/bootstrap.h"

%}

//TOKENS
%token MIMETYPE
%token OPEN_BRACKET CLOSE_BRACKET OPEN_BRACE CLOSE_BRACE COLON
%token NUMBER IDENT MISSING_DATA
%token ANALYSES
%token TAXA_TOKEN CHAR_TOKEN
%token SEARCH_METHOD BRANCH_AND_BOUND HILL_CLIMBING GENETIC_ALGORITHM
%token TOKEN_NNI TOKEN_SPR TOKEN_TBR TOKEN_PDG
%token EVALUATION EWMP
%token HC_PARAMS GA_PARAMS BS_PARAMS
%token MAX_TREES PERCENT

%%

file:
  MIMETYPE alignment_sizes { initializeAlignment(); }
  alignment { checkNumberOfTaxa(); printAlignment(alignment); }
  { setConfigsToDefault(&config); }
  { initializeGlobalAuxSequences(); }
  opt_analyses
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

opt_analyses:
  ANALYSES COLON analyses | { bootstrap(alignment, &config); } ;

analyses:
  analyses analysis
  | analysis
;

analysis:
  IDENT { setName(&config, token); printf("\n===== %s =====\n", token); } OPEN_BRACE 
  options
  CLOSE_BRACE { bootstrap(alignment, &config); setConfigsToDefault(&config); }
;

options:
  options option
  | option
;

option:
  searchMethod
  | evaluation
  | hcParams
  | gaParams
  | bsParams
  | maxTrees
;

searchMethod:
  SEARCH_METHOD method
;

method:
  BRANCH_AND_BOUND { config.searchMethod = branchAndBoundSearch; }
  | HILL_CLIMBING { config.searchMethod = hillClimbingSearch; }
  | GENETIC_ALGORITHM { config.searchMethod = geneticAlgorithmSearch; }
;

evaluation:
  EVALUATION EWMP { config.evalFn = fitchParsimony; }
;

hcParams:
  HC_PARAMS hcOperator hcProbability hcReplicates
;

hcOperator:
  TOKEN_SPR { config.hc_operator = SPR; }
  | TOKEN_NNI { config.hc_operator = NNI; }
;

hcProbability:
  NUMBER PERCENT { config.spr_probability = atof(token) / 100; }
;

hcReplicates:
  NUMBER { config.hc_replicates = atoi(token); }
;

gaParams:
  GA_PARAMS gaMutationOperator gaPopulationSize gaGenerations
;

gaMutationOperator:
  TOKEN_SPR { config.ga_mutationOperator = randomSPR; }
  | TOKEN_NNI { config.ga_mutationOperator = randomNNI; }
;

gaPopulationSize:
  NUMBER { config.ga_populationSize = atoi(token); }
;

gaGenerations:
  NUMBER { config.ga_generations = atoi(token); }
;

bsParams:
  BS_PARAMS NUMBER { config.bs_replicates = atoi(token); }
;

maxTrees:
  MAX_TREES NUMBER { config.answer_size = atoi(token); }
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
  printf("Allowed states size: %ld\n", allowedArraySize());
# endif


#ifdef DEBUG
  printf("Taxa parsed: %d\nCharacters parsed in last taxon: %d\n", taxon, character);
#endif

  destroyGlobalAuxSequences();

  if (alignment)
    destroyAlignment(alignment);

  if (weights)
    destroyCharacterWeights();

  if (labels) {
    free(labels[0]);
    free(labels);
  }

  yylex_destroy();
}
