/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GASPAR_H_INCLUDED
# define YY_YY_GASPAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    MIMETYPE = 258,                /* MIMETYPE  */
    OPEN_BRACKET = 259,            /* OPEN_BRACKET  */
    CLOSE_BRACKET = 260,           /* CLOSE_BRACKET  */
    OPEN_BRACE = 261,              /* OPEN_BRACE  */
    CLOSE_BRACE = 262,             /* CLOSE_BRACE  */
    COLON = 263,                   /* COLON  */
    NUMBER = 264,                  /* NUMBER  */
    IDENT = 265,                   /* IDENT  */
    MISSING_DATA = 266,            /* MISSING_DATA  */
    ANALYSES = 267,                /* ANALYSES  */
    TAXA_TOKEN = 268,              /* TAXA_TOKEN  */
    CHAR_TOKEN = 269,              /* CHAR_TOKEN  */
    SEARCH_METHOD = 270,           /* SEARCH_METHOD  */
    BRANCH_AND_BOUND = 271,        /* BRANCH_AND_BOUND  */
    HILL_CLIMBING = 272,           /* HILL_CLIMBING  */
    GENETIC_ALGORITHM = 273,       /* GENETIC_ALGORITHM  */
    TOKEN_NNI = 274,               /* TOKEN_NNI  */
    TOKEN_SPR = 275,               /* TOKEN_SPR  */
    TOKEN_SUBTREE_SWAP = 276,      /* TOKEN_SUBTREE_SWAP  */
    TOKEN_HYBRID = 277,            /* TOKEN_HYBRID  */
    TOKEN_TBR = 278,               /* TOKEN_TBR  */
    TOKEN_PDG = 279,               /* TOKEN_PDG  */
    EVALUATION = 280,              /* EVALUATION  */
    EWMP = 281,                    /* EWMP  */
    HC_PARAMS = 282,               /* HC_PARAMS  */
    GA_PARAMS = 283,               /* GA_PARAMS  */
    BS_PARAMS = 284,               /* BS_PARAMS  */
    SPR_PARAMS = 285,              /* SPR_PARAMS  */
    HYBRID_PARAMS = 286,           /* HYBRID_PARAMS  */
    MAX_TREES = 287,               /* MAX_TREES  */
    PERCENT = 288,                 /* PERCENT  */
    SEED = 289                     /* SEED  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define MIMETYPE 258
#define OPEN_BRACKET 259
#define CLOSE_BRACKET 260
#define OPEN_BRACE 261
#define CLOSE_BRACE 262
#define COLON 263
#define NUMBER 264
#define IDENT 265
#define MISSING_DATA 266
#define ANALYSES 267
#define TAXA_TOKEN 268
#define CHAR_TOKEN 269
#define SEARCH_METHOD 270
#define BRANCH_AND_BOUND 271
#define HILL_CLIMBING 272
#define GENETIC_ALGORITHM 273
#define TOKEN_NNI 274
#define TOKEN_SPR 275
#define TOKEN_SUBTREE_SWAP 276
#define TOKEN_HYBRID 277
#define TOKEN_TBR 278
#define TOKEN_PDG 279
#define EVALUATION 280
#define EWMP 281
#define HC_PARAMS 282
#define GA_PARAMS 283
#define BS_PARAMS 284
#define SPR_PARAMS 285
#define HYBRID_PARAMS 286
#define MAX_TREES 287
#define PERCENT 288
#define SEED 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GASPAR_H_INCLUDED  */
