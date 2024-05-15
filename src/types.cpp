#ifndef TYPES_CPP
#define TYPES_CPP

#include <iostream>
#include <vector>
#include <string>
#include <stdarg.h>
#include <stack>
#include <regex>
#ifndef AST_HPP
#include "ast.hpp"
#endif
#ifndef TYPES_HPP
#include "types.hpp"
#endif
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
using namespace std;

/********************** ASSUMPTIONS FOR THE CONSTRUCTION OF TYPE SYSTEMS *****************************************/

// Write any assumptions that you take in the comment below
/*
----
*/

/********************** ASSUMPTIONS FOR THE CONSTRUCTION OF TYPE SYSTEMS *****************************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.

extern ASTNode* root;
extern int PARSER_DEBUG_INSIDE_VERBOSE;        // for verbose output purposes
extern int SYMBOL_TABLE_DEBUG_INSIDE_VERBOSE;
extern int SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.
int DEBUG_TYPE_CALL_COUNTER = 0;
stack<int> DEBUG_TYPE_CONTROL_FLOW;
// Symbol Table Configurations
SemanticError* ErrorMsg;                    // Semantic Error Message
SymbolTable* currTable;                     // pointer to the current symbol table in use
SymbolTable* globalTable;                   // pointer to the root (global scope) symbol table
stack<string> class_names_in_type_system;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

TypeExpression* type_print() {
    // A support will be provided for printing only primitive types from the print statement
    TypeExpression* domain = type_void();
    TypeExpression* range = type_void();
    TypeExpression* print = type_function(domain, range);
    return print;
}

// Check whether a given type can be printed using the "print" function
int check_print_param(TypeExpression* T) {
    if(T->type == TYPE_INT || T->type == TYPE_FLOAT || T->type == TYPE_STR || T->type == TYPE_BOOL) return 1;
    else if(T->type == TYPE_FUNC || T->type == TYPE_UNDF || T->type == TYPE_VOID) return 0;
    else if(T->type == TYPE_ARRAY) return check_print_param(T->array);
    else {
        int num_fields = (T->fields).size();
        for(int i=0; i<num_fields; i++) {
            int ret = check_print_param((T->fields)[i]);
            if(ret == 0) return 0;
        }
        return 1;
    }
}

TypeExpression* type_range() {
    // A support for only one primitive type integer
    TypeExpression* domain = new TypeExpression();
    TypeExpression* range = type_array(-1, type_int());
    TypeExpression* rng = type_function(domain, range);
    return rng;
}

TypeExpression* type_len() {
    // A support for the array "length" function.
    TypeExpression* undf = new TypeExpression();
    TypeExpression* domain = type_array(-1, undf);
    TypeExpression* range = type_int();
    TypeExpression* rng = type_function(domain, range);
    return rng;
}

// Whenever there is a semantic error (raised in symbol table) found during parsing then this function is called which
// returns with a semantic error in the program.
void semantic_error_symbol (
    int type, // Defines the type of the error which is being reported
    int lineno, // Line number of the offending token
    int columnno, // Column of the offending token
    string msg = "",            // Error message
    int flag = 0
) {
        switch(type) {
            case ERR_MISMATCH: {
                fprintf(stderr, "[SEMANTIC ERROR]: TYPE MISMATCH\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_NOT_FOUND: {
                fprintf(stderr, "[SEMANTIC ERROR]: DECLARATION MISSING\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_SCOPE: {
                fprintf(stderr, "[SEMANTIC ERROR]: SYMBOL NOT DEFINED IN THIS SCOPE\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_WRONG_PARAMS: {
                fprintf(stderr, "[SEMANTIC ERROR]: FUNCTION PARAMETERS ARE WRONG\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_TYPECAST: {
                fprintf(stderr, "[SEMANTIC ERROR]: IMPLICIT TYPE CASTING NOT SUPPORTED\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_BOUNDS: { // This is a runtime error so this error would not actually happen in the compile time
                fprintf(stderr, "[SEMANTIC ERROR]: ARRAY ACCESS ARE OUT OF BOUNDS OR NOT CORRECT\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_WRG_USE: { // Actually this is an internal compilation error so the control may not come inside this function for this case.
                fprintf(stderr, "[SEMANTIC ERROR]: WRONG USAGE OF STRUCTURE CONSTRUCTOR\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_UNDF: {
                fprintf(stderr, "[SEMANTIC ERROR]: ERROR NOT KNOWN\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_OTHER: {
                fprintf(stderr, "[SEMANTIC ERROR]: SEMANTIC ERROR FOUND IN THE PROGRAM\n");
                if(msg != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case WARNING: {
                fprintf(stderr, "[SEMANTIC WARNING]: SAME type USED TWICE IN SAME SCOPE. EARLIER DECLARATION IS OVERSHADOWED BY LATTER\n");
                if((ErrorMsg->msg) != "") fprintf(stderr, "[SEMANTIC WARNING]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC WARNING]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            default: { // Matches with none of the error codes. This should not happen.
                fprintf(
                    stderr,
                    "[SEMANTIC ERROR]: An unknown type error occured near column %d on line %d\n",
                    columnno,
                    lineno
                );
                break;
            }
        }

        return;
}

// Whenever there is a semantic error (raised in type systems) found during parsing then this function is called which
// returns with a semantic error in the program.
void semantic_error_type(
    ASTNode* operand1,
    string optr,
    ASTNode* operand2 = NULL
) {
    int lineno = operand1->lineno, columnno = operand1->columnno;
    string msg = optr + " operation not supported for types " + (operand1->T->encode);
    if(operand2 != NULL) msg += " and " + (operand2->T->encode);
    fprintf(stderr, "[SEMANTIC TYPE ERROR]: TYPE ERROR FOUND IN THE PROGRAM\n");
    if(msg != "") fprintf(stderr, "[SEMANTIC TYPE ERROR]: %s\n", const_cast<char*>(msg.c_str()));
    fprintf(stderr, "[SEMANTIC TYPE ERROR]: Error occured near line %d on column %d\n", lineno, columnno);
    return;
}

// This function returns Type in case of correct types NULL in case of error.
// A limited implicit type casting is implemented here however this is not as required as such.
TypeExpression* type_checking_unary(string optr, ASTNode* operand) {
    // Check if any of the types to be considered is a RECORD of a single field. That can be casted into a single simple type as well.
    TypeExpression *T = operand->T;
    while(T->type == TYPE_RECORD && (T->fields).size() == 1) T = (T->fields)[0];
    
    // Basic binary operations are not supported on any other types
    // except the 4 basic types of INT, FLOAT, BOOL and STRING
    int type = T->type;
    if(type != TYPE_INT && type != TYPE_FLOAT && type != TYPE_BOOL && type != TYPE_STR) {
        // TYPE ERROR SHOULD BE RETURNED
        semantic_error_type(operand, optr);
        return NULL;
        // return operand->T;
    }

    if (
        // Output will be the computation result
        optr == "+" || optr == "-" || optr == "~"
    )
    {
        if(type == TYPE_STR) {
            // This operation is not supported for arithmetic types
            // TYPE ERROR SHOULD BE RETURNED
            semantic_error_type(operand, optr);
            return NULL;
            // return operand->T;
        }
        else if(type == TYPE_BOOL) return type_bool();
        else if(type == TYPE_FLOAT) return type_float();
        else return type_int();
    }

    if (
        // Output will be a boolean as these are relational operators
        optr == "and" || optr == "or" || optr == "not"
    )
    {
        if(type == TYPE_STR) {
            // This operation is not supported for arithmetic types
            // TYPE ERROR SHOULD BE RETURNED
            semantic_error_type(operand, optr);
            return NULL;
            // return operand->T;
        }
        else if(type != TYPE_BOOL) {
            operand->T = type_bool();
            return type_bool();
        }
        else return type_bool();
    }

    if (
        // These are strict conditional operators
        optr == "if" || optr == "else"
    )
    {
        if(type != TYPE_BOOL) {
            // This operation is not supported for arithmetic types
            // TYPE ERROR SHOULD BE RETURNED
            semantic_error_type(operand, optr);
            return NULL;
            // return operand->T;
        }
        else return type_bool();
    }
    
    else {
        // This is not one of the basic operator for which the type checking implementation is demanded in Milestone 1.
        // Such cases are not supported for now. They directly result in a true output.
        return operand->T;
    }

    return 0; // Control should never reach here if the execution is correct.
}

// This function returns Type in case of correct types NULL in case of error.
// A limited implicit type casting is implemented here however this is not as required as such.
TypeExpression* type_checking_binary(ASTNode* operand1, string optr, ASTNode* operand2) {
    // Check if any of the types to be considered is a RECORD of a single field. That can be casted into a single simple type as well.
    TypeExpression *T1 = operand1->T, *T2 = operand2->T;
    while(T1->type == TYPE_RECORD && (T1->fields).size() == 1) T1 = (T1->fields)[0];
    while(T2->type == TYPE_RECORD && (T2->fields).size() == 1) T2 = (T2->fields)[0];
    
    int type1 = T1->type, type2 = T2->type;
    if(type1 == TYPE_VOID && type2 == TYPE_VOID) return type_void();

    // Case of comparison operators
    if(
        optr == "in" || optr == "not-in" // These come under comp_op non terminal
    ) {
        if(type2 != TYPE_ARRAY && type2 != TYPE_RECORD) {
            // TYPE ERROR SHOULD BE RETURNED
            semantic_error_type(operand1, optr, operand2);
            return NULL;
            // return operand1->T;
        }
        else if(type2 == TYPE_ARRAY) {
            int num = type_check(operand2->T->array, operand1->T);
            if(num==1) return type_bool();
            else {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
        }
        else {
            return type_bool();

            // MAYBE NOT NEEDED
            // for(int i=0;i<(operand2->T->fields).size();i++) {
            //     int num = type_check((operand2->T->fields)[i], operand1->T);
            //     if(num==1) return type_bool();
            // }
            // semantic_error_type(operand1, optr, operand2);
            // return NULL;
        }
    }
    
    // Basic binary operations are not supported on any other types
    // except the 4 basic types of INT, FLOAT, BOOL and STRING
    if(type1 != TYPE_INT && type1 != TYPE_FLOAT && type1 != TYPE_BOOL && type1 != TYPE_STR) {
        // TYPE ERROR SHOULD BE RETURNED
        semantic_error_type(operand1, optr, operand2);
        return NULL;
        // return operand1->T;
    }
    if(type2 != TYPE_INT && type2 != TYPE_FLOAT && type2 != TYPE_BOOL && type2 != TYPE_STR) {
        // TYPE ERROR SHOULD BE RETURNED
        semantic_error_type(operand1, optr, operand2);
        return NULL;
        // return operand1->T;
    }

    if (
        // These are computation operators
        // Output will be the computation result
        optr == "+" || optr == "-" || optr == "*" || optr == "/" || optr == "**" || optr == "%" ||
        optr == "//" || optr == "+=" || optr == "-=" || optr == "*=" || optr == "/=" || optr == "//=" ||
        optr == "%=" || optr == "**=" || optr == "=" || optr == "&=" || optr == "|=" || optr == "^=" ||
        optr == "<<=" || optr == ">>="
    )
    {
        if(type1 == type2) {
            if(type1 == TYPE_STR && type2 == TYPE_STR) {
                // MINOR SUPPORT PROVIDED FOR STRING OPERATIONS
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;

                return type_str(operand1->T->space + operand2->T->space);
            }
            else if(type1 == TYPE_BOOL) return type_bool();
            else if(type1 == TYPE_FLOAT) return type_float();
            else return type_int();
        }
        else {
            // Implicit type casting cases
            if(type1 == TYPE_INT && type2 == TYPE_FLOAT) {
                operand1->T = type_float();
                return type_float();
            }
            if(type1 == TYPE_INT && type2 == TYPE_BOOL) {
                operand2->T = type_int();
                return type_int();
            }
            if(type1 == TYPE_INT && type2 == TYPE_STR) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_INT) {
                operand2->T = type_float();
                return type_float();
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_BOOL) {
                operand2->T = type_float();
                return type_float();
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_STR) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_INT) {
                operand1->T = type_int();
                return type_int();
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_FLOAT) {
                operand1->T = type_float();
                return type_float();
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_STR) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_INT) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_BOOL) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_FLOAT) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
        }
    }

    if (
        // These are shift operators which should have 2nd operand as an integer only
        // Output will be the computation result
        optr == "<<" || optr == ">>"
    )
    {
        if(type2 == TYPE_STR || type2 == TYPE_FLOAT) {
            // TYPE ERROR SHOULD BE RETURNED
            semantic_error_type(operand1, optr, operand2);
            return NULL;
            // return operand1->T;
        }
        
        if(type1 == type2) {
            if(type1 == TYPE_STR && type2 == TYPE_STR) {
                // This operation is not supported for arithmetic types
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            else if(type1 == TYPE_BOOL) return type_bool();
            else if(type1 == TYPE_FLOAT) return type_float();
            else return type_int();
        }
        else {
            // Implicit type casting cases
            if(type1 == TYPE_INT && type2 == TYPE_BOOL) {
                operand2->T = type_int();
                return type_int();
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_INT) {
                return type_float();
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_BOOL) {
                operand2->T = type_int();
                return type_float();
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_INT) {
                return type_bool();
            }
            if(type1 == TYPE_STR && type2 == TYPE_INT) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_BOOL) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
        }
    }

    if (
        // These are relational operators which give boolean as the output
        optr == "==" || optr == "!=" || optr == ">" || optr == ">=" || optr == "<" || optr == "<=" ||
        optr == "is-not" || optr == "is" // These come under comp_op non terminal
    )
    {
        if(type1 == type2) return type_bool();
        else {
            // Implicit type casting cases
            if(type1 == TYPE_INT && type2 == TYPE_FLOAT) {
                operand1->T = type_float();
                return type_bool();
            }
            if(type1 == TYPE_INT && type2 == TYPE_BOOL) {
                operand2->T = type_int();
                return type_bool();
            }
            if(type1 == TYPE_INT && type2 == TYPE_STR) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_INT) {
                operand2->T = type_float();
                return type_bool();
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_BOOL) {
                operand2->T = type_float();
                return type_bool();
            }
            if(type1 == TYPE_FLOAT && type2 == TYPE_STR) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_INT) {
                operand1->T = type_int();
                return type_bool();
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_FLOAT) {
                operand1->T = type_float();
                return type_bool();
            }
            if(type1 == TYPE_BOOL && type2 == TYPE_STR) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_INT) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_BOOL) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
            if(type1 == TYPE_STR && type2 == TYPE_FLOAT) {
                // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
            }
        }
    }
    
    if(
        // These operators work by type casting values to booleans and then finding there values.
        optr == "and" || optr == "or" || optr == "not" || optr == "&" ||
        optr == "|" || optr == "^" || optr == "~"
    )
    {
        if(type1 == TYPE_STR || type2 == TYPE_STR) {
            // TYPE ERROR SHOULD BE RETURNED
                semantic_error_type(operand1, optr, operand2);
                return NULL;
                // return operand1->T;
        }
        else {
            // Implicit type casting cases
            if(type1 != TYPE_BOOL && type2 != TYPE_BOOL) {
                operand1->T = type_bool();
                operand2->T = type_bool();
                return type_bool();
            }
            else if(type1 != TYPE_BOOL) {
                operand1->T = type_bool();
                return type_bool();
            }
            else if(type2 != TYPE_BOOL) {
                operand2->T = type_bool();
                return type_bool();
            }
            else return type_bool();
        }
    }
    
    else {
        // This is not one of the basic operator for which the type checking implementation is demanded in Milestone 1.
        // Such cases are not supported for now. They directly result in a true output.
        return operand1->T;
    }

    return 0; // Control should never reach here if the execution is correct.
}

string collect_terminals(ASTNode* root) {
    if((root->children).size() == 0) return (root->content);
    else if((root->content) != "") return (root->content);
    else {
        string ans = "";
        for(int i=0;i<(root->children).size();i++) {
            string get = collect_terminals((root->children)[i]);
            ans = ans + get;
        }
        return ans;
    }
}

TypeExpression* number_type(string input) {
    const std::regex integerRegex(R"((\b[1-9][0-9]*|0[0-7]*|0[xX][0-9a-fA-F]+|0[bB][01]+)\b)");
    const std::regex floatRegex(R"(\b(\d+\.\d*|\.\d+|\d+)([eE][-+]?\d+)?\b)");
    const std::regex imagRegex(R"(\b(\d+\.\d*|\.\d+|\d+)([eE][-+]?\d+)?(j|J)\b)");
    string result;
    smatch matches;

    if(regex_search(input, matches, integerRegex)) {
        // cout << "Number identified as integer\n";
        return type_int();
    }
    else if(regex_search(input, matches, floatRegex)) {
        // cout << "Number identified as floating-point\n";
        return type_float();
    }
    else if (regex_search(input, matches, imagRegex)) {
        // Actually such numbers with imaginary values are not supported.
        // We will return integer here to be safe and issue a warning for the same
        int type = WARNING;
        string msg = "Imaginary numbers are not supported.";
        (ErrorMsg->msg) = "";
        semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
        return type_int();
    }
    else {
        // Other cases which are not expected to occur in lexer will come here
        // Here we will be giving a lexical error in the program
        int type = ERR_UNDF;
        string msg = "The number identified is not supported by lexical utility.";
        (ErrorMsg->msg) = "";
        semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
        return NULL;
    }
    
    return NULL; // Control should never reach here
}

// Set the type and delcarations for the NAME terminal
int set_name_type(ASTNode* root, string content, int len) {
    if(content == "__name__") {
        // This is a variable of string type. However, the actual
        // length of the string will be decided by the assignment to it.
        root->T = type_str(len);
        root->declarations = vector<STentry*>();
    }
    else if(content == "__init__") {
        // This will be a function so will be handled in funcdef
        // THIS FUNCTION IS NEVER CALLED SO WE NEED NOT WORRY ABOUT THE 
        root->T = type_str(len);
        root->declarations = vector<STentry*>();
    }
    else if(content == "range") {
        root->T = type_range();
        root->declarations = vector<STentry*>();
    }
    else if(content == "print") {
        root->T = type_print();
        root->declarations = vector<STentry*>();
    }
    else if(content == "len") {
        root->T = type_len();
        root->declarations = vector<STentry*>();
    }
    else if(content == "int") {
        root->T = type_int();
        root->declarations = vector<STentry*>();
    }
    else if(content == "float") {
        root->T = type_float();
        root->declarations = vector<STentry*>();
    }
    else if(content == "bool") {
        root->T = type_bool();
        root->declarations = vector<STentry*>();
    }
    else if(content == "str") {
        root->T = type_str(len);
        root->declarations = vector<STentry*>();
    }
    else if(content == "list") {
        TypeExpression* undf = new TypeExpression();
        root->T = type_array(-1, undf);
        root->declarations = vector<STentry*>();
    }
    else if(content == "self") {
        // If this is a case where "self" keyword is used inside a class then "self" corresponds to an object of that class
        bool class_flag = class_names_in_type_system.empty();
        if(class_flag == true) {
            // A case where "self" is used outside the classes is allowed. It will be a normal variable.
            root->T = new TypeExpression();
            root->declarations = vector<STentry*>();
        }
        else {
            // This "self" actually is a reference to a class object.
            string class_name = class_names_in_type_system.top();
            STentry* entry = lookup(class_name, NULL);
            if(entry == NULL) {
                // This case should not occur this is some internal compilation error.
                int type = ERR_UNDF;
                string msg = "Some internal compilation error occured";
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            else {
                root->T = entry->symbol_type;
                root->declarations = vector<STentry*>();
                // cout << "Identified a self under a class and given a type " << (root->T->encode) << "\n";
            }
        }
    }
    
    // THIS CASE IS INCOMPLETE - CLASS OBJECTS NEED TO BE HANDLED
    // INFACT ANY VARIABLE USED IN THE PROGRAM REQUIRES TO BE HANDLED HERE
    else {
        // This is a new NAME not predefined in compiler
        // root->T = type_void();
        // root->declarations = vector<STentry*>();
        
        // SCOPE CHECKING AND USER DEFINITION REQUIRED HERE
        // Cannot do scope checking at this stage
        STentry* entry = lookup(content, NULL);
        if(entry == NULL) {
            // cout << "No such entry is found" << "\n";
            root->T = new TypeExpression();
            root->declarations = vector<STentry*>();
        }
        else {
            // cout << "This is a user defined variable or type" << "\n";
            root->T = entry->symbol_type;
            root->declarations = vector<STentry*>();
        }
    }

    return 0; // This return denotes no error
}

int semantic_analysis_recursive(struct ASTNode* root) {
    string type = (root->type);
    string name = (root->name);
    int flag = 0, local_debug_counter = DEBUG_TYPE_CALL_COUNTER;

    if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
        cout << "[TYPE SYSTEM]: Called semantic analysis for " << type << " non terminal with " << name << " production.";
        cout << " Call: " << local_debug_counter << "\n";
        DEBUG_TYPE_CALL_COUNTER++;
        DEBUG_TYPE_CONTROL_FLOW.push(local_debug_counter);
    }

    // Set mapping of non-terminals with there respective symbol table
    // Exception case - when there is a increment in scope
    root->table = currTable;

    // Semantic analysis for start non-terminal
    if(type == "start") {
        // file_input
        // You will have to call the compute offsets function here
        // That is done in the "main.cpp" file
        flag = semantic_analysis_recursive((root->children)[0]);
        if(flag < 0) return flag;
        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if(type =="file_input") {
        // continued_file_input ENDMARKER
        flag = semantic_analysis_recursive((root->children)[0]);
        if(flag < 0) return flag;
        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if(type == "continued_file_input") {
        switch((root->children).size()) {
            case 2: {
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                if((root->children)[1]->type == "NEWLINE") {
                    // continued_file_input NEWLINE
                    root->T = (root->children)[0]->T;
                    root->declarations = (root->children)[0]->declarations;
                }
                else if((root->children)[1]->type == "stmt") {
                    // continued_file_input stmt
                    flag = semantic_analysis_recursive((root->children)[1]);
                    if(flag < 0) return flag;
                    root->T = (root->children)[0]->T;
                    (root->T->fields).push_back((root->children)[1]->T);
                    root->declarations = (root->children)[0]->declarations;
                    (root->declarations).insert(
                        (root->declarations).end(),
                        ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                    );
                }
                else {
                    // This error should not happen of the parse tree is correctly constructed
                    if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                    return -1;
                }
                break;
            }
            case 0: {
                // %empty
                root->T = type_record(deque<TypeExpression*>());
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // Semantic analysis for the case of function definition
    if(type == "funcdef") {
        switch((root->children).size()) {
            case 5: {
                // DEF NAME parameters COLON suite
                // cout << "Inside funcdef during semantic analysis" << "\n";
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                TypeExpression* none = type_void();
                TypeExpression* T = type_function((root->children)[2]->T, none);
                string lexeme = (root->children)[1]->content;
                if(!class_names_in_type_system.empty()) {
                    // This function has been declared inside a class so the name needs to contain that information
                    string class_name = class_names_in_type_system.top();
                    lexeme = class_name + "." + lexeme;
                }
                // cout << "Entry getting added in symbol table" << "\n";
                STentry* entry = add(lexeme, "FUNCTION", T, root->lineno, root->columnno, &flag);
                if(entry == NULL) {
                    // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                    // cout << "Error in adding entry" << "\n";
                    string error_message = "Error in function declaration";
                    semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                    return -1;
                }
                else if(flag > 0) {
                    // Variable overloading or class overloading is done which may not be intended. Issue a warning for this.
                    // cout << "Some other error happened" << "\n";
                    semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
                }
                
                // Construct symbol table for functions
                flag = incr_scope(FUNC_SCOPE, lexeme, T);
                if(flag < 0) return flag;
                
                // Before going to the suite of the function first parameters need to be added to the symbol table
                int num_params = ((root->children)[2]->names).size();
                for(int i=0; i<num_params; i++) {
                    string lexeme = ((root->children)[2]->names)[i];
                    TypeExpression* T = ((root->children)[2]->T->fields)[i];
                    STentry* entry = add(lexeme, "PARAMETER", T, root->lineno, root->columnno, &flag);
                    if(entry == NULL) {
                        // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                        string error_message = "Error in function declaration";
                        semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                        return -1;
                    }
                    else if(flag > 0) {
                        // Variable overloading or class overloading is done which may not be intended. Issue a warning for this.
                        // cout << "Some other error happened" << "\n";
                        semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
                    }
                }
                
                flag = semantic_analysis_recursive((root->children)[4]);
                if(flag < 0) return flag;
                
                
                flag = decr_scope();
                if(flag < 0) return flag;
                (root->table) = (root->children)[4]->table;

                // cout << "Funcdef is done" << "\n";

                root->T = T;
                root->declarations = (root->children)[4]->declarations;
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
                    if((root->children)[2]->T == NULL) cout << "[TYPE SYSTEM]: parameters non-terminal is NULL\n";
                }

                break;
            }
            case 7: {
                // DEF NAME parameters RIGHTARROW test COLON suite
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[4]);
                if(flag < 0) return flag;
                TypeExpression* T = type_function((root->children)[2]->T, (root->children)[4]->T);
                string lexeme = (root->children)[1]->content;
                if(!class_names_in_type_system.empty()) {
                    // This function has been declared inside a class so the name needs to contain that information
                    string class_name = class_names_in_type_system.top();
                    lexeme = class_name + "." + lexeme;
                }
                STentry* entry = add(lexeme, "FUNCTION", T, root->lineno, root->columnno, &flag);
                if(entry == NULL) {
                    // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                    string error_message = "Error in function declaration";
                    semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                    return -1;
                }
                else if(flag > 0) {
                    // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                    semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
                }
                
                // Construct symbol table for functions
                flag = incr_scope(FUNC_SCOPE, lexeme, T);
                if(flag < 0) return flag;

                // Before going to the suite of the function first parameters need to be added to the symbol table
                int num_params = ((root->children)[2]->names).size();
                for(int i=0; i<num_params; i++) {
                    string lexeme = ((root->children)[2]->names)[i];
                    TypeExpression* T = ((root->children)[2]->T->fields)[i];
                    STentry* entry = add(lexeme, "PARAMETER", T, root->lineno, root->columnno, &flag);
                    if(entry == NULL) {
                        // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                        string error_message = "Error in function declaration";
                        semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                        return -1;
                    }
                    else if(flag > 0) {
                        // Variable overloading or class overloading is done which may not be intended. Issue a warning for this.
                        // cout << "Some other error happened" << "\n";
                        semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
                    }
                }

                flag = semantic_analysis_recursive((root->children)[6]);
                if(flag < 0) return flag;
                flag = decr_scope();
                if(flag < 0) return flag;
                (root->table) = (root->children)[4]->table;
                
                root->T = T;
                root->declarations = (root->children)[6]->declarations;
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
                    if((root->children)[2]->T == NULL) cout << "[TYPE SYSTEM]: parameters non-terminal is NULL\n";
                }
                
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "parameters") {
        switch((root->children).size()) {
            case 2: {
                // OPENING_BRACKET CLOSING_BRACKET
                root->T = type_void();
                root->declarations = vector<STentry*>();
                root->names = deque<string>();
                break;
            }
            case 3: {
                // OPENING_BRACKET typedargslist CLOSING_BRACKET
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
                root->T = (root->children)[1]->T;
                root->declarations = (root->children)[1]->declarations;
                root->names = (root->children)[1]->names;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "typedargslist") {
        if(name == "typedargslist.1" || name == "typedargslist.2") {
            // tfpdef EQUAL test next_arg COMMA
            // tfpdef EQUAL test next_arg
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[2]);
            if(flag < 0) return flag;
            TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
            (root->children)[3]->T = T;
            (root->children)[3]->names = (root->children)[0]->names;
            flag = semantic_analysis_recursive((root->children)[3]);
            if(flag < 0) return flag;
            root->T = (root->children)[3]->T;
            root->declarations = (root->children)[3]->declarations;
            root->names = (root->children)[3]->names;
        }
        else if(name == "typedargslist.3" || name == "typedargslist.4") {
            // tfpdef next_arg COMMA
            // tfpdef next_arg
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            (root->children)[1]->T = (root->children)[0]->T;
            (root->children)[1]->names = (root->children)[0]->names;
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
            root->names = (root->children)[1]->names;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
        // cout << "Leaving typedargslist with type " << (root->T->encode) << "\n";
    }

    if(type == "next_arg") {
        switch((root->children).size()) {
            case 5: {
                // next_arg COMMA tfpdef EQUAL test
                (root->children)[0]->T = (root->T);
                (root->children)[0]->names = (root->names);
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[4]);
                if(flag < 0) return flag;
                TypeExpression* T = type_checking_binary((root->children)[2], (root->children)[3]->content, (root->children)[4]);
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back(T);
                root->declarations = vector<STentry*>();
                (root->names) = (root->children)[0]->names;
                (root->names).push_back(((root->children)[2]->names)[0]);
                break;
            }
            case 3: {
                // next_arg COMMA tfpdef
                (root->children)[0]->T = (root->T);
                (root->children)[0]->names = (root->names);
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back((root->children)[2]->T);
                root->declarations = vector<STentry*>();
                (root->names) = (root->children)[0]->names;
                (root->names).push_back(((root->children)[2]->names)[0]);
                break;
            }
            case 0: {
                // %empty production
                deque<TypeExpression*> T = deque<TypeExpression*>(1, root->T);
                root->T = type_record(T);
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "tfpdef") {
        (root->names) = deque<string>();
        switch((root->children).size()) {
            case 3: {
                // NAME COLON test
                string content = (root->children)[0]->content;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                root->T = (root->children)[2]->T;
                root->declarations = (root->children)[2]->declarations;
                (root->names).push_back(content);
                break;
            }
            case 1: {
                // NAME
                string content = (root->children)[0]->content;
                int len = content.length();
                // Type of the function parameter is assumed to be None in case of no parameter type annotation.
                (root->T) = type_void();
                (root->declarations) = vector<STentry*>();
                (root->names).push_back(content);
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // Semantic analysis for the case of class definition
    if(type == "classdef") {
        if(name == "classdef.1") {
            // CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite
            class_names_in_type_system.push((root->children)[1]->content);
            flag = semantic_analysis_recursive((root->children)[3]);
            if(flag < 0) return flag;
            TypeExpression* arglist_type = (root->children)[3]->T;
            string lexeme = (root->children)[1]->content;
            TypeExpression* T1 = type_record(deque<TypeExpression*>(), 1, arglist_type->fields, lexeme);
            STentry* entry = add(lexeme, "CLASS", T1, root->lineno, root->columnno, &flag);
            if(entry == NULL) {
                // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                string error_message = "Error in class declaration";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                return -1;
            }
            else if(flag > 0) {
                // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
            }

            flag = incr_scope(CLASS_SCOPE, lexeme, NULL);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[6]);
            if(flag < 0) return flag;
            flag = decr_scope();
            if(flag < 0) return flag;

            TypeExpression* T2 = type_record((root->children)[6]->T->fields, 1, arglist_type->fields, lexeme);
            T2->lexeme = (&(entry->lexeme));
            entry->symbol_type = T2;
            class_names_in_type_system.pop();
            (root->table) = (root->children)[6]->table;
        }
        else if(name == "classdef.2") {
            // CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite
            string lexeme = (root->children)[1]->content;
            class_names_in_type_system.push((root->children)[1]->content);
            TypeExpression* T1 = type_record(deque<TypeExpression*>(), 1, deque<TypeExpression*>(), lexeme);
            STentry* entry = add(lexeme, "CLASS", T1, root->lineno, root->columnno, &flag);
            if(entry == NULL) {
                // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                string error_message = "Error in class declaration";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                return -1;
            }
            else if(flag > 0) {
                // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
            }

            flag = incr_scope(CLASS_SCOPE, lexeme, NULL);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[5]);
            if(flag < 0) return flag;
            flag = decr_scope();
            if(flag < 0) return flag;

            TypeExpression* T2 = type_record((root->children)[5]->T->fields, 1, deque<TypeExpression*>(), lexeme);
            T2->lexeme = (&(entry->lexeme));
            entry->symbol_type = T2;
            class_names_in_type_system.pop();
            (root->table) = (root->children)[5]->table;
        }
        else if(name == "classdef.3") {
            // CLASS NAME COLON suite
            string lexeme = (root->children)[1]->content;
            class_names_in_type_system.push((root->children)[1]->content);
            TypeExpression* T1 = type_record(deque<TypeExpression*>(), 1, deque<TypeExpression*>(), lexeme);
            STentry* entry = add(lexeme, "CLASS", T1, root->lineno, root->columnno, &flag);
            if(entry == NULL) {
                // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                string error_message = "Error in class declaration";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                return -1;
            }
            else if(flag > 0) {
                // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
            }

            flag = incr_scope(CLASS_SCOPE, lexeme, NULL);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[3]);
            if(flag < 0) return flag;
            flag = decr_scope();
            if(flag < 0) return flag;

            TypeExpression* T2 = type_record((root->children)[3]->T->fields, 1, deque<TypeExpression*>(), lexeme);
            T2->lexeme = (&(entry->lexeme));
            entry->symbol_type = T2;
            class_names_in_type_system.pop();
            (root->table) = (root->children)[3]->table;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "comp_iter") {
        // comp_if
        // comp_for
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if(type == "comp_if") {
        switch ((root->children).size()) {
            case 3: {
                // IF test_nocond comp_iter
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;

                // set the type and declarations same as for comp_iter
                root->T = (root->children)[2]->T;
                root->declarations = (root->children)[2]->declarations;
                break;
            }
            case 2: {
                // IF test_nocond
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[1]->T;
                root->declarations = (root->children)[1]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "comp_for") {
        switch ((root->children).size()) {
            case 5: {
                // FOR exprlist IN or_test comp_iter
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[3]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[4]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

                // set the type and declarations same as for comp_iter
                root->T = (root->children)[4]->T;
                root->declarations = (root->children)[4]->declarations;
                break;
            }
            case 4: {
                // FOR exprlist IN or_test
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[3]);
                if(flag < 0) return flag;

                // set the type and declarations same as for or_test
                root->T = (root->children)[3]->T;
                root->declarations = (root->children)[3]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // Not supported properly just coded for completeness
    if(type == "continued_dictorset") {
        if(name == "continued_dictorset.1") {
            // continued_dictorset COMMA test COLON test
            (root->children)[0]->T = root->T;
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[4]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->declarations = (root->children)[0]->declarations;
            TypeExpression* T = type_checking_binary((root->children)[2], (root->children)[3]->content, (root->children)[4]);
            if(T == NULL) return -1;
            SymbolTable* table;
            STentry* entry = add(
                (root->children)[2]->full_content,
                "DICTIONARY_KEY",
                T,
                root->lineno, root->columnno, &flag, table
            );
            (root->declarations).push_back(entry);
            root->T = (root->children)[0]->T;
            (root->T->fields).push_back(T);
        }
        else if(name == "continued_dictorset.2") {
            // continued_dictorset COMMA DOUBLE_STAR expr
            (root->children)[0]->T = root->T;
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[3]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->declarations = (root->children)[0]->declarations;
            TypeExpression* T = type_checking_unary((root->children)[2]->content, (root->children)[3]);
            if(T == NULL) return -1;
            SymbolTable* table;
            STentry* entry = add(
                (root->children)[3]->full_content,
                "DICTIONARY_KEY",
                T,
                root->lineno, root->columnno, &flag, table
            );
            (root->declarations).push_back(entry);
            root->T = (root->children)[0]->T;
            (root->T->fields).push_back(T);
        }
        else if(name == "continued_dictorset.3") {
            // %empty
            deque<TypeExpression*> type;
            type.push_back(root->T);
            root->T = type_record(type);
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Not supported properly. Just coded for completeness
    if (type == "dictorsetmaker") {
        if(name == "dictorsetmaker.1" || name == "dictorsetmaker.2" || name == "dictorsetmaker.3") {
            // test COLON test comp_for
            // test COLON test continued_dictorset COMMA
            // test COLON test continued_dictorset
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            (root->children)[3]->T = (root->children)[2]->T;
            flag = semantic_analysis_recursive((root->children)[3]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[3]->T;
            TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
            if(T == NULL) return -1;
            SymbolTable* table;
            root->declarations = vector<STentry*>();
            STentry* entry = add(
                (root->children)[0]->full_content,
                "DICTIONARY_KEY",
                T,
                root->lineno, root->columnno, &flag, table
            );
            (root->declarations).push_back(entry);
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
            );
        }
        else if(name == "dictorsetmaker.4" || name == "dictorsetmaker.5" || name == "dictorsetmaker.6") {
            // DOUBLE_STAR expr comp_for
            // DOUBLE_STAR expr continued_dictorset COMMA
            // DOUBLE_STAR expr continued_dictorset
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            TypeExpression* T = type_checking_unary((root->children)[0]->content, (root->children)[1]);
            if(T == NULL) return -1;
            (root->children)[2]->T = T;
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[2]->T;
            SymbolTable* table;
            root->declarations = vector<STentry*>();
            STentry* entry = add(
                (root->children)[0]->full_content,
                "DICTIONARY_KEY",
                T,
                root->lineno, root->columnno, &flag, table
            );
            (root->declarations).push_back(entry);
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
            );
        }
        if(name == "dictorsetmaker.7" || name == "dictorsetmaker.8" || name == "dictorsetmaker.9") {
            // test comp_for
            // test continued_testlist COMMA
            // test continued_testlist
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            SymbolTable* table;
            root->declarations = vector<STentry*>();
            STentry* entry = add(
                (root->children)[0]->full_content,
                "DICTIONARY_KEY",
                (root->children)[0]->T,
                root->lineno, root->columnno, &flag, table
            );
            (root->declarations).push_back(entry);
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else if(name == "dictorsetmaker.10" || name == "dictorsetmaker.11" || name == "dictorsetmaker.12") {
            // star_expr comp_for
            // star_expr continued_testlist COMMA
            // star_expr continued_testlist
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            SymbolTable* table;
            root->declarations = vector<STentry*>();
            STentry* entry = add(
                (root->children)[0]->full_content,
                "DICTIONARY_KEY",
                (root->children)[0]->T,
                root->lineno, root->columnno, &flag, table
            );
            (root->declarations).push_back(entry);
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if (type == "continued_comma_test") {
        switch ((root->children).size()) {
            case 3: {
                // continued_comma_test COMMA test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) return flag;

                // set the type of test
                int num = ((root->children)[0]->children).size();
                if(num == 0) {
                    root->T = type_record(deque<TypeExpression*>());
                    (root->T->fields).push_back((root->children)[0]->T);
                    (root->T->fields).push_back((root->children)[2]->T);
                }
                else {
                    root->T = (root->children)[0]->T;
                    (root->T->fields).push_back((root->children)[2]->T);
                }
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            case 0: {
                // empty production
                // if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) cout << "[TYPE SYSTEM]: Inside the empty production\n";
                // if(root == NULL) cout << "root is NULL";
                // else if(root->declarations == NULL) cout << "not defined\n";
                root->declarations = vector<STentry*>();
                // if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) cout << "[TYPE SYSTEM]: Going outside the empty production\n";
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "testlist") {
        switch ((root->children).size()) {
            case 3: {
                // test continued_comma_test COMMA
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                (root->children)[1]->T = (root->children)[0]->T;
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) return flag;

                // set the type of expr
                int num = ((root->children)[1]->children).size();
                if(num == 0) root->T = (root->children)[0]->T;
                else {
                    root->T = (root->children)[1]->T;
                    (root->T->fields).push_front((root->children)[0]->T);
                }
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                );
                break;
            }
            case 2: {
                // test continued_comma_test
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                (root->children)[1]->T = (root->children)[0]->T;
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) return flag;

                // set the type of expr
                int num = ((root->children)[1]->children).size();
                if(num == 0) root->T = (root->children)[0]->T;
                else {
                    root->T = (root->children)[1]->T;
                    (root->T->fields).push_front((root->children)[0]->T);
                }
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "exprlist") {
        // expr continued_exprlist COMMA
        // expr continued_exprlist
        // star_expr continued_exprlist COMMA
        // star_expr continued_exprlist
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) return flag;
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) return flag;
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "continued_exprlist") {
        switch ((root->children).size()) {
            case 3: {
                // continued_exprlist COMMA expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) return flag;

                // set the type of expr
                int num = ((root->children)[0]->children).size();
                if(num == 0) {
                    root->T = type_record(deque<TypeExpression*>());
                    (root->T->fields).push_back((root->children)[0]->T);
                    (root->T->fields).push_back((root->children)[2]->T);
                }
                else {
                    root->T = (root->children)[0]->T;
                    (root->T->fields).push_back((root->children)[2]->T);
                }
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            case 0: {
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "sliceop") {
        // COLON test
        // COLON
    }

    if (type == "arglist") {
        // argument continued_argument COMMA
        // argument continued_argument
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "argument") {
        switch ((root->children).size()) {
            case 3: {
                // test EQUAL test
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            case 2: {
                if ((root->children)[0]->type == "DOUBLE_STAR" || (root->children)[0]->type == "STAR") {
                    // DOUBLE_STAR test
                    // STAR test
                    flag = semantic_analysis_recursive((root->children)[1]);
                    if (flag < 0) {
                        // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                        return flag;
                    }
                    TypeExpression* T = type_checking_unary((root->children)[0]->content, (root->children)[1]);
                    root->T = T;
                    root->declarations = (root->children)[1]->declarations;
                }   
                else {
                    // test comp_for
                    flag = semantic_analysis_recursive((root->children)[0]);
                    if (flag < 0) {
                        // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                        return flag;
                    }
                    flag = semantic_analysis_recursive((root->children)[1]);
                    if (flag < 0) {
                        // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                        return flag;
                    }
                    root->T = (root->children)[0]->T;
                    root->declarations = (root->children)[0]->declarations;
                    (root->declarations).insert(
                        (root->declarations).end(),
                        ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                    );
                }
                break;
            }
            case 1: {
                // test
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[0]->T;
                // cout << "We have got this type in the argument non-terminal: " << (root->T->encode) << "\n";
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "continued_argument") {
        switch ((root->children).size()) {
            case 3: {
                // continued_argument COMMA argument
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) return flag;

                // set the type of expr
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back((root->children)[2]->T);
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            case 0: {
                // empty production
                root->T = type_record(deque<TypeExpression*>(1, (root->T)));
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "subscriptlist") {
        // subscript continued_subscript COMMA
        // subscript continued_subscript
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if(type == "subscript") {
        if(name == "subscript.1") {
            // test
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else if(name == "subscript.2") {
            // test COLON test sliceop
        }
        else if(name == "subscript.3") {
            // test COLON test
        }
        else if(name == "subscript.4") {
            // test COLON sliceop
        }
        else if(name == "subscript.5") {
            // test COLON
        }
        else if(name == "subscript.6") {
            // COLON test sliceop
        }
        else if(name == "subscript.7") {
            // COLON test
        }
        else if(name == "subscript.8") {
            // COLON sliceop
        }
        else if(name == "subscript.9") {
            // COLON
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if (type == "continued_subscript") {
        switch ((root->children).size()) {
            case 3: {
                // continued_subscript COMMA subscript
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) return flag;

                // set the type of expr
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back((root->children)[2]->T);
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            case 0: {
                // empty production
                root->T = type_record(deque<TypeExpression*>(1, root->T));
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "testlist_comp") {
        if(name == "testlist_comp.1" || name == "testlist_comp.4") {
            // test comp_for
            // star_expr comp_for
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else if(name == "testlist_comp.2" || name == "testlist_comp.3" || name == "testlist_comp.5" || name == "testlist_comp.6") {
            // test continued_testlist COMMA
            // test continued_testlist
            // star_expr continued_testlist COMMA
            // star_expr continued_testlist
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "continued_testlist") {
        switch ((root->children).size()) {
            case 3: {
                // continued_testlist COMMA test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) return flag;

                // set the type of expr
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back((root->children)[2]->T);
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            case 0: {
                // %empty production
                deque<TypeExpression*> types = deque<TypeExpression*>(1, root->T);
                root->T = type_record(types);
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "strings") {
        switch ((root->children).size()) {
            case 2: {
                // strings STRING
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                int size = ((root->children)[0])->T->space + ((root->children)[1]->content).length();
                root->T = type_str(size);
                root->declarations = vector<STentry*>();
                root->content = (root->children)[0]->content + (root->children)[1]->content;;
                break;
            }
            case 1: {
                // STRING
                int len = ((root->children)[0]->content).length();
                root->T = type_str(len);
                root->declarations = vector<STentry*>();
                root->content = (root->children)[0]->content;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "atom") {
        if(name == "atom.1") {
            // OPENING_BRACKET testlist_comp CLOSING_BRACKET
            // This case denotes a set declaration
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else if(name == "atom.3") {
            // OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET
            // This case denotes a list declaration
            // Though the actual python interpreter works differently the type checking for prototype will be strict.
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) return flag;
            root->declarations = (root->children)[1]->declarations;

            // Type checking and type creation
            root->T = (root->children)[1]->T;
            int number = ((root->children)[1]->T->fields).size();
            if(number == 0) {
                // This case is supported with the consideration of a void type.
                // But most probably this will result in a type error later on.
                TypeExpression* undf = new TypeExpression();
                root->T = type_array(0, undf);
            }
            else {
                TypeExpression* T = ((root->children)[1]->T->fields)[0];
                for(int i = 1; i < number; i++) {
                    int type_flag = type_check(T, ((root->children)[1]->T->fields)[i]);
                    if(type_flag != 1) {
                        int type = ERR_WRG_USE;
                        string msg = "A list cannot be made using elements of different type.";
                        (ErrorMsg->msg) = "";
                        semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                        return -1;
                    }
                }
                root->T = type_array(number, T);
            }
        }
        else if(name == "atom.5") {
            // OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET
            // This case denotes a dictionary declaration
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else if(name == "atom.7") {
            // NAME
            string content = (root->children)[0]->content;
            int len = content.length();
            flag = set_name_type(root, content, len);
            if(flag < 0) return flag;
            (root->names) = deque<string>(1, content);
            // cout << "Name found which is " << content << " with type " << (root->T->encode) << "\n";
        }
        else if(name == "atom.8") {
            // NUMBER
            string check_num = (root->children)[0]->content;
            root->T = number_type(check_num);
            root->declarations = vector<STentry*>();
            if((root->T) == NULL) return -1;
        }
        else if(name == "atom.9") {
            // strings
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            int len = (root->children)[0]->content.length();
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else if(name == "atom.2" || name == "atom.4" || name == "atom.6" || name == "atom.10" || name == "atom.13") {
            // OPENING_BRACKET CLOSING_BRACKET
            // OPENING_SQ_BRACKET CLOSING_SQ_BRACKET
            // OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET
            // ELLIPSES_LITERAL - No support provided for this
            // TOKEN_NONE
            root->T = type_void();
            root->declarations = vector<STentry*>();
        }
        else if(name == "atom.11" || name == "atom.12") {
            // TOKEN_TRUE
            // TOKEN_FALSE
            root->T = type_bool();
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "trailers") {
        if(name == "trailers.1") {
            // trailers trailer
            (root->children)[0]->T = (root->T);
            (root->children)[0]->names = (root->names);
            
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            
            (root->children)[1]->T = (root->children)[0]->T;
            (root->children)[1]->names = (root->children)[0]->names;
            
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            
            // Type setting for "trailers"
            (root->T) = (root->children)[1]->T;
            (root->names) = (root->children)[1]->names;

            // Concatenate declarations for the "trailers"
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else if(name == "trailers.2") {
            // %empty production
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "trailer") {
        if(name == "trailer.1") {
            // OPENING_BRACKET arglist CLOSING_BRACKET
            // A function denoted by this trailer
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->declarations = (root->children)[1]->declarations;            
            
            // First step is to contruct the type of the function being called if it's type is not already known
            if((root->T->type) == TYPE_UNDF) {
                TypeExpression* domain = (root->children)[1]->T;
                TypeExpression* range = new TypeExpression();
                TypeExpression* T = type_function(domain, range);
                STentry* entry = lookup_restricted((root->names)[0], T);
                if(entry == NULL) {
                    int type = ERR_WRONG_PARAMS;
                    string msg = "No method named " + (root->names)[0] + " with appropriate parameter list found";
                    (ErrorMsg->msg) = "";
                    semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                    return -1;
                }
                else root->T = entry->symbol_type;
            }
            
            // Scope checking for the function being called is to be done here
            if((root->T->type) != TYPE_FUNC) {
                // Rigorous type checking needs to be done here. If the "trailer" is not a FUNCTION then this is an error
                int type = ERR_NOT_FOUND;
                string msg = "No method named " + (root->names)[0] + " found in the current scope";
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            
            int arg_flag = type_check(root->T->domain, (root->children)[1]->T);
            if((root->names)[0] == "len") {
                // cout << "We are inside the handling for the len function\n";
                int num_fields = ((root->children)[1]->T->fields).size();
                // cout << "Number of fields in arglist are " << num_fields << "\n";
                if(num_fields == 0) arg_flag = 0;
                else if(((root->children)[1]->T->fields)[0]->type == TYPE_ARRAY) {
                    // cout << "Type of arguments in len are " << (root->children)[1]->T->encode << "\n";
                    arg_flag = 1;
                    root->T->domain = (root->children)[1]->T;
                }
                else {
                    // cout << "We are not accepting this type for len because it is " << ((root->children)[1]->T->fields)[0]->encode << "\n";
                    arg_flag = 0;
                }
            }
            else if((root->names)[0] == "print") {
                int num_fields = ((root->children)[1]->T->fields).size();
                if(num_fields == 0) arg_flag = 0;
                else {
                    arg_flag = check_print_param((root->children)[1]->T);
                    if(arg_flag == 1) root->T->domain = (root->children)[1]->T;
                }
            }
            else if((root->names)[0] == "range") {
                int num_fields = ((root->children)[1]->T->fields).size();
                if(num_fields > 2 || num_fields == 0 || ((root->children)[1]->T->fields)[0]->type != TYPE_INT) arg_flag = 0;
                else {
                    if(num_fields == 2 && ((root->children)[1]->T->fields)[1]->type != TYPE_INT) arg_flag = 0;
                    else {
                        arg_flag = 1;
                        root->T->domain = (root->children)[1]->T;
                    }
                }
            }

            if(arg_flag != 1) {
                int type = ERR_WRONG_PARAMS;
                string msg = "No method named " + (root->names)[0] + " with appropriate parameter list found";
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            else (root->T) = (root->T->range);
        }
        else if(name == "trailer.2") {
            // OPENING_BRACKET CLOSING_BRACKET
            // A function call with void parameters is denoted by this trailer
            root->declarations = vector<STentry*>();

            // First step is to contruct the type of the function being called if it's type is not already known
            if((root->T->type) == TYPE_UNDF) {
                TypeExpression* domain = type_void();
                TypeExpression* range = new TypeExpression();
                TypeExpression* T = type_function(domain, range);
                STentry* entry = lookup_restricted((root->names)[0], T);
                if(entry == NULL) {
                    int type = ERR_WRONG_PARAMS;
                    string msg = "No method named " + (root->names)[0] + " with empty parameter list found";
                    (ErrorMsg->msg) = "";
                    semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                    return -1;
                }
                else root->T = entry->symbol_type;
            }
            
            if((root->T->type) != TYPE_FUNC) {
                // Rigorous type checking needs to be done here. If the "trailer" is not a FUNCTION then this is an error
                int type = ERR_NOT_FOUND;
                string msg = "No method named " + (root->names)[0] + " found in the current scope";
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            else if((root->T->domain->type) != TYPE_VOID) {
                int type = ERR_WRONG_PARAMS;
                string msg = "No method named " + (root->names)[0] + " with empty parameter list found";
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            else (root->T) = (root->T->range);
        }
        else if(name == "trailer.3") {
            // OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET
            // An array indexing is denoted by this trailer.
            // Infact this can also be used for dictionary and set indexing cases.
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->declarations = (root->children)[1]->declarations;

            // Type Setting for subscripting of a type
            if((root->T->type) != TYPE_ARRAY) {
                // Rigorous type checking needs to be done here. If the "trailer" is not an ARRAY then this is an error
                int type = ERR_WRG_USE;
                string msg = "Subscript operator supported for type " + (root->T->encode);
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            else if((root->T->array->type) == TYPE_UNDF) {
                // This is the case where a new type is being defined by the trailers for the previous atom.
                int num_fields = ((root->children)[1]->T->fields).size();
                // cout << "WE ARE INSIDE THE CASE WHERE LIST TYPE SETTING IS HANDLED with num_fields: " << num_fields << "\n";
                for(int i=num_fields-1; i>-1; i--) {
                    // The following working is only valid in cases a list or an array type definition
                    if(i == num_fields - 1) (root->T) = type_array(-1, ((root->children)[1]->T->fields)[i]);
                    else if(((root->children)[1]->T->fields)[i]->type != TYPE_INT) {
                        int type = ERR_BOUNDS;
                        string msg = "Only integers are allowed for indexing arrays and lists";
                        (ErrorMsg->msg) = "";
                        semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                        return -1;
                    }
                    else (root->T) = type_array(-1, (root->T));
                }
            }
            else {
                // This is the case of array indexing and thus no new type is defined here.
                // In the updated code this if-case is never actually reached.
                if((root->children)[1]->T->type != TYPE_RECORD) {
                    TypeExpression* T = (root->children)[1]->T;
                    (root->children)[1]->T->fields = deque<TypeExpression*>(1, T);
                }
                int num_fields = ((root->children)[1]->T->fields).size();
                // cout << "We are into type handling for trailer.3 production\n";
                for(int i=0; i<num_fields; i++) {
                    // The following working is only valid in cases a list or an array is being indexed
                    if(((root->children)[1]->T->fields)[i]->type != TYPE_INT) {
                        int type = ERR_BOUNDS;
                        string msg = "Only integers are allowed for indexing arrays and lists";
                        (ErrorMsg->msg) = "";
                        semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                        return -1;
                    }
                    else if((root->T->type) != TYPE_ARRAY) {
                        // Rigorous type checking needs to be done here. If the "trailer" is not an ARRAY then this is an error
                        int type = ERR_BOUNDS;
                        string msg = "Indexing is only supported for arrays and lists";
                        (ErrorMsg->msg) = "";
                        semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                        return -1;
                    }
                    else {
                        // cout << "We are going into an array indexing conversion here\n";
                        // if((root->T) == NULL) cout << "Oh my god the type is already NULL\n";
                        (root->T) = (root->T->array);
                        // if((root->T) == NULL) cout << "Oh my god the type has become NULL\n";
                    }
                }
            }
        }
        else if(name == "trailer.4") {
            // DOT NAME
            // A class utility is called using this trailer. This needs to be handled to support classes in python.
            
            // ASSUMPTION - Only classes have a scope resolution functionality and rest all cases will be an error
            if(root->T->class_flag == 0 && (root->T->type <= 8 && root->T->type >= 0)) {
                // Something other than a class name and class object is being used for a scope resolution
                int type = ERR_WRG_USE;
                string msg = "Scope resolution not supported for type " + (root->T->encode);
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
            else if(root->T->type <= 8 && root->T->type >= 0) {
                // A class name is being used for scope resolution
                int type_number = root->T->class_flag;
                string class_name = (root->names)[0];
                cout << "We have a class name here " << class_name << "\n";
            }
            else if(root->T->class_flag == 0) {
                // A class object is being used for scope resolution
                string obj_name = (root->names)[0];
                cout << "We have a class object here " << obj_name << "\n";
            }
            else {
                // This case should not occur this is some kind of an internal compiler error.
                int type = ERR_UNDF;
                string msg = "Some internal compilation error occured";
                (ErrorMsg->msg) = "";
                semantic_error_symbol(type, (root->lineno), (root->columnno), msg);
                return -1;
            }
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "atom_expr") {
        int adder_num = 0;
        if(name == "atom_expr.1") {
            // AWAIT atom trailers
            // Case not supported for AWAIT
            adder_num = 1;
        }
        if(name == "atom_expr.1" || name == "atom_expr.2") {
            // AWAIT atom trailers
            // atom trailers
            // The trailer can actually change the type of the atom
            flag = semantic_analysis_recursive((root->children)[0 + adder_num]);
            if(flag < 0) return flag;

            // Before going to the "trailers" we need to pass the information about what is the type of the "atom"
            // the "trailers" are going to work on.
            (root->children)[1 + adder_num]->T = (root->children)[0 + adder_num]->T;
            (root->children)[1 + adder_num]->names = (root->children)[0 + adder_num]->names;

            flag = semantic_analysis_recursive((root->children)[1 + adder_num]);
            if(flag < 0) return flag;
            
            // Type Setting for "atom_expr"
            // That is done inside the "trailers" and "trailer". Because that is easier.
            root->declarations = vector<STentry*>();
            (root->T) = (root->children)[1 + adder_num]->T;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if (type == "power") {
        switch ((root->children).size()) {
            case 3: {
                // atom_expr DOUBLE_STAR factor
                // DOUBLE_STAR is the exponential expression here
                // Type Checking will be required
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], "**", (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            case 1: {
                // atom_expr
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[0]->T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default:  {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "factor") {
        switch ((root->children).size()) {
            case 2: {
                // PLUS factor
                // MINUS factor
                // TILDE factor
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_unary((root->children)[0]->content, (root->children)[1]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            case 1: {
                // power
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[0]->T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "continued_factor") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // continued_factor STAR factor
                // continued_factor DIV factor
                // continued_factor REM factor
                // continued_factor FLOOR_DIV factor
                // continued_factor AT factor
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "term") {
        // factor continued_factor
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "continued_term") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry *>();
                break;
            }
            case 3: {
                // ccontinued_term PLUS term
                // continued_term MINUS term
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "arith_expr") {
        // term continued_term
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "continued_arith_expr") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry *>();
                break;
            }
            case 3: {
                // continued_arith_expr LEFT_SHIFT arith_expr
                // continued_arith_expr RIGHT_SHIFT arith_expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "shift_expr") {
        // arith_expr continued_arith_expr
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "continued_shift_expr") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry *>();
                break;
            }
            case 3: {
                // continued_shift_expr BITWISE_AND shift_expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "and_expr") {
        // shift_expr continued_shift_expr
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "continued_and_expr") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry *>();
                break;
            }
            case 3: {
                // continued_and_expr CARET and_expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "xor_expr") {
        // and_expr continued_and_expr
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "continued_xor_expr") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // continued_xor_expr BITWISE_OR xor_expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "expr") {
        // xor_expr continued_xor_expr
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "star_expr") {
        // STAR expr
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[1]->declarations;
    }

    if (type == "comp_op") {
        // COMP_OP
        // IN
        // NOT IN
        // IS
        // IS NOT
        root->T = type_bool();
        root->declarations = vector<STentry*>();
        if((root->children).size() == 1) (root->content) = (root->children)[0]->content;
        else (root->content) = (root->children)[0]->content + "-" + (root->children)[1]->content;
    }

    if(type == "comparison_stmt") {
        switch ((root->children).size()) {
            case 0: {
                // %empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // comparison_stmt comp_op expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                string optr = (root->children)[1]->full_content;
                TypeExpression* T = type_checking_binary((root->children)[0], optr, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "comparison") {
        // expr comparison_stmt
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if (type == "not_test") {
        switch ((root->children).size()) {
            case 2: {
                // NOT not_test
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_unary((root->children)[0]->content, (root->children)[1]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[1]->declarations;
                break;
            }
            case 1: {
                // comparison
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[0]->T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "and_test") {
        // not_test continued_and_test
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }
    
    if(type == "continued_and_test") {
        switch ((root->children).size()) {
            case 0: {
                // %empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // continued_and_test AND not_test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "or_test") {
        // and_test continued_or_test
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
    }

    if(type == "continued_or_test") {
        switch((root->children).size()) {
            case 0: {
                // %empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // continued_or_test OR and_test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                if (T == NULL) return -1;
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "test_nocond") {
        // or_test
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if (type == "test") {
        // cout << "Inside test non terminal" << "\n";
        switch ((root->children).size()) {
            case 5: {
                // or_test IF or_test ELSE test
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[4]);
                if(flag < 0) return flag;
                TypeExpression* T1 = type_checking_unary((root->children)[1]->content, (root->children)[2]);
                if (T1 == NULL) return -1;
                root->T = (root->children)[0]->T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
                );
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[4]->declarations).begin(), ((root->children)[4]->declarations).end()
                );
                break;
            }
            case 1: {
                // or_test
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[0]->T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
        // cout << "Returning from test non terminal" << "\n";
    }

    // Semantic analysis for the case of statements
    if(type == "stmts") {
        switch ((root->children).size()) {
            case 2: {
                // stmts stmt
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
                deque<TypeExpression*> decs = (root->children)[0]->T->fields;
                decs.push_back((root->children)[1]->T);
                root->T = type_record(decs);
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                );
                break;
            }
            case 1: {
                // stmt
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                root->T = (root->children)[0]->T;
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // Check the semantic analysis for a statement
    if(type == "stmt") {
        if(name == "stmt.1" || name == "stmt.2") {
            // simple_stmt
            // compound_stmt
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "simple_stmt") {
        if(name == "simple_stmt.1" || name == "simple_stmt.2") {
            // small_stmt next_small_stmt SEMI_COLON NEWLINE
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "compound_stmt") {
        if(
            name == "compound_stmt.1" || name == "compound_stmt.2" || name == "compound_stmt.3" ||
            name == "compound_stmt.4" || name == "compound_stmt.5" || name == "compound_stmt.6"
        ) {
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "small_stmt") {
        if(name == "small_stmt.1" || name == "small_stmt.2" || name == "small_stmt.3" || name == "small_stmt.4" || name == "small_stmt.5" ) {
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "next_small_stmt") {
        if(name == "next_small_stmt.1") {
            // next_small_stmt SEMI_COLON small_stmt
            (root->children)[0]->T = root->T;
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[2]);
            if(flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
            );
        }
        else if(name == "next_small_stmt.2") {
            // empty production
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "stmt_helper") {
        switch((root->children).size()) {
            case 0: {
                // empty production
                deque<TypeExpression*> type;
                type.push_back(root->T);
                root->T = type_record(type);
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // stmt_helper COMMA NAME
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                string content = (root->children)[2]->content;
                int len = content.length();
                ASTNode* node = new ASTNode();
                flag = set_name_type(node, content, len);
                if(flag < 0) return flag;
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back(node->T);
                root->declarations = (root->children)[0]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // Features are not supported. Just type checking done for completeness.
    if(type == "global_stmt" || type == "nonlocal_stmt") {
        // GLOBAL NAME stmt_helper
        // NONLOCAL NAME stmt_helper
        string content = (root->children)[1]->content;
        int len = content.length();
        ASTNode* node = new ASTNode();
        flag = set_name_type(node, content, len);
        if(flag < 0) return flag;
        (root->children)[2]->T = node->T;
        flag = semantic_analysis_recursive((root->children)[2]);
        if(flag < 0) return flag;
        root->declarations = (root->children)[2]->declarations;
        root->T = (root->children)[2]->T;
        (root->T->fields).push_front(node->T);
    }

    // Feature not supported. Just type checking done for completeness.
    if(type == "assert_stmt") {
        if(name == "assert_stmt.1") {
            // ASSERT test COMMA test
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[3]);
            if(flag < 0) return flag;
            TypeExpression* T = type_checking_binary((root->children)[1], (root->children)[2]->content, (root->children)[3]);
            root->T = T;
            root->declarations = (root->children)[1]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
            );
        }
        else if(name == "assert_stmt.2") {
            // ASSERT test
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "expr_stmt") {
        if(name == "expr_stmt.1") {
            // testlist_star_expr annassign
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) return flag;

            string lexeme = (root->children)[0]->full_content;
            STentry* entry = add(lexeme, "NAME", (root->children)[1]->T, root->lineno, root->columnno, &flag);
            if(entry == NULL) {
                // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                string error_message = "Error in declaration of variable";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                return -1;
            }
            else if(flag > 0) {
                // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
            }

            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
            );
        }
        else if(name == "expr_stmt.2") {
            // testlist_star_expr AUGASSIGN testlist
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            flag = semantic_analysis_recursive((root->children)[2]);
            if(flag < 0) return flag;
            
            // SCOPE AND TYPE CHECKING
            // scope checking is not required because that would have been already done on "atom_expr" level.
            TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
            if(T == NULL) return -1;

            root->T = T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
            );
        }
        else if(name == "expr_stmt.3") {
            // testlist_star_expr continued_expr_stmt
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) return flag;
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "continued_expr_stmt") {
        if(name == "continued_expr_stmt.1") {
            // continued_expr_stmt EQUAL testlist_star_expr
            (root->children)[0]->T = root->T;
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
            if(T == NULL) return -1;
            root->T = T;
            root->declarations = (root->children)[0]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[2]->declarations).begin(), ((root->children)[2]->declarations).end()
            );
        }
        else if(name == "continued_expr_stmt.2") {
            // empty declaration
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "testlist_star_expr") {
        // cout << "Entered testlist_star_expr" << endl;
        if(
            name == "testlist_star_expr.1" || name == "testlist_star_expr.2" ||
            name == "testlist_star_expr.3" || name == "testlist_star_expr.4"
        ) {
            // test continued_testlist COMMA
            // test continued_testlist
            // star_expr continued_testlist COMMA
            // star_expr continued_testlist
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) return flag;
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Check the semantic analysis for a simple statement
    if(type == "flow_stmt") {
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        if(name == "flow_stmt.1" || name == "flow_stmt.2" || name == "flow_stmt.3") {
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
                           
    }

    // Check the semantic analysis for a simple statement
    if(type == "break_stmt") {
        // BREAK
        // No need for any type system code here
        root->T = type_void();
        root->declarations = vector<STentry*>();
    }

    // Check the semantic analysis for a simple statement
    if(type == "continue_stmt") {
        // CONTINUE
        // No need for any type system code here
        root->T = type_void();
        root->declarations = vector<STentry*>();
    }

    // Check the semantic analysis for a simple statement
    if(type == "return_stmt") {
        if(name == "return_stmt.1") {
            // RETURN testlist
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else if(name == "return_stmt.2") {
            // RETURN
            root->T = type_void();
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Not supported but written here completeness of type systems.
    if(type == "raise_stmt") {
        if(name == "return_stmt.1") {
            // RAISE test FROM test
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[3]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            TypeExpression* T = type_checking_binary((root->children)[1], (root->children)[2]->content, (root->children)[3]);
            root->T = T;
            root->declarations = (root->children)[1]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
            );
        }
        else if(name == "return_stmt.2") {
            // RAISE test
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else if(name == "return_stmt.3") {
            // RAISE
            root->T = type_void();
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Included for the completeness of type systems but is not supported.
    if(type == "try_stmt") {
        if(name == "try_stmt.1") {
            // TRY COLON suite except_stmt else_stmt finally_stmt
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[3]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[4]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[5]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[2]->T;
            root->declarations = (root->children)[2]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
            );
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[4]->declarations).begin(), ((root->children)[4]->declarations).end()
            );
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[5]->declarations).begin(), ((root->children)[5]->declarations).end()
            );
        }
        else if(name == "try_stmt.2") {
            // TRY COLON suite FINALLY COLON suite
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[5]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[2]->T;
            root->declarations = (root->children)[2]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[5]->declarations).begin(), ((root->children)[5]->declarations).end()
            );
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Included for the completeness of type systems but is not supported.
    if(type == "except_stmt") {
        if(name == "except_stmt.1") {
            // except_stmt except_clause COLON suite
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[3]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[3]->T;
            root->declarations = (root->children)[3]->declarations;
        }
        else if(name == "except_stmt.2") {
            // except_clause COLON suite
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[2]->T;
            root->declarations = (root->children)[2]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Included for the completeness of type systems but is not supported.
    if(type == "finally_stmt") {
        if(name == "finally_stmt.1") {
            // FINALLY COLON suite
            flag = semantic_analysis_recursive((root->children)[2]);
            if(flag < 0) return flag;
            root->T = (root->children)[2]->T;
            root->declarations = (root->children)[2]->declarations;
        }
        else if(name == "finally_stmt.2") {
            // %empty
            root->T = type_void();
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    // Included for the completeness of type systems but is not supported.
    if(type == "except_clause") {
        // EXCEPT test AS NAME
        if(name == "except_clause.1") {
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else if(name == "except_clause.2") {
            // EXCEPT test
            flag = semantic_analysis_recursive((root->children)[1]);
            if(flag < 0) return flag;
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else if(name == "except_clause.3") {
            // EXCEPT
            root->T = type_void();
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(type == "for_stmt") {
        // FOR exprlist IN testlist COLON suite else_stmt
        flag = semantic_analysis_recursive((root->children)[1]);
        if(flag < 0) return flag;
        flag = semantic_analysis_recursive((root->children)[3]);
        if(flag < 0) return flag;
        root->T = type_bool();

        flag = incr_scope(OTHER_SCOPE, "FOR", root->T);
        if(flag < 0) return flag;
        flag = semantic_analysis_recursive((root->children)[5]);
        if(flag < 0) return flag;
        flag = decr_scope();
        if (flag < 0) return flag;
        (root->table) = (root->children)[5]->table;

        flag = semantic_analysis_recursive((root->children)[6]);
        if(flag < 0) return flag;

        root->declarations = (root->children)[5]->declarations;
    }

    if(type == "while_stmt") {
        // WHILE test COLON suite else_stmt
        flag = semantic_analysis_recursive((root->children)[1]);
        if(flag < 0) return flag;
        root->T = type_bool();

        flag = incr_scope(OTHER_SCOPE, "WHILE", root->T);
        if(flag < 0) return flag;
        flag = semantic_analysis_recursive((root->children)[3]);
        if(flag < 0) return flag;
        flag = decr_scope();
        if(flag < 0) return flag;
        (root->table) = (root->children)[3]->table;

        flag = semantic_analysis_recursive((root->children)[4]);
        if(flag < 0) return flag;

        root->declarations = (root->children)[3]->declarations;
    }

    if(type == "else_stmt") {
        switch ((root->children).size()) {
            case 3: {
                // ELSE COLON suite
                root->T = type_bool();
                
                flag = incr_scope(OTHER_SCOPE, "ELSE", root->T);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                flag = decr_scope();
                if(flag < 0) return flag;
                (root->table) = (root->children)[2]->table;

                root->declarations = (root->children)[2]->declarations;
                break;
            }
            case 0: {
                // empty production
                root->T = type_void();
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "elif_stmt") {
        switch ((root->children).size()) {
            case 5: {
                // elif_stmt ELIF test COLON suite
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                root->T = type_bool();

                flag = incr_scope(OTHER_SCOPE , "ELIF", root->T);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[4]);
                if(flag < 0) return flag;
                flag = decr_scope();
                if(flag < 0) return flag;
                (root->table) = (root->children)[4]->table;

                root->declarations = (root->children)[4]->declarations;
                break;
            }
            case 0: {
                // empty production
                root->T = type_void();
                root->declarations = vector<STentry*>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "if_stmt") {
        // IF test COLON suite elif_stmt else_stmt
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = type_bool();
        
        flag = incr_scope(OTHER_SCOPE, "IF", root->T);
        if(flag < 0) return flag;
        flag = semantic_analysis_recursive((root->children)[3]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        flag = decr_scope();
        if(flag < 0) return flag;
        (root->table) = (root->children)[3]->table;
        
        flag = semantic_analysis_recursive((root->children)[4]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        flag = semantic_analysis_recursive((root->children)[5]);
        if (flag < 0) {
            // cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }

        root->declarations = (root->children)[3]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[4]->declarations).begin(), ((root->children)[4]->declarations).end()
        );
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[5]->declarations).begin(), ((root->children)[5]->declarations).end()
        );
    }

    // Check the semantic analysis for a simple statement
    if(type == "annassign") {
        switch((root->children).size()) {
            case 4: {
                // COLON test EQUAL test
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[3]);
                if (flag < 0) return flag;

                // SCOPE AND TYPE CHECKING
                // scope checking is not required because that would have been already done on "atom_expr" level.
                int type_check_flag = type_check_with_typecast((root->children)[1]->T, (root->children)[3]->T);
                if(type_check_flag != 1) {
                    // cout << "Semantic error from annassign\n";
                    semantic_error_type((root->children)[1], "=", (root->children)[3]);
                    return -1;
                }

                root->T = (root->children)[1]->T;
                root->declarations = (root->children)[1]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
                );
                break;
            }
            case 2: {
                // COLON test
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) return flag;
                
                // SCOPE AND TYPE CHECKING
                // Nothing required because everything inside the "test" non-terminal would have been already checked.
                root->T = (root->children)[1]->T;
                root->declarations = (root->children)[1]->declarations;
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if(type == "suite") {
        if(name == "suite.1") {
            // simple_stmt
            flag = semantic_analysis_recursive((root->children)[0]);
            if(flag < 0) return flag;
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
        }
        else if(name == "suite.2") {
            // NEWLINE INDENT stmts DEDENT
            flag = semantic_analysis_recursive((root->children)[2]);
            if(flag < 0) return flag;
            if((root->children)[2]->T->type == TYPE_RECORD) root->T = (root->children)[2]->T;
            else {
                deque<TypeExpression*> type;
                type.push_back((root->children)[2]->T);
                root->T = type_record(type);
            }
            root->declarations = (root->children)[2]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
        DEBUG_TYPE_CONTROL_FLOW.pop();
        cout << "[TYPE SYSTEM]: Exiting semantic analysis for " << type << " non terminal with " << name << " production.";
        cout << " Call: " << local_debug_counter;
        if(!DEBUG_TYPE_CONTROL_FLOW.empty()) cout << " Traceback: " << DEBUG_TYPE_CONTROL_FLOW.top();
        cout << "\n";
    }
    return 0;
}

// This is the function called from COMPILER MAIN for semantic analysis
int semantic_analysis() {
    ErrorMsg = new SemanticError();
    currTable = new SymbolTable();
    globalTable = currTable;
    int flag = semantic_analysis_recursive(root);
    return flag;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/


#endif // TYPES_CPP
