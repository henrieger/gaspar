/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gaspar-parser.y"


#include "functions.h"
#include "gaspar/gaspar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#line 83 "gaspar-parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_GASPAR_PARSER_H_INCLUDED
# define YY_YY_GASPAR_PARSER_H_INCLUDED
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


#endif /* !YY_YY_GASPAR_PARSER_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MIMETYPE = 3,                   /* MIMETYPE  */
  YYSYMBOL_OPEN_BRACKET = 4,               /* OPEN_BRACKET  */
  YYSYMBOL_CLOSE_BRACKET = 5,              /* CLOSE_BRACKET  */
  YYSYMBOL_OPEN_BRACE = 6,                 /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 7,                /* CLOSE_BRACE  */
  YYSYMBOL_COLON = 8,                      /* COLON  */
  YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
  YYSYMBOL_IDENT = 10,                     /* IDENT  */
  YYSYMBOL_MISSING_DATA = 11,              /* MISSING_DATA  */
  YYSYMBOL_ANALYSES = 12,                  /* ANALYSES  */
  YYSYMBOL_TAXA_TOKEN = 13,                /* TAXA_TOKEN  */
  YYSYMBOL_CHAR_TOKEN = 14,                /* CHAR_TOKEN  */
  YYSYMBOL_SEARCH_METHOD = 15,             /* SEARCH_METHOD  */
  YYSYMBOL_BRANCH_AND_BOUND = 16,          /* BRANCH_AND_BOUND  */
  YYSYMBOL_HILL_CLIMBING = 17,             /* HILL_CLIMBING  */
  YYSYMBOL_GENETIC_ALGORITHM = 18,         /* GENETIC_ALGORITHM  */
  YYSYMBOL_TOKEN_NNI = 19,                 /* TOKEN_NNI  */
  YYSYMBOL_TOKEN_SPR = 20,                 /* TOKEN_SPR  */
  YYSYMBOL_TOKEN_SUBTREE_SWAP = 21,        /* TOKEN_SUBTREE_SWAP  */
  YYSYMBOL_TOKEN_HYBRID = 22,              /* TOKEN_HYBRID  */
  YYSYMBOL_TOKEN_TBR = 23,                 /* TOKEN_TBR  */
  YYSYMBOL_TOKEN_PDG = 24,                 /* TOKEN_PDG  */
  YYSYMBOL_EVALUATION = 25,                /* EVALUATION  */
  YYSYMBOL_EWMP = 26,                      /* EWMP  */
  YYSYMBOL_HC_PARAMS = 27,                 /* HC_PARAMS  */
  YYSYMBOL_GA_PARAMS = 28,                 /* GA_PARAMS  */
  YYSYMBOL_BS_PARAMS = 29,                 /* BS_PARAMS  */
  YYSYMBOL_SPR_PARAMS = 30,                /* SPR_PARAMS  */
  YYSYMBOL_HYBRID_PARAMS = 31,             /* HYBRID_PARAMS  */
  YYSYMBOL_MAX_TREES = 32,                 /* MAX_TREES  */
  YYSYMBOL_PERCENT = 33,                   /* PERCENT  */
  YYSYMBOL_SEED = 34,                      /* SEED  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_file = 36,                      /* file  */
  YYSYMBOL_37_1 = 37,                      /* $@1  */
  YYSYMBOL_38_2 = 38,                      /* $@2  */
  YYSYMBOL_39_3 = 39,                      /* $@3  */
  YYSYMBOL_alignment_sizes = 40,           /* alignment_sizes  */
  YYSYMBOL_taxa = 41,                      /* taxa  */
  YYSYMBOL_characters = 42,                /* characters  */
  YYSYMBOL_alignment = 43,                 /* alignment  */
  YYSYMBOL_sequence = 44,                  /* sequence  */
  YYSYMBOL_label = 45,                     /* label  */
  YYSYMBOL_sequence_chars = 46,            /* sequence_chars  */
  YYSYMBOL_char_seq = 47,                  /* char_seq  */
  YYSYMBOL_charset = 48,                   /* charset  */
  YYSYMBOL_49_4 = 49,                      /* $@4  */
  YYSYMBOL_analyses_declaration = 50,      /* analyses_declaration  */
  YYSYMBOL_opt_analyses = 51,              /* opt_analyses  */
  YYSYMBOL_analyses = 52,                  /* analyses  */
  YYSYMBOL_analysis = 53,                  /* analysis  */
  YYSYMBOL_54_5 = 54,                      /* $@5  */
  YYSYMBOL_options = 55,                   /* options  */
  YYSYMBOL_option = 56,                    /* option  */
  YYSYMBOL_searchMethod = 57,              /* searchMethod  */
  YYSYMBOL_method = 58,                    /* method  */
  YYSYMBOL_evaluation = 59,                /* evaluation  */
  YYSYMBOL_hcParams = 60,                  /* hcParams  */
  YYSYMBOL_hcOperator = 61,                /* hcOperator  */
  YYSYMBOL_hcReplicates = 62,              /* hcReplicates  */
  YYSYMBOL_gaParams = 63,                  /* gaParams  */
  YYSYMBOL_gaMutationOperator = 64,        /* gaMutationOperator  */
  YYSYMBOL_gaSelectionStrength = 65,       /* gaSelectionStrength  */
  YYSYMBOL_66_6 = 66,                      /* $@6  */
  YYSYMBOL_gaPopulationSize = 67,          /* gaPopulationSize  */
  YYSYMBOL_gaGenerations = 68,             /* gaGenerations  */
  YYSYMBOL_gaGenerationCuttof = 69,        /* gaGenerationCuttof  */
  YYSYMBOL_bsParams = 70,                  /* bsParams  */
  YYSYMBOL_hybridParams = 71,              /* hybridParams  */
  YYSYMBOL_72_7 = 72,                      /* $@7  */
  YYSYMBOL_maxTrees = 73,                  /* maxTrees  */
  YYSYMBOL_seed = 74                       /* seed  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   66

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  97

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    28,    28,    29,    30,    28,    35,    36,    40,    44,
      48,    49,    53,    59,    60,    64,    65,    69,    70,    74,
      74,    75,    79,    83,    83,    83,    83,    86,    87,    91,
      91,    97,    98,   102,   103,   104,   105,   106,   107,   108,
     112,   116,   117,   118,   122,   126,   130,   131,   132,   136,
     140,   144,   145,   146,   147,   151,   151,   154,   158,   162,
     166,   170,   170,   174,   178
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "MIMETYPE",
  "OPEN_BRACKET", "CLOSE_BRACKET", "OPEN_BRACE", "CLOSE_BRACE", "COLON",
  "NUMBER", "IDENT", "MISSING_DATA", "ANALYSES", "TAXA_TOKEN",
  "CHAR_TOKEN", "SEARCH_METHOD", "BRANCH_AND_BOUND", "HILL_CLIMBING",
  "GENETIC_ALGORITHM", "TOKEN_NNI", "TOKEN_SPR", "TOKEN_SUBTREE_SWAP",
  "TOKEN_HYBRID", "TOKEN_TBR", "TOKEN_PDG", "EVALUATION", "EWMP",
  "HC_PARAMS", "GA_PARAMS", "BS_PARAMS", "SPR_PARAMS", "HYBRID_PARAMS",
  "MAX_TREES", "PERCENT", "SEED", "$accept", "file", "$@1", "$@2", "$@3",
  "alignment_sizes", "taxa", "characters", "alignment", "sequence",
  "label", "sequence_chars", "char_seq", "charset", "$@4",
  "analyses_declaration", "opt_analyses", "analyses", "analysis", "$@5",
  "options", "option", "searchMethod", "method", "evaluation", "hcParams",
  "hcOperator", "hcReplicates", "gaParams", "gaMutationOperator",
  "gaSelectionStrength", "$@6", "gaPopulationSize", "gaGenerations",
  "gaGenerationCuttof", "bsParams", "hybridParams", "$@7", "maxTrees",
  "seed", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-17)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      12,     0,    17,    11,    19,   -17,    25,    18,   -17,    31,
      32,    28,   -17,   -17,   -17,   -17,   -17,   -17,    28,   -17,
      -2,   -17,   -17,    33,   -17,   -17,    -2,   -17,   -17,   -11,
     -17,   -17,    35,    36,   -17,   -17,    34,    39,    37,   -17,
     -17,   -17,   -17,    37,   -17,    42,   -17,     1,    -6,    23,
      15,   -16,    41,    43,    44,    -7,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,    45,   -17,   -17,   -17,   -17,    46,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,    47,    24,    26,   -17,
      49,   -17,   -17,   -17,    51,   -17,   -17
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     0,     0,     1,     0,
       0,     0,     6,     7,     8,     9,    14,    13,     3,    11,
       0,     4,    10,     0,    17,    21,    12,    16,    18,    26,
      19,    15,     0,     0,    25,     5,    24,     0,     0,    64,
      23,    20,    29,    22,    28,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    41,    42,    43,    40,    44,    47,
      46,    48,     0,    52,    51,    53,    54,     0,    60,    61,
      63,    30,    31,    49,    45,    55,     0,     0,     0,    57,
       0,    62,    56,    58,     0,    59,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -17,   -17,   -17,   -17,   -17,   -17,    54,    56,   -17,    48,
     -17,   -17,    38,   -17,   -17,    27,   -17,   -17,     8,   -17,
     -17,    10,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    11,    21,    29,     5,     6,     7,    18,    19,
      20,    26,    27,    28,    37,    34,    35,    43,    44,    45,
      55,    56,    57,    67,    58,    59,    72,    84,    60,    77,
      86,    88,    90,    94,    96,    61,    62,    87,    63,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      81,    32,    23,    73,    74,    75,    76,    24,    48,    25,
      64,    65,    66,     3,     4,     1,    48,     8,    49,     9,
      50,    51,    52,    33,    53,    54,    49,    10,    50,    51,
      52,     3,    53,    54,    69,    70,    71,    16,    17,     4,
      14,    15,    30,    38,    41,    39,    32,    42,    47,    68,
      78,    46,    79,    80,    83,    85,    89,    91,    93,    92,
      95,    13,    12,    40,    31,    82,    22
};

static const yytype_int8 yycheck[] =
{
       7,    12,     4,    19,    20,    21,    22,     9,    15,    11,
      16,    17,    18,    13,    14,     3,    15,     0,    25,     8,
      27,    28,    29,    34,    31,    32,    25,     8,    27,    28,
      29,    13,    31,    32,    19,    20,    21,     9,    10,    14,
       9,     9,     9,     8,     5,     9,    12,    10,     6,    26,
       9,    43,     9,     9,     9,     9,     9,    33,     9,    33,
       9,     7,     6,    36,    26,    55,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    36,    13,    14,    40,    41,    42,     0,     8,
       8,    37,    42,    41,     9,     9,     9,    10,    43,    44,
      45,    38,    44,     4,     9,    11,    46,    47,    48,    39,
       9,    47,    12,    34,    50,    51,    74,    49,     8,     9,
      50,     5,    10,    52,    53,    54,    53,     6,    15,    25,
      27,    28,    29,    31,    32,    55,    56,    57,    59,    60,
      63,    70,    71,    73,    16,    17,    18,    58,    26,    19,
      20,    21,    61,    19,    20,    21,    22,    64,     9,     9,
       9,     7,    56,     9,    62,     9,    65,    72,    66,     9,
      67,    33,    33,     9,    68,     9,    69
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    37,    38,    39,    36,    40,    40,    41,    42,
      43,    43,    44,    45,    45,    46,    46,    47,    47,    49,
      48,    48,    50,    51,    51,    51,    51,    52,    52,    54,
      53,    55,    55,    56,    56,    56,    56,    56,    56,    56,
      57,    58,    58,    58,    59,    60,    61,    61,    61,    62,
      63,    64,    64,    64,    64,    66,    65,    67,    68,    69,
      70,    72,    71,    73,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     0,     7,     2,     2,     3,     3,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     0,
       4,     1,     3,     2,     1,     1,     0,     2,     1,     0,
       5,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     2,     3,     1,     1,     1,     1,
       6,     1,     1,     1,     1,     0,     3,     1,     1,     1,
       2,     0,     4,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 28 "gaspar-parser.y"
                           { initializeAlignment(); }
#line 1318 "gaspar-parser.c"
    break;

  case 3: /* $@2: %empty  */
