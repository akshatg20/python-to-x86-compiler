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
using namespace std;

int yylex();
extern int yylineno;
extern char *yytext;
void yyerror(const char* s);

/* Debug mode specification variables for parser */
int PARSER_DEBUG_OUTSIDE_VERBOSE = 0;       // for debugging purposes only
int PARSER_DEBUG_INSIDE_VERBOSE = 0;        // for verbose output purposes

// Compiler configuration variables
extern char *inputfile_path,*outputfile_path,*errorfile_path,*astfile_path,*dotfile_path;
extern int DOT_GENERATION,AST_GENERATION;

// Function to extract path without file extension from a file path
string getwithoutextension(char* filePath) {
    string path(filePath), ret="";
    int dotPos = -1;
    for(int i=path.length()-1;i>-1;i--) {
        if(path[i]=='.') { dotPos = i; break; }
    }
    if(dotPos > 0) ret = path.substr(0, dotPos);
    else ret = path;
    return ret;
}

/* 
This is a model file that demonstrates the logic used to make AST:
Assumptions:
1. hierarchy of operands is maintained
2. hierarchy of optrs, unless they are used with operands are not maintained
3. all operators and operands are propagated upwards unless they destroy hierarchy or they are useful to disambiguate things
3. all operators in a production are assumed to have same precedence (precedence is disambiguated using CFG of parser)
5. operands when used without an explicit operator are assumed to have an implicit operator
6. Unspecified optr/operand flag is assumed to be operand. Similarly we assume operand when both optr and operand flags are set to true
7. statements like continue, except and break; can be both operator and operand so kept as operand otherwise, they would have been propagated upwards and merged into other operators
8. Ellipsis literal as operand is assumed
9. brackets have been assumed as operators and they are automatically merged into other operators when necessary
10. Keywords are treated as operators
11. Braces are ignored when obvious.
Usage: For each production, send the node corresponding to all ternimals and non-terminals with optional content and mandatory specification of optr/operand;
Example 
S : a B {$$ = processNode("S",2,$1,createNode("B",$1,operand=true))};
*/

struct ASTNode {
        string type;
        string content;
        vector<struct ASTNode*> children;
        bool optr;
        bool operand;
        ASTNode(string type, string content = "", bool optr = false, bool operand = false) : type(type), content(content), optr(optr),  operand(operand) {}
};
typedef struct ASTNode ASTNode;

ASTNode* createNode(string type, string content = "", bool optr=false, bool operand = false)  {
        return new ASTNode(type, content, optr, operand);
}

int counter = 0;
ASTNode* root;

int getNewId();
int writeTree(ASTNode* node,int id, char* filePath, char* astPath) ;
string dquote_to_html(string s);
ASTNode* processNodes(string name,int numNodes, ...);

int mycounter=0;
int AST_DEBUG_OUTSIDE_VERBOSE = 0;
int AST_DEBUG_INSIDE_VERBOSE = 0;
int AST_DEBUG = 0;
int dfs(ASTNode* root);
vector<ASTNode*> v_r_dfs;
vector<ASTNode*> ret_single_childs(ASTNode* root);
int writeTree3(vector<ASTNode*> nodes, int id, char* filePath, char* astPath);

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

%%

start:
        file_input         {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: Parse Success\n");
                $$ = $1; root = $$;
                
                int result = writeTree(root, getNewId(), dotfile_path, astfile_path);;
                
                // Seperate AST Generation
                if(AST_DEBUG) {
                        vector<ASTNode*> s_ast =  ret_single_childs(root);
                        string dotfile = getwithoutextension(dotfile_path);
                        string astfile = getwithoutextension(astfile_path);
                        for(int i=0;i<s_ast.size();i++) {
                                ASTNode* node = s_ast[i];
                                string temp = dotfile + "_SAST_" + to_string(mycounter) + ".dot";
                                string temp2 = astfile + "_SAST_" + to_string(mycounter) + ".pdf";
                                printf("[AST]: A Seperate script and AST is to be created at %s and %s.\n", const_cast<char*>(temp.c_str()), const_cast<char*>(temp2.c_str()));
                                writeTree(node, getNewId(), const_cast<char*>(temp.c_str()), const_cast<char*>(temp2.c_str()));
                                mycounter++;
                        }
                }

                // Traverse to find nodes with single children. They will serve as roots.
                // This tries to generate different trees for a single input file.
                if(AST_DEBUG) {
                        // printf("[AST]: Doing Traversal to find nodes with single children to generate seperate ASTs.\n");
                        // int r_dfs = dfs(root);
                        // int result_r_dfs = writeTree3(v_r_dfs, getNewId(), dotfile_path, astfile_path);
                }

                return result;
        }
        ;  

file_input:
        continued_file_input ENDMARKER { $$ = $1; }
        ;

continued_file_input:
        continued_file_input NEWLINE {$$ = $1;}
        | continued_file_input stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: NEXT STATEMENT TO COME UP\n\n"); } {
                $$ = processNodes("continued_file_input"
                        ,2,
                        $1,
                        $2);
                ($$->operand) = true;
                ($$->optr) = true;
        }
        | %empty { $$ = NULL; }
        ;    

funcdef:
        DEF NAME parameters RIGHTARROW test COLON suite {
                $$ = processNodes("funcdef",7,
                createNode("DEF",$1,true,false),
                createNode("NAME",$2,false,true),
                $3,
                createNode("RIGHTARROW",$4,true,false),
                $5,
                createNode("COLON",$6,true,false),
                $7
                );
        }
        | DEF NAME parameters COLON suite  {
                $$ = processNodes("funcdef",5,
                createNode("DEF",$1,true,false),
                createNode("NAME",$2,false,true),
                $3,
                createNode("COLON",$4,true,false),
                $5
                );
        }
        ;

