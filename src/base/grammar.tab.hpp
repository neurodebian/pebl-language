/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
#line 36 "src/base/grammar.y"

  
  pInt    iValue;  /* For the lexical analyser. NUMBER tokens */
  pDouble fValue;
  char        *strValue; 
  PNode       *exp;    /* For expressions. */
  char        *symbol; /* The name of a variable*/
  char        *function; 



/* Line 2068 of yacc.c  */
#line 147 "src/base/grammar.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


