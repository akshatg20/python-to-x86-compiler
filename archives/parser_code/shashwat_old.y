%{

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <queue>
using namespace std;

extern int yylex();  // You can declare yylex without defining it here

// extern 
int yyerror(string);
extern int yyparse();
extern int yylineno;
extern string yytext;

extern FILE* yyin;

int debug_mode = 1;

// void yyerror(string s);
%}

%token ENDMARKER
%token NEWLINE
%token DEF
%token NAME
%token RIGHTARROW
%token DOUBLE_STAR
%token TYPE
%token AUGASSIGN
%token BREAK
%token CONTINUE
%token RETURN
%token ASYNC
%token RAISE
%token FROM
%token ASSERT
%token GLOBAL
%token NONLOCAL
%token IF
%token ELIF
%token ELSE
%token WHILE
%token FOR
%token TRY
%token IN
%token FINALLY
%token EXCEPT
%token AS
%token AND
%token OR
%token NOT
%token IS
%token CLASS
%token TOKEN_TRUE
%token TOKEN_FALSE
%token TOKEN_NONE
%token AWAIT

%token INDENT
%token DEDENT
%token BYTES_STRING


%token COMP_OP
%token LEFT_SHIFT
%token RIGHT_SHIFT
%token FLOOR_DIV
%token NUMBER
%token ELLIPSES_LITERAL
%token STRING
%token COLON
%token SEMI_COLON
%token OPENING_BRACKET
%token CLOSING_BRACKET
%token OPENING_SQ_BRACKET
%token CLOSING_SQ_BRACKET
%token OPENING_CURLY_BRACKET
%token CLOSING_CURLY_BRACKET
%token STAR
%token EQUAL
%token COMMA
%token PLUS
%token MINUS
%token DIV
%token AT
%token TILDE
%token REM
%token CARET
%token BITWISE_AND
%token BITWISE_OR
%token DOT

%start start

%%

start: file_input { if(debug_mode) printf("[PARSER]: parse success\n"); return 0; }
     ;  

file_input: continued_file_input ENDMARKER
          ;

continued_file_input: continued_file_input NEWLINE
                    | continued_file_input stmt
                    | /* empty */
                    ;    

funcdef: DEF NAME parameters RIGHTARROW test COLON suite
       | DEF NAME parameters COLON suite 
       ;

parameters: OPENING_BRACKET typedargslist CLOSING_BRACKET
          | OPENING_BRACKET CLOSING_BRACKET
          ;

typedargslist: tfpdef EQUAL test next_arg COMMA
             | tfpdef EQUAL test next_arg   
             | tfpdef next_arg COMMA
             | tfpdef next_arg 
             ;

next_arg: next_arg COMMA tfpdef EQUAL test 
        | next_arg COMMA tfpdef
        | /* empty */
        ;

tfpdef: NAME COLON test
      | NAME  
      ;


stmt: simple_stmt   
    | compound_stmt
    ;

simple_stmt: small_stmt next_small_stmt SEMI_COLON NEWLINE
           | small_stmt next_small_stmt NEWLINE
           ;

next_small_stmt: next_small_stmt SEMI_COLON small_stmt 
               | /* empty */
               ;

small_stmt: flow_stmt
          | expr_stmt
          | global_stmt
          | nonlocal_stmt
          | assert_stmt
          ;

expr_stmt: testlist_star_expr annassign
         | testlist_star_expr AUGASSIGN testlist
         | testlist_star_expr continued_expr_stmt
         ;

continued_expr_stmt: continued_expr_stmt EQUAL testlist_star_expr
                   | /* empty */
                   ;     

annassign: COLON test EQUAL test
         | COLON test
         ;

testlist_star_expr: test continued_testlist COMMA
                  | test continued_testlist
                  | star_expr continued_testlist COMMA
                  | star_expr continued_testlist
                  ;                     

flow_stmt: break_stmt
         | continue_stmt
         | return_stmt
         | raise_stmt
         ;

break_stmt: BREAK
          ;  

continue_stmt: CONTINUE
             ;

return_stmt: RETURN testlist
           | RETURN
           ; 

raise_stmt: RAISE test FROM test
          | RAISE test
          | RAISE
          ;

global_stmt: GLOBAL NAME stmt_helper
           ;

nonlocal_stmt: NONLOCAL NAME stmt_helper
             ;

assert_stmt: ASSERT test COMMA test
           | ASSERT test 
           ;

stmt_helper: stmt_helper COMMA NAME 
           | /* empty */
           ;

compound_stmt: if_stmt
             | while_stmt
             | for_stmt
             | try_stmt
             | funcdef
             | classdef
             ;

if_stmt: IF test COLON suite elif_stmt else_stmt
       ;

elif_stmt: elif_stmt ELIF test COLON suite 
         | /* empty */
         ; 

else_stmt: ELSE COLON suite
         | /* empty */
         ;

while_stmt: WHILE test COLON suite else_stmt
          ;  
        
for_stmt: FOR exprlist IN testlist COLON suite else_stmt
        ;

try_stmt: TRY COLON suite except_stmt else_stmt finally_stmt
        | TRY COLON suite FINALLY COLON suite
        ;

except_stmt: except_stmt except_clause COLON suite 
           | except_clause COLON suite
           ;

finally_stmt: FINALLY COLON suite
            | /* empty */    
            ;

except_clause: EXCEPT test AS NAME 
             | EXCEPT test
             | EXCEPT
             ;

suite: simple_stmt
     | NEWLINE INDENT stmts DEDENT
     ;

stmts: stmts stmt 
     | stmt
     ;

test: or_test IF or_test ELSE test
    | or_test 
    ;

