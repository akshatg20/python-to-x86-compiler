#ifndef SYMBOL_TABLE_CPP
#define SYMBOL_TABLE_CPP

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>
#include <utility>
#include <string>
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
using namespace std;

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF SYMBOL TABLE *****************************/

// Write any assumptions that you take in the comment below
/*
1) The function "define_type()" must have been called before "ret_user_defined()" for a particular user type, for desired output.
2) Both of the above functions must be called only for a user-defined type
3) SemanticError* ErrorMsg should be initialized in the parse.y file
4) Not done any alignment while computing offsets
*/

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF SYMBOL TABLE *****************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.

extern int yylineno;
extern SemanticError* ErrorMsg;                         // Semantic Error Message
extern SymbolTable* currTable;                          // pointer to the current symbol table in use
extern SymbolTable* globalTable;                        // pointer to the root (global scope) symbol table
extern int current_scope;                               // maintains the current scope while parsing, initialized to zero
extern char* inputfile_path;                            // path of the source file

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.
int new_type_no = 9;                             // holds a unique type number for different user-defined types
unordered_map<int,TypeExpression*> numToType;    // hashes each unique type number to its Type Expression  
int SYMBOL_TABLE_DEBUG_INSIDE_VERBOSE = 0;
int SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE = 0;

string getLexemeName(string str, char delim);
string generateKey(string lexeme, string encoding = "");
int deleteEntry(string key);
int deleteEntryScope(string key);
STentry* lookupScope(string lexeme, TypeExpression* T = NULL);

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** MEMBER FUNCTIONS FOR STEntry **************************************************/

// Make constructor for the class
STentry::STentry() {
    this->symbol_type = NULL;
    this->scope_level = this->offset = 0;
    return;
}

// Make constructor for the class
STentry::STentry(string lexeme, TypeExpression* type, int lineno, int scope, string token, int column)
{
    this->symbol_type = type; 
    this->refPoints.push_back(lineno);
    this->scope_level = scope;
    this->token = token;
    this->srcfilepath = inputfile_path;
    this->column = column;

    // if entry is for a function
    if(type != NULL && type->type == TYPE_FUNC) {
        
        // if current table is CLASS_SCOPE
        if(currTable->type == CLASS_SCOPE) {
            string className = currTable->name;
            this->lexeme = className + "." + generateKey(lexeme,type->encode);
        }
        else {
            this->lexeme = generateKey(lexeme,type->encode);
        }
    }
    // if not a function
    this->lexeme = lexeme;

    return;
}

// function to add subsequent line nos of occurence of symbol
void STentry::addLineNo() {
    this->refPoints.push_back(yylineno);
}

void STentry::updatePDTValues(int ival, float fval, string strval) {
    this->var.ival = ival;
    this->var.fval = fval;
    this->var.strval = strval;
}

/*********************************** MEMBER FUNCTIONS FOR STEntry **************************************************/

/*********************************** MEMBER FUNCTIONS FOR SymbolTable **********************************************/

// Default Constructor
SymbolTable::SymbolTable() {
    this->parent = NULL;
    this->type = GLOBAL_SCOPE;
    this->name = "GLOBAL";
}

// Constructor
SymbolTable::SymbolTable(SymbolTable* parent, int flag, string name) {
    this->parent = parent;
    this->type = flag;
    this->name = name;
}

