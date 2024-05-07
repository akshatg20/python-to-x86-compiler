#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <deque>
#include <string.h>
#include <string>
#include <iomanip>
#include <map>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <unordered_map>
using namespace std;

#ifdef __has_include
#  if __has_include("header.h")
    #include "parse.tab.h"
#  endif
#endif

#ifndef AST_HPP
#include "ast.hpp"
#endif
#ifndef UTILS_HPP
#include "utils.hpp"
#endif
#ifndef TYPES_HPP
#include "types.hpp"
#endif
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
#ifndef GEN_3AC_HPP
#include "gen_3ac.hpp"
#endif
#ifndef GEN_X86_HPP
#include "gen_x86.hpp"
#endif

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF COMPILER *********************************/

// Write any assumptions that you take in the comment below
/*
----
*/

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF COMPILER *********************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.
extern int yyparse();
extern int init_lexer(FILE*);
extern int LEXER_DEBUG_OUTSIDE_VERBOSE;
extern int LEXER_DEBUG_INSIDE_VERBOSE;
extern int PARSER_DEBUG_OUTSIDE_VERBOSE;
extern int PARSER_DEBUG_INSIDE_VERBOSE;
extern int AST_DEBUG_OUTSIDE_VERBOSE;
extern int AST_DEBUG_INSIDE_VERBOSE;
extern int SYMBOL_TABLE_DEBUG_INSIDE_VERBOSE;
extern int SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE;
extern int DEBUG_X86_INSIDE_VERBOSE;
extern int DEBUG_X86_OUTSIDE_VERBOSE;
extern bool isAST;
extern map<string,int> lexemeCount;
extern map<string,string> lexemeMap;
extern ASTNode* root;
extern SymbolTable* currTable;
extern SymbolTable* globalTable;
extern unordered_map<string, SymbolTable*> labelMap;

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

// All classes and structures that you want to declare should go here.

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.

// Variables related directly to the compiler.
// Global debug control variables.
int DEBUG_INSIDE_VERBOSE = 0;
int DEBUG_OUTSIDE_VERBOSE = 0;
int DEBUG_3AC_INSIDE_VERBOSE;
int DEBUG_3AC_OUTSIDE_VERBOSE;
int DEBUG_3AC = 0;
int DEBUG_SYMBOL_TABLE = 0;
int DEBUG_X86 = 0;
int MILESTONE2_DEMO = 1;
// Compiler configuration variables
char *inputfile_path,*outputfile_path,*errorfile_path,*astfile_path,*dotfile_path,
        *parsefile_path,*assembly_outputfile_path,*path_3ac,*path_sym;
int DOT_GENERATION = 0, AST_GENERATION = 0, PARSE_TREE_GENERATION = 0, GENERATION_3AC = 0, SYMBOL_TABLE_PRINT = 0;
int COMPILER_DEBUG = 0;
int current_scope = 0;                      // maintains the current scope while parsing, initialized to zero
RegisterAllocation* regAlloc;


