%{
    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <string>
    #include <map>
    #include <stack>
    #include <set>
    #include <vector>
    #include <cstdlib>

    using namespace std;

    /* these maps store lexemes and their counts, only for testing purposes */
    std::map<std::string,std::string> lexemeMap;
    std::map<std::string,int> lexemeCount;

    /* variables required for raising lexical errors */
    int error_flag = 0;
    std::string error_char;

    bool DEBUG_MODE = true;

    /* these stacks store opening braces, required for maintaining state in case of nested brackets */
    std::stack<char> braces_stack;

    /* this stack maintains the indentation level for each statement */
    std::stack<int> indentation_stack;                        

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

    /* function to check if input file is of correct extension or not */
    bool isPyFile(const char* filename) {
        const char* extension = ".py";
        size_t len = strlen(filename);
    return (len > strlen(extension) && strcmp(filename + len - strlen(extension), extension) == 0);
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

/* Indentation is determined by the number of non-whitespace characters at the beginning of a line. Also, the line should  */
INDENTATION ^{BLANKS}*
/* An explicit line joiner is a backlash('\') followed immediately by an End-of-Line('\n') */
LINE_JOINER \\\n       
/* Newline marks end of logical line */ 
NEWLINE \n
/* Operators as given in lexical specifications */
OPERATOR -|\+|\*\*|\*|\/\/|\/|%|@|<<|>>|&|(\|)|\^|~|:=|<|>|<=|>=|==|!=
/* Delimiters as given in lexical specifications  */
DELIMITER [\(\)\[\]{}]|[,:\.;@=]|>>=|<<=|\*\*=|->|\+=|-=|\*=|\/=|\/\/=|%=|@=|&=|(\|=)|\^=
/* Few delimiters also serve as augmented assignment operators */
AUGASSIGN >>=|<<=|\*\*=|\/\/=|\+=|-=|\*=|\/=|=|%=|@=|&=
/* Few illegal characters given in the specification */
ILLEGALCHARS [\?\$`]
/* A comment starts with a hash symbol ('#') and covers everything till the EOL. It does not adhere to explicit line joining and can start at any point */
COMMENT {BLANKS}*#.*\n
/* Blanks here include whitespace, tabs, formfeed character, and carriage return character */
BLANKS [ \t\r\f]
/* Opening braces include (,[,{ */
OPENING_BRACES [\[\({]
/* Closing braces include ),],} */
CLOSING_BRACES [\]\)\}]
%%

<INSIDE_BRACKET>{CLOSING_BRACES}            {
    if(DEBUG_MODE) {
        printf("[LEXER]: %c %c popped off\n",braces_stack.top(),yytext[0]);
    }
    if(!isBracketCorrect(braces_stack.top(),yytext[0])) {
        error_flag = 3;
        return 0;
    }
    else {
        braces_stack.pop();
        if(braces_stack.empty()) BEGIN(INITIAL);
    }
}
<INSIDE_BRACKET>{OPENING_BRACES}                    { lexemeMap[yytext] = "DELIMITER"; lexemeCount[yytext]++; braces_stack.push(yytext[0]); }                                            
<INSIDE_BRACKET>{COMMENT}|{NEWLINE}|{BLANKS}        { /* do nothing */}
<INSIDE_BRACKET>{OPERATOR}                          { lexemeMap[yytext] = "OPERATOR"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{DELIMITER}                         { lexemeMap[yytext] = "DELIMITER"; lexemeCount[yytext]++; }
<INSIDE_BRACKET>{ILLEGALCHARS}                      { error_flag = 1; error_char = yytext; return 0; }
<INSIDE_BRACKET>.                                   { /* do nothing */}

<INDENTATION_TEST>{INDENTATION}               {
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
<INDENTATION_TEST>{NEWLINE}|{COMMENT}     { /* do nothing */}
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

<<EOF>> {
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

{OPENING_BRACES}    { 
    lexemeMap[yytext] = "DELIMITER"; 
    lexemeCount[yytext]++; 
    braces_stack.push(yytext[0]); 
    /* upon encountering a bracket, we go into INSIDE_BRACKET state where we do not test for indentation */ 
    BEGIN(INSIDE_BRACKET); 
}

{COMMENT}           {
    /* comments in themselves are not useful but since they end with a newline, they are used to prompt the indentation testing mode */
    BEGIN(INDENTATION_TEST);
    /* we also might have to return a newline token from here */
    /* return NEWLINE */
}

{INDENTATION}       {
    /* If we encounter indentation at first line itself, return error. */
    if(yylineno == 1)   {error_flag = 2; return 0; }
    /* otherwise if we encounter blank space in INITIAL mode, it is probably due to explicit line joining and should be ignored */
}

{LINE_JOINER}       {
    lexemeMap[yytext] = "LINE_JOINER";
    lexemeCount[yytext]++;
    /* ignore this since we are continuing within the same logical line */
}

{NEWLINE}           {
    /* this marks the end of a logical line */
    /* We have to probably return a NEWLINE token from here 
        return NEWLINE;    
    */
    /* After encountering a newline, we will go into indentation testing mode */
    BEGIN(INDENTATION_TEST);
}

{OPERATOR}          {
    lexemeMap[yytext] = "OPERATOR";
    lexemeCount[yytext]++;
    /* return OPERATOR */
}

{DELIMITER}       { 
    lexemeMap[yytext] = "DELIMITER";
    lexemeCount[yytext]++;
}

{ILLEGALCHARS}      {
    /* the appearance of these characters outside of string literals should lead to unconditional errors */
    error_flag = 1;
    error_char = yytext;
    return 0;
}

{BLANKS}            {
    /* ignore blank spaces */
}

.                   { 
    /* ignore as of now */
}

%%

int main(int argc, char** argv) {
    if (argc != 2 || !isPyFile(argv[1])) {
        std::cerr << "Usage: " << argv[0] << " <filename.py>" << endl;
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        std::cerr << "Error opening input file: " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    
    indentation_stack.push(0);
    yyin = inputFile;
    yylex();

    if(DEBUG_MODE) {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << std::left << std::setw(17) << "TOKEN" << std::left << std::setw(10) << "COUNT" << std::left << std::setw(10) << "LEXEME" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;

        int count = 0;
        std::map<std::string, std::string>::iterator it;
        for (it = lexemeMap.begin(); it != lexemeMap.end(); ++it) {
            
        string TOKEN = it->second;
        string LEXEME = it->first;
        count = lexemeCount[LEXEME];

        std::cout << std::left << std::setw(17) << TOKEN << std::left << std::setw(10) << count << std::left << std::setw(10) << LEXEME << std::endl;
        }
        std::cout << "--------------------------------------------------" << std::endl;
    }

    if(error_flag == 1)
        std::cout << "[LEXER ERROR]: Illegal character " << error_char << " occurred at line: " << yylineno << std::endl;
    else if(error_flag == 2)
        std::cout << "[LEXER ERROR]: Incorrect Indentation occurred at line: " << yylineno << std::endl;
    else if(error_flag == 3)
        std::cout << "[LEXER ERROR]: Incorrect Brackets occurred at line: " << yylineno << std::endl;
    
    fclose(inputFile);    
    return 0;
}
