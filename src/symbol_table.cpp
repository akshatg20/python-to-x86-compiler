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
extern int scope_resolution_flag;
extern SemanticError* ErrorMsg;                         // Semantic Error Message
extern SymbolTable* currTable;                          // pointer to the current symbol table in use
extern SymbolTable* actual_currTable;                   // this pointer will be used to point to the actual scope in scope resolution cases
extern SymbolTable* globalTable;                        // pointer to the root (global scope) symbol table
extern int current_scope;                               // maintains the current scope while parsing, initialized to zero
extern char* inputfile_path;                            // path of the source file

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.
int new_type_no = TYPE_UNDF + 1;                        // holds a unique type number for different user-defined types
stack<vector<int>> new_type_frame;                      // holds the unique type numbers which are defined in this scope
unordered_map<int,TypeExpression*> numToType;           // hashes each unique type number to its Type Expression
unordered_map<int,TypeExpression*> numToUserDefined;    // hashes each unique type number to Type Expression for Object
int SYMBOL_TABLE_DEBUG_INSIDE_VERBOSE = 0;
int SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE = 0;

unordered_map<string, SymbolTable*> labelMap;     // hashes each unique label to its corresponding symbol table
int if_counter = 0;
int debug_st = 0;

string getLexemeName(string str, char delim);
string generateKey(string lexeme, string encoding = "");
int deleteEntry(string key);
int deleteEntryScope(string key);
int fillRecord(STentry* entry, SymbolTable* table);
int fillGlobalRecord(SymbolTable* table);

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** MEMBER FUNCTIONS FOR STEntry **************************************************/

// Make constructor for the class
STentry::STentry() {
    this->symbol_type = NULL;
    this->scope_level = this->offset = 0;
    this->tablePtr = NULL;
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
    this->tablePtr = NULL;

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
    this->funcRecord = new ActivationRecord();
    children = vector<SymbolTable*>();
    hashTable = unordered_map<string, STentry*>();
    return;
}

// Constructor
SymbolTable::SymbolTable(SymbolTable* parent, int flag, string name) {
    this->parent = parent;
    this->type = flag;
    this->name = name;
    this->funcRecord = new ActivationRecord();
    children = vector<SymbolTable*>();
    hashTable = unordered_map<string, STentry*>();
    return;
}

