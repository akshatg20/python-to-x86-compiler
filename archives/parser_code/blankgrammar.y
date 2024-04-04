%{
// #include <algorithm>
// #include <iostream>
// #include <iomanip>
// #include <fstream>
// #include <string>
// #include <string.h>
// #include <map>
// #include <stack>
// #include <set>
// #include <vector>
// #include <cstdlib>
// #include <utility>
// #include <cctype>
// #include <queue>
// #include <stdarg.h>
// #ifndef AST_HPP
// #include "ast.hpp"
// #endif
// using namespace std;

// /*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF PARSER ***********************************/

// // Write any assumptions that you take in the comment below
// /*
// ----
// */

// /*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF PARSER ***********************************/

// // All required external source files are already included to this code.
// // Declare any external variables you want to use here with an "extern" keyword.
// extern int yylineno;
// extern char* yytext;
// extern int counter;
// extern int AST_DEBUG_OUTSIDE_VERBOSE;
// extern int AST_DEBUG_INSIDE_VERBOSE;
// extern char *inputfile_path,*outputfile_path,*errorfile_path,*astfile_path,*dotfile_path,*parsefile_path;
// extern int DOT_GENERATION,AST_GENERATION,PARSE_TREE_GENERATION;
// extern ASTNode* root;
// extern vector<ASTNode*> v_r_dfs;
// extern bool isAST;

// /*********************************** DATA STORAGE STRUCTURES ******************************************************/

// // All classes and structures that you want to declare should go here.

// /*********************************** DATA STORAGE STRUCTURES ******************************************************/

// /*********************************** DATA STORAGE ELEMENTS ********************************************************/

// // All variables that you want to declare should go here.

// int yylex();
// void yyerror(const char* s);

// /* Debug mode specification variables for parser */
// int PARSER_DEBUG_OUTSIDE_VERBOSE = 0;       // for debugging purposes only
// int PARSER_DEBUG_INSIDE_VERBOSE = 0;        // for verbose output purposes

// /*********************************** DATA STORAGE ELEMENTS ********************************************************/



// Creates a new list containing only i, an index into the array of instructions
vector<int>* makelist(int i) {
    vector<int>* newList = new vector<int>();
    newList->push_back(i);
    return newList;
}

// Concatenates the lists pointed to by p1 and p2, and returns a pointer to the concatenated list
vector<int>* merge(vector<int>* p1, vector<int>* p2) {
    vector<int>* mergedList = new vector<int>(*p1);
    mergedList->insert(mergedList->end(), p2->begin(), p2->end());
    return mergedList;
}

// Inserts i as the target label for each of the instructions on the list pointed to by p
void backpatch(vector<int>* p, int targetLabel) {
    for (int& i : *p) {
        i = targetLabel;
    }
}



%}

