#ifndef SYMBOL_TABLE_CPP
#define SYMBOL_TABLE_CPP

#include <iostream>
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
----
*/

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF SYMBOL TABLE *****************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.


/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.
int current_scope;                               // maintains the current scope while parsing, initialized to zero
SymbolTable* currTable;                          // pointer to the current symbol table in use
extern int yylineno;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

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

// Make constructor for the class
STentry::STentry() {
    symbol_type = 0; scope_level = 0;
    symbol_size = 0;
    return;
}

// Make constructor for the class
STentry::STentry(int type, int scope, int size) {
    symbol_type = type; scope_level = scope;
    symbol_size = size;
    return;
}

void STentry::addLineNo(int lineno) {
    this->refPoints.push_back(lineno);
}

void STentry::updatePDTValues(int ival, float fval, string strval, bool bval) {
    this->var.ival = ival;
    this->var.fval = fval;
    this->var.strval = strval;
    this->var.boolval = bval;
}

int STentry::getSymbolType() { 
    return this->symbol_type; 
}

int STentry::getSymbolScope() {
    return this->scope_level;
}

int STentry::getListType() {
    return this->list_type;
}

int STentry::getFuncType() {
    return this->func_attr.func_type;
}

vector<int> STentry::getLineRefs() {
    return this->refPoints;
}

// function to add description about the symbol table
void SymbolTable::addDescription(string msg) {
    this->desc = msg;
}

// function to add PDT entry to the symbol table
void SymbolTable::addBasicEntry(string lexeme,int type, int size, int scope, int lineno, int ival, float fval, string strval, bool bval) {
    // if entry is new
    STentry* ptr = NULL;
    if(currTable->hashTable.find(lexeme) == currTable->hashTable.end()) {
        // create a new Symbol Table Entry
        STentry entry(type,size,scope);
        STentry* ptr = &entry;
        ptr->addLineNo(lineno);
        ptr->updatePDTValues(ival,fval,strval,bval); 
        currTable->hashTable[lexeme] = entry;  
    }
    else {
        // get the existing Symbol Table Entry
        STentry entry = currTable->hashTable[lexeme]; 
        STentry* ptr = &entry;
        ptr->addLineNo(lineno);
        ptr->updatePDTValues(ival,fval,strval,bval); 
    }
}

// function to lookup entry in the symbol table
STentry* SymbolTable::lookup(string lexeme) {
    STentry* res = NULL;
    SymbolTable* temp = currTable;
    // keep looking for entry till we reach the global symbol table
    while(temp != NULL) {
        // if entry is found, return entry
        if(temp->hashTable.find(lexeme) != temp->hashTable.end()) {  
            res = &temp->hashTable[lexeme];
            break;
        }
        else {
            temp = temp->parent;
        }
    }
    if(res == NULL) {
        char* lex = const_cast<char*> (lexeme.c_str());
        fprintf(stderr,"[SYMBOL ERROR]: %s not declared before use at line no %d\n", lex, yylineno);
        exit(-1);
    }
    return res;
}

// function to increment scope
void SymbolTable::incr_scope() {
    // increment the scope level
    current_scope++;

    // create a new symbol table
    SymbolTable newTable(currTable);
    SymbolTable* ptr = &newTable;

    // make the parent and child connections
    currTable->children.push_back(ptr);
    ptr->parent = currTable;

    // now point the currTable pointer to this newly created table
    currTable = ptr;
}

// function to decrement scope
void SymbolTable::decr_scope() {
    // decrement the scope level
    current_scope--;

    // point the *currTable pointer to the parent of the current node
    currTable = currTable->parent;
}

void STentry::setFuncDetails(int func_type, int num_params, vector<Param> params) {
    this->func_attr.func_type = func_type;
    this->func_attr.num_params = num_params;
    this->func_attr.funcParams = params;
}

void SymbolTable::addFuncionDetails(string lexeme, int func_type, int num_params, vector<Param> params) {
    STentry* entry = lookup(lexeme);
    entry->setFuncDetails(func_type,num_params,params);
}