// function to dump the symbol table onto an external file
void SymbolTable::dumpST(FILE* outputFile, SymbolTable* table) {
    fprintf(outputFile,"--------------------,-------------------------,------------------------------------------------------------------------------------------,-------------\n");
    fprintf(outputFile,"LEXEME              ,TOKEN                    ,TYPE                                                                                      ,LINE_NO\n");
    fprintf(outputFile,"--------------------,-------------------------,------------------------------------------------------------------------------------------,-------------\n");


    unordered_map<string,STentry*>::iterator it;
    unordered_map<string,STentry*> currHashTable = table->hashTable;

    for(it = currHashTable.begin(); it != currHashTable.end(); it++) {
        // print the lexeme
        string name = getLexemeName(it->first,'$');
        char* name1 = const_cast<char*> (name.c_str());
        fprintf(outputFile, "%-21s,",name1);

        // print the token of the symbol
        string token = it->second->token;
        char* token1 = const_cast<char*> (token.c_str());
        fprintf(outputFile,"%-26s,",token1);

        // print the type of symbol
        string type = it->second->symbol_type->encode;
        char* type1 = const_cast<char*> (type.c_str());
        // printf("%s\n",type1);
        fprintf(outputFile,"%-91s,",type1);

        // print the line no of the symbol declaration
        vector<int> lines = it->second->refPoints;
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
    mangle = "u";
    name = "";
    lexeme = NULL;
    array = domain = range = user_defined = NULL;
    inheritance = fields = deque<TypeExpression*>();
    return;
}

TypeExpression::TypeExpression (
    int tp,
    int num,
    deque<TypeExpression*> fields_arr,
    int size,
    int flag,
    deque<TypeExpression*> inherit
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
            mangle = "i";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
            break;
        }
        
        case TYPE_FLOAT:  {
            type = TYPE_FLOAT;
            space = sizeof(float); // Can change based on machine specifications
            number = -1;
            class_flag = 0;
            encode = "FLOATING-POINT";
            mangle = "f";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
            break;
        }
        
        case TYPE_STR:    {
            if(size < 0) {
                // This is an erreneous case which should not occur
                // However, this may denote a simple not known case in string sizes
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Error in String size computation\n");
            }
            
            type = TYPE_STR;
            space = size;
            number = -1;
            class_flag = 0;
            encode = "STRING";
            mangle = "s";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
            break;
        }
        
        case TYPE_BOOL:   {
            type = TYPE_BOOL;
            space = sizeof(bool); // Can change based on machine specifications
            number = -1;
            class_flag = 0;
            encode = "BOOLEAN";
            mangle = "b";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
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
            mangle = "v";
            name = "";
            lexeme = NULL;
            array = domain = range = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
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
                // However, this may denote a simple not known case in array sizes
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) printf("[TYPING ERROR]: Negative size or unknown size array Declaration\n");
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
            mangle = "P" + (array->mangle);
            name = "";
            lexeme = NULL;
            domain = range = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
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
            mangle = "F" + (domain->mangle) + "F" + (range->mangle) + "F";
            name = "";
            lexeme = NULL;
            array = user_defined = NULL;
            inheritance = fields = deque<TypeExpression*>();
            break;
        }
        
        case TYPE_RECORD: {
            type = TYPE_RECORD;
            fields = fields_arr;
            space = 0;
            class_flag = 0;
            for(int i=0; i<fields.size(); i++) space += (fields[i]->space);
            number = -1;
            if(fields.size() == 0) { encode = "RECORD()"; mangle = ""; }
            else {
                encode = "RECORD(" + (fields[0]->encode);
                for(int i=1; i<fields.size(); i++) encode += (string(";") + (fields[i]->encode));
                encode += string(")");
                mangle += (fields[0]->mangle);
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
            if(user == NULL) {
                // The user defined type is not in current scope and so cannot be accessed.
                // Will check this case in Semantic Analysis in the parser
                TypeExpression();
                break;
            }
            
            type = tp;
            space = (user->space);
            number = -1;
            class_flag = 0;
            encode = (*(user->lexeme));
            mangle = (user->mangle);
            name = "";
            lexeme = NULL;
            array = domain = range = NULL;
            user_defined = user;
            inheritance = fields = deque<TypeExpression*>();
            break;
        }
    }

    if(space < 0) space = 0;

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
    // In case of inheritance the typing test is directional and the object calling this function should be the child class.
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
            if(number == T->number || number == -1 || T->number == -1) return type_check(array, T->array);
            else return 0;
        }
        else if(type == TYPE_FUNC) {
            int check1 = type_check(domain, T->domain);
            int check2 = type_check(range, T->range);
            if(check1 == 1 && check2 == 1) return 1;
            else if(check1 == -1 || check2 == -1) return -1;
            else return 0;
        }
        else if(type == TYPE_RECORD) {
            if(fields.size() != (T->fields).size()) return 0;
            for(int i=0; i<fields.size(); i++) {
                int check = type_check(fields[i], (T->fields)[i]);
                if(check != 1) return check;
            }
            return 1;
        }
    }
    else {
        // This type is a user defined compound type.
        // Will require using the symbol table for getting information about the same.
        int num = type_scope_check(T);
        if(num < 0) return -1;
        if(type > 8 && (T->type) > 8) {
            if(type == T->type) return 1;
            else return 0;
        }
        else if(type >= 0 && type <= 7) {
            TypeExpression* T_base = ret_user_defined(num);
            return same_type(T_base);
        }
        else return type_check(user_defined, T);
    }

    return false; // Code should never reach here
}

