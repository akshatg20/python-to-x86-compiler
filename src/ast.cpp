#ifndef AST_CPP
#define AST_CPP

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <queue>
#include <stdarg.h>
#ifndef AST_HPP
#include "ast.hpp"
#endif
#ifndef UTILS_HPP
#include "utils.hpp"
#endif
using namespace std;


/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF AST **************************************/

/*
1) AST construction is done on basis of the grammar. Whenever a production is reduced an AST node is made.
2) AST construction assumes that there are no two consecutive operators without an operand in between which essentially means cases
like "operator operator operator operand" do not occur. This is very rare anyways and in general not permitted by the grammar.
This assumption breaks down in cases like - NOT NOT NOT IN array => This is allowed by the grammar but may not supported.
3) Special structural features of the AST -
a) 
4) If type annotation for a function parameter or function return type is missing then we are assuming it to be None.
*/

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF AST **************************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.
extern char *inputfile_path,*outputfile_path,*errorfile_path,*astfile_path,*dotfile_path;
extern int DOT_GENERATION,AST_GENERATION,PARSE_TREE_GENERATION;


/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// Global AST construction nodes
ASTNode* root;

// Other variables to control the working under AST construction.
int counter = 0;
int AST_DEBUG_OUTSIDE_VERBOSE = 0;
int AST_DEBUG_INSIDE_VERBOSE = 0;
int AST_STRUCTURE_DEBUG = 0;

// This variable determines whether an AST will be constructed or a parse tree
bool isAST = false;

// Possible unary operators in a python code based on the semantic analysis of grammar
vector<string> unary_operators = {":", "raise", "assert", "finally", "except", "not", "*", "**", "if", "return", "else"};

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

int setDebugNum()
{
        static int x = 0;
        return ++x;
}

// AST node creation routine.
ASTNode* createNode(string type, string content)  {
        ASTNode* node = new ASTNode(type, content);
        if(content != EPSILON && content != "") node->full_content = node->content;
        node->children = deque<ASTNode*>();
        node->name = "";
        node->debug_type = "";
        // giving default values to all nodes
        node->lineno = 0;
        node->columnno = 0;
        node->debug_num = 0;
        
        node->tr = new string("");
        node->fl = new string("");
        node->next = new string("");
        node->code = new string("");
        node->addr = new string("");
        node->val = new string("NULL");
        node->call = new string("");
        
        node->T = NULL;
        node->declarations = vector<STentry*>();
        node->names = deque<string>();
        node->label = "";
        node->table = NULL;


        return node;
}

// The main tree generation function which constructs and joins the whole AST or Parse Tree based on
// the flag passed in the boolean "isAST".
ASTNode* processNodes(string name, int numNodes, ...)  
{
        // All the arguments passed to the function is stored in "arr" vector using <stdarg.h> library routines.
        vector<ASTNode*> arr; // This is a vector to store the arguments passed to the function
        va_list args;
        va_start(args, numNodes);
        for (int i = 0; i < numNodes; ++i)  {
                ASTNode* arg = va_arg(args, ASTNode*);
                arr.push_back(arg);
        }
        va_end(args);

        ASTNode* node = NULL;
        if(AST_STRUCTURE_DEBUG == 1) { // Building of DEBUG Tree
                // Simplify the parse tree by removing all non-terminals producing empty string.
                vector<ASTNode*> arr_simplified;
                for (int i = 0; i < arr.size(); ++i)  {
                        if(arr[i] == NULL) continue;
                        ASTNode* arg = arr[i];
                        if(arg->content != EPSILON) arr_simplified.push_back(arg);
                }
                arr = arr_simplified;
                numNodes = arr.size();

                // Simplify the parse tree by removing all non-terminals generating only one non-terminal or terminal further.
                if(arr.size() == 1) {
                        (arr[0]->type) = name;
                        return arr[0];
                }

                if(numNodes > 0) node = createNode(name, "");
                else node = createNode(name, EPSILON);
                for(int x=0; x<arr.size(); x++) {
                        ASTNode* i = arr[x];
                        if(i != NULL) (node->children).push_back(i);
                }
        }
        else if(isAST == false) { // Building of Parse Tree
                if(numNodes > 0) node = createNode(name, "");
                else node = createNode(name, EPSILON);
                for(int x=0; x<arr.size(); x++) {
                        ASTNode* i = arr[x];
                        if(i != NULL) {
                                (node->children).push_back(i);
                                // cout << (i->full_content) << "\n";
                                if(i->full_content != EPSILON) (node->full_content) += (i->full_content);
                        }
                }
        }
        else { // Building of AST
                // Simplify the AST by removing all non-terminals producing empty string.
                vector<ASTNode*> arr_simplified;
                for (int i = 0; i < arr.size(); ++i)  {
                        if(arr[i] == NULL) continue;
                        ASTNode* arg = arr[i];
                        if(arg->content != EPSILON) arr_simplified.push_back(arg);
                        else {
                                // Check this border case implementation for recursive (both left recursive and right recursive) productions
                                // This is useful for - trailers, continued_argument and many others
                                if((arg->children).size() > 0) {
                                        arg->content = "";
                                        arr_simplified.push_back(arg);
                                }
                        }
                }
                arr = arr_simplified;
                numNodes = arr.size();

                // Simplify the AST by removing all non-terminals generating only one non-terminal or terminal further.
                if(numNodes == 1) {
                        (arr[0]->type) = name;
                        return arr[0];
                }

                // Special simplifications for different cases for construction of AST
                string content = ""; // Content to be added in the current node while building AST
                if(name == "funcdef") { // Simplification for Function Definition
                        content = "def";
                }
                else if(name == "atom_expr") { // Simplification for Atomic Expression
                        if(numNodes > 2) { arr.pop_back(); content = "await"; }
                }
                else if(name == "") {
                        // No extra handling required here. The program generates the other exception
                        // cases correctly by handling in the 2nd pass of the AST.
                }

                if(numNodes > 0) node = createNode(name, content);
                else node = createNode(name, EPSILON);
                for(int x=0; x<arr.size(); x++) {
                        ASTNode* i = arr[x];
                        if(i != NULL) (node->children).push_back(i);
                }   
        }

        node->debug_num = setDebugNum();
        node->debug_type = node->type +" - " + to_string(node->debug_num) + " - " + node->name;

        return node;
}

