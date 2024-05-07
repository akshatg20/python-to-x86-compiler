#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <deque>
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
using namespace std;

#define EPSILON "ε"

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

// The AST generated while parsing is a Tree with the following struct
// representing one node of the tree. The root of the tree is represented in "root" node.
// The "root" is ready for use AFTER PARSING IS COMPLETE.
struct ASTNode {
        // ALL THESE ARE COMPUTED DURING THE CONSTRUCTION OF PARSE TREE OR AST
        // Basic storage elements for storing details about the TOKEN
        string type;
        string debug_type;
        string name;
        string content;
        string full_content; // Store the full content in the non-terminal using this string
        deque<struct ASTNode*> children;
        // Details about the position of the non-terminal
        int debug_num; // Numbering of parse tree visits
        int lineno;
        int columnno;
        // Data elements required for construction of the 3AC from the Parse Tree
        string* tr;
        string* fl;
        string* next;
        string* code;
        string* addr;
        string* val;
        string* call;
        
        // ALL THESE ARE COMPUTED DURING THE TOP-DOWN PARSE OF SEMANTIC ANALYZER
        // Details about the Type of the non-terminal represented by this node
        TypeExpression* T;
        // Details about the variables declared under the body of the non-terminal
        vector<STentry*> declarations;
        deque<string> names;
        // Label that can be used for the labelling in 3AC
        string label;
        // This is set by the type system for further mapping creation in 3AC which will be used later in x86 generation
        SymbolTable* table;

        // Parameterized Constructor to construct AST or Parse Tree
        ASTNode() : type(""), content("") {}
        ASTNode(string type, string content = "") : type(type), content(content) {}
};
typedef struct ASTNode ASTNode;

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** FUNCTION DECLARATIONS ********************************************************/

// AST node creation routine.
ASTNode* createNode(string type, string content = "");

// Generate new ID for each node in the AST or Parse Tree for the purpose of dot script generation.
int getNewId();

// The main tree generation function which constructs and joins the whole AST or Parse Tree based on
// the flag passed in the boolean "isAST".
ASTNode* processNodes(string name,int numNodes, ...);

// Write tree to dot file with node, id and filename
// This is the main routine to be called from the parser at the end of parsing
int writeTree(ASTNode* node,int id, char* filePath, char* astPath, char* parsePath);

// Simplify the AST given the root node of the constructed AST
ASTNode* simplify_ast(ASTNode* root);

/*********************************** FUNCTION DECLARATIONS ********************************************************/

#endif // AST_HPP
