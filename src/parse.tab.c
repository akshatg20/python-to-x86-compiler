/* A Bison parser, made by GNU Bison 3.8.1.  */

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
#define YYBISON 30801

/* Bison version string.  */
#define YYBISON_VERSION "3.8.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parse.y"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <queue>
#include <stdarg.h>
#ifndef AST_HPP
#include "ast.hpp"
#endif
#ifndef TYPES_HPP
#include "types.hpp"
#endif
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
using namespace std;

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF PARSER ***********************************/

// Write any assumptions that you take in the comment below
/*
----
*/

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF PARSER ***********************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.
extern int yylineno;
extern char* yytext;
extern int counter;
extern int AST_DEBUG_OUTSIDE_VERBOSE;
extern int AST_DEBUG_INSIDE_VERBOSE;
extern int AST_STRUCTURE_DEBUG;
extern char *inputfile_path,*outputfile_path,*errorfile_path,*astfile_path,*dotfile_path,*parsefile_path;
extern int DOT_GENERATION,AST_GENERATION,PARSE_TREE_GENERATION;
extern ASTNode* root;
extern vector<ASTNode*> v_r_dfs;
extern bool isAST;
extern SemanticError* ErrorMsg;                         // Semantic Error Message
extern SymbolTable* currTable;                          // pointer to the current symbol table in use
extern int current_scope;                               // maintains the current scope while parsing, initialized to zero

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

// All classes and structures that you want to declare should go here.

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.

int yylex();
void yyerror(const char* s);

/* Debug mode specification variables for parser */
int PARSER_DEBUG_OUTSIDE_VERBOSE = 0;       // for debugging purposes only
int PARSER_DEBUG_INSIDE_VERBOSE = 0;        // for verbose output purposes

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

#line 144 "parse.tab.c"

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