// This returns a true if the condition at the root node places a criteria of a unary operator.
// All cases are hardcoded based on the grammar.
bool case_unary_operator(ASTNode* root) {
        // A unary operator should have only one child.
        if((root->children).size() != 1) return false;
        
        // Check if the operator belongs to the set of possible unary operators
        bool check = false;
        for(int i=0; i<unary_operators.size(); i++) {
                if((root->content) == unary_operators[i]) { check = true; break; }
        }
        if(check == false) return false;
        else return true;

        // THE BELOW CODE IS USELESS WE CAN SIMPLIFY THE CODE BY RETURNING TRUE ABOVE DIRECTLY - HOWEVER TEST THIS CLAIM !!!
        // ELSE in an else statement is a unary operator if it is the only operator.
        if(((root->content) == "else") && ((root->type) == "else_stmt")) return true;
        // COLON in an annassign statement is a unary operator if it is the only operator.
        if(((root->content) == ":") && ((root->type) == "annassign")) return true;
        // COLON in a subscript statement is a unary operator if it is the only operator.
        if(((root->content) == ":") && ((root->type) == "subscript")) return true;
        // COLON in a sliceop statement is a unary operator if it is the only operator.
        if(((root->content) == ":") && ((root->type) == "sliceop")) return true;
        // RAISE in a raise_stmt statement is a unary operator if it is the only operator.
        if(((root->content) == "raise") && ((root->type) == "raise_stmt")) return true;
        // ASSERT in a assert_stmt statement is a unary operator if it is the only operator.
        if(((root->content) == "assert") && ((root->type) == "assert_stmt")) return true;
        // FINALLY in a finally_stmt statement is a unary operator if it is the only operator.
        if(((root->content) == "finally") && ((root->type) == "finally_stmt")) return true;
        // EXCEPT in an except_clause statement is a unary operator if it is the only operator.
        if(((root->content) == "except") && ((root->type) == "except_clause")) return true;
        // NOT in a not_test statement is a unary operator if it is the only operator.
        if(((root->content) == "not") && ((root->type) == "not_test")) return true;
        // RETURN in a return_stmt statement is a unary operator if it is the only operator.
        if(((root->content) == "return") && ((root->type) == "return_stmt")) return true;
        // IF in a comp_if statement is a unary operator if it is the only operator.
        if(((root->content) == "if") && ((root->type) == "comp_if")) return true;
        // STAR in a star_expr statement is a unary operator if it is the only operator.
        if(((root->content) == "*") && ((root->type) == "star_expr")) return true;
        // STAR in an argument statement is a unary operator if it is the only operator.
        if(((root->content) == "*") && ((root->type) == "argument")) return true;
        // DOUBLE_STAR in a dictorsetmaker statement is a unary operator if it is the only operator.
        if(((root->content) == "**") && ((root->type) == "dictorsetmaker")) return true;
        // DOUBLE_STAR in a continued_dictorset statement is a unary operator if it is the only operator.
        if(((root->content) == "**") && ((root->type) == "continued_dictorset")) return true;
        // DOUBLE_STAR in an argument statement is a unary operator if it is the only operator.
        if(((root->content) == "**") && ((root->type) == "argument")) return true;
        
        // Matches with non of the unary operator cases so it should not be a unary operator
        return false;
}