#line 29 "gaspar-parser.y"
            { checkNumberOfTaxa(); printAlignment(alignment); }
#line 1324 "gaspar-parser.c"
    break;

  case 4: /* $@3: %empty  */
#line 30 "gaspar-parser.y"
  { setConfigsToDefault(&config); }
#line 1330 "gaspar-parser.c"
    break;

  case 8: /* taxa: TAXA_TOKEN COLON NUMBER  */
#line 40 "gaspar-parser.y"
                          { globalTaxa = atoi(token); }
#line 1336 "gaspar-parser.c"
    break;

  case 9: /* characters: CHAR_TOKEN COLON NUMBER  */
#line 44 "gaspar-parser.y"
                          { globalCharacters = atoi(token); }
#line 1342 "gaspar-parser.c"
    break;

  case 10: /* alignment: alignment sequence  */
#line 48 "gaspar-parser.y"
                     { checkNumberOfCharacters(); }
#line 1348 "gaspar-parser.c"
    break;

  case 11: /* alignment: sequence  */
#line 49 "gaspar-parser.y"
             { checkNumberOfCharacters(); }
#line 1354 "gaspar-parser.c"
    break;

  case 12: /* sequence: label sequence_chars  */
#line 55 "gaspar-parser.y"
  { taxon++; }
