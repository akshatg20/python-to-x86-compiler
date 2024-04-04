%{
    #include <iostream>
    #include <map>
    #include <set>
    #include <stack>
    #include <vector>
    #include <queue>
    #include <string>
    #include <algorithm>
    #include <iomanip>
    using namespace std;
    
    /* These maps store lexemes and their counts, only for testing purposes */
    map<string,string> lexemeMap;
    map<string,int> lexemeCount;
    
    // Variable to check debug outputs
    bool DEBUG_MODE = true;
    int error_flag = 1;
    string error_char;
    
    /* Function to check if input file is of correct extension or not */
    bool isPyFile(const char* filename) {
        const char* extension = ".py";
        size_t len = strlen(filename);
        return (len > strlen(extension) && strcmp(filename + len - strlen(extension), extension) == 0);
    }
%}

%option noyywrap
%option yylineno

%x INDENTATION_TEST
%x INSIDE_BRACKET

/*Definitions for the scanning and tokenization of literals in python*/
/*Literals include constant terms in a code. These are constants of some built-in types*/

/*Definitions for string literals*/
stringprefix    r|u|R|U|f|F|fr|Fr|fR|FR|rf|rF|Rf|RF
stringescapeseq \\[.\n]
shortstringchar [^\\\"\'\n]
shortstringitem ({shortstringchar}|{stringescapeseq})
longstringchar  [^\\]
longstringitem  ({longstringchar}|{stringescapeseq})
shortstring     (\'({shortstringitem}*)\')|(\"({shortstringitem}*)\")
longstring      (\'\'\'({longstringitem}*)\'\'\')|(\"\"\"({longstringitem}*)\"\"\")
stringliteral   ({stringprefix}?)({shortstring}|{longstring})

/*Definitions for byte literals*/
bytesprefix     b|B|br|Br|bR|BR|rb|rB|Rb|RB
bytesescapeseq  \\[.\\n]
shortbyteschar  [^\\\"\'\n]
shortbytesitem  {shortbyteschar}|{bytesescapeseq}
longbyteschar   [^\\]
longbytesitem   {longbyteschar}|{bytesescapeseq}
shortbytes      (\'({shortbytesitem}*)\')|(\"({shortbytesitem}*)\")
longbytes       (\'\'\'({longbytesitem}*)\'\'\')|(\"\"\"({longbytesitem}*)\"\"\")
bytesliteral    {bytesprefix}({shortbytes}|{longbytes})

/*Definitions for integer literals*/
nonzerodigit [1-9]
digit        [0-9]
bindigit     [01]
octdigit     [0-7]
hexdigit     {digit}|[a-fA-F]
decinteger   ({nonzerodigit}([_]|{digit})*)|(0([_]0)*)
bininteger   0[bB]([_]|{bindigit})+
octinteger   0[oO]([_]|{octdigit})+
hexinteger   0[xX]([_]|{hexdigit})+
integer      {decinteger}|{bininteger}|{octinteger}|{hexinteger}

/*Definitions for floating point literals*/
digitpart     {digit}([_]|{digit})*
fraction      .{digitpart}
exponent      [eE][+-]{digitpart}
pointfloat    ({digitpart}{fraction})|({digitpart}.)
exponentfloat ({digitpart}|{pointfloat}){exponent}
floatnumber   {pointfloat}|{exponentfloat}

/*Definitions for imaginary number literals*/
imagnumber    ({floatnumber}|{digitpart})[jJ]

%%

<INDENTATION_TEST>{stringliteral}         {
    // Code to handle the presence of a string-literal in the program
    lexemeMap[yytext] = "string_literal";
    lexemeCount[yytext]++;
}

<INDENTATION_TEST>{bytesliteral}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "byte_literal";
    lexemeCount[yytext]++;
}

<INDENTATION_TEST>{integer}         {
    // Code to handle the presence of a string-literal in the program
    lexemeMap[yytext] = "integer_literal";
    lexemeCount[yytext]++;
}

<INDENTATION_TEST>{floatnumber}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "floating_point_literal";
    lexemeCount[yytext]++;
}

<INDENTATION_TEST>{imagnumber}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "imaginary_number_literal";
    lexemeCount[yytext]++;
}

<INDENTATION_TEST>.                       {
    // Code to handle other tokens in the program
    // Ignored for now
}

<INSIDE_BRACKET>{stringliteral}         {
    // Code to handle the presence of a string-literal in the program
    lexemeMap[yytext] = "string_literal";
    lexemeCount[yytext]++;
}

<INSIDE_BRACKET>{bytesliteral}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "byte_literal";
    lexemeCount[yytext]++;
}

<INSIDE_BRACKET>{integer}         {
    // Code to handle the presence of a string-literal in the program
    lexemeMap[yytext] = "integer_literal";
    lexemeCount[yytext]++;
}

<INSIDE_BRACKET>{floatnumber}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "floating_point_literal";
    lexemeCount[yytext]++;
}

<INSIDE_BRACKET>{imagnumber}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "imaginary_number_literal";
    lexemeCount[yytext]++;
}

<INSIDE_BRACKET>.                       {
    // Code to handle other tokens in the program
    // Ignored for now
}

{stringliteral}         {
    // Code to handle the presence of a string-literal in the program
    lexemeMap[yytext] = "string_literal";
    lexemeCount[yytext]++;
}

{bytesliteral}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "byte_literal";
    lexemeCount[yytext]++;
}

{integer}         {
    // Code to handle the presence of a string-literal in the program
    lexemeMap[yytext] = "integer_literal";
    lexemeCount[yytext]++;
}

{floatnumber}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "floating_point_literal";
    lexemeCount[yytext]++;
}

{imagnumber}           {
    // Code to handle the presence of a byte-literal in the program
    lexemeMap[yytext] = "imaginary_number_literal";
    lexemeCount[yytext]++;
}

.                       {
    // Code to handle other tokens in the program
    // Ignored for now
}

%%

int main(int argc, char** argv) {
    if (argc != 2 || !isPyFile(argv[1])) {
        cerr << "Usage: " << argv[0] << " <filename.py>" << endl;
        return -1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return -1;
    }
    
    yyin = inputFile;
    yylex();

    if(DEBUG_MODE == true) {
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(30) << "TOKEN" << left << setw(30) << "COUNT" << left << setw(30) << "LEXEME" << endl;
        cout << "--------------------------------------------------" << endl;

        int count = 0;
        map<string, string>::iterator it;
        for (it = lexemeMap.begin(); it != lexemeMap.end(); ++it) {
            
            string TOKEN = it->second;
            string LEXEME = it->first;
            count = lexemeCount[LEXEME];

            cout << left << setw(30) << TOKEN << left << setw(30) << count << left << setw(30) << LEXEME << endl;
        }
        cout << "--------------------------------------------------" << endl;
    }

    if(error_flag == 1)
        cout << "[LEXER]: Illegal character " << error_char << " occurred at line: " << yylineno << endl;
    else if(error_flag == 2)
        cout << "[LEXER]: Incorrect Indentation occurred at line: " << yylineno << endl;
    else if(error_flag == 3)
        cout << "[LEXER]: Incorrect Brackets occurred at line: " << yylineno << endl;
    
    fclose(inputFile);    
    return 0;
}