void STentry::setClassDetails(int num_attrs, vector<Param> classAttrs, vector<FuncAttrs> memFuncs) {
    this->num_attrs = num_attrs;
    this->classAttrs = classAttrs;
    this->memFuncs = memFuncs;
}

void SymbolTable::addClassDetails(string lexeme, int num_attrs, vector<Param> classAttrs, vector<FuncAttrs> memFuncs) {
    STentry* entry = lookup(lexeme);
    entry->setClassDetails(num_attrs,classAttrs,memFuncs);
}

// function to dump the symbol table onto an external file
void SymbolTable::dumpST(FILE* outputFile, SymbolTable* table) {
    fprintf(outputFile,"----------------- ------------- ------- -------\n");
    fprintf(outputFile,"LEXEME            TYPE          SCOPE   LINE_NO\n");
    fprintf(outputFile,"----------------- ------------- ------- -------\n");

    unordered_map<string,STentry>::iterator it;
    unordered_map<string,STentry> currHashTable = table->hashTable;

    for(it = currHashTable.begin(); it != currHashTable.end(); it++) {
        // print the lexeme
        string name = getLexemeName(it->first,'$');
        char* name1 = const_cast<char*> (name.c_str());
        fprintf(outputFile, "%-17s",name1);

        // print the type of symbol
        switch (it->second.getSymbolType())
        {
            case TYPE_INT: {
                fprintf(outputFile,"%-13s","int");
                break;
            }

            case TYPE_FLOAT: {
                fprintf(outputFile,"%-13s","float");
                break;
            }

            case TYPE_BOOL: {
                fprintf(outputFile,"%-13s","boolean");
                break;
            }

            case TYPE_STR: {
                fprintf(outputFile,"%-13s","string");
                break;
            }

            case TYPE_LIST: {
                fprintf(outputFile,"list:");
                
                // find which type of list
                int list_type = it->second.getListType();
                if(list_type == TYPE_INT) fprintf(outputFile,"%-8s","int");
                else if(list_type == TYPE_FLOAT) fprintf(outputFile,"%-8s","float"); 
                else if(list_type == TYPE_BOOL) fprintf(outputFile,"%-8s","bool");
                else if(list_type == TYPE_STR) fprintf(outputFile,"%-8s","string");

                break;
            }

            case TYPE_FUNC: {
                fprintf(outputFile,"func:");
                
                // find which type of list
                int list_type = it->second.getFuncType();
                if(list_type == TYPE_INT) fprintf(outputFile,"%-8s","int");
                else if(list_type == TYPE_FLOAT) fprintf(outputFile,"%-8s","float"); 
                else if(list_type == TYPE_BOOL) fprintf(outputFile,"%-8s","bool");
                else if(list_type == TYPE_STR) fprintf(outputFile,"%-8s","string");
                else if(list_type == TYPE_VOID) fprintf(outputFile,"%-8s","void");
                else if(list_type == TYPE_LIST) fprintf(outputFile,"%-8s","list");

                break;
            }

            case TYPE_CLASS: {
                fprintf(outputFile,"%-13s","class");
                break;
            }
        }

        // print the scope of the symbol
        fprintf(outputFile,"%-8d",it->second.getSymbolScope());

        // print the line nos of the symbol reference
        vector<int> lines = it->second.getLineRefs();
        fprintf(outputFile,"%-7d\n",lines.front());
        fprintf(outputFile,"\n\n\n");
    }
}

void dumpAllSTs(FILE* outputFile, SymbolTable* table) {
    if(table->desc != "") {
        char* prnt = const_cast<char*> ((table->desc).c_str());
        fprintf(outputFile,"%s\n\n",prnt);
    }
    else fprintf(outputFile,"Symbol Table\n\n");
    // print the current hashtable
    table->dumpST(outputFile,table);
    // subsequently, print all the child hashtables
    vector<SymbolTable*>::iterator it;
    for(it = table->children.begin(); it != table->children.end(); it++) {
        dumpAllSTs(outputFile,*it);
    }
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/

#endif // SYMBOL_TABLE_CPP
