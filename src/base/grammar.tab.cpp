/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "src/base/grammar.y"

  
#include "PNode.h"
#include <stdio.h>
#include <iostream>
#include <cctype>
#include <cstring>
#include <vector>
#include <stack>

//This is taken directly from Defs.h  
#ifdef PEBL_EMSCRIPTEN
#define pDouble double
#define pInt int
#else
#define pDouble long double
#define pInt long int
#endif

  // Prototypes to keep the compiler happy
  void yyerror (char *error);
  int  yylex ();
  extern FILE * yyin;
  PNode * gParseTreeHead;
  PNode * parse(const char* filename);
  extern int yylineno;
  char* sourcefilename;




/* Line 268 of yacc.c  */
#line 103 "src/base/grammar.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PEBL_AND = 258,
     PEBL_ADD = 259,
     PEBL_ARGLIST = 260,
     PEBL_ASSIGN = 261,
     PEBL_BREAK = 262,
     PEBL_COMMA = 263,
     PEBL_DEFINE = 264,
     PEBL_DIVIDE = 265,
     PEBL_DOT = 266,
     PEBL_ELSE = 267,
     PEBL_ELSEIF = 268,
     PEBL_END = 269,
     PEBL_EOF = 270,
     PEBL_EQ = 271,
     PEBL_FUNCTION = 272,
     PEBL_FUNCTIONS = 273,
     PEBL_GE = 274,
     PEBL_GT = 275,
     PEBL_IF = 276,
     PEBL_IFELSE = 277,
     PEBL_LAMBDAFUNCTION = 278,
     PEBL_LBRACE = 279,
     PEBL_LBRACKET = 280,
     PEBL_LE = 281,
     PEBL_LIBRARYFUNCTION = 282,
     PEBL_LISTHEAD = 283,
     PEBL_LISTITEM = 284,
     PEBL_LOOP = 285,
     PEBL_LPAREN = 286,
     PEBL_LT = 287,
     PEBL_MULTIPLY = 288,
     PEBL_NE = 289,
     PEBL_NEWLINE = 290,
     PEBL_NOT = 291,
     PEBL_OR = 292,
     PEBL_POWER = 293,
     PEBL_RETURN = 294,
     PEBL_RBRACE = 295,
     PEBL_RBRACKET = 296,
     PEBL_RPAREN = 297,
     PEBL_SUBTRACT = 298,
     PEBL_SEMI = 299,
     PEBL_STATEMENTS = 300,
     PEBL_START = 301,
     PEBL_VARIABLEDATUM = 302,
     PEBL_VARLIST = 303,
     PEBL_WHILE = 304,
     PEBL_AND_TAIL = 305,
     PEBL_ADD_TAIL = 306,
     PEBL_ASSIGN_TAIL = 307,
     PEBL_BREAK_TAIL = 308,
     PEBL_DIVIDE_TAIL = 309,
     PEBL_EQ_TAIL = 310,
     PEBL_GE_TAIL = 311,
     PEBL_GT_TAIL = 312,
     PEBL_IF_TAIL = 313,
     PEBL_LE_TAIL = 314,
     PEBL_LISTITEM_TAIL = 315,
     PEBL_LOOP_TAIL1 = 316,
     PEBL_LOOP_TAIL2 = 317,
     PEBL_LT_TAIL = 318,
     PEBL_MULTIPLY_TAIL = 319,
     PEBL_NE_TAIL = 320,
     PEBL_NOT_TAIL = 321,
     PEBL_OR_TAIL = 322,
     PEBL_POWER_TAIL = 323,
     PEBL_RETURN_TAIL = 324,
     PEBL_SUBTRACT_TAIL = 325,
     PEBL_STATEMENTS_TAIL1 = 326,
     PEBL_STATEMENTS_TAIL2 = 327,
     PEBL_WHILE_TAIL = 328,
     PEBL_WHILE_TAIL2 = 329,
     PEBL_FUNCTION_TAIL1 = 330,
     PEBL_FUNCTION_TAIL2 = 331,
     PEBL_FUNCTION_TAIL_LIBFUNCTION = 332,
     PEBL_FLOAT = 333,
     PEBL_INTEGER = 334,
     PEBL_STRING = 335,
     PEBL_SYMBOL = 336,
     PEBL_LOCALVAR = 337,
     PEBL_GLOBALVAR = 338,
     PEBL_FUNCTIONNAME = 339,
     PEBL_UMINUS = 340
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 36 "src/base/grammar.y"

  
  pInt    iValue;  /* For the lexical analyser. NUMBER tokens */
  pDouble fValue;
  char        *strValue; 
  PNode       *exp;    /* For expressions. */
  char        *symbol; /* The name of a variable*/
  char        *function; 



