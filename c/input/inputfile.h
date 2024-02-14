#ifndef __INPUTFILE_H__
#define __INPUTFILE_H__

#include <stdio.h>
#include "../sequence-alignment.h"

#define TOKEN_SIZE NAMESIZE
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

// Transforms numbers read from input to sequence
void convertNumberToSequence();

// Adds a missing data to the sequence
void addMissingData();

// Adds a charset to the sequence
void addCharset();

// Check if number of parsed taxa corresponds with assigned taxa
void checkNumberOfTaxa();

// Check if number of parsed characters in taxon corresponds with assigned amount
void checkNumberOfCharacters();

#endif // !__INPUTFILE_H__
