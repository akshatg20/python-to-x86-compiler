%option yylineno

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
    #include "shashwat.tab.c"
    using namespace std;

    extern int yyerror(string);
    extern int yyparse();

    /* these maps store lexemes and their counts, only for testing purposes */
    map<string,string> lexemeMap;
    map<string,int> lexemeCount;

    /* variables required for raising lexical errors */
    int error_flag = 0;
    string error_char;

    bool DEBUG_MODE = true;

    /* function to check if input file is of correct extension or not */
    bool isPyFile(const char* filename) {
        const char* extension = ".py";
        size_t len = strlen(filename);
        return (len > strlen(extension) && strcmp(filename + len - strlen(extension), extension) == 0);
    }

    /* these stacks store opening braces, required for maintaining state in case of nested brackets */
    stack<char> braces_stack;

    /* this stack maintains the indentation level for each statement */
    stack<int> indentation_stack;

    /* function to calculate indentation level */
    int current_indentatation() {
        int indentation = 0;                     
        int numWhiteSpaces = 0, numTabs = 0;   
        
        // counting the number of whitespaces and tabs
        for(int i = 0; i < strlen(yytext); i++) {
            if(yytext[i] == ' ') numWhiteSpaces++;
            else if(yytext[i] == '\t') numTabs++;
            else if(yytext[i] == '\f' || yytext[i] == '\r') continue; 
            else break;
        }

        indentation += numWhiteSpaces;                 
        indentation += 4*(numTabs);           
        
        return indentation;
    }

    /* function to check if brackets are similar */
    bool isBracketCorrect(char c1, char c2) {
        if( (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}') )
            return true;
        else return false;
    }
%}

%option noyywrap
%option yylineno

%x INDENTATION_TEST
%x INSIDE_BRACKET

