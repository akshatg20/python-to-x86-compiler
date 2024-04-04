%{
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
%}

%union {
    struct ASTNode* ast;
    char* lexeme;
}

%token<lexeme>  NEWLINE
%token<lexeme>  INDENT
%token<lexeme>  DEDENT
%token<lexeme>  ENDMARKER
%token<lexeme>  DEF
%token<lexeme>  NAME
%token<lexeme>  RIGHTARROW
%token<lexeme>  DOUBLE_STAR
%token<lexeme>  AUGASSIGN
%token<lexeme>  BREAK
%token<lexeme>  CONTINUE
%token<lexeme>  RETURN
%token<lexeme>  RAISE
%token<lexeme>  FROM
%token<lexeme>  ASSERT
%token<lexeme>  GLOBAL
%token<lexeme>  NONLOCAL
%token<lexeme>  IF
%token<lexeme>  ELIF
%token<lexeme>  ELSE
%token<lexeme>  WHILE
%token<lexeme>  FOR
%token<lexeme>  TRY
%token<lexeme>  IN
%token<lexeme>  FINALLY
%token<lexeme>  EXCEPT
%token<lexeme>  AS
%token<lexeme>  AND
%token<lexeme>  OR
%token<lexeme>  NOT
%token<lexeme>  IS
%token<lexeme>  COMP_OP
%token<lexeme>  LEFT_SHIFT
%token<lexeme>  RIGHT_SHIFT
%token<lexeme>  FLOOR_DIV
%token<lexeme>  AWAIT
%token<lexeme>  NUMBER
%token<lexeme>  ELLIPSES_LITERAL
%token<lexeme>  TOKEN_TRUE
%token<lexeme>  TOKEN_FALSE
%token<lexeme>  TOKEN_NONE
%token<lexeme>  STRING
%token<lexeme>  CLASS
%token<lexeme>  COLON
%token<lexeme>  SEMI_COLON
%token<lexeme>  OPENING_BRACKET
%token<lexeme>  CLOSING_BRACKET
%token<lexeme>  OPENING_SQ_BRACKET
%token<lexeme>  CLOSING_SQ_BRACKET
%token<lexeme>  OPENING_CURLY_BRACKET
%token<lexeme>  CLOSING_CURLY_BRACKET
%token<lexeme>  STAR
%token<lexeme>  EQUAL
%token<lexeme>  COMMA
%token<lexeme>  PLUS
%token<lexeme>  MINUS
%token<lexeme>  DIV
%token<lexeme>  AT
%token<lexeme>  TILDE
%token<lexeme>  REM
%token<lexeme>  CARET
%token<lexeme>  BITWISE_AND
%token<lexeme>  BITWISE_OR
%token<lexeme>  DOT

%locations

%start start

%type<ast> start 
%type<ast> file_input 
%type<ast> continued_file_input
%type<ast> funcdef
%type<ast> parameters
%type<ast> typedargslist
%type<ast> next_arg
%type<ast> tfpdef
%type<ast> stmt
%type<ast> simple_stmt
%type<ast> next_small_stmt
%type<ast> small_stmt
%type<ast> expr_stmt
%type<ast> continued_expr_stmt
%type<ast> annassign
%type<ast> testlist_star_expr
%type<ast> flow_stmt
%type<ast> break_stmt
%type<ast> continue_stmt
%type<ast> return_stmt
%type<ast> raise_stmt
%type<ast> global_stmt
%type<ast> nonlocal_stmt
%type<ast> assert_stmt
%type<ast> stmt_helper
%type<ast> compound_stmt
%type<ast> if_stmt
%type<ast> elif_stmt
%type<ast> else_stmt
%type<ast> while_stmt
%type<ast> for_stmt
%type<ast> try_stmt
%type<ast> except_stmt
%type<ast> finally_stmt
%type<ast> except_clause
%type<ast> suite
%type<ast> stmts
%type<ast> test
%type<ast> test_nocond
%type<ast> or_test
%type<ast> continued_or_test
%type<ast> and_test
%type<ast> continued_and_test
%type<ast> not_test
%type<ast> comparison
%type<ast> comparison_stmt
%type<ast> comp_op
%type<ast> star_expr
%type<ast> expr
%type<ast> continued_xor_expr
%type<ast> xor_expr
%type<ast> continued_and_expr
%type<ast> and_expr
%type<ast> continued_shift_expr
%type<ast> shift_expr
%type<ast> continued_arith_expr
%type<ast> arith_expr
%type<ast> continued_term
%type<ast> term
%type<ast> continued_factor
%type<ast> factor
%type<ast> power
%type<ast> atom_expr
%type<ast> trailers
%type<ast> trailer
%type<ast> atom
%type<ast> strings
%type<ast> testlist_comp
%type<ast> continued_testlist
%type<ast> subscriptlist
%type<ast> continued_subscript
%type<ast> subscript
%type<ast> sliceop
%type<ast> exprlist
%type<ast> continued_exprlist
%type<ast> testlist
%type<ast> continued_comma_test
%type<ast> dictorsetmaker
%type<ast> continued_dictorset
%type<ast> classdef
%type<ast> arglist
%type<ast> continued_argument
%type<ast> argument
%type<ast> comp_iter
%type<ast> comp_for
%type<ast> comp_if

%type<ast> forcheck

%%

// --------------------- Segment 1 ---------------------


start:
        file_input         {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: Parse Success\n");
                if(AST_DEBUG_INSIDE_VERBOSE) printf("[AST]: Root Node for the AST build\n");
                
                // For AST the start symbol is ignored as it has no special semantic meaning.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("start" , 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "start.1";
                
                // Generate the AST or Parse Tree for the program
                root = $$; // Set the root node of the Parse Tree or the AST.
                
                if(isAST == true && AST_STRUCTURE_DEBUG == 0) {
                        // Simplifications into AST to get a compact structure
                        root = simplify_ast(root);
                }

                // Write a result into a dot file to generate PDF
                int result = writeTree(root, getNewId(), dotfile_path, astfile_path, parsefile_path);
                if(AST_DEBUG_INSIDE_VERBOSE) printf("[AST]: AST and Parse Tree built\n");

                // Set the column number and line number for the non-terminal
                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;

                return result;
        }
        ;  

file_input:
        continued_file_input ENDMARKER {
                // Grammar contains ENDMARKER to mark completion of parsing process returned when lexer reads an <<EOF>> token.
                // From perspective of AST this is not an important node and this leads to an extra awkward looking top
                // portion of the tree. Thus the node corresponding to "ENDMARKER" is ignored for building AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("file_input", 2,
                                $1,
                                createNode("ENDMARKER", $2)
                        );
                }
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "file_input.1";

        }
        ;