// function to dump the symbol table onto an external file
void SymbolTable::dumpST(FILE* outputFile, SymbolTable* table) {
    fprintf(outputFile,"--------------------,-------------------------,------------------------------------------------------------------------------------------,-------------\n");
    fprintf(outputFile,"LEXEME              ,TOKEN                    ,TYPE                                                                                      ,LINE_NO\n");
    fprintf(outputFile,"--------------------,-------------------------,------------------------------------------------------------------------------------------,-------------\n");


    unordered_map<string,STentry>::iterator it;
    unordered_map<string,STentry> currHashTable = table->hashTable;

    for(it = currHashTable.begin(); it != currHashTable.end(); it++) {
        // print the lexeme
        string name = getLexemeName(it->first,'$');
        char* name1 = const_cast<char*> (name.c_str());
        fprintf(outputFile, "%-21s,",name1);

        // print the token of the symbol
        string token = it->second.token;
        char* token1 = const_cast<char*> (token.c_str());
        fprintf(outputFile,"%-26s,",token1);

        // print the type of symbol
        string type = it->second.symbol_type->encode;
        char* type1 = const_cast<char*> (type.c_str());
        // printf("%s\n",type1);
        fprintf(outputFile,"%-91s,",type1);

        // print the line no of the symbol declaration
        vector<int> lines = it->second.refPoints;
        fprintf(outputFile,"%-10d,\n",lines.front());
    }
    fprintf(outputFile,"-------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

/*********************************** MEMBER FUNCTIONS FOR SymbolTable **********************************************/

/*********************************** MEMBER FUNCTIONS FOR TypeExpressions ******************************************/

TypeExpression::TypeExpression() {
    type = TYPE_UNDF;
    space = 0;
    number = -1;
    class_flag = 0;
    encode = "UNDEFINED";
    name = "";
    lexeme = NULL;
    array = domain = range = user_defined = NULL;
    inheritance = fields = vector<TypeExpression*>();
    return;
}

TypeExpression::TypeExpression (
    int tp,
    int num,
    vector<TypeExpression*> fields_arr,
    int size,
    int flag,
    vector<TypeExpression*> inherit
) {
    
    if(tp < 0) {
        // This is an erreneous case which should not occur
        if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Error in Type Expression calling\n");
        return;
    }
    
    switch(tp) {
        
        case TYPE_INT:    {
            type = TYPE_INT;
            space = sizeof(int); // Can change based on machine specifications
            number = -1;
            class_flag = 0;
            encode = "INTEGER";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }
        
        case TYPE_FLOAT:  {
            type = TYPE_FLOAT;
            space = sizeof(float); // Can change based on machine specifications
            number = -1;
            class_flag = 0;
            encode = "FLOATING-POINT";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }
        
        case TYPE_STR:    {
            if(size < 0) {
                // This is an erreneous case which should not occur
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Error in String size computation\n");
                return;
            }
            
            type = TYPE_STR;
            space = size;
            number = -1;
            class_flag = 0;
            encode = "STRING";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }
        
        case TYPE_BOOL:   {
            type = TYPE_BOOL;
            space = sizeof(bool); // Can change based on machine specifications
            number = -1;
            class_flag = 0;
            encode = "BOOLEAN";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }

        case TYPE_VOID:   {
            type = TYPE_VOID;
            // The below line imparts a warning under flag -Wpointer-arith so it is kept commented
            // space = sizeof(void); // Can change based on machine specifications
            space = 1;
            number = -1;
            class_flag = 0;
            encode = "NONE";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }
        
        case TYPE_UNDF:   {
            // An undefined type created by the Default Constructor
            TypeExpression();
            break;
        }
        
        case TYPE_ARRAY:  {
            if(num < 0) {
                // This is an erreneous case which should not occur
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Error in Array Declaration\n");
                return;
            }
            if(fields_arr.size() == 0) {
                // This is an erreneous case which should not occur
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Error in Array Declaration - Fields not passed correctly\n");
                return;
            }
            
            type = TYPE_ARRAY;
            array = fields_arr[0];
            space = num * (array->space);
            number = num;
            class_flag = 0;
            encode = "ARRAY(" + to_string(num) + string(";") + (array->encode) + string(")");
            name = "";
            lexeme = NULL;
            domain = range = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }

        case TYPE_FUNC:   {
            if(fields_arr.size() <= 1) {
                // This is an erreneous case which should not occur
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Error in Function Declaration - Fields not passed correctly\n");
                return;
            }
            
            type = TYPE_FUNC;
            domain = fields_arr[0];
            range = fields_arr[1];
            space = (domain->space) + (range->space); // Doubtful - What should be the space of the type of a function ?
            number = -1;
            class_flag = 0;
            encode = "FUNCTION(" + (domain->encode) + string("->") + (range->encode) + string(")");
            name = "";
            lexeme = NULL;
            array = user_defined = NULL;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }
        
        case TYPE_RECORD: {
            type = TYPE_RECORD;
            fields = fields_arr;
            space = 0;
            for(int i=0; i<fields.size(); i++) space += (fields[i]->space);
            number = -1;
            if(fields.size() == 0) encode = "RECORD()";
            else {
                encode = "RECORD(" + (fields[0]->encode);
                for(int i=1; i<fields.size(); i++) encode += (string(";") + (fields[i]->encode));
                encode += string(")");
            }
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;

            // In case of classes we will get the value of flag = 1
            if(flag == 1) {
                class_flag = 1;
                inheritance = inherit;
            }

            break;
        }
        
        default:          {
            // Case of a user defined type is to be handled by the help of the Symbol Table.
            // The symbol table will provide the pointer to TypeExpression for user defined type.
            TypeExpression* user = ret_user_defined(tp);
            if(user == NULL) TypeExpression(); // Will check this case in Semantic Analysis in the parser
            
            type = tp;
            space = (user->space);
            number = -1;
            class_flag = 0;
            encode = (user->name);
            name = "";
            lexeme = NULL;
            array = domain = range = NULL;
            user_defined = user;
            inheritance = fields = vector<TypeExpression*>();
            break;
        }
    }

    return;
}

int TypeExpression::update_space() {
    if(type == TYPE_VOID) {
        // The below line imparts a warning under flag -Wpointer-arith so it is kept commented
        // space = sizeof(void); // Can change based on machine specifications
        space = 1;
    }
    else if(type == TYPE_UNDF) space = 0;
    else if(type == TYPE_STR) {
        // In this case the entry from Symbol Table is needed to be checked.
        // That entry will tell the 
    }
    return space;
}

// Based on Type Equivalence on Pg 372 of DRAG Book
int TypeExpression::same_type(TypeExpression* T) {
    if(T == NULL) return -1;
    else if(T->type == TYPE_UNDF || type == TYPE_UNDF) return -1;
    else if(type >= 0 && type <= 7 && (T->type) >= 0 && (T->type) <= 7) {
        // Both the types are formed from pre-defined type constructors only and are not user defined.
        if(T->type == TYPE_BOOL || T->type == TYPE_FLOAT || T->type == TYPE_INT || T->type == TYPE_STR || T->type == TYPE_VOID) {
            if(type == T->type) return 1;
            else return 0;
        }
        else if(type == TYPE_BOOL || type == TYPE_FLOAT || type == TYPE_INT || type == TYPE_STR || type == TYPE_VOID) {
            return 0;
        }
        else if(T->type != type) return 0;
        else if(type == TYPE_ARRAY) {
            if(number == T->number) return type_check(array, T->array);
            else return 0;
        }
        else if(type == TYPE_FUNC) {
            bool check1 = type_check(domain, T->domain);
            bool check2 = type_check(range, T->range);
            if(check1 == true && check2 == true) return 1;
            else return 0;
        }
        else if(type == TYPE_RECORD) {
            if(fields.size() != (T->fields).size()) return false;
            for(int i=0; i<fields.size(); i++) {
                bool check = type_check(fields[i], (T->fields)[i]);
                if(check == false) return 0;
            }
            return 1;
        }
    }
    else {
        // This type is a user defined compound type.
        // Will require using the symbol table for getting information about the same.
        int num = type_scope_check(T);
        if(num < 0) return -1;
        if(type >= 0 && type <= 7) {
            TypeExpression* T_base = ret_user_defined(num);
            return same_type(T_base);
        }
        else return type_check(user_defined, T);
    }

    return false; // Code should never reach here
}

/*********************************** MEMBER FUNCTIONS FOR TypeExpressions ******************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

// utility function to extract the name out of the lexeme, for eg. if lexeme = funcName$int$ , return just "funcName"
string getLexemeName(string str, char delim) {
    size_t pos = str.find(delim);
    if (pos != std::string::npos) {
        return str.substr(0, pos);
    }
    return str;
}

// utility function to generate key from lexeme and type encoding
string generateKey(string lexeme, string encoding) {
    return lexeme + "$" + encoding;
}

// function to lookup entry in the symbol table, assumed that proper key is passed
STentry* lookup(string lexeme, TypeExpression* T) {

    // generate key
    string key = lexeme;
    if(T != NULL && T->type == TYPE_FUNC) key = generateKey(lexeme,T->encode);

    STentry* res = NULL;
    SymbolTable* temp = currTable;
    // keep looking for entry till we reach the global symbol table
    while(temp != NULL) {
        // if entry is found, return entry
        if(temp->hashTable.find(key) != temp->hashTable.end()) {  
            res = &temp->hashTable[key];
            break;
        }
        else {
            temp = temp->parent;
        }
    }
    return res;
}

// function to lookup in scope
STentry* lookupScope(string lexeme, TypeExpression* T) {

    // generate key
    string key = lexeme;
    if(T != NULL && T->type == TYPE_FUNC) key = generateKey(lexeme,T->encode);

    STentry* res = NULL;
    if(currTable->hashTable.find(key) != currTable->hashTable.end()) {
        res = &currTable->hashTable[key];
    }
    return res;
}

// function to increment scope
void incr_scope(int scope_flag, string lexeme, TypeExpression* T) {
    // increment the scope level
    current_scope++;
    string key = lexeme;
    if(T != NULL && T->type == TYPE_FUNC) key = generateKey(lexeme,T->encode);

    // create a new symbol table
    SymbolTable* newTable = new SymbolTable(currTable,scope_flag,key);

    // make the parent and child connections
    currTable->children.push_back(newTable);
    newTable->parent = currTable;

    // now point the currTable pointer to this newly created table
    currTable = newTable;
}

// function to decrement scope
void decr_scope() {
    // decrement the scope level
    current_scope--;

    // point the *currTable pointer to the parent of the current node
    if(currTable != NULL)
        currTable = currTable->parent;
    else 
        printf("[SYMBOL_TABLE_ERROR]: current symbol table is NULL\n");
}

// function to delete entry
int deleteEntry(string key) {
    SymbolTable* temp = currTable;
    while(temp != NULL) {
        // if entry is found, delete entry
        if(temp->hashTable.find(key) != temp->hashTable.end()) {  
            temp->hashTable.erase(key);
            return 1;
        }
        else {
            temp = temp->parent;
        }
    }
    return 0;
}

// function to delete symbol table entry in present scope only
int deleteEntryScope(string key) {
    if(currTable->hashTable.find(key) != currTable->hashTable.end()) {
        currTable->hashTable.erase(key);
        return 1;
    }
    return 0;
}


// Doubt --> When will this function be called?
int define_type(TypeExpression* T, string name) {

    if(T == NULL) {
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Null Type passed to 'define_type'";
    }

    if(T->type <= 8) {
        /* wrong call for this function */
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Function called for basic types";
        return -1;
    }

    // hash the unique type number to its TypeExpression
    numToType[new_type_no] = T;

    return new_type_no++;
}

