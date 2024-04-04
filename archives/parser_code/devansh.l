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
    #include "devansh.tab.h"
    using namespace std;

    int yycolumn = 1;

    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;

    #define YY_DECL int scanner(void)

    /* variables required for raising lexical errors */
    int error_flag = 0;
    char* error_char;

    /* these maps store lexemes and their counts, only for testing purposes */
    map<string,string> lexemeMap;
    map<string,int> lexemeCount;

    /* some helper variables */
    bool reached_eof = false;               // to check if input end reached
    bool continued_line = false;            // to check if explicit line joining has been used
    bool flag = false;
    stack<char> braces_stack;               // parenthesis nesting levels (used for indentation check)

    /* Debug mode specification variables for lexer */
    int LEXER_DEBUG_OUTSIDE_VERBOSE = 0;       // for debugging purposes only
    int LEXER_DEBUG_INSIDE_VERBOSE = 0;        // for verbose output purposes

    /* A scanner state that takes care of tokenization*/
    struct curr_state {
        int curr_indent;                    // current indentation state
        stack<int> indentation_stack;       // stack maintains the indentation level for each statement
        int remaining_indent;               // stores how many indentation tokens are remaining to be accounted
        bool at_start_of_line;
        int buffer_token;                   // buffers one token while calculating indentation 
    };

    static struct curr_state *state = NULL;

    /* function to check if brackets are similar */
    bool isBracketCorrect(char c1, char c2);

    /* function to display error messages */
    void yylxr_error(const char *msg);
%}

%option noyywrap
%option yylineno

%x INSIDE_BRACKET