// Simplify the AST given the root node of the constructed AST
ASTNode* simplify_ast(ASTNode* root) {
        // "flag" to check whether an added child was the first child of the parent or not.
        // In case of first child the child's terminal should come first in case of terminal concatenation based simplification.
        int n = (root->children).size(), flag = 0;
        deque<ASTNode*> new_children;
        for(int i=0; i<n; i++) {
                ASTNode* node = simplify_ast((root->children)[i]);
                
                // Simplify the AST by removing all empty children from the new_children list.
                if(node == NULL) continue;
                if((node->content) == EPSILON) continue;
                if((node->content) == "" && (node->children).size() == 0) continue;

                if(n > 1 && i == 0) flag = 1; // First child from more than 1 children is getting added.
                new_children.push_back(node);
        }
        (root->children) = new_children;
        
        if(root->content == EPSILON && (root->children).size() == 0) return NULL;
        else if(root->content == "" && (root->children).size() == 0) return NULL;
        else if((root->children).size() == 0) return root;
        else {
                if(root->content == EPSILON) {
                        if(AST_DEBUG_OUTSIDE_VERBOSE) { // This is an erreneous case - If this kind of thing happens then why ??
                                cout << "[AST]: A->ε recursive simplification done in AST for " << root->type << "\n";
                        }
                        root->content = ""; // Error correction
                }

                // This is AST simplification for the nodes with only one child. However, this cannot be done
                // for cases where we have a unary operator.
                if((root->children).size() == 1 && case_unary_operator(root) == false) {
                        (root->children)[0]->type = root->type; // Keep the "type" of the node at the upper level.
                        if((root->content).length() > 0 && (root->content) != EPSILON) {
                                if(((root->children)[0]->content).length() > 0 && ((root->children)[0]->content) != EPSILON) {
                                        if(flag == 0) {
                                                ((root->children)[0]->content) = (root->content)  + "$" + ((root->children)[0]->content);
                                        }
                                        else ((root->children)[0]->content) = ((root->children)[0]->content) + "$" +  (root->content);
                                }
                                else ((root->children)[0]->content) = (root->content);
                        }
                        // This simplification commented below is not needed.
                        // else if(((root->children)[0]->content) == EPSILON) (root->children)[0]->content = "";
                        return (root->children)[0];
                }
                else return root; // Check if any more cases of simplification are possible
        }

        // Code should never reach here
        return NULL;

}

// Generate new ID for each node in the AST or Parse Tree for the purpose of dot script generation.
int getNewId() 
{
        return ++counter;
}

// Write tree to dot file with node, id and filename
// This is the recursive dot code generation routine. Acts as a helper function only.
pair<string,string> writeTree_recursive(ASTNode* node, int id) {
    string def = "";
    string arr = "";
    def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content)+")\"];\n";
    for (int i = 0; i < node->children.size(); i++) {
        int childId = getNewId();
        arr = arr + "node" + to_string(id) + " -- node" + to_string(childId) + ";\n";
        pair<string,string> p = writeTree_recursive(node->children[i], childId);
        def = def + p.first;
        arr = arr + p.second;
    }
    return pair<string,string>(def,arr);
}

// Write tree to dot file with node, id and filename
// This is the main routine to be called from the parser at the end of parsing
int writeTree(ASTNode* node, int id, char* filePath, char* astPath, char* parsePath) {
    // writing it as string
    string def = "", arr = "";
    def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content) + ")\"];\n";
    for (int i = 0; i < node->children.size(); i++) {
        int childId = getNewId();
        arr = arr + "node" + to_string(id) + " -- node" + to_string(childId) + ";\n";
        pair<string,string> p = writeTree_recursive(node->children[i], childId);
        def = def + p.first;
        arr = arr + p.second;
    }
    string stringContent = def + "\n" + arr;
    // over with string
    
    if(AST_GENERATION == 1 || DOT_GENERATION == 1 || PARSE_TREE_GENERATION == 1) {
        if(strlen(filePath) == 0) strcpy(filePath, "dot_file.dot");
        FILE* file = fopen(filePath, "w");
        if(!file) {
                fprintf(stderr, "[COMPILER ERROR]: Failed to create file %s\n", filePath);
                return 1;
        }
        fprintf(file, "Graph {\n%s\n}\n", const_cast<char*>(stringContent.c_str()));
        fclose(file);

        // Run the command to create AST or Parse Tree for the Input program
        if(AST_GENERATION == 1 || PARSE_TREE_GENERATION == 1) {
                string filePath_string(filePath); // File path
                string astpath_string(astPath);
                string parsepath_string(parsePath);
                string command = ""; // Command to execute
                if(AST_GENERATION == 1) command = "dot -Tpdf " + filePath_string + " -o " + astpath_string;
                else command = "dot -Tpdf " + filePath_string + " -o " + parsepath_string;
                int result = system(const_cast<char*>(command.c_str())); // Execute the command
                if(result != 0) { // Check if the command executed successfully
                        fprintf(stderr, "[COMPILER ERROR]: Error in executing the dot script.\n");
                        return 1;
                }
                if(DOT_GENERATION == 0) {
                        command = "rm " + filePath_string; // Command to execute
                        int result = system(const_cast<char*>(command.c_str())); // Execute the command
                        if(result != 0) { // Check if the command executed successfully
                                fprintf(stderr, "[COMPILER ERROR]: An internal error occurred.\n");
                                return 1;
                        }
                }
        }
    }

    return 0;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/

#endif // AST_CPP