/* Line 293 of yacc.c  */
#line 236 "src/base/grammar.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 248 "src/base/grammar.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   543

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    19,    26,    28,    33,    36,
      41,    47,    51,    57,    61,    63,    67,    70,    73,    75,
      78,    82,    86,    93,   100,   108,   117,   120,   124,   131,
     139,   142,   147,   153,   157,   159,   164,   166,   171,   173,
     179,   182,   185,   190,   195,   200,   205,   210,   215,   220,
     224,   228,   232,   236,   240,   244,   247,   249,   251,   253,
     255,   257,   259,   261,   262,   264,   266
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      87,     0,    -1,   105,    88,   105,    -1,    87,    88,   105,
      -1,     9,    84,    31,   101,    42,   105,    89,    -1,     9,
      84,    31,    42,   105,    89,    -1,    91,    -1,    24,   105,
      90,    40,    -1,    96,   105,    -1,    92,   105,    96,   105,
      -1,    24,   105,    92,   105,    40,    -1,    24,   105,    94,
      -1,    24,   105,    92,   105,    94,    -1,    24,   105,    40,
      -1,    93,    -1,    92,   105,    93,    -1,    95,    35,    -1,
      95,    40,    -1,   102,    -1,     7,    35,    -1,    82,     6,
     102,    -1,    83,     6,   102,    -1,    49,    31,   102,    42,
     105,    91,    -1,    21,    31,   102,    42,   105,    91,    -1,
      21,    31,   102,    42,   105,    91,    97,    -1,    30,    31,
     104,     8,   102,    42,   105,    91,    -1,    39,    93,    -1,
      12,   105,    91,    -1,    13,    31,   102,    42,   105,    91,
      -1,    13,    31,   102,    42,   105,    91,    97,    -1,    31,
      42,    -1,    31,   105,   100,    42,    -1,    25,   105,   100,
     105,    41,    -1,    25,   105,    41,    -1,   102,    -1,   102,
       8,   105,   100,    -1,   104,    -1,   104,     8,   105,   101,
      -1,   103,    -1,    31,   105,   102,   105,    42,    -1,    43,
     102,    -1,    36,   102,    -1,   102,     4,   105,   102,    -1,
     102,    10,   105,   102,    -1,   102,    33,   105,   102,    -1,
     102,    38,   105,   102,    -1,   102,    43,   105,   102,    -1,
     102,    37,   105,   102,    -1,   102,     3,   105,   102,    -1,
     102,    32,   102,    -1,   102,    20,   102,    -1,   102,    19,
     102,    -1,   102,    26,   102,    -1,   102,    16,   102,    -1,
     102,    34,   102,    -1,    84,    98,    -1,    79,    -1,    78,
      -1,    80,    -1,    99,    -1,   104,    -1,    82,    -1,    83,
      -1,    -1,   106,    -1,    35,    -1,   106,    35,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   159,   159,   167,   175,   185,   200,   209,   213,   214,
     218,   219,   220,   222,   228,   231,   235,   239,   248,   250,
     252,   261,   269,   282,   288,   304,   311,   316,   323,   329,
     346,   350,   360,   363,   367,   371,   379,   383,   389,   392,
     395,   401,   404,   408,   411,   414,   417,   420,   423,   427,
     430,   433,   436,   439,   442,   451,   465,   468,   471,   478,
     481,   486,   491,   500,   501,   505,   506
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PEBL_AND", "PEBL_ADD", "PEBL_ARGLIST",
  "PEBL_ASSIGN", "PEBL_BREAK", "PEBL_COMMA", "PEBL_DEFINE", "PEBL_DIVIDE",
  "PEBL_DOT", "PEBL_ELSE", "PEBL_ELSEIF", "PEBL_END", "PEBL_EOF",
  "PEBL_EQ", "PEBL_FUNCTION", "PEBL_FUNCTIONS", "PEBL_GE", "PEBL_GT",
  "PEBL_IF", "PEBL_IFELSE", "PEBL_LAMBDAFUNCTION", "PEBL_LBRACE",
  "PEBL_LBRACKET", "PEBL_LE", "PEBL_LIBRARYFUNCTION", "PEBL_LISTHEAD",
  "PEBL_LISTITEM", "PEBL_LOOP", "PEBL_LPAREN", "PEBL_LT", "PEBL_MULTIPLY",
  "PEBL_NE", "PEBL_NEWLINE", "PEBL_NOT", "PEBL_OR", "PEBL_POWER",
  "PEBL_RETURN", "PEBL_RBRACE", "PEBL_RBRACKET", "PEBL_RPAREN",
  "PEBL_SUBTRACT", "PEBL_SEMI", "PEBL_STATEMENTS", "PEBL_START",
  "PEBL_VARIABLEDATUM", "PEBL_VARLIST", "PEBL_WHILE", "PEBL_AND_TAIL",
  "PEBL_ADD_TAIL", "PEBL_ASSIGN_TAIL", "PEBL_BREAK_TAIL",
  "PEBL_DIVIDE_TAIL", "PEBL_EQ_TAIL", "PEBL_GE_TAIL", "PEBL_GT_TAIL",
  "PEBL_IF_TAIL", "PEBL_LE_TAIL", "PEBL_LISTITEM_TAIL", "PEBL_LOOP_TAIL1",
  "PEBL_LOOP_TAIL2", "PEBL_LT_TAIL", "PEBL_MULTIPLY_TAIL", "PEBL_NE_TAIL",
  "PEBL_NOT_TAIL", "PEBL_OR_TAIL", "PEBL_POWER_TAIL", "PEBL_RETURN_TAIL",
  "PEBL_SUBTRACT_TAIL", "PEBL_STATEMENTS_TAIL1", "PEBL_STATEMENTS_TAIL2",
  "PEBL_WHILE_TAIL", "PEBL_WHILE_TAIL2", "PEBL_FUNCTION_TAIL1",
  "PEBL_FUNCTION_TAIL2", "PEBL_FUNCTION_TAIL_LIBFUNCTION", "PEBL_FLOAT",
  "PEBL_INTEGER", "PEBL_STRING", "PEBL_SYMBOL", "PEBL_LOCALVAR",
  "PEBL_GLOBALVAR", "PEBL_FUNCTIONNAME", "PEBL_UMINUS", "$accept",
  "functions", "function", "functionblock", "functionsequence", "block",
  "sequence", "statement", "endstatement", "ustatement", "returnstatement",
  "elseifseq", "arglist", "list", "explist", "varlist", "exp", "datum",
  "variable", "nlornone", "newlines", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    91,    92,    92,    93,    94,    95,    95,
      95,    95,    95,    95,    95,    95,    96,    97,    97,    97,
      98,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   104,   104,   105,   105,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     7,     6,     1,     4,     2,     4,
       5,     3,     5,     3,     1,     3,     2,     2,     1,     2,
       3,     3,     6,     6,     7,     8,     2,     3,     6,     7,
       2,     4,     5,     3,     1,     4,     1,     4,     1,     5,
       2,     2,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      63,    65,     0,     0,    64,     1,     0,    63,    63,    66,
       0,     3,     2,     0,    63,    61,    62,     0,    36,     0,
      63,    63,    63,     5,     6,     0,     0,     0,     4,    37,
       0,     0,    63,     0,    63,     0,     0,    13,     0,     0,
      57,    56,    58,    61,    62,     0,     0,    63,    14,    11,
       0,    63,    59,    18,    38,    60,    19,     0,     0,     0,
       0,    41,    26,     0,    40,     0,     0,     0,    63,    55,
       7,     0,    16,    17,     8,    63,    63,    63,     0,     0,
       0,     0,     0,    63,     0,    63,    63,    63,     0,    33,
      63,    34,     0,    63,     0,    20,    21,    30,     0,    10,
      15,    12,    63,     0,     0,     0,    53,    51,    50,    52,
      49,     0,    54,     0,     0,     0,    63,     0,    63,     0,
       0,    63,     0,     9,    48,    42,    43,    44,    47,    45,
      46,     0,    32,     0,     0,    39,     0,    31,    63,    23,
      35,    63,    22,     0,    63,     0,    24,     0,    63,     0,
       0,    25,     0,    27,     0,    63,     0,    28,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    23,    46,    24,    47,    48,    49,    50,
      51,   146,    69,    52,    90,    17,    53,    54,    55,     3,
       4
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -91
static const yytype_int16 yypact[] =
{
     -25,   -91,     9,    13,    -6,   -91,   -58,   -25,   -25,   -91,
      -1,   -91,   -91,   -26,   -25,   -91,   -91,   -10,    26,    12,
     -25,   -25,   -25,   -91,   -91,    12,   -62,    24,   -91,   -91,
       3,     8,   -25,    16,   -25,   263,   255,   -91,   263,    17,
     -91,   -91,   -91,    36,    46,    27,    19,   -25,   -91,   -91,
     -29,   -25,   -91,   480,   -91,   -91,   -91,   263,    10,   -62,
     263,   500,   -91,    30,    28,   263,   263,   263,   -23,   -91,
     -91,   165,   -91,   -91,   -91,   -25,   -25,   -25,   263,   263,
     263,   263,   263,   -25,   263,   -25,   -25,   -25,   345,   -91,
     -25,   365,    54,   390,   410,   480,   480,   -91,   263,   -91,
     -91,   -91,   -25,   263,   263,   263,    67,    67,    67,    67,
      67,   263,    67,   263,   263,   263,   -25,    31,   -25,   263,
      32,   -25,    33,   -91,   500,    -5,    28,    28,   500,   -91,
      -5,    57,   -91,   263,   435,   -91,    57,   -91,   -25,    11,
     -91,   -25,   -91,   191,   -25,    51,   -91,    57,   -25,    57,
     263,   -91,   247,   -91,   455,   -25,    57,    11,   -91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -91,   -91,    82,    62,   -91,    18,   -52,   -34,   -68,    60,
      41,   -60,   -91,   -91,   -90,    72,    78,   -91,    -9,    -7,
     -91
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      11,    12,    62,   101,    18,    77,    72,    19,   122,     5,
       1,    73,     1,    25,    26,    27,    14,    18,     6,    97,
      15,    16,     6,   144,   145,    58,    10,    60,    83,     9,
      13,    30,    20,    86,    21,    32,    22,   100,    56,    57,
      71,    34,    66,   140,    74,    31,    35,    59,    65,    32,
      92,    89,    67,    38,    33,    34,    15,    16,    68,    70,
      35,    98,   119,    36,    37,    72,    86,    38,   103,   104,
     105,    76,   132,    39,   135,   137,   111,    77,   113,   114,
     115,   138,   150,   117,   101,     8,   120,    28,    40,    41,
      42,   148,    15,    16,    45,   123,    63,   158,    29,     0,
      83,     0,    40,    41,    42,    86,    43,    44,    45,   131,
      87,   133,   102,    61,   136,     0,    64,     0,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,     0,     0,   147,    88,    91,   149,    93,     0,
       0,   152,     0,    94,    95,    96,     0,     0,   156,   139,
       0,     0,     0,     0,   142,     0,   106,   107,   108,   109,
     110,     0,   112,     0,     0,   151,     0,   153,     0,     0,
       0,     0,    30,     0,   157,     0,    91,     0,     0,     0,
       0,   124,   125,   126,     0,     0,    31,     0,     0,   127,
      32,   128,   129,   130,     0,    33,    34,   134,    30,     0,
       0,    35,     0,     0,    36,    99,     0,     0,    38,     0,
       0,    91,    31,     0,    39,     0,    32,     0,     0,     0,
       0,    33,    34,     0,     0,     0,     0,    35,   154,     0,
       0,    37,     0,     0,    38,     0,     0,     0,     0,     0,
      39,     0,     0,    40,    41,    42,     0,    43,    44,    45,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,     0,     0,     0,    31,    40,
      41,    42,    32,    43,    44,    45,    31,    33,    34,     0,
      32,     0,     0,    35,     0,    33,    34,    99,    32,     0,
      38,    35,     0,     0,    34,     0,    39,     0,    38,    35,
       0,     0,     0,     0,    39,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,    41,    42,     0,    43,
      44,    45,     0,    40,    41,    42,     0,    43,    44,    45,
       0,    40,    41,    42,     0,    15,    16,    45,    75,    76,
       0,     0,     0,     0,     0,    77,     0,     0,     0,     0,
       0,    78,     0,     0,    79,    80,     0,     0,    75,    76,
       0,    81,     0,   118,     0,    77,     0,    82,    83,    84,
       0,    78,    85,    86,    79,    80,     0,   116,    87,     0,
       0,    81,     0,    75,    76,     0,     0,    82,    83,    84,
      77,     0,    85,    86,     0,     0,    78,     0,    87,    79,
      80,     0,     0,    75,    76,     0,    81,     0,     0,     0,
      77,     0,    82,    83,    84,     1,    78,    85,    86,    79,
      80,     0,     0,    87,     0,     0,    81,     0,    75,    76,
       0,     0,    82,    83,    84,    77,     0,    85,    86,     0,
       0,    78,   121,    87,    79,    80,     0,     0,    75,    76,
       0,    81,     0,     0,     0,    77,     0,    82,    83,    84,
       0,    78,    85,    86,    79,    80,     0,   141,    87,     0,
       0,    81,     0,    75,    76,     0,     0,    82,    83,    84,
      77,     0,    85,    86,     0,     0,    78,   155,    87,    79,
      80,     0,     0,     0,    76,     0,    81,     0,     0,     0,
      77,     0,    82,    83,    84,     0,    78,    85,    86,    79,
      80,     0,     0,    87,     0,     0,    81,     0,     0,     0,
       0,     0,    82,    83,    84,     0,     0,     0,    86,     0,
       0,     0,     0,    87
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-91))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       7,     8,    36,    71,    13,    10,    35,    14,    98,     0,
      35,    40,    35,    20,    21,    22,    42,    26,     9,    42,
      82,    83,     9,    12,    13,    32,    84,    34,    33,    35,
      31,     7,    42,    38,     8,    25,    24,    71,    35,    31,
      47,    31,     6,   133,    51,    21,    36,    31,    31,    25,
      59,    41,     6,    43,    30,    31,    82,    83,    31,    40,
      36,    68,     8,    39,    40,    35,    38,    43,    75,    76,
      77,     4,    41,    49,    42,    42,    83,    10,    85,    86,
      87,    24,    31,    90,   152,     3,    93,    25,    78,    79,
      80,   143,    82,    83,    84,   102,    36,   157,    26,    -1,
      33,    -1,    78,    79,    80,    38,    82,    83,    84,   116,
      43,   118,    71,    35,   121,    -1,    38,    -1,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   138,    -1,    -1,   141,    57,    58,   144,    60,    -1,
      -1,   148,    -1,    65,    66,    67,    -1,    -1,   155,   131,
      -1,    -1,    -1,    -1,   136,    -1,    78,    79,    80,    81,
      82,    -1,    84,    -1,    -1,   147,    -1,   149,    -1,    -1,
      -1,    -1,     7,    -1,   156,    -1,    98,    -1,    -1,    -1,
      -1,   103,   104,   105,    -1,    -1,    21,    -1,    -1,   111,
      25,   113,   114,   115,    -1,    30,    31,   119,     7,    -1,
      -1,    36,    -1,    -1,    39,    40,    -1,    -1,    43,    -1,
      -1,   133,    21,    -1,    49,    -1,    25,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    36,   150,    -1,
      -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    78,    79,    80,    -1,    82,    83,    84,
      -1,    -1,    -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     7,    -1,    -1,    -1,    -1,    -1,    21,    78,
      79,    80,    25,    82,    83,    84,    21,    30,    31,    -1,
      25,    -1,    -1,    36,    -1,    30,    31,    40,    25,    -1,
      43,    36,    -1,    -1,    31,    -1,    49,    -1,    43,    36,
      -1,    -1,    -1,    -1,    49,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80,    -1,    82,
      83,    84,    -1,    78,    79,    80,    -1,    82,    83,    84,
      -1,    78,    79,    80,    -1,    82,    83,    84,     3,     4,
      -1,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    19,    20,    -1,    -1,     3,     4,
      -1,    26,    -1,     8,    -1,    10,    -1,    32,    33,    34,
      -1,    16,    37,    38,    19,    20,    -1,    42,    43,    -1,
      -1,    26,    -1,     3,     4,    -1,    -1,    32,    33,    34,
      10,    -1,    37,    38,    -1,    -1,    16,    -1,    43,    19,
      20,    -1,    -1,     3,     4,    -1,    26,    -1,    -1,    -1,
      10,    -1,    32,    33,    34,    35,    16,    37,    38,    19,
      20,    -1,    -1,    43,    -1,    -1,    26,    -1,     3,     4,
      -1,    -1,    32,    33,    34,    10,    -1,    37,    38,    -1,
      -1,    16,    42,    43,    19,    20,    -1,    -1,     3,     4,
      -1,    26,    -1,    -1,    -1,    10,    -1,    32,    33,    34,
      -1,    16,    37,    38,    19,    20,    -1,    42,    43,    -1,
      -1,    26,    -1,     3,     4,    -1,    -1,    32,    33,    34,
      10,    -1,    37,    38,    -1,    -1,    16,    42,    43,    19,
      20,    -1,    -1,    -1,     4,    -1,    26,    -1,    -1,    -1,
      10,    -1,    32,    33,    34,    -1,    16,    37,    38,    19,
      20,    -1,    -1,    43,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    35,    87,   105,   106,     0,     9,    88,    88,    35,
      84,   105,   105,    31,    42,    82,    83,   101,   104,   105,
      42,     8,    24,    89,    91,   105,   105,   105,    89,   101,
       7,    21,    25,    30,    31,    36,    39,    40,    43,    49,
      78,    79,    80,    82,    83,    84,    90,    92,    93,    94,
      95,    96,    99,   102,   103,   104,    35,    31,   105,    31,
     105,   102,    93,    95,   102,    31,     6,     6,    31,    98,
      40,   105,    35,    40,   105,     3,     4,    10,    16,    19,
      20,    26,    32,    33,    34,    37,    38,    43,   102,    41,
     100,   102,   104,   102,   102,   102,   102,    42,   105,    40,
      93,    94,    96,   105,   105,   105,   102,   102,   102,   102,
     102,   105,   102,   105,   105,   105,    42,   105,     8,     8,
     105,    42,   100,   105,   102,   102,   102,   102,   102,   102,
     102,   105,    41,   105,   102,    42,   105,    42,    24,    91,
     100,    42,    91,   105,    12,    13,    97,   105,    92,   105,
      31,    91,   105,    91,   102,    42,   105,    91,    97
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 159 "src/base/grammar.y"
    {gParseTreeHead =  new OpNode(PEBL_FUNCTIONS,(yyvsp[(2) - (3)].exp),NULL, sourcefilename, yylineno);

		           (yyval.exp) = gParseTreeHead;
		}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 167 "src/base/grammar.y"
    { gParseTreeHead = new OpNode(PEBL_FUNCTIONS, (yyvsp[(2) - (3)].exp), (yyvsp[(1) - (3)].exp), sourcefilename, yylineno);
		           (yyval.exp) = gParseTreeHead;
		}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 175 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, (yyvsp[(4) - (7)].exp), (yyvsp[(7) - (7)].exp), sourcefilename, yylineno);  
		tmpFN->SetFunctionName((yyvsp[(2) - (7)].function));
		PNode * tmpNode = new DataNode(Variant((yyvsp[(2) - (7)].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		free((yyvsp[(2) - (7)].function));
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);

        }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 185 "src/base/grammar.y"
    { ;
		PNode * tmpFN = new OpNode(PEBL_LAMBDAFUNCTION, NULL, (yyvsp[(6) - (6)].exp), sourcefilename, yylineno); 
		tmpFN->SetFunctionName((yyvsp[(2) - (6)].function));
		PNode * tmpNode = new DataNode(Variant((yyvsp[(2) - (6)].function), P_DATA_FUNCTION), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, tmpFN, sourcefilename, yylineno);
                free((yyvsp[(2) - (6)].function));
		  }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 200 "src/base/grammar.y"
    {
		   /*When no return value is provided, return 1 (true)*/
                  DataNode* retval  = new DataNode (Variant(1), sourcefilename, yylineno);
		  OpNode *tmpReturn = new OpNode(PEBL_RETURN, retval, NULL, sourcefilename, yylineno);
    	           (yyval.exp) = new OpNode(PEBL_STATEMENTS,(yyvsp[(1) - (1)].exp),tmpReturn,sourcefilename,yylineno);
                 }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 209 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(3) - (4)].exp);}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 213 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (2)].exp);}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 214 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_STATEMENTS, (yyvsp[(1) - (4)].exp), (yyvsp[(3) - (4)].exp), sourcefilename, yylineno);}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 218 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(3) - (5)].exp);}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 219 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(3) - (3)].exp);}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 220 "src/base/grammar.y"
    {
  (yyval.exp)  = new OpNode(PEBL_STATEMENTS, (yyvsp[(3) - (5)].exp), (yyvsp[(5) - (5)].exp), sourcefilename, yylineno);}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 222 "src/base/grammar.y"
    { (yyval.exp) = new DataNode (Variant(0), sourcefilename, yylineno);}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 228 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 231 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_STATEMENTS, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 235 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (2)].exp);}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 239 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (2)].exp);}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 248 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 250 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_BREAK, NULL, NULL, sourcefilename, yylineno);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 253 "src/base/grammar.y"
    { 
	        Variant tmpV((yyvsp[(1) - (3)].symbol),P_DATA_LOCALVARIABLE);       /*create a new temporary variant*/
		    free((yyvsp[(1) - (3)].symbol));
			PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		    (yyval.exp) = new OpNode(PEBL_ASSIGN, tmpNode, (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 262 "src/base/grammar.y"
    { 
	        Variant tmpV((yyvsp[(1) - (3)].symbol),P_DATA_GLOBALVARIABLE);      /*create a new temporary variant*/
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);        /*create basic pnode*/
		(yyval.exp) = new OpNode(PEBL_ASSIGN, tmpNode, (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);   /*Use symbol node in assignment node*/
		}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 269 "src/base/grammar.y"
    {;
		(yyval.exp) = new OpNode(PEBL_WHILE, (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp), sourcefilename, yylineno); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 282 "src/base/grammar.y"
    {
		(yyval.exp) = new OpNode(PEBL_IF, (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp), sourcefilename, yylineno); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 288 "src/base/grammar.y"
    {
		/*First make the else node*/
		PNode * tmpNode = new OpNode(PEBL_ELSE, (yyvsp[(6) - (7)].exp), (yyvsp[(7) - (7)].exp), sourcefilename, yylineno);
		/*Put the else node in the IF node*/
		(yyval.exp) = new OpNode(PEBL_IFELSE, (yyvsp[(3) - (7)].exp), tmpNode, sourcefilename, yylineno); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 304 "src/base/grammar.y"
    {
		PNode * tmpNode = new OpNode(PEBL_VARIABLEDATUM, (yyvsp[(3) - (8)].exp), (yyvsp[(5) - (8)].exp), sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_LOOP, tmpNode, (yyvsp[(8) - (8)].exp), sourcefilename, yylineno); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 311 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_RETURN, (yyvsp[(2) - (2)].exp), NULL, sourcefilename, yylineno);}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 316 "src/base/grammar.y"
    {

		(yyval.exp) = (yyvsp[(3) - (3)].exp); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 323 "src/base/grammar.y"
    {
		/*First make the else node*/

		  (yyval.exp) =  new OpNode(PEBL_IF, (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp), sourcefilename, yylineno);

   }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 329 "src/base/grammar.y"
    {

		/*First make the else node*/
		PNode * tmpNode = new OpNode(PEBL_ELSE, (yyvsp[(6) - (7)].exp), (yyvsp[(7) - (7)].exp), sourcefilename, yylineno);
		/*Put the else node in the IF node*/
		(yyval.exp) = new OpNode(PEBL_IFELSE, (yyvsp[(3) - (7)].exp), tmpNode, sourcefilename, yylineno); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 346 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_ARGLIST, NULL, NULL, sourcefilename, yylineno);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 350 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_ARGLIST, (yyvsp[(3) - (4)].exp), NULL, sourcefilename, yylineno);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 360 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTHEAD,(yyvsp[(3) - (5)].exp), NULL, sourcefilename, yylineno);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 363 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTHEAD, NULL, NULL, sourcefilename, yylineno);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 367 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTITEM, (yyvsp[(1) - (1)].exp), NULL, sourcefilename, yylineno);}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 371 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_LISTITEM, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 379 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_VARLIST, (yyvsp[(1) - (1)].exp), NULL, sourcefilename, yylineno);}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 383 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_VARLIST,(yyvsp[(1) - (4)].exp),(yyvsp[(4) - (4)].exp), sourcefilename, yylineno);}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 389 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 392 "src/base/grammar.y"
    {(yyval.exp) = (yyvsp[(3) - (5)].exp);}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 395 "src/base/grammar.y"
    {
		Variant tmpV = 0;
		PNode * tmpNode = new DataNode(tmpV, sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_SUBTRACT, tmpNode, (yyvsp[(2) - (2)].exp), sourcefilename, yylineno); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 401 "src/base/grammar.y"
    {(yyval.exp) = new OpNode(PEBL_NOT, (yyvsp[(2) - (2)].exp), NULL, sourcefilename, yylineno); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 404 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_ADD, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);  }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 408 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_DIVIDE,(yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);  }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 411 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_MULTIPLY, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 414 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_POWER, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 417 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_SUBTRACT, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 420 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_OR, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 423 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_AND, (yyvsp[(1) - (4)].exp), (yyvsp[(4) - (4)].exp), sourcefilename, yylineno); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 427 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_LT,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 430 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_GT,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 433 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_GE,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 436 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_LE,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 439 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_EQ,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 442 "src/base/grammar.y"
    { (yyval.exp) = new OpNode(PEBL_NE,  (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), sourcefilename, yylineno);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 451 "src/base/grammar.y"
    {


		  /*Memory leak here, by electricfence*/
		Variant v = Variant((yyvsp[(1) - (2)].function),P_DATA_FUNCTION);
		PNode * tmpNode = new DataNode(v, sourcefilename, yylineno);
		(yyval.exp) = new OpNode(PEBL_FUNCTION, tmpNode, (yyvsp[(2) - (2)].exp), sourcefilename, yylineno);
		free((yyvsp[(1) - (2)].function));
		}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 465 "src/base/grammar.y"
    { (yyval.exp) = new DataNode ((yyvsp[(1) - (1)].iValue), sourcefilename, yylineno); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 468 "src/base/grammar.y"
    { (yyval.exp) = new DataNode ((yyvsp[(1) - (1)].fValue), sourcefilename, yylineno);}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 471 "src/base/grammar.y"
    {
	  Variant tmpV((yyvsp[(1) - (1)].strValue));            /*create a new temporary variant*/
	  free((yyvsp[(1) - (1)].strValue));
	  (yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);

                        }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 478 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 481 "src/base/grammar.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 486 "src/base/grammar.y"
    { 
		Variant tmpV((yyvsp[(1) - (1)].symbol), P_DATA_LOCALVARIABLE);           /*create a new temporary variant*/;
		(yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);                        /*Make a new variable node here.*/
                free((yyvsp[(1) - (1)].symbol));
                }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 491 "src/base/grammar.y"
    { 
		Variant tmpV((yyvsp[(1) - (1)].symbol), P_DATA_GLOBALVARIABLE);          /*create a new temporary variant*/;
		(yyval.exp) = new DataNode(tmpV, sourcefilename, yylineno);  /*Make a new variable node here.*/
		free((yyvsp[(1) - (1)].symbol));
		 }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 500 "src/base/grammar.y"
    {/*nothing*/;}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 501 "src/base/grammar.y"
    {/**/;}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 505 "src/base/grammar.y"
    {/**/;}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 506 "src/base/grammar.y"
    {/**/;}
    break;



/* Line 1806 of yacc.c  */
#line 2236 "src/base/grammar.tab.cpp"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 512 "src/base/grammar.y"


void yyerror (char *error)
{

  std::cerr << "line " << yylineno << " of "<< sourcefilename<<": " << error << std::endl;
  exit(1);
}

extern int yy_flex_debug;

PNode * parse (const char* filename)
{
  //yydebug=1;          /*Bison must be run with -t option to use debugging*/
  //yy_flex_debug = 1;   /*Flex must be run with -d option to use*/
  /*This is currently only called once, so use
   *it to open a hard-coded file for testing
   */
  
  ///Reset the linecounter
  yylineno = 1;

    FILE * filein = fopen(filename,"r");
    if(!filein) 
	{
	    fprintf(stderr,"Could not open %s\n",filename);
	    exit(1);
	}
    fprintf(stderr,"File [%s] opened successfully.\n", filename);
    yyin=filein;
    
    //Set global filename indicator to current filename for use in error reporting.
    sourcefilename = strdup(filename);

    yyparse ();

    free(sourcefilename);
    return gParseTreeHead;
}