parameters:
        OPENING_BRACKET typedargslist CLOSING_BRACKET {
                $$ = processNodes("parameters",3,
                createNode("OPENING_BRACKET",$1,true,false),
                $2,
                createNode("CLOSING_BRACKET",$3,true,false)
                );
        }
        | OPENING_BRACKET CLOSING_BRACKET {
                $$ = NULL;
        }
                ;

typedargslist:
        tfpdef EQUAL test next_arg COMMA {
                $$ = processNodes("typedargslist",5,
                                $1,
                                createNode("EQUAL",$2,true,false),
                                $3,
                                $4,
                                createNode("COMMA",$5,true,false)
                                );
        }
        | tfpdef EQUAL test next_arg {
                $$ = processNodes("typedargslist",4,
                                $1,
                                createNode("EQUAL",$2,true,false),
                                $3,
                                $4
                                );
        }
        | tfpdef next_arg COMMA {
                $$ = processNodes("typedargslist",3,
                                $1,
                                $2,
                                createNode("COMMA",$3,true,false)
                                );
        }
        | tfpdef next_arg {
                $$ = processNodes("typedargslist",2,
                                $1,
                                $2
                                );
        }
        ;

next_arg:
        next_arg COMMA tfpdef EQUAL test {
                $$ = processNodes("next_arg",5,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3,
                        createNode("EQUAL",$4,true,false),
                        $5
                        );
        }
        | next_arg COMMA tfpdef {
                $$ = processNodes("next_arg",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                        );
        }
        | %empty {
                $$ = NULL;
        }
        ;


tfpdef:
        NAME COLON test {
                $$ = processNodes("tfpdef",3,
                        createNode("NAME",$1,false,true),
                        createNode("COLON",$2,true,false),
                        $3
                        );
        }
        | NAME  {
                $$ = processNodes("tfpdef",1,
                        createNode("NAME",$1,false,true)
                        );
        }
        ;


stmt:
        simple_stmt   { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: simple_stmt selected \n"); } {
                $$ = $1;
        }
        | compound_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: compound_stmt selected \n"); }  {
                $$ = $1;
        }
        ;

simple_stmt:
        small_stmt next_small_stmt SEMI_COLON NEWLINE {
                $$ = processNodes("simple_stmt",3,
                        $1,
                        $2,
                        createNode("SEMI_COLON",$3,true,false)
                        );
        }
        | small_stmt next_small_stmt NEWLINE {
                $$ = processNodes("simple_stmt",2,
                        $1,
                        $2
                        );
        }
        ;

next_small_stmt:
        next_small_stmt SEMI_COLON small_stmt {
                $$ = processNodes("next_small_stmt",3,
                        $1,
                        createNode("SEMI_COLON",$2,true,false),
                        $3
                        );
        }
        | %empty {
                $$ = NULL;
        }
        ;

small_stmt:
        flow_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt selected \n"); } {
                $$ = $1;
        }
        | expr_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: expr_stmt selected \n"); } {
                $$ = $1;
        }
        | global_stmt {
                $$ = $1;
        }
        | nonlocal_stmt {
                $$ = $1;
        }
        | assert_stmt {
                $$ = $1;
        }
        ;

expr_stmt: testlist_star_expr annassign  {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: annotated assignment in expr_stmt\n");
        } {
                $$ = processNodes("expr_stmt",2,
                        $1,
                        $2
                );
        }
        | testlist_star_expr AUGASSIGN testlist {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: augmented assignment in expr_stmt\n");
        } {
                $$ = processNodes("expr_stmt",3,
                        $1,
                        createNode("AUGASSIGN",$2,true,false),
                        $3
                        );
        }
        | testlist_star_expr continued_expr_stmt {
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: normal assignment in expr_stmt\n");
        } {
                $$ = processNodes("expr_stmt",2,
                        $1,
                        $2
                        );
        }
        ;

continued_expr_stmt:
        continued_expr_stmt EQUAL testlist_star_expr {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: testlist added\n");
        } {
                $$ = processNodes("continued_expr_stmt",3,
                        $1,
                        createNode("EQUAL",$2,true,false),
                        $3
                        );
        }
        | %empty {
                $$ = NULL;
        } 
        ;     

annassign:
        COLON test EQUAL test {
                $$ = processNodes("annassign",4,
                        createNode("COLON",$1,true,false),
                        $2,
                        createNode("EQUAL",$3,true,false),
                        $4
                        );
        }
        | COLON test {
                $$ = processNodes("annassign",2,
                        createNode("COLON",$1,true,false),
                        $2
                        );
        }
        ;

testlist_star_expr:
        test continued_testlist COMMA {
                $$ = processNodes("testlist_star_expr",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                        );
        }
        | test continued_testlist {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: single test in testlist\n");
        } {
                $$ = processNodes("testlist_star_expr",2,
                        $1,
                        $2
                        );
        }
        | star_expr continued_testlist COMMA {
                $$ = processNodes("testlist_star_expr",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                        );
        }
        | star_expr continued_testlist {
                $$ = processNodes("testlist_star_expr",2,
                        $1,
                        $2
                        );
        }
        ;                     

flow_stmt:
        break_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: break_stmt\n"); } {
                $$ = $1;
        }
        | continue_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: continue_stmt\n"); } {
                $$ = $1;
        }
        | return_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: return_stmt\n"); } {
                $$ = $1;
        }
        | raise_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: flow_stmt: raise_stmt\n"); } {
                $$ = $1;
        }
        ;

break_stmt:
        BREAK {
                $$ = createNode("BREAK",$1,false,true);
        }
        ; 

continue_stmt:
        CONTINUE {
                $$ = createNode("CONTINUE",$1,false,true);
        }
        ;