// Based on Type Equivalence on Pg 372 of DRAG Book
int TypeExpression::same_type_with_typecast(TypeExpression* T) {
    // In case of inheritance the typing test is directional and the object calling this function should be the child class.
    if(T == NULL) return -1;
    else if(T->type == TYPE_UNDF || type == TYPE_UNDF) return -1;
    else if(type >= 0 && type <= 7 && (T->type) >= 0 && (T->type) <= 7) {
        // Both the types are formed from pre-defined type constructors only and are not user defined.
        if(T->type == TYPE_BOOL || T->type == TYPE_FLOAT || T->type == TYPE_INT || T->type == TYPE_STR || T->type == TYPE_VOID) {
            if(type == T->type) return 1;
            else if(type == TYPE_FLOAT && T->type == TYPE_INT) return 1;
            else if(type == TYPE_INT && T->type == TYPE_FLOAT) return 1;
            else if(type == TYPE_VOID || T->type == TYPE_VOID) return 1;
            else return 0;
        }
        else if(type == TYPE_BOOL || type == TYPE_FLOAT || type == TYPE_INT || type == TYPE_STR || type == TYPE_VOID) {
            return 0;
        }
        else if(T->type != type) return 0;
        else if(type == TYPE_ARRAY) {
            if(number == T->number || number == -1 || T->number == -1) return type_check_with_typecast(array, T->array);
            else return 0;
        }
        else if(type == TYPE_FUNC) {
            int check1 = type_check_with_typecast(domain, T->domain);
            int check2 = type_check_with_typecast(range, T->range);
            if(check1 == 1 && check2 == 1) return 1;
            else if(check1 == -1 || check2 == -1) return -1;
            else return 0;
        }
        else if(type == TYPE_RECORD) {
            // cout << "Inside RECORD with types " << encode << " " << T->encode << "\n";
            if(class_flag > 0) {
                // cout << "Inside RECORD INHERITANCE with types " << encode << " " << T->encode << "\n";
                // The current type object denote a class so extended type checking required supporting inheritance.
                for(int i = 0; i < inheritance.size(); i++) {
                    TypeExpression* chk = inheritance[i];
                    int check = type_check_with_typecast(chk, T);
                    if(check == 1) return check;
                }
            }
            // cout << "Inside RECORD FINAL with types " << encode << " " << T->encode << "\n";
            if(fields.size() != (T->fields).size()) return 0;
            for(int i=0; i<fields.size(); i++) {
                int check = type_check_with_typecast(fields[i], (T->fields)[i]);
                if(check != 1) return check;
            }
            return 1;
        }
    }
    else {
        // This type is a user defined compound type.
        // Will require using the symbol table for getting information about the same.
        // cout << "Inside SPECIAL with types " << encode << " " << T->encode << "\n";
        int num = type_scope_check(T);
        if(num < 0) return -1;
        if(type > 8 && (T->type) > 8) {
            // cout << "Inside SPECIAL 1 with types " << encode << " " << T->encode << "\n";
            if(type == T->type) return 1;
            else return type_check_with_typecast(user_defined, T);
        }
        else if(type >= 0 && type <= 7) {
            // cout << "Inside SPECIAL 2 with types " << encode << " " << T->encode << "\n";
            TypeExpression* T_base = ret_user_defined(num);
            return same_type_with_typecast(T_base);
        }
        else return type_check_with_typecast(user_defined, T);
    }

    return false; // Code should never reach here
}