TypeExpression* ret_user_defined(int type) {

    if(type <= 8) {
        /* wrong call for this function */
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Function called for basic types";
        return NULL;
    }
    else if(numToType.find(type) == numToType.end()) {
        /* entry corresponding to the number not found */
        ErrorMsg->error_type = ERR_NOT_FOUND;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Type number has not been assigned to any class";
        return NULL;
    }
    else {
        TypeExpression* T = numToType[type];
        return T;
    }
}

int type_scope_check(TypeExpression* T) {

    if(T == NULL) {
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Null Type passed to 'type_scope_check'";
    }

    /* in case of basic data types */
    if(T->type <= 8) return T->type;

    /* in case the data type in undefined */
    else if(T->type == TYPE_UNDF) {
        ErrorMsg->error_type = ERR_UNDF;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Undefined data type";
    }

    else {
        /* get the unique type number */
        int type = T->type;

        if(numToType.find(type) == numToType.end()) {
            /* symbol table entry corresponding to the number not found */
            ErrorMsg->error_type = ERR_NOT_FOUND;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Type Expression Entry not found --- THIS SHOULDN'T OCCUR!!";
            return -2;
        }   
        string name = *T->lexeme;
        string key = generateKey(name,T->encode);
        if(lookup(key) == NULL) {
            /* the type is not present in the current or parent scope */
            ErrorMsg->error_type = ERR_SCOPE;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Entry not found in valid scope";
            return -1;
        }
        return T->type;
    }

    return -1; // Control should never reach here
}

