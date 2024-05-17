#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <unordered_map>
#include <map>
#include <deque>
using namespace std;

// TYPE TOKENS ARE MODIFIED HERE
// Type of Tokens
#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STR 2
#define TYPE_BOOL 3
// TYPE_LIST changed to TYPE_ARRAY -> Signifies the ARRAY type constructor - Pg 371 DRAG Book
#define TYPE_ARRAY 4
// Signifies the ARROW (->) type constructor - Pg 371 DRAG Book
#define TYPE_FUNC 5
// TYPE_CLASS changed to TYPE_RECORD -> Signifies the RECORD type constructor - Pg 371 DRAG Book
// This will be used for CLASS also - Which is not convered in DRAG Book
// We will consider CLASS to be a type which is a RECORD of it's Member Variables and Member Functions
#define TYPE_RECORD 6
#define TYPE_VOID 7
#define TYPE_UNDF 8

// Type of Errors
#define ERR_MISMATCH 0                  // type mismatch error
#define ERR_NOT_FOUND 1                 // symbol not found
#define ERR_SCOPE 2                     // scoping error
#define ERR_WRONG_PARAMS 3              // wrong params to the function
#define ERR_TYPECAST 4                  // wrong combination being tried to be typecasted
#define ERR_BOUNDS 5                    // out of bounds array access
#define ERR_WRG_USE 6                   // function used in incorrect context
#define ERR_UNDF 7                      // undefined data type
#define ERR_OTHER 8                     // other errors
#define WARNING 9                       // overloading warning

// Types of Scopes
#define GLOBAL_SCOPE 0
#define CLASS_SCOPE 1
#define FUNC_SCOPE 2
#define OTHER_SCOPE 3

// REQUIREMENTS FROM THE SYMBOL TABLE -
/*
1) The Type and Relative Address for their storage is saved in the symbol table entry for every name.
2) All functions related to type systems will be implemented in "symbol_table.cpp" only. They will be used in "parse.y" for type analysis.
3) Do we have to implement Runtime Storage Management ?
4) Do we have to implement recursive type - Given on page 372 of DRAG Book.
5) Do we have to implement Address Alignment of Page 374 of DRAG Book.
6) USER DEFINED TYPES are to be supported using the Symbol Table
7) The Cross Product Type Constructor of DRAG Book on Page 372 is not implemented and those cases will be handled from RECORDS only
    -> Is there a problem in this assumption ?
*/

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

// All classes and structures that you want to declare should go here.

// forward definition required
class SymbolTable;

// TYPE EXPRESSIONS ARE DETAILED IN Pg 371 of DRAG BOOK - IT IS IMPLEMENTED HERE
class TypeExpression {
public:
        // This denotes the type of the Expression.
        // Will either be one of the Type Tokens or a number denoting a declared type name during compile time.
        // Type Name declarations are to be supported by the Symbol Table implementation.
        // For example - class Devansh {} -> Then this name "Devansh" is now a new type name.
        int type;
        int space; // How much space in bytes will the Type denoted by a TypeExpression consume
        string encode; // String encoding of the type - Like int[2][3] == Array(2,Array(3,Integer)) -> Don't know whether it is useful
        string mangle; // This is used for name mangling in function overloading for x86 generation
        string name; // Important in case of user_defined types. If a type is user_defined then the name of the type is given here.
        // The lexeme whose type this TypeExpression denotes is stored as a pointer.
        // This points inside Symbol Table entry where lexeme is stored. This is specifically used for string type.
        // This is set after the TypeExpression is added to the 
        string* lexeme;
        // This will be 0 in general. However, if this denotes a CLASS then it will be the user_defined_type_number.
        // This flag shows if a Type is a class.
        int class_flag;