#include "parse.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NEWLINE = 3,                    /* NEWLINE  */
  YYSYMBOL_INDENT = 4,                     /* INDENT  */
  YYSYMBOL_DEDENT = 5,                     /* DEDENT  */
  YYSYMBOL_ENDMARKER = 6,                  /* ENDMARKER  */
  YYSYMBOL_DEF = 7,                        /* DEF  */
  YYSYMBOL_NAME = 8,                       /* NAME  */
  YYSYMBOL_RIGHTARROW = 9,                 /* RIGHTARROW  */
  YYSYMBOL_DOUBLE_STAR = 10,               /* DOUBLE_STAR  */
  YYSYMBOL_AUGASSIGN = 11,                 /* AUGASSIGN  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_RAISE = 15,                     /* RAISE  */
  YYSYMBOL_FROM = 16,                      /* FROM  */
  YYSYMBOL_ASSERT = 17,                    /* ASSERT  */
  YYSYMBOL_GLOBAL = 18,                    /* GLOBAL  */
  YYSYMBOL_NONLOCAL = 19,                  /* NONLOCAL  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_ELIF = 21,                      /* ELIF  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_WHILE = 23,                     /* WHILE  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_TRY = 25,                       /* TRY  */
  YYSYMBOL_IN = 26,                        /* IN  */
  YYSYMBOL_FINALLY = 27,                   /* FINALLY  */
  YYSYMBOL_EXCEPT = 28,                    /* EXCEPT  */
  YYSYMBOL_AS = 29,                        /* AS  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_OR = 31,                        /* OR  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_IS = 33,                        /* IS  */
  YYSYMBOL_COMP_OP = 34,                   /* COMP_OP  */
  YYSYMBOL_LEFT_SHIFT = 35,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 36,               /* RIGHT_SHIFT  */
  YYSYMBOL_FLOOR_DIV = 37,                 /* FLOOR_DIV  */
  YYSYMBOL_AWAIT = 38,                     /* AWAIT  */
  YYSYMBOL_NUMBER = 39,                    /* NUMBER  */
  YYSYMBOL_ELLIPSES_LITERAL = 40,          /* ELLIPSES_LITERAL  */
  YYSYMBOL_TOKEN_TRUE = 41,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 42,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_NONE = 43,                /* TOKEN_NONE  */
  YYSYMBOL_STRING = 44,                    /* STRING  */
  YYSYMBOL_CLASS = 45,                     /* CLASS  */
  YYSYMBOL_COLON = 46,                     /* COLON  */
  YYSYMBOL_SEMI_COLON = 47,                /* SEMI_COLON  */
  YYSYMBOL_OPENING_BRACKET = 48,           /* OPENING_BRACKET  */
  YYSYMBOL_CLOSING_BRACKET = 49,           /* CLOSING_BRACKET  */
  YYSYMBOL_OPENING_SQ_BRACKET = 50,        /* OPENING_SQ_BRACKET  */
  YYSYMBOL_CLOSING_SQ_BRACKET = 51,        /* CLOSING_SQ_BRACKET  */
  YYSYMBOL_OPENING_CURLY_BRACKET = 52,     /* OPENING_CURLY_BRACKET  */
  YYSYMBOL_CLOSING_CURLY_BRACKET = 53,     /* CLOSING_CURLY_BRACKET  */
  YYSYMBOL_STAR = 54,                      /* STAR  */
  YYSYMBOL_EQUAL = 55,                     /* EQUAL  */
  YYSYMBOL_COMMA = 56,                     /* COMMA  */
  YYSYMBOL_PLUS = 57,                      /* PLUS  */
  YYSYMBOL_MINUS = 58,                     /* MINUS  */
  YYSYMBOL_DIV = 59,                       /* DIV  */
  YYSYMBOL_AT = 60,                        /* AT  */
  YYSYMBOL_TILDE = 61,                     /* TILDE  */
  YYSYMBOL_REM = 62,                       /* REM  */
  YYSYMBOL_CARET = 63,                     /* CARET  */
  YYSYMBOL_BITWISE_AND = 64,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 65,                /* BITWISE_OR  */
  YYSYMBOL_DOT = 66,                       /* DOT  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_start = 68,                     /* start  */
  YYSYMBOL_file_input = 69,                /* file_input  */
  YYSYMBOL_continued_file_input = 70,      /* continued_file_input  */
  YYSYMBOL_funcdef = 71,                   /* funcdef  */
  YYSYMBOL_parameters = 72,                /* parameters  */
  YYSYMBOL_typedargslist = 73,             /* typedargslist  */
  YYSYMBOL_next_arg = 74,                  /* next_arg  */
  YYSYMBOL_tfpdef = 75,                    /* tfpdef  */
  YYSYMBOL_stmt = 76,                      /* stmt  */
  YYSYMBOL_simple_stmt = 77,               /* simple_stmt  */
  YYSYMBOL_next_small_stmt = 78,           /* next_small_stmt  */
  YYSYMBOL_small_stmt = 79,                /* small_stmt  */
  YYSYMBOL_expr_stmt = 80,                 /* expr_stmt  */
  YYSYMBOL_continued_expr_stmt = 81,       /* continued_expr_stmt  */
  YYSYMBOL_annassign = 82,                 /* annassign  */
  YYSYMBOL_testlist_star_expr = 83,        /* testlist_star_expr  */
  YYSYMBOL_flow_stmt = 84,                 /* flow_stmt  */
  YYSYMBOL_break_stmt = 85,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 86,             /* continue_stmt  */
  YYSYMBOL_return_stmt = 87,               /* return_stmt  */
  YYSYMBOL_raise_stmt = 88,                /* raise_stmt  */
  YYSYMBOL_global_stmt = 89,               /* global_stmt  */
  YYSYMBOL_nonlocal_stmt = 90,             /* nonlocal_stmt  */
  YYSYMBOL_assert_stmt = 91,               /* assert_stmt  */
  YYSYMBOL_stmt_helper = 92,               /* stmt_helper  */
  YYSYMBOL_compound_stmt = 93,             /* compound_stmt  */
  YYSYMBOL_if_stmt = 94,                   /* if_stmt  */
  YYSYMBOL_elif_stmt = 95,                 /* elif_stmt  */
  YYSYMBOL_else_stmt = 96,                 /* else_stmt  */
  YYSYMBOL_while_stmt = 97,                /* while_stmt  */
  YYSYMBOL_for_stmt = 98,                  /* for_stmt  */
  YYSYMBOL_try_stmt = 99,                  /* try_stmt  */
  YYSYMBOL_except_stmt = 100,              /* except_stmt  */
  YYSYMBOL_finally_stmt = 101,             /* finally_stmt  */
  YYSYMBOL_except_clause = 102,            /* except_clause  */
  YYSYMBOL_suite = 103,                    /* suite  */
  YYSYMBOL_stmts = 104,                    /* stmts  */
  YYSYMBOL_test = 105,                     /* test  */
  YYSYMBOL_test_nocond = 106,              /* test_nocond  */
  YYSYMBOL_or_test = 107,                  /* or_test  */
  YYSYMBOL_continued_or_test = 108,        /* continued_or_test  */
  YYSYMBOL_and_test = 109,                 /* and_test  */
  YYSYMBOL_continued_and_test = 110,       /* continued_and_test  */
  YYSYMBOL_not_test = 111,                 /* not_test  */
  YYSYMBOL_comparison = 112,               /* comparison  */
  YYSYMBOL_comparison_stmt = 113,          /* comparison_stmt  */
  YYSYMBOL_comp_op = 114,                  /* comp_op  */
  YYSYMBOL_star_expr = 115,                /* star_expr  */
  YYSYMBOL_expr = 116,                     /* expr  */
  YYSYMBOL_continued_xor_expr = 117,       /* continued_xor_expr  */
  YYSYMBOL_xor_expr = 118,                 /* xor_expr  */
  YYSYMBOL_continued_and_expr = 119,       /* continued_and_expr  */
  YYSYMBOL_and_expr = 120,                 /* and_expr  */
  YYSYMBOL_continued_shift_expr = 121,     /* continued_shift_expr  */
  YYSYMBOL_shift_expr = 122,               /* shift_expr  */
  YYSYMBOL_continued_arith_expr = 123,     /* continued_arith_expr  */
  YYSYMBOL_arith_expr = 124,               /* arith_expr  */
  YYSYMBOL_continued_term = 125,           /* continued_term  */
  YYSYMBOL_term = 126,                     /* term  */
  YYSYMBOL_continued_factor = 127,         /* continued_factor  */
  YYSYMBOL_factor = 128,                   /* factor  */
  YYSYMBOL_power = 129,                    /* power  */
  YYSYMBOL_atom_expr = 130,                /* atom_expr  */
  YYSYMBOL_trailers = 131,                 /* trailers  */
  YYSYMBOL_atom = 132,                     /* atom  */
  YYSYMBOL_strings = 133,                  /* strings  */
  YYSYMBOL_testlist_comp = 134,            /* testlist_comp  */
  YYSYMBOL_continued_testlist = 135,       /* continued_testlist  */
  YYSYMBOL_trailer = 136,                  /* trailer  */
  YYSYMBOL_subscriptlist = 137,            /* subscriptlist  */
  YYSYMBOL_continued_subscript = 138,      /* continued_subscript  */
  YYSYMBOL_subscript = 139,                /* subscript  */
  YYSYMBOL_sliceop = 140,                  /* sliceop  */
  YYSYMBOL_exprlist = 141,                 /* exprlist  */
  YYSYMBOL_continued_exprlist = 142,       /* continued_exprlist  */
  YYSYMBOL_testlist = 143,                 /* testlist  */
  YYSYMBOL_continued_comma_test = 144,     /* continued_comma_test  */
  YYSYMBOL_dictorsetmaker = 145,           /* dictorsetmaker  */
  YYSYMBOL_continued_dictorset = 146,      /* continued_dictorset  */
  YYSYMBOL_classdef = 147,                 /* classdef  */
  YYSYMBOL_arglist = 148,                  /* arglist  */
  YYSYMBOL_continued_argument = 149,       /* continued_argument  */
  YYSYMBOL_argument = 150,                 /* argument  */
  YYSYMBOL_comp_iter = 151,                /* comp_iter  */
  YYSYMBOL_comp_for = 152,                 /* comp_for  */
  YYSYMBOL_comp_if = 153                   /* comp_if  */
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
typedef yytype_int16 yy_state_t;

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   869

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  225
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  353

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   241,   241,   274,   294,   308,   321,   334,   370,   401,
     418,   439,   464,   487,   507,   528,   552,   571,   583,   604,
     624,   634,   647,   668,   691,   710,   721,   731,   741,   749,
     757,   772,   793,   816,   839,   861,   872,   894,   915,   935,
     955,   975,   996,  1006,  1016,  1026,  1039,  1055,  1072,  1092,
    1109,  1131,  1150,  1166,  1192,  1218,  1241,  1262,  1282,  1295,
    1305,  1315,  1325,  1335,  1345,  1358,  1387,  1411,  1423,  1447,
    1458,  1537,  1568,  1594,  1622,  1647,  1672,  1691,  1703,  1725,
    1743,  1759,  1770,  1793,  1810,  1824,  1859,  1873,  1887,  1908,
    1928,  1939,  1960,  1980,  1991,  2009,  2020,  2041,  2061,  2072,
    2086,  2100,  2115,  2129,  2148,  2169,  2190,  2210,  2221,  2242,
    2262,  2273,  2294,  2314,  2325,  2346,  2366,  2386,  2397,  2418,
    2438,  2458,  2469,  2490,  2510,  2530,  2550,  2570,  2590,  2601,
    2619,  2637,  2655,  2668,  2690,  2701,  2724,  2737,  2756,  2767,
    2786,  2804,  2823,  2841,  2860,  2878,  2893,  2907,  2918,  2932,
    2944,  2956,  2970,  2988,  3004,  3015,  3035,  3053,  3064,  3084,
    3105,  3124,  3143,  3156,  3176,  3194,  3212,  3230,  3251,  3273,
    3292,  3302,  3310,  3334,  3355,  3376,  3394,  3415,  3433,  3452,
    3468,  3486,  3503,  3523,  3541,  3561,  3582,  3601,  3620,  3631,
    3651,  3672,  3691,  3703,  3726,  3751,  3773,  3794,  3819,  3842,
    3853,  3873,  3891,  3902,  3922,  3944,  3968,  3991,  4002,  4032,
    4063,  4092,  4110,  4133,  4152,  4162,  4172,  4193,  4211,  4229,
    4243,  4251,  4263,  4287,  4313,  4334
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
  "\"end of file\"", "error", "\"invalid token\"", "NEWLINE", "INDENT",
  "DEDENT", "ENDMARKER", "DEF", "NAME", "RIGHTARROW", "DOUBLE_STAR",
  "AUGASSIGN", "BREAK", "CONTINUE", "RETURN", "RAISE", "FROM", "ASSERT",
  "GLOBAL", "NONLOCAL", "IF", "ELIF", "ELSE", "WHILE", "FOR", "TRY", "IN",
  "FINALLY", "EXCEPT", "AS", "AND", "OR", "NOT", "IS", "COMP_OP",
  "LEFT_SHIFT", "RIGHT_SHIFT", "FLOOR_DIV", "AWAIT", "NUMBER",
  "ELLIPSES_LITERAL", "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_NONE", "STRING",
  "CLASS", "COLON", "SEMI_COLON", "OPENING_BRACKET", "CLOSING_BRACKET",
  "OPENING_SQ_BRACKET", "CLOSING_SQ_BRACKET", "OPENING_CURLY_BRACKET",
  "CLOSING_CURLY_BRACKET", "STAR", "EQUAL", "COMMA", "PLUS", "MINUS",
  "DIV", "AT", "TILDE", "REM", "CARET", "BITWISE_AND", "BITWISE_OR", "DOT",
  "$accept", "start", "file_input", "continued_file_input", "funcdef",
  "parameters", "typedargslist", "next_arg", "tfpdef", "stmt",
  "simple_stmt", "next_small_stmt", "small_stmt", "expr_stmt",
  "continued_expr_stmt", "annassign", "testlist_star_expr", "flow_stmt",
  "break_stmt", "continue_stmt", "return_stmt", "raise_stmt",
  "global_stmt", "nonlocal_stmt", "assert_stmt", "stmt_helper",
  "compound_stmt", "if_stmt", "elif_stmt", "else_stmt", "while_stmt",
  "for_stmt", "try_stmt", "except_stmt", "finally_stmt", "except_clause",
  "suite", "stmts", "test", "test_nocond", "or_test", "continued_or_test",
  "and_test", "continued_and_test", "not_test", "comparison",
  "comparison_stmt", "comp_op", "star_expr", "expr", "continued_xor_expr",
  "xor_expr", "continued_and_expr", "and_expr", "continued_shift_expr",
  "shift_expr", "continued_arith_expr", "arith_expr", "continued_term",
  "term", "continued_factor", "factor", "power", "atom_expr", "trailers",
  "atom", "strings", "testlist_comp", "continued_testlist", "trailer",
  "subscriptlist", "continued_subscript", "subscript", "sliceop",
  "exprlist", "continued_exprlist", "testlist", "continued_comma_test",
  "dictorsetmaker", "continued_dictorset", "classdef", "arglist",
  "continued_argument", "argument", "comp_iter", "comp_for", "comp_if", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-225)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -225,    39,  -225,   302,  -225,  -225,  -225,    55,  -225,  -225,
    -225,   783,   783,   783,    66,    78,   783,   783,    71,    36,
     783,   212,  -225,  -225,  -225,  -225,  -225,  -225,    80,   594,
     621,     3,   808,   808,   808,   808,  -225,  -225,  -225,  -225,
    -225,    13,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,    73,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,    86,
    -225,    60,  -225,    70,  -225,  -225,   104,    75,  -225,  -225,
      76,    96,  -225,  -225,   100,   354,  -225,  -225,   -17,  -225,
     119,   119,    95,  -225,    94,   808,  -225,    26,   119,    93,
    -225,  -225,  -225,  -225,    11,   783,   783,    92,  -225,    97,
     783,   120,   128,   103,    74,    98,    99,   101,    63,    -9,
      30,   808,    25,  -225,    20,     6,   105,   783,   783,   111,
     111,   354,   354,   113,   115,   783,   166,  -225,   106,    25,
     354,   540,    71,   121,  -225,   122,  -225,  -225,  -225,   119,
     783,   124,  -225,   126,  -225,  -225,  -225,   406,  -225,   129,
     675,   675,   153,   783,   783,   675,  -225,   150,   155,  -225,
     808,   808,   808,   808,   808,   808,   808,   808,   808,   808,
     808,   808,   808,  -225,   567,   702,   182,  -225,   146,  -225,
     144,   140,   783,   354,   783,  -225,  -225,   188,  -225,   175,
      71,    71,   156,   513,   163,   783,    59,   167,  -225,   783,
     169,   783,    -1,   152,  -225,   186,   675,   675,   160,  -225,
     119,   675,   675,  -225,  -225,   783,  -225,  -225,  -225,   783,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,   168,   729,
     173,   171,  -225,  -225,   783,  -225,   783,   170,   179,  -225,
    -225,  -225,   114,   181,  -225,  -225,  -225,   354,  -225,   461,
     354,   201,   204,   187,   354,  -225,   354,  -225,   783,  -225,
     190,   178,   783,   756,   183,  -225,  -225,  -225,  -225,   783,
     191,  -225,   729,  -225,   184,  -225,  -225,   233,   354,   783,
    -225,   354,   175,  -225,  -225,  -225,   234,   198,  -225,   354,
    -225,  -225,  -225,   354,   648,    -8,   808,   211,   756,  -225,
    -225,   191,  -225,   702,   202,   206,  -225,   213,  -225,  -225,
    -225,   354,  -225,  -225,  -225,   783,  -225,  -225,  -225,  -225,
     783,  -225,  -225,   233,   783,   354,  -225,    -8,  -225,  -225,
    -225,  -225,  -225
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     2,     0,     1,     4,     3,     0,   145,    46,
      47,    49,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   146,   148,   149,   150,   151,   153,     0,     0,
       0,     0,     0,     0,     0,     0,    63,     5,    20,    25,
      27,    35,    26,    42,    43,    44,    45,    28,    29,    30,
      21,    59,    60,    61,    62,   162,    86,    90,    93,    95,
     162,    98,   107,   110,   113,   117,   121,   128,   132,   134,
     138,   147,    64,     0,   192,    48,    51,    56,    58,    58,
       0,     0,   188,   188,     0,     0,    94,   138,     0,   140,
     162,   162,     0,   142,     0,     0,   144,   162,   162,     0,
     104,   129,   130,   131,     0,     0,     0,    33,    31,    39,
       0,    88,    91,    41,    96,   105,   108,   111,   114,   118,
     122,     0,   136,   152,     0,     0,   190,     0,     0,    53,
      54,     0,     0,   185,   183,     0,     0,    81,     0,   135,
       0,     0,     0,   156,   154,   159,   157,   139,   141,   207,
       0,   201,   199,   204,   202,   143,    23,     0,    32,    37,
       0,    38,     0,     0,     0,    40,   100,     0,   102,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,     0,     0,     0,   137,    19,    10,
       0,    17,     0,     0,   189,    50,    55,     0,    67,    69,
     184,   182,     0,     0,     0,    80,    69,     0,   210,     0,
       0,     0,   219,     0,   214,     0,   155,   158,   198,   196,
     207,   200,   203,    22,    24,     0,    34,   160,   161,     0,
      89,    92,   101,   103,    97,   106,   109,   112,   115,   116,
     119,   120,   127,   123,   124,   125,   126,   164,     0,   179,
     171,     0,   170,   166,     0,     9,     0,    14,     0,     8,
     191,    57,    69,     0,    70,   187,   186,     0,    84,     0,
       0,    79,    77,     0,     0,   217,     0,   218,     0,   215,
       0,   212,     0,   197,   195,   193,    36,    85,   163,   181,
     177,   178,   175,   165,   168,    18,    17,    13,     0,     0,
      65,     0,    69,    82,    83,    73,     0,     0,    72,     0,
      75,   209,   216,     0,   211,   223,     0,     0,   194,   180,
     176,   173,   174,   167,    12,    16,     7,     0,    68,    71,
      78,     0,    74,   208,   213,     0,   222,   220,   221,   206,
       0,   172,   169,    11,     0,     0,    76,   225,    87,   205,
      15,    66,   224
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,  -225,  -225,  -225,  -225,  -225,   -33,   141,  -193,
       1,  -225,   109,  -225,  -225,  -225,   108,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,   192,  -225,  -225,  -225,  -197,
    -225,  -225,  -225,  -225,  -225,    67,  -110,  -225,   -11,  -225,
    -103,  -225,   112,  -225,   -12,  -225,  -225,  -225,     7,   -15,
    -225,   116,  -225,   102,  -225,   107,  -225,   -37,  -225,   -36,
    -225,    68,  -225,  -225,   189,   248,  -225,   247,   -20,  -225,
    -225,  -225,   -44,  -224,   142,   199,   -73,  -225,  -225,    65,
    -225,   110,  -225,   -31,   -61,   -64,  -225
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,     3,    36,   125,   190,   257,   325,    37,
     137,   104,    39,    40,   107,   108,    41,    42,    43,    44,
      45,    46,    47,    48,    49,   129,    50,    51,   262,   264,
      52,    53,    54,   206,   308,   207,   138,   269,    55,   347,
      56,   111,    57,   112,    58,    59,   114,   170,    60,    61,
     115,    62,   116,    63,   117,    64,   118,    65,   119,    66,
     120,    67,    68,    69,   122,    70,    71,    92,   109,   187,
     251,   294,   252,   291,    84,   133,    75,   126,    99,   218,
      72,   213,   281,   214,   336,   337,   338
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    76,    77,    83,    38,    80,    81,   162,    86,   272,
     268,     8,   335,    95,   156,   192,   142,   100,    90,    90,
      97,   198,   199,   142,   105,    82,   144,   146,   188,   140,
     208,   141,   158,   152,   154,    20,    91,    91,    98,     4,
     113,    21,    22,    23,    24,    25,    26,    27,   176,   177,
     142,    29,   193,    30,   278,    31,    96,    32,   157,   106,
      33,    34,   202,    73,    35,   300,   320,   178,   322,   189,
     143,   145,   150,   184,    78,   185,   304,   151,   153,     8,
     149,   263,    85,   259,   179,   219,    79,   205,    88,   180,
     181,   186,   182,   110,    74,   159,   121,   341,   174,   175,
     166,   101,   102,   103,   123,   329,   167,   168,   169,    21,
      22,    23,    24,    25,    26,    27,   195,   196,   124,    29,
     127,    30,   131,    31,    74,    32,   135,    83,    33,    34,
     212,   128,    35,   204,   205,   299,   263,   238,   239,   220,
     240,   241,   132,   142,   147,   148,   155,   160,   279,    82,
     227,   163,   231,   161,   227,   234,   285,   302,   164,   165,
     305,   194,   172,   171,   310,   173,   311,   197,   228,   200,
     203,   201,   228,   212,   250,   229,   232,   216,   217,   315,
     221,   258,   222,   260,   225,   266,   266,   233,   326,   183,
     253,   328,   254,   255,   271,   256,   261,   263,   275,   332,
     277,   280,   267,   333,    38,   227,   227,   265,   265,   270,
     227,   227,   282,   274,   286,   276,   283,   288,   287,   292,
       8,   346,   293,   228,   228,   298,   297,   301,   228,   228,
     306,   307,   348,   309,   314,   351,   313,   289,   290,   318,
     323,   188,   330,   295,   331,   296,   242,   243,   244,   245,
     246,    22,    23,    24,    25,    26,    27,   340,   343,   345,
      29,   344,    30,   324,    31,   191,   224,   312,   226,    87,
      38,   130,   317,   273,   236,   230,   139,    94,   319,   342,
     237,   321,   134,   334,   215,   284,   352,   235,   327,     0,
       0,     0,     0,     0,   248,     0,     0,     0,     0,     0,
       0,   339,     0,   212,     0,     5,     0,   317,     6,     7,
       8,     0,   250,     0,     9,    10,    11,    12,     0,    13,
      14,    15,    16,     0,     0,    17,    18,    19,     0,   349,
       0,     0,     0,   350,    20,     0,     0,     0,     0,     0,
      21,    22,    23,    24,    25,    26,    27,    28,     0,     0,
      29,     0,    30,     0,    31,     0,    32,   136,     0,    33,
      34,     0,     8,    35,     0,     0,     9,    10,    11,    12,
       0,    13,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,     0,
       0,     0,    21,    22,    23,    24,    25,    26,    27,     0,
       0,     0,    29,     0,    30,     0,    31,     0,    32,   223,
       0,    33,    34,     0,     8,    35,     0,     0,     9,    10,
      11,    12,     0,    13,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,     0,     0,    21,    22,    23,    24,    25,    26,
      27,     0,     0,     0,    29,     0,    30,     0,    31,     0,
      32,     0,     0,    33,    34,     0,   303,    35,     7,     8,
       0,     0,     0,     9,    10,    11,    12,     0,    13,    14,
      15,    16,     0,     0,    17,    18,    19,     0,     0,     0,
       0,     0,     0,    20,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,    26,    27,    28,     0,     0,    29,
       0,    30,     0,    31,     0,    32,     0,     0,    33,    34,
       7,     8,    35,     0,     0,     9,    10,    11,    12,     0,
      13,    14,    15,    16,     0,     0,    17,    18,    19,     0,
       0,     0,     0,     0,     0,    20,     0,     0,     8,     0,
     209,    21,    22,    23,    24,    25,    26,    27,    28,     0,
       0,    29,     0,    30,     0,    31,     0,    32,     0,     0,
      33,    34,    20,     0,    35,     8,     0,   209,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,    29,   210,
      30,     0,    31,     0,   211,     0,     0,    33,    34,    20,
       0,    35,     8,     0,     0,    21,    22,    23,    24,    25,
      26,    27,     0,     0,     0,    29,   247,    30,     0,    31,
       0,   211,     0,     0,    33,    34,    20,     0,    35,     8,
       0,     0,    21,    22,    23,    24,    25,    26,    27,     0,
       0,     0,    29,    89,    30,     0,    31,     0,    32,     0,
       0,    33,    34,    20,     0,    35,     8,     0,   209,    21,
      22,    23,    24,    25,    26,    27,     0,     0,     0,    29,
       0,    30,    93,    31,     0,    32,     0,     0,    33,    34,
      20,     0,    35,     8,     0,     0,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,    29,     0,    30,     0,
      31,     0,   211,     0,     0,    33,    34,    20,     0,    35,
       8,     0,     0,    21,    22,    23,    24,    25,    26,    27,
       0,     0,     0,    29,     0,    30,     0,    31,     0,    32,
       0,     0,    33,    34,    20,     0,    35,     8,     0,     0,
      21,    22,    23,    24,    25,    26,    27,     0,   249,     0,
      29,     0,    30,     0,    31,     0,     0,     0,     0,    33,
      34,    20,     0,    35,     8,     0,   316,    21,    22,    23,
      24,    25,    26,    27,     0,   289,     0,    29,     0,    30,
       0,    31,     0,     0,     0,     0,    33,    34,    20,     0,
      35,     8,     0,     0,    21,    22,    23,    24,    25,    26,
      27,     0,     0,     0,    29,     0,    30,     0,    31,     0,
       0,     0,     0,    33,    34,    20,     8,    35,     0,     0,
       0,    21,    22,    23,    24,    25,    26,    27,     0,     0,
       0,    29,     0,    30,     0,    31,     0,     0,     0,     0,
      33,    34,     0,     0,    35,     0,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,    29,     0,    30,     0,
      31,     0,     0,     0,     0,    33,    34,     0,     0,    35
};

