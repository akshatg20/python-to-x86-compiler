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

#ifndef YY_YY_PARSE_TAB_H_INCLUDED
# define YY_YY_PARSE_TAB_H_INCLUDED
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
    NEWLINE = 258,                 /* NEWLINE  */
    INDENT = 259,                  /* INDENT  */
    DEDENT = 260,                  /* DEDENT  */
    ENDMARKER = 261,               /* ENDMARKER  */
    DEF = 262,                     /* DEF  */
    NAME = 263,                    /* NAME  */
    RIGHTARROW = 264,              /* RIGHTARROW  */
    DOUBLE_STAR = 265,             /* DOUBLE_STAR  */
    AUGASSIGN = 266,               /* AUGASSIGN  */
    BREAK = 267,                   /* BREAK  */
    CONTINUE = 268,                /* CONTINUE  */
    RETURN = 269,                  /* RETURN  */
    RAISE = 270,                   /* RAISE  */
    FROM = 271,                    /* FROM  */
    ASSERT = 272,                  /* ASSERT  */
    GLOBAL = 273,                  /* GLOBAL  */
    NONLOCAL = 274,                /* NONLOCAL  */
    IF = 275,                      /* IF  */
    ELIF = 276,                    /* ELIF  */
    ELSE = 277,                    /* ELSE  */
    WHILE = 278,                   /* WHILE  */
    FOR = 279,                     /* FOR  */
    TRY = 280,                     /* TRY  */
    IN = 281,                      /* IN  */
    FINALLY = 282,                 /* FINALLY  */
    EXCEPT = 283,                  /* EXCEPT  */
    AS = 284,                      /* AS  */
    AND = 285,                     /* AND  */
    OR = 286,                      /* OR  */
    NOT = 287,                     /* NOT  */
    IS = 288,                      /* IS  */
    COMP_OP = 289,                 /* COMP_OP  */
    LEFT_SHIFT = 290,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 291,             /* RIGHT_SHIFT  */
    FLOOR_DIV = 292,               /* FLOOR_DIV  */
    AWAIT = 293,                   /* AWAIT  */
    NUMBER = 294,                  /* NUMBER  */
    ELLIPSES_LITERAL = 295,        /* ELLIPSES_LITERAL  */
    TOKEN_TRUE = 296,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 297,             /* TOKEN_FALSE  */
    TOKEN_NONE = 298,              /* TOKEN_NONE  */
    STRING = 299,                  /* STRING  */
    CLASS = 300,                   /* CLASS  */
    COLON = 301,                   /* COLON  */
    SEMI_COLON = 302,              /* SEMI_COLON  */
    OPENING_BRACKET = 303,         /* OPENING_BRACKET  */
    CLOSING_BRACKET = 304,         /* CLOSING_BRACKET  */
    OPENING_SQ_BRACKET = 305,      /* OPENING_SQ_BRACKET  */
    CLOSING_SQ_BRACKET = 306,      /* CLOSING_SQ_BRACKET  */
    OPENING_CURLY_BRACKET = 307,   /* OPENING_CURLY_BRACKET  */
    CLOSING_CURLY_BRACKET = 308,   /* CLOSING_CURLY_BRACKET  */
    STAR = 309,                    /* STAR  */
    EQUAL = 310,                   /* EQUAL  */
    COMMA = 311,                   /* COMMA  */
    PLUS = 312,                    /* PLUS  */
    MINUS = 313,                   /* MINUS  */
    DIV = 314,                     /* DIV  */
    AT = 315,                      /* AT  */
    TILDE = 316,                   /* TILDE  */
    REM = 317,                     /* REM  */
    CARET = 318,                   /* CARET  */
    BITWISE_AND = 319,             /* BITWISE_AND  */
    BITWISE_OR = 320,              /* BITWISE_OR  */
    DOT = 321                      /* DOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 74 "parse.y"

    struct ASTNode* ast;
    char* lexeme;

#line 135 "parse.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_PARSE_TAB_H_INCLUDED  */