continued_file_input:
        continued_file_input NEWLINE {
                // For AST we can ignore the NEWLINE as it has no special semantic meaning.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_file_input", 2,
                                $1,
                                createNode("NEWLINE", $2)
                        );
                }
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_file_input.1";
        }
        | continued_file_input stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: NEXT STATEMENT TO COME UP\n\n");
                
                // No direct simplification is possible here.
                $$ = processNodes("continued_file_input" , 2,
                        $1,
                        $2
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_file_input.2";
        }
        | %empty { 
                // This kind of a node will automatically be ignored by the AST in processNodes.
                $$ = processNodes("continued_file_input", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_file_input.3";
        }
        ;    

// ---------------- End of Segment 1 -----------------

funcdef:
        DEF NAME parameters RIGHTARROW test COLON suite {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: funcdef non-terminal used\n");
                
                // DEF and RIGHTARROW can be identified as operators and propogated up in AST
                // COLON does not add any special semantic meaning so it can be ignored
                // Please see special handling of function definitions in "processNodes"
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("funcdef", 7,
                                createNode("DEF", $1),
                                createNode("NAME",$2),
                                $3,
                                createNode("RIGHTARROW", $4),
                                $5,
                                createNode("COLON", $6),
                                $7
                        );
                }
                else {
                        $$ = processNodes("funcdef", 4,
                                createNode("NAME", $2),
                                $3,
                                $5,
                                $7
                        );
                        ($$->content) = string($1) + "$" + string($4);
                }

                // A function definitions is a declaration statement so SYMBOL TABLE ENTRY is to be generated for this
                // A function will have the type parameters -> test in this case
                // ($$->T) = type_function($3->T, $5->T);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "funcdef.1";

        }
        | DEF NAME parameters COLON suite  {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: funcdef non-terminal used\n");

                // DEF can be identified as operators and propogated up in AST
                // COLON does not add any special semantic meaning so it can be ignored
                // Please see special handling of function definitions in "processNodes"
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("funcdef", 5,
                                createNode("DEF", $1),
                                createNode("NAME",$2),
                                $3,
                                createNode("COLON",$4),
                                $5
                        );
                }
                else {
                        $$ = processNodes("funcdef", 3,
                                createNode("NAME",$2),
                                $3,
                                $5
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "funcdef.2";
        }
        ;

parameters:
        OPENING_BRACKET typedargslist CLOSING_BRACKET {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("parameters", 3,
                                createNode("OPENING_BRACKET",$1),
                                $2,
                                createNode("CLOSING_BRACKET",$3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "parameters";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "parameters.1";
        }
        | OPENING_BRACKET CLOSING_BRACKET {
                // Empty brackets do not have any such semantic significance in general.
                // But this non-terminal denotes parameters of a function so better to keep an empty string for parameters here.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("parameters" , 2,
                                createNode("OPENING_BRACKET", $1),
                                createNode("CLOSING_BRACKET", $2)
                        );
                }
                else {
                        // Construct a node with empty brackets to indicate empty brackets in AST
                        $$ = createNode("parameters", " " + string($1) + string($2) + " ");
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "parameters.2";
        }
        ;

typedargslist:
        tfpdef EQUAL test next_arg COMMA {
                // COMMA ignored as it has no semantic significance for AST.
                // Right recursive productions can be simplified to a single level in AST.
                // EQUAL can be identified as an operator and can be propogated up for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("typedargslist", 5,
                                $1,
                                createNode("EQUAL", $2),
                                $3,
                                $4,
                                createNode("COMMA", $5)
                        );
                }
                else {
                        $$ = $4;
                        ($$->type) = "typedargslist";
                        ASTNode* node = processNodes("EQUAL", 2, $1, $3);
                        (node->content) = string($2);
                        ($$->children).push_front(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "typedargslist.1";
        }
        | tfpdef EQUAL test next_arg {
                // Right recursive productions can be simplified to a single level in AST.
                // EQUAL can be identified as an operator and can be propogated up for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("typedargslist", 4,
                                $1,
                                createNode("EQUAL", $2),
                                $3,
                                $4
                        );
                }
                else {
                        $$ = $4;
                        ($$->type) = "typedargslist";
                        ASTNode* node = processNodes("EQUAL", 2, $1, $3);
                        (node->content) = string($2);
                        ($$->children).push_front(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "typedargslist.2";
        }
        | tfpdef next_arg COMMA {
                // COMMA ignored as it has no semantic significance for AST.
                // Right recursive productions can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("typedargslist", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "typedargslist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "typedargslist.3";
        }
        | tfpdef next_arg {
                // Right recursive productions can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("typedargslist", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "typedargslist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "typedargslist.4";
        }
        ;

next_arg:
        next_arg COMMA tfpdef EQUAL test {
                // Left recursive productions can be simplified to a single level in AST.
                // COMMA has no semantic meaning so it can be ignored
                // EQUAL can be identified as an operator and can be propogated up for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("next_arg" ,5,
                                $1,
                                createNode("COMMA", $2),
                                $3,
                                createNode("EQUAL", $4),
                                $5
                        );
                }
                else {
                        $$ = $1;
                        ASTNode* node = processNodes("EQUAL", 2, $3, $5);
                        (node->content) = string($4);
                        ($$->children).push_back(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "next_arg.1";
        }
        | next_arg COMMA tfpdef {
                // Left recursive productions can be simplified to a single level in AST.
                // COMMA has no semantic meaning so it can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("next_arg" ,3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "next_arg.2";
        }
        | %empty {
                // Will be ignored automatically for AST
                $$ = processNodes("next_arg", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "next_arg.3";
        }
        ;


tfpdef:
        NAME COLON test {
                // COLON can be identified as an operator and moved up here for simplifying the AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("tfpdef", 3,
                                createNode("NAME", $1),
                                createNode("COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("tfpdef", 2,
                                createNode("NAME", $1),
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "tfpdef.1";
        }
        | NAME  { // #notrequired
                // This is just like tfpdef is a terminal for the AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("tfpdef", 1,
                                createNode("NAME", $1)
                        );
                }
                else $$ = createNode("NAME", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "tfpdef.2";
        }
        ;

// ------------------ End of Segment 2 ------------------

// ------------------ Segment 3 ------------------

stmt:
        simple_stmt   {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: simple_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "stmt.1";
        }
        | compound_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: compound_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "stmt.2";
        }
        ;

simple_stmt:
        small_stmt next_small_stmt SEMI_COLON NEWLINE {
                // Right recursive productions can be simplified to a single level in AST
                // SEMI_COLON and NEWLINE place no semantic meaning except statement seperation so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("simple_stmt", 4,
                                $1,
                                $2,
                                createNode("SEMI_COLON", $3),
                                createNode("NEWLINE", $4)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "simple_stmt";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "simple_stmt.1";
        }
        | small_stmt next_small_stmt NEWLINE {
                // Right recursive productions can be simplified to a single level in AST
                // NEWLINE place no semantic meaning except statement seperation so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("simple_stmt", 3,
                                $1,
                                $2,
                                createNode("NEWLINE", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "simple_stmt";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "simple_stmt.2";
        }
        ;

next_small_stmt:
        next_small_stmt SEMI_COLON small_stmt {
                // Left recursive productions can be simplified to a single level in AST
                // SEMI_COLON is just a seperator and does not have much semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("next_small_stmt", 3,
                                $1,
                                createNode("SEMI_COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "next_small_stmt.1";
        }
        | %empty {
                // This will be automatically ignored by "processNodes" for an AST
                $$ = processNodes("next_small_stmt", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "next_small_stmt.2";
        }
        ;

small_stmt:
        flow_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("small_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "small_stmt.1";
        }
        | expr_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: expr_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("small_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "small_stmt.2";
        }
        | global_stmt {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("small_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "small_stmt.3";
        }
        | nonlocal_stmt {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("small_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "small_stmt.4";
        }
        | assert_stmt { // #notrequired
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("small_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "small_stmt.5";
        }
        ;

// ----------------------- End of Segment 3 -----------------------

// ----------------------- Segment 4 -----------------------

expr_stmt:
        testlist_star_expr annassign  {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: annotated assignment in expr_stmt\n");
                
                // It can be observed here that "annassign" is the operator and we can make "testlist_star_expr" a child
                // of "annassign" as a simplification for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("expr_stmt", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "expr_stmt";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "expr_stmt.1";
        }
        | testlist_star_expr AUGASSIGN testlist {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: augmented assignment in expr_stmt\n");
                
                // It can be observed here that AUGASSIGN is the operator which can be propagated for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("expr_stmt", 3,
                                $1,
                                createNode("AUGASSIGN", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("expr_stmt", 2,
                                $1,
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "expr_stmt.2";
        }
        | testlist_star_expr continued_expr_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: normal assignment in expr_stmt\n");
                
                // Right recursive productions can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("expr_stmt",2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "expr_stmt";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "expr_stmt.3";
        }
        ;

continued_expr_stmt:
        continued_expr_stmt EQUAL testlist_star_expr {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: testlist added\n");
                
                // Left recursive production can be simplified in AST and shown on a single level
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_expr_stmt", 3,
                                $1,
                                createNode("EQUAL", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                        if( ($$->content).length() > 0 && ($$->content) != EPSILON ) ($$->content) = ($$->content) + "$" + string($2);
                        else ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_expr_stmt.1";
        }
        | %empty {
                // Will be automatically ignored by "processNodes" for AST
                $$ = processNodes("continued_expr_stmt", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_expr_stmt.2";
        }
        ;     

annassign:
        COLON test EQUAL test {
                // COLON and EQUAL can be considered as operator here and propogated upwards for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("annassign", 4,
                                createNode("COLON", $1),
                                $2,
                                createNode("EQUAL", $3),
                                $4
                        );
                }
                else {
                        $$ = processNodes("annassign", 2,
                                $2,
                                $4
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "annassign.1";
        }
        | COLON test {
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually feel like an conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("annassign", 2,
                                createNode("COLON", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("annassign", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "annassign.2";
        }
        ;

testlist_star_expr:
        test continued_testlist COMMA {
                // COMMA can be ignored in AST as it has no significant semantic meaning
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_star_expr", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_star_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_star_expr.1";
        }
        | test continued_testlist {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: single test in testlist\n");
                
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_star_expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_star_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_star_expr.2";
        }
        | star_expr continued_testlist COMMA { // #notrequired
                // COMMA can be ignored in AST as it has no significant semantic meaning
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_star_expr", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_star_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_star_expr.3";
        }
        | star_expr continued_testlist {// #notrequired
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_star_expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_star_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_star_expr.4";
        }
        ;                     

flow_stmt:
        break_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: break_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("flow_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "flow_stmt.1";
        }
        | continue_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: continue_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("flow_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "flow_stmt.2";
        }
        | return_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: return_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("flow_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "flow_stmt.3";
        }
        | raise_stmt { // #notrequired
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: raise_stmt\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("flow_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "flow_stmt.4";
        }
        ;

break_stmt:
        BREAK {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("break_stmt", 1,
                                createNode("BREAK", $1)
                        );
                }
                else $$ = createNode("break_stmt", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "break_stmt.1";
        }
        ; 

continue_stmt:
        CONTINUE {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continue_stmt", 1,
                                createNode("CONTINUE", $1)
                        );
                }
                else $$ = createNode("continue_stmt", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continue_stmt.1";

        }
        ;

return_stmt:
        RETURN testlist {
                // This is a tough case. Here RETURN is a unary operator and thus we cannot directly
                // add RETURN in the "content" of "testlist" node -> That would actually feel like part of testing expression list.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("return_stmt", 2,
                                createNode("RETURN", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("return_stmt", 1, $2);
                        // $$ = $2;
                        // ($$->type) = "return_stmt";
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "return_stmt.1";
        }
        | RETURN {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("return_stmt", 1,
                                createNode("RETURN", $1)
                        );
                }
                else $$ = createNode("return_stmt", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "return_stmt.2";
        }
        ;

// #notrequired
raise_stmt: 
        RAISE test FROM test {
                // RAISE and FROM can be seen as operators and propogated upward in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("raise_stmt", 4,
                                createNode("RAISE", $1),
                                $2,
                                createNode("FROM", $3),
                                $4
                        );
                }
                else {
                        $$ = processNodes("raise_stmt", 2,
                                $2,
                                $4
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "raise_stmt.1";
        }
        | RAISE test {
                // This is a tough case. Here RAISE is a unary operator and thus we cannot directly
                // add RAISE in the "content" of "test" node -> That would actually feel like part of conditional test.
                // RAISE can be seen as operators and propogated upward in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("raise_stmt", 2,
                                createNode("RAISE", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("raise_stmt", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "raise_stmt.2";
        }
        | RAISE {
                // This is just a terminal from perspective of AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("raise_stmt", 1,
                                createNode("RAISE", $1)
                        );
                }
                else $$ = createNode("raise_stmt", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "raise_stmt.3";
        }
        ;

global_stmt:
        GLOBAL NAME stmt_helper {
                // GLOBAL can be identified as the operator here and kept at top.
                // This is a right recursive production so can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("global_stmt", 3,
                                createNode("GLOBAL", $1),
                                createNode("NAME", $2),
                                $3
                        );
                }
                else {
                        $$ = $3;
                        ($$->type) = "global_stmt";
                        ASTNode* node = createNode("NAME", $2);
                        ($$->children).push_front(node);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "global_stmt.1";
        }
        ;

// #notrequired
nonlocal_stmt:
        NONLOCAL NAME stmt_helper {
                // NONLOCAL can be identified as the operator here and kept at top.
                // This is a right recursive production so can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("nonlocal_stmt", 3,
                                createNode("NONLOCAL", $1),
                                createNode("NAME", $2),
                                $3
                        );
                }
                else {
                        $$ = $3;
                        ($$->type) = "nonlocal_stmt";
                        ASTNode* node = createNode("NAME", $2);
                        ($$->children).push_front(node);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "nonlocal_stmt.1";
        }
        ;

// #notrequired
assert_stmt:
        ASSERT test COMMA test {
                // ASSERT and COMMA are operators so can be propogated upwards.
                // COMMA has no significant semantic meaning so it can be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("assert_smt", 4,
                                createNode("ASSERT", $1),
                                $2,
                                createNode("COMMA", $3),
                                $4
                        );
                }
                else {
                        $$ = processNodes("assert_smt", 2,
                                $2,
                                $4
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "assert_stmt.1";
        }
        | ASSERT test {
                // This is a tough case. Here ASSERT is a unary operator and thus we cannot directly
                // add ASSERT in the "content" of "test" node -> That would actually look like a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("assert_stmt", 2,
                                createNode("ASSERT", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("assert_stmt", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "assert_stmt.2";
        }
        ;

stmt_helper:
        stmt_helper COMMA NAME {
                // Left recursive productions can be simplified to a single level in AST
                // COMMA has no semantic meaning so it can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("stmt_helper", 3,
                                $1,
                                createNode("COMMA", $2),
                                createNode("NAME", $3)
                        );
                }
                else {
                        $$ = $1;
                        ASTNode* node = createNode("NAME", $3);
                        ($$->children).push_back(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "stmt_helper.1";
        }
        | %empty {
                // Will be ignored by "processNodes" for AST
                $$ = processNodes("stmt_helper", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "stmt_helper.2";
        }
        ;

// Section 5

compound_stmt:
        if_stmt  {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: if_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("compound_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "compound_stmt.1";
        }
        | while_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: while_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("compound_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "compound_stmt.2";
        }
        | for_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: for_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("compound_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "compound_stmt.3";
        }
        | try_stmt { // #notrequired
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: try_stmt selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("compound_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "compound_stmt.4";
        }
        | funcdef {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: func_def selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("compound_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "compound_stmt.5";
        }
        | classdef {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: class_def selected \n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("compound_stmt", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "compound_stmt.6";
        }
        ;

if_stmt:
        IF test COLON suite elif_stmt else_stmt {
                // IF can be propogated as operator and COLON can be ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("if_stmt", 6,
                                createNode("IF", $1),
                                $2,
                                createNode("COLON", $3),
                                $4,
                                $5,
                                $6
                        );
                }
                else {
                        $$ = processNodes("if_stmt", 4,
                                $2,
                                $4,
                                $5,
                                $6
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "if_stmt.1";
        }
        ;

elif_stmt:
        elif_stmt ELIF test COLON suite {
                // ELIF can be propogated as operator and COLON can be ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("elif_stmt", 5,
                                $1,
                                createNode("ELIF", $2),
                                $3,
                                createNode("COLON", $4),
                                $5
                        );
                }
                else {
                        $$ = processNodes("elif_stmt", 3,
                                $1,
                                $3,
                                $5
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "elif_stmt.1";
        }
        | %empty {
                // Will be ignored by "processNodes" for AST
                $$ = processNodes("elif_stmt", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "elif_stmt.2";
        }
        ;


else_stmt:
        ELSE COLON suite {
                // This is a tough case. Here ELSE is a unary operator and thus we cannot directly
                // add ELSE in the "content" of "suite" node -> That would actually feel like a part of expression suite.
                // ELSE can be propogated as operator and COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("else_stmt", 3,
                                createNode("ELSE", $1),
                                createNode("COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("else_stmt", 1, $3);
                        ($$->content) = string($1);
                        // Below code works if the operator ELSE is not considered as an unary operator.
                        // $$ = $3;
                        // ($$->type) = "else_stmt";
                        // ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "else_stmt.1";
        }
        | %empty {
                // Will be ignored by "processNodes" for AST
                $$ = processNodes("else_stmt", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "else_stmt.2";
        }
        ;

while_stmt:
        WHILE test COLON suite else_stmt {
                // WHILE and COLON are operators. WHILE is propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("while_stmt", 5,
                                createNode("WHILE", $1),
                                $2,
                                createNode("COLON", $3),
                                $4,
                                $5
                        );
                }
                else {
                        $$ = processNodes("while_stmt", 3,
                                $2,
                                $4,
                                $5
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "while_stmt.1";
        }
        ;  

// #changegrammar
forcheck: 
        exprlist IN testlist {
                // FOR, IN and COLON are operators. FOR and IN are propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("forcheck", 3,
                                $1,
                                createNode("IN", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("forcheck", 2,
                                $1,
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "forcheck.1";
        }
        ;

for_stmt:
        FOR forcheck COLON suite else_stmt {
                // FOR, IN and COLON are operators. FOR and IN are propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("for_stmt", 5,
                                createNode("FOR", $1),
                                $2,
                                createNode("COLON", $3),
                                $4,
                                $5
                        );
                }
                else {
                        $$ = processNodes("for_stmt", 3,
                                $2,
                                $4,
                                $5
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "for_stmt.1";
        }
        ;

/* for_stmt:
        FOR exprlist IN testlist COLON suite else_stmt {
                // FOR, IN and COLON are operators. FOR and IN are propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("for_stmt", 7,
                                createNode("FOR", $1),
                                $2,
                                createNode("IN", $3),
                                $4,
                                createNode("COLON", $5),
                                $6,
                                $7
                        );
                }
                else {
                        $$ = processNodes("for_stmt", 4,
                                $2,
                                $4,
                                $6,
                                $7
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "for_stmt.1";
        }
        ; */

// #notrequired
try_stmt:
        TRY COLON suite except_stmt else_stmt finally_stmt {
                // TRY and COLON are operators. TRY is propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("try_stmt", 6,
                                createNode("TRY", $1),
                                createNode("COLON", $2),
                                $3,
                                $4,
                                $5,
                                $6
                        );
                }
                else {
                        $$ = processNodes("try_stmt", 4,
                                $3,
                                $4,
                                $5,
                                $6
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "try_stmt.1";
        }
        | TRY COLON suite FINALLY COLON suite {
                // TRY, FINALLY and COLON are operators. TRY and FINALLY are propogated and COLON ignored for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("try_stmt", 6,
                                createNode("TRY", $1),
                                createNode("COLON", $2),
                                $3,
                                createNode("FINALLY", $4),
                                createNode("COLON", $5),
                                $6
                        );
                }
                else {
                        $$ = processNodes("try_stmt", 2,
                                $3,
                                $6
                        );
                        ($$->content) = string($1) + "$" + string($4);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "try_stmt.2";
        }
        ;

// #notrequired
except_stmt:
        except_stmt except_clause COLON suite {
                // Left recursive production can be simplified to a single level in AST
                // Here COLON is the operator and as it is the only operator so it is not ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("except_stmt",4,
                                $1,
                                $2,
                                createNode("COLON", $3),
                                $4
                        );
                }
                else {
                        $$ = $1;
                        ASTNode* node = processNodes("COLON", 2,
                                        $2,
                                        $4
                        );
                        (node->content) = string($3);
                        ($$->children).push_back(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "except_stmt.1";
        }
        | except_clause COLON suite {
                // Here COLON is the operator and as it is the only operator so it is not ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("except_stmt", 3,
                                $1,
                                createNode("COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("except_stmt", 2,
                                $1,
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "except_stmt.2";
        }
        ;

// #notrequired
finally_stmt:
        FINALLY COLON suite {
                // This is a tough case. Here FINALLY is a unary operator and thus we cannot directly
                // add FINALLY in the "content" of "suite" node -> That would actually seem like part of the suite of statements.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("finally_stmt", 3,
                                createNode("FINALLY", $1),
                                createNode("COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("finally_stmt", 1, $3);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "finally_stmt.1";
        }
        | %empty   {
                // Will be ignored by "processNodes" for AST
                $$ = processNodes("finally_stmt", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "finally_stmt.2";
        }
        ;

// #notrequired
except_clause:
        EXCEPT test AS NAME {
                // EXCEPT and AS are operators here and can be propagated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("except_clause", 4,
                                createNode("EXCEPT", $1),
                                $2,
                                createNode("AS", $3),
                                createNode("NAME", $4)
                        );
                }
                else {
                        $$ = processNodes("except_clause", 2,
                                $2,
                                createNode("NAME", $4)
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "except_clause.1";
        }
        | EXCEPT test {
                // This is a tough case. Here EXCEPT is a unary operator and thus we cannot directly
                // add EXCEPT in the "content" of "test" node -> That would actually seem like a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("except_clause", 2,
                                createNode("EXCEPT", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("except_clause", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "except_clause.2";
        }
        | EXCEPT {
                // This is just like a terminal for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("except_clause", 1,
                                createNode("EXCEPT", $1)
                        );
                }
                else $$ = createNode("EXCEPT", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "except_clause.3";
        }
        ;

suite:
        simple_stmt {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("suite", 1, $1);
                else {
                        $$ = $1;
                        ($$->type) = "suite";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "suite.1";
        }
        | NEWLINE INDENT stmts DEDENT {
                // INDENT and DEDENT do not add much to semantic meaning so can be ignored
                // NEWLINE does not add any semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("suite", 4,
                                createNode("NEWLINE", $1),
                                createNode("INDENT", $2),
                                $3,
                                createNode("DEDENT", $4)
                        );
                }
                else {
                        $$ = $3;
                        ($$->type) = "suite";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "suite.2";
        }
        ;

stmts:
        stmts stmt {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("stmts", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "stmts.1";
        }
        | stmt {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("stmts", 1, $1);
                else {
                        $$ = $1;
                        ($$->type) = "stmts";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "stmts.2";
        }
        ;

test:
        or_test IF or_test ELSE test {
                // Right recursive productions can be reduced to a single level in AST.
                // However, a test statement can be long in general so better not convert to single level to protect semantic meaning.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("test", 5,
                                $1,
                                createNode("IF", $2),
                                $3,
                                createNode("ELSE", $4),
                                $5
                        );
                }
                else {
                        // It's not necessary that this will make a node $$ with 3 children. See the working of
                        // "processNodes". If $1, $2 or $3 have no children and no content then they will be ignored and
                        // not added as a child to $$ node.
                        $$ = processNodes("test", 3,
                                $1,
                                $3,
                                $5
                        );
                        
                        // The parser semantic actions maintain an invariant that any non-terminal if produces empty string will
                        // have EPSILON in it's contents. Thus, whenever "content" is added to a node after calling "processNodes"
                        // it should be checked whether the number of children of the node is zero or not.
                        // if(($$->children).size() > 0) ($$->content) = string($2) + "$" + string($4);

                        // The above concept is ignored for now - It is may give some issues
                        ($$->content) = string($2) + "$" + string($4);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "test.1";
        }
        | or_test {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("test", 1, $1);
                else {
                        $$ = $1;
                        ($$->type) = "test";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "test.2";
        }
        ;

test_nocond:
        or_test {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("test_nocond", 1, $1);
                else {
                        $$ = $1;
                        ($$->type) = "test_nocond";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "test_nocond.1";
        }
        ;

or_test:
        and_test continued_or_test {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("or_test", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "or_test";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "or_test.1";
        }
        ;

continued_or_test:
        continued_or_test OR and_test {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_or_test", 3,
                                $1,
                                createNode("OR", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + string($2);
                        else ($$->content) = string($2);
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_or_test.1";
        }
        | %empty {
                // Will be ignored in AST automatically by processNodes
                $$ = processNodes("continued_or_test", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_or_test.2";
        }
        ;

and_test:
        not_test continued_and_test {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("and_test", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "and_test";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "and_test.1";
        }
        ;

continued_and_test:
        continued_and_test AND not_test {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_and_test", 3,
                                $1,
                                createNode("AND", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + string($2);
                        else ($$->content) = string($2);
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_and_test.1";
        }
        | %empty {
                // Will be ignored in AST automatically by processNodes
                $$ = processNodes("continued_and_test", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_and_test.2";
        }
        ;

not_test:
        NOT not_test {
                // This is a tough case. Here NOT is a unary operator and thus we cannot directly
                // add NOT in the "content" of "comparison" node -> That would actually feel like included in comparison expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("not_test", 2,
                                createNode("NOT", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("not_test", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "not_test.1";
        }
        | comparison {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("not_test", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "not_test.2";
        }
        ;

comparison:
        expr comparison_stmt {
                // A right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comparison", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "comparison";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comparison.1";
        }
        ;

comparison_stmt:
        comparison_stmt comp_op expr {
                // A left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comparison_stmt", 3,
                                $1,
                                $2,
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + ($2->content);
                        else ($$->content) = ($2->content);
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comparison_stmt.1";
        }
        | %empty {
                // Will be ignored by processNodes automatically for AST
                $$ = processNodes("comparison_stmt", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comparison_stmt.2";
        }
        ;

comp_op:
        COMP_OP {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_op", 1,
                                createNode("COMP_OP", $1)
                        );
                }
                else $$ = createNode("COMP_OP", string($1));

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_op.1";
        }
        | IN    {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_op", 1,
                                createNode("IN", $1)
                        );
                }
                else $$ = createNode("IN", string($1));

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_op.2";
        }
        | NOT IN {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_op", 2,
                                createNode("NOT", $1),
                                createNode("IN", $2)
                        );
                }
                else $$ = createNode("NOT-IN", string($1) + string($2));

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_op.3";
        }
        | IS     {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_op", 1,
                                createNode("IS", $1)
                        );
                }
                else $$ = createNode("IS", string($1));

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_op.4";
        }
        | IS NOT {
                // This is like a terminal being represented using a non-terminal
                // This can be simplified in the AST to a single node.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_op", 1,
                                createNode("IS", $1),
                                createNode("NOT", $2)
                        );
                }
                else $$ = createNode("IS-NOT", string($1) + string($2));

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_op.5";
        }
        ;

// #notrequired
star_expr:
        STAR expr  {
                // This is a tough case. Here STAR is a unary operator and thus we cannot directly
                // add STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("star_expr", 2,
                                createNode("STAR", $1),
                                $2
                        );
                }
                else {
                        if(($$->type) == "expr") $$ = processNodes("star_expr", 1, $2);
                        ($$->content) = ($$->content) + " " + string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "star_expr.1";
        }
        ;

expr:
        xor_expr continued_xor_expr {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "expr.1";
        }
        ;

continued_xor_expr:
        continued_xor_expr BITWISE_OR xor_expr {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_xor_expr", 3,
                                $1,
                                createNode("BITWISE_OR", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_xor_expr.1";
        }
        | %empty {
                // Will be ignored automatically in AST by processNodes.
                $$ = processNodes("continued_xor_expr", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_xor_expr.2";
        }
        ;

xor_expr:
        and_expr continued_and_expr {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("xor_expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "xor_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "xor_expr.1";
        }
        ;

continued_and_expr:
        continued_and_expr CARET and_expr {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_and_expr", 3,
                                $1,
                                createNode("CARET", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_and_expr.1";
        }
        | %empty {
                // Will be ignored automatically in AST by processNodes.
                $$ = processNodes("continued_and_expr", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_and_expr.2";
        }
        ;

and_expr:
        shift_expr continued_shift_expr {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("and_expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "and_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "and_expr.1";
        }
        ;
    
continued_shift_expr:
        continued_shift_expr BITWISE_AND shift_expr {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_shift_expr", 3,
                                $1,
                                createNode("BITWISE_AND", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_shift_expr.1";
        }
        | %empty {
                // Will be ignored automatically in AST by processNodes.
                $$ = processNodes("continued_shift_expr", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_shift_expr.2";
        }
        ;

shift_expr:
        arith_expr continued_arith_expr {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("shift_expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "shift_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "shift_expr.1";
        }
        ;

continued_arith_expr:
        continued_arith_expr LEFT_SHIFT arith_expr {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_arith_expr", 3,
                                $1,
                                createNode("LEFT_SHIFT", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_arith_expr.1";
        }
        | continued_arith_expr RIGHT_SHIFT arith_expr {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_arith_expr", 3,
                                $1,
                                createNode("RIGHT_SHIFT", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_arith_expr.2";
        }
        | %empty {
                // Will be ignored automatically in AST by processNodes.
                $$ = processNodes("continued_arith_expr", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_arith_expr.3";
        }
        ;

arith_expr:
        term continued_term {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("arith_expr", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "arith_expr";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "arith_expr.1";
        }
        ;

continued_term:
        continued_term PLUS term {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_term", 3,
                                $1,
                                createNode("PLUS", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_term.1";
        }
        | continued_term MINUS term {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_term", 3,
                                $1,
                                createNode("MINUS", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_term.2";
        }
        | %empty {
                // Will be ignored automatically in AST by processNodes.
                $$ = processNodes("continued_term", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_term.3";
        }
        ;

term:
        factor continued_factor {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("term", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "term";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "term.1";
        }
        ;

continued_factor:
        continued_factor STAR factor {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_factor", 3,
                                $1,
                                createNode("STAR", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_factor.1";
        }
        | continued_factor DIV factor {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_factor", 3,
                                $1,
                                createNode("DIV", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_factor.2";
        }
        | continued_factor AT factor {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_factor", 3,
                                $1,
                                createNode("AT", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_factor.3";
        }
        | continued_factor REM factor {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_factor", 3,
                                $1,
                                createNode("REM", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_factor.4";
        }
        | continued_factor FLOOR_DIV factor {
                // Left recursive productions can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_factor", 3,
                                $1,
                                createNode("FLOOR_DIV", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = ($$->content) + "$" + $2;
                        else ($$->content) = $2;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_factor.5";
        }
        | %empty {
                // Will be ignored automatically in AST by processNodes.
                $$ = processNodes("continued_factor", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_factor.6";
        }
        ;

factor:
        PLUS factor {
                // Right recursive production can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("factor", 2,
                                createNode("PLUS", $1),
                                $2
                        );
                }
                else {
                        $$ = $2;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = string($1) + "$" + ($$->content);
                        else ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "factor.1";
        }
        | MINUS factor {
                // Right recursive production can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("factor", 2,
                                createNode("MINUS", $1),
                                $2
                        );
                }
                else {
                        $$ = $2;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = string($1) + "$" + ($$->content);
                        else ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "factor.2";
        }
        | TILDE factor {
                // Right recursive production can be simplified to a single level in AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("factor", 2,
                                createNode("TILDE", $1),
                                $2
                        );
                }
                else {
                        $$ = $2;
                        if(($$->content).length() > 0 && ($$->content) != EPSILON) ($$->content) = string($1) + "$" + ($$->content);
                        else ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "factor.3";
        }
        | power {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("factor", 1, $1);
                }
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "factor.4";
        }
        ;

power:
        atom_expr DOUBLE_STAR factor {
                // DOUBLE_STAR is the operator here. Can be propogated up.
                // See the special handling in "ProcessNodes".
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("power", 3,
                                $1,
                                createNode("DOUBLE_STAR", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("power", 2,
                                $1,
                                $3
                        );
                        ($$->content) = $2;
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "power.1";
        }
        | atom_expr {
                if(isAST == false) $$ = processNodes("power", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "power.2";
        }
        ;

atom_expr:
        AWAIT atom trailers { // #notrequired
                // AWAIT is an operator here so can be used accordingly.
                // Special handling done for AWAIT in "processNodes".
                // Writing AWAIT as the 3rd argument is NOT A TYPO here. Please see "processNodes" function.
                if(isAST == false) {
                        $$ = processNodes("atom_expr", 3,
                                createNode("AWAIT", $1),
                                $2,
                                $3
                        );
                }
                else {
                        $$ = processNodes("atom_expr", 3,
                                $2,
                                $3,
                                createNode("AWAIT", $1)
                        );
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom_expr.1";
        }
        | atom trailers {
                $$ = processNodes("atom_expr", 2,
                        $1,
                        $2
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom_expr.2";
        }
        ;

trailers:
        trailers trailer {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: trailer added\n");
                
                // This is a left recursive production which can be simplified in the AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("trailers", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "trailers.1";
        }
        | %empty {
                // Will be ignored in processNodes automatically for AST.
                $$ = processNodes("trailers", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "trailers.2";
        }
        ;

atom:
        OPENING_BRACKET testlist_comp CLOSING_BRACKET {
                // Simplification of BRACKETS is possible for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 3,
                                createNode("OPENING_BRACKET", $1),
                                $2,
                                createNode("CLOSING_BRACKET", $3)
                        );
                }
                else {
                        // This is a tough case. Here () will have to be treated as UNARY operators.
                        $$ = processNodes("atom", 1, $2);
                        ($$->content) = " " + string($1) + string($3) + " ";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.1";
        }
        | OPENING_BRACKET CLOSING_BRACKET {
                // The case of empty brackets is irrelevant from a semantic perspective.
                // In AST such cases should be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 2, // "atom: OPENING_BRACKET CLOSING_BRACKET\n
                                createNode("OPENING_BRACKET", $1),
                                createNode("CLOSING_BRACKET", $2)
                        );
                }
                else {
                        // Empty brackets especially kept to preserve the meaning of the program
                        $$ = createNode("atom", " " + string($1) + string($2) + " ");
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.2";
        }
        | OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET {
                // Simplification of BRACKETS is possible for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 3, // "atom: OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET\n
                                createNode("OPENING_SQ_BRACKET", $1),
                                $2,
                                createNode("CLOSING_SQ_BRACKET", $3)
                        );
                }
                else {
                        // This is a tough case. Here [] will have to be treated as UNARY operators.
                        $$ = processNodes("atom", 1, $2);
                        ($$->content) = " " + string($1) + string($3) + " ";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.3";
        }
        | OPENING_SQ_BRACKET CLOSING_SQ_BRACKET {
                // The case of empty brackets is irrelevant from a semantic perspective.
                // In AST such cases should be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 2, // "atom: OPENING_SQ_BRACKET CLOSING_SQ_BRACKET\n
                                createNode("OPENING_SQ_BRACKET", $1),
                                createNode("CLOSING_SQ_BRACKET", $2)
                        );
                }
                else {
                        // Empty brackets especially kept to preserve the meaning of the program
                        $$ = createNode("atom", " " + string($1) + string($2) + " ");
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.4";
        }
        | OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET { // #notrequired
                // Simplification of BRACKETS is possible for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 3, // "atom: OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET\n
                                createNode("OPENING_CURLY_BRACKET", $1),
                                $2,
                                createNode("CLOSING_CURLY_BRACKET", $3)
                        );
                }
                else {
                        // This is a tough case. Here {} will have to be treated as UNARY operators.
                        $$ = processNodes("atom", 1, $2);
                        ($$->content) = " " + string($1) + string($3) + " ";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.5";
        }
        | OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET { // #notrequired
                // The case of empty brackets is irrelevant from a semantic perspective.
                // In AST such cases should be ignored.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 2, // "atom: OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET\n
                                createNode("OPENING_CURLY_BRACKET", $1),
                                createNode("CLOSING_CURLY_BRACKET", $2)
                        );
                }
                else {
                        // Empty brackets especially kept to preserve the meaning of the program
                        $$ = createNode("atom", " " + string($1) + string($2) + " ");
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.6";
        }
        | NAME {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'NAME' used\n");
                
                // An "atom" is an element of the code. It can be a terminal of the AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 1,
                                createNode("NAME", $1)
                        );
                }
                else $$ = createNode("NAME", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.7";
        }
        | NUMBER  {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'NUMBER' used\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 1,
                                createNode("NUMBER", $1)
                        );
                }
                else $$ = createNode("NUMBER", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.8";
        }
        | strings {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'STRING' used\n");
                
                // If the "atom" is a string then in the AST it can be treated as a terminal only.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("atom", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.9";
        }      
        | ELLIPSES_LITERAL { // #notrequired
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'ELLIPSES_LITERAL' used\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 1,
                                createNode("ELLIPSES_LITERAL", $1)
                        );
                }
                else $$ = createNode("ELLIPSES_LITERAL", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.10";
        }
        | TOKEN_TRUE {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 1,
                                createNode("TOKEN_TRUE", $1)
                        );
                }
                else $$ = createNode("TOKEN_TRUE", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.11";
        }
        | TOKEN_FALSE {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 1,
                                createNode("TOKEN_FALSE", $1)
                        );
                }
                else $$ = createNode("TOKEN_FALSE", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.12";
        }
        | TOKEN_NONE {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("atom", 1,
                                createNode("TOKEN_NAME", $1)
                        );
                }
                else $$ = createNode("TOKEN_NONE", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "atom.13";
        }

strings:
        strings STRING  {
                // Left recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("strings", 2,
                                $1,
                                createNode("STRING", $2)
                        );
                }
                else {
                        $$ = $1;
                        ASTNode* node = createNode("STRING", $2);
                        ($$->children).push_back(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "strings.1";
        }
        | STRING {
                // From the perspective of an AST, a string is an "atom"
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("strings", 1,
                                createNode("STRING",$1)
                        );
                }
                else $$ = createNode("STRING", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "strings.2";
        }
        ;

testlist_comp:
        test comp_for { // #notrequired
                // Simplification maybe possible but can make AST intractable diagramatically due to oversimplification.
                $$ = processNodes("testlist_comp", 2,
                        $1,
                        $2
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_comp.1";
        }
        | test continued_testlist COMMA {
                // COMMA ignored for AST as it has no semantic significance
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_comp", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_comp";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_comp.2";
        }
        | test continued_testlist {
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_comp", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_comp";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_comp.3";
        }
        | star_expr comp_for {
                // Simplification maybe possible but can make AST intractable diagramatically due to oversimplification.
                $$ = processNodes("testlist_comp", 2,
                        $1,
                        $2
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_comp.4";
        }
        | star_expr continued_testlist COMMA {
                // COMMA ignored for AST as it has no semantic significance
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_comp", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_comp";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_comp.5";
        }
        | star_expr continued_testlist {
                // Right recursive production can be simplified to a single level for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist_comp", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist_comp";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist_comp.6";
        }
        ;

continued_testlist:
        continued_testlist COMMA test  {
                // Left recursive production can be simplified to a single level in AST
                // COMMA has no significant semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_testlist", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_testlist.1";
        }
        | continued_testlist COMMA star_expr { // #notrequired
                // Left recursive production can be simplified to a single level in AST
                // COMMA has no significant semantic meaning so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_testlist", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_testlist.2";
        }
        | %empty  {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: no further tests added\n");
                
                // Will be automatically ignored by "processNodes" for AST
                $$ = processNodes("continued_testlist", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_testlist.3";
        }      
        ;

trailer:
        OPENING_BRACKET arglist CLOSING_BRACKET {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: arglist within brackets added \n");
                
                // Brackets removed for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("trailer", 3,
                                createNode("OPENING_BRACKET", $1),
                                $2,
                                createNode("CLOSING_BRACKET", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "trailer";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "trailer.1";
        }
        | OPENING_BRACKET CLOSING_BRACKET {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: empty brackets added \n");
                
                // Empty brackets have no significance in AST.
                // However, to avoid oversimplification of AST they are kept as a single terminal.
                // Special "empty bracket" simplification is done in "processNodes" function.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("trailer", 2,
                                createNode("OPENING_BRACKET", $1),
                                createNode("CLOSING_BRACKET", $2)
                        );
                }
                else $$ = createNode("trailer", " " + string($1) + string($2) + " ");
                
                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "trailer.2";
        }
        | OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET {
                // Brackets removed for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("trailer", 3,
                                createNode("OPENING_SQ_BRACKET", $1),
                                $2,
                                createNode("CLOSING_SQ_BRACKET", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "trailer";
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "trailer.3";
        }
        | DOT NAME {
                // Special simplification for AST - Remove the extra "trailer" node and directly write the non-terminal.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("trailer", 2,
                                createNode("DOT", $1),
                                createNode("NAME", $2)
                        );
                }
                else $$ = createNode("trailer", string($1) + " " + string($2));

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "trailer.4";
        }
        ; 

// #notrequired
subscriptlist:
        subscript continued_subscript COMMA {
                // COMMA will have no semantic meaning it is just a seperator - Can be ignored
                // AST simplification for right recursive production. Bring all terms on a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscriptlist", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "subscriptlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscriptlist.1";

        }
        | subscript continued_subscript {
                // AST simplification for right recursive production. Bring all terms on a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscriptlist", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "subscriptlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscriptlist.2";
        }
        ;

// #notrequired
continued_subscript:
        continued_subscript COMMA subscript  {
                // Simplification in AST possible for left recursive productions to bring all terms on a single level.
                // COMMA can be ignored because that has no semantic significance.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_subscript", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_subscript.1";
        }
        | %empty {
                $$ = processNodes("continued_subscript", 0); // Will be ignored in processNodes automatically.

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_subscript.2";
        }
        ;

// #notrequired
subscript:
        test {
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("subscript", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.1";
        }
        | test COLON test sliceop { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                // Also, how can we simplify this node further by simplifying "sliceop" in AST ?
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 4,
                                $1,
                                createNode("COLON", $2),
                                $3,
                                $4
                        );
                }
                else {
                        $$ = processNodes("subscript", 3,
                                $1,
                                $3,
                                $4
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.2";
        }
        | test COLON test { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 3,
                                $1,
                                createNode("COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("subscript", 2,
                                $1,
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.3";
        }
        | test COLON sliceop { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 3,
                                $1,
                                createNode("COLON", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("subscript", 2,
                                $1,
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.4";
        }
        | test COLON { // #notrequired
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually seem to be a part of conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 2,
                                $1,
                                createNode("COLON", $2)
                        );
                }
                else {
                        $$ = processNodes("subscript", 1, $1);
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.5";
        }
        | COLON test sliceop { // #notrequired
                // Semantically this seems to have COLON as the operator. But this needs confirmation.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 3,
                                createNode("COLON", $1),
                                $2,
                                $3
                        );
                }
                else {
                        $$ = processNodes("subscript", 2,
                                $2,
                                $3
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.6";
        }
        | COLON test { // #notrequired
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually seem to be a part of conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 2,
                                createNode("COLON", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("subscript", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.7";
        }
        | COLON sliceop { // notrequired
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "sliceop" node -> That would actually seem to be a part of slicing operator.
                // However, this is a rarely occuring case - Can somekind of simplification be done here ?
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 2,
                                createNode("COLON", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("subscript", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.8";
        }
        | COLON {
                // This behaves like a terminal for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("subscript", 1,
                                createNode("COLON", $1)
                        );
                }
                else $$ = createNode("COLON", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "subscript.9";
        }
        ;

// #notrequired
sliceop:
        COLON test {
                // This is a tough case. Here COLON is a unary operator and thus we cannot directly
                // add COLON in the "content" of "test" node -> That would actually seem to be an operator in conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("sliceop", 2,
                                createNode("COLON", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("sliceop", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "sliceop.1";
        }
        | COLON {
                // This behaves like a terminal for AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("sliceop", 1,
                                createNode("COLON", $1)
                        );
                }
                else $$ = createNode("COLON", $1);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "sliceop.2";
        }
        ;


exprlist:
        expr continued_exprlist COMMA {
                // COMMA is not important from semantic perspective so ignored in AST.
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("exprlist", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "exprlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "exprlist.1";
        }
        | expr continued_exprlist {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("exprlist", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "exprlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "exprlist.2";
        }
        | star_expr continued_exprlist COMMA {
                // COMMA is not important from semantic perspective so ignored in AST.
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("exprlist", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "exprlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "exprlist.3";
        }
        | star_expr continued_exprlist {
                // Right recursive production can be simplified in AST to a single level.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("exprlist", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "exprlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "exprlist.4";
        }
        ;

continued_exprlist:
        continued_exprlist COMMA expr {
                // Left recursive production can be simplified in AST to a single level.
                // COMMA has no semantic meaning as such and thus can be ignored here.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_exprlist", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_exprlist.1";
        }
        | continued_exprlist COMMA star_expr { // #notrequired
                // Left recursive production can be simplified in AST to a single level.
                // COMMA has no semantic meaning as such and thus can be ignored here.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_exprlist", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_exprlist.2";
        }
        | %empty {
                // Will be ignored automatically in case of AST
                $$ = processNodes("continued_exprlist", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_exprlist.3";
        }
        ;

testlist:
        test continued_comma_test COMMA {
                // COMMA have no signifiance is semantic meaning so it is ignored
                // Left recursive production can be simplified into a single level in an AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist.1";
        }
        | test continued_comma_test {
                // Left recursive production can be simplified into a single level in an AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("testlist", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "testlist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "testlist.2";
        }
        ;

continued_comma_test:
        continued_comma_test COMMA test {
                // Left recursive production can be simplified into a single level in an AST
                // COMMA can be ignored because it carries no semantic meaning
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_comma_test", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_comma_test.1";
        }
        | %empty {
                // Will be automatically ignored for AST by "processNodes"
                $$ = processNodes("continued_comma_test", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_comma_test.2";
        }
        ; 

// #notrequired
dictorsetmaker:
        test COLON test comp_for {
                // COLON can be identified as the only operator and propagated upwards in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 4,
                                $1,
                                createNode("COLON", $2),
                                $3,
                                $4
                        );
                }
                else {
                        $$ = processNodes("dictorsetmaker", 3,
                                $1,
                                $3,
                                $4
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.1";
        }
        | test COLON test continued_dictorset COMMA {
                // COMMA has no significant semantic meaning so it can be ignored.
                // Right recursive production can be simplified in a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 5,
                                $1,
                                createNode("COLON", $2),
                                $3,
                                $4,
                                createNode("COMMA", $5)
                        );
                }
                else {
                        $$ = $4;
                        ($$->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("COLON", 2, $1, $3);
                        (node->content) = string($2);
                        ($$->children).push_front(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.2";

        }
        | test COLON test continued_dictorset {
                // Right recursive production can be simplified in a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 4,
                                $1,
                                createNode("COLON", $2),
                                $3,
                                $4
                        );
                }
                else {
                        $$ = $4;
                        ($$->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("COLON", 2, $1, $3);
                        (node->content) = string($2);
                        ($$->children).push_front(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.3";
        }
        | DOUBLE_STAR expr comp_for {
                // DOUBLE_STAR can be identified as operator and propagated upwards in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 3,
                                createNode("DOUBLE_STAR", $1),
                                $2,
                                $3
                        );
                }
                else {
                        $$ = processNodes("dictorsetmaker", 2,
                                $2,
                                $3
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.4";
        }
        | DOUBLE_STAR expr continued_dictorset COMMA {
                // COMMA has no significant semantic meaning so it can be ignored.
                // Right recursive production can be simplified in a single level in AST
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add DOUBLE_STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 4,
                                createNode("DOUBLE_STAR", $1),
                                $2,
                                $3,
                                createNode("COMMA", $4)
                        );
                }
                else {
                        $$ = $3;
                        ($$->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("DOUBLE_STAR", 1, $2);
                        (node->content) = string($1);
                        ($$->children).push_front(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.5";
        }
        | DOUBLE_STAR expr continued_dictorset {
                // Right recursive production can be simplified in a single level in AST
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add DOUBLE_STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 3,
                                createNode("DOUBLE_STAR", $1),
                                $2,
                                $3
                        );
                }
                else {
                        $$ = $3;
                        ($$->type) = "dictorsetmaker";
                        ASTNode* node = processNodes("DOUBLE_STAR", 1, $2);
                        (node->content) = string($1);
                        ($$->children).push_front(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.6";
        } 
        | test comp_for {
                // Difficult to make simplifications here and can lead to oversimplification and node deletions in AST
                $$ = processNodes("dictorsetmaker", 2,
                        $1,
                        $2
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.7";
        }
        | test continued_testlist COMMA {
                // Right recursive production can be simplified to a single level in AST
                // COMMA not significant semantically so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "dictorsetmaker";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.8";
        }
        | test continued_testlist {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "dictorsetmaker";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.9";
        }
        | star_expr comp_for {
                // Difficult to make simplifications here and can lead to oversimplification and node deletions in AST
                $$ = processNodes("dictorsetmaker", 2,
                        $1,
                        $2
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.10";
        }
        | star_expr continued_testlist COMMA {
                // Right recursive production can be simplified to a single level in AST
                // COMMA not significant semantically so can be ignored
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "dictorsetmaker";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.11";
        }
        | star_expr continued_testlist {
                // Right recursive production can be simplified to a single level in AST
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("dictorsetmaker", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "dictorsetmaker";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "dictorsetmaker.12";
        }       
        ;

// #notrequired
continued_dictorset:
        continued_dictorset COMMA test COLON test {
                // Left recursive productions can be simplified to a single level in AST
                // Here both COMMA and COLON are operator and both are generally insignificant.
                // But in this context we ignore COMMA and COLON is propogated up.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_dictorset", 5,
                                $1,
                                createNode("COMMA", $2),
                                $3,
                                createNode("COLON", $4),
                                $5
                        );
                }
                else {
                        $$ = $1;
                        ASTNode* node = processNodes("COLON", 2, $3, $5);
                        (node->content) = string($4);
                        ($$->children).push_back(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_dictorset.1";
        }
        | continued_dictorset COMMA DOUBLE_STAR expr {
                // Left recursive productions can be simplified to a single level in AST
                // Here both COMMA and DOUBLE_STAR are operator. In this context we ignore COMMA and DOUBLE_STAR is propogated up.
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add DOUBLE_STAR in the "content" of "expr" node -> That would actually feel like an expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("continued_dictorset", 4,
                                $1,
                                createNode("COMMA", $2),
                                createNode("DOUBLE_STAR", $3),
                                $4
                        );
                }
                else {
                        $$ = $1;
                        ASTNode* node = processNodes("DOUBLE_STAR", 1, $4);
                        ($$->children).push_back(node);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_dictorset.2";
        }
        | %empty {
                // Will be ignored by "processNodes" for AST
                $$ = processNodes("continued_dictorset", 0);

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_dictorset.3";
        }
        ;     

classdef:
        CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite {
                // CLASS and COLON can be considered as operators. COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("classdef", 7,
                                createNode("CLASS", $1),
                                createNode("NAME", $2),
                                createNode("OPENING_BRACKET", $3),
                                $4,
                                createNode("CLOSING_BRACKET", $5),
                                createNode("COLON", $6),
                                $7
                        );
                }
                else {
                        $$ = processNodes("classdef", 3,
                                createNode("NAME", $2),
                                $4,
                                $7
                        );
                        ($$->content) = string($1);
                }
                
                if(AST_DEBUG_OUTSIDE_VERBOSE) {
                        printf("[AST]: classdef -> CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite used\n");
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "classdef.1";
        }
        | CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite {
                // CLASS and COLON can be considered as operators. COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("classdef", 6,
                                createNode("CLASS", $1),
                                createNode("NAME", $2),
                                createNode("OPENING_BRACKET", $3),
                                createNode("CLOSING_BRACKET", $4),
                                createNode("COLON", $5),
                                $6
                        );
                }
                else {
                        $$ = processNodes("classdef", 3,
                                createNode("NAME", $2),
                                createNode("BRACKETS", " " + string($3) + string($4) + " "),
                                $6
                        );
                        ($$->content) = string($1);
                }

                if(AST_DEBUG_OUTSIDE_VERBOSE) {
                        printf("[AST]: classdef-> CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite used\n");
                        char* prnt = const_cast<char*> (($6->content).c_str());
                        printf("[AST]: contents in suite - %s\n", prnt);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "classdef.2";
        }
        | CLASS NAME COLON suite {
                // CLASS and COLON can be considered as operators. COLON can be ignored for AST.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("classdef", 4,
                                createNode("CLASS", $1),
                                createNode("NAME", $2),
                                createNode("COLON", $3),
                                $4
                        );
                }
                else {
                        $$ = processNodes("classdef", 2,
                                createNode("NAME", $2),
                                $4
                        );
                        ($$->content) = string($1);
                }

                if(AST_DEBUG_OUTSIDE_VERBOSE) {
                        cout<<"[AST]: classdef-> CLASS NAME COLON suite used"<<"\n";                
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "classdef.3";
        }
        ;

arglist:
        argument continued_argument COMMA {
                if(isAST == false) {
                        $$ = processNodes("arglist", 3,
                                $1,
                                $2,
                                createNode("COMMA", $3)
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "arglist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "arglist.1";
        }
        | argument continued_argument {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: single argument added in arglist\n");
                
                // Right recursive production can be simplified for an AST into a single level.
                if(isAST == false) {
                        $$ = processNodes("arglist", 2,
                                $1,
                                $2
                        );
                }
                else {
                        $$ = $2;
                        ($$->type) = "arglist";
                        ($$->children).push_front($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "arglist.2";
        }
        ;

continued_argument:
        continued_argument COMMA argument {
                // Simplification in AST possible for left recursive productions to bring all terms on a single level.
                // COMMA can be ignored because that has no semantic significance.
                if(isAST == false) {
                        $$ = processNodes("continued_argument", 3,
                                $1,
                                createNode("COMMA", $2),
                                $3
                        );
                }
                else {
                        $$ = $1;
                        ($$->children).push_back($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_argument.1";
        }
        | %empty {
                $$ = processNodes("continued_argument", 0); // Will be ignored automatically in AST

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "continued_argument.2";
        }
        ;

argument:
        test comp_for { // #notrequired
                $$ = processNodes("argument", 2,
                        $1,
                        $2                
                );

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "argument.1";
        }
        | test EQUAL test {
                // EQUAL can be identified as an operator and can be propogated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("argument", 3,
                                $1,
                                createNode("EQUAL", $2),
                                $3
                        );
                }
                else {
                        $$ = processNodes("argument", 2,
                                $1,
                                $3
                        );
                        ($$->content) = string($2);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "argument.2";
        }
        | DOUBLE_STAR test { // #notrequired
                // This is a tough case. Here DOUBLE_STAR is a unary operator and thus we cannot directly
                // add STAR in the "content" of "test" node -> That would actually feel like a STAR annotated to a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("argument", 2,
                                createNode("DOUBLE_STAR", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("argument", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "argument.3";
        }
        | STAR test { // #notrequired
                // This is a tough case. Here STAR is a unary operator and thus we cannot directly
                // add STAR in the "content" of "test" node -> That would actually feel like a STAR annotated to a conditional test.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("argument", 2,
                                createNode("STAR", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("argument", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "argument.4";
        }
        | test {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: argument contains a single test\n");
                
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("argument", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "argument.5";
        }
        ;

// #notrequired
comp_iter:
        comp_for { 
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("comp_iter", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_iter.1";
        }
        | comp_if { 
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) $$ = processNodes("comp_iter", 1, $1);
                else $$ = $1;

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_iter.2";
        }
        ;

// #notrequired
comp_for:
        FOR exprlist IN or_test comp_iter {
                // FOR and IN can be identified as operators for AST and propogated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_for", 5, // "comp_for: FOR exprlist IN or_test comp_iter\n
                                createNode("FOR", $1),
                                $2,
                                createNode("IN", $3),
                                $4,
                                $5
                        );
                }
                else {
                        $$ = processNodes("comp_for", 3, // "comp_for: FOR exprlist IN or_test comp_iter\n
                                $2,
                                $4,
                                $5
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_for.1";
        }
        | FOR exprlist IN or_test {
                // FOR and IN can be identified as operators for AST and propogated upwards.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_for", 4, // "comp_for: FOR exprlist IN or_test\n
                                createNode("FOR", $1),
                                $2,
                                createNode("IN", $3),
                                $4
                        );
                }
                else {
                        $$ = processNodes("comp_for", 2, // "comp_for: FOR exprlist IN or_test\n
                                $2,
                                $4
                        );
                        ($$->content) = string($1) + "$" + string($3);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_for.2";
        }
        ;

// #notrequired
comp_if:
        IF test_nocond comp_iter {
                // IF can be identified as the operator here and propogated upwards in this.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_if", 3, // "comp_if: IF test_nocond comp_iter\n
                                createNode("IF", $1),
                                $2,
                                $3
                        );
                }
                else {
                        $$ = processNodes("comp_if", 2, // "comp_if: IF test_nocond comp_iter\n
                                $2,
                                $3
                        );
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_if.1";
        }
        | IF test_nocond {
                // This is a tough case. Here IF is a unary operator and thus we cannot directly
                // add IF in the "content" of "test_nocond" node -> That would actually feel a non-conditional test expression.
                if(isAST == false || AST_STRUCTURE_DEBUG == 1) {
                        $$ = processNodes("comp_if", 2, // "comp_if: IF test_nocond\n
                                createNode("IF", $1),
                                $2
                        );
                }
                else {
                        $$ = processNodes("comp_if", 1, $2);
                        ($$->content) = string($1);
                }

                ($$->columnno) = yylloc.first_column;
                ($$->lineno) = yylineno;
                $$->name = "comp_if.2";
        }
        ;

%%

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you want to declare should go here.

// Whenever there is a syntax error found during parsing then this function is called which
// returns with a syntax error in the program.
void yyerror(const char* s) {
        fprintf(stderr, "[SYNTAX ERROR]: Offending token near '%s' at column no %d on line no %d\n", yytext, yylloc.first_column, yylineno);
        return;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/