static const yytype_int16 yycheck[] =
{
      11,    12,    13,    18,     3,    16,    17,   110,    20,   206,
     203,     8,    20,    10,     3,     9,    24,    32,    29,    30,
      31,   131,   132,    24,    11,    18,    90,    91,     8,    46,
     140,    48,   105,    97,    98,    32,    29,    30,    31,     0,
      60,    38,    39,    40,    41,    42,    43,    44,    57,    58,
      24,    48,    46,    50,    55,    52,    53,    54,    47,    46,
      57,    58,   135,     8,    61,   262,   290,    37,   292,    49,
      90,    91,    46,    48,     8,    50,   269,    97,    98,     8,
      95,    22,    46,   193,    54,   149,     8,    28,     8,    59,
      60,    66,    62,    20,   105,   106,    10,   321,    35,    36,
      26,    33,    34,    35,    44,   302,    32,    33,    34,    38,
      39,    40,    41,    42,    43,    44,   127,   128,    48,    48,
      16,    50,    46,    52,   135,    54,    26,   142,    57,    58,
     141,    56,    61,    27,    28,    21,    22,   174,   175,   150,
     176,   177,    46,    24,    49,    51,    53,    55,   212,   142,
     161,    31,   164,    56,   165,   170,   220,   267,    30,    56,
     270,    56,    63,    65,   274,    64,   276,    56,   161,    56,
       4,    56,   165,   184,   185,    22,    26,    56,    56,   282,
      56,   192,    56,   194,    55,   200,   201,    32,   298,   121,
       8,   301,    46,    49,   205,    55,     8,    22,   209,   309,
     211,    49,    46,   313,   203,   216,   217,   200,   201,    46,
     221,   222,    26,    46,   225,    46,    56,    49,   229,    46,
       8,   331,    51,   216,   217,    46,    56,    46,   221,   222,
      29,    27,   335,    46,    56,   345,    46,    46,   249,    56,
      56,     8,     8,   254,    46,   256,   178,   179,   180,   181,
     182,    39,    40,    41,    42,    43,    44,    46,    56,    46,
      48,    55,    50,   296,    52,   124,   157,   278,   160,    21,
     269,    79,   283,   206,   172,   163,    87,    30,   289,   323,
     173,   292,    83,   314,   142,   220,   347,   171,   299,    -1,
      -1,    -1,    -1,    -1,   184,    -1,    -1,    -1,    -1,    -1,
      -1,   316,    -1,   314,    -1,     3,    -1,   318,     6,     7,
       8,    -1,   323,    -1,    12,    13,    14,    15,    -1,    17,
      18,    19,    20,    -1,    -1,    23,    24,    25,    -1,   340,
      -1,    -1,    -1,   344,    32,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      48,    -1,    50,    -1,    52,    -1,    54,     3,    -1,    57,
      58,    -1,     8,    61,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    48,    -1,    50,    -1,    52,    -1,    54,     3,
      -1,    57,    58,    -1,     8,    61,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,
      54,    -1,    -1,    57,    58,    -1,     5,    61,     7,     8,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      19,    20,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    48,
      -1,    50,    -1,    52,    -1,    54,    -1,    -1,    57,    58,
       7,     8,    61,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    -1,    -1,    23,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,     8,    -1,
      10,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    48,    -1,    50,    -1,    52,    -1,    54,    -1,    -1,
      57,    58,    32,    -1,    61,     8,    -1,    10,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    48,    49,
      50,    -1,    52,    -1,    54,    -1,    -1,    57,    58,    32,
      -1,    61,     8,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      -1,    54,    -1,    -1,    57,    58,    32,    -1,    61,     8,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    -1,    54,    -1,
      -1,    57,    58,    32,    -1,    61,     8,    -1,    10,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    48,
      -1,    50,    51,    52,    -1,    54,    -1,    -1,    57,    58,
      32,    -1,    61,     8,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    48,    -1,    50,    -1,
      52,    -1,    54,    -1,    -1,    57,    58,    32,    -1,    61,
       8,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,    54,
      -1,    -1,    57,    58,    32,    -1,    61,     8,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    46,    -1,
      48,    -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    57,
      58,    32,    -1,    61,     8,    -1,    10,    38,    39,    40,
      41,    42,    43,    44,    -1,    46,    -1,    48,    -1,    50,
      -1,    52,    -1,    -1,    -1,    -1,    57,    58,    32,    -1,
      61,     8,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,
      -1,    -1,    -1,    57,    58,    32,     8,    61,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    61,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    48,    -1,    50,    -1,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    68,    69,    70,     0,     3,     6,     7,     8,    12,
      13,    14,    15,    17,    18,    19,    20,    23,    24,    25,
      32,    38,    39,    40,    41,    42,    43,    44,    45,    48,
      50,    52,    54,    57,    58,    61,    71,    76,    77,    79,
      80,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      93,    94,    97,    98,    99,   105,   107,   109,   111,   112,
     115,   116,   118,   120,   122,   124,   126,   128,   129,   130,
     132,   133,   147,     8,   105,   143,   105,   105,     8,     8,
     105,   105,   115,   116,   141,    46,   111,   132,     8,    49,
     105,   115,   134,    51,   134,    10,    53,   105,   115,   145,
     116,   128,   128,   128,    78,    11,    46,    81,    82,   135,
      20,   108,   110,   135,   113,   117,   119,   121,   123,   125,
     127,    10,   131,    44,    48,    72,   144,    16,    56,    92,
      92,    46,    46,   142,   142,    26,     3,    77,   103,   131,
      46,    48,    24,   135,   152,   135,   152,    49,    51,   116,
      46,   135,   152,   135,   152,    53,     3,    47,   143,   105,
      55,    56,   107,    31,    30,    56,    26,    32,    33,    34,
     114,    65,    63,    64,    35,    36,    57,    58,    37,    54,
      59,    60,    62,   128,    48,    50,    66,   136,     8,    49,
      73,    75,     9,    46,    56,   105,   105,    56,   103,   103,
      56,    56,   143,     4,    27,    28,   100,   102,   103,    10,
      49,    54,   105,   148,   150,   141,    56,    56,   146,   152,
     105,    56,    56,     3,    79,    55,    83,   105,   115,    22,
     109,   111,    26,    32,   116,   118,   120,   122,   124,   124,
     126,   126,   128,   128,   128,   128,   128,    49,   148,    46,
     105,   137,   139,     8,    46,    49,    55,    74,   105,   103,
     105,     8,    95,    22,    96,   115,   116,    46,    76,   104,
      46,   105,    96,   102,    46,   105,    46,   105,    55,   152,
      49,   149,    26,    56,   146,   152,   105,   105,    49,    46,
     105,   140,    46,    51,   138,   105,   105,    56,    46,    21,
      96,    46,   103,     5,    76,   103,    29,    27,   101,    46,
     103,   103,   105,    46,    56,   107,    10,   105,    56,   105,
     140,   105,   140,    56,    74,    75,   103,   105,   103,    96,
       8,    46,   103,   103,   150,    20,   151,   152,   153,   116,
      46,   140,   139,    56,    55,    46,   103,   106,   107,   105,
     105,   103,   151
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    73,    73,    74,    74,    74,    75,    75,
      76,    76,    77,    77,    78,    78,    79,    79,    79,    79,
      79,    80,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    83,    84,    84,    84,    84,    85,    86,    87,    87,
      88,    88,    88,    89,    90,    91,    91,    92,    92,    93,
      93,    93,    93,    93,    93,    94,    95,    95,    96,    96,
      97,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     102,   103,   103,   104,   104,   105,   105,   106,   107,   108,
     108,   109,   110,   110,   111,   111,   112,   113,   113,   114,
     114,   114,   114,   114,   115,   116,   117,   117,   118,   119,
     119,   120,   121,   121,   122,   123,   123,   123,   124,   125,
     125,   125,   126,   127,   127,   127,   127,   127,   127,   128,
     128,   128,   128,   129,   129,   130,   130,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   133,   133,   134,   134,   134,   134,   134,   134,
     135,   135,   135,   136,   136,   136,   136,   137,   137,   138,
     138,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     140,   140,   141,   141,   141,   141,   142,   142,   142,   143,
     143,   144,   144,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   146,   146,   146,   147,   147,
     147,   148,   148,   149,   149,   150,   150,   150,   150,   150,
     151,   151,   152,   152,   153,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     7,     5,     3,
       2,     5,     4,     3,     2,     5,     3,     0,     3,     1,
       1,     1,     4,     3,     3,     0,     1,     1,     1,     1,
       1,     2,     3,     2,     3,     0,     4,     2,     3,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       4,     2,     1,     3,     3,     4,     2,     3,     0,     1,
       1,     1,     1,     1,     1,     6,     5,     0,     3,     0,
       5,     7,     6,     6,     4,     3,     3,     0,     4,     2,
       1,     1,     4,     2,     1,     5,     1,     1,     2,     3,
       0,     2,     3,     0,     2,     1,     2,     3,     0,     1,
       1,     2,     1,     2,     2,     2,     3,     0,     2,     3,
       0,     2,     3,     0,     2,     3,     3,     0,     2,     3,
       3,     0,     2,     3,     3,     3,     3,     3,     0,     2,
       2,     2,     1,     3,     1,     3,     2,     2,     0,     3,
       2,     3,     2,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     3,     2,     2,     3,     2,
       3,     3,     0,     3,     2,     3,     2,     3,     2,     3,
       0,     1,     4,     3,     3,     2,     3,     2,     2,     1,
       2,     1,     3,     2,     3,     2,     3,     3,     0,     3,
       2,     3,     0,     4,     5,     4,     3,     4,     3,     2,
       3,     2,     2,     3,     2,     5,     4,     0,     7,     6,
       4,     3,     2,     3,     0,     2,     3,     2,     2,     1,
       1,     1,     5,     4,     3,     2
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: file_input  */
#line 241 "parse.y"
                           {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: Parse Success\n");
                if(AST_DEBUG_INSIDE_VERBOSE) printf("[AST]: Root Node for the AST build\n");
                
                // For AST the start symbol is ignored as it has no special semantic meaning.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("start" , 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "start.1";
                
                // Generate the AST or Parse Tree for the program
                root = (yyval.ast); // Set the root node of the Parse Tree or the AST.
                
                if(isAST == true && AST_STRUCTURE_DEBUG == 0) {
                        // Simplifications into AST to get a compact structure
                        root = simplify_ast(root);
                }

                // Write a result into a dot file to generate PDF
                int result = writeTree(root, getNewId(), dotfile_path, astfile_path, parsefile_path);
                if(AST_DEBUG_INSIDE_VERBOSE) printf("[AST]: AST and Parse Tree built\n");

                // Set the column number and line number for the non-terminal
                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;

                return result;
        }
#line 1809 "parse.tab.c"
    break;

  case 3: /* file_input: continued_file_input ENDMARKER  */
#line 274 "parse.y"
                                       {
                // Grammar contains ENDMARKER to mark completion of parsing process returned when lexer reads an <<EOF>> token.
                // From perspective of AST this is not an important node and this leads to an extra awkward looking top
                // portion of the tree. Thus the node corresponding to "ENDMARKER" is ignored for building AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("file_input", 2,
                                (yyvsp[-1].ast),
                                createNode("ENDMARKER", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = (yyvsp[-1].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "file_input.1";

        }
#line 1831 "parse.tab.c"
    break;

  case 4: /* continued_file_input: continued_file_input NEWLINE  */
#line 294 "parse.y"
                                     {
                // For AST we can ignore the NEWLINE as it has no special semantic meaning.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_file_input", 2,
                                (yyvsp[-1].ast),
                                createNode("NEWLINE", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = (yyvsp[-1].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_file_input.1";
        }
#line 1850 "parse.tab.c"
    break;

  case 5: /* continued_file_input: continued_file_input stmt  */
#line 308 "parse.y"
                                    {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: NEXT STATEMENT TO COME UP\n\n");
                
                // No direct simplification is possible here.
                (yyval.ast) = processNodes("continued_file_input" , 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_file_input.2";
        }
#line 1868 "parse.tab.c"
    break;

  case 6: /* continued_file_input: %empty  */
#line 321 "parse.y"
                 { 
                // This kind of a node will automatically be ignored by the AST in processNodes.
                (yyval.ast) = processNodes("continued_file_input", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_file_input.3";
        }
#line 1881 "parse.tab.c"
    break;

  case 7: /* funcdef: DEF NAME parameters RIGHTARROW test COLON suite  */
#line 334 "parse.y"
                                                        {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: funcdef non-terminal used\n");
                
                // DEF and RIGHTARROW can be identified as operators and propogated up in AST
                // COLON does not add any special semantic meaning so it can be ignored
                // Please see special handling of function definitions in "processNodes"
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("funcdef", 7,
                                createNode("DEF", (yyvsp[-6].lexeme)),
                                createNode("NAME",(yyvsp[-5].lexeme)),
                                (yyvsp[-4].ast),
                                createNode("RIGHTARROW", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("funcdef", 4,
                                createNode("NAME", (yyvsp[-5].lexeme)),
                                (yyvsp[-4].ast),
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-6].lexeme)) + "$" + string((yyvsp[-3].lexeme));
                }

                // A function definitions is a declaration statement so SYMBOL TABLE ENTRY is to be generated for this
                // A function will have the type parameters -> test in this case
                // ($$->T) = type_function($3->T, $5->T);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "funcdef.1";

        }
#line 1922 "parse.tab.c"
    break;

  case 8: /* funcdef: DEF NAME parameters COLON suite  */
#line 370 "parse.y"
                                           {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: funcdef non-terminal used\n");

                // DEF can be identified as operators and propogated up in AST
                // COLON does not add any special semantic meaning so it can be ignored
                // Please see special handling of function definitions in "processNodes"
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("funcdef", 5,
                                createNode("DEF", (yyvsp[-4].lexeme)),
                                createNode("NAME",(yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("COLON",(yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("funcdef", 3,
                                createNode("NAME",(yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-4].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "funcdef.2";
        }
#line 1955 "parse.tab.c"
    break;

  case 9: /* parameters: OPENING_BRACKET typedargslist CLOSING_BRACKET  */
#line 401 "parse.y"
                                                      {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("parameters", 3,
                                createNode("OPENING_BRACKET",(yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("CLOSING_BRACKET",(yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "parameters";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "parameters.1";
        }
#line 1977 "parse.tab.c"
    break;

  case 10: /* parameters: OPENING_BRACKET CLOSING_BRACKET  */
#line 418 "parse.y"
                                          {
                // Empty brackets do not have any such semantic significance in general.
                // But this non-terminal denotes parameters of a function so better to keep an empty string for parameters here.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("parameters" , 2,
                                createNode("OPENING_BRACKET", (yyvsp[-1].lexeme)),
                                createNode("CLOSING_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // Construct a node with empty brackets to indicate empty brackets in AST
                        (yyval.ast) = createNode("parameters", " " + string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)) + " ");
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "parameters.2";
        }
#line 2000 "parse.tab.c"
    break;

  case 11: /* typedargslist: tfpdef EQUAL test next_arg COMMA  */
#line 439 "parse.y"
                                         {
                // COMMA ignored as it has no semantic significance for AST.
                // Right recursive productions can be simplified to a single level in AST.
                // EQUAL can be identified as an operator and can be propogated up for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("typedargslist", 5,
                                (yyvsp[-4].ast),
                                createNode("EQUAL", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "typedargslist";
                        ASTNode* node = processNodes("EQUAL", 2, (yyvsp[-4].ast), (yyvsp[-2].ast));
                        (node->content) = string((yyvsp[-3].lexeme));
                        ((yyval.ast)->children).push_front(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "typedargslist.1";
        }
#line 2030 "parse.tab.c"
    break;

  case 12: /* typedargslist: tfpdef EQUAL test next_arg  */
#line 464 "parse.y"
                                     {
                // Right recursive productions can be simplified to a single level in AST.
                // EQUAL can be identified as an operator and can be propogated up for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("typedargslist", 4,
                                (yyvsp[-3].ast),
                                createNode("EQUAL", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "typedargslist";
                        ASTNode* node = processNodes("EQUAL", 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
                        (node->content) = string((yyvsp[-2].lexeme));
                        ((yyval.ast)->children).push_front(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "typedargslist.2";
        }
#line 2058 "parse.tab.c"
    break;

  case 13: /* typedargslist: tfpdef next_arg COMMA  */
#line 487 "parse.y"
                                {
                // COMMA ignored as it has no semantic significance for AST.
                // Right recursive productions can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("typedargslist", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "typedargslist";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "typedargslist.3";
        }
#line 2083 "parse.tab.c"
    break;

  case 14: /* typedargslist: tfpdef next_arg  */
#line 507 "parse.y"
                          {
                // Right recursive productions can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("typedargslist", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "typedargslist";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "typedargslist.4";
        }
#line 2106 "parse.tab.c"
    break;

  case 15: /* next_arg: next_arg COMMA tfpdef EQUAL test  */
#line 528 "parse.y"
                                         {
                // Left recursive productions can be simplified to a single level in AST.
                // COMMA has no semantic meaning so it can be ignored
                // EQUAL can be identified as an operator and can be propogated up for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("next_arg" ,5,
                                (yyvsp[-4].ast),
                                createNode("COMMA", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("EQUAL", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-4].ast);
                        ASTNode* node = processNodes("EQUAL", 2, (yyvsp[-2].ast), (yyvsp[0].ast));
                        (node->content) = string((yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_back(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "next_arg.1";
        }
#line 2135 "parse.tab.c"
    break;

  case 16: /* next_arg: next_arg COMMA tfpdef  */
#line 552 "parse.y"
                                {
                // Left recursive productions can be simplified to a single level in AST.
                // COMMA has no semantic meaning so it can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("next_arg" ,3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "next_arg.2";
        }
#line 2159 "parse.tab.c"
    break;

  case 17: /* next_arg: %empty  */
#line 571 "parse.y"
                 {
                // Will be ignored automatically for AST
                (yyval.ast) = processNodes("next_arg", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "next_arg.3";
        }
#line 2172 "parse.tab.c"
    break;

  case 18: /* tfpdef: NAME COLON test  */
#line 583 "parse.y"
                        {
                // COLON can be identified as an operator and moved up here for simplifying the AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("tfpdef", 3,
                                createNode("NAME", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("tfpdef", 2,
                                createNode("NAME", (yyvsp[-2].lexeme)),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "tfpdef.1";
        }
#line 2198 "parse.tab.c"
    break;

  case 19: /* tfpdef: NAME  */
#line 604 "parse.y"
                { // #notrequired
                // This is just like tfpdef is a terminal for the AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("tfpdef", 1,
                                createNode("NAME", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("NAME", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "tfpdef.2";
        }
#line 2216 "parse.tab.c"
    break;

  case 20: /* stmt: simple_stmt  */
#line 624 "parse.y"
                      {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: simple_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "stmt.1";
        }
#line 2231 "parse.tab.c"
    break;

  case 21: /* stmt: compound_stmt  */
#line 634 "parse.y"
                        {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: compound_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "stmt.2";
        }
#line 2246 "parse.tab.c"
    break;

  case 22: /* simple_stmt: small_stmt next_small_stmt SEMI_COLON NEWLINE  */
#line 647 "parse.y"
                                                      {
                // Right recursive productions can be simplified to a single level in AST
                // SEMI_COLON and NEWLINE place no semantic meaning except statement seperation so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("simple_stmt", 4,
                                (yyvsp[-3].ast),
                                (yyvsp[-2].ast),
                                createNode("SEMI_COLON", (yyvsp[-1].lexeme)),
                                createNode("NEWLINE", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->type) = "simple_stmt";
                        ((yyval.ast)->children).push_front((yyvsp[-3].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "simple_stmt.1";
        }
#line 2272 "parse.tab.c"
    break;

  case 23: /* simple_stmt: small_stmt next_small_stmt NEWLINE  */
#line 668 "parse.y"
                                             {
                // Right recursive productions can be simplified to a single level in AST
                // NEWLINE place no semantic meaning except statement seperation so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("simple_stmt", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("NEWLINE", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "simple_stmt";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "simple_stmt.2";
        }
#line 2297 "parse.tab.c"
    break;

  case 24: /* next_small_stmt: next_small_stmt SEMI_COLON small_stmt  */
#line 691 "parse.y"
                                              {
                // Left recursive productions can be simplified to a single level in AST
                // SEMI_COLON is just a seperator and does not have much semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("next_small_stmt", 3,
                                (yyvsp[-2].ast),
                                createNode("SEMI_COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "next_small_stmt.1";
        }
#line 2321 "parse.tab.c"
    break;

  case 25: /* next_small_stmt: %empty  */
#line 710 "parse.y"
                 {
                // This will be automatically ignored by "processNodes" for an AST
                (yyval.ast) = processNodes("next_small_stmt", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "next_small_stmt.2";
        }
#line 2334 "parse.tab.c"
    break;

  case 26: /* small_stmt: flow_stmt  */
#line 721 "parse.y"
                  {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("small_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "small_stmt.1";
        }
#line 2349 "parse.tab.c"
    break;

  case 27: /* small_stmt: expr_stmt  */
#line 731 "parse.y"
                    {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: expr_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("small_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "small_stmt.2";
        }
#line 2364 "parse.tab.c"
    break;

  case 28: /* small_stmt: global_stmt  */
#line 741 "parse.y"
                      {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("small_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "small_stmt.3";
        }
#line 2377 "parse.tab.c"
    break;

  case 29: /* small_stmt: nonlocal_stmt  */
#line 749 "parse.y"
                        {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("small_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "small_stmt.4";
        }
#line 2390 "parse.tab.c"
    break;

  case 30: /* small_stmt: assert_stmt  */
#line 757 "parse.y"
                      { // #notrequired
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("small_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "small_stmt.5";
        }
#line 2403 "parse.tab.c"
    break;

  case 31: /* expr_stmt: testlist_star_expr annassign  */
#line 772 "parse.y"
                                      {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: annotated assignment in expr_stmt\n");
                
                // It can be observed here that "annassign" is the operator and we can make "testlist_star_expr" a child
                // of "annassign" as a simplification for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("expr_stmt", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "expr_stmt";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "expr_stmt.1";
        }
#line 2429 "parse.tab.c"
    break;

  case 32: /* expr_stmt: testlist_star_expr AUGASSIGN testlist  */
#line 793 "parse.y"
                                                {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: augmented assignment in expr_stmt\n");
                
                // It can be observed here that AUGASSIGN is the operator which can be propagated for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("expr_stmt", 3,
                                (yyvsp[-2].ast),
                                createNode("AUGASSIGN", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("expr_stmt", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "expr_stmt.2";
        }
#line 2457 "parse.tab.c"
    break;

  case 33: /* expr_stmt: testlist_star_expr continued_expr_stmt  */
#line 816 "parse.y"
                                                 {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: normal assignment in expr_stmt\n");
                
                // Right recursive productions can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("expr_stmt",2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "expr_stmt";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "expr_stmt.3";
        }
#line 2482 "parse.tab.c"
    break;

  case 34: /* continued_expr_stmt: continued_expr_stmt EQUAL testlist_star_expr  */
#line 839 "parse.y"
                                                     {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: testlist added\n");
                
                // Left recursive production can be simplified in AST and shown on a single level
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_expr_stmt", 3,
                                (yyvsp[-2].ast),
                                createNode("EQUAL", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                        if( ((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON ) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + string((yyvsp[-1].lexeme));
                        else ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_expr_stmt.1";
        }
#line 2509 "parse.tab.c"
    break;

  case 35: /* continued_expr_stmt: %empty  */
#line 861 "parse.y"
                 {
                // Will be automatically ignored by "processNodes" for AST
                (yyval.ast) = processNodes("continued_expr_stmt", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_expr_stmt.2";
        }
#line 2522 "parse.tab.c"
    break;

  case 36: /* annassign: COLON test EQUAL test  */
#line 872 "parse.y"
                              {
                // COLON and EQUAL can be considered as operator here and propogated upwards for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("annassign", 4,
                                createNode("COLON", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("EQUAL", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("annassign", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme)) + "$" + string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "annassign.1";
        }
#line 2549 "parse.tab.c"
    break;

  case 37: /* annassign: COLON test  */
#line 894 "parse.y"
                     {
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually feel like an conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("annassign", 2,
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("annassign", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "annassign.2";
        }
#line 2572 "parse.tab.c"
    break;

  case 38: /* testlist_star_expr: test continued_testlist COMMA  */
#line 915 "parse.y"
                                      {
                // COMMA can be ignored in AST as it has no significant semantic meaning
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_star_expr", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "testlist_star_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_star_expr.1";
        }
#line 2597 "parse.tab.c"
    break;

  case 39: /* testlist_star_expr: test continued_testlist  */
#line 935 "parse.y"
                                  {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: single test in testlist\n");
                
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_star_expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "testlist_star_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_star_expr.2";
        }
#line 2622 "parse.tab.c"
    break;

  case 40: /* testlist_star_expr: star_expr continued_testlist COMMA  */
#line 955 "parse.y"
                                             { // #notrequired
                // COMMA can be ignored in AST as it has no significant semantic meaning
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_star_expr", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "testlist_star_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_star_expr.3";
        }
#line 2647 "parse.tab.c"
    break;

  case 41: /* testlist_star_expr: star_expr continued_testlist  */
#line 975 "parse.y"
                                       {// #notrequired
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_star_expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "testlist_star_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_star_expr.4";
        }
#line 2670 "parse.tab.c"
    break;

  case 42: /* flow_stmt: break_stmt  */
#line 996 "parse.y"
                   {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: break_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("flow_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "flow_stmt.1";
        }
#line 2685 "parse.tab.c"
    break;

  case 43: /* flow_stmt: continue_stmt  */
#line 1006 "parse.y"
                        {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: continue_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("flow_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "flow_stmt.2";
        }
#line 2700 "parse.tab.c"
    break;

  case 44: /* flow_stmt: return_stmt  */
#line 1016 "parse.y"
                      {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: return_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("flow_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "flow_stmt.3";
        }
#line 2715 "parse.tab.c"
    break;

  case 45: /* flow_stmt: raise_stmt  */
#line 1026 "parse.y"
                     { // #notrequired
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: raise_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("flow_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "flow_stmt.4";
        }
#line 2730 "parse.tab.c"
    break;

  case 46: /* break_stmt: BREAK  */
#line 1039 "parse.y"
              {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("break_stmt", 1,
                                createNode("BREAK", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("break_stmt", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "break_stmt.1";
        }
#line 2748 "parse.tab.c"
    break;

  case 47: /* continue_stmt: CONTINUE  */
#line 1055 "parse.y"
                 {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continue_stmt", 1,
                                createNode("CONTINUE", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("continue_stmt", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continue_stmt.1";

        }
#line 2767 "parse.tab.c"
    break;

  case 48: /* return_stmt: RETURN testlist  */
#line 1072 "parse.y"
                        {
                // This is a tough case. Here RETURN is a unary operator and thus we cannot directly
                // add RETURN in the "content" of "testlist" node -> That would actually feel like part of testing expression list.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("return_stmt", 2,
                                createNode("RETURN", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("return_stmt", 1, (yyvsp[0].ast));
                        // $$ = $2;
                        // ($$->type) = "return_stmt";
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "return_stmt.1";
        }
#line 2792 "parse.tab.c"
    break;

  case 49: /* return_stmt: RETURN  */
#line 1092 "parse.y"
                 {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("return_stmt", 1,
                                createNode("RETURN", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("return_stmt", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "return_stmt.2";
        }
#line 2810 "parse.tab.c"
    break;

  case 50: /* raise_stmt: RAISE test FROM test  */
#line 1109 "parse.y"
                             {
                // RAISE and FROM can be seen as operators and propogated upward in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("raise_stmt", 4,
                                createNode("RAISE", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("FROM", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("raise_stmt", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme)) + "$" + string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "raise_stmt.1";
        }
#line 2837 "parse.tab.c"
    break;

  case 51: /* raise_stmt: RAISE test  */
#line 1131 "parse.y"
                     {
                // This is a tough case. Here RAISE is a unary operator and thus we cannot directly
                // add RAISE in the "content" of "test" node -> That would actually feel like part of conditional test.
                // RAISE can be seen as operators and propogated upward in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("raise_stmt", 2,
                                createNode("RAISE", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("raise_stmt", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "raise_stmt.2";
        }
#line 2861 "parse.tab.c"
    break;

  case 52: /* raise_stmt: RAISE  */
#line 1150 "parse.y"
                {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("raise_stmt", 1,
                                createNode("RAISE", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("raise_stmt", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "raise_stmt.3";
        }
#line 2879 "parse.tab.c"
    break;

  case 53: /* global_stmt: GLOBAL NAME stmt_helper  */
#line 1166 "parse.y"
                                {
                // GLOBAL can be identified as the operator here and kept at top.
                // This is a right recursive production so can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("global_stmt", 3,
                                createNode("GLOBAL", (yyvsp[-2].lexeme)),
                                createNode("NAME", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "global_stmt";
                        ASTNode* node = createNode("NAME", (yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_front(node);
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "global_stmt.1";
        }
#line 2906 "parse.tab.c"
    break;

  case 54: /* nonlocal_stmt: NONLOCAL NAME stmt_helper  */
#line 1192 "parse.y"
                                  {
                // NONLOCAL can be identified as the operator here and kept at top.
                // This is a right recursive production so can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("nonlocal_stmt", 3,
                                createNode("NONLOCAL", (yyvsp[-2].lexeme)),
                                createNode("NAME", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "nonlocal_stmt";
                        ASTNode* node = createNode("NAME", (yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_front(node);
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "nonlocal_stmt.1";
        }
#line 2933 "parse.tab.c"
    break;

  case 55: /* assert_stmt: ASSERT test COMMA test  */
#line 1218 "parse.y"
                               {
                // ASSERT and COMMA are operators so can be propogated upwards.
                // COMMA has no significant semantic meaning so it can be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("assert_smt", 4,
                                createNode("ASSERT", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("assert_smt", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "assert_stmt.1";
        }
#line 2961 "parse.tab.c"
    break;

  case 56: /* assert_stmt: ASSERT test  */
#line 1241 "parse.y"
                      {
                // This is a tough case. Here ASSERT is a unary operator and thus we cannot directly
                // add ASSERT in the "content" of "test" node -> That would actually look like a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("assert_stmt", 2,
                                createNode("ASSERT", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("assert_stmt", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "assert_stmt.2";
        }
#line 2984 "parse.tab.c"
    break;

  case 57: /* stmt_helper: stmt_helper COMMA NAME  */
#line 1262 "parse.y"
                               {
                // Left recursive productions can be simplified to a single level in AST
                // COMMA has no semantic meaning so it can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("stmt_helper", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                createNode("NAME", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ASTNode* node = createNode("NAME", (yyvsp[0].lexeme));
                        ((yyval.ast)->children).push_back(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "stmt_helper.1";
        }
#line 3009 "parse.tab.c"
    break;

  case 58: /* stmt_helper: %empty  */
#line 1282 "parse.y"
                 {
                // Will be ignored by "processNodes" for AST
                (yyval.ast) = processNodes("stmt_helper", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "stmt_helper.2";
        }
#line 3022 "parse.tab.c"
    break;

  case 59: /* compound_stmt: if_stmt  */
#line 1295 "parse.y"
                 {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: if_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("compound_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "compound_stmt.1";
        }
#line 3037 "parse.tab.c"
    break;

  case 60: /* compound_stmt: while_stmt  */
#line 1305 "parse.y"
                     {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: while_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("compound_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "compound_stmt.2";
        }
#line 3052 "parse.tab.c"
    break;

  case 61: /* compound_stmt: for_stmt  */
#line 1315 "parse.y"
                   {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: for_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("compound_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "compound_stmt.3";
        }
#line 3067 "parse.tab.c"
    break;

  case 62: /* compound_stmt: try_stmt  */
#line 1325 "parse.y"
                   { // #notrequired
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: try_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("compound_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "compound_stmt.4";
        }
#line 3082 "parse.tab.c"
    break;

  case 63: /* compound_stmt: funcdef  */
#line 1335 "parse.y"
                  {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: func_def selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("compound_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "compound_stmt.5";
        }
#line 3097 "parse.tab.c"
    break;

  case 64: /* compound_stmt: classdef  */
#line 1345 "parse.y"
                   {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: class_def selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("compound_stmt", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "compound_stmt.6";
        }
#line 3112 "parse.tab.c"
    break;

  case 65: /* if_stmt: IF test COLON suite elif_stmt else_stmt  */
#line 1358 "parse.y"
                                                {
                // IF can be propogated as operator and COLON can be ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("if_stmt", 6,
                                createNode("IF", (yyvsp[-5].lexeme)),
                                (yyvsp[-4].ast),
                                createNode("COLON", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("if_stmt", 4,
                                (yyvsp[-4].ast),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-5].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "if_stmt.1";
        }
#line 3143 "parse.tab.c"
    break;

  case 66: /* elif_stmt: elif_stmt ELIF test COLON suite  */
#line 1387 "parse.y"
                                        {
                // ELIF can be propogated as operator and COLON can be ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("elif_stmt", 5,
                                (yyvsp[-4].ast),
                                createNode("ELIF", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("elif_stmt", 3,
                                (yyvsp[-4].ast),
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "elif_stmt.1";
        }
#line 3172 "parse.tab.c"
    break;

  case 67: /* elif_stmt: %empty  */
#line 1411 "parse.y"
                 {
                // Will be ignored by "processNodes" for AST
                (yyval.ast) = processNodes("elif_stmt", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "elif_stmt.2";
        }
#line 3185 "parse.tab.c"
    break;

  case 68: /* else_stmt: ELSE COLON suite  */
#line 1423 "parse.y"
                         {
                // This is a tough case. Here ELSE is a unary operator and thus we cannot directly
                // add ELSE in the "content" of "suite" node -> That would actually feel like a part of expression suite.
                // ELSE can be propogated as operator and COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("else_stmt", 3,
                                createNode("ELSE", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("else_stmt", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                        // Below code works if the operator ELSE is not considered as an unary operator.
                        // $$ = $3;
                        // ($$->type) = "else_stmt";
                        // ($$->content) = string($1);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "else_stmt.1";
        }
#line 3214 "parse.tab.c"
    break;

  case 69: /* else_stmt: %empty  */
#line 1447 "parse.y"
                 {
                // Will be ignored by "processNodes" for AST
                (yyval.ast) = processNodes("else_stmt", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "else_stmt.2";
        }
#line 3227 "parse.tab.c"
    break;

  case 70: /* while_stmt: WHILE test COLON suite else_stmt  */
#line 1458 "parse.y"
                                         {
                // WHILE and COLON are operators. WHILE is propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("while_stmt", 5,
                                createNode("WHILE", (yyvsp[-4].lexeme)),
                                (yyvsp[-3].ast),
                                createNode("COLON", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("while_stmt", 3,
                                (yyvsp[-3].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-4].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "while_stmt.1";
        }
#line 3256 "parse.tab.c"
    break;

  case 71: /* for_stmt: FOR exprlist IN testlist COLON suite else_stmt  */
#line 1537 "parse.y"
                                                       {
                // FOR, IN and COLON are operators. FOR and IN are propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("for_stmt", 7,
                                createNode("FOR", (yyvsp[-6].lexeme)),
                                (yyvsp[-5].ast),
                                createNode("IN", (yyvsp[-4].lexeme)),
                                (yyvsp[-3].ast),
                                createNode("COLON", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("for_stmt", 4,
                                (yyvsp[-5].ast),
                                (yyvsp[-3].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-6].lexeme)) + "$" + string((yyvsp[-4].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "for_stmt.1";
        }
#line 3288 "parse.tab.c"
    break;

  case 72: /* try_stmt: TRY COLON suite except_stmt else_stmt finally_stmt  */
#line 1568 "parse.y"
                                                           {
                // TRY and COLON are operators. TRY is propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("try_stmt", 6,
                                createNode("TRY", (yyvsp[-5].lexeme)),
                                createNode("COLON", (yyvsp[-4].lexeme)),
                                (yyvsp[-3].ast),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("try_stmt", 4,
                                (yyvsp[-3].ast),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-5].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "try_stmt.1";
        }
#line 3319 "parse.tab.c"
    break;

  case 73: /* try_stmt: TRY COLON suite FINALLY COLON suite  */
#line 1594 "parse.y"
                                              {
                // TRY, FINALLY and COLON are operators. TRY and FINALLY are propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("try_stmt", 6,
                                createNode("TRY", (yyvsp[-5].lexeme)),
                                createNode("COLON", (yyvsp[-4].lexeme)),
                                (yyvsp[-3].ast),
                                createNode("FINALLY", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("try_stmt", 2,
                                (yyvsp[-3].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-5].lexeme)) + "$" + string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "try_stmt.2";
        }
#line 3348 "parse.tab.c"
    break;

  case 74: /* except_stmt: except_stmt except_clause COLON suite  */
#line 1622 "parse.y"
                                              {
                // Left recursive production can be simplified to a single level in AST
                // Here COLON is the operator and as it is the only operator so it is not ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("except_stmt",4,
                                (yyvsp[-3].ast),
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-3].ast);
                        ASTNode* node = processNodes("COLON", 2,
                                        (yyvsp[-2].ast),
                                        (yyvsp[0].ast)
                        );
                        (node->content) = string((yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_back(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "except_stmt.1";
        }
#line 3378 "parse.tab.c"
    break;

  case 75: /* except_stmt: except_clause COLON suite  */
#line 1647 "parse.y"
                                    {
                // Here COLON is the operator and as it is the only operator so it is not ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("except_stmt", 3,
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("except_stmt", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "except_stmt.2";
        }
#line 3404 "parse.tab.c"
    break;

  case 76: /* finally_stmt: FINALLY COLON suite  */
#line 1672 "parse.y"
                            {
                // This is a tough case. Here FINALLY is a unary operator and thus we cannot directly
                // add FINALLY in the "content" of "suite" node -> That would actually seem like part of the suite of statements.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("finally_stmt", 3,
                                createNode("FINALLY", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("finally_stmt", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "finally_stmt.1";
        }
#line 3428 "parse.tab.c"
    break;

  case 77: /* finally_stmt: %empty  */
#line 1691 "parse.y"
                   {
                // Will be ignored by "processNodes" for AST
                (yyval.ast) = processNodes("finally_stmt", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "finally_stmt.2";
        }
#line 3441 "parse.tab.c"
    break;

  case 78: /* except_clause: EXCEPT test AS NAME  */
#line 1703 "parse.y"
                            {
                // EXCEPT and AS are operators here and can be propagated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("except_clause", 4,
                                createNode("EXCEPT", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("AS", (yyvsp[-1].lexeme)),
                                createNode("NAME", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = processNodes("except_clause", 2,
                                (yyvsp[-2].ast),
                                createNode("NAME", (yyvsp[0].lexeme))
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme)) + "$" + string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "except_clause.1";
        }
#line 3468 "parse.tab.c"
    break;

  case 79: /* except_clause: EXCEPT test  */
#line 1725 "parse.y"
                      {
                // This is a tough case. Here EXCEPT is a unary operator and thus we cannot directly
                // add EXCEPT in the "content" of "test" node -> That would actually seem like a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("except_clause", 2,
                                createNode("EXCEPT", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("except_clause", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "except_clause.2";
        }
#line 3491 "parse.tab.c"
    break;

  case 80: /* except_clause: EXCEPT  */
#line 1743 "parse.y"
                 {
                // This is just like a terminal for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("except_clause", 1,
                                createNode("EXCEPT", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("EXCEPT", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "except_clause.3";
        }
#line 3509 "parse.tab.c"
    break;

  case 81: /* suite: simple_stmt  */
#line 1759 "parse.y"
                    {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("suite", 1, (yyvsp[0].ast));
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "suite";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "suite.1";
        }
#line 3525 "parse.tab.c"
    break;

  case 82: /* suite: NEWLINE INDENT stmts DEDENT  */
#line 1770 "parse.y"
                                      {
                // INDENT and DEDENT do not add much to semantic meaning so can be ignored
                // NEWLINE does not add any semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("suite", 4,
                                createNode("NEWLINE", (yyvsp[-3].lexeme)),
                                createNode("INDENT", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("DEDENT", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "suite";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "suite.2";
        }
#line 3550 "parse.tab.c"
    break;

  case 83: /* stmts: stmts stmt  */
#line 1793 "parse.y"
                   {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("stmts", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "stmts.1";
        }
#line 3572 "parse.tab.c"
    break;

  case 84: /* stmts: stmt  */
#line 1810 "parse.y"
               {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("stmts", 1, (yyvsp[0].ast));
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "stmts";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "stmts.2";
        }
#line 3588 "parse.tab.c"
    break;

  case 85: /* test: or_test IF or_test ELSE test  */
#line 1824 "parse.y"
                                     {
                // Right recursive productions can be reduced to a single level in AST.
                // However, a test statement can be long in general so better not convert to single level to protect semantic meaning.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("test", 5,
                                (yyvsp[-4].ast),
                                createNode("IF", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("ELSE", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        // It's not necessary that this will make a node $$ with 3 children. See the working of
                        // "processNodes". If $1, $2 or $3 have no children and no content then they will be ignored and
                        // not added as a child to $$ node.
                        (yyval.ast) = processNodes("test", 3,
                                (yyvsp[-4].ast),
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        
                        // The parser semantic actions maintain an invariant that any non-terminal if produces empty string will
                        // have EPSILON in it's contents. Thus, whenever "content" is added to a node after calling "processNodes"
                        // it should be checked whether the number of children of the node is zero or not.
                        // if(($$->children).size() > 0) ($$->content) = string($2) + "$" + string($4);

                        // The above concept is ignored for now - It is may give some issues
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme)) + "$" + string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "test.1";
        }
#line 3628 "parse.tab.c"
    break;

  case 86: /* test: or_test  */
#line 1859 "parse.y"
                  {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("test", 1, (yyvsp[0].ast));
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "test";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "test.2";
        }
#line 3644 "parse.tab.c"
    break;

  case 87: /* test_nocond: or_test  */
#line 1873 "parse.y"
                {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("test_nocond", 1, (yyvsp[0].ast));
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "test_nocond";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "test_nocond.1";
        }
#line 3660 "parse.tab.c"
    break;

  case 88: /* or_test: and_test continued_or_test  */
#line 1887 "parse.y"
                                   {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("or_test", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "or_test";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "or_test.1";
        }
#line 3683 "parse.tab.c"
    break;

  case 89: /* continued_or_test: continued_or_test OR and_test  */
#line 1908 "parse.y"
                                      {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_or_test", 3,
                                (yyvsp[-2].ast),
                                createNode("OR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + string((yyvsp[-1].lexeme));
                        else ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_or_test.1";
        }
#line 3708 "parse.tab.c"
    break;

  case 90: /* continued_or_test: %empty  */
#line 1928 "parse.y"
                 {
                // Will be ignored in AST automatically by processNodes
                (yyval.ast) = processNodes("continued_or_test", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_or_test.2";
        }
#line 3721 "parse.tab.c"
    break;

  case 91: /* and_test: not_test continued_and_test  */
#line 1939 "parse.y"
                                    {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("and_test", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "and_test";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "and_test.1";
        }
#line 3744 "parse.tab.c"
    break;

  case 92: /* continued_and_test: continued_and_test AND not_test  */
#line 1960 "parse.y"
                                        {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_and_test", 3,
                                (yyvsp[-2].ast),
                                createNode("AND", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + string((yyvsp[-1].lexeme));
                        else ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_and_test.1";
        }
#line 3769 "parse.tab.c"
    break;

  case 93: /* continued_and_test: %empty  */
#line 1980 "parse.y"
                 {
                // Will be ignored in AST automatically by processNodes
                (yyval.ast) = processNodes("continued_and_test", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_and_test.2";
        }
#line 3782 "parse.tab.c"
    break;

  case 94: /* not_test: NOT not_test  */
#line 1991 "parse.y"
                     {
                // This is a tough case. Here NOT is a unary operator and thus we cannot directly
                // add NOT in the "content" of "comparison" node -> That would actually feel like included in comparison expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("not_test", 2,
                                createNode("NOT", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("not_test", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "not_test.1";
        }
#line 3805 "parse.tab.c"
    break;

  case 95: /* not_test: comparison  */
#line 2009 "parse.y"
                     {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("not_test", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "not_test.2";
        }
#line 3818 "parse.tab.c"
    break;

  case 96: /* comparison: expr comparison_stmt  */
#line 2020 "parse.y"
                             {
                // A right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comparison", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "comparison";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comparison.1";
        }
#line 3841 "parse.tab.c"
    break;

  case 97: /* comparison_stmt: comparison_stmt comp_op expr  */
#line 2041 "parse.y"
                                     {
                // A left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comparison_stmt", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + ((yyvsp[-1].ast)->content);
                        else ((yyval.ast)->content) = ((yyvsp[-1].ast)->content);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comparison_stmt.1";
        }
#line 3866 "parse.tab.c"
    break;

  case 98: /* comparison_stmt: %empty  */
#line 2061 "parse.y"
                 {
                // Will be ignored by processNodes automatically for AST
                (yyval.ast) = processNodes("comparison_stmt", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comparison_stmt.2";
        }
#line 3879 "parse.tab.c"
    break;

  case 99: /* comp_op: COMP_OP  */
#line 2072 "parse.y"
                {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_op", 1,
                                createNode("COMP_OP", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("COMP_OP", string((yyvsp[0].lexeme)));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_op.1";
        }
#line 3898 "parse.tab.c"
    break;

  case 100: /* comp_op: IN  */
#line 2086 "parse.y"
                {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_op", 1,
                                createNode("IN", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("IN", string((yyvsp[0].lexeme)));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_op.2";
        }
#line 3917 "parse.tab.c"
    break;

  case 101: /* comp_op: NOT IN  */
#line 2100 "parse.y"
                 {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_op", 2,
                                createNode("NOT", (yyvsp[-1].lexeme)),
                                createNode("IN", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("NOT-IN", string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_op.3";
        }
#line 3937 "parse.tab.c"
    break;

  case 102: /* comp_op: IS  */
#line 2115 "parse.y"
                 {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_op", 1,
                                createNode("IS", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("IS", string((yyvsp[0].lexeme)));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_op.4";
        }
#line 3956 "parse.tab.c"
    break;

  case 103: /* comp_op: IS NOT  */
#line 2129 "parse.y"
                 {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_op", 1,
                                createNode("IS", (yyvsp[-1].lexeme)),
                                createNode("NOT", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("IS-NOT", string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_op.5";
        }
#line 3976 "parse.tab.c"
    break;

  case 104: /* star_expr: STAR expr  */
#line 2148 "parse.y"
                   {
                // This is a tough case. Here STAR is a unary operator and thus we cannot directly
                // add STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("star_expr", 2,
                                createNode("STAR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        if(((yyval.ast)->type) == "expr") (yyval.ast) = processNodes("star_expr", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = ((yyval.ast)->content) + " " + string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "star_expr.1";
        }
#line 3999 "parse.tab.c"
    break;

  case 105: /* expr: xor_expr continued_xor_expr  */
#line 2169 "parse.y"
                                    {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "expr.1";
        }
#line 4022 "parse.tab.c"
    break;

  case 106: /* continued_xor_expr: continued_xor_expr BITWISE_OR xor_expr  */
#line 2190 "parse.y"
                                               {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_xor_expr", 3,
                                (yyvsp[-2].ast),
                                createNode("BITWISE_OR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_xor_expr.1";
        }
#line 4047 "parse.tab.c"
    break;

  case 107: /* continued_xor_expr: %empty  */
#line 2210 "parse.y"
                 {
                // Will be ignored automatically in AST by processNodes.
                (yyval.ast) = processNodes("continued_xor_expr", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_xor_expr.2";
        }
#line 4060 "parse.tab.c"
    break;

  case 108: /* xor_expr: and_expr continued_and_expr  */
#line 2221 "parse.y"
                                    {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("xor_expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "xor_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "xor_expr.1";
        }
#line 4083 "parse.tab.c"
    break;

  case 109: /* continued_and_expr: continued_and_expr CARET and_expr  */
#line 2242 "parse.y"
                                          {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_and_expr", 3,
                                (yyvsp[-2].ast),
                                createNode("CARET", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_and_expr.1";
        }
#line 4108 "parse.tab.c"
    break;

  case 110: /* continued_and_expr: %empty  */
#line 2262 "parse.y"
                 {
                // Will be ignored automatically in AST by processNodes.
                (yyval.ast) = processNodes("continued_and_expr", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_and_expr.2";
        }
#line 4121 "parse.tab.c"
    break;

  case 111: /* and_expr: shift_expr continued_shift_expr  */
#line 2273 "parse.y"
                                        {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("and_expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "and_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "and_expr.1";
        }
#line 4144 "parse.tab.c"
    break;

  case 112: /* continued_shift_expr: continued_shift_expr BITWISE_AND shift_expr  */
#line 2294 "parse.y"
                                                    {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_shift_expr", 3,
                                (yyvsp[-2].ast),
                                createNode("BITWISE_AND", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_shift_expr.1";
        }
#line 4169 "parse.tab.c"
    break;

  case 113: /* continued_shift_expr: %empty  */
#line 2314 "parse.y"
                 {
                // Will be ignored automatically in AST by processNodes.
                (yyval.ast) = processNodes("continued_shift_expr", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_shift_expr.2";
        }
#line 4182 "parse.tab.c"
    break;

  case 114: /* shift_expr: arith_expr continued_arith_expr  */
#line 2325 "parse.y"
                                        {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("shift_expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "shift_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "shift_expr.1";
        }
#line 4205 "parse.tab.c"
    break;

  case 115: /* continued_arith_expr: continued_arith_expr LEFT_SHIFT arith_expr  */
#line 2346 "parse.y"
                                                   {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_arith_expr", 3,
                                (yyvsp[-2].ast),
                                createNode("LEFT_SHIFT", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_arith_expr.1";
        }
#line 4230 "parse.tab.c"
    break;

  case 116: /* continued_arith_expr: continued_arith_expr RIGHT_SHIFT arith_expr  */
#line 2366 "parse.y"
                                                      {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_arith_expr", 3,
                                (yyvsp[-2].ast),
                                createNode("RIGHT_SHIFT", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_arith_expr.2";
        }
#line 4255 "parse.tab.c"
    break;

  case 117: /* continued_arith_expr: %empty  */
#line 2386 "parse.y"
                 {
                // Will be ignored automatically in AST by processNodes.
                (yyval.ast) = processNodes("continued_arith_expr", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_arith_expr.3";
        }
#line 4268 "parse.tab.c"
    break;

  case 118: /* arith_expr: term continued_term  */
#line 2397 "parse.y"
                            {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("arith_expr", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "arith_expr";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "arith_expr.1";
        }
#line 4291 "parse.tab.c"
    break;

  case 119: /* continued_term: continued_term PLUS term  */
#line 2418 "parse.y"
                                 {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_term", 3,
                                (yyvsp[-2].ast),
                                createNode("PLUS", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_term.1";
        }
#line 4316 "parse.tab.c"
    break;

  case 120: /* continued_term: continued_term MINUS term  */
#line 2438 "parse.y"
                                    {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_term", 3,
                                (yyvsp[-2].ast),
                                createNode("MINUS", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_term.2";
        }
#line 4341 "parse.tab.c"
    break;

  case 121: /* continued_term: %empty  */
#line 2458 "parse.y"
                 {
                // Will be ignored automatically in AST by processNodes.
                (yyval.ast) = processNodes("continued_term", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_term.3";
        }
#line 4354 "parse.tab.c"
    break;

  case 122: /* term: factor continued_factor  */
#line 2469 "parse.y"
                                {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("term", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "term";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "term.1";
        }
#line 4377 "parse.tab.c"
    break;

  case 123: /* continued_factor: continued_factor STAR factor  */
#line 2490 "parse.y"
                                     {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_factor", 3,
                                (yyvsp[-2].ast),
                                createNode("STAR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_factor.1";
        }
#line 4402 "parse.tab.c"
    break;

  case 124: /* continued_factor: continued_factor DIV factor  */
#line 2510 "parse.y"
                                      {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_factor", 3,
                                (yyvsp[-2].ast),
                                createNode("DIV", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_factor.2";
        }
#line 4427 "parse.tab.c"
    break;

  case 125: /* continued_factor: continued_factor AT factor  */
#line 2530 "parse.y"
                                     {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_factor", 3,
                                (yyvsp[-2].ast),
                                createNode("AT", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_factor.3";
        }
#line 4452 "parse.tab.c"
    break;

  case 126: /* continued_factor: continued_factor REM factor  */
#line 2550 "parse.y"
                                      {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_factor", 3,
                                (yyvsp[-2].ast),
                                createNode("REM", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_factor.4";
        }
#line 4477 "parse.tab.c"
    break;

  case 127: /* continued_factor: continued_factor FLOOR_DIV factor  */
#line 2570 "parse.y"
                                            {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_factor", 3,
                                (yyvsp[-2].ast),
                                createNode("FLOOR_DIV", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = ((yyval.ast)->content) + "$" + (yyvsp[-1].lexeme);
                        else ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_factor.5";
        }
#line 4502 "parse.tab.c"
    break;

  case 128: /* continued_factor: %empty  */
#line 2590 "parse.y"
                 {
                // Will be ignored automatically in AST by processNodes.
                (yyval.ast) = processNodes("continued_factor", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_factor.6";
        }
#line 4515 "parse.tab.c"
    break;

  case 129: /* factor: PLUS factor  */
#line 2601 "parse.y"
                    {
                // Right recursive production can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("factor", 2,
                                createNode("PLUS", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = string((yyvsp[-1].lexeme)) + "$" + ((yyval.ast)->content);
                        else ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "factor.1";
        }
#line 4538 "parse.tab.c"
    break;

  case 130: /* factor: MINUS factor  */
#line 2619 "parse.y"
                       {
                // Right recursive production can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("factor", 2,
                                createNode("MINUS", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = string((yyvsp[-1].lexeme)) + "$" + ((yyval.ast)->content);
                        else ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "factor.2";
        }
#line 4561 "parse.tab.c"
    break;

  case 131: /* factor: TILDE factor  */
#line 2637 "parse.y"
                       {
                // Right recursive production can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("factor", 2,
                                createNode("TILDE", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        if(((yyval.ast)->content).length() > 0 && ((yyval.ast)->content) != EPSILON) ((yyval.ast)->content) = string((yyvsp[-1].lexeme)) + "$" + ((yyval.ast)->content);
                        else ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "factor.3";
        }
#line 4584 "parse.tab.c"
    break;

  case 132: /* factor: power  */
#line 2655 "parse.y"
                {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("factor", 1, (yyvsp[0].ast));
                }
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "factor.4";
        }
#line 4599 "parse.tab.c"
    break;

  case 133: /* power: atom_expr DOUBLE_STAR factor  */
#line 2668 "parse.y"
                                     {
                // DOUBLE_STAR is the operator here. Can be propogated up.
                // See the special handling in "ProcessNodes".
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("power", 3,
                                (yyvsp[-2].ast),
                                createNode("DOUBLE_STAR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("power", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = (yyvsp[-1].lexeme);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "power.1";
        }
#line 4626 "parse.tab.c"
    break;

  case 134: /* power: atom_expr  */
#line 2690 "parse.y"
                    {
                if(isAST == false) (yyval.ast) = processNodes("power", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "power.2";
        }
#line 4639 "parse.tab.c"
    break;

  case 135: /* atom_expr: AWAIT atom trailers  */
#line 2701 "parse.y"
                            { // #notrequired
                // AWAIT is an operator here so can be used accordingly.
                // Special handling done for AWAIT in "processNodes".
                // Writing AWAIT as the 3rd argument is NOT A TYPO here. Please see "processNodes" function.
                if(isAST == false) {
                        (yyval.ast) = processNodes("atom_expr", 3,
                                createNode("AWAIT", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("atom_expr", 3,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast),
                                createNode("AWAIT", (yyvsp[-2].lexeme))
                        );
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom_expr.1";
        }
#line 4667 "parse.tab.c"
    break;

  case 136: /* atom_expr: atom trailers  */
#line 2724 "parse.y"
                        {
                (yyval.ast) = processNodes("atom_expr", 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom_expr.2";
        }
#line 4682 "parse.tab.c"
    break;

  case 137: /* trailers: trailers trailer  */
#line 2737 "parse.y"
                         {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: trailer added\n");
                
                // This is a left recursive production which can be simplified in the AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("trailers", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "trailers.1";
        }
#line 4706 "parse.tab.c"
    break;

  case 138: /* trailers: %empty  */
#line 2756 "parse.y"
                 {
                // Will be ignored in processNodes automatically for AST.
                (yyval.ast) = processNodes("trailers", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "trailers.2";
        }
#line 4719 "parse.tab.c"
    break;

  case 139: /* atom: OPENING_BRACKET testlist_comp CLOSING_BRACKET  */
#line 2767 "parse.y"
                                                      {
                // Simplification of BRACKETS is possible for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 3,
                                createNode("OPENING_BRACKET", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("CLOSING_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // This is a tough case. Here () will have to be treated as UNARY operators.
                        (yyval.ast) = processNodes("atom", 1, (yyvsp[-1].ast));
                        ((yyval.ast)->content) = " " + string((yyvsp[-2].lexeme)) + string((yyvsp[0].lexeme)) + " ";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.1";
        }
#line 4743 "parse.tab.c"
    break;

  case 140: /* atom: OPENING_BRACKET CLOSING_BRACKET  */
#line 2786 "parse.y"
                                          {
                // The case of empty brackets is irrelevant from a semantic perspective.
                // In AST such cases should be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 2, // "atom: OPENING_BRACKET CLOSING_BRACKET\n
                                createNode("OPENING_BRACKET", (yyvsp[-1].lexeme)),
                                createNode("CLOSING_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // Empty brackets especially kept to preserve the meaning of the program
                        (yyval.ast) = createNode("atom", " " + string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)) + " ");
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.2";
        }
#line 4766 "parse.tab.c"
    break;

  case 141: /* atom: OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET  */
#line 2804 "parse.y"
                                                              {
                // Simplification of BRACKETS is possible for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 3, // "atom: OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET\n
                                createNode("OPENING_SQ_BRACKET", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("CLOSING_SQ_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // This is a tough case. Here [] will have to be treated as UNARY operators.
                        (yyval.ast) = processNodes("atom", 1, (yyvsp[-1].ast));
                        ((yyval.ast)->content) = " " + string((yyvsp[-2].lexeme)) + string((yyvsp[0].lexeme)) + " ";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.3";
        }
#line 4790 "parse.tab.c"
    break;

  case 142: /* atom: OPENING_SQ_BRACKET CLOSING_SQ_BRACKET  */
#line 2823 "parse.y"
                                                {
                // The case of empty brackets is irrelevant from a semantic perspective.
                // In AST such cases should be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 2, // "atom: OPENING_SQ_BRACKET CLOSING_SQ_BRACKET\n
                                createNode("OPENING_SQ_BRACKET", (yyvsp[-1].lexeme)),
                                createNode("CLOSING_SQ_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // Empty brackets especially kept to preserve the meaning of the program
                        (yyval.ast) = createNode("atom", " " + string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)) + " ");
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.4";
        }
#line 4813 "parse.tab.c"
    break;

  case 143: /* atom: OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET  */
#line 2841 "parse.y"
                                                                     { // #notrequired
                // Simplification of BRACKETS is possible for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 3, // "atom: OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET\n
                                createNode("OPENING_CURLY_BRACKET", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("CLOSING_CURLY_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // This is a tough case. Here {} will have to be treated as UNARY operators.
                        (yyval.ast) = processNodes("atom", 1, (yyvsp[-1].ast));
                        ((yyval.ast)->content) = " " + string((yyvsp[-2].lexeme)) + string((yyvsp[0].lexeme)) + " ";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.5";
        }
#line 4837 "parse.tab.c"
    break;

  case 144: /* atom: OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET  */
#line 2860 "parse.y"
                                                      { // #notrequired
                // The case of empty brackets is irrelevant from a semantic perspective.
                // In AST such cases should be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 2, // "atom: OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET\n
                                createNode("OPENING_CURLY_BRACKET", (yyvsp[-1].lexeme)),
                                createNode("CLOSING_CURLY_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        // Empty brackets especially kept to preserve the meaning of the program
                        (yyval.ast) = createNode("atom", " " + string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)) + " ");
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.6";
        }
#line 4860 "parse.tab.c"
    break;

  case 145: /* atom: NAME  */
#line 2878 "parse.y"
               {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'NAME' used\n");
                
                // An "atom" is an element of the code. It can be a terminal of the AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 1,
                                createNode("NAME", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("NAME", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.7";
        }
#line 4880 "parse.tab.c"
    break;

  case 146: /* atom: NUMBER  */
#line 2893 "parse.y"
                  {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'NUMBER' used\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 1,
                                createNode("NUMBER", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("NUMBER", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.8";
        }
#line 4899 "parse.tab.c"
    break;

  case 147: /* atom: strings  */
#line 2907 "parse.y"
                  {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'STRING' used\n");
                
                // If the "atom" is a string then in the AST it can be treated as a terminal only.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("atom", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.9";
        }
#line 4915 "parse.tab.c"
    break;

  case 148: /* atom: ELLIPSES_LITERAL  */
#line 2918 "parse.y"
                           { // #notrequired
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'ELLIPSES_LITERAL' used\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 1,
                                createNode("ELLIPSES_LITERAL", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("ELLIPSES_LITERAL", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.10";
        }
#line 4934 "parse.tab.c"
    break;

  case 149: /* atom: TOKEN_TRUE  */
#line 2932 "parse.y"
                     {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 1,
                                createNode("TOKEN_TRUE", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("TOKEN_TRUE", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.11";
        }
#line 4951 "parse.tab.c"
    break;

  case 150: /* atom: TOKEN_FALSE  */
#line 2944 "parse.y"
                      {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 1,
                                createNode("TOKEN_FALSE", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("TOKEN_FALSE", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.12";
        }
#line 4968 "parse.tab.c"
    break;

  case 151: /* atom: TOKEN_NONE  */
#line 2956 "parse.y"
                     {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("atom", 1,
                                createNode("TOKEN_NONE", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("TOKEN_NONE", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "atom.13";
        }
#line 4985 "parse.tab.c"
    break;

  case 152: /* strings: strings STRING  */
#line 2970 "parse.y"
                        {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("strings", 2,
                                (yyvsp[-1].ast),
                                createNode("STRING", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ASTNode* node = createNode("STRING", (yyvsp[0].lexeme));
                        ((yyval.ast)->children).push_back(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "strings.1";
        }
#line 5008 "parse.tab.c"
    break;

  case 153: /* strings: STRING  */
#line 2988 "parse.y"
                 {
                // From the perspective of an AST, a string is an "atom"
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("strings", 1,
                                createNode("STRING",(yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("STRING", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "strings.2";
        }
#line 5026 "parse.tab.c"
    break;

  case 154: /* testlist_comp: test comp_for  */
#line 3004 "parse.y"
                      { // #notrequired
                // Simplification maybe possible but can make AST intractable diagramatically due to oversimplification.
                (yyval.ast) = processNodes("testlist_comp", 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_comp.1";
        }
#line 5042 "parse.tab.c"
    break;

  case 155: /* testlist_comp: test continued_testlist COMMA  */
#line 3015 "parse.y"
                                        {
                // COMMA ignored for AST as it has no semantic significance
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_comp", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "testlist_comp";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_comp.2";
        }
#line 5067 "parse.tab.c"
    break;

  case 156: /* testlist_comp: test continued_testlist  */
#line 3035 "parse.y"
                                  {
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_comp", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "testlist_comp";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_comp.3";
        }
#line 5090 "parse.tab.c"
    break;

  case 157: /* testlist_comp: star_expr comp_for  */
#line 3053 "parse.y"
                             {
                // Simplification maybe possible but can make AST intractable diagramatically due to oversimplification.
                (yyval.ast) = processNodes("testlist_comp", 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_comp.4";
        }
#line 5106 "parse.tab.c"
    break;

  case 158: /* testlist_comp: star_expr continued_testlist COMMA  */
#line 3064 "parse.y"
                                             {
                // COMMA ignored for AST as it has no semantic significance
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_comp", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "testlist_comp";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_comp.5";
        }
#line 5131 "parse.tab.c"
    break;

  case 159: /* testlist_comp: star_expr continued_testlist  */
#line 3084 "parse.y"
                                       {
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist_comp", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "testlist_comp";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist_comp.6";
        }
#line 5154 "parse.tab.c"
    break;

  case 160: /* continued_testlist: continued_testlist COMMA test  */
#line 3105 "parse.y"
                                       {
                // Left recursive production can be simplified to a single level in AST
                // COMMA has no significant semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_testlist", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_testlist.1";
        }
#line 5178 "parse.tab.c"
    break;

  case 161: /* continued_testlist: continued_testlist COMMA star_expr  */
#line 3124 "parse.y"
                                             { // #notrequired
                // Left recursive production can be simplified to a single level in AST
                // COMMA has no significant semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_testlist", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_testlist.2";
        }
#line 5202 "parse.tab.c"
    break;

  case 162: /* continued_testlist: %empty  */
#line 3143 "parse.y"
                  {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: no further tests added\n");
                
                // Will be automatically ignored by "processNodes" for AST
                (yyval.ast) = processNodes("continued_testlist", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_testlist.3";
        }
#line 5217 "parse.tab.c"
    break;

  case 163: /* trailer: OPENING_BRACKET arglist CLOSING_BRACKET  */
#line 3156 "parse.y"
                                                {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: arglist within brackets added \n");
                
                // Brackets removed for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("trailer", 3,
                                createNode("OPENING_BRACKET", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("CLOSING_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "trailer";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "trailer.1";
        }
#line 5242 "parse.tab.c"
    break;

  case 164: /* trailer: OPENING_BRACKET CLOSING_BRACKET  */
#line 3176 "parse.y"
                                          {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: empty brackets added \n");
                
                // Empty brackets have no significance in AST.
                // However, to avoid oversimplification of AST they are kept as a single terminal.
                // Special "empty bracket" simplification is done in "processNodes" function.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("trailer", 2,
                                createNode("OPENING_BRACKET", (yyvsp[-1].lexeme)),
                                createNode("CLOSING_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("trailer", " " + string((yyvsp[-1].lexeme)) + string((yyvsp[0].lexeme)) + " ");
                
                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "trailer.2";
        }
#line 5265 "parse.tab.c"
    break;

  case 165: /* trailer: OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET  */
#line 3194 "parse.y"
                                                              {
                // Brackets removed for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("trailer", 3,
                                createNode("OPENING_SQ_BRACKET", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                createNode("CLOSING_SQ_BRACKET", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "trailer";
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "trailer.3";
        }
#line 5288 "parse.tab.c"
    break;

  case 166: /* trailer: DOT NAME  */
#line 3212 "parse.y"
                   {
                // Special simplification for AST - Remove the extra "trailer" node and directly write the non-terminal.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("trailer", 2,
                                createNode("DOT", (yyvsp[-1].lexeme)),
                                createNode("NAME", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("trailer", string((yyvsp[-1].lexeme)) + " " + string((yyvsp[0].lexeme)));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "trailer.4";
        }
#line 5307 "parse.tab.c"
    break;

  case 167: /* subscriptlist: subscript continued_subscript COMMA  */
#line 3230 "parse.y"
                                            {
                // COMMA will have no semantic meaning it is just a seperator - Can be ignored
                // AST simplification for right recursive production. Bring all terms on a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscriptlist", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "subscriptlist";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscriptlist.1";

        }
#line 5333 "parse.tab.c"
    break;

  case 168: /* subscriptlist: subscript continued_subscript  */
#line 3251 "parse.y"
                                        {
                // AST simplification for right recursive production. Bring all terms on a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscriptlist", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "subscriptlist";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscriptlist.2";
        }
#line 5356 "parse.tab.c"
    break;

  case 169: /* continued_subscript: continued_subscript COMMA subscript  */
#line 3273 "parse.y"
                                             {
                // Simplification in AST possible for left recursive productions to bring all terms on a single level.
                // COMMA can be ignored because that has no semantic significance.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_subscript", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_subscript.1";
        }
#line 5380 "parse.tab.c"
    break;

  case 170: /* continued_subscript: %empty  */
#line 3292 "parse.y"
                 {
                (yyval.ast) = processNodes("continued_subscript", 0); // Will be ignored in processNodes automatically.

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_subscript.2";
        }
#line 5392 "parse.tab.c"
    break;

  case 171: /* subscript: test  */
#line 3302 "parse.y"
             {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("subscript", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.1";
        }
#line 5405 "parse.tab.c"
    break;

  case 172: /* subscript: test COLON test sliceop  */
#line 3310 "parse.y"
                                  { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                // Also, how can we simplify this node further by simplifying "sliceop" in AST ?
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 4,
                                (yyvsp[-3].ast),
                                createNode("COLON", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 3,
                                (yyvsp[-3].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.2";
        }
#line 5434 "parse.tab.c"
    break;

  case 173: /* subscript: test COLON test  */
#line 3334 "parse.y"
                          { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 3,
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.3";
        }
#line 5460 "parse.tab.c"
    break;

  case 174: /* subscript: test COLON sliceop  */
#line 3355 "parse.y"
                             { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 3,
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.4";
        }
#line 5486 "parse.tab.c"
    break;

  case 175: /* subscript: test COLON  */
#line 3376 "parse.y"
                     { // #notrequired
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually seem to be a part of conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 2,
                                (yyvsp[-1].ast),
                                createNode("COLON", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 1, (yyvsp[-1].ast));
                        ((yyval.ast)->content) = string((yyvsp[0].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.5";
        }
#line 5509 "parse.tab.c"
    break;

  case 176: /* subscript: COLON test sliceop  */
#line 3394 "parse.y"
                             { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 3,
                                createNode("COLON", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.6";
        }
#line 5535 "parse.tab.c"
    break;

  case 177: /* subscript: COLON test  */
#line 3415 "parse.y"
                     { // #notrequired
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually seem to be a part of conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 2,
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.7";
        }
#line 5558 "parse.tab.c"
    break;

  case 178: /* subscript: COLON sliceop  */
#line 3433 "parse.y"
                        { // notrequired
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "sliceop" node -> That would actually seem to be a part of slicing operator.
                // However, this is a rarely occuring case - Can somekind of simplification be done here ?
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 2,
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("subscript", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.8";
        }
#line 5582 "parse.tab.c"
    break;

  case 179: /* subscript: COLON  */
#line 3452 "parse.y"
                {
                // This behaves like a terminal for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("subscript", 1,
                                createNode("COLON", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("COLON", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "subscript.9";
        }
#line 5600 "parse.tab.c"
    break;

  case 180: /* sliceop: COLON test  */
#line 3468 "parse.y"
                   {
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually seem to be an operator in conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("sliceop", 2,
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("sliceop", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "sliceop.1";
        }
#line 5623 "parse.tab.c"
    break;

  case 181: /* sliceop: COLON  */
#line 3486 "parse.y"
                {
                // This behaves like a terminal for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("sliceop", 1,
                                createNode("COLON", (yyvsp[0].lexeme))
                        );
                }
                else (yyval.ast) = createNode("COLON", (yyvsp[0].lexeme));

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "sliceop.2";
        }
#line 5641 "parse.tab.c"
    break;

  case 182: /* exprlist: expr continued_exprlist COMMA  */
#line 3503 "parse.y"
                                      {
                // COMMA is not important from semantic perspective so ignored in AST.
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("exprlist", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "exprlist";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "exprlist.1";
        }
#line 5666 "parse.tab.c"
    break;

  case 183: /* exprlist: expr continued_exprlist  */
#line 3523 "parse.y"
                                  {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("exprlist", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "exprlist";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "exprlist.2";
        }
#line 5689 "parse.tab.c"
    break;

  case 184: /* exprlist: star_expr continued_exprlist COMMA  */
#line 3541 "parse.y"
                                             {
                // COMMA is not important from semantic perspective so ignored in AST.
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("exprlist", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "exprlist";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "exprlist.3";
        }
#line 5714 "parse.tab.c"
    break;

  case 185: /* exprlist: star_expr continued_exprlist  */
#line 3561 "parse.y"
                                       {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("exprlist", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "exprlist";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "exprlist.4";
        }
#line 5737 "parse.tab.c"
    break;

  case 186: /* continued_exprlist: continued_exprlist COMMA expr  */
#line 3582 "parse.y"
                                      {
                // Left recursive production can be simplified in AST to a single level.
                // COMMA has no semantic meaning as such and thus can be ignored here.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_exprlist", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_exprlist.1";
        }
#line 5761 "parse.tab.c"
    break;

  case 187: /* continued_exprlist: continued_exprlist COMMA star_expr  */
#line 3601 "parse.y"
                                             { // #notrequired
                // Left recursive production can be simplified in AST to a single level.
                // COMMA has no semantic meaning as such and thus can be ignored here.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_exprlist", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_exprlist.2";
        }
#line 5785 "parse.tab.c"
    break;

  case 188: /* continued_exprlist: %empty  */
#line 3620 "parse.y"
                 {
                // Will be ignored automatically in case of AST
                (yyval.ast) = processNodes("continued_exprlist", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_exprlist.3";
        }
#line 5798 "parse.tab.c"
    break;

  case 189: /* testlist: test continued_comma_test COMMA  */
#line 3631 "parse.y"
                                        {
                // COMMA have no signifiance is semantic meaning so it is ignored
                // Left recursive production can be simplified into a single level in an AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "testlist";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist.1";
        }
#line 5823 "parse.tab.c"
    break;

  case 190: /* testlist: test continued_comma_test  */
#line 3651 "parse.y"
                                    {
                // Left recursive production can be simplified into a single level in an AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("testlist", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "testlist";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "testlist.2";
        }
#line 5846 "parse.tab.c"
    break;

  case 191: /* continued_comma_test: continued_comma_test COMMA test  */
#line 3672 "parse.y"
                                        {
                // Left recursive production can be simplified into a single level in an AST
                // COMMA can be ignored because it carries no semantic meaning
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_comma_test", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_comma_test.1";
        }
#line 5870 "parse.tab.c"
    break;

  case 192: /* continued_comma_test: %empty  */
#line 3691 "parse.y"
                 {
                // Will be automatically ignored for AST by "processNodes"
                (yyval.ast) = processNodes("continued_comma_test", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_comma_test.2";
        }
#line 5883 "parse.tab.c"
    break;

  case 193: /* dictorsetmaker: test COLON test comp_for  */
#line 3703 "parse.y"
                                 {
                // COLON can be identified as the only operator and propagated upwards in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 4,
                                (yyvsp[-3].ast),
                                createNode("COLON", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("dictorsetmaker", 3,
                                (yyvsp[-3].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.1";
        }
#line 5911 "parse.tab.c"
    break;

  case 194: /* dictorsetmaker: test COLON test continued_dictorset COMMA  */
#line 3726 "parse.y"
                                                    {
                // COMMA has no significant semantic meaning so it can be ignored.
                // Right recursive production can be simplified in a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 5,
                                (yyvsp[-4].ast),
                                createNode("COLON", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("COLON", 2, (yyvsp[-4].ast), (yyvsp[-2].ast));
                        (node->content) = string((yyvsp[-3].lexeme));
                        ((yyval.ast)->children).push_front(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.2";

        }
#line 5941 "parse.tab.c"
    break;

  case 195: /* dictorsetmaker: test COLON test continued_dictorset  */
#line 3751 "parse.y"
                                              {
                // Right recursive production can be simplified in a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 4,
                                (yyvsp[-3].ast),
                                createNode("COLON", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("COLON", 2, (yyvsp[-3].ast), (yyvsp[-1].ast));
                        (node->content) = string((yyvsp[-2].lexeme));
                        ((yyval.ast)->children).push_front(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.3";
        }
#line 5968 "parse.tab.c"
    break;

  case 196: /* dictorsetmaker: DOUBLE_STAR expr comp_for  */
#line 3773 "parse.y"
                                    {
                // DOUBLE_STAR can be identified as operator and propagated upwards in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 3,
                                createNode("DOUBLE_STAR", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("dictorsetmaker", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.4";
        }
#line 5994 "parse.tab.c"
    break;

  case 197: /* dictorsetmaker: DOUBLE_STAR expr continued_dictorset COMMA  */
#line 3794 "parse.y"
                                                     {
                // COMMA has no significant semantic meaning so it can be ignored.
                // Right recursive production can be simplified in a single level in AST
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add DOUBLE_STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 4,
                                createNode("DOUBLE_STAR", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("DOUBLE_STAR", 1, (yyvsp[-2].ast));
                        (node->content) = string((yyvsp[-3].lexeme));
                        ((yyval.ast)->children).push_front(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.5";
        }
#line 6024 "parse.tab.c"
    break;

  case 198: /* dictorsetmaker: DOUBLE_STAR expr continued_dictorset  */
#line 3819 "parse.y"
                                               {
                // Right recursive production can be simplified in a single level in AST
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add DOUBLE_STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 3,
                                createNode("DOUBLE_STAR", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("DOUBLE_STAR", 1, (yyvsp[-1].ast));
                        (node->content) = string((yyvsp[-2].lexeme));
                        ((yyval.ast)->children).push_front(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.6";
        }
#line 6052 "parse.tab.c"
    break;

  case 199: /* dictorsetmaker: test comp_for  */
#line 3842 "parse.y"
                        {
                // Difficult to make simplifications here and can lead to oversimplification and node deletions in AST
                (yyval.ast) = processNodes("dictorsetmaker", 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.7";
        }
#line 6068 "parse.tab.c"
    break;

  case 200: /* dictorsetmaker: test continued_testlist COMMA  */
#line 3853 "parse.y"
                                        {
                // Right recursive production can be simplified to a single level in AST
                // COMMA not significant semantically so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.8";
        }
#line 6093 "parse.tab.c"
    break;

  case 201: /* dictorsetmaker: test continued_testlist  */
#line 3873 "parse.y"
                                  {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.9";
        }
#line 6116 "parse.tab.c"
    break;

  case 202: /* dictorsetmaker: star_expr comp_for  */
#line 3891 "parse.y"
                             {
                // Difficult to make simplifications here and can lead to oversimplification and node deletions in AST
                (yyval.ast) = processNodes("dictorsetmaker", 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.10";
        }
#line 6132 "parse.tab.c"
    break;

  case 203: /* dictorsetmaker: star_expr continued_testlist COMMA  */
#line 3902 "parse.y"
                                             {
                // Right recursive production can be simplified to a single level in AST
                // COMMA not significant semantically so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.11";
        }
#line 6157 "parse.tab.c"
    break;

  case 204: /* dictorsetmaker: star_expr continued_testlist  */
#line 3922 "parse.y"
                                       {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("dictorsetmaker", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "dictorsetmaker";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "dictorsetmaker.12";
        }
#line 6180 "parse.tab.c"
    break;

  case 205: /* continued_dictorset: continued_dictorset COMMA test COLON test  */
#line 3944 "parse.y"
                                                  {
                // Left recursive productions can be simplified to a single level in AST
                // Here both COMMA and COLON are operator and both are generally insignificant.
                // But in this context we ignore COMMA and COLON is propogated up.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_dictorset", 5,
                                (yyvsp[-4].ast),
                                createNode("COMMA", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-4].ast);
                        ASTNode* node = processNodes("COLON", 2, (yyvsp[-2].ast), (yyvsp[0].ast));
                        (node->content) = string((yyvsp[-1].lexeme));
                        ((yyval.ast)->children).push_back(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_dictorset.1";
        }
#line 6209 "parse.tab.c"
    break;

  case 206: /* continued_dictorset: continued_dictorset COMMA DOUBLE_STAR expr  */
#line 3968 "parse.y"
                                                     {
                // Left recursive productions can be simplified to a single level in AST
                // Here both COMMA and DOUBLE_STAR are operator. In this context we ignore COMMA and DOUBLE_STAR is propogated up.
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add DOUBLE_STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("continued_dictorset", 4,
                                (yyvsp[-3].ast),
                                createNode("COMMA", (yyvsp[-2].lexeme)),
                                createNode("DOUBLE_STAR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-3].ast);
                        ASTNode* node = processNodes("DOUBLE_STAR", 1, (yyvsp[0].ast));
                        ((yyval.ast)->children).push_back(node);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_dictorset.2";
        }
#line 6237 "parse.tab.c"
    break;

  case 207: /* continued_dictorset: %empty  */
#line 3991 "parse.y"
                 {
                // Will be ignored by "processNodes" for AST
                (yyval.ast) = processNodes("continued_dictorset", 0);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_dictorset.3";
        }
#line 6250 "parse.tab.c"
    break;

  case 208: /* classdef: CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite  */
#line 4002 "parse.y"
                                                                       {
                // CLASS and COLON can be considered as operators. COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("classdef", 7,
                                createNode("CLASS", (yyvsp[-6].lexeme)),
                                createNode("NAME", (yyvsp[-5].lexeme)),
                                createNode("OPENING_BRACKET", (yyvsp[-4].lexeme)),
                                (yyvsp[-3].ast),
                                createNode("CLOSING_BRACKET", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("classdef", 3,
                                createNode("NAME", (yyvsp[-5].lexeme)),
                                (yyvsp[-3].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-6].lexeme));
                }
                
                if(AST_DEBUG_OUTSIDE_VERBOSE) {
                        printf("[AST]: classdef -> CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite used\n");
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "classdef.1";
        }
#line 6285 "parse.tab.c"
    break;

  case 209: /* classdef: CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite  */
#line 4032 "parse.y"
                                                                 {
                // CLASS and COLON can be considered as operators. COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("classdef", 6,
                                createNode("CLASS", (yyvsp[-5].lexeme)),
                                createNode("NAME", (yyvsp[-4].lexeme)),
                                createNode("OPENING_BRACKET", (yyvsp[-3].lexeme)),
                                createNode("CLOSING_BRACKET", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("classdef", 3,
                                createNode("NAME", (yyvsp[-4].lexeme)),
                                createNode("BRACKETS", " " + string((yyvsp[-3].lexeme)) + string((yyvsp[-2].lexeme)) + " "),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-5].lexeme));
                }

                if(AST_DEBUG_OUTSIDE_VERBOSE) {
                        printf("[AST]: classdef-> CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite used\n");
                        char* prnt = const_cast<char*> (((yyvsp[0].ast)->content).c_str());
                        printf("[AST]: contents in suite - %s\n", prnt);
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "classdef.2";
        }
#line 6321 "parse.tab.c"
    break;

  case 210: /* classdef: CLASS NAME COLON suite  */
#line 4063 "parse.y"
                                 {
                // CLASS and COLON can be considered as operators. COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("classdef", 4,
                                createNode("CLASS", (yyvsp[-3].lexeme)),
                                createNode("NAME", (yyvsp[-2].lexeme)),
                                createNode("COLON", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("classdef", 2,
                                createNode("NAME", (yyvsp[-2].lexeme)),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme));
                }

                if(AST_DEBUG_OUTSIDE_VERBOSE) {
                        cout<<"[AST]: classdef-> CLASS NAME COLON suite used"<<"\n";                
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "classdef.3";
        }
#line 6352 "parse.tab.c"
    break;

  case 211: /* arglist: argument continued_argument COMMA  */
#line 4092 "parse.y"
                                          {
                if(isAST == false) {
                        (yyval.ast) = processNodes("arglist", 3,
                                (yyvsp[-2].ast),
                                (yyvsp[-1].ast),
                                createNode("COMMA", (yyvsp[0].lexeme))
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-1].ast);
                        ((yyval.ast)->type) = "arglist";
                        ((yyval.ast)->children).push_front((yyvsp[-2].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "arglist.1";
        }
#line 6375 "parse.tab.c"
    break;

  case 212: /* arglist: argument continued_argument  */
#line 4110 "parse.y"
                                      {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: single argument added in arglist\n");
                
                // Right recursive production can be simplified for an AST into a single level.
                if(isAST == false) {
                        (yyval.ast) = processNodes("arglist", 2,
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[0].ast);
                        ((yyval.ast)->type) = "arglist";
                        ((yyval.ast)->children).push_front((yyvsp[-1].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "arglist.2";
        }
#line 6400 "parse.tab.c"
    break;

  case 213: /* continued_argument: continued_argument COMMA argument  */
#line 4133 "parse.y"
                                          {
                // Simplification in AST possible for left recursive productions to bring all terms on a single level.
                // COMMA can be ignored because that has no semantic significance.
                if(isAST == false) {
                        (yyval.ast) = processNodes("continued_argument", 3,
                                (yyvsp[-2].ast),
                                createNode("COMMA", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = (yyvsp[-2].ast);
                        ((yyval.ast)->children).push_back((yyvsp[0].ast));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_argument.1";
        }
#line 6424 "parse.tab.c"
    break;

  case 214: /* continued_argument: %empty  */
#line 4152 "parse.y"
                 {
                (yyval.ast) = processNodes("continued_argument", 0); // Will be ignored automatically in AST

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "continued_argument.2";
        }
#line 6436 "parse.tab.c"
    break;

  case 215: /* argument: test comp_for  */
#line 4162 "parse.y"
                      { // #notrequired
                (yyval.ast) = processNodes("argument", 2,
                        (yyvsp[-1].ast),
                        (yyvsp[0].ast)                
                );

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "argument.1";
        }
#line 6451 "parse.tab.c"
    break;

  case 216: /* argument: test EQUAL test  */
#line 4172 "parse.y"
                          {
                // EQUAL can be identified as an operator and can be propogated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("argument", 3,
                                (yyvsp[-2].ast),
                                createNode("EQUAL", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("argument", 2,
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "argument.2";
        }
#line 6477 "parse.tab.c"
    break;

  case 217: /* argument: DOUBLE_STAR test  */
#line 4193 "parse.y"
                           { // #notrequired
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add STAR in the "content" of "test" node -> That would actually feel like a STAR annotated to a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("argument", 2,
                                createNode("DOUBLE_STAR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("argument", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "argument.3";
        }
#line 6500 "parse.tab.c"
    break;

  case 218: /* argument: STAR test  */
#line 4211 "parse.y"
                    { // #notrequired
                // This is a tough case. Here STAR is a unary operator and thus we cannot directly
                // add STAR in the "content" of "test" node -> That would actually feel like a STAR annotated to a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("argument", 2,
                                createNode("STAR", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("argument", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "argument.4";
        }
#line 6523 "parse.tab.c"
    break;

  case 219: /* argument: test  */
#line 4229 "parse.y"
               {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: argument contains a single test\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("argument", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "argument.5";
        }
#line 6538 "parse.tab.c"
    break;

  case 220: /* comp_iter: comp_for  */
#line 4243 "parse.y"
                 { 
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("comp_iter", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_iter.1";
        }
#line 6551 "parse.tab.c"
    break;

  case 221: /* comp_iter: comp_if  */
#line 4251 "parse.y"
                  { 
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) (yyval.ast) = processNodes("comp_iter", 1, (yyvsp[0].ast));
                else (yyval.ast) = (yyvsp[0].ast);

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_iter.2";
        }
#line 6564 "parse.tab.c"
    break;

  case 222: /* comp_for: FOR exprlist IN or_test comp_iter  */
#line 4263 "parse.y"
                                          {
                // FOR and IN can be identified as operators for AST and propogated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_for", 5, // "comp_for: FOR exprlist IN or_test comp_iter\n
                                createNode("FOR", (yyvsp[-4].lexeme)),
                                (yyvsp[-3].ast),
                                createNode("IN", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("comp_for", 3, // "comp_for: FOR exprlist IN or_test comp_iter\n
                                (yyvsp[-3].ast),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-4].lexeme)) + "$" + string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_for.1";
        }
#line 6593 "parse.tab.c"
    break;

  case 223: /* comp_for: FOR exprlist IN or_test  */
#line 4287 "parse.y"
                                  {
                // FOR and IN can be identified as operators for AST and propogated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_for", 4, // "comp_for: FOR exprlist IN or_test\n
                                createNode("FOR", (yyvsp[-3].lexeme)),
                                (yyvsp[-2].ast),
                                createNode("IN", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("comp_for", 2, // "comp_for: FOR exprlist IN or_test\n
                                (yyvsp[-2].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-3].lexeme)) + "$" + string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_for.2";
        }
#line 6620 "parse.tab.c"
    break;

  case 224: /* comp_if: IF test_nocond comp_iter  */
#line 4313 "parse.y"
                                 {
                // IF can be identified as the operator here and propogated upwards in this.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_if", 3, // "comp_if: IF test_nocond comp_iter\n
                                createNode("IF", (yyvsp[-2].lexeme)),
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("comp_if", 2, // "comp_if: IF test_nocond comp_iter\n
                                (yyvsp[-1].ast),
                                (yyvsp[0].ast)
                        );
                        ((yyval.ast)->content) = string((yyvsp[-2].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_if.1";
        }
#line 6646 "parse.tab.c"
    break;

  case 225: /* comp_if: IF test_nocond  */
#line 4334 "parse.y"
                         {
                // This is a tough case. Here IF is a unary operator and thus we cannot directly
                // add IF in the "content" of "test_nocond" node -> That would actually feel a non-conditional test expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        (yyval.ast) = processNodes("comp_if", 2, // "comp_if: IF test_nocond\n
                                createNode("IF", (yyvsp[-1].lexeme)),
                                (yyvsp[0].ast)
                        );
                }
                else {
                        (yyval.ast) = processNodes("comp_if", 1, (yyvsp[0].ast));
                        ((yyval.ast)->content) = string((yyvsp[-1].lexeme));
                }

                ((yyval.ast)->columnno) = yylloc.first_column;
                ((yyval.ast)->lineno) = yylineno;
                (yyval.ast)->name = "comp_if.2";
        }
#line 6669 "parse.tab.c"
    break;


#line 6673 "parse.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 4354 "parse.y"


/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you want to declare should go here.

// Whenever there is a syntax error found during parsing then this function is called which
// returns with a syntax error in the program.
void yyerror(const char* s) {
        fprintf(stderr, "[SYNTAX ERROR]: Offending token near '%s' at column no %d on line no %d\n", yytext, yylloc.first_column, yylineno);
        return;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/
