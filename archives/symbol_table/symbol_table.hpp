#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <unordered_map>
#include <map>
using namespace std;

// type of tokens
#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STR 2
#define TYPE_BOOL 3
#define TYPE_LIST 4
#define TYPE_FUNC 5
#define TYPE_CLASS 6
#define TYPE_VOID 7
#define TYPE_UNDF 8

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

// All classes and structures that you want to declare should go here.

// A structure to hold the four primitive data types
struct primitiveDataType {
    int ival;
    float fval;
    string strval;
    bool boolval;
};
typedef struct primitiveDataType PDT;

// A structure to store parameters of a particular function
struct Param {
    int param_type;                                 // type of paramater
    string param_name;                              // name of parameter
    PDT param_default_val;                          // stores the default value of the param, if any
};
typedef struct Param Param;

struct FuncAttrs {
    // attributes required in case of functions
    int func_type;                                  // output type of function
    int num_params;                                 // number of parameters of the function
    vector<Param> funcParams;                       // list of parameters of the function
};
typedef struct FuncAttrs FuncAttrs;

// Symbol table entry class
class STentry {
    private:
    int symbol_type;                                // for example, int , float, class etc.
    int symbol_size;                                // length of the type, for example int - 4, float - 8, custom for lists, functions, classes
    int scope_level;                                // specifies the scope of the current entry
    vector<int> refPoints;                          // stores the line nos where the symbol was used

    // attributes required in case of primitive data types (PDTs)
    PDT var;                                        // primitive data type variable value                                    

    // attributes required in case of lists
    int list_type;                                  // type of variables to be stored in the list
    int list_size;                                  // size of the list
    int* list_addr;                                 // base address of the list

    // attributes required in case of functions
    FuncAttrs func_attr;                            // function details

    // attributes required in case of classes
    int num_attrs;                                  // number of attributes of the class
    vector<Param> classAttrs;                       // list of attributes of the class
    vector<FuncAttrs> memFuncs;                     // list of member functions of the class
    

    public:
    // Default Constructor
    STentry();
    // Constructor
    STentry(int type, int scope, int size = 0);
    // Helper function to update line nos
    void addLineNo(int lineno);
    // Helper function to update values for primitive data types
    void updatePDTValues(int ival = 0, float fval = 0.0, string strval = "", bool bval = false);
    // Helper functions to access private variables
    int getSymbolType();
    int getSymbolScope();
    vector<int> getLineRefs();
    int getListType();
    int getFuncType();
    void setFuncDetails(int func_type, int num_params, vector<Param> params);
    void setClassDetails(int num_attrs, vector<Param> classAttrs, vector<FuncAttrs> memFuncs);

};
typedef struct STentry STentry; 

class SymbolTable {
    private:
    unordered_map<string, STentry> hashTable;        // the hash table for the current node 
    public:
    vector<SymbolTable*> children;                   // children of current node   
    SymbolTable* parent;                             // parent of current node
    string desc;                                     // description of symbol table   
    // Constructor
    SymbolTable(SymbolTable* parent, string msg = "") { this->parent = parent; this->desc = msg; }
    // function to add description about the symbol table
    void addDescription(string msg);
    // function to add variable to the symbol table
    void addBasicEntry(string lexeme, int type, int size, int scope, int lineno, int ival = 0, float fval = 0.0, string strval = "", bool bval = false);
    // function to add details about functions in the symbol table
    void addFuncionDetails(string lexeme, int func_type, int num_params, vector<Param> params);
    // function to add details about classes in the symbol table
    void addClassDetails(string lexeme, int num_attrs, vector<Param> classAttrs, vector<FuncAttrs> memFuncs);
    // function to lookup entry in the symbol table
    STentry* lookup(string lexeme);
    // function to dump the symbol table
    void dumpST(FILE* outputFile, SymbolTable* table);
    // function to increment the scope level and create a new symbol table for the new scope
    void incr_scope();
    // function to decrement the scope level
    void decr_scope();
};

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** FUNCTION DECLARATIONS ********************************************************/

// All functions that you want to declare should go here.

// function to print all symbol tables, should be called with the globalST
void dumpAllSTs(FILE* outputFile, SymbolTable* currTable);

/*********************************** FUNCTION DECLARATIONS ********************************************************/

#endif // SYMBOL_TABLE_HPP