#line 1360 "gaspar-parser.c"
    break;

  case 13: /* label: IDENT  */
#line 59 "gaspar-parser.y"
        { strncpy(alignment->labels[taxon], token, TOKEN_SIZE); character = 0; }
#line 1366 "gaspar-parser.c"
    break;

  case 14: /* label: NUMBER  */
#line 60 "gaspar-parser.y"
           { strncpy(alignment->labels[taxon], token, TOKEN_SIZE); character = 0; }
#line 1372 "gaspar-parser.c"
    break;

  case 17: /* char_seq: NUMBER  */
#line 69 "gaspar-parser.y"
         { addNumbersToSequence(); }
#line 1378 "gaspar-parser.c"
    break;

  case 19: /* $@4: %empty  */
#line 74 "gaspar-parser.y"
                      { addMultistateChar(); }
#line 1384 "gaspar-parser.c"
    break;

  case 21: /* charset: MISSING_DATA  */
#line 75 "gaspar-parser.y"
                 { addMissingData(); }
#line 1390 "gaspar-parser.c"
    break;

  case 24: /* opt_analyses: seed  */
#line 83 "gaspar-parser.y"
                                   { bootstrap(alignment, &config); }
#line 1396 "gaspar-parser.c"
    break;

  case 26: /* opt_analyses: %empty  */