        // The following in the variables in UNION of all possible types.
        // The basic types - TYPE_INT, TYPE_FLOAT, TYPE_STR, TYPE_BOOL, TYPE_VOID, TYPE_UNDF - Will have none of these
        // Storage defined for TYPE_ARRAY and NULL for others
        int number;
        TypeExpression* array;
        // Storage defined for TYPE_FUNC and NULL for others
        TypeExpression* domain;
        TypeExpression* range;
        // Storage defined for TYPE_RECORD and EMPTY for other
        deque<TypeExpression*> fields;
        // In case if this RECORD represent a CLASS then the variable class_flag will be 1.
        // All types from which this type inherits will be stored in this vector.
        deque<TypeExpression*> inheritance;
        // In case of the particular identifier being of some user defined type the pointer to the TypeExpression of that
        // type will be stored within the TypeExpression. This will require support from Symbol Table.
        TypeExpression* user_defined;
        
private:
        // Checks and computes the correct amount of storage required to store this type.
        // Needs to be invoked again and again to compute the correct value of "space".
        int update_space();

public:
        // Default Constructor for the class - Initializes with 0 space and TYPE_UNDF as type
        TypeExpression();
        
        // Constructor for class object - Works based on the provided type
        // For basic types "fields" is irrelevant.
        // For ARRAY type "fields" contain only 1 element and number is used
        // For FUNC type "fields" have 2 elements
        // For RECORD type "fields" can be a generic vector
        // Size is used especially for "str" type where the length of the string should be given - Which is variable
        TypeExpression(
            int type,
            int number = -1,
            deque<TypeExpression*> fields = deque<TypeExpression*>(),
            int size = 0,
            int flag = 0,
            deque<TypeExpression*> inheritance = deque<TypeExpression*>()
        );

        // Checks whether the passed type is same as the type denoted by the object of this class.
        // Similar to the same_type() function declared below in this file.
        // Returns -1 in cases of errors like not defined type T
        int same_type(TypeExpression* T);
        int same_type_with_typecast(TypeExpression* T);
};
typedef class TypeExpression TypeExpression;

// This Structure will help in generation of Semantic Errors during the compilation
// A global variable of this structure is made and maintained by the Symbol Table
// Should atleast contain the Error Location with an error description string.
// A variable of "int" or "enum" type to denote the type of error.
// Any other important information about the error.
struct SemanticError {
    string msg;
    int lineno;
    int error_type;
};
typedef struct SemanticError SemanticError;

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

// Holds information useful during function calls
struct ActivationRecord {
  int stackMemAlloc;                    // stores the amount of bytes to be allocated on the stack for the function  
  vector<int> params;                   // offsets of integer/pointer parameters
  int returnAddr;                       // address to which function returns to
  int prevStackPointer;                 // previous address of the stack pointer
  unordered_map<string,int> savedVars;  // variables saved from caller, integer
  unordered_map<string,int> tempVars;   // offsets of temp values used during the function call, integer
  int numParams;                        // number of parameters
  int numVars;                          // number of local variables
  int sizeVars;                         // size occupied by local variables
  int sizeParams;                       // size occupied by parameters
};
typedef struct ActivationRecord ActivationRecord;

// Symbol table entry class
class STentry {
public:
    TypeExpression* symbol_type;                    // for example, int , float, class etc.
    int scope_level;                                // specifies the scope of the current entry
    int offset;                                     // offset of the symbol from the function declaration
    vector<int> refPoints;                          // stores the line nos where the symbol was used
    PDT var;                                        // primitive data type variable value                                    
    vector<Param> funcParams;                       // parameters in case of a function
    string lexeme;                                  // name of symbol, for convenience 
    string token;                                   // for example, NUMBER, STRING, NAME ...
    char* srcfilepath;                              // source file info
    int column;                                     // column no of the entry
    SymbolTable* tablePtr;                          // points to the symbol table for functions/classes

    // Default Constructor
    STentry();
    // Constructor
    STentry(string lexeme, TypeExpression* type, int lineno, int scope, string token, int column);
    // Helper function to update line nos
    void addLineNo();
    // Helper function to update values for primitive data types
    void updatePDTValues(int ival = 0, float fval = 0.0, string strval = "");

};
typedef struct STentry STentry; 