STentry* ST_add(string lexeme, string token, TypeExpression* T, int lineno, int column, int* flag) {
    string key = lexeme;
    if(T != NULL && T->type == TYPE_FUNC) key = generateKey(lexeme,T->encode);

    STentry* entry = lookupScope(key,T);
    // if it is a new entry
    if(entry == NULL) {
        *flag = 0;
    }
    // if entry already exists
    else {
        // in case of class overloading 
        if(entry->symbol_type->type == TYPE_RECORD) {
            *flag = 2;
            ErrorMsg->error_type = WARNING;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Class Overloading warning";
        }
        else if(entry->symbol_type->type == TYPE_FUNC) {
            *flag = 3;
            ErrorMsg->error_type = WARNING;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Same function declared twice";
        }
        else {
            *flag = 1;
            ErrorMsg->error_type = WARNING;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Variable Overloading warning";
        }
        // delete previous entry
        if(deleteEntryScope(key) == 0) {
            ErrorMsg->error_type = ERR_OTHER;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "No entry to delete --> THIS SHOULDN'T OCCUR!!";
            return NULL;
        }
    }
    // add new entry
    STentry* newEntry = new STentry(lexeme, T, lineno, current_scope, token, column);
    // add this entry to the current symbol table
    currTable->hashTable[lexeme] = *newEntry;

    // return pointer to the entry
    return newEntry;
}