#line 83 "gaspar-parser.y"
                                                                                               { bootstrap(alignment, &config); }
#line 1402 "gaspar-parser.c"
    break;

  case 29: /* $@5: %empty  */
#line 91 "gaspar-parser.y"
        { setName(&config, token); printf("\n===== %s =====\n", token); }
#line 1408 "gaspar-parser.c"
    break;

  case 30: /* analysis: IDENT $@5 OPEN_BRACE options CLOSE_BRACE  */
#line 93 "gaspar-parser.y"
              { bootstrap(alignment, &config); setConfigsToDefault(&config); }
#line 1414 "gaspar-parser.c"
    break;

  case 41: /* method: BRANCH_AND_BOUND  */
#line 116 "gaspar-parser.y"
                   { config.searchMethod = branchAndBoundSearch; }
#line 1420 "gaspar-parser.c"
    break;

  case 42: /* method: HILL_CLIMBING  */
#line 117 "gaspar-parser.y"
                  { config.searchMethod = hillClimbingSearch; }
#line 1426 "gaspar-parser.c"
    break;

  case 43: /* method: GENETIC_ALGORITHM  */
#line 118 "gaspar-parser.y"
                      { config.searchMethod = geneticAlgorithmSearch; }
#line 1432 "gaspar-parser.c"
    break;

  case 44: /* evaluation: EVALUATION EWMP  */
#line 122 "gaspar-parser.y"
                  { config.evalFn = fitchParsimony; }
