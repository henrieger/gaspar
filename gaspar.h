#ifndef __GASPAR_H__
#define __GASPAR_H__

#include <stdio.h>
#include "sequence-alignment/sequence-alignment.h"

#define TOKEN_SIZE LABEL_SIZE
#define ERROR_SIZE 256

extern char token[TOKEN_SIZE];
extern int lineNumber;
extern alignment_t alignment;
extern int taxon;
extern int character;

// Lexical analyser
int yylex();

// Prints errors and exits
void yyerror(const char *s);

// Sofisticated error print function
void printError(const char *format, ...);

// Initialize global alignment and weights based on provided dimensions
void initializeAlignment();

// Transforms numbers read from input to current sequence
void addNumbersToSequence();

// Adds a missing data to current sequence
void addMissingData();

// Adds a charset to current sequence
void addCharset();

// Check if number of parsed taxa corresponds with assigned taxa
void checkNumberOfTaxa();

// Check if number of parsed characters in taxon corresponds with assigned amount
void checkNumberOfCharacters();

#endif // !__GASPAR_H__
