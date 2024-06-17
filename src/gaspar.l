%{

#include <stdio.h>
#include <string.h>

#include "gaspar.h"
#include "gaspar.tab.h"

void assignToken(const char *typeForPrint);
int lineNumber = 1;

%} 

line_feed [\n]
blank [\t ]+
ident [a-zA-Z_\'][a-zA-Z0-9_\']*
number [0-9]+
missing_data [?\-]
mimetype "text/x-gaspar"

%option nounput
%option noinput

%%

{line_feed} { lineNumber++; }

{blank}

{mimetype} {
  assignToken("mimeType");
  return MIMETYPE;
}

\[ {
  assignToken("openBracket");
  return OPEN_BRACKET;
}

\] {
  assignToken("closeBracket");
  return CLOSE_BRACKET;
}

\: {
  assignToken("colon");
  return COLON;
}

\{ {
  assignToken("openBrace");
  return OPEN_BRACE;
}

\} {
  assignToken("closeBrace");
  return CLOSE_BRACE;
}

\% {
  assignToken("percent");
  return PERCENT;
}

taxa {
  assignToken("taxa");
  return TAXA_TOKEN;
}

characters {
  assignToken("characters");
  return CHAR_TOKEN;
}

analyses {
  assignToken("analyses");
  return ANALYSES;
}

searchMethod {
  assignToken("searchMethod");
  return SEARCH_METHOD;
}

branchAndBound {
  assignToken("branchAndBound");
  return BRANCH_AND_BOUND;
}

hillClimbing {
  assignToken("hillClimbing");
  return HILL_CLIMBING;
}

geneticAlgorithm {
  assignToken("geneticAlgorithm");
  return GENETIC_ALGORITHM;
}

evaluation {
  assignToken("evaluation");
  return EVALUATION;
}

ewmp {
  assignToken("ewmp");
  return EWMP;
}

maxTrees {
  assignToken("maxTrees");
  return MAX_TREES;
}

spr {
  assignToken("spr");
  return TOKEN_SPR;
}

nni {
  assignToken("nni");
  return TOKEN_NNI;
}

tbr {
  assignToken("tbr");
  return TOKEN_TBR;
}

pdg {
  assignToken("pdg");
  return TOKEN_PDG;
}

hcParams {
  assignToken("hcParams");
  return HC_PARAMS;
}

gaParams {
  assignToken("gaParams");
  return GA_PARAMS;
}

bsParams {
  assignToken("bsParams");
  return BS_PARAMS;
}

{number} {
  assignToken("number");
  return NUMBER;
}

{ident} {
  assignToken("ident");
  return IDENT;
}

{missing_data} {
  assignToken("missing_data");
  return MISSING_DATA;
}

%%

void assignToken(const char *typeForPrint) {
  strncpy(token, yytext, TOKEN_SIZE-1);
#ifdef DEBUG
  printf("%s\t\t# %s\n", typeForPrint, token);
#endif
}