#line 1438 "gaspar-parser.c"
    break;

  case 46: /* hcOperator: TOKEN_SPR  */
#line 130 "gaspar-parser.y"
            { config.hc_operator = SPR; }
#line 1444 "gaspar-parser.c"
    break;

  case 47: /* hcOperator: TOKEN_NNI  */
#line 131 "gaspar-parser.y"
              { config.hc_operator = NNI; }
#line 1450 "gaspar-parser.c"
    break;

  case 48: /* hcOperator: TOKEN_SUBTREE_SWAP  */
#line 132 "gaspar-parser.y"
                       { config.hc_operator = SUBTREE_SWAP; }
#line 1456 "gaspar-parser.c"
    break;

  case 49: /* hcReplicates: NUMBER  */
#line 136 "gaspar-parser.y"
         { config.hc_replicates = atoi(token); }
#line 1462 "gaspar-parser.c"
    break;

  case 51: /* gaMutationOperator: TOKEN_SPR  */
#line 144 "gaspar-parser.y"
            { config.ga_mutationOperator = randomSPR; }
#line 1468 "gaspar-parser.c"
    break;

  case 52: /* gaMutationOperator: TOKEN_NNI  */
#line 145 "gaspar-parser.y"
              { config.ga_mutationOperator = randomNNI; }
#line 1474 "gaspar-parser.c"
    break;

  case 53: /* gaMutationOperator: TOKEN_SUBTREE_SWAP  */
#line 146 "gaspar-parser.y"
                       { config.ga_mutationOperator = randomSubtreeSwap; }
#line 1480 "gaspar-parser.c"
    break;

  case 54: /* gaMutationOperator: TOKEN_HYBRID  */
#line 147 "gaspar-parser.y"
                 { config.ga_mutationOperator = hybridOp; }
#line 1486 "gaspar-parser.c"
    break;

  case 55: /* $@6: %empty  */
#line 151 "gaspar-parser.y"
         { config.ga_selectionStrength = atof(token) / 100; }
#line 1492 "gaspar-parser.c"
    break;

  case 57: /* gaPopulationSize: NUMBER  */
#line 154 "gaspar-parser.y"
         { config.ga_populationSize = atoi(token); }
#line 1498 "gaspar-parser.c"
    break;

  case 58: /* gaGenerations: NUMBER  */
#line 158 "gaspar-parser.y"
         { config.ga_generations = atoi(token); }
#line 1504 "gaspar-parser.c"
    break;

  case 59: /* gaGenerationCuttof: NUMBER  */
#line 162 "gaspar-parser.y"
         { config.ga_generationCuttof = atoi(token); }
#line 1510 "gaspar-parser.c"
    break;

  case 60: /* bsParams: BS_PARAMS NUMBER  */
#line 166 "gaspar-parser.y"
                   { config.bs_replicates = atoi(token); }
#line 1516 "gaspar-parser.c"
    break;

  case 61: /* $@7: %empty  */
#line 170 "gaspar-parser.y"
                       { config.hybrid_nniProb = atof(token) / 100; }
#line 1522 "gaspar-parser.c"
    break;

  case 63: /* maxTrees: MAX_TREES NUMBER  */
#line 174 "gaspar-parser.y"
                   { config.answer_size = atoi(token); }
#line 1528 "gaspar-parser.c"
    break;

  case 64: /* seed: SEED NUMBER  */
#line 178 "gaspar-parser.y"
              {srand(atoi(token)); printf("\nSeed: %d\n", atoi(token)); }
#line 1534 "gaspar-parser.c"
    break;


#line 1538 "gaspar-parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 181 "gaspar-parser.y"


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
  printf("Alignment size: %d\nSequence size: %d\n", alignment->taxa, alignment->characters);
  printf("Allowed states size: %ld\n", allowedArraySize(alignment->characters));
# endif


#ifdef DEBUG
  printf("Taxa parsed: %d\nCharacters parsed in last taxon: %d\n", taxon, character);
#endif

  if (alignment)
    destroyAlignment(alignment);

  if (labels) {
    free(labels[0]);
    free(labels);
  }

  yylex_destroy();
}