return_stmt:
        RETURN testlist {
                $$ = processNodes("return_stmt",2,
                        createNode("RETURN",$1,false,true),
                        $2
                        );
        }
        | RETURN {
                $$ = createNode("RETURN",$1,false,true);
        }
        ;

raise_stmt:
        RAISE test FROM test {
                $$ = processNodes("raise_stmt",4,
                        createNode("RAISE",$1,false,true),
                        $2,
                        createNode("FROM",$3,false,true),
                        $4
                        );
        }
        | RAISE test {
                $$ = processNodes("raise_stmt",2,
                        createNode("RAISE",$1,false,true),
                        $2
                        );
        }
        | RAISE {
                $$ = createNode("RAISE",$1,false,true);
        }
        ;

global_stmt:
        GLOBAL NAME stmt_helper {
                $$ = processNodes("global_stmt",2,
                        createNode("GLOBAL",$1,true,false),
                        createNode("NAME",$2,false,true),
                        $3
                        );
        }
        ;

nonlocal_stmt:
        NONLOCAL NAME stmt_helper {
                $$ = processNodes("nonlocal_stmt",2,
                        createNode("NONLOCAL",$1,true,false),
                        createNode("NAME",$2,false,true),
                        $3
                        );
        }
        ;

assert_stmt:
        ASSERT test COMMA test {
                $$ = processNodes("ssert_smt",4,
                        createNode("ASSERT",$1,true,false),
                        $2,
                        createNode("COMMA",$3,true,false),
                        $4
                        );
        }
        | ASSERT test {
                $$ = processNodes("assert_stmt",2,
                        createNode("ASSERT",$1,true,false),
                        $2
                        );
        }
        ;

stmt_helper:
        stmt_helper COMMA NAME {
                $$ = processNodes("stmt_helper",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        createNode("NAME",$3,false,true)
                        );
        }
        | %empty {
                $$ = NULL;
        }
        ;

compound_stmt:
        if_stmt  { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: if_stmt selected \n"); } {
                $$ = $1;
        }
        | while_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: while_stmt selected \n"); } {
                $$ = $1;
        }
        | for_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: for_stmt selected \n"); } {
                $$ = $1;
        }
        | try_stmt { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: try_stmt selected \n"); } {
                $$ = $1;
        }
        | funcdef { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: func_def selected \n"); } {
                $$ = $1;
        }
        | classdef { if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSER]: class_def selected \n"); } {
                $$ = $1;
        }
        ;

if_stmt:
        IF test COLON suite elif_stmt else_stmt {
                $$ = processNodes("if_stmt",6,
                        createNode("IF",$1,true,false),
                        $2,
                        createNode("COLON",$3,true,false),
                        $4,
                        $5,
                        $6
                );
        }
        ;