/*********************************** MEMBER FUNCTIONS FOR TypeExpressions ******************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

// This function is used for rectification of details inside the Type of a lexeme if they are not already updated
void rectify_type(TypeExpression* T) {
    // Rectification of encoding of the type T is implemented
    if(T->type == TYPE_BOOL) T->encode = "BOOLEAN";
    else if(T->type == TYPE_FLOAT) T->encode = "FLOATING_POINT";
    else if(T->type == TYPE_INT) T->encode = "INTEGER";
    else if(T->type == TYPE_STR) T->encode = "STRING";
    else if(T->type == TYPE_VOID) T->encode = "NONE";
    else if(T->type == TYPE_UNDF) T->encode = "UNDEFINED";
    else if(T->type == TYPE_ARRAY) {
        rectify_type(T->array);
        T->encode = "ARRAY(" + to_string(T->number) + string(";") + (T->array->encode) + string(")");
    }
    else if(T->type == TYPE_FUNC) {
        rectify_type(T->domain);
        rectify_type(T->range);
        T->encode = "FUNCTION(" + (T->domain->encode) + string("->") + (T->range->encode) + string(")");
    }
    else if(T->type == TYPE_RECORD) {
        for(int i=0; i<(T->fields).size(); i++) rectify_type((T->fields)[i]);
        if((T->fields).size() == 0) (T->encode) = "RECORD()";
        else {
            T->encode = "RECORD(" + (T->fields[0]->encode);
            for(int i=1; i<(T->fields).size(); i++) (T->encode) += (string(";") + ((T->fields)[i]->encode));
            (T->encode) += string(")");
        }
    }
    else {
        // This is the case of user defined types - Left for now - Maybe used for classes operation
    }
    return;
}

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

// Extract the name of a function (or other entity) from key generated from "generateKey"
string extract_name(string key) {
    string name = "";
    for(int i=0;i<key.length();i++) {
        if(key[i]=='$') break;
        name.push_back(key[i]);
    }
    return name;
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
            res = temp->hashTable[key];
            break;
        }
        else {
            temp = temp->parent;
        }
    }
    return res;
}

// function to lookup entry in the symbol table, assumed that proper key is passed
// This is only called for functions and looks up only the domain part of the function.
STentry* lookup_restricted(string lexeme, TypeExpression* T) {
    // This works only for function types
    if(T == NULL || T->type != TYPE_FUNC) return NULL;
    if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
        char* ch1 = const_cast<char*>(lexeme.c_str());
        printf("[SYMBOL TABLE]: Restricted lookup is called for function %s\n", ch1);
    }
    STentry* res = NULL;
    SymbolTable* temp = currTable;
    int found_flag = 0;
    // keep looking for entry till we reach the global symbol table
    while(temp != NULL) {
        // if entry is found, return entry
        if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
            char* ch1 = const_cast<char*>((temp->name).c_str());
            printf("[SYMBOL TABLE]: Checking inside the symbol table %s inside lookup_restricted\n", ch1);
        }
        
        unordered_map<string, STentry*>::iterator it;
        for(it = (temp->hashTable).begin(); it != (temp->hashTable).end(); it++) {
            string name = extract_name(it->first);
            if(name != lexeme) continue;
            TypeExpression* type = (it->second)->symbol_type;
            if(type->type != TYPE_FUNC) continue;
            else {
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
                    char* ch1 = const_cast<char*>((T->domain->encode).c_str());
                    char* ch2 = const_cast<char*>((type->domain->encode).c_str());
                    printf("[SYMBOL TABLE]: Going into type Checking for types %s and %s inside lookup_restricted\n", ch1, ch2);
                }
                int flag = type_check_with_typecast(T->domain, type->domain);
                if(SYMBOL_TABLE_DEBUG_OUTSIDE_VERBOSE) {
                    char* ch1 = const_cast<char*>((T->domain->encode).c_str());
                    char* ch2 = const_cast<char*>((type->domain->encode).c_str());
                    printf("[SYMBOL TABLE]: Type Checking successful for types %s and %s with output %d\n", ch1, ch2, flag);
                }
                if(flag == 1) {
                    res = (it->second);
                    found_flag = 1; break;
                }
            }
        }
        if(found_flag == 1) break;
        else temp = temp->parent;
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
        res = currTable->hashTable[key];
    }
    return res;
}

// function to lookup entry in the current symbol table only, assumed that proper key is passed
// This is only called for functions and looks up only the domain part of the function.
STentry* lookup_restricted_scope(string lexeme, TypeExpression* T) {
    // This works only for function types
    if(T == NULL || T->type != TYPE_FUNC) return NULL;

    STentry* res = NULL;
    SymbolTable* temp = currTable;
    
    // if entry is found, return entry
    unordered_map<string, STentry*>::iterator it;
    for(it = (temp->hashTable).begin(); it != (temp->hashTable).end(); it++) {
        string name = extract_name(it->first);
        if(name != lexeme) continue;
        TypeExpression* type = (it->second)->symbol_type;
        if(type->type != TYPE_FUNC) continue;
        else {
            int flag = type_check_with_typecast(T->domain, type->domain);
            if(flag == 1) {
                res = (it->second);
                break;
            }
        }
    }

    return res;
}

// function to increment scope
int incr_scope(int scope_flag, string lexeme, TypeExpression* T) {
    // increment the scope level
    current_scope++;
    string key = lexeme;
    if(T != NULL && T->type == TYPE_FUNC) key = generateKey(lexeme,T->encode);

    // create a new symbol table
    SymbolTable* newTable = new SymbolTable(currTable,scope_flag,key);

    // assign this pointer to the function entry in the orginal symbol table
    // this step is only to be done for cases of functions and classes
    if(scope_flag == FUNC_SCOPE || scope_flag == CLASS_SCOPE) {
        STentry* entry = lookup(lexeme,T);
        if(entry == NULL) {
            // This is a case of error and this should not occur.
            ErrorMsg->error_type = ERR_NOT_FOUND;
            ErrorMsg->lineno = yylineno;
            if(scope_flag == FUNC_SCOPE) ErrorMsg->msg = "Function " + lexeme + " is not defined in this scope.";
            else ErrorMsg->msg = "Class " + lexeme + " is not defined in this scope.";
            return -1;
        }
        else entry->tablePtr = newTable;
    }

    // make the parent and child connections
    currTable->children.push_back(newTable);
    newTable->parent = currTable;

    // now point the currTable pointer to this newly created table and add an empty vector to the type_stack
    currTable = newTable;
    new_type_frame.push(vector<int>());
    return 0;
}

// function to decrement scope
int decr_scope() {
    // decrement the scope level
    current_scope--;

    // point the *currTable pointer to the parent of the current node
    if(currTable != NULL)
        currTable = currTable->parent;
    else {
        // An empty currTable is a critical memory error
        ErrorMsg->error_type = ERR_UNDF;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Current symbol table not found.\n";
        return -1;
    }

    // Delete the types defined in this frame which are now out of scope
    vector<int> types = new_type_frame.top();
    new_type_frame.pop();
    new_type_no -= types.size();
    for(int i = 0; i < types.size(); i++) {
        int defined_type = types[i];
        if(numToType.find(defined_type) != numToType.end()) numToType.erase(defined_type);
        if(numToUserDefined.find(defined_type) != numToUserDefined.end()) numToUserDefined.erase(defined_type);
    }

    return 0;
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
        else temp = temp->parent;
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


int define_type(TypeExpression* T, string name) {
    if(T == NULL) {
        // NULL type-expression is not allowed inside this function
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Null Type passed to 'define_type'";
        return -1;
    }

    // The given type should not be a previously defined type
    for(int i = 0; i < new_type_no; i++) {
        TypeExpression* chk = numToType[i];
        int flag = type_check(T, chk);
        if(flag == 1) {
            // The given type is a previously defined type
            ErrorMsg->error_type = ERR_WRG_USE;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Already defined type is being defined again";
            return -1;
        }
    }

    // Hash the unique type number to its TypeExpression
    numToType[new_type_no] = T;
    vector<int> types = new_type_frame.top();
    types.push_back(new_type_no);
    new_type_frame.pop();
    new_type_frame.push(types);

    return new_type_no++;
}

int withdraw_type(int type) {
    // This functionality is especially available for classes to withdraw the type
    // definition of the latest defined type.
    if(type <= 8) {
        /* wrong call for this function */
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Function called for basic types";
        return -1;
    }
    else if(numToType.find(type) == numToType.end()) {
        /* entry corresponding to the number not found */
        ErrorMsg->error_type = ERR_NOT_FOUND;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Type number has not been assigned to any class";
        return -1;
    }
    else if(type != new_type_no - 1) {
        /* functionality not supported to withdraw types defined deep in history */
        ErrorMsg->error_type = ERR_UNDF;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Special kind of type deletion not supported";
        return -1;
    }
    else {
        new_type_no--;
        if(numToType.find(new_type_no) != numToType.end()) numToType.erase(new_type_no);
        return 0;
    }

    return -1; // Control should never reach here
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
        string lexeme = *(T->lexeme);
        STentry* entry = lookup(lexeme, NULL);
        if(entry == NULL) {
            /* The user defined type is not found in the current scope */
            ErrorMsg->error_type = ERR_NOT_FOUND;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "User defined type is not available in the current scope";
            return NULL;
        }
        else return T;
    }

    return NULL; // Control should never reach here
}

