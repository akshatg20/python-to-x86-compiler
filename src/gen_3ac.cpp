#ifndef GEN_3AC_CPP
#define GEN_3AC_CPP

#include <iostream>
#include <vector>
#include <cstdarg>
#include <string>
#ifndef GEN_3AC_HPP
#include "gen_3ac.hpp"
#endif
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
#ifndef AST_HPP
#include "ast.hpp"
#endif
using namespace std;

#define CHECK(z) else if(name == z)

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF 3AC IR ***********************************/

// Write any assumptions that you take in the comment below
/*
----
*/

/*********************************** ASSUMPTIONS FOR THE CONSTRUCTION OF 3AC IR ***********************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.

// Global AST or Parse Tree root ASTNode
extern ASTNode* root;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.
int temprorary_3ac_counter = 0;
int label_3ac_counter = 0;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

string* gen(string s) {
    return new string(s);
}

string* label(string* s) {
    *s = *s + "\n";
    return s;

}

bool evalbool(string* s)
{
    // #cantwrite : seeing s (val) convert it to appropriate boolean value
    // comment below
    return true;
}
string* bool2val(bool b)
{
    if(b)
        return new string("true");
    return new string("false");

}

string* newTemp() {
    temprorary_3ac_counter++;
    string x = "t" + to_string(temprorary_3ac_counter);
    string* ptr = new string(x);
    return ptr;
}


string* newLabel() {
    label_3ac_counter++;
    string x = "L" + to_string(label_3ac_counter);
    string* ptr = new string(x);
    return ptr;
}

string* newLabel(string x) {
    string* ptr = new string(x);
    return ptr;
}

std::string* merge(int count = 0, ...) {
    std::string* result = new std::string();
    va_list args;
    va_start(args, count); // Initialize the argument list with the count

    for (int i = 0; i < count; ++i) {
        std::string* nextString = va_arg(args, std::string*); // Get the next argument
        if (nextString) {
            *result += "\n" + *nextString;
        }
    }

    va_end(args); // Clean up
    return result;
}

string *lab, *lab2, *temp, *temp2;
unordered_map<string, pair<vector<string> , vector<string> > > func_args;
unordered_map<string, int> k2n;
unordered_map<int, string*> n2c;
string curr_func;
int x=0;


int debug3ac = 1;
int after3ac = 0;
int printcode = 0;

// To be called on root ASTNode of parse tree.
// This will construct the complete 3AC code after running the second pass through the parse tree.
// To be called on root ASTNode of parse tree
int generate3AC(ASTNode* n) {

    if(n == NULL) 
        return 0;
    
    // COMMENT THIS LINE BEFORE STARING THE CODING PART
    // printf("Code for 3AC generation has started\n");
    // string x = "Comment this line";
    // (root->code) = gen(x);

    string name = (n->name);
    if(false) {}
    // Segment 1
    CHECK("start.1")
    {
        if(debug3ac) cout<<"At start.1"<<"(" << n->type << ")\n";

        n->next = newLabel("exit");
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(3, 
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n"),
            gen("exit:"));

        cout<< " DONE with 3AC" << endl;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("file_input.1")
    {
        if(debug3ac) cout<<"At file_input.1"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        if(debug3ac) cout<<(n->children)[0]->name<<"(" << n->type << ")\n";

        generate3AC((n->children)[0]);

        if(debug3ac) cout<<"Code for file_input.1"<<"(" << n->type << ")\n";

        n->code = merge(1,
            n->children[0]->code
            // gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_file_input.1")
    {
        if(debug3ac) cout<<"At continued_file_input.1"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
            // gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";

        if(debug3ac) cout<< " Abacus colours" <<endl;

        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    
    CHECK("continued_file_input.2")
    {
        if(debug3ac) cout<<"At continued_file_input.2"<<"(" << n->type << ")\n";
        (n->children)[0]->next = newLabel();
        (n->children)[1]->next = n->next;

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->code = merge(2,
            n->children[0]->code,
            //label((n->children)[0]->next),
            n->children[1]->code
            // gen("goto " + *((n->children)[1]->next) + "\n")
        );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";

        if(debug3ac) cout<<" Pencil box\n" <<endl;

        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    
    CHECK("continued_file_input.3")
    {
        if(debug3ac) cout<<"At continued_file_input.3"<<"(" << n->type << ")\n";
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";

        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("funcdef.1")
    {
        // #cantwrite : right now supports only position-based arguments
        // #noteadded : test is the return type + parameters need handling of type
        if(after3ac) cout<<"HellowShashank\n";

        if(debug3ac) cout << "At funcdef.1" << "(" << n->type << ")\n";

        if(after3ac) cout<<" in funcdef" <<endl;

        n->children[6]->next = n->next;

        curr_func = n->children[1]->content; // better if we could replace curr_func with symbol table something -> dollar name
        func_args[curr_func].first = vector<string>(); 
        func_args[curr_func].second = vector<string>();

        if(debug3ac) cout<< " HI WORLD1" <<endl;

        if(after3ac) cout<<"In funcdef.1\n" ;
        generate3AC(n->children[2]);
        generate3AC(n->children[4]);
        generate3AC(n->children[6]);
        if(after3ac) cout<<"In funcdef.1\n";

        if(debug3ac) cout<< " HI WORLD2" <<endl;

        n->code = merge(8,
                    gen("function " + n->children[1]->content + ":"),
                    gen("beginfunc"),
                    n->children[2]->code,
                    label(lab),
                    n->children[6]->code,
                    gen("goto " + *(n->children[6]->next)),
                    gen("return"),
                    gen("endfunc")
        );
        
        if(debug3ac) cout<< " HI WORLD3" <<endl;
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";

        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("parameters.1")
    {
        if(debug3ac) cout << "At parameters.1" << "(" << n->type << ")\n";

        if(after3ac) cout<< "In parameters" <<endl;

        n->children[1]->next =n->next;

        generate3AC(n->children[1]);

        n->code = merge(2,
                    n->children[1]->code
                    // gen("goto " + *(n->children[1]->next))
                );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("parameters.2") 
    {
        if(debug3ac) cout << "At parameters.2" << "(" << n->type << ")\n";
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("typedargslist.1")
    {
        if(debug3ac) cout << "At typedargslist.1" << "(" << n->type << ")\n";

        // #cantwrite : could not include the tougher case
        lab = newLabel();
        temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        
        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[3]);
        
        func_args[curr_func].second.push_back(*(n->children[2]->val));

        n->code = merge(6,
                    label(lab),
                    gen(*(temp) + "= popparam"),
                    gen(*(temp2) +  "=" + *(temp) +  "!=NULL"),
                    gen("if" + *(temp2) + "goto" + *label(lab)),
                    gen(*(temp) + "=" + *(n->children[2]->val)),
                    label(lab2)
                );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("typedargslist.2")
    {
        if(debug3ac) cout << "At typedargslist.2" << "(" << n->type << ")\n";
        // #cantwrite : could not include the tougher case
        lab= newLabel();
        temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[3]);

        func_args[curr_func].second.push_back(*(n->children[2]->val));

        n->code = merge(6,
                    label(lab),
                    gen(*(temp) + "= popparam"),
                    gen(*(temp2) +  "=" + *(temp) +  "!=NULL"),
                    gen("if" + *(temp2) + "goto" + *label(lab)),
                    gen(*(temp) + "=" + *(n->children[2]->val)),
                    label(lab2)
                );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("typedargslist.3")
    {
        if(debug3ac) cout << "At typedargslist.3" << "(" << n->type << ")\n";
        // #cantwrite : could not include the tougher case
        lab= newLabel();
        temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        func_args[curr_func].first.push_back(*(n->children[1]->val));

        // if(!evalbool(temp2->val))
        //     return -1; // error

                n->code = merge(5,
                    label(lab),
                    gen(*(temp) + "= popparam"),
                    gen(*(temp2) +  "=" + *(temp) +  "!=NULL"),
                    gen("if" + *(temp2) + "goto" + *label(lab)),
                    label(lab2)
                );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("typedargslist.4")
    {
        if(debug3ac) cout << "At typedargslist.4" << "(" << n->type << ")\n";

        // #cantwrite : could not include the tougher case
        lab= newLabel();
        temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        func_args[curr_func].first.push_back(*(n->children[1]->val));

        // if(!evalbool(temp2->val))
        //     return -1; // error

        n->code = merge(5,
                    label(lab),
                    gen(*(temp) + "= popparam"),
                    gen(*(temp2) +  "=" + *(temp) +  "!=NULL"),
                    gen("if" + *(temp2) + "goto" + *label(lab)),
                    label(lab2)
                );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("next_arg.1") 
    {
        if(debug3ac) cout << "At next_arg.1" << "(" << n->type << ")\n";
        // #cantwrite : could not include the tougher case
        lab= newLabel();
        temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[4]);

        n->code = merge(6,
                    label(lab),
                    gen(*(temp) + "= popparam"),
                    gen(*(temp2) +  "=" + *(temp) +  "!=NULL"),
                    gen("if" + *(temp2) + "goto" + *label(lab)),
                    gen(*temp + "=" + *(n->children[4]->val)),
                    label(lab2)
                );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("next_arg.2") 
    {
        if(debug3ac) cout << "At next_arg.2" << "(" << n->type << ")\n";
        lab= newLabel();
        temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[3]);

        n->code = merge(5,
                    label(lab),
                    gen(*(temp) + "= popparam"),
                    gen(*(temp2) +  "=" + *(temp) +  "!=NULL"),
                    gen("if" + *(temp2) + "goto" + *label(lab)),
                    label(lab2)
                ); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("next_arg.3") {
        if(debug3ac) cout << "At next_arg.3" << "(" << n->type << ")\n";

        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("tfpdef.1") 
    {
        if(debug3ac) cout << "AT tfpdef.1" << "(" << n->type << ")\n";

        n->val = new string((n->children)[0]->content);
        
        generate3AC((n->children)[2]);

        n->code = (n->children)[2]->code;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("tfpdef.2") 
    {
        if(debug3ac) cout << "AT tfpdef.1" << "(" << n->type << ")\n";
        return -1;
    }
    
    CHECK("stmt.1")
    {
        if(debug3ac) cout<<"At stmt.1"<<"(" << n->type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code
            // gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";

        if(debug3ac) cout<<"HiBoy\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("stmt.2")
    {
        if(debug3ac) cout<<"At stmt.2"<<"(" << n->type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code
            // gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";

        if(debug3ac) cout<<"HiBoy2\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("simple_stmt.1")
    {
        if(debug3ac) cout<<"At simple_stmt.1"<<"(" << n->type << ")\n";
        (n->children)[0]->next = newLabel();
        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(4,
            n->children[0]->code,
            label((n->children)[0]->next),
            n->children[1]->code
            // gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("simple_stmt.2")
    {
        if(debug3ac) cout<<"At simple_stmt.2"<<"(" << n->type << ")\n";

        (n->children)[0]->next = newLabel();
        (n->children)[1]->next = n->next;

        

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        if(debug3ac) cout<<"Abacus tool"<<endl;

        n->code = merge(4,
            n->children[0]->code,
            label((n->children)[0]->next),
            n->children[1]->code
            // gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("next_small_stmt.1")
    {
        if(debug3ac) cout<<"At next_small_stmt.1"<<"(" << n->type << ")\n";
        (n->children)[0]->next = newLabel();
        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(4,
            n->children[0]->code,
            label((n->children)[0]->next),
            n->children[1]->code,
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("next_small_stmt.2")
    {
        if(debug3ac) cout<<"At next_small_stmt.2"<<"(" << n->type << ")\n";
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("small_stmt.1")
    {
        if(debug3ac) cout<<"At small_stmt.1"<<"(" << n->type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("small_stmt.2")
    {
        if(debug3ac) cout<<"At small_stmt.2"<<"(" << n->type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("small_stmt.3")
    {
        if(debug3ac) cout<<"At small_stmt.3"<<"(" << n->type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            (n->children)[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("small_stmt.4")
    {
        if(debug3ac) cout<<"At small_stmt.4"<<"(" << n->type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("small_stmt.5")
    {
        if(debug3ac) cout<<"At small_stmt.5"<<"(" << n->type << ")\n";
        // #notrequired
        return -1;
    }

    CHECK("expr_stmt.1")
    {
        // #cantwrite : can't use the :test in annassign
        // [ testlist ]  [ : test = test ] <- single assignment and report error if multiple assignments , handle the type check thing
        // [ testlist ] [ : test ] <- declaration of type  #cantwrite as don't know what is meant by declaration of form a:int 
        // the information of type is ignored in annassign so ensure that it is handled
        if(debug3ac) cout<<"At expr_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(4,
            n->children[0]->code,
            n->children[1]->code,
            gen(*(n->children[0]->val) + " = " + *(n->children[1]->addr) + "\n"),
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("expr_stmt.2")
    {
        if(debug3ac) cout<<"At expr_stmt.2"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        string* x = newTemp();
        string* y = newTemp();

        // #cantwrite : unknown error with merge
        n->code = merge(6,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(x) + " = " + *((n->children)[0]->val) + "\n"),
            gen (*(y) + " = " + *(x) + " " + *(n->children[1]->val) + " " + *((n->children[2])->val) + "\n"),
            gen(*((n->children)[0])->val + " = " + *(y)),
            gen("goto " + *((n->children)[3]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("expr_stmt.3")
    {
        if(debug3ac) cout<<"At expr_stmt.3"<<"(" << n->type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        string* compotype = newTemp();

        n->code = merge(4,
            n->children[0]->code,
            n->children[1]->code,
            gen(*(compotype) + " = " + *(n->children[1]->addr) + "\n"),
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }


    CHECK("continued_expr_stmt.1")
    {
        // cantwrite : cant use the do the merge type thing in annassign (type)
        if(debug3ac) cout<<"At continued_expr_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[2]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[2]);

        n->addr = newTemp();

        n->code = merge(4,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->addr) + " = " + *((n->children)[2]->val) + "\n"),
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("continued_expr_stmt.2")
    {
        // #cantwrite : cant use the mergetype thing (here nothing needs to be merged but same framework)
        if(debug3ac) cout<<"At continued_expr_stmt.2"<<"(" << n->type << ")\n";
        n->code = merge();
        cout<<"Hewllow"<<endl;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("annassign.1")
    {
        // cantwrite : cant use the :test in annassign (type)
        if(debug3ac) cout<<"At annassign.1"<<"(" << n->type << ")\n";

        (n->children)[3]->next = n->next;

        generate3AC((n->children)[3]);

        n->addr = newTemp();

        n->code = merge(3,
            n->children[3]->code,
            gen(*(n->addr) + " = " + *((n->children)[3]->val) + "\n"),
            gen("goto " + *((n->children)[3]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("annassign.2")
    {
        // #cantwrite : cant use the :test in annassign (type)
        if(debug3ac) cout<<"At annassign.2"<<"(" << n->type << ")\n";

        (n->children)[3]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[3]);

        n->code = merge(2,
            n->children[2]->code,
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("testlist_star_expr.1")
    {
        // #cantwrite : make a composite type for assignment purposes by running the rules, used the val parameter so have to set val (used in continued_expr_stmt)

        if(debug3ac) cout<<"At testlist_star_expr.1"<<"(" << n->type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(3,
            n->children[0]->code,
            n->children[1]->code,
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("testlist_star_expr.2")
    {
        // #cantwrite : make a composite type for assignment purposes by running the rules, used the val parameter so have to set val (used in continued_expr_stmt)

        if(debug3ac) cout<<"At testlist_star_expr.2"<<"(" << n->type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(3,
            n->children[0]->code,
            n->children[1]->code,
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("flow_stmt.1")
    {
        // #cantwrite : have written simply the words however don't know if it is right to use break, continue and return as words and not specify where to go
        // also omitted the child
        if(debug3ac) cout<<"At flow_stmt.1"<<"(" << n->type << ")\n";

        generate3AC((n->children)[0]);

        n->code = gen("break\n");
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
        // ommitted merge and next since break transfers control and no need of merge here
    }
    CHECK("flow_stmt.2")
    {
        // #cantwrite : have written simply the words however don't know if it is right to use break, continue and return as words and not specify where to go
        // also omitted the child
        if(debug3ac) cout<<"At flow_stmt.2"<<"(" << n->type << ")\n";

        generate3AC((n->children)[0]);

        n->code = gen("continue\n");
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
        // ommitted merge and next since continue transfers control and no need of merge here
    }
    CHECK("flow_stmt.3")
    {
        // #cantwrite : have written simply the words however don't know if it is right to use break, continue and return as words and not specify where to go
        // omitted the child
        if(debug3ac) cout<<"At flow_stmt.3"<<"(" << n->type << ")\n";

        n->code = gen("return\n");
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
        // ommitted merge and next since return transfers control and no need of merge here
    }

    CHECK("global_stmt.1")
    {
        // #cantwrite : push this part to relevant part of the code in 3AC
        if(debug3ac) cout<<"At global_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[2]->next = n->next;

        generate3AC((n->children)[2]);

        n->code = merge(3,
            gen("global : " + n->children[1]->content),
            n->children[2]->code,
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("global_stmt.2")
    {
        // #cantwrite : push this part to relevant part of the code in 3AC
        if(debug3ac) cout<<"At global_stmt.2"<<"(" << n->type << ")\n";

        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("stmt_helper.1")
    {
        if(debug3ac) cout<<"At stmt_helper.1"<<"(" << n->type << ")\n";

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen(", " + n->children[1]->content)
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("stmt_helper.2")
    {
        if(debug3ac) cout<<"At stmt_helper.2"<<"(" << n->type << ")\n";

        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
    }

    // Section 5
    CHECK("compound_stmt.1")
    {
        if(debug3ac) cout<<"At compound_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

        if(debug3ac) cout<<"At compound_stmt.1"<<"(" << n->type << ")\n";
    }
    CHECK("compound_stmt.2")
    {
        if(debug3ac) cout<<"At compound_stmt.2"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("compound_stmt.3")
    {
        if(debug3ac) cout<<"At compound_stmt.3"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("compound_stmt.4")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At compound_stmt.4"<<"(" << n->type << ")\n";

        return -1;
    }
    CHECK("compound_stmt.5")
    {
        if(debug3ac) cout<<"At compound_stmt.5"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        if(after3ac) cout<<"In compound_stmt.5\n";
        if(after3ac) cout<<n->children[0]->type<<endl;
        generate3AC((n->children)[0]);
        if(after3ac) cout<<"In compound_stmt.5\n";

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
        
    }
    CHECK("compound_stmt.6")
    {
        if(debug3ac) cout<<"At compound_stmt.6"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("if_stmt.1")
    {
        if(debug3ac) cout<<"At if_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[1]->tr =newLabel();
        (n->children)[1]->fl = newLabel();
        (n->children)[3]->next = n->next;
        (n->children)[4]->tr = n->next;
        (n->children)[4]->fl = newLabel();
        (n->children)[5]->next = n->next;

        generate3AC((n->children)[1]);
        generate3AC((n->children)[3]);
        generate3AC((n->children)[4]);
        generate3AC((n->children)[5]);

        

        n->code = merge(9,
            n->children[1]->code,
            label((n->children)[1]->tr),
            n->children[3]->code,
            gen("goto " + *((n->children)[3]->next) + "\n"),
            label((n->children)[2]->fl),
            n->children[4]->code,
            label((n->children)[4]->fl),
            gen(*(n->children[5]->code)),
            gen("goto " + *((n->children)[5]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("elif_stmt.1")
    {
        if(debug3ac) cout<<"At elif_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[0]->tr = n->next;
        (n->children)[0]->fl = newLabel();
        (n->children)[2]->tr = newLabel();
        (n->children)[2]->fl = n->next;
        (n->children)[4]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[2]);
        generate3AC((n->children)[4]);

        // #cantwrite : merge type thing
        n->code = merge(6,
            n->children[0]->code,
            label((n->children)[0]->fl),
            n->children[2]->code,
            label((n->children)[2]->tr),
            n->children[4]->code,
            gen("goto " + *((n->children)[4]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("elif_stmt.2")
    {
        if(debug3ac) cout<<"At elif_stmt.2"<<"(" << n->type << ")\n";

        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("else_stmt.1")
    {
        if(debug3ac) cout<<"At else_stmt.1"<<"(" << n->type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[1]);

        n->code = merge(2,
            n->children[1]->code,
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("while_stmt.1")
    {
        string* begin = newLabel();
        n->children[1]->tr = newLabel();
        n->children[1]->fl = newLabel();
        n->children[3]->next = begin;
        n->children[4]->next = n->next;

        generate3AC(n->children[1]);
        generate3AC(n->children[3]);
        generate3AC(n->children[4]);

        n->code = merge(9,
            gen("goto " + *begin + "\n"),
            label(begin),
            n->children[1]->code,
            label(n->children[1]->tr),
            n->children[3]->code,
            gen("goto " + *(n->children[3]->next) + "\n"),
            label(n->children[1]->fl),
            n->children[4]->code,
            gen("goto " + *(n->children[4]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("forcheck")
    {
        string* tt=newTemp();
        string* tt2=newTemp();
        string* tt3=newTemp();

        n->code = merge(6,
            gen(*(tt3) + " = " + *(tt) + " < n"), // replace this with list size
            gen("ifFalse " + *(tt3) + " goto " + *(n->fl)),
            gen(n->content + " = " + *(n->val) + "[" + *(tt) + "]"),
            gen("goto " + *(n->tr)),
            gen(*(tt2) = *(tt) + " + 1"),
            gen(*(tt) + " = " + *(tt2))
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
        
    }
    CHECK("for_stmt.1")
    {
        string* tempf = newTemp(); // range list stored here -> have to change it
        string tempstr = n->children[1]->content;
        const char* dummy = tempstr.c_str();
        ASTNode *forcheck = createNode("forcheck", dummy);
        forcheck->val = tempf;

        string* begin = newLabel();
        forcheck->tr = newLabel();
        forcheck->fl = newLabel();
        n->children[5]->next = begin;
        n->children[6]->next = n->next;

        generate3AC(forcheck);
        generate3AC(n->children[5]);
        generate3AC(n->children[6]);

        n->code = merge(9,
            gen("goto " + *begin + "\n"),
            label(begin),
            forcheck->code,
            label(forcheck->tr),
            n->children[5]->code,
            gen("goto " + *(n->children[5]->next) + "\n"),
            label(forcheck->fl),
            n->children[6]->code,
            gen("goto " + *(n->children[6]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("try_stmt.1")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At try_stmt.1"<<"(" << n->type << ")\n";

        return -1;
    }
    CHECK("try_stmt.2")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At try_stmt.2"<<"(" << n->type << ")\n";

        return -1;
    }

    CHECK("except_stmt.1")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At except_stmt.1"<<"(" << n->type << ")\n";

        return -1;
    }
    CHECK("except_stmt.2")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At except_stmt.2"<<"(" << n->type << ")\n";

        return -1;
    }

    CHECK("finally_stmt.1")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At finally_stmt.1"<<"(" << n->type << ")\n";

        return -1;
    }
    CHECK("finally_stmt.2")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At finally_stmt.2"<<"(" << n->type << ")\n";

        return -1;
    }

    CHECK("except_clause.1")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At except_clause.1"<<"(" << n->type << ")\n";

        return -1;
    }
    CHECK("except_clause.2")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At except_clause.2"<<"(" << n->type << ")\n";

        return -1;
    }
    CHECK("except_clause.3")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout<<"At except_clause.3"<<"(" << n->type << ")\n";

        return -1;
    }

    CHECK("suite.1")
    {
        if(debug3ac) cout<<"At suite.1"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("suite.2")
    {
        // #cantwrite : take care of INDENT and DEDENT as per scope rules
        if(debug3ac) cout<<"At suite.2"<<"(" << n->type << ")\n";

        (n->children)[2]->next = n->next;

        generate3AC((n->children)[2]);

        n->code = merge(2,
            n->children[2]->code,
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        if(debug3ac) cout<<"SHASHWAT"<<endl;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("smts.1")
    {
        if(debug3ac) cout<<"At smts.1"<<"(" << n->type << ")\n";

        (n->children)[0]->next = newLabel();
        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(4,
            n->children[0]->code,
            label((n->children)[0]->next),
            n->children[1]->code,
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("smts.2")
    {
        if(debug3ac) cout<<"At smts.2"<<"(" << n->type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("test.1")
    { 
        // ON IT
        if(debug3ac) cout<<"At test.1"<<"(" << n->type << ")\n";

        n->children[2]->tr = newLabel();
        n->children[2]->fl = newLabel();
        n->children[0]->tr = n->tr;
        n->children[0]->fl = n->fl;
        n->children[0]->next = n->next;
        n->children[4]->tr = n->tr;
        n->children[4]->fl = n->fl;
        n->children[4]->next = n->next;
        n->addr = newTemp();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[4]);

        // #cantwrite evalbool() function to compute boolean values of functions
        if(evalbool(n->children[2]->val))
        {
            n->val = n->children[0]->val;
        }
        else
        {
            n->val = n->children[4]->val;
        }

        n->code = merge(11,
            n->children[2]->code,
            gen("if " + *(n->children[2]->addr) + " goto " + *(n->children[2]->tr) + "\n"),
            gen("ifFalse" + *(n->children[2]->addr) + " goto " + *(n->children[2]->fl) + "\n"),
            label(n->children[0]->tr),
            n->children[0]->code,
            gen(*(n->addr) + " = " + *(n->children[0]->val) + "\n"),
            gen("goto " + *(n->children[0]->next) + "\n"),
            label(n->children[4]->fl),
            n->children[4]->code,
            gen(*(n->addr) + " = " + *(n->children[4]->val) + "\n"),
            gen("goto " + *(n->children[4]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    CHECK("test.2")
    {
        if(debug3ac) cout<<"At test.2"<<"(" << n->type << ")\n";

        n->children[0]->tr = newLabel();
        n->children[0]->fl = newLabel();
        n->children[0]->next = n->next;
        n->addr = newTemp();

        generate3AC(n->children[0]);

        n->val = n->children[0]->val;

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *(n->children[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("test_nocond")
    {
        if(debug3ac) cout<<"At test_nocond"<<"(" << n->type << ")\n";

        n->children[0]->tr = n->tr;
        n->children[0]->fl = n->fl;
        n->children[0]->next = n->next;

        generate3AC(n->children[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *(n->children[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("or_test.1") 
    {
        if(debug3ac) cout << "At or_test.1" << "(" << n->type << ")\n";
        // or_test -> and_test continued_or_test
        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("continued_or_expr.1") 
    {
        if(debug3ac) cout << "At continued_or_expr.1" << "(" << n->type << ")\n";
        // continued_or_expr -> continued_or_expr OR and_expr

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " or " + *(n->children[2]->val) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    

    CHECK("continued_or_expr.2") 
    {
        if(debug3ac) cout << "At continued_or_expr.2" << "(" << n->type << ")\n";
        // continued_or_expr ->  empty
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("and_test.1") 
    {
        if(debug3ac) cout << "At and_test.1" << "(" << n->type << ")\n";
        // and_test -> not_test continued_and_test
        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("continued_and_expr.1") 
    {
        if(debug3ac) cout << "At continued_and_expr.1" << "(" << n->type << ")\n";
        // continued_and_expr -> continued_and_expr AND not_test

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " and " + *(n->children[2]->val) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    

    CHECK("continued_and_expr.2") 
    {
        if(debug3ac) cout << "At continued_and_expr.2" << "(" << n->type << ")\n";
        // continued_and_expr ->  empty
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    // doubt
    CHECK("not_test.1") 
    {
        if(debug3ac) cout << "At not_test.1" << "(" << n->type << ")\n";
        // NOT not_test
        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        (n->val) = newTemp();
        n->code =  merge(2,
            n->children[1]->code,
            gen(*(n->val) + " = " + " ! " +  *(n->children[0]->val) + " * " + *(n->children[1]->val) + "\n")
            );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    
    }
    
    // doubt
    CHECK("not_test.2") 
    {
        if(debug3ac) cout << "AT not_test.2" << "(" << n->type << ")\n";

        generate3AC((n->children)[0]);
        n->code = n->children[0]->code;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("comparison.1") 
    {
        if(debug3ac) cout << "AT comparison.1" << "(" << n->type << ")\n";
        // comparison -> expr comparison_stmt
        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    // cantwrite
    CHECK("comparison_stmt.1") 
    {
        if(debug3ac) cout << "At comparison_stmt.1" << "(" << n->type << ")\n";
        // comparison_stmt -> comparison_stmt comp_op expr

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + *(n->children[1]->val) + *(n->children[2]->val) + "\n")
        ); 
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("comparison_stmt.2") 
    {
        if(debug3ac) cout << "At comparison_stmt.2" << "(" << n->type << ")\n";
        // comparison_stmt -> empty
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    // cantwrite
    CHECK("comp_op.1") {
        if(debug3ac) cout << "At comp_op.1" << "(" << n->type << ")\n";
        
        n->val = new string(n->children[0]->content);
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    // cantwrite
    CHECK("comp_op.2") {
        if(debug3ac) cout << "At comp_op.2" << "(" << n->type << ")\n";

        n->val = new string(n->children[0]->content);
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }

    CHECK("comp_op.3") {
        if(debug3ac) cout << "At comp_op.3" << "(" << n->type << ")\n";
        return -1;
    }

    CHECK("comp_op.4") {
        if(debug3ac) cout << "At comp_op.4" << "(" << n->type << ")\n";
        return -1;
    }

    CHECK("comp_op.5") {
        if(debug3ac) cout << "At comp_op.5" << "(" << n->type << ")\n";
        return -1;
    }

    CHECK("star_expr.1") {
        if(debug3ac) cout << "At star_expr.1" << "(" << n->type << ")\n";
        return -1;
    }

    CHECK("expr.1") 
    {
        if(debug3ac) cout << "At expr.1" << "(" << n->type << ")\n";
        // expr -> xor_expr continued_xor_expr
        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_xor_expr.1") 
    {
        if(debug3ac) cout << "At continued_xor_expr.1" << "(" << n->type << ")\n";
        // continued_xor_expr -> continued_xor_expr BITWISE_OR xor_expr

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " | " + *(n->children[2]->val) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_xor_expr.2") 
    {
        if(debug3ac) cout << "At continued_xor_expr.2" << "(" << n->type << ")\n";
        // continued_xor_expr ->  empty
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("xor_expr.1") 
    {
        if(debug3ac) cout << "At xor_expr.1" << "(" << n->type << ")\n";
        // xor_expr -> and_expr continued_and_expr

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_and_expr.1") 
    {
        if(debug3ac) cout << "At continued_and_expr.1" << "(" << n->type << ")\n";
        // continued_and_expr -> continued_and_expr CARET and_expr

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " ^ " + *(n->children[2]->val) + "\n")
        );      
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
 
    }

    CHECK("continued_and_expr.2") 
    {
        if(debug3ac) cout << "At continued_and_expr.2" << "(" << n->type << ")\n";
        // continued_and_expr -> empty

        n->code = merge();  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
    }

    CHECK("and_expr.1") 
    {
        if(debug3ac) cout << "At and_expr.1" << "(" << n->type << ")\n";
        // and_expr -> shift_expr continued_shift_expr

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_shift_expr.1") 
    {
        if(debug3ac) cout << "At continued_shift_expr.1" << "(" << n->type << ")\n";
        // continued_shift_expr -> continued_shift_expr BITWISE_AND shift_expr

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " & " + *(n->children[2]->val) + "\n")
        );  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
     
    }

    CHECK("continued_shift_expr.2") 
    {
        if(debug3ac) cout << "At continued_shift_expr.2" << "(" << n->type << ")\n";
        // continued_shift_expr -> empty

        n->code = merge(); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
   
    }    

    CHECK("shift_expr.1") 
    {
        if(debug3ac) cout << "At shift_expr.1" << "(" << n->type << ")\n";
        // and_expr -> shift_expr continued_shift_expr

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_arith_expr.1") 
    {
        if(debug3ac) cout << "At continued_arith_expr.1" << "(" << n->type << ")\n";
        // continued_arith_expr -> continued_arith_expr LEFT_SHIFT arith_exp

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " << " + *(n->children[2]->val) + "\n")
        ); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
      
    }

    CHECK("continued_arith_expr.2") 
    {
        if(debug3ac) cout << "At continued_arith_expr.2" << "(" << n->type << ")\n";
        // continued_arith_expr -> continued_arith_expr RIGHT_SHIFT arith_exp

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " >> " + *(n->children[2]->val) + "\n")
        ); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
      
    }

    CHECK("continued_arith_expr.3") 
    {
        if(debug3ac) cout << "At continued_arith_expr.3" << "(" << n->type << ")\n";
        // continued_arith_expr -> empty

        n->code = merge();  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
    }

    CHECK("arith_expr.1") 
    {
        if(debug3ac) cout << "At arith_expr.1" << "(" << n->type << ")\n";
        // arith_expr -> term continued_term

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }  

    CHECK("continued_term.1") 
    {
        if(debug3ac) cout << "At continued_term.1" << "(" << n->type << ")\n";
        // continued_term -> continued_term PLUS term

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " + " + *(n->children[2]->val) + "\n")
        );  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
     
    } 

    CHECK("continued_term.2") 
    {
        if(debug3ac) cout << "At continued_term.2" << "(" << n->type << ")\n";
        // continued_term -> continued_term MINUS term

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " - " + *(n->children[2]->val) + "\n")
        ); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
      
    }

    CHECK("continued_term.3") 
    {
        if(debug3ac) cout << "At continued_term.3" << "(" << n->type << ")\n";
        // continued_term -> empty

        n->code = merge();  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    
    }

    CHECK("term.1") 
    {
        if(debug3ac) cout << "At term.1" << "(" << n->type << ")\n";
        // term -> factor continued_factor

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("continued_factor.1") 
    {
        if(debug3ac) cout << "At continued_factor.1" << "(" << n->type << ")\n";
        // continued_factor -> continued_factor STAR factor

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " * " + *(n->children[2]->val) + "\n")
        );  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
     
    } 

    CHECK("continued_factor.2") 
    {
        if(debug3ac) cout << "At continued_factor.2" << "(" << n->type << ")\n";
        // continued_factor -> continued_factor DIV factor

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " / " + *(n->children[2]->val) + "\n")
        );  
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
     
    }

    CHECK("continued_factor.3") 
    {
        if(debug3ac) cout << "At continued_factor.3" << "(" << n->type << ")\n";
        // continued_factor -> continued_factor AT factor

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " @ " + *(n->children[2]->val) + "\n")
        ); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
      
    }

    CHECK("continued_factor.4") 
    {
        if(debug3ac) cout << "At continued_factor.4" << "(" << n->type << ")\n";
        // continued_factor -> continued_factor REM factor

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " % " + *(n->children[2]->val) + "\n")
        );   
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    
    }

    CHECK("continued_factor.5") 
    {
        if(debug3ac) cout << "At continued_factor.5" << "(" << n->type << ")\n";
        // continued_factor -> continued_factor FLOORDIV factor

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " // " + *(n->children[2]->val) + "\n")
        ); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
      
    }

    CHECK("continued_factor.6") 
    {
        if(debug3ac) cout << "At continued_factor.6" << "(" << n->type << ")\n";
        // continued_factor -> EMPTY

        n->code = merge(); 
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
      
    }

    CHECK("power.1")
    {
        if(debug3ac) cout<<"At power.1"<<"(" << n->type << ")\n";

        n->children[0]->next = n->next;
        n->addr = newTemp();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->code = merge(4,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->addr) + " = " + *(n->children[0]->val) + " ** " + *(n->children[2]->val) + "\n"),
            gen("goto " + *(n->children[2]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("power.2")
    {
        if(debug3ac) cout<<"At power.2"<<"(" << n->type << ")\n";

        n->children[0]->next = n->next;
        generate3AC(n->children[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *(n->children[0]->next) + "\n")
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("atom_expr.1")
    {
        if(debug3ac) cout<<"At atom_expr.1"<<"(" << n->type << ")\n";

        return -1; // #notrequired
    }
    CHECK("atom_expr.2")
    {
        if(debug3ac) cout<<"At atom_expr.1"<<"(" << n->type << ")\n";

        n->children[0]->next = n->next;
        generate3AC(n->children[0]);

        n->val = merge(2,
        n->children[0]->val, 
        n->children[2]->val);

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("trailers.1") 
    {
        if(debug3ac) cout<<"At trailers.1"<<"(" << n->type << ")\n";

        n->val = merge(2, n->children[0]->val, n->children[1]->val);
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("trailers.2") 
    {
        if(debug3ac) cout<<"At trailers.2"<<"(" << n->type << ")\n";

        n->val = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }



    // manupulate the codes of atom
    CHECK("atom.1") 
    {
        if(debug3ac) cout<<"At atom.1"<<"(" << n->type << ")\n";

        generate3AC(n->children[1]);
        n->val = n->children[1]->val; // rather manupulate this
        n->code = merge();
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.2") 
    {
        if(debug3ac) cout<<"At atom.2"<<"(" << n->type << ")\n";
        // rather manupulate this
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.3") 
    {
        if(debug3ac) cout<<"At atom.3"<<"(" << n->type << ")\n";
        generate3AC(n->children[1]);
        n->val = n->children[1]->val; // rather manupulate this
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.4") 
    {
        if(debug3ac) cout<<"At atom.4"<<"(" << n->type << ")\n";
        // rather manupulate this
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.5") 
    {
        if(debug3ac) cout<<"At atom.5"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("atom.6") 
    {
        if(debug3ac) cout<<"At atom.6"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("atom.7") 
    {
        if(debug3ac) cout<<"At atom.7"<<"(" << n->type << ")\n";
        n->val = n->children[0]->val;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.8")  
    {
        if(debug3ac) cout<<"At atom.8"<<"(" << n->type << ")\n";
        n->val = n->children[0]->val;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.9") 
    {

        if(debug3ac) cout<<"At atom.9"<<"(" << n->type << ")\n";
        n->val = n->children[0]->val;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.10") 
    {

        if(debug3ac) cout<<"At atom.10"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("atom.11") 
    {

        if(debug3ac) cout<<"At atom.11"<<"(" << n->type << ")\n";
        n->val = n->children[0]->val;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.12") 
    {

        if(debug3ac) cout<<"At atom.12"<<"(" << n->type << ")\n";
        n->val = n->children[0]->val;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("atom.13") 
    {

        if(debug3ac) cout<<"At atom.13"<<"(" << n->type << ")\n";
        n->val = n->children[0]->val;
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("strings.1") 
    {

        if(debug3ac) cout<<"At strings.1"<<"(" << n->type << ")\n";
        n->val = merge(2,n->children[0]->val, new string(n->children[1]->content));
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("strings.2") 
    {

        if(debug3ac) cout<<"At strings.1"<<"(" << n->type << ")\n";
        n->val = new string(n->children[0]->content);
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }


    CHECK("testlist_comp.1") 
    {
        if(debug3ac) cout<<"At testlist_comp.1"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("testlist_comp.2") 
    {
        if(debug3ac) cout<<"At testlist_comp.2"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("testlist_comp.3") 
    {
        if(debug3ac) cout<<"At testlist_comp.2"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("testlist_comp.4") 
    {
        if(debug3ac) cout<<"At testlist_comp.1"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("testlist_comp.5") 
    {
        if(debug3ac) cout<<"At testlist_comp.1"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("testlist_comp.6") 
    {
        if(debug3ac) cout<<"At testlist_comp.1"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("continued_testlist.1") 
    {
        if(debug3ac) cout<<"At testlist_comp.2"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + ", " + *(n->children[2]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("continued_testlist.2") 
    {
        if(debug3ac) cout<<"At continued_testlist_comp.2"<<"(" << n->type << ")\n";
        return -1;
    }
    CHECK("continued_testlist.3") 
    {
        if(debug3ac) cout<<"At continued_testlist.3"<<"(" << n->type << ")\n";
        
        n->val = new string();
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("trailer.1") 
    {
        if(debug3ac) cout<<"At trailer.1"<<"(" << n->type << ")\n";
        
        n->val = n->children[2]->code;
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("trailer.2") 
    {
        if(debug3ac) cout<<"At trailers.2"<<"(" << n->type << ")\n";
        n->val = new string("");
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("trailer.3") 
    {
        if(debug3ac) cout<<"trailer.3"<<"(" << n->type << ")\n";
            return -1;
    }
    CHECK("trailer.4") 
    {
        
        if(debug3ac) cout<<"At trailers.2"<<"(" << n->type << ")\n";
        n->val = new string("." + (n->children[1]->content));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("exprlist.1") 
    {
        if(debug3ac) cout<<"At exprlist.1"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("exprlist.2") 
    {
        if(debug3ac) cout<<"At exprlist.2"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
            
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("exprlist.3") 
    {
        if(debug3ac) cout<<"exprlist.3"<<"(" << n->type << ")\n";
            return -1;
    }
    CHECK("exprlist.4") 
    {
        if(debug3ac) cout<<"exprlist.4"<<"(" << n->type << ")\n";
            return -1;
    }
    CHECK("continued_exprlist.1") 
    {
        if(debug3ac) cout<<"At continued_exprlist.2"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + ", " + *(n->children[2]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("continued_exprlist.2") 
    {
        if(debug3ac) cout<<"continued_exprlist.2"<<"(" << n->type << ")\n";
            return -1;

    }
    CHECK("continued_exprlist.3") 
    {
        if(debug3ac) cout<<"continued_exprlist.3"<<"(" << n->type << ")\n";
        n->val = new string();
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("testlist.1") 
    {
        if(debug3ac) cout<<"At testlist.1"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("testlist.2") 
    {
        if(debug3ac) cout<<"At testlist.2"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("continued_comma_test.1") 
    {
        if(debug3ac) cout<<"At continued_comma_test.1"<<"(" << n->type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + ", " + *(n->children[2]->val));
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("continued_comma_test.2") 
    {
        if(debug3ac) cout<<"At continued_comma_test.1"<<"(" << n->type << ")\n";

        n->val = new string();
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    // Add more code here

    CHECK("arglist.1")
    {
        x=0;
        n2c.clear();
        k2n.clear();

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        // #cantwrite -> get to the function call and add flag for class and functions
        string callfunc=curr_func; // change this to value that comes from atom

        int i;
        for(i=0;i<func_args[callfunc].first.size();i++) // compulsory parameters
        {
            string* tt = newTemp();

            n->code = merge(3,
                n->code,
                gen(*(tt) + " = " + *(n2c[i])),
                gen("param " + *(tt))
            );
        }
        
        int curr = i;
        for(i=0;i<func_args[callfunc].second.size();i++) // compulsory parameters
        {
            if(k2n.find(func_args[callfunc].second[i]) != k2n.end())
            {
                int v = k2n[func_args[callfunc].second[i]];
                string* tt = newTemp();
                
                n->code = merge(3,
                n->code,
                gen(*(tt) + " = " + *(n2c[v])),
                gen("param " + *(tt))
                );
            }
            else
            {
                n->code = merge(3,
                n->code,
                gen("param NULL")
                );
            }
        }

        n->code = merge(4,
            n->code,
            gen("stackpointer +xxx"),
            gen("call" + callfunc + to_string(func_args[callfunc].first.size() + func_args[callfunc].second.size())),
            gen("stackpointer -yyy")
        );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("arglist.2")
    {
        
        x=0;
        n2c.clear();
        k2n.clear();

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        // #cantwrite -> get to the function call and add flag for class and functions
        string callfunc=curr_func; // change this to value that comes from atom

        int i;
        for(i=0;i<func_args[callfunc].first.size();i++) // compulsory parameters
        {
            string* tt = newTemp();

            n->code = merge(3,
                n->code,
                gen(*(tt) + " = " + *(n2c[i])),
                gen("param " + *(tt))
            );
        }
        
        int curr = i;
        for(i=0;i<func_args[callfunc].second.size();i++) // compulsory parameters
        {
            if(k2n.find(func_args[callfunc].second[i]) != k2n.end())
            {
                int v = k2n[func_args[callfunc].second[i]];
                string* tt = newTemp();
                
                n->code = merge(3,
                n->code,
                gen(*(tt) + " = " + *(n2c[v])),
                gen("param " + *(tt))
                );
            }
            else
            {
                n->code = merge(3,
                n->code,
                gen("param NULL")
                );
            }
        }

        n->code = merge(4,
            n->code,
            gen("stackpointer +xxx"),
            gen("call" + callfunc + to_string(func_args[callfunc].first.size() + func_args[callfunc].second.size())),
            gen("stackpointer -yyy")
        );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("continued_argument.1")
    {
        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->code = merge(2,
            n->children[0]->code,
            n->children[2]->code
        );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("continued_argument.2")
    {
        n->code = merge();
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }


    }
    CHECK("argument.1")
    {
        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        k2n[*(n->children[0]->val)] = x;
        n2c[x] = n->children[2]->val;
        x++;

        n->code = merge();
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }
    CHECK("argument.2")
    {

        generate3AC(n->children[0]);

        n2c[x] = n->children[1]->val;
        x++;

        n->code = merge();
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }


    CHECK("classdef.1")
    {
        if(debug3ac) cout << "At classdef.1" << endl;

        n->children[6]->next = n->next;

        generate3AC(n->children[3]);
        generate3AC(n->children[6]);

        n->code = merge(
            // 8, 
            //         gen("class" + n->children[1]->content + ":"),
            //         gen("beginfunc"),
            //         n->children[3]->code,
            //         label(lab),
            //         n->children[6]->code,
            //         gen("goto " + *(n->children[6]->next)),
            //         gen("return"),
            //         gen("endfunc")
                );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("classdef.2")
    {
        if(debug3ac) cout << "At classdef.2" << endl;

        n->children[5]->next = n->next;

        generate3AC(n->children[5]);

        n->code = merge(
            // 7, 
            //         gen("class" + n->children[1]->content + ":"),
            //         gen("beginfunc"),
            //         label(lab),
            //         n->children[5]->code,
            //         gen("goto " + *(n->children[5]->next)),
            //         gen("return"),
            //         gen("endfunc")
            );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
            if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("classdef.3") 
    {
        if(debug3ac) cout << "AT classdef.3" << endl;

        n->children[3]->next = n->next;

        generate3AC(n->children[3]);

                n->code = merge(
                    // 7, 
                    // gen("class" + n->children[1]->content + ":"),
                    // gen("beginfunc"),
                    // label(lab),
                    // n->children[3]->code,
                    // gen("goto " + *(n->children[3]->next)),
                    // gen("return"),
                    // gen("endfunc")
        );
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    // ****************************************** TERMINALS IN THE GRAMMAR ***********************************************
    CHECK("AUGASSIGN")
    {
        if(debug3ac) cout<<"At AUGASSIGN"<<"(" << n->type << ")\n";

        size_t pos = (n->content).find('=');
        if (pos != std::string::npos) 
        {
            (n->val) = new string((n->content).substr(0, pos));
        }
        else
        {
            return -1;
        }
        
        if(after3ac) cout << "At" << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
    }

    // ****************************************** TERMINALS IN THE GRAMMAR ***********************************************

    // ****************************************** NON TERMINALS IN THE GRAMMAR *******************************************

    // ****************************************** NON TERMINALS IN THE GRAMMAR *******************************************

    return 0;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/


#endif // GEN_3AC_CPP




