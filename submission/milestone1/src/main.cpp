#include <iostream>
#include <string.h>
#include <iomanip>
#include <map>
#include <cstdio>
using namespace std;

#ifdef __has_include
#  if __has_include("header.h")
    #include "parse.tab.h"
#  endif
#endif

// External variables, functions and data structures for use here.
extern int yyparse();
extern int init_lexer(FILE*);
extern int LEXER_DEBUG_OUTSIDE_VERBOSE;
extern int LEXER_DEBUG_INSIDE_VERBOSE;
extern int PARSER_DEBUG_OUTSIDE_VERBOSE;
extern int PARSER_DEBUG_INSIDE_VERBOSE;
extern int AST_DEBUG_OUTSIDE_VERBOSE;
extern int AST_DEBUG_INSIDE_VERBOSE;
extern map<string,int> lexemeCount;
extern map<string,string> lexemeMap;

// Global debug control variables.
int DEBUG_INSIDE_VERBOSE = 0;
int DEBUG_OUTSIDE_VERBOSE = 0;

// Compiler configuration variables
char *inputfile_path,*outputfile_path,*errorfile_path,*astfile_path,*dotfile_path;
int DOT_GENERATION = 0,AST_GENERATION = 0;

// Function to check the input program file extension
bool isPyFile(const char* filename) {
    const char* extension = ".py";
    size_t len = strlen(filename);
    return (len > strlen(extension) && strcmp(filename + len - strlen(extension), extension) == 0);
}

// Help flag implementation
void printhelp() {
    cout << "Usage: ./cs335 [options]\n"
         << "Options:\n"
         << "  --help     Display this information.\n"
         << "  --input    Add the path of the input file. By default it is the standard input.\n"
         << "             The next argument after --input flag should correspond to the location where the input file is present.\n"
         << "  --output   Add the path of the output file. By default compiler output is displayed at the standard output.\n"
         << "             The next argument after --output flag should correspond to the location where the output is to be stored.\n"
         << "  --error    Add the path of the error file. By default it is the standard error.\n"
         << "             The next argument after --error flag should correspond to the location where the error is redirected.\n"
         << "  --dot      Configure the compiler to output the DOT script corresponding to input program in a .dot file.\n"
         << "             The next argument after --dot flag should correspond to the location where the dot file is to be stored.\n"
         << "  --ast      Configure the compiler to output Abstract Syntax Tree of the input program in a PDF.\n"
         << "             The next argument after --ast flag should correspond to the location where the ast file is to be stored.\n"
         << "  --verbose  Get detailed compilation log and debug outputs.\n"
         << "  --full     Display the full debug output.\n"
         << "";
    
    return;
}

