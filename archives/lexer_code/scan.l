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
line_joiner \\\n
newline \n
operator -|\+|\*\*|\*|\/\/|\/|%|@|<<|>>|&|(\|)|\^|~|:=|<|>|<=|>=|==|!=
delimiter [\(\)\[\]{}]|[,:\.;@=]|>>=|<<=|\*\*=|->|\+=|-=|\*=|\/=|\/\/=|%=|@=|&=|(\|=)|\^=
augassign >>=|<<=|\*\*=|\/\/=|\+=|-=|\*=|\/=|=|%=|@=|&=
illegalchars [\?\$`]
comment {blanks}*#.*\n
blanks [ \t\r\f]
opening_braces [\[\({]
closing_braces [\]\)\}]
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
keywords         (False|await|else|import|pass|None|break|except|in|raise|True|class|finally|is|return|and|continue|for|lambda|try|as|def|from|nonlocal|while|assert|del|global|not|with|async|elif|if|or|yield)
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

<INSIDE_BRACKET>{closing_braces}            {
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
}

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

<INSIDE_BRACKET>{type}                              { lexemeMap[yytext] = "TYPE_SPECIFER"; lexemeCount[yytext]++; }    
<INSIDE_BRACKET>{keywords}                          { lexemeMap[yytext] = "KEYWORDS"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{rid_system}                        { lexemeMap[yytext] = "RID"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{rid_classpvt}                      { lexemeMap[yytext] = "RID"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{rid__}                             { lexemeMap[yytext] = "RID"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{id}                                { lexemeMap[yytext] = "NAME"; lexemeCount[yytext]++; }

<INSIDE_BRACKET>{opening_braces}                    { lexemeMap[yytext] = "DELIMITER"; lexemeCount[yytext]++; braces_stack.push(yytext[0]); }                                            
<INSIDE_BRACKET>{operator}                          { lexemeMap[yytext] = "OPERATOR"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{delimiter}                         { lexemeMap[yytext] = "DELIMITER"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{illegalchars}                      { error_flag = 1; error_char = yytext; return 0; }
<INSIDE_BRACKET>{comment}|{newline}|{blanks}        { /* do nothing */}
<INSIDE_BRACKET>{ellipses_literal}                  { lexemeMap[yytext] = "ELLIPSES_LITERAL"; lexemeCount[yytext]++; }



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

<INDENTATION_TEST>{newline}|{comment}     { /* do nothing */}
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
}

{opening_braces}    { 
    lexemeMap[yytext] = "DELIMITER"; 
    lexemeCount[yytext]++; 
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation */ 
    BEGIN(INSIDE_BRACKET); 
}

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
}

{operator}          {
    lexemeMap[yytext] = "OPERATOR";
    lexemeCount[yytext]++;
    /* return OPERATOR */
}
{ellipses_literal}                  { 
    lexemeMap[yytext] = "ELLIPSES_LITERAL"; 
    lexemeCount[yytext]++; 
}

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
    return 0;
}

.                   { 
    /* ignore as of now */
}

%%


int main(int argc, char** argv) {
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
}