test_nocond: or_test
           ;

or_test: and_test continued_or_test
       ;

continued_or_test: continued_or_test OR and_test 
                 | /* empty */
                 ;

and_test: not_test continued_and_test
        ;

continued_and_test: continued_and_test AND not_test 
                  | /* empty */
                  ;

not_test: NOT not_test
        | comparison
        ;

comparison: expr comparison_stmt
          ;

comparison_stmt: comparison_stmt comp_op expr 
               | /* empty */
               ;

comp_op: COMP_OP 
       | IN 
       | NOT IN
       | IS
       | IS NOT
       ; 

/*  till here */

star_expr: STAR expr    
         ;

expr: xor_expr continued_xor_expr
    ;

continued_xor_expr: continued_xor_expr BITWISE_OR xor_expr 
                  | /* empty */
                  ;

xor_expr: and_expr continued_and_expr
        ;

continued_and_expr: continued_and_expr CARET and_expr 
                  | /* empty */
                  ;

and_expr: shift_expr continued_shift_expr
        ;
    
continued_shift_expr: continued_shift_expr BITWISE_AND shift_expr 
                    | /* empty */
                    ;

shift_expr: arith_expr continued_arith_expr
          ;

continued_arith_expr: continued_arith_expr LEFT_SHIFT arith_expr 
                    | continued_arith_expr RIGHT_SHIFT arith_expr 
                    | /* empty */
                    ;

arith_expr: term continued_term
          ;

continued_term: continued_term PLUS term 
              | continued_term MINUS term 
              | /* empty */
              ;

term: factor continued_factor
    ;

continued_factor: continued_factor STAR factor 
                | continued_factor AT factor 
                | continued_factor DIV factor 
                | continued_factor REM factor 
                | continued_factor FLOOR_DIV factor 
                | /* empty */
                ;

factor: PLUS factor
      | MINUS factor
      | TILDE factor
      | power
      ;

power: atom_expr DOUBLE_STAR factor
     | atom_expr 
     ;    

atom_expr: AWAIT atom trailers
         | atom trailers
         ;

trailers: trailers trailer
        | /* empty */
        ;

atom: OPENING_BRACKET testlist_comp CLOSING_BRACKET
    | OPENING_BRACKET CLOSING_BRACKET
    | OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET
    | OPENING_SQ_BRACKET CLOSING_SQ_BRACKET
    | OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET
    | OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET
    | NAME 
    | NUMBER 
    | strings 
    | ELLIPSES_LITERAL
    | TOKEN_TRUE 
    | TOKEN_FALSE
    | TOKEN_NONE

strings: strings STRING 
       | STRING
       ; 

testlist_comp: test comp_for
             | test continued_testlist COMMA
             | test continued_testlist
             | star_expr comp_for
             | star_expr continued_testlist COMMA
             | star_expr continued_testlist
             ;

continued_testlist: continued_testlist COMMA test 
                  | continued_testlist COMMA star_expr
                  | /* empty */
                  ;

trailer: OPENING_BRACKET arglist CLOSING_BRACKET
       | OPENING_BRACKET CLOSING_BRACKET
       | OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET
       | DOT NAME
       ;

subscriptlist: subscript continued_subscript COMMA
             | subscript continued_subscript
             ;

continued_subscript: continued_subscript COMMA subscript 
                   | /* empty */
                   ;

subscript: test
         | test COLON test sliceop
         | test COLON test
         | test COLON sliceop
         | test COLON
         | COLON test sliceop
         | COLON test
         | COLON sliceop
         | COLON
         ;

sliceop: COLON test
       | COLON 
       ;

exprlist: expr continued_exprlist COMMA
        | expr continued_exprlist
        | star_expr continued_exprlist COMMA
        | star_expr continued_exprlist
        ;

continued_exprlist: continued_exprlist COMMA expr 
                  | continued_exprlist COMMA star_expr
                  | /* empty */
                  ;

testlist: test continued_comma_test COMMA
        | test continued_comma_test
        ;

continued_comma_test: continued_comma_test COMMA test
                    | /* empty */
                    ;    

dictorsetmaker : test COLON test comp_for
	        | test COLON test continued_dictorset COMMA
	        | test COLON test continued_dictorset
	        | DOUBLE_STAR expr comp_for
	        | DOUBLE_STAR expr continued_dictorset COMMA
	        | DOUBLE_STAR expr continued_dictorset
	        | test comp_for
	        | test continued_testlist COMMA
	        | test continued_testlist
	        | star_expr comp_for
	        | star_expr continued_testlist COMMA
	        | star_expr continued_testlist
	        ;

continued_dictorset: continued_dictorset COMMA test COLON test
                   | continued_dictorset COMMA DOUBLE_STAR expr
                   | /* empty */
                   ;     


classdef: CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite
        | CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite
        | CLASS NAME COLON suite
        ;

arglist: argument continued_argument COMMA
       | argument continued_argument
       ;

continued_argument: continued_argument COMMA argument 
                  | /* empty */
                  ;

argument: test comp_for
        | test EQUAL test 
        | DOUBLE_STAR test
        | STAR test
        | test
        ;

comp_iter: comp_for
         | comp_if
         ;

comp_for: FOR exprlist IN or_test comp_iter
        | FOR exprlist IN or_test
        ;

comp_if: IF test_nocond comp_iter
       | IF test_nocond
       ;
         

%%

int main(int argc, char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");

    if (!inputFile) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
   
    yyin = inputFile;
	yyparse();
    fclose(inputFile);
	return 0;
}

int yyerror(string s) 
{
    fprintf(stderr, "[PARSING ERROR]: %s", s.c_str());
    return 0;
}