/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

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
         << "  --output   Add the path of the output file. By default compiler output is stored in a .s file in the same directory.\n"
         << "             The next argument after --output flag should correspond to the location where the output is to be stored.\n"
         << "  --error    Add the path of the error file. By default it is the standard error.\n"
         << "             The next argument after --error flag should correspond to the location where the error is redirected.\n"
         << "  --debug    Add the path for debug output. By default debug output is displayed at the standard output.\n"
         << "             The next argument after --debug flag should correspond to the location where the debug output is to be stored.\n"
         << "  --dot      Configure the compiler to output the DOT script corresponding to input program in a .dot file.\n"
         << "             The next argument after --dot flag should correspond to the location where the dot file is to be stored.\n"
         << "  --ast      Configure the compiler to output Abstract Syntax Tree of the input program in a PDF.\n"
         << "             The next argument after --ast flag should correspond to the location where the ast file is to be stored.\n"
         << "  --parse    Configure the compiler to output Parse Tree of the input program in a PDF.\n"
         << "             The next argument after --parse flag should correspond to the location where the parse tree file is to be stored.\n"
         << "  --3ac      Get the output 3AC IR of the source program. When this flag is set the flags --ast and --parse will be ignored.\n"
         << "             The next argument after --3ac flag should correspond to the location where the 3AC IR text file is to be stored.\n"
         << "  --symbol   Get details of information stored in symbol table in form of .csv file outputs.\n"
         << "             The next argument after --symbol flag should correspond to the directory where the symbol table is to be dumped.\n"
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
    assembly_outputfile_path = (char*) malloc(1000*sizeof(char));
    errorfile_path = (char*) malloc(1000*sizeof(char));
    astfile_path = (char*) malloc(1000*sizeof(char));
    parsefile_path = (char*) malloc(1000*sizeof(char));
    dotfile_path = (char*) malloc(1000*sizeof(char));
    path_3ac = (char*) malloc(1000*sizeof(char));
    path_sym = (char*) malloc(1000*sizeof(char));
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
        else if(!strcmp(argv[i],"-de") || !strcmp(argv[i],"-DE") || !strcmp(argv[i],"--debug")) {
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --debug flag");
                return 1;
            }
            outputfile_path = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-o") || !strcmp(argv[i],"-O") || !strcmp(argv[i],"--output")) {
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --output flag");
                return 1;
            }
            assembly_outputfile_path = argv[i+1]; i++;
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
            SYMBOL_TABLE_DEBUG_INSIDE_VERBOSE = 1;
            DEBUG_3AC_INSIDE_VERBOSE = 1;
            DEBUG_X86_INSIDE_VERBOSE = 1;
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
            SYMBOL_TABLE_DEBUG_INSIDE_VERBOSE = 1;
            SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE = 1;
            DEBUG_3AC_INSIDE_VERBOSE = 1;
            DEBUG_3AC_OUTSIDE_VERBOSE = 1;
            DEBUG_X86_INSIDE_VERBOSE = 1;
            DEBUG_X86_OUTSIDE_VERBOSE = 1;
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
            astfile_path = argv[i+1]; i++; isAST = true;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-p") || !strcmp(argv[i],"-P") || !strcmp(argv[i],"--parse")) {
            PARSE_TREE_GENERATION = 1;
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --parse flag");
                return 1;
            }
            parsefile_path = argv[i+1]; i++;
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
        else if(!strcmp(argv[i],"-3") || !strcmp(argv[i],"--3ac")) {
            GENERATION_3AC = 1;
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --3ac flag");
                return 1;
            }
            path_3ac = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else if(!strcmp(argv[i],"-s") || !strcmp(argv[i],"-S") || !strcmp(argv[i],"--symbol")) {
            SYMBOL_TABLE_PRINT = 1;
            if(i == argc-1) {
                fprintf(stderr, "[COMPILER ERROR]: Missing output file after --symbol flag");
                return 1;
            }
            path_sym = argv[i+1]; i++;
            if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Identified " << argv[i] << " option\n";
        }
        else {
            fprintf(stderr, "[COMPILER ERROR]: Unrecognised %d-th command line option %s\n", i, argv[i]);
            return 1;
        }
    }
    
    if(DEBUG_INSIDE_VERBOSE) {
        if(strlen(inputfile_path) > 0) cout << "[COMPILER]: Input File is " << inputfile_path <<"\n";
        else cout << "[COMPILER]: Input File is stdin\n";
        if(strlen(outputfile_path) > 0) cout << "[COMPILER]: Debug Output File is " << outputfile_path <<"\n";
        else cout << "[COMPILER]: Debug Output File is stdout\n";
        if(strlen(errorfile_path) > 0) cout << "[COMPILER]: Error File is " << errorfile_path <<"\n";
        else cout << "[COMPILER]: Error File is stderr\n";
        cout << "[COMPILER]: Assembly Output File is " << assembly_outputfile_path <<"\n";
        if(strlen(dotfile_path) > 0) cout << "[COMPILER]: Dot Script output file is " << dotfile_path <<"\n";
        else cout << "[COMPILER]: No DOT script output is to be generated\n";
        if(strlen(path_3ac) == 0 && strlen(path_sym) == 0) {
            if(strlen(astfile_path) > 0 && strlen(parsefile_path) > 0) {
                cout << "[COMPILER]: AST output file is " << astfile_path <<"\n";
                cout << "[COMPILER]: No Parse Tree can be generated because --ast flag was given\n";
                PARSE_TREE_GENERATION = 0;
            }
            else if(strlen(astfile_path) > 0) {
                cout << "[COMPILER]: AST output file is " << astfile_path <<"\n";
                cout << "[COMPILER]: No Parse Tree is to be generated\n";
            }
            else if(strlen(parsefile_path) > 0) {
                cout << "[COMPILER]: Parse Tree output file is " << parsefile_path <<"\n";
                cout << "[COMPILER]: No AST is to be generated\n";
                isAST = false;
            }
            else {
                cout << "[COMPILER]: No Parse Tree is to be generated\n";
                cout << "[COMPILER]: No AST is to be generated\n";
            }
            cout << "[COMPILER]: No Symbol Table dump file is to be generated\n";
            cout << "[COMPILER]: No 3AC IR output file is to be generated\n";
        }
        else {
            if(strlen(astfile_path) > 0 && strlen(parsefile_path) > 0) {
                cout << "[COMPILER]: Parse Tree output file is " << parsefile_path <<"\n";
                if(strlen(path_3ac) > 0) cout << "[COMPILER]: No AST can be generated because --3ac flag was given\n";
                else cout << "[COMPILER]: No AST can be generated because --symbol flag was given\n";
                isAST = false;
                AST_GENERATION = 0;
            }
            else if(strlen(astfile_path) > 0) {
                if(strlen(path_3ac) > 0) cout << "[COMPILER]: No AST can be generated because --3ac flag was given\n";
                else cout << "[COMPILER]: No AST can be generated because --symbol flag was given\n";
                cout << "[COMPILER]: No Parse Tree is to be generated\n";
                isAST = false;
                AST_GENERATION = 0;
            }
            else if(strlen(parsefile_path) > 0) {
                cout << "[COMPILER]: Parse Tree output file is " << parsefile_path <<"\n";
                cout << "[COMPILER]: No AST is to be generated\n";
            }
            else {
                cout << "[COMPILER]: No Parse Tree is to be generated\n";
                cout << "[COMPILER]: No AST is to be generated\n";
            }
            if(strlen(path_3ac) > 0) cout << "[COMPILER]: 3AC IR output file is " << path_3ac <<"\n";
            else cout << "[COMPILER]: No 3AC IR output file is to be generated\n";
            if(strlen(path_sym) > 0) cout << "[COMPILER]: Symbol Table dump file is " << path_sym <<"\n";
            else cout << "[COMPILER]: No Symbol Table dump file is to be generated\n";
        }
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
    if(strlen(inputfile_path) > 0) 
    {
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
    
    // A sample test case for debugging the complete source code
    if(COMPILER_DEBUG == 1) {
        argc = 7;
        argv[1] = strdup("--input");
        argv[2] = strdup("../testcases/public1.py");
        argv[3] = strdup("--3ac");
        argv[4] = strdup("./output/debug3ac/public1.pdf");
        argv[5] = strdup("--parse");
        argv[6] = strdup("b.pdf");
    }
    // cout << "argv: " << argv[2] << "\n";
    
    /***************************************** COMMAND LINE UTILITY *******************************************/
    
    // COMMAND LINE SETTINGS PHASE
    // Command parsing functionality is be called here. This will set all flags
    // for the overall compilation toolchain.
    int flag = command_parse(argc, argv);
    if(flag == 1) {
        // Program terminates here as a help flag was called or an error occured during compilation.
        return 1;
    }
    // printf("%s\n", assembly_outputfile_path);


    if(DEBUG_X86) {

        // cout << "start\n";

        const char* file_path_3ac = "../testcases/x86_testcases/x86_output/test4/test4.txt";
        const char* output_x86_path = "../testcases/x86_testcases/x86_output/test4/test4_akshat.s";

        FILE* output_x86;
        output_x86 = fopen(output_x86_path, "w");

        // cout << "file opened\n";

        if(!output_x86) {
            fprintf(stderr, "[COMPILER ERROR]: File %s not found\n", output_x86_path);
            return 1;
        }

        string code_3ac = readFromFile(file_path_3ac);

        // cout << "code read from file\n";

        regAlloc = new RegisterAllocation();

        // cout << "reg allocated\n";

        int flag = generate_x86(code_3ac,output_x86);

        if(flag < 0) {
            printf("[x86 GENERATION ERROR]: Error in x86_64 generation\n");
            return 1;
        }
        return 0;
    }
    // printf("%s\n", assembly_outputfile_path);

    /***************************************** COMMAND LINE UTILITY ENDS **************************************/

    /***************************************** FRONTEND OF COMPILER *******************************************/

    // PARSING PHASE
    // Call the main parser loop which drives the lexer as well internally.
    // The symbol table is created here itself and semantic checking is done alongwith syntax checking.
    // A visualisation of the parsing is created in form of a abstract syntax tree of the program.
    // printf("Just before entering parser %s\n", assembly_outputfile_path);
    if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Entering the main parser loop" << "\n";
    // printf("Here just above parser %s\n", assembly_outputfile_path);
    flag = yyparse();
    // printf("%s\n", assembly_outputfile_path);
    if(flag != 0) {
        // Program terminates here as an error occured during parsing.
        return 1;
    }

    // Table output of the Lexer tokens (which is a part of debug output outside verbose).
    // Used for debugging purposes while development of frontend of compiler.
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
    // cout << isAST << "\n";

    // If the AST flag is set then the compiler would not move ahead this
    if(isAST == true) return 0;
    // printf("%s\n", assembly_outputfile_path);

    // Debug for symbol table
    if(DEBUG_SYMBOL_TABLE == 1) {
        int flag = 0;
        TypeExpression* attr1 = type_int();
        TypeExpression* attr2 = type_bool();

        deque<TypeExpression*> fields;
        fields.push_back(attr1);
        fields.push_back(attr2);

        TypeExpression* T = type_record(fields,1,deque<TypeExpression*>());

        add("DummyClass","CLASS",T,1,0,&flag);

        incr_scope(1,"other");

        T = type_int();
        add("x","INTEGER",T,2,0,&flag);

        decr_scope();

        T = type_float();
        add("y","FLOATING-POINT",T,3,0,&flag);

        // Dump the symbol table as per the requirements of the given compiler flags
        if(SYMBOL_TABLE_PRINT == 1) {
            string command = "mkdir -p " + string(path_sym);
            int result = system(const_cast<char*>(command.c_str())); // Execute the command
            if(result != 0) { // Check if the command executed successfully
                fprintf(stderr, "[COMPILER ERROR]: Error in creating folder for symbol table.\n");
                return 1;
            }
            
            // Call the function to dump all of the symbol table in the given file
            dumpAllSTs(path_sym, currTable);
        }

        return 0;
    }

    if(DEBUG_3AC == 0) {
        // cout << "hello" << "\n";
        
        // TOP TO DOWN PASS SEMANTIC ANALYSIS PHASE
        // Semantic Analysis and Symbol Table construction is done here
        if(DEBUG_3AC_OUTSIDE_VERBOSE) cout << "[COMPILER]: ENTERING INTO SEMANTIC ANALYSIS" << "\n";
        flag = semantic_analysis();
        if(DEBUG_3AC_OUTSIDE_VERBOSE) cout << "[COMPILER]: RETURNED FROM SEMANTIC ANALYSIS" << "\n";
        if(flag < 0) {
            // Some kind of error occured during semantic analysis which will be caught by the function.
            printf("[SEMANTIC ANALYSIS]: Error in semantic analysis of the program.\n");
            return 1;
        }

        if(MILESTONE2_DEMO == 0) {
            // Compute offsets for the Symbol Table entries
            if(DEBUG_3AC_OUTSIDE_VERBOSE) cout << "[COMPILER]: GLOBAL OFFSETS COMPUTATION STARTED" << "\n";
            flag = compute_offsets(globalTable, 0);
            if(flag < 0) {
                // Some kind of error occured during computation of offsets in the Symbol Table.
                // However, this is not a semantic or syntax error. This is a bug in the code.
                printf("[SYMBOL TABLE]: Error in computation of offsets in Symbol Table.\n");
                return 1;
            }
        }

        // Dump the symbol table as per the requirements of the given compiler flags
        if(SYMBOL_TABLE_PRINT == 1) {
            string command = "mkdir -p " + string(path_sym);
            int result = system(const_cast<char*>(command.c_str())); // Execute the command
            if(result != 0) { // Check if the command executed successfully
                fprintf(stderr, "[COMPILER ERROR]: Error in creating folder for symbol table.\n");
                return 1;
            }
            
            // Call the function to dump all of the symbol table in the given file
            if(DEBUG_3AC_OUTSIDE_VERBOSE) cout << "[COMPILER]: DUMPING THE SYMBOL TABLE" << "\n";
            dumpAllSTs(path_sym, globalTable);
        }

        if(MILESTONE2_DEMO == 0) {
            // Creation of Activation Records for runtime support
            if(DEBUG_3AC_OUTSIDE_VERBOSE) cout << "[COMPILER]: FILLING ACTIVATION RECORDS" << "\n";
            flag = fillActivationRecords(globalTable);
            if(flag < 0) {
                // Some kind of error occured during computation of activation record from Symbol Table.
                // However, this is not a semantic or syntax error. This is a bug in the code.
                printf("[SYMBOL TABLE]: Error in creation of Activation Records.\n");
                return 1;
            }
        }
    }
    // printf("%s\n", assembly_outputfile_path);

    /***************************************** FRONTEND OF COMPILER ENDS **************************************/

    /***************************************** INTERMEDIATE REPRESENTATION ************************************/

    // REPRESENTATION GENERATION PHASE
    // Generation of 3AC IR
    if(DEBUG_INSIDE_VERBOSE) cout << "[COMPILER]: Enterring 3AC Construction Unit" << "\n";
    flag = make3AC(root);
    if(flag < 0) {
        // Some kind of error occured during computation of offsets in the Symbol Table.
        // However, this is not a semantic or syntax error. This is a bug in the code.
        printf("[COMPILER]: Error in code generation of the 3AC IR. Exiting from the compiler\n");
        return 1;
    }
    if(DEBUG_OUTSIDE_VERBOSE) cout << "[COMPILER]: Already Exited 3AC Construction Unit" << "\n";
    
    /***************************************** INTERMEDIATE REPRESENTATION ENDS *******************************/
    
    /***************************************** BACKEND OF COMPILER ********************************************/

    // MACHINE OPTIMIZATION PHASE
    // Machine Optimizations for the generated IR for efficient execution of the program.


    // Writing of the 3AC IR in a text file.
    FILE* output_3ac;
    if(strlen(path_3ac) == 0) {
        string path_3ac_string = "3ac_out.txt";
        path_3ac = const_cast<char*>(path_3ac_string.c_str());
        // printf("Path of 3ac file %s\n", path_3ac);
    }
    output_3ac = fopen(path_3ac, "w");
    if(!output_3ac) {
        fprintf(stderr, "[COMPILER ERROR]: File %s not found\n", path_3ac);
        return 1;
    }
    
    // Write into file the code for 3AC
    string code_3ac = *(root->code);
    // cout << code_3ac << "\n";
    fprintf(output_3ac, "%s\n", const_cast<char*>(code_3ac.c_str()));
    fclose(output_3ac);
    // fprintf(output_3ac, "%s", code_3ac.c_str());
    // char* code = const_cast<char*>(code_3ac.c_str());
    // fprintf(output_3ac, code);

    if(DEBUG_OUTSIDE_VERBOSE) {
        // Print the label mappings generated by the compiler for the x86 code generation
        for(unordered_map<string, SymbolTable*>::iterator it = labelMap.begin(); it != labelMap.end(); ++it) {
            cout << "[COMPILER]: Label " << (it->first) << " is mapped to Symbol Table " << (it->second->name) << "\n";
        }
    }

    // printf("Path of 3ac file %s\n", path_3ac);
    if(MILESTONE2_DEMO == 0) {
        // CODE GENERATION PHASE
        // Conversion of intermediate code to final x86 assembly program that can run directly on modern systems supporting x86 architecture.
        // printf("Path of 3ac file %s\n", path_3ac);
        if(strlen(assembly_outputfile_path) == 0) {
            // Get the current working directory
            char cwd[1000];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                // Append the file name to the current directory path
                strcat(cwd, "/out.s");
                assembly_outputfile_path = cwd;
            }
            else {
                // Handle error if getcwd fails
                fprintf(stderr, "[COMPILER ERROR]: Error in getting the current working directory.\n");
                return 1;
            }
        }
        FILE* output_x86;
        // printf("%s\n", assembly_outputfile_path);
        output_x86 = fopen(assembly_outputfile_path, "w");
        if(!output_x86) {
            fprintf(stderr, "[COMPILER ERROR]: File %s not found\n", assembly_outputfile_path);
            return 1;
        }

        regAlloc = new RegisterAllocation();
        string path_3ac_string(path_3ac);

        flag = generate_x86(code_3ac, output_x86);
        if(flag < 0) {
            // Some kind of error occured during computation of offsets in the Symbol Table.
            // However, this is not a semantic or syntax error. This is a bug in the code.
            printf("[COMPILER]: Error in x86 code generation. Exiting from the compiler\n");
            return 1;
        }

        path_3ac = const_cast<char*>(path_3ac_string.c_str());
        // printf("Path of 3ac file %s\n", path_3ac);
    }

    // printf("Path of 3ac file %s\n", path_3ac);
    // Deletion of the 3AC IR in a text file based on the flags passed to the compiler from command line.
    if(GENERATION_3AC == 0) {
        string path_3ac_string(path_3ac);
        string command = "rm " + path_3ac_string; // Command to execute
        // cout << command << "\n";
        int result = system(const_cast<char*>(command.c_str())); // Execute the command
        if(result != 0) { // Check if the command executed successfully
            fprintf(stderr, "[COMPILER ERROR]: An internal error occurred.\n");
            return 1;
        }
    }

    /***************************************** BACKEND OF COMPILER ENDS ***************************************/
 
    // Exit the compiler
    return 0;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/

#endif // MAIN_CPP