elif_stmt:
        elif_stmt ELIF test COLON suite {
                $$ = processNodes("elif_stmt",5,
                        $1,
                        createNode("ELIF",$2,true,false),
                        $3,
                        createNode("COLON",$4,true,false),
                        $5
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;


else_stmt:
        ELSE COLON suite {
                $$ = processNodes("else_stmt",3,
                        createNode("ELSE",$1,true,false),
                        createNode("COLON",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

while_stmt:
        WHILE test COLON suite else_stmt {
                $$ = processNodes("while_stmt",5,
                        createNode("WHILE",$1,true,false),
                        $2,
                        createNode("COLON",$3,true,false),
                        $4,
                        $5
                );
        }
        ;  
        
for_stmt:
        FOR exprlist IN testlist COLON suite else_stmt {
                $$ = processNodes("for_stmt",6,
                        createNode("FOR",$1,true,false),
                        $2,
                        createNode("IN",$3,true,false),
                        $4,
                        createNode("COLON",$5,true,false),
                        $6,
                        $7
                );
        }
        ;

try_stmt:
        TRY COLON suite except_stmt else_stmt finally_stmt {
                $$ = processNodes("try_stmt",6,
                        createNode("TRY",$1,true,false),
                        createNode("COLON",$2,true,false),
                        $3,
                        $4,
                        $5,
                        $6
                );
        }
        | TRY COLON suite FINALLY COLON suite {
                $$ = processNodes("try_stmt",6,
                        createNode("TRY",$1,true,false),
                        createNode("COLON",$2,true,false),
                        $3,
                        createNode("FINALLY",$4,true,false),
                        createNode("COLON",$5,true,false),
                        $6
                );
        }
        ;

except_stmt:
        except_stmt except_clause COLON suite {
                $$ = processNodes("except_stmt",4,
                        $1,
                        $2,
                        createNode("COLON",$3,true,false),
                        $4
                );
        }
        | except_clause COLON suite {
                $$ = processNodes("except_stmt",3,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3
                );
        }
        ;

finally_stmt:
        FINALLY COLON suite {
                $$ = processNodes("finally_stmt",3,
                        createNode("FINALLY",$1,true,false),
                        createNode("COLON",$2,true,false),
                        $3
                );
        }
        | %empty   {
                $$ = NULL;
        } 
        ;

except_clause:
        EXCEPT test AS NAME {
                $$ = processNodes("except_clause",4,
                        createNode("EXCEPT",$1,true,false),
                        $2,
                        createNode("AS",$1,true,false),
                        createNode("NAME",$1,false,true)
                );
        }
        | EXCEPT test {
                $$ = processNodes("except_clause",2,
                        createNode("EXCEPT",$1,true,false),
                        $2
                );
        }
        | EXCEPT {
                $$ = createNode("EXCEPT",$1,false,true);
        }
        ;

suite:
        simple_stmt {
                $$ = $1;
        }
        | NEWLINE INDENT stmts DEDENT {
                $$ = $3;
        }
        ;

stmts:
        stmts stmt {
                $$ = processNodes("stmts",2,
                        $1,
                        $2
                );
        }
        | stmt {
                $$ = $1;
        }
        ;

test:
        or_test IF or_test ELSE test {
                $$ = processNodes("test",5,
                        $1,
                        createNode("IF",$2,true,false),
                        $3,
                        createNode("ELSE",$4,true,false),
                        $5
                );
        }
        | or_test {
                $$ = $1;
        }
        ;

test_nocond:
        or_test {
                $$ = $1;
        }
        ;

or_test:
        and_test continued_or_test {
                $$ = processNodes("or_test",2,
                                $1,
                                $2
                        );
        }
        ;

continued_or_test:
        continued_or_test OR and_test {
                $$ = processNodes("continued_or_test",3,
                                $1,
                                createNode("OR",$2,true,false),
                                $3
                        );
        }
        | %empty {
                $$ = NULL;
        }
        ;

and_test:
        not_test continued_and_test {
                $$ = processNodes("and_test",2,
                        $1,
                        $2
                );
        }
        ;

continued_and_test:
        continued_and_test AND not_test {
                $$ = processNodes("continued_and_test",3,
                        $1,
                        createNode("AND",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

not_test:
        NOT not_test {
                $$ = processNodes("not_test",2,
                        createNode("NOT",$1,true,false),
                        $2
                );
        }
        | comparison {
                $$ = $1;
        }
        ;

comparison:
        expr comparison_stmt {
                $$ = processNodes("comparison",2,
                        $1,
                        $2
                );
        }
        ;

comparison_stmt:
        comparison_stmt comp_op expr {
                $$ = processNodes("comparison_stmt",3,
                        $1,
                        $2,
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

comp_op:
        COMP_OP {
                $$ = createNode("COMP_OP",$1,true,false);
        }
        | IN    {
                $$ = createNode("IN",$1,true,false);
        }
        | NOT IN {
                $$ = createNode("NOT IN",string($1) + string($2),true,false);
        }
        | IS     {
                $$ = createNode("IS",$1,true,false);
        }
        | IS NOT {
                $$ = createNode("IS NOT",string($1) + string($2),true,false);
        }
        ;

star_expr:
        STAR expr  {
                $$ = processNodes("star_expr",2,
                        createNode("STAR",$1,true,false),
                        $2
                );
        }
        ;

expr:
        xor_expr continued_xor_expr {
                $$ = processNodes("expr",2,
                        $1,
                        $2
                );
        }
        ;

continued_xor_expr:
        continued_xor_expr BITWISE_OR xor_expr {
                $$ = processNodes("continued_xor_expr",3,
                        $1,
                        createNode("BITWISE_OR",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

xor_expr:
        and_expr continued_and_expr {
                $$ = processNodes("xor_expr",2,
                        $1,
                        $2
                );
        }
        ;

continued_and_expr:
        continued_and_expr CARET and_expr {
                $$ = processNodes("continued_and_expr",3,
                        $1,
                        createNode("CARET",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

and_expr:
        shift_expr continued_shift_expr {
                $$ = processNodes("and_expr",2,
                        $1,
                        $2
                );
        }
        ;
    
continued_shift_expr:
        continued_shift_expr BITWISE_AND shift_expr {
                $$ = processNodes("continued_shift_expr",3,
                        $1,
                        createNode("BITWISE_AND",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

shift_expr:
        arith_expr continued_arith_expr {
                $$ = processNodes("shift_expr",2,
                        $1,
                        $2
                );
        }
        ;

continued_arith_expr:
        continued_arith_expr LEFT_SHIFT arith_expr {
                $$ = processNodes("continued_arith_expr",3,
                        $1,
                        createNode("LEFT_SHIFT",$2,true,false),
                        $3
                );
        }
        | continued_arith_expr RIGHT_SHIFT arith_expr {
                $$ = processNodes("continued_arith_expr",3,
                        $1,
                        createNode("RIGHT_SHIFT",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

arith_expr:
        term continued_term {
                $$ = processNodes("arith_expr",2,
                        $1,
                        $2
                );
        }
        ;

continued_term:
        continued_term PLUS term {
                $$ = processNodes("continued_term",3,
                        $1,
                        createNode("PLUS",$2,true,false),
                        $3
                );
        }
        | continued_term MINUS term {
                $$ = processNodes("continued_term",3,
                        $1,
                        createNode("MINUS",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

term:
        factor continued_factor {
                $$ = processNodes("term",2,
                        $1,
                        $2
                );
        }
        ;

continued_factor:
        continued_factor STAR factor {
                $$ = processNodes("continued_factor",3,
                        $1,
                        createNode("STAR",$2,true,false),
                        $3
                );
        }
        | continued_factor DIV factor {
                $$ = processNodes("continued_factor",3,
                        $1,
                        createNode("DIV",$2,true,false),
                        $3
                );
        }
        | continued_factor AT factor {
                $$ = processNodes("continued_factor",3,
                        $1,
                        createNode("AT",$2,true,false),
                        $3
                );
        }
        | continued_factor REM factor {
                $$ = processNodes("continued_factor",3,
                        $1,
                        createNode("REM",$2,true,false),
                        $3
                );
        }
        | continued_factor FLOOR_DIV factor {
                $$ = processNodes("continued_factor",3,
                        $1,
                        createNode("FLOOR_DIV",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

factor:
        PLUS factor {
                $$ = processNodes("factor",2,
                                createNode("PLUS",$1,true,false),
                                $2
                        );
        }
        | MINUS factor {
                $$ = processNodes("factor",2,
                                createNode("MINUS",$1,true,false),
                                $2
                        );
        }
        | TILDE factor {
                $$ = processNodes("factor",2,
                                createNode("TILDE",$1,true,false),
                                $2
                        );
        }
        | power {
                $$ = $1;
        }
        ;

power:
        atom_expr DOUBLE_STAR factor {
                $$ = processNodes("power",3,
                        $1,
                        createNode("DOUBLE_STAR",$2,true,false),
                        $3
                );
        }
        | atom_expr {
                $$ = $1;
        }
        ;

atom_expr:
        AWAIT atom trailers {
                $$ = processNodes("atom_expr",3,
                        createNode("AWAIT",$1,true,false),
                        $2,
                        $3
                );
        }
        | atom trailers {
                $$ = processNodes("atom_expr",2,
                        $1,
                        $2
                );
        }
        ;

trailers:
        trailers trailer {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: trailer added\n");
        } {
                $$ = processNodes("trailers",2,
                        $1,
                        $2
                );
        }
        | %empty {
        $$ = NULL;
        }
        ;

atom:
        OPENING_BRACKET testlist_comp CLOSING_BRACKET {
                $$ = processNodes("atom",3,
                        createNode("OPENING_BRACKET",$1,true,false),
                        $2,
                        createNode("CLOSING_BRACKET",$3,true,false)
                );
        }
        | OPENING_BRACKET CLOSING_BRACKET {
                $$ = processNodes("atom",2, // "atom: OPENING_BRACKET CLOSING_BRACKET\n
                                createNode("OPENING_BRACKET",$1,true,false),
                                createNode("CLOSING_BRACKET",$2,true,false)
                        );
        }
        | OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET {
                $$ = processNodes("atom",3, // "atom: OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET\n
                                createNode("OPENING_SQ_BRACKET",$1,true,false),
                                $2,
                                createNode("CLOSING_SQ_BRACKET",$3,true,false)
                        );
        }
        | OPENING_SQ_BRACKET CLOSING_SQ_BRACKET {
                $$ = processNodes("atom",2, // "atom: OPENING_SQ_BRACKET CLOSING_SQ_BRACKET\n
                                createNode("OPENING_SQ_BRACKET",$1,true,false),
                                createNode("CLOSING_SQ_BRACKET",$2,true,false)
                        );
        }
        | OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET {
                $$ = processNodes("atom",3, // "atom: OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET\n
                                createNode("OPENING_CURLY_BRACKET",$1,true,false),
                                $2,
                                createNode("CLOSING_CURLY_BRACKET",$3,true,false)
                        );
        }
        | OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET {
                $$ = processNodes("atom",2, // "atom: OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET\n
                                createNode("OPENING_CURLY_BRACKET",$1,true,false),
                                createNode("CLOSING_CURLY_BRACKET",$2,true,false)
                        );
        }
        | NAME { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'NAME' used\n"); } {
                $$ = createNode("NAME",$1,false,true);
        }
        | NUMBER  { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'NUMBER' used\n"); } {
                $$ = createNode("NUMBER",$1,false,true);
        }
        | strings { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'STRING' used\n"); } {
                $$ = $1;
        }      
        | ELLIPSES_LITERAL { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: atom 'ELLIPSES_LITERAL' used\n"); } {
                $$ = createNode("ELLIPSES_LITERAL",$1,false,true);
        }
        | TOKEN_TRUE {
                $$ = createNode("TOKEN_TRUE",$1,false,true);
        }
        | TOKEN_FALSE {
                $$ = createNode("TOKEN_FALSE",$1,false,true);
        }
        | TOKEN_NONE {
                $$ = createNode("TOKEN_NONE",$1,false,true);
        }

strings:
        strings STRING  {
                $$ = processNodes("strings",2,
                        $1,
                        createNode("STRING",$2,false,true)
                );
        }
        | STRING {
                $$ = createNode("STRING",$1,false,true);
        }
        ;

testlist_comp:
        test comp_for {
                $$ = processNodes("testlist_comp",2,
                        $1,
                        $2
                );
        }
        | test continued_testlist COMMA {
                $$ = processNodes("testlist_comp",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | test continued_testlist {
                $$ = processNodes("testlist_comp",2,
                        $1,
                        $2
                );
        }
        | star_expr comp_for {
                $$ = processNodes("testlist_comp",2,
                        $1,
                        $2
                );
        }
        | star_expr continued_testlist COMMA {
                $$ = processNodes("testlist_comp",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | star_expr continued_testlist {
                $$ = processNodes("testlist_comp",2,
                        $1,
                        $2
                );
        }
        ;

continued_testlist:
        continued_testlist COMMA test  {
                $$ = processNodes("continued_testlist",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | continued_testlist COMMA star_expr {
                $$ = processNodes("continued_testlist",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | %empty  { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: no further tests added\n"); $$ = NULL; 
        }      
        ;

trailer:
        OPENING_BRACKET arglist CLOSING_BRACKET {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: arglist within brackets added \n");
        } {
                $$ = processNodes("trailer",3,
                        createNode("OPENING_BRACKET",$1,true,false),
                        $2,
                        createNode("CLOSING_BRACKET",$3,true,false)
                );
        }
        | OPENING_BRACKET CLOSING_BRACKET {
                if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: empty brackets added \n");
        } {
                $$ = processNodes("trailer",2,
                        createNode("OPENING_BRACKET",$1,true,false),
                        createNode("CLOSING_BRACKET",$2,true,false)
                );
        }
        | OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET {
                $$ = processNodes("trailer",3,
                        createNode("OPENING_SQ_BRACKET",$1,true,false),
                        $2,
                        createNode("CLOSING_SQ_BRACKET",$3,true,false)
                );
        }
        | DOT NAME {
                $$ = processNodes("trailer",2,
                        createNode("DOT",$1,true,false),
                        createNode("NAME",$2,false,true)
                );
        }
        ; 

subscriptlist:
        subscript continued_subscript COMMA {
                $$ = processNodes("subscriptlist",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | subscript continued_subscript {
                $$ = processNodes("subscriptlist",2,
                        $1,
                        $2
                );
        }
        ;

continued_subscript:
        continued_subscript COMMA subscript  {
                $$ = processNodes("continued_subscript",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

subscript:
        test { $$ = $1; }
        | test COLON test sliceop {
                $$ = processNodes("subscript",4,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3,
                        $4
                );
        }
        | test COLON test {
                $$ = processNodes("subscript",3,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3
                );
        }
        | test COLON sliceop {
                $$ = processNodes("subscript",3,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3
                );
        }
        | test COLON {
                $$ = processNodes("subscript",2,
                        $1,
                        createNode("COLON",$2,true,false)
                );
        }
        | COLON test sliceop {
                $$ = processNodes("subscript",3,
                        createNode("COLON",$1,true,false),
                        $2,
                        $3
                );
        }
        | COLON test {
                $$ = processNodes("subscript",2,
                        createNode("COLON",$1,true,false),
                        $2
                );
        }
        | COLON sliceop {
                $$ = processNodes("subscript",2,
                        createNode("COLON",$1,true,false),
                        $2
                );
        }
        | COLON {
                $$ = createNode("COLON",$1,true,false);
        }
        ;

sliceop:
        COLON test {
                $$ = processNodes("sliceop",2,
                        createNode("COLON",$1,true,false),
                        $2
                );
        }
        | COLON {
                $$ = createNode("COLON",$1,true,false);
        }
        ;

exprlist:
        expr continued_exprlist COMMA {
                $$ = processNodes("exprlist",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | expr continued_exprlist {
                $$ = processNodes("exprlist",2,
                        $1,
                        $2
                );
        }
        | star_expr continued_exprlist COMMA {
                $$ = processNodes("exprlist",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | star_expr continued_exprlist {
                $$ = processNodes("exprlist",2,
                        $1,
                        $2
                );
        }
        ;

continued_exprlist:
        continued_exprlist COMMA expr {
                $$ = processNodes("continued_exprlist",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | continued_exprlist COMMA star_expr {
                $$ = processNodes("continued_exprlist",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

testlist:
        test continued_comma_test COMMA {
                $$ = processNodes("testlist",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | test continued_comma_test {
                $$ = processNodes("testlist",2,
                        $1,
                        $2
                );
        }
        ;

continued_comma_test:
        continued_comma_test COMMA test {
                $$ = processNodes("continued_comma_test",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ; 

dictorsetmaker:
        test COLON test comp_for {
                $$ = processNodes("dictorsetmaker",4,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3,
                        $4
                );
        }
        | test COLON test continued_dictorset COMMA {
                $$ = processNodes("dictorsetmaker",5,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3,
                        $4,
                        createNode("COMMA",$5,true,false)
                );
        }
        | test COLON test continued_dictorset {
                $$ = processNodes("dictorsetmaker",4,
                        $1,
                        createNode("COLON",$2,true,false),
                        $3,
                        $4
                );
        }
        | DOUBLE_STAR expr comp_for {
                $$ = processNodes("dictorsetmaker",3,
                        createNode("DOUBLE_STAR",$1,true,false),
                        $2,
                        $3
                );
        }
        | DOUBLE_STAR expr continued_dictorset COMMA {
                $$ = processNodes("dictorsetmaker",4,
                        createNode("DOUBLE_STAR",$1,true,false),
                        $2,
                        $3,
                        createNode("COMMA",$4,true,false)
                );
        }
        | DOUBLE_STAR expr continued_dictorset {
                $$ = processNodes("dictorsetmaker",3,
                        createNode("DOUBLE_STAR",$1,true,false),
                        $2,
                        $3
                );
        } 
        | test comp_for {
                $$ = processNodes("dictorsetmaker",2,
                        $1,
                        $2
                );
        }
        | test continued_testlist COMMA {
                $$ = processNodes("dictorsetmaker",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | test continued_testlist {
                $$ = processNodes("dictorsetmaker",2,
                        $1,
                        $2
                );
        }
        | star_expr comp_for {
                $$ = processNodes("dictorsetmaker",2,
                        $1,
                        $2
                );
        }
        | star_expr continued_testlist COMMA {
                $$ = processNodes("dictorsetmaker",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | star_expr continued_testlist {
                $$ = processNodes("dictorsetmaker",2,
                        $1,
                        $2
                );
        }       
        ;

continued_dictorset:
        continued_dictorset COMMA test COLON test {
                $$ = processNodes("continued_dictorset",5,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3,
                        createNode("COLON",$4,true,false),
                        $5
                );
        }
        | continued_dictorset COMMA DOUBLE_STAR expr {
                $$ = processNodes("continued_dictorset",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        createNode("DOUBLE_STAR",$3,true,false),
                        $4
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;     


classdef:
        CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite {
                $$ = processNodes("classdef",6,
                        createNode("CLASS",$1,true,false),
                        createNode("NAME",$2,false,true),
                        createNode("OPENING_BRACKET",$3,true,false),
                        $4,
                        createNode("CLOSING_BRACKET",$5,true,false),
                        createNode("COLON",$6,true,false),
                        $7
                );
        }
        | CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite {
                $$ = processNodes("classdef",5,
                        createNode("CLASS",$1,true,false),
                        createNode("NAME",$2,false,true),
                        createNode("OPENING_BRACKET",$3,true,false),
                        createNode("CLOSING_BRACKET",$4,true,false),
                        createNode("COLON",$5,true,false),
                        $6
                );
        }
        | CLASS NAME COLON suite {
                $$ = processNodes("classdef",3,
                        createNode("CLASS",$1,true,false),
                        createNode("NAME",$2,false,true),
                        createNode("COLON",$3,true,false),
                        $4
                );
        }
        ;

arglist:
        argument continued_argument COMMA {
                $$ = processNodes("arglist",3,
                        $1,
                        $2,
                        createNode("COMMA",$3,true,false)
                );
        }
        | argument continued_argument { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: single argument added in arglist\n"); } {
                $$ = processNodes("arglist",2,
                        $1,
                        $2
                );
        }
        ;

continued_argument:
        continued_argument COMMA argument {
                $$ = processNodes("continued_argument",3,
                        $1,
                        createNode("COMMA",$2,true,false),
                        $3
                );
        }
        | %empty {
                $$ = NULL;
        }
        ;

argument:
        test comp_for {
                $$ = processNodes("argument",2,
                        $1,
                        $2
                
                );
        }
        | test EQUAL test {
                $$ = processNodes("argument",3,
                        $1,
                        createNode("EQUAL",$2,true,false),
                        $3
                );
        }
        | DOUBLE_STAR test {
                $$ = processNodes("argument",2,
                        createNode("DOUBLE_STAR",$1,true,false),
                        $2
                );
        }
        | STAR test {
                $$ = processNodes("argument",2,
                        createNode("STAR",$1,true,false),
                        $2
                );
        }
        | test { if(PARSER_DEBUG_OUTSIDE_VERBOSE) printf("[PARSER]: argument contains a single test\n"); } {
                $$ = $1;
        }
        ;

comp_iter:
        comp_for { $$ = $1; }
        | comp_if { $$ = $1; }
        ;

comp_for:
        FOR exprlist IN or_test comp_iter {
                $$ = processNodes("comp_for",5, // "comp_for: FOR exprlist IN or_test comp_iter\n
                        createNode("FOR",$1,true,false),
                        $2,
                        createNode("IN",$3,true,false),
                        $4,
                        $5
                );
        }
        | FOR exprlist IN or_test {
                $$ = processNodes("comp_for",4, // "comp_for: FOR exprlist IN or_test\n
                        createNode("FOR",$1,true,false),
                        $2,
                        createNode("IN",$3,true,false),
                        $4
                );
        }
        ;

comp_if:
        IF test_nocond comp_iter {
                $$ = processNodes("comp_if",3, // "comp_if: IF test_nocond comp_iter\n
                        createNode("IF",$1,true,false),
                        $2,
                        $3
                );
        }
        | IF test_nocond {
                $$ = processNodes("comp_if",2, // "comp_if: IF test_nocond\n
                        createNode("IF",$1,true,false),
                        $2
                );
        }
        ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "[PARSING ERROR]: Offending token near '%s' at column no %d on line no %d\n", yytext, yylloc.first_column,yylineno);
    return;
}

ASTNode* processNodes(string name,int numNodes, ...)  {
    vector<int> positions;
    int cntr=0;
    vector<ASTNode*> arr;
    va_list args;
    va_start(args, numNodes);
    for (int i = 0; i < numNodes; ++i)  {
        ASTNode* arg = va_arg(args, ASTNode*);
        arr.push_back(arg);
    }
    va_end(args);
    ASTNode* node = nullptr;
    std::vector<ASTNode*> optrs;
    std::vector<ASTNode*> operands;
    bool flag = false;
    std::string content = "";

    // populate vector (do loop for it)
    for(int x=0;x<arr.size();x++) {
        ASTNode* i = arr[x];
        if(i!=NULL) {
                if(i->optr && !i->operand) optrs.push_back(i);
                else if(!i->optr && i->operand) {
                        operands.push_back(i);
                        cntr++;
                }
                else if(!i->optr && !i->operand) {
                        ;
                }
                else {
                        // operand set, none set or both set
                        operands.push_back(i);
                        positions.push_back(cntr);
                        cntr++;
                }
        }
    }

    for(int x=0;x<optrs.size();x++) {
        ASTNode* i = optrs[x];
        if(flag) content += (" ; " + (i->content));
        else content += (i->content);
        flag=true;
    }

    // Single Case:
    if((optrs.size() + operands.size())==1) {
        if(optrs.size()==1) {
                node = optrs[0];
                /* node->optr = true; */
        }
        else {
                node = operands[0];
                /* node->operand = true; */
        }
    }
    else {
        if(positions.size()==1) {
                vector<ASTNode*> ins;
                if(operands.size()>1 && !flag) {
                        for(int z=0;z<operands.size();z++) {
                                /* ((operands[positions[0]])->children).push_back(operands[z]); */
                                if(z!=positions[0]) ins.push_back(operands[z]);
                        }
                        ((operands[positions[0]])->children).insert(((operands[positions[0]])->children).begin(), ins.begin(), ins.end());
                }
                node = operands[positions[0]]; 
                ins.clear();
        }
        else {
                node = createNode(name, content);
                node->optr = flag;
                for(int x=0;x<operands.size();x++) {
                        ASTNode* i = operands[x];
                        node->children.push_back(i);
                        node->operand = true;
                }

                // write to file using a new coutner
                if(AST_DEBUG) {
                        string dotfile = getwithoutextension(dotfile_path);
                        string astfile = getwithoutextension(astfile_path);
                        string temp = dotfile + "_" + to_string(mycounter) + ".dot";
                        string temp2 = astfile + "_" + to_string(mycounter) + ".pdf";
                        printf("[AST]: Generating Extra scripts and ASTs for debugging at %s and %s.\n", const_cast<char*>(temp.c_str()), const_cast<char*>(temp2.c_str()));
                        writeTree(node, getNewId(), const_cast<char*>(temp.c_str()), const_cast<char*>(temp2.c_str()));
                        mycounter++;
                }
        }

    }
    optrs.clear();
    operands.clear();
    return node;
}

int dfs(ASTNode* root) {
        if(root == NULL) return 0;
        if(root->content != "") {
                v_r_dfs.push_back(root);
                return 0;
        }
        for(int i=0; i<(root->children).size(); i++) {
                ASTNode* it = (root->children)[i];
                dfs(it);
        }
        return 0;
}

vector<ASTNode*> ret_single_childs(ASTNode* root) {
        vector<ASTNode*> ret_list;
        if((root->children).size() == 1 &&
                ((((root->children)[0])->children).size() != 0)) ret_list.push_back(root);
        for(int i=0; i<(root->children).size(); i++) {
                ASTNode* it = (root->children)[i];
                vector<ASTNode*> values = ret_single_childs(it);
                for(int j =0; j<values.size();j++) {
                        ASTNode* x = values[j];
                        ret_list.push_back(x);
                }
        }
        return ret_list;
}

int getNewId() { return ++counter; }

string dquote_to_html(string s) {
    string temp = "";
    for(int i=0;i<s.size();i++) {
        if(s[i]=='"') temp = temp + "&quot;";
        else temp = temp + s[i]; 
    }
    return temp;
}

// Write tree to dot file with node, id and filename
pair<string,string> writeTree2(ASTNode* node, int id) {
    string def = "";
    string arr = "";
    def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content) + ")\"];\n";
    for (int i = 0; i < node->children.size(); i++) {
        int childId = getNewId();
        arr = arr + "node" + to_string(id) + " -- node" + to_string(childId) + ";\n";
        pair<string,string> p = writeTree2(node->children[i], childId);
        def = def + p.first;
        arr = arr + p.second;
    }
    return pair<string,string>(def,arr);
}

// Write tree to dot file with node, id and filename
int writeTree3(vector<ASTNode*> nodes, int id, char* filePath, char* astPath) {
        string stringContent = "";
        for(int i=0;i< nodes.size();i++) {
                ASTNode* node = nodes[i];
                // writing it as string
                string def = "";
                string arr = "";
                def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content) + ")\"];\n";
                for (int i = 0; i < node->children.size(); i++) {
                        int childId = getNewId();
                        arr = arr + "node" + to_string(id) + " -- node" + to_string(childId) + ";\n";
                        pair<string,string> p = writeTree2(node->children[i], childId);
                        def = def + p.first;
                        arr = arr + p.second;
                }
                stringContent += ("Subgraph SG" + to_string(i+1) + " {\n"+ def + "\n" + arr + "\n}\n");
        }
        
        // write to file
        if(AST_GENERATION == 1 || DOT_GENERATION == 1) {
                if(strlen(filePath) == 0) strcpy(filePath, "ast.dot");
                FILE* file = fopen(filePath, "w");
                if(!file) {
                        fprintf(stderr, "[COMPILER ERROR]: Failed to create file %s\n", filePath);
                        return 1;
                }
                fprintf(file, "Graph {\n%s\n}\n", const_cast<char*>(stringContent.c_str()));
                fclose(file);
                // Run the command to create AST for the Input program
                if(AST_GENERATION == 1) {
                        // File path
                        string filePath_string(filePath);
                        string astpath_string(astPath);
                        // Command to execute
                        string command = "dot -Tpdf " + filePath_string + " -o " + astpath_string;
                        // Execute the command
                        int result = system(const_cast<char*>(command.c_str()));
                        // Check if the command executed successfully
                        if(result != 0) {
                                fprintf(stderr, "[COMPILER ERROR]: Error in executing the dot script.\n");
                                return 1;
                        }
                        if(DOT_GENERATION == 0) {
                                // Command to execute
                                command = "rm " + filePath_string;
                                // Execute the command
                                int result = system(const_cast<char*>(command.c_str()));
                                // Check if the command executed successfully
                                if(result != 0) {
                                        fprintf(stderr, "[COMPILER ERROR]: Error in deleting the generated dot script.\n");
                                        return 1;
                                }
                        }
                }
        }
        return 0;
}

// Write tree to dot file with node, id and filename
int writeTree(ASTNode* node, int id, char* filePath, char* astPath) {
    // writing it as string
    string def = "";
    string arr = "";
    def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content) + ")\"];\n";
    for (int i = 0; i < node->children.size(); i++) {
        int childId = getNewId();
        arr = arr + "node" + to_string(id) + " -- node" + to_string(childId) + ";\n";
        pair<string,string> p = writeTree2(node->children[i], childId);
        def = def + p.first;
        arr = arr + p.second;
    }
    string stringContent = def + "\n" + arr;
    // over with string
    
    if(AST_GENERATION == 1 || DOT_GENERATION == 1) {
        if(strlen(filePath) == 0) strcpy(filePath, "ast.dot");
        FILE* file = fopen(filePath, "w");
        if(!file) {
                fprintf(stderr, "[COMPILER ERROR]: Failed to create file %s\n", filePath);
                return 1;
        }
        fprintf(file, "Graph {\n%s\n}\n", const_cast<char*>(stringContent.c_str()));
        fclose(file);
        // Run the command to create AST for the Input program
        if(AST_GENERATION == 1) {
                // File path
                string filePath_string(filePath);
                string astpath_string(astPath);
                // Command to execute
                string command = "dot -Tpdf " + filePath_string + " -o " + astpath_string;
                // Execute the command
                int result = system(const_cast<char*>(command.c_str()));
                // Check if the command executed successfully
                if(result != 0) {
                        fprintf(stderr, "[COMPILER ERROR]: Error in executing the dot script.\n");
                        return 1;
                }
                if(DOT_GENERATION == 0) {
                        // Command to execute
                        command = "rm " + filePath_string;
                        // Execute the command
                        int result = system(const_cast<char*>(command.c_str()));
                        // Check if the command executed successfully
                        if(result != 0) {
                                fprintf(stderr, "[COMPILER ERROR]: Error in deleting the generated dot script.\n");
                                return 1;
                        }
                }
        }
    }
    return 0;
}