class SymbolTable {
public:
    unordered_map<string, STentry*> hashTable;       // the hash table for the current node 
    vector<SymbolTable*> children;                   // children of current node   
    SymbolTable* parent;                             // parent of current node 
    int type;                                        // type of symbol table
    string name;                                     // name of symbol table
    ActivationRecord* funcRecord;                    // holds important information for function calls

    // Default Constructor
    SymbolTable();
    // Constructor
    SymbolTable(SymbolTable* parent, int flag, string name);
    // function to dump the symbol table
    void dumpST(FILE* outputFile, SymbolTable* table);
};

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** FUNCTION DECLARATIONS ********************************************************/

// All functions that you want to declare should go here.

// BELOW ARE THE FUNCTIONS WHICH ARE TO BE IMPLEMENTED AS PART OF THE SYMBOL TABLE

// This is the main relative address computation routine.
// Please note the variable - extern SymbolTable* globalTable - Added in symbol_table.cpp -> Maybe useful for this function.
// This will be called ONLY ONCE throughout the execution of parser at the end of parsing process. So, the symbol table will be ready before call to this function.
// This function should compute the "offset" values for all the Symbol Table entries in the complete tree.
// RELATIVE ADDRESS COMPUTATION
// The virtual memory of the program when executing will contain a program variable segment where compile time variables are stored.
// The address at starting of that segment will be referred to as offset = 0.
// All static memory definitions (NOT DECLARATIONS) in program will have a UNIQUE offset value (stored in its Symbol Table Entry) denoting the the address where the value of that variable will be stored during the program execution.
//      FOR EXAMPLE - class X {}; -> DECLARES a class so no need for any offset for this.
//                    X obj;      -> DEFINES an object of the class - So, memory needs to be allocated for this so an "offset" required.
// The "offset" computation is to be done based on the Preorder Traversal over the Symbol Table Tree.
//      -> First all entries in root is given "offsets" starting from 0.
//      -> Then left subtree will be given offsets after storage of all root Symbol Table entries. Then right subtree.
//      FOR EXAMPLE -
//      Root Level - Global Symbol Table has 3 entries (INT [offset = 0], FLOAT [offset = 4] and ARRAY(2,ARRAY(3,INT)) [offset = 12])
//      Child 1 of Root - Has 1 entry (FUNCTION(Which has 2 variables defined inside its body - INT [offset = 36], BOOL [offset = 40]))
//      Child 2 of Root - Has 2 entries (STRING(size = 37) [offset = 41], BOOL [offset = 78])
//      With ADDRESS ALIGNMENT (Pg 374) last level will have offsets 44 (41->44) and 84 (44+37=81->84) -> Not clear whether this is to be implemented
// In case of any error return -1 and fill SemanticError appropriately. Otherwise return 0.
int compute_offsets(SymbolTable* table, int offset);

// Inline "add" function to be finally used in "parse.y"
// This function is made because the TypeExpression needs to store a pointer to the lexeme it points to
// But this pointer can be available only after adding the lexeme to Symbol Table. So, "lexeme" field
// of TypeExpression is changed after adding the entry to Symbol Table.
STentry* add(string lexeme, string token, TypeExpression* T, int lineno, int column, int* flag, SymbolTable* table = NULL);
void rectify_type(TypeExpression* T);

// LOOKUP NEEDS TO SUPPORT FUNCTION OVERLOADING AND OVERRIDING SO FUNCTIONALITY IS APPENDED WITH TYPE KEY
// function to lookup entry in the symbol table
// The key to lookup an entry is the "lexeme" and type "T" combined.
// The type will be specifically useful in cases of function overloading. Otherwise the "lookup" should be possible without it.
// IN CASES WHEN A FUNCTION IS NOT LOOKED UP IT IS NOT GUARANTEED THAT A TYPE-EXPRESSION WILL BE PROVIDED.
// In case of no error return the pointer to symbol table entry for this lexeme.
// In case of any error (like lookup not successful) return NULL and fill SemanticError appropriately.
STentry* lookup(string lexeme, TypeExpression* T = NULL);
STentry* lookup_restricted(string lexeme, TypeExpression* T = NULL);
STentry* lookupScope(string lexeme, TypeExpression* T = NULL);
STentry* lookup_restricted_scope(string lexeme, TypeExpression* T = NULL);

