#ifndef TYPES_CPP
#define TYPES_CPP

#include <iostream>
#include <vector>
#include <string>
#include <stdarg.h>
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
extern SemanticError* ErrorMsg;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

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

TypeExpression* type_print() {
    // A support for only one primitive type at a time
    TypeExpression* T = type_bool();
    vector<TypeExpression*> fields;
    fields.push_back(T);
    TypeExpression* domain = type_record(fields);
    TypeExpression* range = type_void();
    TypeExpression* print = type_function(domain, range);
    return print;
}

TypeExpression* type_range() {
    // A support for only one primitive type integer
    TypeExpression  *T1 = type_int(), *T2 = type_int();
    vector<TypeExpression*> fields;
    fields.push_back(T1);
    TypeExpression* domain = type_record(fields);
    TypeExpression* range = type_array(0, T2);
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
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_NOT_FOUND: {
                fprintf(stderr, "[SEMANTIC ERROR]: DECLARATION MISSING\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_SCOPE: {
                fprintf(stderr, "[SEMANTIC ERROR]: SYMBOL NOT DEFINED IN THIS SCOPE\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_WRONG_PARAMS: {
                fprintf(stderr, "[SEMANTIC ERROR]: FUNCTION PARAMETERS ARE WRONG\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_TYPECAST: {
                fprintf(stderr, "[SEMANTIC ERROR]: IMPLICIT TYPE CASTING NOT SUPPORTED\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_BOUNDS: { // This is a runtime error so this error would not actually happen in the compile time
                fprintf(stderr, "[SEMANTIC ERROR]: ARRAY ACESS ARE OUT OF BOUNDS\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_WRG_USE: { // Actually this is an internal compilation error so the control may not come inside this function for this case.
                fprintf(stderr, "[SEMANTIC ERROR]: WRONG USAGE OF INTERNAL SYMBOL TABLE FUNCTIONS\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_UNDF: {
                fprintf(stderr, "[SEMANTIC ERROR]: ERROR NOT KNOWN\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case ERR_OTHER: {
                fprintf(stderr, "[SEMANTIC ERROR]: SEMANTIC ERROR FOUND IN THE PROGRAM\n");
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>(msg.c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
                fprintf(stderr, "[SEMANTIC ERROR]: Error occured near column %d on line %d\n", columnno, lineno);
                break;
            }

            case WARNING: {
                fprintf(stderr, "[SEMANTIC WARNING]: SAME type USED TWICE IN SAME SCOPE. EARLIER DECLARATION IS OVERSHADOWED BY LATTER\n");
                fprintf(stderr, "[SEMANTIC WARNING]: %s\n", const_cast<char*>((ErrorMsg->msg).c_str()));
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
    fprintf(stderr, "[SEMANTIC TYPE ERROR]: %s\n", const_cast<char*>(msg.c_str()));
    fprintf(stderr, "[SEMANTIC TYPE ERROR]: Error occured near line %d on column %d\n", lineno, columnno);
    return;
}

// This function returns Type in case of correct types NULL in case of error.
// A limited implicit type casting is implemented here however this is not as required as such.
TypeExpression* type_checking_unary(string optr, ASTNode* operand) {
    // Basic binary operations are not supported on any other types
    // except the 4 basic types of INT, FLOAT, BOOL and STRING
    int type = operand->T->type;
    if(type != TYPE_INT && type != TYPE_FLOAT && type != TYPE_BOOL && type != TYPE_STR) {
        semantic_error_type(operand, optr);
        return NULL;
    }

    if (
        // Output will be the computation result
        optr == "+" || optr == "-" || optr == "~"
    )
    {
        if(type == TYPE_STR) {
            // This operation is not supported for arithmetic types
            semantic_error_type(operand, optr);
            return NULL;
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
            semantic_error_type(operand, optr);
            return NULL;
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
            semantic_error_type(operand, optr);
            return NULL;
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
    int type1 = operand1->T->type, type2 = operand2->T->type;

    // Case of comparison operators
    if(
        optr == "in" || optr == "not-in" // These come under comp_op non terminal
    ) {
        if(type2 != TYPE_ARRAY && type2 != TYPE_RECORD) {
            semantic_error_type(operand1, optr, operand2);
            return NULL;
        }
        else if(type2 == TYPE_ARRAY) {
            int num = type_check(operand2->T->array, operand1->T);
            if(num==1) return type_bool();
            else {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
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
        semantic_error_type(operand1, optr, operand2);
        return NULL;
    }
    if(type2 != TYPE_INT && type2 != TYPE_FLOAT && type2 != TYPE_BOOL && type2 != TYPE_STR) {
        semantic_error_type(operand1, optr, operand2);
        return NULL;
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
        // cout << "here\n";
        if(type1 == type2) {
            if(type1 == TYPE_STR && type2 == TYPE_STR) {
                // MINOR SUPPORT PROVIDED FOR STRING OPERATIONS
                // This operation is not supported for arithmetic types
                // semantic_error_type(operand1, optr, operand2);
                // return NULL;

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
                semantic_error_type(operand1, optr, operand2);
                return NULL;
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
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_INT) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_BOOL) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_FLOAT) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
        }
    }

    if (
        // These are shift operators which should have 2nd operand as an integer only
        // Output will be the computation result
        optr == "<<" || optr == ">>"
    )
    {
        // cout << "here\n";
        if(type2 == TYPE_STR || type2 == TYPE_FLOAT) {
            semantic_error_type(operand1, optr, operand2);
            return NULL;
        }
        
        if(type1 == type2) {
            if(type1 == TYPE_STR && type2 == TYPE_STR) {
                // This operation is not supported for arithmetic types
                semantic_error_type(operand1, optr, operand2);
                return NULL;
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
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_BOOL) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
        }
    }

    if (
        // These are relational operators which give boolean as the output
        optr == "==" || optr == "!=" || optr == ">" || optr == ">=" || optr == "<" || optr == "<=" ||
        optr == "is-not" || optr == "is" // These come under comp_op non terminal
    )
    {
        // cout << "here\n";
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
                semantic_error_type(operand1, optr, operand2);
                return NULL;
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
                semantic_error_type(operand1, optr, operand2);
                return NULL;
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
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_INT) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_BOOL) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
            }
            if(type1 == TYPE_STR && type2 == TYPE_FLOAT) {
                semantic_error_type(operand1, optr, operand2);
                return NULL;
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
            semantic_error_type(operand1, optr, operand2);
            return NULL;
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

// Set the type and delcarations for the NAME terminal
int set_name_type(ASTNode* root, string content, int len) {
    // cout << "HELLO THIS IS IN SET_NAME_TYPE for = " << content << "\n";
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
    else {
        // This is a new NAME not predefined in compiler
        root->T = type_void();
        root->declarations = vector<STentry*>();
        
        // SCOPE CHECKING AND USER DEFINITION REQUIRED HERE
        // cout << "lookup started" << "\n";
        // STentry* entry = lookup(content, NULL);
        // if(entry == NULL) {
        //     cout << "No such entry is found" << "\n";
        //     root->T = type_void();
        //     root->declarations = vector<STentry*>();
        // }
        // else {
        //     cout << "Oh my god this is a user defined type" << "\n";
        //     root->T = entry->symbol_type;
        //     root->declarations = vector<STentry*>();
        // }
    }

    // THIS CASE IS NOT REQUIRED
    // else if(content == "range") {
    //     root->T = type_range();
    //     root->declarations = vector<STentry*>();
    // }
    // else if(content == "print") {
    //     root->T = type_print();
    //     root->declarations = vector<STentry*>();
    // }

    return 0;
}

int semantic_analysis_recursive(struct ASTNode* root) {
    string type = (root->type);
    string name = (root->name);
    int flag = 0;

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
                root->T = type_record(vector<TypeExpression*>());
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
                    // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                    // cout << "Some other error happened" << "\n";
                    semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
                }

                // Construct symbol table for functions
                incr_scope(FUNC_SCOPE, lexeme, T);
                flag = semantic_analysis_recursive((root->children)[4]);
                if(flag < 0) return flag;
                decr_scope();

                // cout << "Funcdef is done" << "\n";

                root->T = T;
                root->declarations = (root->children)[4]->declarations;

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
                incr_scope(FUNC_SCOPE, lexeme, T);
                flag = semantic_analysis_recursive((root->children)[6]);
                if(flag < 0) return flag;
                decr_scope();
                
                root->T = T;
                root->declarations = (root->children)[6]->declarations;
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
                root->T = type_record(vector<TypeExpression*>());
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // OPENING_BRACKET typedargslist CLOSING_BRACKET
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
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

    if(type == "typedargslist") {
        switch((root->children).size()) {
            case 5: {
                // tfpdef EQUAL test next_arg COMMA
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[3]);
                if(flag < 0) return flag;
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                root->T = type_record(vector<TypeExpression*>());
                (root->T->fields).push_back(T);
                (root->T->fields).insert(
                    (root->T->fields).end(),
                    ((root->children)[3]->T->fields).begin(), ((root->children)[3]->T->fields).end()
                );
                root->declarations = vector<STentry*>();
                break;
            }
            case 4: {
                // tfpdef EQUAL test next_arg
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[3]);
                if(flag < 0) return flag;
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                root->T = type_record(vector<TypeExpression*>());
                (root->T->fields).push_back(T);
                (root->T->fields).insert(
                    (root->T->fields).end(),
                    ((root->children)[3]->T->fields).begin(), ((root->children)[3]->T->fields).end()
                );
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // tfpdef next_arg COMMA
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
                TypeExpression* T = (root->children)[0]->T;
                root->T = type_record(vector<TypeExpression*>());
                (root->T->fields).push_back(T);
                (root->T->fields).insert(
                    (root->T->fields).end(),
                    ((root->children)[3]->T->fields).begin(), ((root->children)[3]->T->fields).end()
                );
                root->declarations = vector<STentry*>();
                break;
            }
            case 2: {
                // tfpdef next_arg
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[1]);
                if(flag < 0) return flag;
                TypeExpression* T = (root->children)[0]->T;
                root->T = type_record(vector<TypeExpression*>());
                (root->T->fields).push_back(T);
                (root->T->fields).insert(
                    (root->T->fields).end(),
                    ((root->children)[3]->T->fields).begin(), ((root->children)[3]->T->fields).end()
                );
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

    if(type == "next_arg") {
        switch((root->children).size()) {
            case 5: {
                // next_arg COMMA tfpdef EQUAL test
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
                break;
            }
            case 3: {
                // next_arg COMMA tfpdef
                flag = semantic_analysis_recursive((root->children)[0]);
                if(flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                TypeExpression* T = (root->children)[2]->T;
                root->T = (root->children)[0]->T;
                (root->T->fields).push_back(T);
                root->declarations = vector<STentry*>();
                break;
            }
            case 0: {
                // %empty
                root->T = type_record(vector<TypeExpression*>());
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
        switch((root->children).size()) {
            case 3: {
                // NAME COLON test
                flag = semantic_analysis_recursive((root->children)[2]);
                if(flag < 0) return flag;
                root->T = (root->children)[2]->T;
                root->declarations = (root->children)[2]->declarations;
                break;
            }
            case 1: {
                // NAME
                string content = (root->children)[0]->content;
                int len = content.length();
                set_name_type(root, content, len);
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
        switch((root->children).size()) {
            case 7: {
                // CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite
                flag = semantic_analysis_recursive((root->children)[3]);
                if(flag < 0) return flag;
                string lexeme = (root->children)[1]->content;

                incr_scope(CLASS_SCOPE, lexeme, NULL);
                flag = semantic_analysis_recursive((root->children)[6]);
                if(flag < 0) return flag;
                decr_scope();

                vector<STentry*> decs_in_suite = (root->children)[6]->declarations;
                vector<TypeExpression*> elements;
                for(int i=0; i<decs_in_suite.size(); i++) {
                    TypeExpression* ent = decs_in_suite[i]->symbol_type;
                    elements.push_back(ent);
                }
                TypeExpression* arglist_type = (root->children)[3]->T;
                TypeExpression* T = type_record(elements, 1, arglist_type->fields);
                
                STentry* entry = add(lexeme, "CLASS", T, root->lineno, root->columnno, &flag);
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

                break;
            }
            case 6: {
                // CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite
                string lexeme = (root->children)[1]->content;

                incr_scope(CLASS_SCOPE, lexeme, NULL);
                flag = semantic_analysis_recursive((root->children)[5]);
                if(flag < 0) return flag;
                decr_scope();

                vector<STentry*> decs_in_suite = (root->children)[5]->declarations;
                vector<TypeExpression*> elements;
                for(int i=0; i<decs_in_suite.size(); i++) {
                    TypeExpression* ent = decs_in_suite[i]->symbol_type;
                    elements.push_back(ent);
                }
                TypeExpression* T = type_record(elements, 1, vector<TypeExpression*>());
                STentry* entry = add(lexeme, "CLASS", T, root->lineno, root->columnno, &flag);
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
                break;
            }
            case 4: {
                // CLASS NAME COLON suite
                string lexeme = (root->children)[1]->content;

                incr_scope(CLASS_SCOPE, lexeme, NULL);
                flag = semantic_analysis_recursive((root->children)[3]);
                if(flag < 0) return flag;
                decr_scope();

                vector<STentry*> decs_in_suite = (root->children)[3]->declarations;
                vector<TypeExpression*> elements;
                for(int i=0; i<decs_in_suite.size(); i++) {
                    TypeExpression* ent = decs_in_suite[i]->symbol_type;
                    elements.push_back(ent);
                }
                TypeExpression* T = type_record(elements, 1, vector<TypeExpression*>());
                STentry* entry = add(lexeme, "CLASS", T, root->lineno, root->columnno, &flag);
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
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "comp_if") {
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

                // no symbol table entry to be made here
                break;
            }
            case 2: {
                // IF test_nocond
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

    if (type == "comp_for") {
        switch ((root->children).size()) {
            case 5: {
                // FOR exprlist IN or_test comp_iter
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[3]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[4]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[3]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

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

    if (type == "comp_iter") {
        // comp_if
        // comp_for
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if (type == "argument") {
        switch ((root->children).size()) {
            case 3: {
                // test EQUAL test
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
                root->T = T;
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                );
                break;
            }
            case 2: {
                if ((root->children)[0]->type == "DOUBLE_STAR" || (root->children)[0]->type == "STAR") {
                    // DOUBLE_STAR test
                    // STAR test
                    flag = semantic_analysis_recursive((root->children)[1]);
                    if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                    flag = semantic_analysis_recursive((root->children)[1]);
                    if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

    if (type == "continued_argument") {
        switch ((root->children).size()) {
            case 3: {
                // continued_argument COMMA argument
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

                // set the type of argument
                root->T = (root->children)[2]->T;
                root->declarations = (root->children)[2]->declarations;
                break;
            }
            case 0: {
                // empty production
                root->T = type_void();
                root->declarations = vector<STentry *>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "arglist") {
        // argument continued_argument COMMA
        // argument continued_argument
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = type_record(vector<TypeExpression*>());
        (root->T->fields).push_back((root->children)[0]->T);
        
        root->declarations = (root->children)[0]->declarations;
    }

    if(type == "continued_dictorset") {
        // ignored this case
    }

    if (type == "dictorsetmaker") {
        // ignored this case
    }

    // doubt
    if (type == "continued_comma_test") {
        switch ((root->children).size()) {
            case 3: {
                // continued_comma_test COMMA test
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0)
                    return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0)
                    return flag;

                // set the type of test
                root->T = (root->children)[2]->T;
                root->declarations = (root->children)[2]->declarations;
                break;
            }
            case 0: {
                // empty production
                root->T = type_void();
                root->declarations = vector<STentry *>();
                break;
            }
            default: {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // doubt
    if (type == "testlist")
    {
        switch ((root->children).size())
        {
        case 3:
        {
            // test continued_comma_test COMMA
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0)
                return flag;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0)
                return flag;

            // set the type of test
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
            break;
        }
        case 2:
        {
            // test continued_comma_test
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0)
                return flag;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0)
                return flag;

            // set the type of test
            root->T = (root->children)[0]->T;
            root->declarations = (root->children)[0]->declarations;
            break;
        }
        default: 
            {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    // ignored the production: continued_exprlist COMMA star_expr
    if (type == "continued_exprlist")
    {
        switch ((root->children).size())
        {
        case 3:
        {
            // continued_exprlist COMMA expr
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0)
                return flag;
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0)
                return flag;

            // set the type of expr
            root->T = (root->children)[2]->T;
            root->declarations = (root->children)[2]->declarations;
            break;
        }
        case 0:
        {
            // empty production
            root->T = type_void();
            root->declarations = vector<STentry *>();
            break;
        }
        default: 
            {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "exprlist")
    {
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0)
            return flag;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0)
            return flag;

        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if (type == "sliceop")
    {
        // ignored
    }

    // doubt
    if (type == "subscript")
    {
        // ignored
    }

    if (type == "continued_subscript")
    {
        switch ((root->children).size())
        {
        case 3:
        {
            // continued_subscript COMMA subscript
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0)
                return flag;
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0)
                return flag;

            // set the type of subscript
            root->T = (root->children)[2]->T;
            root->declarations = (root->children)[2]->declarations;
            break;
        }
        case 0:
        {
            // empty production
            root->T = type_void();
            root->declarations = vector<STentry *>();
            break;
        }
        default: 
            {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
        }
    }

    if (type == "subscriptlist")
    {
        // ignored for now
    }

    if (type == "testlist_comp")
    {
        // ignored
    }

    if (type == "strings") {
        switch ((root->children).size()) {
            case 2: {
                // strings STRING
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

    if (type == "atom") {
        switch ((root->children).size()) {
            case 3: {
                // OPENING_BRACKET testlist_comp CLOSING_BRACKET
                // OPENING_CURLY_BRACKET dictorsetmaker CLOSING_CURLY_BRACKET
                // OPENING_SQ_BRACKET testlist_comp CLOSING_SQ_BRACKET
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                        cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                        return flag;
                    }
                root->T = (root->children)[1]->T;
                root->declarations = (root->children)[1]->declarations;
                break;
            }
            case 2: {
                // OPENING_BRACKET CLOSING_BRACKET
                // OPENING_SQ_BRACKET CLOSING_SQ_BRACKET
                // OPENING_CURLY_BRACKET CLOSING_CURLY_BRACKET
                root->T = type_void();
                root->declarations = vector<STentry*>();
                break;
            }
            case 1: {
                if((root->children)[0]->type == "NAME") {
                    // NAME
                    string content = (root->children)[0]->content;
                    // cout << "In atom with " << content << "\n";
                    int len = content.length();
                    set_name_type(root, content, len);
                    // cout << "This is from ATOM and this results in NAME of type = " << (root->T->encode) << "\n";
                }
                else if((root->children)[0]->type == "NUMBER") {
                    // NUMBER
                    // It can be any type of number but this will be handled later in type castings for now we consider integers and floating point
                    // IMAGINARY NUMBERS ARE NOT SUPPORTED
                    root->T = type_int();
                    root->declarations = vector<STentry*>();
                }
                else if ((root->children)[0]->type == "ELLIPSES_LITERAL") {
                    // ELLIPSES_LITERAL - No support provided for this
                    root->T = type_void();
                    root->declarations = vector<STentry*>();
                }
                else if ((root->children)[0]->type == "TOKEN_TRUE") {
                    // TOKEN_TRUE
                    root->T = type_bool();
                    root->declarations = vector<STentry*>();
                }
                else if ((root->children)[0]->type == "TOKEN_FALSE") {
                    // TOKEN_FALSE
                    root->T = type_bool();
                    root->declarations = vector<STentry*>();
                }
                else if ((root->children)[0]->type == "TOKEN_NONE") {
                    // TOKEN_NONE
                    root->T = type_void();
                    root->declarations = vector<STentry*>();
                }
                else {
                    // strings
                    flag = semantic_analysis_recursive((root->children)[0]);
                    if (flag < 0) {
                        cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                        return flag;
                    }
                    int len = (root->children)[0]->content.length();
                    root->T = (root->children)[0]->T;
                    root->declarations = (root->children)[0]->declarations;
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

    if (type == "trailers") {
        switch ((root->children).size()) {
            case 2: {
                // trailers trailer
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << " in trailers " << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << " in trailer " << "\n";
                    return flag;
                }
                int type1 = (root->children)[0]->T->type, type2 = (root->children)[1]->T->type;
                root->content = (root->children)[0]->content + (root->children)[1]->content;
                
                // Type setting for "trailers"
                if(type1 == TYPE_VOID && type2 == TYPE_VOID) root->T = type_void();
                else if(type1 == TYPE_VOID && type2 == TYPE_RECORD) root->T = (root->children)[1]->T;
                else if(type1 == TYPE_RECORD && type2 == TYPE_VOID) {
                    // This kind of case is difficult to handle. NOT SUPPORTED
                    root->T = (root->children)[0]->T;
                }
                else {
                    root->T = (root->children)[0]->T;
                    (root->T->fields).insert(
                        (root->T->fields).end(),
                        ((root->children)[1]->T->fields).begin(), ((root->children)[1]->T->fields).end()
                    );
                }

                // Concatenate declarations for the "trailers"
                root->declarations = (root->children)[0]->declarations;
                (root->declarations).insert(
                    (root->declarations).end(),
                    ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
                );
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

    if (type == "trailer") {
        switch ((root->children).size()) {
            case 3: {
                // OPENING_BRACKET arglist CLOSING_BRACKET
                // OPENING_SQ_BRACKET subscriptlist CLOSING_SQ_BRACKET
                // A function denoted by this trailer
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[1]->T;
                root->declarations = (root->children)[1]->declarations;
                break;
            }
            case 2: {
                if ((root->children)[0]->type == "DOT") {
                    // DOT NAME
                    // A class name denoted by this
                    root->T = type_void();
                    root->declarations = vector<STentry*>();
                    root->content = (root->children)[0]->content + (root->children)[1]->content;
                }
                else {
                    // OPENING_BRACKET CLOSING_BRACKET
                    // A function denoted by this trailer
                    root->T = type_record(vector<TypeExpression*>());
                    root->declarations = vector<STentry*>();
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

    if (type == "atom_expr") {
        if(name == "atom_expr.1") {
            // AWAIT atom trailers
            // Case not supported for this AWAIT
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            // cout << "In atom_expr with " << (root->full_content);
            deque<ASTNode*> trailers = ((root->children)[2]->children);
            
            // Type Setting for "atom_expr"
            if(trailers.size() == 0) root->T = (root->children)[1]->T;
            else if(trailers.size() == 2) {
                string content1 = (root->children)[1]->content, content2 = (root->children)[2]->content;
                (root->content) = content1 + content2;
                
                if((root->children)[2]->T->type == TYPE_RECORD) {
                    // This is a function call and the parameter list is available in "trailers"
                    // We cannot do type checking and scope checking here as we also need return type
                    TypeExpression* domain = (root->children)[2]->T;
                    (root->T) = type_function(domain, type_void());
                }
                else root->T = (root->children)[1]->T;
            }
            else {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
            
            root->declarations = vector<STentry*>();
        }
        else if(name == "atom_expr.2") {
            // atom trailers
            // The trailer can actually change the type of the atom
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            // cout << "In atom_expr with " << (root->full_content);
            deque<ASTNode*> trailers = ((root->children)[1]->children);
            
            // Type Setting for "atom_expr"
            if(trailers.size() == 0) root->T = (root->children)[0]->T;
            else if(trailers.size() == 2) {
                string content1 = (root->children)[0]->content, content2 = (root->children)[1]->content;
                (root->content) = content1 + content2;
                
                if((root->children)[1]->T->type == TYPE_RECORD) {
                    // This is a function call and the parameter list is available in "trailers"
                    // We cannot do type checking and scope checking here as we also need return type
                    TypeExpression* domain = (root->children)[1]->T;
                    (root->T) = type_function(domain, type_void());
                }
                else root->T = (root->children)[0]->T;
            }
            else {
                // This error should not happen of the parse tree is correctly constructed
                if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
                return -1;
            }
            
            root->declarations = vector<STentry*>();
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
        // cout << "Leaving atom_expr of " << (root->full_content);
    }

    if (type == "power") {
        switch ((root->children).size()) {
            case 3: {
                // atom_expr DOUBLE_STAR factor
                // DOUBLE_STAR is the exponential expression here
                // Type Checking will be required
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

    if (type == "comparison_stmt") {
        switch ((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // comparison_stmt comp_op expr
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                string optr = (root->children)[1]->full_content;
                // cout << (root->children)[0]->T->encode << " " << (root->children)[2]->T->encode << "\n";
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
        // cout << "Returned from expression with flag = " << flag << "\n";
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        // cout << (root->children)[0]->full_content << " ";
        // cout << (root->children)[1]->full_content << "\n";
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        // cout << "Returned from continued_stmt with for " << (root->children)[0]->full_content + (root->children)[1]->full_content << "\n";
        root->T = (root->children)[1]->T;
        root->declarations = (root->children)[0]->declarations;
        (root->declarations).insert(
            (root->declarations).end(),
            ((root->children)[1]->declarations).begin(), ((root->children)[1]->declarations).end()
        );
        // cout << "here\n";
    }

    if (type == "not_test") {
        switch ((root->children).size()) {
            case 2: {
                // NOT not_test
                flag = semantic_analysis_recursive((root->children)[1]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                // cout << "here" << "\n";
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
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        // cout << "here" << "\n";
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        // cout << "here" << "\n";
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
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // continued_and_test AND not_test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                cout << "here" << "\n";
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        (root->children)[1]->T = (root->children)[0]->T;
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // continued_or_test OR and_test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = (root->children)[0]->T;
        root->declarations = (root->children)[0]->declarations;
    }

    if (type == "test") {
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
                // cout << "Going inside test non terminal" << "\n";
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                // cout << "here in test -> or_test after return from or_test" << "\n";
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
        // cout << "stmts called\n";
        switch ((root->children).size()) {
            case 2: {
                // stmts stmt
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[0]->T;
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
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

    // Check the semantic analysis for a statement
    if(type == "stmt") {
        if(name == "stmt.1" || name == "stmt.2") {
            // simple_stmt
            // cout << "Statement non terminal is called\n";
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
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
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
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
            if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
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
            // cout << "Going inside expr_stmt" << "\n";
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            // cout << "Out of expr_stmt" << "\n";
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
            if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
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

    if(type == "global_stmt") {
        // GLOBAL NAME stmt_helper
        string content = (root->children)[1]->content;
        int len = content.length();
        set_name_type(root, content, len);
        root->T = (root->children)[1]->T;
        flag = semantic_analysis_recursive((root->children)[2]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->declarations = (root->children)[2]->declarations;
    }

    if(type == "stmt_helper") {
        switch((root->children).size()) {
            case 0: {
                // empty production
                root->declarations = vector<STentry*>();
                break;
            }
            case 3: {
                // stmt_helper COMMA NAME
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[2]->T;
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

    // Check the semantic analysis for a simple statement
    if(type == "nonlocal_stmt") {
        // ignored
    }

    // Check the semantic analysis for a simple statement
    if(type == "assert_stmt") {
        // ignored
    }

    // Check the semantic analysis for a simple statement
    if(type == "expr_stmt") {
        // cout << "Inside expr_stmt" << (root->full_content) << "\n";
        if(name == "expr_stmt.1") {
            // testlist_star_expr annassign
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }

            string lexeme = (root->children)[0]->full_content;
            STentry* entry = add(lexeme, "NAME", (root->children)[1]->T, root->lineno, root->columnno, &flag);
            if(entry == NULL) {
                // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                // cout << "Error in adding entry" << "\n";
                string error_message = "Error in declaration of variable";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                return -1;
            }
            else if(flag > 0) {
                // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                // cout << "Some other error happened" << "\n";
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
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            } 
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }

            TypeExpression* T = type_checking_binary((root->children)[0], (root->children)[1]->content, (root->children)[2]);
            string lexeme = (root->children)[0]->full_content;
            STentry* entry = add(lexeme, "NAME", T, root->lineno, root->columnno, &flag);
            if(entry == NULL) {
                // Some error has occured in the Symbol Table. Handle this in Semantic error handling
                // cout << "Error in adding entry" << "\n";
                string error_message = "Error in declaration of variable";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
                return -1;
            }
            else if(flag > 0) {
                // Variable overloading or class overloading is done which will may not be intended. Issue a warning for this.
                // cout << "Some other error happened" << "\n";
                semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, "", flag);
            }
            
            // SCOPE CHECKING IS TO BE DONE HERE
            // STentry* entry = lookup(lexeme, NULL);
            // if(entry == NULL) {
            //     // Some error has occured in the Symbol Table. Handle this in Semantic error handling
            //     // cout << "Error in adding entry" << "\n";
            //     string error_message = "Scope Error occured in assignment\n";
            //     semantic_error_symbol(ErrorMsg->error_type, root->lineno, root->columnno, error_message);
            //     return -1;
            // }

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
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
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
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            flag = semantic_analysis_recursive((root->children)[2]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
        if(
            name == "testlist_star_expr.1" || name == "testlist_star_expr.2" ||
            name == "testlist_star_expr.3" || name == "testlist_star_expr.4"
        ) {
            // test continued_testlist COMMA
            // test continued_testlist
            // star_expr continued_testlist COMMA
            // star_expr continued_testlist
            flag = semantic_analysis_recursive((root->children)[0]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            (root->children)[1]->T = (root->children)[0]->T;
            flag = semantic_analysis_recursive((root->children)[1]);
            if (flag < 0) {
                cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                return flag;
            }
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
        }
        else {
            // This error should not happen of the parse tree is correctly constructed
            if(PARSER_DEBUG_INSIDE_VERBOSE) printf("[PARSING ERROR]: Error in parsing process encountered during semantic analysis\n");
            return -1;
        }
    }

    if (type == "continued_testlist") {
        switch ((root->children).size()) {
            case 3: {
                // continued_testlist COMMA test
                (root->children)[0]->T = root->T;
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) return flag;
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) return flag;

                // set the type of expr
                int num = ((root->children)[0]->children).size();
                if(num == 0) {
                    root->T = type_record(vector<TypeExpression*>());
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
                    ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
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

    // Check the semantic analysis for a simple statement
    if(type == "flow_stmt") {
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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
        // No need for any type system code here
        root->T = type_void();
        root->declarations = vector<STentry*>();
    }

    // Check the semantic analysis for a simple statement
    if(type == "continue_stmt") {
        // No need for any type system code here
        root->T = type_void();
        root->declarations = vector<STentry*>();
    }

    // Check the semantic analysis for a simple statement
    if(type == "return_stmt") {
        if(name == "return_stmt.1") {
            // RETURN testlist
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

    // Check the semantic analysis for a simple statement
    if(type == "raise_stmt") {
        if(name == "return_stmt.1") {
            // RAISE test FROM test
            root->T = (root->children)[1]->T;
            root->declarations = (root->children)[1]->declarations;
            (root->declarations).insert(
                (root->declarations).end(),
                ((root->children)[3]->declarations).begin(), ((root->children)[3]->declarations).end()
            );
        }
        else if(name == "return_stmt.2") {
            // RAISE test
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

    if(type == "try_stmt") {
        // ignored
    }

    if(type == "except_stmt") {
        // ignored
    }

    if(type == "finally_stmt") {
        // ignored
    }

    if(type == "except_clause") {
        // ignored
    }

    if (type == "forcheck") {
        // exprlist IN testlist
        flag = semantic_analysis_recursive((root->children)[0]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        flag = semantic_analysis_recursive((root->children)[2]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

        root->T = type_bool();
        incr_scope(OTHER_SCOPE, "", root->T);
        flag = semantic_analysis_recursive((root->children)[5]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        decr_scope();

        flag = semantic_analysis_recursive((root->children)[6]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

        root->declarations = (root->children)[5]->declarations;
    }

    if (type == "for_stmt") {
        // FOR forcheck COLON suite else_stmt
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = type_bool();

        incr_scope(OTHER_SCOPE, "FOR", root->T);
        flag = semantic_analysis_recursive((root->children)[3]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        decr_scope();

        flag = semantic_analysis_recursive((root->children)[4]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

        root->declarations = (root->children)[5]->declarations;
    }

    if (type == "while_stmt") {
        // WHILE test COLON suite else_stmt
        flag = semantic_analysis_recursive((root->children)[1]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        root->T = type_bool();

        incr_scope(OTHER_SCOPE, "WHILE", root->T);
        flag = semantic_analysis_recursive((root->children)[3]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
        decr_scope();

        flag = semantic_analysis_recursive((root->children)[4]);
        if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }

        root->declarations = (root->children)[3]->declarations;
    }

    if (type == "else_stmt") {
        switch ((root->children).size()) {
            case 3: {
                // ELSE COLON suite
                root->T = type_bool();
                
                incr_scope(OTHER_SCOPE, "ELSE", root->T);
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                decr_scope();

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
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = type_bool();

                incr_scope(OTHER_SCOPE , "ELIF", root->T);
                flag = semantic_analysis_recursive((root->children)[4]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                decr_scope();

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
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        root->T = type_bool();
        
        incr_scope(OTHER_SCOPE, "IF", root->T);
        flag = semantic_analysis_recursive((root->children)[3]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        decr_scope();
        // cout << "Returned from suite in if_test" << "\n";
        
        flag = semantic_analysis_recursive((root->children)[4]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
            return flag;
        }
        flag = semantic_analysis_recursive((root->children)[5]);
        if (flag < 0) {
            cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

                if((root->children)[3]->T->type == TYPE_FUNC) {
                    TypeExpression* domain = (root->children)[3]->T->domain;
                    TypeExpression* range = (root->children)[1]->T;
                    
                    // SCOPE CHECKING SHOULD BE DONE HERE
                    // type_scope_check((root->children))
                    (root->children)[3]->T = type_function(domain, range);
                    // string lexeme = "";
                    // STentry* entry = lookup(lexeme, (root->children)[3]->T);
                }
                else {
                    TypeExpression* T = type_checking_binary((root->children)[1], (root->children)[2]->content, (root->children)[3]);
                    if(T == NULL) return -1;
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
                // SCOPE CHECKING SHOULD BE DONE HERE
                // type_scope_check((root->children))
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

    if (type == "suite") {
        // cout << "Inside suite" << "\n";
        switch ((root->children).size()) {
            case 4: {
                // NEWLINE INDENT stmts DEDENT
                flag = semantic_analysis_recursive((root->children)[2]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
                    return flag;
                }
                root->T = (root->children)[2]->T;
                root->declarations = (root->children)[2]->declarations;
                break;
            }
            case 1: {
                // simple_stmt
                flag = semantic_analysis_recursive((root->children)[0]);
                if (flag < 0) {
                    cout << "Error taken inside " << (root->type) << " for " << (root->name) << "\n";
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

    return 0;
}

// This is the function called from COMPILER MAIN for semantic analysis
int semantic_analysis() {
    int flag = semantic_analysis_recursive(root);
    return flag;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/


#endif // TYPES_CPP