int type_scope_check(TypeExpression* T, int flag) {
    if(T == NULL) {
        ErrorMsg->error_type = ERR_WRG_USE;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Null Type passed to type_scope_check";
        return -1;
    }

    /* in case of basic data types */
    if((T->type) < TYPE_UNDF) return (T->type);

    /* in case the data type in undefined */
    else if(T->type == TYPE_UNDF) {
        ErrorMsg->error_type = ERR_UNDF;
        ErrorMsg->lineno = yylineno;
        ErrorMsg->msg = "Undefined data type";
        return -1;
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
        string name = *(numToType[type]->lexeme);
        SymbolTable* table = currTable;
        if(flag == 1 && scope_resolution_flag > 0) currTable = actual_currTable;
        if(lookup(name) == NULL) {
            /* the type is not present in the current or parent scope */
            ErrorMsg->error_type = ERR_SCOPE;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Entry not found in valid scope";
            return -1;
        }
        currTable = table;
        return (T->type);
    }

    return -1; // Control should never reach here
}

// Whenever a new entry is to be added to the current symbol table - This function is called.
// Please take the source file path from "extern char* inputfile_path" which is defined in "main.cpp" -> And store in SymbolTable
// The "lexeme" stores the complete declared NAME and should be added appropriately in a STentry.
// FEATURES TO SUPPORT -
// Function Overloading - If added entry is a function with same "lexeme" but different type then it is allowed.
//                        In such cases the passed type T will be helpful to check whether the function can be added.
// Function Overriding - NOT IMPLEMENTED => Do we have to implement this ?
// Class Inheritance - If added "lexeme" is a class then it can inherit from a parent.
//                     In such cases vector<TypeExpression*> inherit in T can be useful.
// Variable Overloading - Is not allowed. In such cases the variable defined later will take over.
//                        The previous declaration of the same "lexeme" will be deleted from Symbol Table of current scope.
// Class Overloading - Is also not allowed and will be treated like variable overloading only.
// Variable Overloading will generate warning - Please update the value of flag to 1 in this case. Fill SemanticError appropriately.
// Class Overloading will generate warning - Please update the value of flag to 2 in this case. Fill SemanticError appropriately.
// In case of no error return the pointer to symbol table entry generated and keep value of flag as 0.
// In case of any error return NULL and fill SemanticError appropriately. In this case value of flag is irrelevant.
STentry* ST_add(string lexeme, string token, TypeExpression* T, int lineno, int column, int* flag, SymbolTable* table = NULL) {
    // Check and rectify the type expression in case the encoding is not updated
    if(T != NULL) rectify_type(T);
    string key = lexeme;
    if(T != NULL && T->type == TYPE_FUNC) key = generateKey(lexeme, T->encode);
    STentry* entry = lookupScope(key, T);
    
    // if it is a new entry
    if(entry == NULL) (*flag) = 0;
    // if entry already exists
    else {
        // in case of class overloading 
        if(entry->symbol_type->type == TYPE_RECORD) {
            (*flag) = 2;
            ErrorMsg->error_type = WARNING;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Class Overloading warning";
        }
        else if(entry->symbol_type->type == TYPE_FUNC) {
            (*flag) = 3;
            ErrorMsg->error_type = WARNING;
            ErrorMsg->lineno = yylineno;
            ErrorMsg->msg = "Same function declared twice";
        }
        else {
            (*flag) = 1;
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
    currTable->hashTable[key] = newEntry;

    // set the Symboltable pointer
    table = currTable;

    // return pointer to the entry
    return newEntry;
}

// "add" function to be finally used in "parse.y"
// This function is made because the TypeExpression needs to store a pointer to the lexeme it points to
// But this pointer can be available only after adding the lexeme to Symbol Table. So, "lexeme" field
// of TypeExpression is changed after adding the entry to Symbol Table.
STentry* add(string lexeme, string token, TypeExpression* T, int lineno, int column, int* flag, SymbolTable* table) {
    STentry* entry = ST_add(lexeme, token, T, lineno, column, flag, table);
    
    // This case of lexeme mapping to the type is not done in case a NULL type is passed. This must be done
    // manually by the calling authority in case a NULL type is passed at some point.
    if(T != NULL) T->lexeme = (&(entry->lexeme));
    
    if(entry != NULL) {
        // cout << "Symbol table entry is added which is NOT NULL" << "\n";
        // cout << "Entry is for " << lexeme << " with encoding " << T->encode << " in symbol table named " << currTable->name << "\n";
        // cout << "Entry is space " << (T->space) << "\n";
    }
    else {
        // cout << "Symbol table entry is added which is NULL" << "\n";
    }

    return entry;
}

int compute_offsets(SymbolTable* table, int offset) {
    // go through each entry in this table
    unordered_map<string,STentry*>::iterator it;
    if(debug_st) cout << "Offsets being calculated for " << table->name << " table" << endl;

    for(it = (table->hashTable).begin(); it != (table->hashTable).end(); it++) {
        // get the current entry
        STentry* entry = it->second;
        if(debug_st) cout << "variable = " << entry->lexeme << "  size = " << entry->symbol_type->space << endl;

        // update the offset
        if(entry->symbol_type->type == TYPE_ARRAY) entry->symbol_type->space += 4;
        offset += entry->symbol_type->space;

        // set the offset for the entry
        entry->offset = offset;

        if(debug_st) cout << "offset = " << entry->offset << endl;
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
    if(table->type == FUNC_SCOPE || table->type == CLASS_SCOPE || table->type == GLOBAL_SCOPE || table->type == OTHER_SCOPE) {

        // create file path
        string filePath;
        if(table->type == OTHER_SCOPE)
            filePath = DirPath + "/" + table->name + to_string(if_counter++) + "_symbol_table.csv";
        else
            filePath = DirPath + "/" + table->name + "_symbol_table.csv";
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

// function to fill activation records of all functions
int fillActivationRecords(SymbolTable* table) {

    // if(debug_st) cout << "fillACtivationRecords() called\n";

    if(table->type == GLOBAL_SCOPE) {
        fillGlobalRecord(table);
    }

    unordered_map<string,STentry*>::iterator it;

    for(it = (table->hashTable).begin(); it != (table->hashTable).end(); it++) {
        int type = it->second->symbol_type->type;
        STentry* currEntry = it->second;
        if(type == TYPE_FUNC) {
            fillRecord(currEntry, it->second->tablePtr);
        }
    }

    vector<SymbolTable*>::iterator it2;
    for(it2 = table->children.begin(); it2 != table->children.end(); it2++) {
        fillActivationRecords(*it2);
    }

    return 0;
}

int fillGlobalRecord(SymbolTable* table) {
    int numVars = 0;
    int sizeVars = 0;

    ActivationRecord* ar = table->funcRecord;
    if(debug_st) cout << "Activation Record being filled for " << table->name << endl;

    int offset = 0;
    string varName = "";

    unordered_map<string,STentry*>::iterator it;
    for(it = (table->hashTable).begin(); it != (table->hashTable).end(); it++) {
        numVars++;
        STentry* entry = it->second;
        offset = entry->offset;
        varName = entry->lexeme;
        ar->tempVars[varName] = offset;
        sizeVars = offset;

        if(debug_st) cout << "variable " << varName << " filled at offset " << ar->tempVars[varName] << endl;
    }
    ar->numVars = numVars;
    ar->sizeVars = sizeVars;

    if(debug_st) cout << "number of variables " << ar->numVars << " and size of func stack = " << ar->sizeVars << endl;

    ar->stackMemAlloc = sizeVars;

    return sizeVars;

}

// function to fill activation record for one function
int fillRecord(STentry* entry, SymbolTable* table) {
    int numParams = 0;
    int numVars = 0;
    int sizeVars = 0;
    int sizeParams = 0;

    // get the activation record
    ActivationRecord* ar = table->funcRecord;

    // get the offset of the variables defined inside this symbol table
    if(debug_st) cout << "Activation Record being filled for " << table->name << endl;

    unordered_map<string,STentry*>::iterator it;
    int offset = 0;
    string varName = "";
    for(it = (table->hashTable).begin(); it != (table->hashTable).end(); it++) {
        numVars++;
        STentry* entry = it->second;
        offset = entry->offset;
        varName = entry->lexeme;
        ar->tempVars[varName] = offset;
        sizeVars = offset;

        if(debug_st) cout << "variable " << varName << " filled at offset " << ar->tempVars[varName] << endl;
    }
    ar->numVars = numVars;
    ar->sizeVars = sizeVars;

    if(debug_st) cout << "number of variables " << ar->numVars << " and size of func stack = " << ar->sizeVars << endl;

    // get the parameters of the function, which will be a record of other type expressions
    TypeExpression* params = entry->symbol_type->domain;
    TypeExpression* tparam = NULL;
    deque<TypeExpression*>::iterator it1;
    string paramName = "";
    for(it1 = params->fields.begin(); it1 != params->fields.end(); it1++) {
        numParams++;
        tparam = *it1;
        offset += tparam->space;
        sizeParams += tparam->space;
        ar->params.push_back(offset);
    }
    ar->numParams = numParams;
    ar->sizeParams = sizeParams;

    // iterate over the subtree of this function symbol table
    vector<SymbolTable*>::iterator it2;
    for(it2 = table->children.begin(); it2 != table->children.end(); it2++) {
        int type = (*it2)->type;
        if(type != FUNC_SCOPE)
            sizeParams += fillGlobalRecord(*it2);
            ar->sizeParams = sizeParams;
    }

    ar->stackMemAlloc = sizeVars + sizeParams;
    return ar->stackMemAlloc;
}

int type_check(TypeExpression* T1, TypeExpression* T2) {
    // In case of inheritance the typing test is directional and the first type should denote the child class.
    if(T1 == NULL || T2 == NULL) return 0;
    int num1 = type_scope_check(T1, 1);
    int num2 = type_scope_check(T2);
    if(num1 < 0 || num2 < 0) return -1;
    TypeExpression T = *(T1);
    return T.same_type(T2);
}

int type_check_with_typecast(TypeExpression* T1, TypeExpression* T2) {
    // In case of inheritance the typing test is directional and the first type should denote the child class.
    if(T1 == NULL || T2 == NULL) return 0;
    int num1 = type_scope_check(T1, 1);
    int num2 = type_scope_check(T2);
    if(num1 < 0 || num2 < 0) return -1;
    TypeExpression T = *(T1);
    return T.same_type_with_typecast(T2);
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
    deque<TypeExpression*> fields = deque<TypeExpression*>();
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
    deque<TypeExpression*> fields;
    fields.push_back(array);
    TypeExpression* ptr = new TypeExpression(type, number, fields);
    return ptr;
}

TypeExpression* type_record(deque<TypeExpression*> fields, int flag, deque<TypeExpression*> inherit, string lexeme) {
    int type = TYPE_RECORD;
    int number = -1;
    TypeExpression* ptr = new TypeExpression(type, number, fields, 0, flag, inherit);

    // Class is a user-defined type. So, it needs to be informed to the symbol table
    if(flag == 1) {
        // cout << "Inside user-defining part with encoding " << (ptr->encode) << " and inherit size " << (ptr->inheritance).size() << "\n";
        int type_number = define_type(ptr, lexeme);
        if(type_number == -1) return NULL;
        ptr->class_flag = type_number;
    }
    
    return ptr;
}

TypeExpression* type_function(TypeExpression* domain, TypeExpression* range) {
    int type = TYPE_FUNC;
    int number = -1;
    deque<TypeExpression*> fields;
    fields.push_back(domain);
    fields.push_back(range);
    TypeExpression* ptr = new TypeExpression(type, number, fields);
    return ptr;
}

TypeExpression* type_user_defined(int type) {
    if(numToUserDefined.find(type) == numToUserDefined.end()) {
        int number = -1;
        TypeExpression* ptr = new TypeExpression(type, number);
        numToUserDefined[type] = ptr;
        return ptr;
    }
    else {
        TypeExpression* ptr = numToUserDefined[type];
        TypeExpression* user = ret_user_defined(type);
        if(user == NULL) user = new TypeExpression();
        
        ptr->type = type;
        ptr->space = (user->space);
        ptr->number = -1;
        ptr->class_flag = 0;
        if(user->lexeme != NULL) ptr->encode = (*(user->lexeme));
        else ptr->encode = "";
        ptr->mangle = (user->mangle);
        ptr->name = "";
        ptr->lexeme = NULL;
        ptr->array = ptr->domain = ptr->range = NULL;
        ptr->user_defined = user;
        ptr->inheritance = ptr->fields = deque<TypeExpression*>();

        return ptr;
    }
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/

#endif // SYMBOL_TABLE_CPP
