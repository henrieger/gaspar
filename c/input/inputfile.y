%{

#include "inputfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sequence-alignment.h"

%}

//TOKENS
%token MIMETYPE
%token OPEN_BRACKET CLOSE_BRACKET COLON
%token NUMBER IDENT MISSING_DATA
%token TAXA_TOKEN CHAR_TOKEN

%%

file:
  MIMETYPE alignment_sizes { alignment = newAlignment(); createCharacterWeights(); } alignment { checkNumberOfTaxa(); } commands
;

alignment_sizes:
  taxa characters | characters taxa
;

taxa:
  TAXA_TOKEN COLON NUMBER { setAlignmentSize(atoi(token)); }
;

characters:
  CHAR_TOKEN COLON NUMBER { setSequenceSize(atoi(token)); }
;

alignment:
  alignment sequence { checkNumberOfCharacters(); taxon++; }
  | sequence { checkNumberOfCharacters(); taxon++; }
;

sequence:
  IDENT
  { strncpy(alignment[taxon].name, token, TOKEN_SIZE); character = 0; }
  sequence_chars
;

sequence_chars:
  sequence_chars char_seq
  | char_seq
;

char_seq:
  NUMBER { convertNumberToSequence(); }
  | charset
;

charset:
  OPEN_BRACKET NUMBER { addCharset(); } CLOSE_BRACKET
  | MISSING_DATA { addMissingData(); }
;

commands:
;

%%

int main(int argc, char **argv) {
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
      printf("Usage: %s <arq>b\n", argv[0]);
      return -1;
    }
  }

  taxon = 0;

  yyin = fp;
  yyparse();

  if (argc != 1)
    fclose(fp);

  printf("Alignment size: %d\nSequence size: %d\n", getAlignmentSize(), getSequenceSize());
  printAlignment(alignment);

  printf("Taxa parsed: %d\nCharacters parsed in last taxon: %d\n", taxon, character);

  if (alignment)
    destroyAlignment(alignment);
}