/*Definitions to match indentation, operators and delimiters in Python 3.12 Grammar*/
indentation ^{blanks}*
newline [\n\r]
line_joiner \\{newline}
double_star \*\*
leftshift_o <<
rightshift_o >>
floordiv_o \/\/
star_o \*
plus_o \+
minus_o \-
div_o \/
rem_o %
tilde_o \~
caret_o \^
bitand_o &
bitor_o \|
operator @|:=|<|>|<=|>=|==|!=
colon_d :
semicolon_d \;
comma_d ,
openingbracket_d \(
closingbracket_d \)
openingsqbracket_d \[
closingsqbracket_d \]
openingcurbracket_d \{
closingcurbracket_d \}
delimiter [\.@=]|(\|=)|\^=
rightarrow ->
augassign >>=|<<=|\*\*=|\/\/=|\+=|-=|\*=|\/=|=|%=|@=|&=
illegalchars [\?\$`]
comment {blanks}*#.*\n
blanks [ \t\r\f]
 /* opening_braces [\[\({]
 closing_braces [\]\)\}] */
ellipses_literal \.\.\.

/* Definitions to match integer literals in Python 3.12 Grammar */
integer {decinteger}|{bininteger}|{octinteger}|{hexinteger}
decinteger {nonzerodigit}(_?{digit})*|0+(_?0)*
bininteger 0(b|B)(_?{bindigit})+
octinteger 0(o|O)(_?{octdigit})+
hexinteger 0(x|X)(_?{hexdigit})+
nonzerodigit [1-9]
digit [0-9]
bindigit [0-1]
octdigit [0-7]
hexdigit [0-9a-fA-F]

/* Definitions to match float literals in Python 3.12 Grammar */
floatnumber {pointfloat}|{exponentfloat}
pointfloat ({digitpart}?){fraction}|{digitpart}(\.)
exponentfloat ({digitpart}|{pointfloat}){exponent}
digitpart {digit}(_?{digit})*
fraction (\.){digitpart}
exponent (e|E)((\+|-)?){digitpart}

/* Definitions to match imaginary literals in Python 3.12 Grammar */
imagnumber ({floatnumber}|{digitpart})(j|J)

/* Definitions to match type specifiers in Python 3.12 Grammar */
type (int|float|bool|str)

/*Definitions to match identifiers in Python 3.12 Grammar*/
async_k          async
raise_k          raise
from_k           from
assert_k         assert
global_k         global
nonlocal_k       nonlocal
if_k             if
elif_k           elif
else_k           else
while_k          while
for_k            for
try_k            try
in_k             in
finally_k        finally
except_k         except
as_k             as
and_k            and
or_k             or
not_k            not
is_k             is
class_k          class
TOKEN_TRUE_k     True
TOKEN_FALSE_k    False
TOKEN_NONE_k     None
await_k          await
def_k            def
break_k          break
continue_k       continue
return_k         return
keywords         (del|with|yield)

Lu              ([A-Z])
Ll              ([a-z])
Lm              ([\xAA\xBA])
Nd              ([0-9])
Pc              [\x95]
id_start        ({Lu}|{Ll}|{Lm}|_)
id_continue     ({id_start}|{Nd}|{Pc}|[\xB7])
id              ({id_start}{id_continue}*)
rid_system      (\_\_(name|init|main)\_\_)
rid_classpvt    (\_\_{id})
rid__           (\_)

/*Definitions for string literals in Python 3.12 Grammar*/
stringprefix    r|u|R|U|f|F|fr|Fr|fR|FR|rf|rF|Rf|RF
stringescapeseq \\(.|\n)
shortstringchar1 [^\\\'\n]
shortstringchar2 [^\\\"\n]
shortstringitem1 ({shortstringchar1}|{stringescapeseq})
shortstringitem2 ({shortstringchar2}|{stringescapeseq})
longstringchar  [^\\]
longstringitem  ({longstringchar}|{stringescapeseq})
shortstring     (\'({shortstringitem1}*)\')|(\"({shortstringitem2}*)\")
longstring      (\'\'\'({longstringitem}*)\'\'\')|(\"\"\"({longstringitem}*)\"\"\")
stringliteral   ({stringprefix}?)({shortstring}|{longstring})

/*Definitions for byte literals*/
bytesprefix     b|B|br|Br|bR|BR|rb|rB|Rb|RB
bytesescapeseq  \\(.|\n)
shortbyteschar1  [^\\\'\n]
shortbyteschar2  [^\\\"\n]
shortbytesitem1  {shortbyteschar1}|{bytesescapeseq}
shortbytesitem2 {shortbyteschar2}|{bytesescapeseq}
longbyteschar   [^\\]
longbytesitem   {longbyteschar}|{bytesescapeseq}
shortbytes      (\'({shortbytesitem1}*)\')|(\"({shortbytesitem2}*)\")
longbytes       (\'\'\'({longbytesitem}*)\'\'\')|(\"\"\"({longbytesitem}*)\"\"\")
bytesliteral    {bytesprefix}({shortbytes}|{longbytes})

%%

<INSIDE_BRACKET>{closingbracket_d}            {
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(!isBracketCorrect(braces_stack.top(),yytext[0])) {
        error_flag = 3;
        return 0;
    }
    else {
        braces_stack.pop();
        if(braces_stack.empty()) BEGIN(INITIAL);
    }
    return CLOSING_BRACKET;

}
<INSIDE_BRACKET>{closingsqbracket_d}            {
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(!isBracketCorrect(braces_stack.top(),yytext[0])) {
        error_flag = 3;
        return 0;
    }
    else {
        braces_stack.pop();
        if(braces_stack.empty()) BEGIN(INITIAL);
    }
    return CLOSING_SQ_BRACKET;

}
<INSIDE_BRACKET>{closingcurbracket_d}            {
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(!isBracketCorrect(braces_stack.top(),yytext[0])) {
        error_flag = 3;
        return 0;
    }
    else {
        braces_stack.pop();
        if(braces_stack.empty()) BEGIN(INITIAL);
    }
    return CLOSING_CURLY_BRACKET;
}
 /* <INSIDE_BRACKET>{closing_braces}            {
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
    if(!isBracketCorrect(braces_stack.top(),yytext[0])) {
        error_flag = 3;
        return 0;
    }
    else {
        braces_stack.pop();
        if(braces_stack.empty()) BEGIN(INITIAL);
    }
} */

<INSIDE_BRACKET>{stringliteral}                     { 
    string s = "";
    for(int i=0;i<yyleng;i++) {
        if(i != yyleng-1 && (yytext[i] == '\\' && yytext[i+1] == '\n') ) i = i+1;
        else s += yytext[i];
    }
    lexemeMap[s] = "STRING_LITERAL"; 
    lexemeCount[s]++;
}
<INSIDE_BRACKET>{bytesliteral}                      { lexemeMap[yytext] = "BYTE_LITERAL"; lexemeCount[yytext]++; }

<INSIDE_BRACKET>{imagnumber}                        { lexemeMap[yytext] = "IMAGINARY_LITERAL"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{floatnumber}                       { lexemeMap[yytext] = "FLOAT_LITERAL"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{integer}                           { lexemeMap[yytext] = "INTEGER_LITERAL"; lexemeCount[yytext]++; }

<INSIDE_BRACKET>{type}                              { lexemeMap[yytext] = "TYPE_SPECIFER"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TYPE;}  

<INSIDE_BRACKET>{async_k}                          { lexemeMap[yytext] = "ASYNC"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ASYNC;}
<INSIDE_BRACKET>{raise_k}                          { lexemeMap[yytext] = "RAISE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return RAISE;}
<INSIDE_BRACKET>{from_k}                           { lexemeMap[yytext] = "FROM"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FROM;}
<INSIDE_BRACKET>{assert_k}                         { lexemeMap[yytext] = "ASSERT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ASSERT;}
<INSIDE_BRACKET>{global_k}                         { lexemeMap[yytext] = "GLOBAL"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return GLOBAL;}
<INSIDE_BRACKET>{nonlocal_k}                       { lexemeMap[yytext] = "NONLOCAL"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return NONLOCAL;}
<INSIDE_BRACKET>{if_k}                             { lexemeMap[yytext] = "IF"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return IF;}
<INSIDE_BRACKET>{elif_k}                           { lexemeMap[yytext] = "ELIF"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ELIF;}
<INSIDE_BRACKET>{else_k}                           { lexemeMap[yytext] = "ELSE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ELSE;}
<INSIDE_BRACKET>{while_k}                          { lexemeMap[yytext] = "WHILE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return WHILE;}
<INSIDE_BRACKET>{for_k}                            { lexemeMap[yytext] = "FOR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FOR;}
<INSIDE_BRACKET>{try_k}                            { lexemeMap[yytext] = "TRY"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TRY;}
<INSIDE_BRACKET>{in_k}                             { lexemeMap[yytext] = "IN"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return IN;}
<INSIDE_BRACKET>{finally_k}                        { lexemeMap[yytext] = "FINALLY"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FINALLY;}
<INSIDE_BRACKET>{except_k}                         { lexemeMap[yytext] = "EXCEPT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return EXCEPT;}
<INSIDE_BRACKET>{as_k}                             { lexemeMap[yytext] = "AS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AS;}
<INSIDE_BRACKET>{and_k}                            { lexemeMap[yytext] = "AND"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AND;}
<INSIDE_BRACKET>{or_k}                             { lexemeMap[yytext] = "OR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return OR;}
<INSIDE_BRACKET>{not_k}                            { lexemeMap[yytext] = "NOT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return NOT;}
<INSIDE_BRACKET>{is_k}                             { lexemeMap[yytext] = "IS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return IS;}
<INSIDE_BRACKET>{class_k}                          { lexemeMap[yytext] = "CLASS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return CLASS;}
<INSIDE_BRACKET>{TOKEN_TRUE_k}                     { lexemeMap[yytext] = "TOKEN_TRUE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TOKEN_TRUE;}
<INSIDE_BRACKET>{TOKEN_FALSE_k}                    { lexemeMap[yytext] = "TOKEN_FALSE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TOKEN_FALSE;}
<INSIDE_BRACKET>{TOKEN_NONE_k}                     { lexemeMap[yytext] = "TOKEN_NONE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TOKEN_NONE;}
<INSIDE_BRACKET>{await_k}                          { lexemeMap[yytext] = "AWAIT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AWAIT;}
<INSIDE_BRACKET>{break_k}                          { lexemeMap[yytext] = "BREAK"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return BREAK;}
<INSIDE_BRACKET>{continue_k}                       { lexemeMap[yytext] = "CONTINUE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return CONTINUE;}
<INSIDE_BRACKET>{return_k}                         { lexemeMap[yytext] = "RETURN"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return RETURN;}
<INSIDE_BRACKET>{def_k}                            { lexemeMap[yytext] = "KEYWORDS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return DEF;}
<INSIDE_BRACKET>{keywords}                         { lexemeMap[yytext] = "KEYWORDS"; lexemeCount[yytext]++; }

<INSIDE_BRACKET>{rid_system}                       { lexemeMap[yytext] = "RID"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{rid_classpvt}                     { lexemeMap[yytext] = "RID"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{rid__}                            { lexemeMap[yytext] = "RID"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{id}                               { lexemeMap[yytext] = "NAME"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return NAME;}

<INSIDE_BRACKET>{openingbracket_d}                 { lexemeMap[yytext] = "OPENING_BRACKET"; lexemeCount[yytext]++; braces_stack.push(yytext[0]); yylval.lexeme = strdup(yytext);return OPENING_BRACKET;} 
<INSIDE_BRACKET>{openingsqbracket_d}               { lexemeMap[yytext] = "OPENING_SQ_BRACKET"; lexemeCount[yytext]++; braces_stack.push(yytext[0]); yylval.lexeme = strdup(yytext);return OPENING_SQ_BRACKET;} 
<INSIDE_BRACKET>{openingcurbracket_d}              { lexemeMap[yytext] = "OPENING_CURLY_BRACKET"; lexemeCount[yytext]++; braces_stack.push(yytext[0]); yylval.lexeme = strdup(yytext);return OPENING_CURLY_BRACKET;}                                            
<INSIDE_BRACKET>{double_star}                      { lexemeMap[yytext] = "DOUBLESTAR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return DOUBLE_STAR;} 
<INSIDE_BRACKET>{leftshift_o}                      { lexemeMap[yytext] = "LEFT_SHIFT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return LEFT_SHIFT;} 
<INSIDE_BRACKET>{rightshift_o}                     { lexemeMap[yytext] = "RIGHT_SHIFT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return RIGHT_SHIFT;} 
<INSIDE_BRACKET>{floordiv_o}                       { lexemeMap[yytext] = "FLOORDIV"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FLOOR_DIV;} 
<INSIDE_BRACKET>{star_o}                           { lexemeMap[yytext] = "STAR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return STAR;} 
<INSIDE_BRACKET>{plus_o}                           { lexemeMap[yytext] = "PLUS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return PLUS;} 
<INSIDE_BRACKET>{minus_o}                          { lexemeMap[yytext] = "MINUS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return MINUS;} 
<INSIDE_BRACKET>{div_o}                            { lexemeMap[yytext] = "DIV"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return DIV;} 
<INSIDE_BRACKET>{rem_o}                            { lexemeMap[yytext] = "REM"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return REM;} 
<INSIDE_BRACKET>{tilde_o}                          { lexemeMap[yytext] = "TILDE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TILDE;}
<INSIDE_BRACKET>{caret_o}                          { lexemeMap[yytext] = "CARET"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return CARET;} 

<INSIDE_BRACKET>{bitand_o}                         { lexemeMap[yytext] = "BITWISE_AND"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return BITWISE_AND;} 
<INSIDE_BRACKET>{bitor_o}                          { lexemeMap[yytext] = "BITWISE_OR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return BITWISE_OR;}                                           
<INSIDE_BRACKET>{operator}                         { lexemeMap[yytext] = "OPERATOR"; lexemeCount[yytext]++; }

<INSIDE_BRACKET>{rightarrow}                       { lexemeMap[yytext] = "RIGHTARROW"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return RIGHTARROW;}
<INSIDE_BRACKET>{augassign}                        { lexemeMap[yytext] = "AUGASSIGN"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AUGASSIGN;}

<INSIDE_BRACKET>{colon_d}                        { lexemeMap[yytext] = "COLON"; lexemeCount[yytext]++;  yylval.lexeme = strdup(yytext);return COLON;}
<INSIDE_BRACKET>{semicolon_d}                        { lexemeMap[yytext] = "SEMICOLON "; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return SEMI_COLON;}
<INSIDE_BRACKET>{comma_d}                        { lexemeMap[yytext] = "COMMA"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return COMMA;}
<INSIDE_BRACKET>{delimiter}                        { lexemeMap[yytext] = "DELIMITER"; lexemeCount[yytext]++; }

<INSIDE_BRACKET>{illegalchars}                     { error_flag = 1; error_char = yytext; return 0; }
<INSIDE_BRACKET>{comment}|{blanks}                 { /* do nothing */}
<INSIDE_BRACKET>{ellipses_literal}                 { lexemeMap[yytext] = "ELLIPSES_LITERAL"; lexemeCount[yytext]++; }


<INSIDE_BRACKET>{newline}                           {yylval.lexeme = strdup(yytext);return NEWLINE;}
<INSIDE_BRACKET>.                                   { /* do nothing */}

<INDENTATION_TEST>{indentation}               {
        /* this rule will be matched when we find some indentation at the start of a line, prompting the lexer 
        to note the indentation and come out of indentation testing mode */
        BEGIN(INITIAL);

        /* current indentation level is higher, then add to stack and return INDENT token */
        if(current_indentatation() > indentation_stack.top() ) {
            if(DEBUG_MODE)
                printf("[LEXER]: <INDENT,%d> generated at line %d\n", current_indentatation(),yylineno);
            indentation_stack.push(current_indentatation());
            /* return INDENT */
        }
        /* current indentation level is lower, then pop the stack until it is lower and keep returning DEDENT tokens */
        else if(current_indentatation() < indentation_stack.top()) {
            while(current_indentatation() < indentation_stack.top()) {
                if(DEBUG_MODE)
                    printf("[LEXER]: <DEDENT,%d> generated at line %d\n",indentation_stack.top(),yylineno);
                indentation_stack.pop();
                /* return DEDENT */
            }
            /* check if the current indentation matches a previous indentation on the stack, if not return error */
            if(current_indentatation() != indentation_stack.top()) {
                error_flag = 2;
                return 0;
            }
        }
        else {
            /* current indentation is same, do nothing */
        }
}

<INDENTATION_TEST>{newline}     {yylval.lexeme = strdup(yytext); return NEWLINE;}
<INDENTATION_TEST>{comment}     { /* do nothing */}

<INDENTATION_TEST>.             {
        /* this rule will be matched when there is no indentation, prompting the lexer to set indentation to zero,
        and come out of indentation testing mode */
        BEGIN(INITIAL);
        /* we also need to return the character we matched back to input stream as it will be part of some other token */
        unput(*yytext);

        if(indentation_stack.top() > 0) {
            while(indentation_stack.top() > 0) { 
                /* return DEDENT ; */ 
                if(DEBUG_MODE)
                    printf("[LEXER]: <DEDENT,%d> generated at line %d\n",indentation_stack.top(),yylineno);
                indentation_stack.pop(); 
            }
            /* indentation error is not possible here as a zero will always be present on the stack */
        }
        else {
            /* no indentation generated */
        }
}

{indentation}       {
    /* If we encounter indentation at first line itself, return error. */
    if(yylineno == 1)   {error_flag = 2; return 0; }
    /* otherwise if we encounter blank space in INITIAL mode, it is probably due to explicit line joining and should be ignored */
}

{stringliteral}         {
    // Code to handle the presence of a string-literal in the program
    string s = "";
    for(int i=0;i<yyleng;i++) {
        if(i != yyleng-1 && (yytext[i] == '\\' && yytext[i+1] == '\n') ) i = i+1;
        else s += yytext[i];
    }
    lexemeMap[s] = "STRING_LITERAL"; 
    lexemeCount[s]++;
}

{bytesliteral}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "BYTES_LITERAL"; 
    lexemeCount[yytext]++;
}

{imagnumber}             { 
    lexemeMap[yytext] = "IMAGINARY_LITERAL"; 
    lexemeCount[yytext]++; 
}

{floatnumber}            { 
    lexemeMap[yytext] = "FLOAT_LITERAL"; 
    lexemeCount[yytext]++; 
}

{integer}                { 
    lexemeMap[yytext] = "INTEGER_LITERAL"; 
    lexemeCount[yytext]++; 
}

{type}          {
    lexemeMap[yytext] = "TYPE_SPECIFIER";
    lexemeCount[yytext]++;
    yylval.lexeme = strdup(yytext);
    return TYPE;
}

{async_k}                          { lexemeMap[yytext] = "ASYNC"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ASYNC;}
{raise_k}                          { lexemeMap[yytext] = "RAISE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return RAISE;}
{from_k}                           { lexemeMap[yytext] = "FROM"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FROM;}
{assert_k}                         { lexemeMap[yytext] = "ASSERT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ASSERT;}
{global_k}                         { lexemeMap[yytext] = "GLOBAL"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return GLOBAL;}
{nonlocal_k}                       { lexemeMap[yytext] = "NONLOCAL"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return NONLOCAL;}
{if_k}                             { lexemeMap[yytext] = "IF"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return IF;}
{elif_k}                           { lexemeMap[yytext] = "ELIF"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ELIF;}
{else_k}                           { lexemeMap[yytext] = "ELSE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return ELSE;}
{while_k}                          { lexemeMap[yytext] = "WHILE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return WHILE;}
{for_k}                            { lexemeMap[yytext] = "FOR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FOR;}
{try_k}                            { lexemeMap[yytext] = "TRY"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TRY;}
{in_k}                             { lexemeMap[yytext] = "IN"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return IN;}
{finally_k}                        { lexemeMap[yytext] = "FINALLY"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FINALLY;}
{except_k}                         { lexemeMap[yytext] = "EXCEPT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return EXCEPT;}
{as_k}                             { lexemeMap[yytext] = "AS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AS;}
{and_k}                            { lexemeMap[yytext] = "AND"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AND;}
{or_k}                             { lexemeMap[yytext] = "OR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return OR;}
{not_k}                            { lexemeMap[yytext] = "NOT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return NOT;}
{is_k}                             { lexemeMap[yytext] = "IS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return IS;}
{class_k}                          { lexemeMap[yytext] = "CLASS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return CLASS;}
{TOKEN_TRUE_k}                     { lexemeMap[yytext] = "TOKEN_TRUE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TOKEN_TRUE;}
{TOKEN_FALSE_k}                    { lexemeMap[yytext] = "TOKEN_FALSE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TOKEN_FALSE;}
{TOKEN_NONE_k}                     { lexemeMap[yytext] = "TOKEN_NONE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TOKEN_NONE;}
{await_k}                          { lexemeMap[yytext] = "AWAIT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return AWAIT;}

{def_k}       {    
    lexemeMap[yytext] = "DEF"; 
    lexemeCount[yytext]++;

    yylval.lexeme = strdup(yytext);return DEF;
}

{break_k}       {    
    lexemeMap[yytext] = "BREAK"; 
    lexemeCount[yytext]++;

    yylval.lexeme = strdup(yytext);return BREAK;
}

{continue_k}       {    
    lexemeMap[yytext] = "CONTINUE"; 
    lexemeCount[yytext]++;

    yylval.lexeme = strdup(yytext);return CONTINUE;
}

{return_k}       {    
    lexemeMap[yytext] = "RETURN"; 
    lexemeCount[yytext]++;

    yylval.lexeme = strdup(yytext);return RETURN;
}

{keywords}       {    
    lexemeMap[yytext] = "KEYWORDS"; 
    lexemeCount[yytext]++;
}

{rid_system}|{rid_classpvt}|{rid__}   {
    lexemeMap[yytext] = "RID"; 
    lexemeCount[yytext]++;
}     

{id}                { 
    lexemeMap[yytext] = "NAME"; 
    lexemeCount[yytext]++;

    yylval.lexeme = strdup(yytext);return NAME;
}

{openingbracket_d}    { 
    lexemeMap[yytext] = "OPENING_BRACKET"; 
    lexemeCount[yytext]++; 
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation */ 
    BEGIN(INSIDE_BRACKET); 

    yylval.lexeme = strdup(yytext);return OPENING_BRACKET;
}
{openingsqbracket_d}    { 
    lexemeMap[yytext] = "OPENING_SQ_BRACKET"; 
    lexemeCount[yytext]++; 
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation */ 
    BEGIN(INSIDE_BRACKET); 

    yylval.lexeme = strdup(yytext);return OPENING_SQ_BRACKET;
}
{openingcurbracket_d}    { 
    lexemeMap[yytext] = "OPENING_CURLY_BRACKET"; 
    lexemeCount[yytext]++; 
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation */ 
    BEGIN(INSIDE_BRACKET); 

    yylval.lexeme = strdup(yytext);return OPENING_CURLY_BRACKET;
}

 /* {opening_braces}    { 
    lexemeMap[yytext] = "DELIMITER"; 
    lexemeCount[yytext]++; 
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation 
    BEGIN(INSIDE_BRACKET); 
} */

{comment}           {
    /* comments in themselves are not useful but since they end with a newline, they are used to prompt the indentation testing mode */
    BEGIN(INDENTATION_TEST);
    /* we also might have to return a newline token from here */
    /* return NEWLINE */
}

{line_joiner}       {
    lexemeMap[yytext] = "LINE_JOINER";
    lexemeCount[yytext]++;
    /* ignore this since we are continuing within the same logical line */
}

{newline}           {
    /* this marks the end of a logical line */
    /* We have to probably return a NEWLINE token from here 
        return NEWLINE;    
    */
    /* After encountering a newline, we will go into indentation testing mode */
    BEGIN(INDENTATION_TEST);

    yylval.lexeme = strdup(yytext);return NEWLINE;
}

{double_star}          {
    lexemeMap[yytext] = "DOUBLESTAR";
    lexemeCount[yytext]++;
    yylval.lexeme = strdup(yytext);return DOUBLE_STAR;
    /* return OPERATOR */
}
{leftshift_o}                      { lexemeMap[yytext] = "LEFT_SHIFT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return LEFT_SHIFT;} 
{rightshift_o}                     { lexemeMap[yytext] = "RIGHT_SHIFT"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return RIGHT_SHIFT;} 
{floordiv_o}                       { lexemeMap[yytext] = "FLOORDIV"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return FLOOR_DIV;} 
{star_o}                           { lexemeMap[yytext] = "STAR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return STAR;} 
{plus_o}                           { lexemeMap[yytext] = "PLUS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return PLUS;} 
{minus_o}                          { lexemeMap[yytext] = "MINUS"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return MINUS;} 
{div_o}                            { lexemeMap[yytext] = "DIV"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return DIV;} 
{rem_o}                            { lexemeMap[yytext] = "REM"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return REM;} 
{tilde_o}                          { lexemeMap[yytext] = "TILDE"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return TILDE;}
{caret_o}                          { lexemeMap[yytext] = "CARET"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return CARET;} 
{bitand_o}                         { lexemeMap[yytext] = "BITWISE_AND"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return BITWISE_AND;} 
{bitor_o}                          { lexemeMap[yytext] = "BITWISE_OR"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return BITWISE_OR;}       
{operator}          {
    lexemeMap[yytext] = "OPERATOR";
    lexemeCount[yytext]++;
    /* return OPERATOR */
}

{ellipses_literal}                  { 
    lexemeMap[yytext] = "ELLIPSES_LITERAL"; 
    lexemeCount[yytext]++; 
}

{augassign}       { 
    lexemeMap[yytext] = "AUGASSIGN";
    lexemeCount[yytext]++;
    yylval.lexeme = strdup(yytext);return AUGASSIGN;
}

{rightarrow}       { 
    lexemeMap[yytext] = "RIGHTARROW";
    lexemeCount[yytext]++;
    yylval.lexeme = strdup(yytext);return RIGHTARROW;
}

{colon_d}                       { lexemeMap[yytext] = "COLON"; lexemeCount[yytext]++;  yylval.lexeme = strdup(yytext);return COLON;}
{semicolon_d}                    { lexemeMap[yytext] = "SEMICOLON "; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return SEMI_COLON;}
{comma_d}                        { lexemeMap[yytext] = "COMMA"; lexemeCount[yytext]++; yylval.lexeme = strdup(yytext);return COMMA;}

{delimiter}       { 
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
}

{illegalchars}      {
    /* the appearance of these characters outside of string literals should lead to unconditional errors */
    error_flag = 1;
    error_char = yytext;
    return 0;
}

{blanks}            {
    /* ignore blank spaces */
}


<<EOF>>             {
    /*Match the EOF file character and generate required number of dedent tokens*/
    if(indentation_stack.top() > 0) {
        while(indentation_stack.top() != 0) {
            /* return DEDENT */
            if(DEBUG_MODE) {
                printf("[LEXER]: <DEDENT,%d> generated after EOF\n", indentation_stack.top());
            }
            indentation_stack.pop();
        }
    }
    // return 0;

    yylval.lexeme = strdup(yytext);
    return ENDMARKER;
}

.                   { 
    /* ignore as of now */
}

%%


/* int main(int argc, char** argv) {
    if (argc != 2 || !isPyFile(argv[1])) {
        cerr << "Usage: " << argv[0] << " <filename.py>" << endl;
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    
    indentation_stack.push(0);
    yyin = inputFile;
    yylex();

    if(DEBUG_MODE) {
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(17) << "TOKEN" << left << setw(10) << "COUNT" << left << setw(10) << "LEXEME" << endl;
        cout << "--------------------------------------------------" << endl;

        int count = 0;
        map<string, string>::iterator it;
        for (it = lexemeMap.begin(); it != lexemeMap.end(); ++it) {
            
        string TOKEN = it->second;
        string LEXEME = it->first;
        count = lexemeCount[LEXEME];

        cout << left << setw(17) << TOKEN << left << setw(10) << count << left << setw(10) << LEXEME << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }

    if(error_flag == 1)
        cout << "[LEXER ERROR]: Illegal character " << error_char << " occurred at line: " << yylineno << endl;
    else if(error_flag == 2)
        cout << "[LEXER ERROR]: Incorrect Indentation occurred at line: " << yylineno << endl;
    else if(error_flag == 3)
        cout << "[LEXER ERROR]: Incorrect Brackets occurred at line: " << yylineno << endl;
    
    fclose(inputFile);    
    return 0;
} */