// function to increment the scope level and create a new symbol table for the new scope
int incr_scope(int scope_flag, string lexeme, TypeExpression* T = NULL);
// function to decrement the scope level
int decr_scope();


// Given pointer to a TypeExpression the Symbol Table should return a UNIQUE TYPE NUMBER for the user defined type T.
// This type number should be unique in Current Scope and Parent scopes. The name of this type will be "name".
// If this name is already used for another user defined type then the one declared later will be kept.
// If this name is used for some other identifier then it will be an error
// In case of some error return -1 and fill SemanticError structure appropriately
int define_type(TypeExpression* T, string name);
int withdraw_type(int type);

// Given the TYPE NUMBER return the pointer to TypeExpression corresponding to this type if this is a user defined type.
// The Returned TypeExpression should belong to the current scope or parent scope.
// Return NULL in case of any error (including cases if type <= 8) and fill SemanticError structure appropriately
TypeExpression* ret_user_defined(int type);

// Given pointer to a TypeExpression the Symbol Table should return -1 if the type is undefined in the current scope (including parent scopes)
// In case of well defined types the TYPE NUMBER should be returned. Type Number should always be >= 0
// In case of some error return -2 and fill SemanticError structure appropriately
int type_scope_check(TypeExpression* T, int flag = 0);

// THIS FUNCTION WILL REQUIRE MODIFICATION BASED ON NEW SYMBOL TABLE STRUCTURE
// function to print all symbol tables, should be called with the globalST
void dumpAllSTs(string DirPath, SymbolTable* currTable);

// function to fill activation records for all functions
int fillActivationRecords(SymbolTable* table);

// BELOW ARE THE FUNCTIONS WHICH ARE TO BE IMPLEMENTED AS PART OF THE TYPE SYSTEM

// This function tells whether two TypeExpressions are "Structurally Equivalent" or not.
// The function is an implementation of theorem specified on page 373 of DRAG book
// A similar function is also implemented as a member function in the class TypeExpression
// Returns -1 in cases of error like not defined types
//      -> Any error here will be fallout from Symbol so no need to fill SemanticError structure
int type_check(TypeExpression* T1, TypeExpression* T2);
int type_check_with_typecast(TypeExpression* T1, TypeExpression* T2);

// HELPER CONSTRUCTOR FUNCTIONS FOR TYPE EXPRESSION - BASED ON Pg 371-372 DRAG BOOK DESCRIPTION
TypeExpression* type_bool();                                                   // "bool" basic type constructor
TypeExpression* type_int();                                                    // "int" basic type constructor
TypeExpression* type_float();                                                  // "float" basic type constructor
TypeExpression* type_str(int size);                                            // "str" basic type constructor
TypeExpression* type_void();                                                   // "void" basic type constructor
TypeExpression* type_array(int number, TypeExpression* array);                 // "array" type constructor
TypeExpression* type_function(TypeExpression* domain, TypeExpression* range);  // "->" type constructor

// This will return NULL in case the given type does not qualify for scope checks.
// The error will be made available in SemanticError by Symbol Table.
TypeExpression* type_user_defined(int type);                                   // For "user_defined" type

// "record" type constructor - flag will be set to 0 if it is a normal record
// For classes - flag = 1 and inherit will be passed
TypeExpression* type_record(
    deque<TypeExpression*> fields,
    int flag = 0,
    deque<TypeExpression*> inherit = deque<TypeExpression*>(),
    string lexeme = ""
);

/*********************************** FUNCTION DECLARATIONS ********************************************************/

#endif // SYMBOL_TABLE_HPP