// Command line parsing utility for the compiler.
// Returns 0 in case of normal return however, returns 1 when the program needs to exit after parsing immediately.
int command_parse(int argc, char* argv[]) {
    // Set the FILE streams for input, output and error.
    inputfile_path = (char*) malloc(1000*sizeof(char));
    outputfile_path = (char*) malloc(1000*sizeof(char));
    errorfile_path = (char*) malloc(1000*sizeof(char));
    astfile_path = (char*) malloc(1000*sizeof(char));
    dotfile_path = (char*) malloc(1000*sizeof(char));
    FILE *inputfile,*outputfile,*errorfile;
    inputfile = stdin;
    outputfile = stdout;
    errorfile = stderr;
    
    // Parse the command line arguments from the CLI
    for(int i=1 ; i<argc ; i++) {
        if(!strcmp(argv[i],"-i") || !strcmp(argv[i],"-I") || !strcmp(argv[i],"--input")) {
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing input file after --input flag");
                return 1;
            }
            inputfile_path = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-o") || !strcmp(argv[i],"-O") || !strcmp(argv[i],"--output")) {
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --output flag");
                return 1;
            }
            outputfile_path = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-e") || !strcmp(argv[i],"-E") || !strcmp(argv[i],"--error")) {
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing error file after --error flag");
                return 1;
            }
            errorfile_path = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-v") || !strcmp(argv[i],"-V") || !strcmp(argv[i],"--verbose")) {
            LEXER_DEBUG_INSIDE_VERBOSE = 1;
            PARSER_DEBUG_INSIDE_VERBOSE = 1;
            DEBUG_INSIDE_VERBOSE = 1;
            AST_DEBUG_INSIDE_VERBOSE = 1;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-f") || !strcmp(argv[i],"-F") || !strcmp(argv[i],"--full")) {
            LEXER_DEBUG_OUTSIDE_VERBOSE = 1;
            PARSER_DEBUG_OUTSIDE_VERBOSE = 1;
            LEXER_DEBUG_INSIDE_VERBOSE = 1;
            PARSER_DEBUG_INSIDE_VERBOSE = 1;
            DEBUG_INSIDE_VERBOSE = 1;
            DEBUG_OUTSIDE_VERBOSE = 1;
            AST_DEBUG_OUTSIDE_VERBOSE = 1;
            AST_DEBUG_INSIDE_VERBOSE = 1;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-h") || !strcmp(argv[i],"-H") || !strcmp(argv[i],"--help")) {
            if(argc > 2) printf("[COMPILER]: Input options or arguments other than --help have been ignored.\n");
            printhelp();
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
            return 1;
        }
        else if(!strcmp(argv[i],"-a") || !strcmp(argv[i],"-A") || !strcmp(argv[i],"--ast")) {
            AST_GENERATION = 1;
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --ast flag");
                return 1;
            }
            astfile_path = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-d") || !strcmp(argv[i],"-D") || !strcmp(argv[i],"--dot")) {
            DOT_GENERATION = 1;
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --dot flag");
                return 1;
            }
            dotfile_path = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else {
            fprintf(stderr, "[COMPILER ERROR]: Unrecognised command line option %s\n", argv[i]);
            return 1;
        }
    }
    
    if(DEBUG_INSIDE_VERBOSE) {
        if(strlen(inputfile_path) > 0) cout << "[COMPILER]: Input File is " << inputfile_path <<"\n";
        else cout << "[COMPILER]: Input File is stdin\n";
        if(strlen(outputfile_path) > 0) cout << "[COMPILER]: Output File is " << outputfile_path <<"\n";
        else cout << "[COMPILER]: Output File is stdout\n";
        if(strlen(errorfile_path) > 0) cout << "[COMPILER]: Error File is " << errorfile_path <<"\n";
        else cout << "[COMPILER]: Error File is stderr\n";
        if(strlen(dotfile_path) > 0) cout << "[COMPILER]: Dot Script output file is " << dotfile_path <<"\n";
        else cout << "[COMPILER]: No DOT script output is to be generated\n";
        if(strlen(astfile_path) > 0) cout << "[COMPILER]: AST output file is " << astfile_path <<"\n";
        else cout << "[COMPILER]: No AST is to be generated\n";
    }
    
    // Setup the error file
    if(strlen(errorfile_path) > 0) {
        errorfile = fopen(errorfile_path, "a");
        if(!errorfile) {
            fprintf(stderr, "[COMPILER ERROR]: File %s not found\n", errorfile_path);
            return 1;
        }
        else if(freopen(errorfile_path, "a", stderr) == NULL) {
            fprintf(stderr, "[COMPILER ERROR]: Unable to open error log file %s\n", errorfile_path);
            return 1;
        }
    }

    // Begin the lexer on the inputfile if the input file is not the standard input.
    if(strlen(inputfile_path) > 0) {
        inputfile = fopen(inputfile_path, "r");
        if(!inputfile) {
            fprintf(stderr, "[COMPILER ERROR]: File %s not found\n", inputfile_path);
            return 1;
        }
        else if(!isPyFile(inputfile_path)) {
            fprintf(stderr, "[COMPILER ERROR]: Given input file has wrong extension. Should be .py\n");
            return 1;
        }
    }
    init_lexer(inputfile);

    // Setup the output file
    if(strlen(outputfile_path) > 0) {
        outputfile = fopen(outputfile_path, "w");
        if(!outputfile) {
            fprintf(stderr, "[COMPILER ERROR]: File %s not found\n", outputfile_path);
            return 1;
        }
        else if(freopen(outputfile_path, "w", stdout) == NULL) {
            fprintf(stderr, "[COMPILER ERROR]: Unable to open output file %s\n", outputfile_path);
            return 1;
        }
    }

    // Return from the command line parser
    return 0;
}

int main(int argc, char* argv[]) {
    // Command parsing functionality is be called here
    int flag = command_parse(argc, argv);
    if(flag == 1) {
        // Program terminates here as a help flag was called or an error occured
        return 1;
    }

    // Call the main parser loop which drives the lexer as well internally.
    if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Entering the main parser loop" << "\n";
    flag = yyparse();
    if(flag != 0) {
        // Program terminates here as an error occured
        return 1;
    }

    // Table output of the Lexer tokens (which is a part of debug output outside verbose).
    // Used for debugging purposes while development.
    if(DEBUG_OUTSIDE_VERBOSE) {
        cout << "[COMPILER][COMPILER][COMPILER][COMPILER][COMPILER][COMPILER]" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << left << setw(17) << "TOKEN" << left << setw(10) << "COUNT" << left << setw(10) << "LEXEME" << endl;
        cout << "------------------------------------------------------------" << endl;
        int count = 0;
        map<string, string>::iterator it;
        for (it = lexemeMap.begin(); it != lexemeMap.end(); ++it) { 
            string TOKEN = it->second;
            string LEXEME = it->first;
            count = lexemeCount[LEXEME];
            cout << left << setw(17) << TOKEN << left << setw(10) << count << left << setw(10) << LEXEME << endl;
        }
        cout << "------------------------------------------------------------" << endl;
        cout << "[COMPILER][COMPILER][COMPILER][COMPILER][COMPILER][COMPILER]" << endl;
    }

    // Exit the compiler
    return 0;
}