%union {
    struct ASTNode* ast;
    char* lexeme;
    struct Marker* marker;
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

%type<marker> M, N, O, P, Q


%%

// Markers
M: %empty {M.instr = nextinstr;};
N: %empty {N.nextlist = makelist(nextinstr); emit("goto _ ");};
O: %empty {M.instr = nextinstr;};
P: %empty {N.nextlist = makelist(nextinstr); emit("goto _ ");};
Q: %empty {M.instr = nextinstr;};



start:
        file_input         
        ;  

file_input:
        continued_file_input ENDMARKER 
        ;

continued_file_input:
        continued_file_input NEWLINE 
        | continued_file_input stmt 
        | %empty 
        ;    

funcdef:
        DEF NAME parameters RIGHTARROW test COLON suite 
        | DEF NAME parameters COLON suite  
        ;

parameters:
        OPENING_BRACKET typedargslist CLOSING_BRACKET 
        | OPENING_BRACKET CLOSING_BRACKET 
        ;

typedargslist:
        tfpdef EQUAL test next_arg COMMA 
        | tfpdef EQUAL test next_arg 
        | tfpdef next_arg COMMA 
        | tfpdef next_arg 
        ;

next_arg:
        next_arg COMMA tfpdef EQUAL test 
        | next_arg COMMA tfpdef 
        | %empty 
        ;


tfpdef:
        NAME COLON test 
        | NAME  
        ;


stmt:
        simple_stmt   
        | compound_stmt 
        ;

simple_stmt:
        small_stmt next_small_stmt SEMI_COLON NEWLINE 
        | small_stmt next_small_stmt NEWLINE 
        ;

next_small_stmt:
        next_small_stmt SEMI_COLON small_stmt 
        | %empty 
        ;

small_stmt:
        flow_stmt 
        | expr_stmt 
        | global_stmt 
        | nonlocal_stmt 
        | assert_stmt
        ;

expr_stmt:
        testlist_star_expr annassign  
        | testlist_star_expr AUGASSIGN testlist 
        | testlist_star_expr continued_expr_stmt 
        ;

continued_expr_stmt:
        continued_expr_stmt EQUAL testlist_star_expr 
        | %empty 
        ;     

annassign:
        COLON test EQUAL test 
        | COLON test 
        ;

testlist_star_expr:
        test continued_testlist COMMA 
        | test continued_testlist 
        | star_expr continued_testlist COMMA 
        | star_expr continued_testlist 
        ;                     

flow_stmt:
        break_stmt 
        | continue_stmt 
        | return_stmt 
        | raise_stmt 
        ;

break_stmt:
        BREAK 
        ; 

continue_stmt:
        CONTINUE 
        ;

return_stmt:
        RETURN testlist 
        | RETURN 
        ;

raise_stmt:
        RAISE test FROM test 
        | RAISE test 
        | RAISE 
        ;

global_stmt:
        GLOBAL NAME stmt_helper 
        ;

nonlocal_stmt:
        NONLOCAL NAME stmt_helper 
        ;

assert_stmt:
        ASSERT test COMMA test 
        | ASSERT test 
        ;

stmt_helper:
        stmt_helper COMMA NAME 
        | %empty 
        ;

compound_stmt:
        if_stmt  
        | while_stmt 
        | for_stmt 
        | try_stmt 
        | funcdef 
        | classdef 
        ;


// ---------------------------------- Segment 1 ----------------------------------

// 
// 1. implement truelist for test and elif_stmt 
//      (I think to implement (1) truelist, falselist, nextlist for all nonterminals (ast) (2) instr for all markers) : struct Terminal, Nonterminals and Marker
// 2. what to do when it is empty ? 
// 3. M and N for suite? Why do we use N? + its implications for while

/* if_stmt:
        IF test COLON     M suite N     O else_stmt 
        {
                backpatch(test.truelist, M.instr);
                backpatch(test.falselist, O.instr);

                // if_stmt.n = suite.n + else_stmt.n + N.n;
                temp = merge(suite.nextlist, N.nextlist);
                if_stmt.nextlist = merge(temp, else_stmt.nextlist);

                
        }
        ; */

if_stmt:
        IF test COLON   M suite N   O elif_stmt P      Q else_stmt 
        {
                backpatch(test.truelist, M.instr);
                backpatch(test.falselist, O.instr);
                        
                        backpatch(elif_stmt.falselist, Q.instr);
                
                // if_stmt.n = suite.n  + N.n + 
                //         elif_stmt.t + 
                //         elif_stmt.n + P.n +
                //         else_stmt.n
                temp = merge(suite.nextlist, N.nextlist);
                temp2 = merge(elif_stmt.nextlist, P.nextlist);
                temp3 = merge(elif_stmt.truelist, else_stmt.nextlist);
                temp4 = merge(temp, temp2);
                if_stmt.nextlist = merge(temp3, temp4);
        }
        ;

elif_stmt: // will have to implement truelist and falselist for elif_stmt, no backpatch for it in truelist in if statement
        elif_stmt ELIF   M test  COLON  N suite 
        {
                backpatch(elif_stmt.falselist, M.instr);
                backpatch(test.truelist, N.instr);

                // elif_stmt.n = elif_stmt.t + suite.n + test.f;
                temp = merge(elif_stmt.truelist, suite.nextlist);
                elif_stmt.nextlist = merge(temp, test.falselist);
        }
        | %empty 
        ;


else_stmt: // 1 way so need not use it
        ELSE COLON suite 
        | %empty 
        ;

/* while_stmt:
        WHILE  M test COLON O suite
        {
                backpatch(suite.nextlist, M.instr);
                backpatch(test.truelist, O.instr);
                
                while_stmt.nextlist = test.falselist;
                emit("goto " + to_string(M.instr));

        }
        ; */

while_stmt:
        WHILE  M test COLON O suite  Q else_stmt
        {
                backpatch(suite.nextlist, M.instr);
                backpatch(test.truelist, O.instr);
                backpatch(test.falselist, Q.instr);
                
                while_stmt.nextlist = else_stmt.nextlist;
                emit("goto " + to_string(M.instr));
        }
        ;  

// Added this nonterminal -> forcheck so that now it is similar to while
forcheck: exprlist IN testlist
        ;

for_stmt:
        FOR forcheck COLON suite else_stmt 
        ;

try_stmt:
        TRY COLON suite except_stmt else_stmt finally_stmt 
        | TRY COLON suite FINALLY COLON suite 
        ;

except_stmt:
        except_stmt except_clause COLON suite 
        | except_clause COLON suite 
        ;

finally_stmt:
        FINALLY COLON suite 
        | %empty   
        ;

except_clause:
        EXCEPT test AS NAME 
        | EXCEPT test 
        | EXCEPT 
        ;

suite:
        simple_stmt 
        | NEWLINE INDENT stmts DEDENT 
        ;

stmts:
        stmts stmt 
        | stmt 
        ;

test:
        or_test IF or_test ELSE test 
        | or_test 
        ;

test_nocond:
        or_test 
        ;

or_test:
        and_test continued_or_test 
        ;

continued_or_test:
        continued_or_test OR and_test 
        | %empty 
        ;

and_test:
        not_test continued_and_test 
        ;

continued_and_test:
        continued_and_test AND not_test 
        | %empty 
        ;

not_test:
        NOT not_test 
        | comparison 
        ;

comparison:
        expr comparison_stmt 
        ;

comparison_stmt:
        comparison_stmt comp_op expr 
        | %empty 
        ;

comp_op:
        COMP_OP 
        | IN    
        | NOT IN 
        | IS    
        | IS NOT 
        ;

star_expr:
        STAR expr 
        ;

expr:
        xor_expr continued_xor_expr 
        ;

continued_xor_expr:
        continued_xor_expr BITWISE_OR xor_expr 
        | %empty 
        ;

xor_expr:
        and_expr continued_and_expr 
        ;

continued_and_expr:
        continued_and_expr CARET and_expr 
        | %empty 
        ;

and_expr:
        shift_expr continued_shift_expr 
        ;

continued_shift_expr:
        continued_shift_expr BITWISE_AND shift_expr 
        | %empty 
        ;

shift_expr:
        arith_expr continued_arith_expr 
        ;

continued_arith_expr:
        continued_arith_expr LEFT_SHIFT arith_expr 
        | continued_arith_expr RIGHT_SHIFT arith_expr 
        | %empty 
        ;

arith_expr:
        term continued_term 
        ;

continued_term:
        continued_term PLUS term 
        | continued_term MINUS term 
        | %empty 
        ;

term:
        factor continued_factor 
        ;

continued_factor:
        continued_factor STAR factor 
        | continued_factor DIV factor 
        | continued_factor AT factor 
        | continued_factor REM factor 
        | continued_factor FLOOR_DIV factor 
        | %empty 
        ;

factor:
        PLUS factor 
        | MINUS factor 
        | TILDE factor 
        | power 
        ;

power:
        atom_expr DOUBLE_STAR factor 
        | atom_expr 
        ;

atom_expr:
        AWAIT atom trailers 
        | atom trailers 
        ;

trailers:
        trailers trailer 
        | %empty 
        ;

atom:
        OPENING_BRACKET testlist_comp CLOSING_BRACKET 
        | OPENING_BRACKET CLOSING_BRACKET 
        | OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET 
        | OPENING_SQ_BRACKET CLOSING_SQ_BRACKET 
        | OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET // #notrequired
        | OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET // #notrequired
        | NAME 
        | NUMBER  
        | strings 
        | ELLIPSES_LITERAL // #notrequired
        | TOKEN_TRUE 
        | TOKEN_FALSE 
        | TOKEN_NONE 

strings:
        strings STRING  
        {
                $$->val = merge($1->val, $2->val);
        }
        | STRING 
        {
                s->val = new
        }
        ;

testlist_comp:
        test comp_for 
        | test continued_testlist COMMA 
        | test continued_testlist 
        | star_expr comp_for 
        | star_expr continued_testlist COMMA 
        | star_expr continued_testlist 
        ;

continued_testlist:
        continued_testlist COMMA test  
        | continued_testlist COMMA star_expr 
        | %empty  
        ;

trailer:
        OPENING_BRACKET arglist CLOSING_BRACKET 
        | OPENING_BRACKET CLOSING_BRACKET 
        | OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET 
        | DOT NAME 
        ; 

subscriptlist:
        subscript continued_subscript COMMA 
        | subscript continued_subscript 
        ;

continued_subscript:
        continued_subscript COMMA subscript  
        | %empty 
        ;

subscript:
        test 
        | test COLON test sliceop 
        | test COLON test 
        | test COLON sliceop 
        | test COLON 
        | COLON test sliceop 
        | COLON test 
        | COLON sliceop 
        | COLON 
        ;

sliceop:
        COLON test 
        | COLON 
        ;

exprlist:
        expr continued_exprlist COMMA 
        | expr continued_exprlist 
        | star_expr continued_exprlist COMMA 
        | star_expr continued_exprlist 
        ;

continued_exprlist:
        continued_exprlist COMMA expr 
        | continued_exprlist COMMA star_expr 
        | %empty 
        ;

testlist:
        test continued_comma_test COMMA 
        | test continued_comma_test 
        ;

continued_comma_test:
        continued_comma_test COMMA test 
        | %empty 
        ; 

dictorsetmaker:
        test COLON test comp_for 
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

continued_dictorset:
        continued_dictorset COMMA test COLON test 
        | continued_dictorset COMMA DOUBLE_STAR expr 
        | %empty 
        ;     

classdef:
        CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite 
        | CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite 
        | CLASS NAME COLON suite 
        ;

arglist:
        argument continued_argument COMMA 
        | argument continued_argument 
        ;

continued_argument:
        continued_argument COMMA argument 
        | %empty 
        ;

argument:
        test comp_for
        | test EQUAL test 
        | DOUBLE_STAR test 
        | STAR test 
        | test 
        ;

comp_iter:
        comp_for 
        | comp_if 
        ;

comp_for:
        FOR exprlist IN or_test comp_iter 
        | FOR exprlist IN or_test 
        ;

comp_if:
        IF test_nocond comp_iter 
        | IF test_nocond 
        ;

%%

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you want to declare should go here.

void yyerror(const char* s) {
    fprintf(stderr, "[PARSING ERROR]: Offending token near '%s' at column no %d on line no %d\n", yytext, yylloc.first_column,yylineno);
    return;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/
https://github.com/Miriam-Assraf/AbstractSyntaxTree.git