/*Definitions to match indentation, operators and delimiters in Python 3.6 Grammar*/
blank             [ \t\r\f]
blanks            {blank}+
line_joiner       \\\n
newline           \n
operator          -|\+|\*\*|\*|\/\/|\/|%|@|<<|>>|&|(\|)|\^|~|:=|<|>|<=|>=|==|!=
delimiter         [\(\)\[\]{}]|[,:\.;@=]|>>=|<<=|\*\*=|->|\+=|-=|\*=|\/=|\/\/=|%=|@=|&=|(\|=)|\^=
illegalchars      [\?\$`]
comment           #.*
opening_braces    [\[\({]
closing_braces    [\]\)\}]
ellipses_literal  \.\.\.

/* Definitions to match integer literals in Python 3.6 Grammar */
integer           {decinteger}|{bininteger}|{octinteger}|{hexinteger}
decinteger        {nonzerodigit}(_?{digit})*|0+(_?0)*
bininteger        0(b|B)(_?{bindigit})+
octinteger        0(o|O)(_?{octdigit})+
hexinteger        0(x|X)(_?{hexdigit})+
nonzerodigit      [1-9]
digit             [0-9]
bindigit          [0-1]
octdigit          [0-7]
hexdigit          [0-9a-fA-F]

/* Definitions to match float literals in Python 3.6 Grammar */
floatnumber       {pointfloat}|{exponentfloat}
pointfloat        ({digitpart}?){fraction}|{digitpart}(\.)
exponentfloat     ({digitpart}|{pointfloat}){exponent}
digitpart         {digit}(_?{digit})*
fraction          (\.){digitpart}
exponent          (e|E)((\+|-)?){digitpart}

/* Definitions to match imaginary literals in Python 3.6 Grammar */
imagnumber        ({floatnumber}|{digitpart})(j|J)

/* Definition to match any type of number in Python 3.6 Grammar */
number            {integer}|{floatnumber}|{imagnumber}

/* Definitions to match type specifiers in Python 3.6 Grammar */
type              (int|float|bool|str)

/*Definitions to match identifiers in Python 3.6 Grammar*/
keywords          (False|await|else|import|pass|None|break|except|in|raise|True|class|finally|is|return|and|continue|for|lambda|try|as|def|from|nonlocal|while|assert|del|global|not|with|async|elif|if|or|yield)
Lu                ([A-Z])
Ll                ([a-z])
Lm                ([\xAA\xBA])
Nd                ([0-9])
Pc                [\x95]
id_start          ({Lu}|{Ll}|{Lm}|_)
id_continue       ({id_start}|{Nd}|{Pc}|[\xB7])
id                ({id_start}{id_continue}*)
rid_system        (\_\_(name|init|main)\_\_)
rid_classpvt      (\_\_{id})
rid__             (\_)

/*Definitions for string literals in Python 3.6 Grammar*/
stringprefix            r|u|R|U|f|F|fr|Fr|fR|FR|rf|rF|Rf|RF
stringescapeseq         \\(.|\n)
shortstringchar1        [^\\\'\n]
shortstringchar2        [^\\\"\n]
shortstringitem1        ({shortstringchar1}|{stringescapeseq})
shortstringitem2        ({shortstringchar2}|{stringescapeseq})
longstringchar1         [^\\\']
longstringchar2         [^\\\"]
longstringitem1         ({longstringchar1}|(\'{longstringchar1})|(\'\'{longstringchar1})|{stringescapeseq})
longstringitem2         ({longstringchar2}|(\"{longstringchar2})|(\"\"{longstringchar2})|{stringescapeseq})
shortstring             (\'({shortstringitem1}*)\')|(\"({shortstringitem2}*)\")
longstring              (\'\'\'({longstringitem1}*)\'\'\')|(\"\"\"({longstringitem2}*)\"\"\")
stringliteral           ({stringprefix}?)({shortstring}|{longstring})
invalid_shortstring     (\'({shortstringitem1}*))|(\"({shortstringitem2}*))
invalid_longstring      (\'\'\'({longstringitem1}*))|(\"\"\"({longstringitem2}*))
invalid_stringliteral   ({stringprefix}?)({invalid_shortstring}|{invalid_longstring})

/*Definitions for byte literals*/
bytesprefix             b|B|br|Br|bR|BR|rb|rB|Rb|RB
bytesescapeseq          \\(.|\n)
shortbyteschar1         [^\\\'\n]
shortbyteschar2         [^\\\"\n]
shortbytesitem1         {shortbyteschar1}|{bytesescapeseq}
shortbytesitem2         {shortbyteschar2}|{bytesescapeseq}
longbyteschar1          [^\\\']
longbyteschar2          [^\\\"]
longbytesitem1          ({longbyteschar1}|(\'{longbyteschar1})|(\'\'{longbyteschar1})|{stringescapeseq})
longbytesitem2          ({longbyteschar2}|(\"{longbyteschar2})|(\"\"{longbyteschar2})|{longbyteschar2})
shortbytes              (\'({shortbytesitem1}*)\')|(\"({shortbytesitem2}*)\")
longbytes               (\'\'\'({longbytesitem1}*)\'\'\')|(\"\"\"({longbytesitem2}*)\"\"\")
bytesliteral            {bytesprefix}({shortbytes}|{longbytes})
invalid_shortbytes      (\'({shortbytesitem1}*))|(\"({shortbytesitem2}*))
invalid_longbytes       (\'\'\'({longbytesitem1}*))|(\"\"\"({longbytesitem2}*))
invalid_bytesliteral    ({bytesprefix}?)({invalid_shortbytes}|{invalid_longbytes})

%%

<INSIDE_BRACKET>{closing_braces}                    {
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!isBracketCorrect(braces_stack.top(),yytext[0])) {
        error_flag = 3;
        yylxr_error("Parenthesis do not match\n");
    }
    else {
        braces_stack.pop();
        if(braces_stack.empty()) BEGIN(INITIAL);
    }
    if(!strcmp(yytext,")")) return CLOSING_BRACKET;
    else if(!strcmp(yytext,"]")) return CLOSING_SQ_BRACKET;
    else return CLOSING_CURLY_BRACKET;
}

<INSIDE_BRACKET>{comment}                           { /* ignore */ }
<INSIDE_BRACKET>{blanks}                            { /* ignore */ }
<INSIDE_BRACKET>{blank}*{comment}?{newline}         { yycolumn = 1; continued_line = false;}

<INSIDE_BRACKET>{stringliteral}                     { 
    string s = "";
    for(int i=0;i<yyleng;i++) {
        if(i != yyleng-1 && (yytext[i] == '\\' && yytext[i+1] == '\n') ) i = i+1;
        else s += yytext[i];
    }
    lexemeMap[yytext] = "STRING_LITERAL";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return STRING;
}
<INSIDE_BRACKET>{bytesliteral}                      {
    lexemeMap[yytext] = "BYTE_LITERAL";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return BYTES_STRING;
}

<INSIDE_BRACKET>{number}                            {
    lexemeMap[yytext] = "NUMBER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return NUMBER;
}
   
<INSIDE_BRACKET>{keywords}                          { 
    lexemeMap[yytext] = "KEYWORD";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,"for")) return FOR;
    else if(!strcmp(yytext,"as")) return AS;
    else if(!strcmp(yytext,"in")) return IN;
    else if(!strcmp(yytext,"async")) return ASYNC;
    else if(!strcmp(yytext,"def")) return DEF;
    else if(!strcmp(yytext,"type")) return TYPE;
    else if(!strcmp(yytext,"break")) return BREAK;
    else if(!strcmp(yytext,"continue")) return CONTINUE;
    else if(!strcmp(yytext,"return")) return RETURN;
    else if(!strcmp(yytext,"raise")) return RAISE;
    else if(!strcmp(yytext,"from")) return FROM;
    else if(!strcmp(yytext,"assert")) return ASSERT;
    else if(!strcmp(yytext,"global")) return GLOBAL;
    else if(!strcmp(yytext,"nonlocal")) return NONLOCAL;
    else if(!strcmp(yytext,"if")) return IF;
    else if(!strcmp(yytext,"elif")) return ELIF;
    else if(!strcmp(yytext,"else")) return ELSE;
    else if(!strcmp(yytext,"while")) return WHILE;
    else if(!strcmp(yytext,"try")) return TRY;
    else if(!strcmp(yytext,"finally")) return FINALLY;
    else if(!strcmp(yytext,"except")) return EXCEPT;
    else if(!strcmp(yytext,"and")) return AND;
    else if(!strcmp(yytext,"or")) return OR;
    else if(!strcmp(yytext,"not")) return NOT;
    else if(!strcmp(yytext,"is")) return IS;
    else if(!strcmp(yytext,"True")) return TOKEN_TRUE;
    else if(!strcmp(yytext,"False")) return TOKEN_FALSE;
    else if(!strcmp(yytext,"None")) return TOKEN_NONE;
    else if(!strcmp(yytext,"class")) return CLASS;
    else yylxr_error("Unknown keyword");
}

<INSIDE_BRACKET>{id}|{rid_system}|{rid_classpvt}|{rid__}
                                                    {
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return NAME; 
}

<INSIDE_BRACKET>{opening_braces}                    { 
    braces_stack.push(yytext[0]);
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,"(")) return OPENING_BRACKET;
    else if(!strcmp(yytext,"[")) return OPENING_SQ_BRACKET;
    else return OPENING_CURLY_BRACKET; 
}                                            

<INSIDE_BRACKET>{operator}                          { 
    lexemeMap[yytext] = "OPERATOR";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,"+")) return PLUS;
    else if(!strcmp(yytext,"-")) return MINUS;
    else if(!strcmp(yytext,"*")) return STAR;
    else if(!strcmp(yytext,"**")) return DOUBLE_STAR;
    else if(!strcmp(yytext,"/")) return DIV;
    else if(!strcmp(yytext,"//")) return FLOOR_DIV;
    else if(!strcmp(yytext,"%")) return REM;
    else if(!strcmp(yytext,"@")) return AT;
    else if(!strcmp(yytext,"|")) return BITWISE_OR;
    else if(!strcmp(yytext,"&")) return BITWISE_AND;
    else if(!strcmp(yytext,"^")) return CARET;
    else if(!strcmp(yytext,"~")) return TILDE;    
    else if(!strcmp(yytext,"<<")) return LEFT_SHIFT;
    else if(!strcmp(yytext,">>")) return RIGHT_SHIFT; 
    else return COMP_OP;
}

<INSIDE_BRACKET>{delimiter}                         { 
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,".")) return DOT;
    else if(!strcmp(yytext,":")) return COLON;
    else if(!strcmp(yytext,";")) return SEMI_COLON;
    else if(!strcmp(yytext,",")) return COMMA;
    else if(!strcmp(yytext,"=")) return EQUAL;
    else if(!strcmp(yytext,"->")) return RIGHTARROW;
    else return AUGASSIGN;  

}

<INSIDE_BRACKET>{illegalchars}                      { error_char = yytext; error_flag = 1; yylxr_error("Illegal Character"); }

<INSIDE_BRACKET>{ellipses_literal}                  {
    lexemeMap[yytext] = "ELLIPSES_LITERAL";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return ELLIPSES_LITERAL;
}

<INSIDE_BRACKET>{invalid_stringliteral}             { error_char = yytext; error_flag = 2; yylxr_error("Ill-formed string"); }
<INSIDE_BRACKET>{invalid_bytesliteral}              { error_char = yytext; error_flag = 2; yylxr_error("Ill-formed byte-literal"); }
<INSIDE_BRACKET>.                                   { /* do nothing */}


{comment}|{blanks}                                  { /* ignore*/ }

{blank}*{comment}?{newline}                         {
    flag = (continued_line == true || yylloc.first_column > 1);
    yycolumn = 1;
    continued_line = false;
    if(flag) {
        if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
        return NEWLINE;
    }
}

{line_joiner}                                       {
    /* ignore this since we are continuing within the same logical line */
    continued_line = true;
    yycolumn = 1;
}

{stringliteral}                                     {
    // Code to handle the presence of a string-literal in the program
    string s = "";
    for(int i=0;i<yyleng;i++) {
        if(i != yyleng-1 && (yytext[i] == '\\' && yytext[i+1] == '\n') ) i = i+1;
        else s += yytext[i];
    }
    lexemeMap[yytext] = "STRING_LITERAL";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return STRING;
}

{bytesliteral}                                      {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "BYTE_LITERAL";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return BYTES_STRING;
}

{number}                                            {
    lexemeMap[yytext] = "NUMBER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return NUMBER;
}

{keywords}                                          {
    lexemeMap[yytext] = "KEYWORD";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,"for")) return FOR;
    else if(!strcmp(yytext,"as")) return AS;
    else if(!strcmp(yytext,"in")) return IN;
    else if(!strcmp(yytext,"async")) return ASYNC;
    else if(!strcmp(yytext,"def")) return DEF;
    else if(!strcmp(yytext,"type")) return TYPE;
    else if(!strcmp(yytext,"break")) return BREAK;
    else if(!strcmp(yytext,"continue")) return CONTINUE;
    else if(!strcmp(yytext,"return")) return RETURN;
    else if(!strcmp(yytext,"raise")) return RAISE;
    else if(!strcmp(yytext,"from")) return FROM;
    else if(!strcmp(yytext,"assert")) return ASSERT;
    else if(!strcmp(yytext,"global")) return GLOBAL;
    else if(!strcmp(yytext,"nonlocal")) return NONLOCAL;
    else if(!strcmp(yytext,"if")) return IF;
    else if(!strcmp(yytext,"elif")) return ELIF;
    else if(!strcmp(yytext,"else")) return ELSE;
    else if(!strcmp(yytext,"while")) return WHILE;
    else if(!strcmp(yytext,"try")) return TRY;
    else if(!strcmp(yytext,"finally")) return FINALLY;
    else if(!strcmp(yytext,"except")) return EXCEPT;
    else if(!strcmp(yytext,"and")) return AND;
    else if(!strcmp(yytext,"or")) return OR;
    else if(!strcmp(yytext,"not")) return NOT;
    else if(!strcmp(yytext,"is")) return IS;
    else if(!strcmp(yytext,"True")) return TOKEN_TRUE;
    else if(!strcmp(yytext,"False")) return TOKEN_FALSE;
    else if(!strcmp(yytext,"None")) return TOKEN_NONE;
    else if(!strcmp(yytext,"class")) return CLASS;
    else yylxr_error("Unknown keyword");

}

{rid_system}|{rid_classpvt}|{rid__}                 {
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return NAME;
}     

{id}                                                {
    if(LEXER_DEBUG_INSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return NAME;
}

{opening_braces}                                    {
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation */ 
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    BEGIN(INSIDE_BRACKET); 
    if(!strcmp(yytext,"(")) return OPENING_BRACKET;
    else if(!strcmp(yytext,"[")) return OPENING_SQ_BRACKET;
    else return OPENING_CURLY_BRACKET; 
}


{operator}                                          {
    lexemeMap[yytext] = "OPERATOR";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,"+")) return PLUS;
    else if(!strcmp(yytext,"-")) return MINUS;
    else if(!strcmp(yytext,"*")) return STAR;
    else if(!strcmp(yytext,"**")) return DOUBLE_STAR;
    else if(!strcmp(yytext,"/")) return DIV;
    else if(!strcmp(yytext,"//")) return FLOOR_DIV;
    else if(!strcmp(yytext,"%")) return REM;
    else if(!strcmp(yytext,"@")) return AT;
    else if(!strcmp(yytext,"|")) return BITWISE_OR;
    else if(!strcmp(yytext,"&")) return BITWISE_AND;
    else if(!strcmp(yytext,"^")) return CARET;
    else if(!strcmp(yytext,"~")) return TILDE;    
    else if(!strcmp(yytext,"<<")) return LEFT_SHIFT;
    else if(!strcmp(yytext,">>")) return RIGHT_SHIFT; 
    else return COMP_OP;
}

{ellipses_literal}                                  { 
    lexemeMap[yytext] = "ELLIPSES_LITERAL";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    return ELLIPSES_LITERAL;
}

{delimiter}                                         {
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(LEXER_DEBUG_OUTSIDE_VERBOSE) printf("[LEXER]: %s detected\n",yytext);
    if(!strcmp(yytext,".")) return DOT;
    else if(!strcmp(yytext,":")) return COLON;
    else if(!strcmp(yytext,";")) return SEMI_COLON;
    else if(!strcmp(yytext,",")) return COMMA;
    else if(!strcmp(yytext,"=")) return EQUAL;
    else if(!strcmp(yytext,"->")) return RIGHTARROW;
    else return AUGASSIGN; 
}

{illegalchars}                                      {
    /* the appearance of these characters outside of string literals should lead to unconditional errors */
    error_char = yytext; error_flag = 1; yylxr_error("Illegal character");
}

{invalid_stringliteral}                             { error_char = yytext; error_flag = 2; yylxr_error("Ill-formed string"); }
{invalid_bytesliteral}                              { error_char = yytext;  error_flag = 2; yylxr_error("Ill-formed byte-literal"); }


<<EOF>>                                             {
    yylloc.last_column = 1;
    yylloc.first_column = 1;
    state->at_start_of_line = true;
    yycolumn = 1;
    return ENDMARKER;
}

.                                                   { yylxr_error("Unknown error"); }

%%

// This throws the specified lexical error and terminates the program.
void yylxr_error(const char *msg) {
    if(error_flag == 1)
        fprintf(stderr,"[LEXICAL ERROR]: %s '%s' occurred at line no %d\n",msg, error_char, yylineno);
    else if(error_flag == 2)
        fprintf(stderr, "[LEXICAL ERROR]: %s found at line no %d as follows:\n%s\n",msg, yylineno, error_char);
    else
        fprintf(stderr,"[LEXICAL ERROR]: %s at line no %d\n",msg, yylineno);
    exit(-1);
}

// Push an indentation column into the stack for indentation data structure maintenance.
void push_idt(int col) {
    state->remaining_indent++;
    state->indentation_stack.push(col);
    return;
}

// Pop the indentation column from the stack upon moving out.
// Throws an error upon getting inconsistent indentation situation. We cannot pop an inner indentation level from the outer one.
void pop_idt(int col) {
    while(state->indentation_stack.size() > 1 && col < state->indentation_stack.top()) {
        state->indentation_stack.pop();
        state->remaining_indent--;
    }
    if(col > state->indentation_stack.top()) yylxr_error("Indentation Error\n");
    return;
}

// Compute the indentation level.
void calculate_indentation(int col) {
    int idt_level = state->indentation_stack.top();
    if(col >  idt_level) push_idt(col);
    else if(col < idt_level) pop_idt(col);
    return;
}

// Consistency in language bracketing.
bool isBracketCorrect(char c1, char c2) {
    if( (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}') ) return true;
    else return false;
}

// Initialize the lexer state and set the lexer input stream as the file object.
int init_lexer(FILE *inputfile, FILE *outputfile) {
    // Set the input stream for the lexer to a file. This is required when an input is given from
    // a program file rather than the standard input itself.
    if(inputfile != stdin) yyin = inputfile;
    if(outputfile != stdout) yyout = outputfile;
    if(state != NULL) delete state; // Free up previously used ghost states of the lexer.

    /* Initialise scanner state structure */
    state = new struct curr_state;
    if(state == NULL) {
        fprintf(stderr, "[LEXER ERROR] Memory allocation for lexer failed.\n");
        return 1;
    }
    state->curr_indent = 1;
    (state->indentation_stack).push(1);
    state->remaining_indent = 0;
    state->buffer_token = -1;
    state->at_start_of_line = false;
    return 0;
}

// The main lexer loop which is used by the parser loop yyparse() for getting the tokens.
int yylex() {
    int curr_token = -1;
    if(reached_eof) yyterminate();

    /* Before scanning the line for other tokens, check the indentation */
    if(state->remaining_indent > 0) {
        state->remaining_indent--;
        curr_token = INDENT;
    }
    else if(state->remaining_indent < 0) {
        state->remaining_indent++;
        curr_token = DEDENT;
    }
    /* Check for buffered tokens */
    else if(state->buffer_token != -1) {
        curr_token = state->buffer_token;
        state->buffer_token = -1;
    }
    /* Scanning for other tokens */
    else {
        curr_token = scanner();

        if(curr_token == NEWLINE) state->at_start_of_line = true;
        else if(state->at_start_of_line == true) {
            state->at_start_of_line = false;
            calculate_indentation(yylloc.first_column);
            state->buffer_token = curr_token;
            curr_token = yylex();
        }
    }

    if(curr_token == ENDMARKER) reached_eof = true;
    return curr_token;
}
