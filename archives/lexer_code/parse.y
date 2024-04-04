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
    int yylex(void);
    void yyerror(char const*);
%}

%token TYPENAME ID
%token NUMBER
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token LPAREN
%token RPAREN
%token EOL

%%

/* Section: Declarations */
/* This section contains variable declarations */

/* Section: Rules */
/* This section contains grammar rules */

expression: expression PLUS expression
          | expression MINUS expression
          | expression MULTIPLY expression
          | expression DIVIDE expression
          | LPAREN expression RPAREN
          | NUMBER
          ;

%%

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 1;
}
