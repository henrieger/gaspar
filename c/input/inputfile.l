%{

#include <stdio.h>
#include <string.h>

#include "inputfile.h"
#include "inputfile.tab.h"

void assignToken(const char *typeForPrint);
int lineNumber = 1;

%} 

line_feed [\n]
blank [\t ]+
ident [a-zA-Z\-_]+
number [0-9]+
missing_data [?]
mimetype "text/x-gaspar"

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

taxa {
  assignToken("taxa");
  return TAXA_TOKEN;
}

characters {
  assignToken("characters");
  return CHAR_TOKEN;
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
  strncpy(token, yytext, TOKEN_SIZE);
#ifdef DEBUG
  printf("%s\t\t# %s\n", typeForPrint, token);
#endif
}