int compute_offsets(SymbolTable* table, int offset) {
    
    // go through each entry in this table
    unordered_map<string,STentry>::iterator it;
    unordered_map<string,STentry> currHashTable = table->hashTable;
    for(it = currHashTable.begin(); it != currHashTable.end(); it++) {

        // get the current entry
        STentry* entry = &(it->second);

        // set the offset for the entry
        entry->offset = offset;

        // update the offset
        offset += entry->symbol_type->space;
    }

    // now go through the children of this symbol table
    vector<SymbolTable*>::iterator it1;
    for(it1 = table->children.begin(); it1 != table->children.end(); it1++) {
        int tableType = (*it1)->type;
        if(tableType == FUNC_SCOPE || tableType == CLASS_SCOPE) {
            compute_offsets(*it1,0);
        }
        else offset = compute_offsets(*it1,offset);
    }

    return offset;
}

// function to print symbol tables for all functions and classes
void dumpAllSTs(string DirPath, SymbolTable* table) {

    // print the current symbol table, if it is a function or a class
    if(table->type == FUNC_SCOPE || table->type == CLASS_SCOPE || table->type == GLOBAL_SCOPE) {

        // create file path
        string filePath = DirPath + "/" + table->name + "_symbol_table.csv";
        char* path = const_cast<char*> (filePath.c_str());

        // Open the file for writing
        FILE* filePtr = fopen(path, "w");
        if(filePtr) {
            table->dumpST(filePtr,table);
        }

        // if error in opening file
        else {
            printf("[SYMBOL_TABLE_ERROR]: Couldn't create new file to dump symbol table\n");
            return;
        }

        // close the file
        fclose(filePtr);
    }

    // go through the children
    vector<SymbolTable*>::iterator it;
    for(it = table->children.begin(); it != table->children.end(); it++) {
        // call dump function recursively
        dumpAllSTs(DirPath, *it);
    }
}

int type_check(TypeExpression* T1, TypeExpression* T2) {
    if(T1 == NULL || T2 == NULL) return 0;
    int num1 = type_scope_check(T1);
    int num2 = type_scope_check(T2);
    if(num1 < 0 || num2 < 0) return -1;
    TypeExpression T = *(T1);
    return T.same_type(T2);
}

TypeExpression* type_bool() {
    int type = TYPE_BOOL;
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number);
    return ptr;
}

TypeExpression* type_int() {
    int type = TYPE_INT;
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number);
    return ptr;
}

TypeExpression* type_float() {
    int type = TYPE_FLOAT;
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number);
    return ptr;
}

TypeExpression* type_str(int size) {
    int type = TYPE_STR;
    int number = -1;
    vector<TypeExpression*> fields = vector<TypeExpression*>();
    TypeExpression* ptr = new TypeExpression(type, number, fields, size);
    return ptr;
}

TypeExpression* type_void() {
    int type = TYPE_VOID;
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number);
    return ptr;
}

TypeExpression* type_array(int number, TypeExpression* array) {
    int type = TYPE_ARRAY;
    vector<TypeExpression*> fields;
    fields.push_back(array);
    TypeExpression* ptr = new TypeExpression(type, number, fields);
    return ptr;
}

TypeExpression* type_record(vector<TypeExpression*> fields, int flag, vector<TypeExpression*> inherit) {
    int type = TYPE_RECORD;
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number, fields, 0, flag, inherit);
    return ptr;
}

TypeExpression* type_function(TypeExpression* domain, TypeExpression* range) {
    int type = TYPE_FUNC;
    // cout << "func";
    int number = -1;
    vector<TypeExpression*> fields;
    fields.push_back(domain);
    fields.push_back(range);
    // cout << fields.size() << endl;
    TypeExpression* ptr = new TypeExpression(type, number, fields);
    return ptr;
}

TypeExpression* type_user_defined(int type) {
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number);
    return ptr;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/

#endif // SYMBOL_TABLE_CPP
