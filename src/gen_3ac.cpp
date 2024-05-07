#ifndef GEN_3AC_CPP
#define GEN_3AC_CPP

#include <iostream>
#include <vector>
#include <cstdarg>
#include <string>
#include <stack>
#include <unordered_map>
#ifndef GEN_3AC_HPP
#include "gen_3ac.hpp"
#endif
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
#ifndef AST_HPP
#include "ast.hpp"
#endif
#include <regex>
using namespace std;
#include <algorithm>

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
extern unordered_map<string, SymbolTable*> labelMap;
extern SymbolTable* globalTable;

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.
int temprorary_3ac_counter = 0;
int label_3ac_counter = 0;
int flabel_3ac_counter = 0;
string *lab, *lab2, *temp, *temp2;
unordered_map<string, pair<vector<string> , vector<string> > > func_args;
unordered_map<string, int> k2n;
unordered_map<int, string*> n2c;
string curr_func;
stack<string> class_names;
bool isclassargs = false;
int x=0;
extern int DEBUG_3AC_INSIDE_VERBOSE;
extern int DEBUG_3AC_OUTSIDE_VERBOSE;


int debug3ac = 1;
int after3ac = 1;
// int printcode = 1;
// int debug3ac = DEBUG_3AC_OUTSIDE_VERBOSE;
// int after3ac = DEBUG_3AC_INSIDE_VERBOSE;
int printcode = 0;
int debugshash =1;
int dopass2 = 1;



/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

void filternewline(string* s);
void removerepeats(string* s);
void removetrailingnewlines(string* s);
void removenewlines(string* s);
void removeblankcolons(string* s);
int generate3AC(ASTNode* n);

std::stack<std::pair<std::unordered_map<std::string, int>, std::unordered_map<int, std::string*>>> stackArgScope;
int getArgScope()
{
    static int arg_scope = 0;
    return arg_scope++;
}

string mangle_name(string name, deque<TypeExpression*> params) {
    // "name" - Corresponds to the name of the function
    // "params" - Types of the parameters passed to a function
    string mangled = "_Z";
    int sz = name.length();
    if(!class_names.empty()) {
        // This case denotes that the given function is a member function of a class
        mangled = "_CZ";
        sz = sz + (class_names.top()).length() + 1;
        mangled = mangled + to_string(sz) + class_names.top() + "." + name;
    }
    else mangled = mangled + to_string(sz) + name;

    if(!class_names.empty()) {
        // In this case of a class the first extra term is a pointer type on the class
        mangled = mangled + "P" + class_names.top();
    }
    if(params.size() == 0) {
        if(class_names.empty()) mangled = mangled + "v";
    }
    else {
        // When the function has non-empty set of parameters than it will have some extra letters
        for(int i=0; i<params.size(); i++) mangled = mangled + (params[i]->mangle);
    }
    return mangled;
}

void removeemptygoto(string* s)
{
    // if ns has goto in its a line and it is not followed by any thing except spaces, remove it
    // scan line by line and if found such line, remove it
    string& ns = *s; // Use a reference to modify the original string

    string result;
    size_t pos = 0;
    while (pos != string::npos)
    {
        size_t newPos = ns.find('\n', pos);
        string currentLine = ns.substr(pos, newPos - pos);

        // If current line is not the same as previous, append it to result
        if (currentLine.find("goto") == string::npos)
        {
            result += '\n'+ currentLine; // Append newline before adding the line, except for the first line
        }
        else if(currentLine.find("goto") != string::npos)
        {
            size_t ps = currentLine.find("goto");
            bool flag=false;
            for(int i=ps+4;i<currentLine.size();i++)
            {
                if(currentLine[i]!=' ')
                {
                    flag = true;
                    break;
                }
            }

            if(flag)
            {
                result += '\n'+ currentLine; // Append newline before adding the line, except for the first line
            }
        }

        if (newPos == string::npos) break; // If at the end of the string, exit the loop
        pos = newPos + 1; // Move past the current newline character
    }

    *s = result; // Assign the processed string back to the original pointer
}

void removenewlines(string* s)
{
    string t="";
    for(int i=0;i<(*s).size();i++)
    {
        char c = (*s)[i];
        if( c!= '\n')
        {
            t = t+ c;
        }
    }
    *s = t;
}

void removetrailingnewlines(string* s)
{
    string& ns = *s; // Use a reference to modify the original string
    bool prev = false;
    int i;
    for (i = ns.size() - 1; i >= 0; --i)
    {
        if (ns[i] == '\n')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    ns = ns.substr(0, i + 1);
}

void removeblankcolons(string* s)
{
    string& ns = *s;

    string result;
    size_t pos = 0;

    while (pos != string::npos)
    {
        size_t newPos = ns.find('\n', pos);
        string currentLine = ns.substr(pos, newPos - pos);

        bool flag = false;
        for(int i=0;i<currentLine.size();i++)
        {
            if(currentLine[i]!=' ' && currentLine[i]!=':')
            {
                flag = true;
                break;
            }
        }

        if(flag)
        {
            result += '\n'+ currentLine;
        }

        if (newPos == string::npos) 
            break;
        pos = newPos + 1;
    }

    *s = result;
}

void removerepeats(string* s)
{
    string& str = *s; // Work with a reference to the original string
    string result;
    string prevLine;
    size_t pos = 0;

    // Use string::npos as the condition to run until the end of the string
    while (pos != string::npos)
    {
        size_t newPos = str.find('\n', pos);
        string currentLine = str.substr(pos, newPos - pos);

        // trim current line
        currentLine.erase(0, currentLine.find_first_not_of(" \t\n\r\f\v"));
        currentLine.erase(currentLine.find_last_not_of(" \t\n\r\f\v") + 1);

        // If current line is not the same as previous, append it to result
        if (currentLine != prevLine || pos == 0) // Also, always include the first line
        {
            if (!result.empty()) result += '\n'; // Append newline before adding the line, except for the first line
            result += currentLine;
        }

        prevLine = currentLine;

        if (newPos == string::npos) break; // If at the end of the string, exit the loop
        pos = newPos + 1; // Move past the current newline character
    }

    *s = result; // Assign the processed string back to the original pointer
}

void filternewline(string* s)
{
    string& ns = *s; // Use a reference to modify the original string
    bool prev = false;
    for (int i = 0; i < ns.size(); ++i)
    {
        if (ns[i] == '\n')
        {
            if (prev)
            {
                ns.erase(i, 1);
                i--; // Adjust the index after erasing a character
            }
            else
            {
                prev = true;
            }
        }
        else
        {
            prev = false;
        }
    }
}

string* gen(string s) 
{
    return new string(s);
}

string* label(string* s) 
{
    *s = *s + ":\n";
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
    if(b) return new string("true");
    return new string("false");
}

string* newTemp() {
    temprorary_3ac_counter++;
    string x = "$t" + to_string(temprorary_3ac_counter);
    string* ptr = new string(x);

    if(debug3ac) cout<<"[3AC]: made new temp : "<< (*ptr) << "\n";
    return ptr;
}

string* newFLabel() 
{
    
    string x = ".LFB" + to_string(flabel_3ac_counter);
    string* ptr = new string(x);
    flabel_3ac_counter++;

    if(debug3ac) cout<<"made new label : "<< (*ptr) << endl;
    
    return ptr;
}

string* newLabel() 
{
    
    string x = ".L" + to_string(label_3ac_counter);
    string* ptr = new string(x);
    label_3ac_counter++;

    if(debug3ac) cout<<"[3AC]: made new label : "<<*ptr << endl;
    
    return ptr;
}

string* newLabel(string x) 
{
    string* ptr = new string(x);

    if(debug3ac) cout<<"[3AC]: made new label : "<<*ptr << endl;
    
    return ptr;
}

std::string* merge(int count = 0, ...) {
    // cout << "here in merge\n";
    std::string* result = new std::string();
    va_list args;
    va_start(args, count); // Initialize the argument list with the count
    // cout << "here in merge\n";

    for (int i = 0; i < count; ++i) {
        // cout << "here in merge\n";
        std::string* nextString = va_arg(args, std::string*); // Get the next argument
        if (nextString) {
            *result += "\n" + *nextString;
        }
    }
    // cout << "here in merge\n";

    // remvoe leading and trailing newlines and spaces
    removetrailingnewlines(result);
    filternewline(result);

    va_end(args); // Clean up
    return result;
}

string genpass23ac(string s)
{
    // S0: add beginfunc and endfunc
    string* temp = newFLabel();
    s = "main:\n"+ *label(temp) + "š" + s + "\nreturn\n•\n\n";
    (*temp).pop_back();
    // cout << (*temp) << "\n";
    labelMap[(*temp)] = globalTable;

    string code = "";

    // S1 : pull functions up and down
    string func = "";
    string other = "";
    
    size_t pos = 0;
    while (pos < s.size()) 
    {
        size_t t = s.find("function™", pos);
        if (t == string::npos) break; 
        size_t u = s.find("endfunc", t);
        if (u == string::npos) break;
        other += s.substr(pos, t - pos);
        func += s.substr(t, u - t + 8) + "\n";
        pos = u + 8;
    }
    other += s.substr(pos);
    code = code + func + other;

    // S2: Convert multiline strings into single line strings
    code = std::regex_replace(code, std::regex("\"\"\""), "\x10");

    bool flag_tq=false;
    bool flag_sq=false;
    bool flag_dq=false;

    for(int i=0;i<code.size();i++)
    {
        if(code[i]=='\x10' && !flag_sq && !flag_dq)
        {
            if(flag_tq)
            {
                flag_tq = false;
            }
            else
            {
                flag_tq = true;
            }
        }if(code[i]=='\"' && !flag_sq && !flag_tq)
        {
            if(flag_dq)
            {
                flag_dq = false;
            }
            else
            {
                flag_dq = true;
            }
        }
        if(code[i]=='\'' && !flag_dq && !flag_tq)
        {
            if(flag_sq)
            {
                flag_sq = false;
            }
            else
            {
                flag_sq = true;
            }
        }

        if(flag_sq || flag_dq || flag_tq)
        {
            if(code[i] == '\n')
                code[i] = '\x11';
        }
    }
    code = std::regex_replace(code, std::regex("\x10"), "\"");
    code = std::regex_replace(code, std::regex("\x11"), "");

    // S3: Trim each line
    s=code; code = ""; string line = "";
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='\n')
        {
            line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
            line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
            code = code + line + "\n";
            line = "";
        }
        else
        {
            line = line + s[i];
        }
    }

    // S4: delete 3 lines of main and name
    std::regex pattern(R"(\n\s*\$t(\d+) = "__main__"\n\s*\$t(\d+) = __name__ == \$t\1\n\s*ifFalse \$t\2 goto \.L\d+)");
    std::string modified_code = std::regex_replace(code, pattern, "");

    // S5: add \t for each call, thing
    s=modified_code; code = ""; line="";
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='\n')
        {
            if(line.substr(0,4)=="call")
            {
                line = "\t" + line;
            }
            code = code + line + "\n";
            line = "";
        }
        else
        {
            line = line + s[i];
        }
    }

    // S6: add \t for all lines except that does not end in ":"
    s=code; code = ""; line="";
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='\n')
        {
            if(line[line.size()-1]==':')
            {
                code = code + line + "\n";
            }
            else
            {
                code = code + "\t" + line + "\n";
            }
            line = "";
        }
        else
        {
            line = line + s[i];
        }
    }

    // S0-revisited
    code = std::regex_replace(code, std::regex("š"), "beginfunc");
    code = std::regex_replace(code, std::regex("•"), "endfunc");
    code = std::regex_replace(code, std::regex("function™ "), "");
    // std::regex exitPattern("(^|\\n)([^\\n]*?exit(:|\\n)[^\\n]*)(\\n|$)");
    std::regex exitPattern(R"((.*?\bgoto\s+exit\b.*?\n))");
    code = std::regex_replace(code, exitPattern, "");

    // S9 remove : replace a line with goto .... : to goto ...
    s=code; code = ""; line = "";
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='\n')
        {
            if(line.find(" ") != string::npos && line[line.size()-1]==':')
                line = "\t" + line.substr(0,line.size()-1);
            code = code + line + "\n";
            line = "";
        }
        else
        {
            line = line + s[i];
        }
    }

    // S10 remove unclosed trailing brackers in each line
    s=code; code = "";
    int curr_open = 0;
    for(int i=0;i<s.size();i++) {
        if(s[i]=='\n') {
            if(i > 0 && curr_open < 0 && s[i-1]==')') code.pop_back();
            curr_open = 0;
        }
        else if(s[i]=='(') curr_open++;
        else {
            if(s[i]==')') curr_open--;
        }
        // if(s[i]=='\n') cout<<"NEWLINE";
        // else cout<<s[i];
        code.push_back(s[i]);
    }

    return code;

}

int make3AC(ASTNode* n)
{
    debug3ac = DEBUG_3AC_INSIDE_VERBOSE;
    after3ac = DEBUG_3AC_OUTSIDE_VERBOSE;
    // printcode = DEBUG_3AC_OUTSIDE_VERBOSE;
    int flag = generate3AC(root);

    removeemptygoto(root->code);
    filternewline(root->code);
    removerepeats(root->code);
    removeblankcolons(root->code);

    if(dopass2)
    {
        *root->code = genpass23ac(*(root->code));
    }

    return flag;
}

void printCode(ASTNode* n)
{
    if(after3ac) {
        cout << "[3AC]: " << "\n" << n->debug_type << " | " << n->content << " | " << endl;
        cout << "[3AC]: " << "CODE : " << *(n->code) << "\n";
        cout << "[3AC]: " << "VAL : " << *(n->val) << "\n";
        cout << "[3AC]: " << "CONTENT : " << n->content<< "\n";
        cout << "[3AC]: " << "=========================================================================================================\n";
    }
    return;
}

// To be called on root ASTNode of parse tree.
// This will construct the complete 3AC code after running the second pass through the parse tree.
// To be called on root ASTNode of parse tree
int generate3AC(ASTNode* n) {

    if(n == NULL) return 0;
    
    // COMMENT THIS LINE BEFORE STARING THE CODING PART
    // printf("Code for 3AC generation has started\n");
    // string x = "Comment this line";
    // (root->code) = gen(x);

    string name = (n->name);
    if(false) {}
    // Segment 1
    CHECK("start.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->next = newLabel("exit");
        labelMap[*(n->next)] = (n->table);
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1, 
            // gen("goto start\nstart:\n"),
            n->children[0]->code
            // gen("\nexit:\nexit")
            );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("file_input.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_file_input.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    
    CHECK("continued_file_input.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        (n->children)[1]->next = n->next;

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("continued_file_input.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout << "[3AC]: "<<"CODE for " << n->type << "\n" << *(n->code) << endl; }

    }

    CHECK("funcdef.1")
    {
        // DEF NAME parameters RIGHTARROW test COLON suite
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        n->children[6]->next = n->next;

        curr_func = n->children[1]->content; // better if we could replace curr_func with symbol table something -> dollar name
        if (func_args.find(curr_func) == func_args.end()) {
            if(debug3ac) cout << "[3AC]: "<< "Sindbad\n" <<endl;
            func_args[curr_func] = std::make_pair(std::vector<std::string>(), std::vector<std::string>());
        }
        else {
            func_args[curr_func].first = vector<string>(); 
            func_args[curr_func].second = vector<string>();
        }

        generate3AC(n->children[2]);
        generate3AC(n->children[4]);
        generate3AC(n->children[6]);
        
        string* lab = newLabel();

        // cout << ((n->children)[1]->content) << "\n";
        // if((n->children)[2] == NULL) cout << "Null here in 1\n";
        // if((n->children)[2]->T == NULL) cout << "Null here in 2\n";
        // cout << ((n->children)[2]->T->fields).size() << "\n";
        string mangled = mangle_name((n->children)[1]->content, (n->children)[2]->T->fields);
        string* func = newFLabel();
        labelMap[*(func)] = ((n->children)[6]->table);

        n->code = merge(9,
            gen("goto " + *lab),
            gen("\n\nfunction™ " + mangled + ":"),
            gen((*func) + ":"),
            gen("beginfunc"),
            n->children[2]->code,
            n->children[6]->code,
            gen("return"),
            gen("endfunc\n\n"),
            label(lab)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }

    CHECK("funcdef.2")
    {
        // DEF NAME parameters COLON suite
        // #cantwrite : right now supports only position-based arguments
        // #noteadded : test is the return type + parameters need handling of type
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        ((n->children)[4])->next = n->next;

        curr_func = n->children[1]->content; // better if we could replace curr_func with symbol table something -> dollar name
        if (func_args.find(curr_func) == func_args.end()) 
        {
            func_args[curr_func] = std::make_pair(std::vector<std::string>(), std::vector<std::string>());
        }
        else
        {
            func_args[curr_func].first = vector<string>(); 
            func_args[curr_func].second = vector<string>();
        }

        generate3AC(n->children[2]);
        generate3AC(n->children[4]);
        
        string* lab = newLabel();

        string mangled = mangle_name((n->children)[1]->content, (n->children)[2]->T->fields);
        string* func = newFLabel();
        labelMap[*(func)] = ((n->children)[4]->table);

        n->code = merge(9,
            gen("goto "+ *lab),
            gen("\n\nfunction™ " + mangled + ":"),
            gen((*func) + ":"),
            gen("beginfunc"),
            n->children[2]->code,
            n->children[4]->code,
            gen("return"),
            gen("endfunc\n\n"),
            label(lab)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("parameters.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[1]->next =n->next;

        generate3AC(n->children[1]);

        n->code = merge(1,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("parameters.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("typedargslist.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // #cantwrite : could not include the tougher case
        // lab = newLabel();
        // temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();
        
        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[3]);
        
        func_args[curr_func].second.push_back(*(n->children[0]->val));

        n->code = merge(8,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->children[0]->val) + " = popparam"),
            gen(*(temp2) +  " = " + *(n->children[0]->val) +  " == NULL"),
            gen("ifFalse " + *(temp2) + " goto " + *label(lab2)),
            gen(*(n->children[0]->val) + " = " + *(n->children[2]->val)),
            lab2,
            n->children[3]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("typedargslist.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // #cantwrite : could not include the tougher case
        // lab = newLabel();
        // temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();
        
        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[3]);
        
        func_args[curr_func].second.push_back(*(n->children[0]->val));

        n->code = merge(8,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->children[0]->val) + " = popparam"),
            gen(*(temp2) +  " = " + *(n->children[0]->val) +  " == NULL"),
            gen("ifFalse " + *(temp2) + " goto " + *label(lab2)),
            gen(*(n->children[0]->val) + " = " + *(n->children[2]->val)),
            lab2,
            n->children[3]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("typedargslist.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // #cantwrite : could not include the tougher case
        // lab= newLabel();
        // temp = newTemp();
        // temp2 = newTemp();
        // lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        func_args[curr_func].first.push_back(*(n->children[0]->val));

        n->code = merge(3,
            n->children[0]->code,
            gen(*(n->children[0]->val) + " = popparam"),
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("typedargslist.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // #cantwrite : could not include the tougher case
        // lab= newLabel();
        // temp = newTemp();
        // temp2 = newTemp();
        // lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        func_args[curr_func].first.push_back(*(n->children[0]->val));

        n->code = merge(3,
            n->children[0]->code,
            gen(*(n->children[0]->val) + " = popparam"),
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("next_arg.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // #cantwrite : could not include the tougher case
        // lab= newLabel();
        // temp = newTemp();
        temp2 = newTemp();
        lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[4]);

        n->code = merge(5,
            gen(*(n->children[2]->val) + "= popparam"),
            gen(*(temp2) +  " = " + *(n->children[2]->val) +  " != NULL"),
            gen("if " + *(temp2) + " goto " + *label(lab2)),
            gen(*n->children[2]->val + " = " + *(n->children[4]->val)),
            label(lab2)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("next_arg.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // lab= newLabel();
        // temp = newTemp();
        // temp2 = newTemp();
        // lab2 = newLabel();

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);
        generate3AC(n->children[3]);

        n->code = merge(1,
            gen(*(n->children[2]->val) + " = popparam")
        ); 
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("next_arg.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("tfpdef.1") 
    {
        // NAME COLON test
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string((n->children)[0]->content);
        
        // Code to call the function on children nodes
        generate3AC((n->children)[2]);
        
        n->code = n->children[0]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("tfpdef.2") 
    {
        // NAME
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string((n->children)[0]->content);
        n->code = n->children[0]->code;

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    
    CHECK("stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = n->children[0]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    
    CHECK("stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("simple_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("simple_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("next_small_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("next_small_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("small_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("small_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("small_stmt.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            (n->children)[0]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("small_stmt.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("small_stmt.5")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("expr_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[1]->next = n->next;

        generate3AC(n->children[0]);
 
        generate3AC(n->children[1]);

        filternewline(n->children[1]->val);
        removerepeats(n->children[1]->val);

        if(debug3ac) cout << "[3AC]: "<<"2 Getting out of "<<n->name<<" (" << n->type << ")\n";

        n->code = merge(3,
            n->children[0]->code,
            n->children[1]->code,
            gen(*(n->children[0]->val) + " = " + *(n->children[1]->val) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("expr_stmt.2")
    {
        // testlist_star_expr += testlist
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);
        

        size_t pos = (n->children[1]->content).find('=');
        string* op = new string((n->children[1]->content).substr(0, pos));
        
        // if(debug3ac) cout<<"[3AC]: 1 Outside remove lines command\n";
        generate3AC((n->children)[2]);
        // if(debug3ac) cout<<"[3AC]: 2 Outside remove lines command\n";
        string* x = newTemp();
        // if(debug3ac) cout<<"[3AC]: 3 Outside remove lines command\n";
        string* y = newTemp();
        // if(debug3ac) cout<<"[3AC]: 4 Outside remove lines command\n";
        removenewlines(n->children[0]->val);
        removenewlines(n->children[2]->val);
        // if(debug3ac) cout<<"[3AC]: 5 Outside remove lines command\n";
        // cout << (*((n->children)[]->code)) << "\n";
        n->code = merge(4,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(x) + " = " + *((n->children)[0]->val) + " " + (*op) + " " + *((n->children)[2]->val)+ "\n"),
            gen (*((n->children)[0]->val) + " = " + *(x) + "\n")
        );
        if(debug3ac) cout<<"[3AC]: 6 Outside remove lines command\n";
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("expr_stmt.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        n->children[1]->val = n->children[0]->val;

        generate3AC((n->children)[1]);

        removenewlines(n->children[1]->val);

        if(n->children[1]->children.size() == 0)
        {
            n->code = merge(2,
                n->children[0]->code,
                n->children[1]->code
            );
        }
        else
        {
            n->code = merge(3,
                n->children[0]->code,
                n->children[1]->code,
                gen(*(n->children[0]->val) + " = " + *(n->children[1]->val) + "\n")
            );
        }
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }


    CHECK("continued_expr_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[2]->next = n->next;

        n->children[0]->val = n->val;
        generate3AC((n->children)[0]);
        n->children[2]->val = n->children[0]->val;
        generate3AC((n->children)[2]);

        removenewlines(n->children[2]->val);

        n->code = merge(4,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->children[0]->val) + " = " + *((n->children)[2]->val) + "\n"),
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("continued_expr_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("annassign.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[3]->next = n->next;
        generate3AC(n->children[1]);
        generate3AC(n->children[3]);

        n->val = n->children[3]->val;

        n->code = merge(2,
            n->children[1]->code,
            n->children[3]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("annassign.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[1]);

        n->code = merge(2,
            n->children[1]->code,
            gen("goto " + *((n->children)[1]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("testlist_star_expr.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->val = merge(2,
            n->children[0]->val,
            n->children[1]->val
        );

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    
    CHECK("testlist_star_expr.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        n->val = merge(2,
            n->children[0]->val,
            n->children[1]->val
        );

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    
    CHECK("testlist_star_expr.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    
    CHECK("testlist_star_expr.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }

    CHECK("flow_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);

        n->code = (n->children)[0]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("flow_stmt.2")
    {
    
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);

        n->code = (n->children)[0]->code;

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << "(" << n->type << " | " << n->name << ")\n" << *(n->code) << "\n";
        if(printcode) { cout << "[3AC]: "<<"CODE for " << n->type << "\n" << *(n->code) << endl; }
    }
    
    CHECK("flow_stmt.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);

        n->code = n->children[0]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("flow_stmt.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }

    CHECK("break_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        n->code = gen("break\n");

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("continue_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        n->code = gen("continue\n");

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("return_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[1]);

        removenewlines(n->children[1]->val);

        n->code = merge(3,
            n->children[1]->code,
            gen("paramret "+ *(n->children[1]->val)),
            gen("return ")
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }

    CHECK("return_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge(1,
            gen("return")
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }
    
    CHECK("raise_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("raise_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("raise_stmt.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }


    CHECK("global_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[2]->next = n->next;

        generate3AC((n->children)[2]);

        n->code = merge(3,
            gen("global : " + n->children[1]->content),
            n->children[2]->code,
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("nonlocal_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("assert_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("assert_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }

    CHECK("stmt_helper.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen(", " + n->children[1]->content)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("stmt_helper.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("compound_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("compound_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("compound_stmt.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        if(debug3ac) cout << "[3AC]: "<<"Joseph Stalin" <<endl;
        generate3AC(n->children[0]);
        if(debug3ac) cout << "[3AC]: "<<"Stalin 2" <<endl;


        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("compound_stmt.4")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("compound_stmt.5")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("compound_stmt.6")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("if_stmt.1")
    {
        // IF test COLON suite elif_stmt else_stmt
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->tr = newLabel();
        (n->children)[1]->fl = newLabel();
        (n->children)[3]->next = n->next;
        (n->children)[4]->tr = n->next;
        (n->children)[4]->fl = newLabel();
        (n->children)[5]->next = n->next;

        labelMap[*((n->children)[1]->tr)] = (n->children)[3]->table;
        labelMap[*((n->children)[1]->fl)] = (n->children)[4]->table;
        labelMap[*((n->children)[4]->fl)] = (n->children)[5]->table;

        generate3AC((n->children)[1]);
        generate3AC((n->children)[3]);
        generate3AC((n->children)[4]);
        generate3AC((n->children)[5]);

        n->code = merge(10,
            n->children[1]->code,
            gen("ifFalse " + *(n->children[1]->val) + " goto " + *(n->children[1]->fl) + "\n"),
            label((n->children)[1]->tr),
            n->children[3]->code,
            gen("goto " + *((n->children)[3]->next) + "\n"),
            label((n->children)[1]->fl),
            n->children[4]->code,
            label((n->children)[4]->fl),
            gen(*(n->children[5]->code)),
            gen("goto " + *((n->children)[5]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("elif_stmt.1")
    {
        // elif_stmt ELIF test COLON suite
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->tr = n->next;
        (n->children)[0]->fl = newLabel();
        (n->children)[2]->tr = newLabel();
        (n->children)[2]->fl = n->next;
        (n->children)[4]->next = n->next;

        labelMap[*((n->children)[0]->fl)] = (n->children)[2]->table;
        labelMap[*((n->children)[2]->tr)] = (n->children)[4]->table;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[2]);
        generate3AC((n->children)[4]);

        n->code = merge(6,
            n->children[0]->code,
            label((n->children)[0]->fl),
            n->children[2]->code,
            label((n->children)[2]->tr),
            n->children[4]->code,
            gen("goto " + *((n->children)[4]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("elif_stmt.2")
    {
        // %empty
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("else_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[2]->next = n->next;

        generate3AC((n->children)[2]);

        n->code = merge(2,
            n->children[2]->code,
            gen("goto " + *((n->children)[2]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("else_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge(1,
            gen("goto " + *(n->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("while_stmt.1")
    {
        // WHILE test COLON suite else_stmt
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        string* begin = newLabel();
        n->children[1]->tr = newLabel();
        n->children[1]->fl = newLabel();
        n->children[3]->next = begin;
        n->children[4]->next = n->next;

        labelMap[*(begin)] = (n->table);
        labelMap[*((n->children)[1]->tr)] = (n->children)[3]->table;
        labelMap[*((n->children)[1]->fl)] = (n->children)[4]->table;

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
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("for_stmt.1")
    {
        // FOR exprlist IN testlist COLON suite else_stmt
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        string* begin = newLabel();
        n->tr = begin;
        n->fl = newLabel();

        labelMap[*(n->tr)] = (n->children)[5]->table;
        labelMap[*(n->fl)] = (n->children)[6]->table;
        
        n->children[5]->next = n->tr;
        n->children[6]->next = n->next;

        generate3AC(n->children[1]);
        generate3AC(n->children[3]);
        generate3AC(n->children[5]);
        generate3AC(n->children[6]); 
        
        string* tt = ((n->children)[1]->addr);
        string* tt2 = newTemp();
        string* tt3 = newTemp();

        string* a, *b, *c;
        string input = *(n->children[3]->val);
        size_t start = input.find("(");
        size_t end = input.find(")");
        size_t c1 = input.find(",");
        size_t c2 = input.find(",", c1+1);

        a = new string(input.substr(start+1, c1- start-1));
        b = new string(input.substr(c1+1, c2-c1-1));
        c = new string(input.substr(c2+1,end-c2-1));

        removenewlines(a);
        removenewlines(b);
        removenewlines(c);

        n->code = merge(14,
            n->children[1]->code,
            n->children[3]->code,
            gen(*(tt) + " = "+ *(a)),
            gen("goto " + (*begin)),
            label(begin),
            gen(*(tt3) + " = " + *(tt) + " < "+ *(b)),
            gen("ifFalse " + *(tt3) + " goto " + *(n->fl)),
            n->children[5]->code,
            gen(*(tt2) +" = "+ *(tt) + " + "+ *(c)),
            gen(*(tt) + " = " + *(tt2)),
            gen("goto " + *(n->tr)),
            label(n->fl),
            n->children[6]->code,
            gen("goto " + *(n->children[6]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("try_stmt.1")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("try_stmt.2")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }

    CHECK("except_stmt.1")
    {
        // #notrequired : try statement was not needed
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("except_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }

    CHECK("finally_stmt.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("finally_stmt.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }

    CHECK("except_clause.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("except_clause.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("except_clause.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }

    CHECK("suite.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *((n->children)[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("suite.2")
    {
        // #cantwrite : take care of INDENT and DEDENT as per scope rules
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[2]->next = n->next;

        generate3AC((n->children)[2]);

        n->code = merge(1,
            n->children[2]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("stmts.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[1]->next = n->next;

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);

        if(debug3ac) cout << "[3AC]: "<<"ConCalma"<<endl;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("stmts.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->next = n->next;

        generate3AC((n->children)[0]);

        n->code = merge(1,
            n->children[0]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("test.1")
    { 
        // or_test IF or_test ELSE test
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[2]->tr = newLabel();
        n->children[2]->fl = newLabel();
        n->children[0]->tr = n->tr;
        n->children[0]->fl = n->fl;
        n->children[0]->next = n->next;
        n->children[4]->tr = n->tr;
        n->children[4]->fl = n->fl;
        n->children[4]->next = n->next;
        n->val = newTemp();

        labelMap[*(n->children[2]->tr)] = (n->children)[0]->table;
        labelMap[*(n->children[2]->fl)] = (n->children)[4]->table;

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
            gen("if " + *(n->children[2]->val) + " goto " + *(n->children[2]->tr) + "\n"),
            gen("ifFalse" + *(n->children[2]->val) + " goto " + *(n->children[2]->fl) + "\n"),
            label(n->children[0]->tr),
            n->children[0]->code,
            gen(*(n->val) + " = " + *(n->children[0]->val) + "\n"),
            gen("goto " + *(n->children[0]->next) + "\n"),
            label(n->children[4]->fl),
            n->children[4]->code,
            gen(*(n->val) + " = " + *(n->children[4]->val) + "\n"),
            gen("goto " + *(n->children[4]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("test.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->call = n->call;

        // n->children[0]->tr = newLabel();
        // n->children[0]->fl = newLabel();
        n->children[0]->next = n->next;

        generate3AC(n->children[0]);

        n->val = n->children[0]->val;

        n->code = merge(1,
            n->children[0]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("test_nocond")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->tr = n->tr;
        n->children[0]->fl = n->fl;
        n->children[0]->next = n->next;

        generate3AC(n->children[0]);

        n->code = merge(2,
            n->children[0]->code,
            gen("goto " + *(n->children[0]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("or_test.1") 
    {
        // and_test continued_or_test
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->call = n->call;
        n->children[1]->call = n->call;

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_or_test.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->val = n->val;
        generate3AC(n->children[0]);
        n->val = newTemp();
        generate3AC(n->children[2]);

        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) + " = " + *(n->children[0]->val) + " or " + *(n->children[2]->val) + "\n")
        );

        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("continued_or_test.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("and_test.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val;

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_and_test.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->val = n->val;
        generate3AC(n->children[0]);
        n->val = newTemp();
        generate3AC(n->children[2]);

        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) + " = " + *(n->children[0]->val) + " and " + *(n->children[2]->val) + "\n")
        );


        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("continued_and_test.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("not_test.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        if(debug3ac) cout << "[3AC]: "<<"Sailor 2.0"<<endl;
        generate3AC((n->children)[1]);

        string sh = *(n->children[1]->val);
        sh.erase(0, sh.find_first_not_of(" \t\n\r\f\v"));
        sh.erase(sh.find_last_not_of(" \t\n\r\f\v") + 1);

        (n->val) = newTemp();
        n->code =  merge(2,
            n->children[1]->code,
            gen(*(n->val) + " = " + " !" + sh + "\n")
        );
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    
    }
    CHECK("not_test.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);

        if(debug3ac) cout << "[3AC]: "<<"Out of  not_test.2"<<endl;

        n->code = n->children[0]->code;
        n->val = n->children[0]->val;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("comparison.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("comparison_stmt.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        n->val = newTemp();

        filternewline(n->children[0]->val);
        filternewline(n->children[1]->val);
        filternewline(n->children[2]->val);
        removetrailingnewlines(n->children[0]->val);
        removetrailingnewlines(n->children[1]->val);
        removetrailingnewlines(n->children[2]->val);
        removerepeats(n->children[0]->val);
        removerepeats(n->children[1]->val);
        removerepeats(n->children[2]->val);

        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " " + *(n->children[1]->val) + " " + *(n->children[2]->val) + "\n")
        ); 

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("comparison_stmt.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("comp_op.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("comp_op.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("comp_op.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }

    CHECK("comp_op.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }

    CHECK("comp_op.5") {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }

    CHECK("star_expr.1") {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }

    CHECK("expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_xor_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

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
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("continued_xor_expr.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("xor_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("continued_and_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " and " + *(n->children[2]->val) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_and_expr.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("and_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("continued_shift_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[2]);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " & " + *(n->children[2]->val) + "\n")
        );  
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_shift_expr.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge(); 
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }    

    CHECK("shift_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_arith_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        removenewlines(n->children[0]->val);
        removenewlines(n->children[2]->val);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " << " + *(n->children[2]->val) + "\n")
        ); 
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_arith_expr.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        removenewlines(n->children[0]->val);
        removenewlines(n->children[2]->val);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " >> " + *(n->children[2]->val) + "\n")
        ); 
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_arith_expr.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();  

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}    
    }

    CHECK("arith_expr.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]);
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    } 

    CHECK("continued_term.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        removenewlines(n->children[0]->val);
        removenewlines(n->children[2]->val);

        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " + " + *(n->children[2]->val) + "\n")
        );  
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
     
    } 

    CHECK("continued_term.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        removenewlines(n->children[0]->val);
        removenewlines(n->children[2]->val);
        
        (n->val) = newTemp();
        n->code = merge(3,
            n->children[0]->code,
            n->children[2]->code,
            gen(*(n->val) +  " = " + *(n->children[0]->val) + " - " + *(n->children[2]->val) + "\n")
        ); 
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
      
    }

    CHECK("continued_term.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();  
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    
    }

    CHECK("term.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC((n->children)[0]); 
        (n->children)[1]->val = (n->children)[0]->val; 

        generate3AC((n->children)[1]);
        n->val = (n->children)[1]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_factor.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        (n->children)[0]->val = (n->val);

        generate3AC((n->children)[0]);
        generate3AC((n->children)[1]);
        generate3AC((n->children)[2]);

        if((*(n->children[2]->val)).find("(") != string::npos)
        {
            n->children[2]->val = newTemp();
            (n->val) = newTemp();

            removenewlines(n->children[0]->val);

            n->code = merge(4,
                n->children[0]->code,
                n->children[2]->code,
                gen(*(n->children[2]->val) +  " = popparam\n"),
                gen(*(n->val) +  " = " + *(n->children[0]->val) + " * " + *(n->children[2]->val) + "\n")
            );
        }
        else
        {
            removenewlines(n->children[0]->val);

            (n->val) = newTemp();
            n->code = merge(3,
                n->children[0]->code,
                n->children[2]->code,
                gen(*(n->val) +  " = " + *(n->children[0]->val) + " * " + *(n->children[2]->val) + "\n")
            );
        }

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    } 

    CHECK("continued_factor.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

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
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_factor.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

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
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_factor.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

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
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("continued_factor.5") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

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
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
      
    }

    CHECK("continued_factor.6") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge(); 
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("factor.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[1]);

        n->val = newTemp();
        string sh = *(n->children[1]->val);
        sh.erase(0, sh.find_first_not_of(" \t\n\r\f\v"));
        sh.erase(sh.find_last_not_of(" \t\n\r\f\v") + 1);
        string sh2 = n->children[0]->content;
        sh2.erase(0, sh2.find_first_not_of(" \t\n\r\f\v"));
        sh2.erase(sh2.find_last_not_of(" \t\n\r\f\v") + 1);

        n->code = merge(2,
            n->children[1]->code,
            gen(*(n->val) + " = " + sh2 + sh)
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    
    CHECK("factor.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[1]);
        removenewlines(n->children[1]->val);

        n->val = newTemp();
        string sh = *(n->children[1]->val);
        sh.erase(0, sh.find_first_not_of(" \t\n\r\f\v"));
        sh.erase(sh.find_last_not_of(" \t\n\r\f\v") + 1);
        string sh2 = n->children[0]->content;
        sh2.erase(0, sh2.find_first_not_of(" \t\n\r\f\v"));
        sh2.erase(sh2.find_last_not_of(" \t\n\r\f\v") + 1);

        n->code = merge(2,
            n->children[1]->code,
            gen(*(n->val) + " = " + sh2 + sh)
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("factor.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";


        generate3AC(n->children[1]);
        
        n->val = newTemp();
        string sh = *(n->children[1]->val);
        sh.erase(0, sh.find_first_not_of(" \t\n\r\f\v"));
        sh.erase(sh.find_last_not_of(" \t\n\r\f\v") + 1);
        string sh2 = n->children[0]->content;
        sh2.erase(0, sh2.find_first_not_of(" \t\n\r\f\v"));
        sh2.erase(sh2.find_last_not_of(" \t\n\r\f\v") + 1);

        n->code = merge(2,
            n->children[1]->code,
            gen(*(n->val) + " = " + sh2 + sh)
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("factor.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";


        generate3AC(n->children[0]);

        n->val = n->children[0]->val;

        n->code = merge(1,
            n->children[0]->code
        );
        

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("power.1")
    {

        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->next = n->next;
        n->val = newTemp();

        generate3AC(n->children[0]);
        
        generate3AC(n->children[2]);

        if(debug3ac) cout << "[3AC]: "<<"Out of  power.1"<<endl;

        if((*(n->children[0]->val)).find("(args)") != string::npos)
        {
            n->children[0]->val = newTemp();

            n->code = merge(1,
                gen(*(n->children[0]->val) +  " = popparam\n")
            );
        }

        n->code = merge(5,
            n->children[0]->code,
            n->code,
            n->children[2]->code,
            gen(*(n->val) + " = " + *(n->children[0]->val) + " ** " + *(n->children[2]->val) + "\n"),
            gen("goto " + *(n->children[2]->next) + "\n")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("power.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";


        n->children[0]->next = n->next;
        generate3AC(n->children[0]);

        if(debug3ac) cout << "[3AC]: "<<"Out of  power.1"<<"(" << n->type << ")\n";

        if((*(n->children[0]->val)).find("(args)") != string::npos)
        {
            n->children[0]->val = newTemp();

            n->code = merge(1,
                gen(*(n->children[0]->val) +  " = popparam\n")
            );
        }

        n->val = n->children[0]->val;

        n->code = merge(2,
            n->children[0]->code,
            n->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("atom_expr.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";


        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("atom_expr.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[1]->next = n->next;
        generate3AC(n->children[0]);
        n->children[1]->call = n->children[0]->call;
        generate3AC(n->children[1]);

        n->val = merge(2,
            n->children[0]->val,
            n->children[1]->val
        );

        // changing len(arr)
        // trim t by removing leading and trailing new lines and spaces
        removenewlines(n->val);
        string t = *n->val;
        t.erase(0, t.find_first_not_of(" \t\n\r\f\v"));
        t.erase(t.find_last_not_of(" \t\n\r\f\v") + 1);
        if(t.substr(0,4)=="len(" && t[t.length()-1]==')')
        {
            n->val = new string(t.substr(4,t.length()-5) + "[-1]");
        }

        

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("trailers.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[0]->call = n->call;
        n->children[1]->call = n->call;

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = merge(2, n->children[0]->val, n->children[1]->val);
        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("trailers.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = merge();

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("atom.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[1]);
        n->val = n->children[1]->val;

        n->code = n->children[1]->code;

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = merge();

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[1]);


        removenewlines(n->children[1]->val);
        string t = *(n->children[1]->val);
        t.erase(0, t.find_first_not_of(" \t\n\r\f\v"));
        t.erase(t.find_last_not_of(" \t\n\r\f\v") + 1);
        if(t[t.size()-1] == ',')
        {
            t = t.substr(0,t.size()-1);
        }

        int commaCount = std::count(t.begin(), t.end(), ',');

        n->val = new string(" [ "+ to_string(commaCount+1)+" , "+t+" ] "); // rather manupulate this
        
        n->code = merge(1,
            n->children[1]->code
        );
        

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string(" [ 0 ] ");

        removenewlines(n->val);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.5") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("atom.6") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("atom.7") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->call = new string(n->children[0]->content);
        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.8")  
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.9") 
    {

        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);

        n->val = newTemp();
        n->code = merge(1,
            gen(*(n->val) + " = " + *(n->children[0]->val))
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.10") 
    {

        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("atom.11") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("atom.12") 
    {

        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("atom.13") 
    {

        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string(n->children[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("strings.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = merge(2,
            n->children[0]->val,
            new string(n->children[1]->content)
        );

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("strings.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string((n->children)[0]->content);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }


    CHECK("testlist_comp.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("testlist_comp.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + " " + *(n->children[1]->val)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("testlist_comp.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";


        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + " " + *(n->children[1]->val));

        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("testlist_comp.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("testlist_comp.5") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("testlist_comp.6") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("continued_testlist.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + " , " + *(n->children[2]->val));
        
        n->code = merge(2,
            n->children[0]->code,
            n->children[2]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("continued_testlist.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("continued_testlist.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("trailer.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->children[1]->call = n->call;

        // stackArgScope.push({k2n,n2c});
        // k2n = std::unordered_map<std::string, int>();
        // for (auto& pair : n2c) {
        //     delete pair.second;  // Clean up dynamic memory to prevent memory leaks
        // }
        // n2c = std::unordered_map<int, std::string*>();

        generate3AC(n->children[1]);
        n->code = n->children[1]->code;
        n->val = n->children[1]->val;

        // k2n = stackArgScope.top().first;
        // n2c = stackArgScope.top().second;
        // stackArgScope.pop();

        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("trailer.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string("");
        
        string callfunc = *(n->call);
        if(callfunc != "print" && callfunc != "range" && callfunc != "len") {
            // This is not a special function
            callfunc = mangle_name(callfunc, deque<TypeExpression*>());
        }

        n->code=merge(3,
            gen("stackpointer +xxx"),
            gen("\tcall " + callfunc + ","+ to_string(0)),
            gen("stackpointer -yyy")
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("trailer.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[1]);

        n->val = new string("[" + *(n->children[1]->val) + "]");
        n->code = n->children[1]->code;

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}    
    }
    CHECK("trailer.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string("." + (n->children[1]->content));
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("subscriptlist.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val) + ",");
        
        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }
    CHECK("subscriptlist.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        if(*(n->children[1]->val) == "NULL")
            *(n->children[1]->val) = "";

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));

        removenewlines(n->val);
        
        n->code = merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }
    CHECK("continued_subscript.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + "," + *(n->children[2]->val) );
        
        n->code = merge(2,
            n->children[0]->code,
            n->children[2]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }
    CHECK("continued_subscript.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }

    CHECK("subscript.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);

        n->val = new string(*(n->children[0]->val));
        
        n->code = merge(1,
            n->children[0]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }
    CHECK("subscript.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("subscript.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("subscript.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("subscript.5")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("subscript.6")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("subscript.7")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("subscript.8")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("subscript.9")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }

    CHECK("sliceop.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("sliceop.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }


    CHECK("exprlist.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val)
        );
        n->addr = (n->children[0]->val);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("exprlist.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val)
        );
        n->addr = (n->children[0]->val);
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("exprlist.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("exprlist.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("continued_exprlist.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + ", " + *(n->children[2]->val)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("continued_exprlist.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;


    }
    CHECK("continued_exprlist.3") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("testlist.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val)
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("testlist.2") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = new string(
            *(n->children[0]->val) + *(n->children[1]->val));
        
        n->code=merge(2,
            n->children[0]->code,
            n->children[1]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("continued_comma_test.1") 
    {
        // continued_comma_test COMMA test
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->val = new string(
            *(n->children[0]->val) + ", " + *(n->children[2]->val));
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("continued_comma_test.2") 
    {
        // %empty
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->val = new string();
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("dictorsetmaker.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.4") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("dictorsetmaker.5")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.6")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.7") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.8")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("dictorsetmaker.9")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("dictorsetmaker.10") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.11")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("dictorsetmaker.12")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("continued_dictorset.1") 
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("continued_dictorset.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("continued_dictorset.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
        
    }
    
    CHECK("classdef.1") {
        // CLASS NAME OPENING_BRACKET arglist CLOSING_BRACKET COLON suite
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        // comment it below
        if(debug3ac) cout << "[3AC]: "<<"Add code to "<<n->name<<" (" << n->type << ")\n";
        n->children[6]->next = n->next;

        // Set the class_names stack to include the presence of a function scope here
        class_names.push((n->children)[1]->content);
        isclassargs = true;
        generate3AC(n->children[3]);
        isclassargs = false;

        generate3AC(n->children[6]);

        // Pop the presence of a class_names stack here
        class_names.pop();

        n->code = (n->children)[6]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }

    CHECK("classdef.2") {
        // CLASS NAME OPENING_BRACKET CLOSING_BRACKET COLON suite
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        n->children[5]->next = n->next;

        // Set the class_names stack to include the presence of a function scope here
        class_names.push((n->children)[1]->content);

        generate3AC(n->children[5]);

        // Pop the presence of a class_names stack here
        class_names.pop();

        n->code = (n->children)[5]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("classdef.3") 
    {
        // CLASS NAME COLON suite
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        n->children[3]->next = n->next;

        // Set the class_names stack to include the presence of a function scope here
        class_names.push((n->children)[1]->content);

        generate3AC(n->children[3]);

        // Pop the presence of a class_names stack here
        class_names.pop();

        n->code = (n->children)[3]->code;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) { printCode(n); }
    }

    // ----------------- End of addcode ---------------

    CHECK("arglist.1")
    {
        // argument continued_argument COMMA
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        x=0;
        n2c.clear();
        k2n.clear();

        n->children[0]->call = n->call;
        n->children[1]->call = n->call;
        generate3AC(n->children[0]);
        generate3AC(n->children[1]);

        n->val = merge(2,
            n->children[0]->val,
            n->children[1]->val
        );

        // #cantwrite -> get to the function call and add flag for class and functions
        string callfunc= *(n->call);// curr_func; // change this to value that comes from atom

        if(debug3ac) cout << "No Problem"<<endl;

        if(func_args.find(callfunc) == func_args.end())
        {
            if(debug3ac) cout << "No Problem 2.0 "<<endl;
            // Special functions
            if(callfunc=="print")
            {
                n->val = new string("(");

                n->code = merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );

                for(int i=0;i<n2c.size();i++)
                {
                    filternewline(n2c[i]);
                    removerepeats(n2c[i]);
                    
                    n->code=merge(5,
                        n->code,
                        gen("param " + *(n2c[i])),
                        gen("stackpointer +xxx"),
                        gen("\tcall " + callfunc + ","+ to_string(1)),
                        gen("stackpointer -yyy")
                    );
                    
                    n->val = new string(*n->val + "," + *n2c[i]);
                }

                string* temp = newTemp();
                n->code=merge(6,
                    n->code,
                    gen((*temp) + " = " + "\"\\n\""),
                    gen("param " + (*temp)),
                    gen("stackpointer +xxx"),
                    gen("\tcall " + callfunc + ","+ to_string(1)),
                    gen("stackpointer -yyy")
                );

                n->val = new string(")");
            }
            else if(callfunc=="range")
            {
                if(n2c.size()>3 || n2c.size()<=0)
                {
                    if(debug3ac) cout << "[3AC]: "<<"Error in arglist.1 : range has wrong number of arguments"<<endl;
                }
                else if(n2c.size()==1)
                {
                    n->val = new string("(0," + *(n2c[0]) + ",1)");
                }
                else if(n2c.size()==2)
                {
                    n->val = new string("(" + *(n2c[0]) + "," + *(n2c[1]) + ",1)");
                }
                else
                {
                    n->val = new string("(" + *(n2c[0]) + "," + *(n2c[1]) + "," + *(n2c[2])+")");
                
                }

                n->code=merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );
            }
            else if(callfunc=="len")
            {
                if(n2c.size()!=1)
                {
                    if(debug3ac) cout << "[3AC]: "<<"Error in arglist.1 : len has wrong number of arguments"<<endl;
                }
                else
                {
                    if(debug3ac) cout<<"Hi World 343"<<endl;
                    n->val = new string("(" + *(n2c[0]) + ")");
                }

                n->code=merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );
            }
            else if(isclassargs && callfunc=="")
            {
                n->val = new string("(" + *(n2c[0]) + ")");

                n->code=merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );
            }
            // Non special functions
            else
            {
                cout << "[3AC]: "<<"Error : Function not found - "<<callfunc<<endl;
                exit(0);
            }
        }
        else
        {
            string mcallfunc = mangle_name(callfunc, (n->T->fields));

            if(debug3ac) cout << "No Problem 3.0 "<<endl;
            n->val = new string("(args)");

            n->code = merge(2,
                n->children[0]->code,
                n->children[1]->code
            );
            
            int i;
            for(i=0;i<func_args[callfunc].first.size();i++) // compulsory parameters
            {
                string* tt = newTemp();

                removenewlines(n2c[i]);

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
                    
                    removenewlines(n2c[v]);

                    n->code = merge(3,
                        n->code,
                        gen(*(tt) + " = " + *(n2c[v])),
                        gen("param " + *(tt))
                    );
                }
                else
                {
                    n->code = merge(2,
                        n->code,
                        gen("param NULL")
                    );
                }
            }

            n->code = merge(4,
                n->code,
                gen("stackpointer +xxx"),
                gen("\tcall " + mcallfunc + "," + to_string(func_args[callfunc].first.size() + func_args[callfunc].second.size())),
                gen("stackpointer -yyy")
            );
        }

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }

    CHECK("arglist.2")
    {
        // argument continued_argument
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        x=0;
        n2c.clear();
        k2n.clear();

        n->children[0]->call = n->call;
        n->children[1]->call = n->call;
        generate3AC(n->children[0]);
        if(debug3ac) cout << "[3AC]: "<< n->children[0]->name << endl;
        if(debug3ac) cout << "[3AC]: "<<"Done with child1"<<endl;
        generate3AC(n->children[1]);

        n->val = merge(2,
            n->children[0]->val,
            n->children[1]->val
        );

        // #cantwrite -> get to the function call and add flag for class and functions
        string callfunc= *(n->call);// curr_func; // change this to value that comes from atom

        if(func_args.find(callfunc) == func_args.end())
        {
            if(debug3ac) cout << "No Problem 1.0"<<endl;

            // Special functions
            if(callfunc=="print")
            {
                if(debug3ac) cout << "No Problem 7.0"<<endl;
                n->val = new string("(");

                n->code = merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );

                for(int i=0;i<n2c.size();i++)
                {
                    filternewline(n2c[i]);
                    removerepeats(n2c[i]);
                    
                    n->code=merge(5,
                        n->code,
                        gen("param " + *(n2c[i])),
                        gen("stackpointer +xxx"),
                        gen("\tcall " + callfunc + ","+ to_string(1)),
                        gen("stackpointer -yyy")
                    );

                    n->val = new string(*n->val + "," + *n2c[i]);
                }

                string* temp = newTemp();
                n->code=merge(6,
                    n->code,
                    gen((*temp) + " = " + "\"\\n\""),
                    gen("param " + (*temp)),
                    gen("stackpointer +xxx"),
                    gen("\tcall " + callfunc + ","+ to_string(1)),
                    gen("stackpointer -yyy")
                );
                
                n->val = new string(*n->val + ")");

            }
            else if(callfunc=="range")
            {
                if(debug3ac) cout << "No Problem 6.0"<<endl;
                if(n2c.size()>3 || n2c.size()<=0)
                {
                    if(debug3ac) cout << "No Problem 8.8"<<endl;

                    if(debug3ac) cout << "[3AC]: "<<"Error in arglist.2 : wrong number of arguments in range()"<<endl;
                    //cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

                    if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
                    if(printcode) {printCode(n);}

                    return -1;
                    
                }
                else if(n2c.size()==1)
                {
                    if(debug3ac) cout << "No Problem 9.9"<<endl;

                    n->val = new string("(0," + (*(n2c[0])) + ",1)");
                }
                else if(n2c.size()==2)
                {
                    if(debug3ac) cout << "No Problem 10.10"<<endl;

                    n->val = new string("(" + *(n2c[0]) + "," + *(n2c[1]) + ",1)");
                }
                else
                {
                    if(debug3ac) cout << "No Problem 11.11"<<endl;

                    n->val = new string("(" + *(n2c[0]) + "," + *(n2c[1]) + "," + *(n2c[2])+")");
                
                }
                
                if(debug3ac) cout << "No Problem N.N"<<endl;

                n->code=merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );
            }
            else if(callfunc=="len")
            {
                if(debug3ac) cout << "No Problem 5.0"<<endl;
                if(debug3ac) cout << "No Problem 3.0"<<endl;
                if(n2c.size()!=1)
                {
                    if(debug3ac) cout << "[3AC]: "<<"Error in arglist.1 : len has wrong number of arguments"<<endl;
                }
                else
                {
                    if(debug3ac) cout<<"Hi World 343"<<endl;
                    n->val = new string("(" + *(n2c[0]) + ")");
                }

                n->code=merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );
            }
            else if(isclassargs && callfunc=="")
            {
                if(debug3ac) cout << "No Problem 4.0"<<endl;

                n->val = new string("(" + *(n2c[0]) + ")");

                n->code=merge(2,
                    n->children[0]->code,
                    n->children[1]->code
                );
            }
            // Non special functions
            else
            {
                cout << "[3AC]: "<<"Error : Function not found - "<<callfunc<<endl;
                exit(0);
            }
        }
        else
        {
            string mcallfunc = mangle_name(callfunc, (n->T->fields));

            if(debug3ac) cout << "No Problem 2.0"<<endl;

            n->val = new string("(args)");

            n->code = merge(2,
                n->children[0]->code,
                n->children[1]->code
            );
            if(debug3ac)
            {

                cout<<"============================================================================================================================^\n";
                // print func_args map
                cout<<"Function Arguments Map\n";
                for(auto it=func_args.begin();it!=func_args.end();it++)
                {
                    cout<<it->first<<" : ";
                    for(int i=0;i<it->second.first.size();i++)
                    {
                        cout<<it->second.first[i]<<" ";
                    }
                    cout<<" : ";
                    for(int i=0;i<it->second.second.size();i++)
                    {
                        cout<<it->second.second[i]<<" ";
                    }
                    cout<<endl;
                }

                // print callfunc
                cout<<"Call Function : "<<callfunc<<endl;
                cout<<"============================================================================================================================^\n";
            }
            int i;
            for(i=0;i<func_args[callfunc].first.size();i++) // compulsory parameters
            {
                string* tt = newTemp();

                removenewlines(n2c[i]);

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
                    
                    removenewlines(n2c[v]);

                    n->code = merge(3,
                        n->code,
                        gen(*(tt) + " = " + *(n2c[v])),
                        gen("param " + *(tt))
                    );
                }
                else
                {
                    n->code = merge(2,
                        n->code,
                        gen("param NULL")
                    );
                }
            }

            n->code = merge(4,
                n->code,
                gen("stackpointer +xxx"),
                gen("\tcall " + mcallfunc + "," + to_string(func_args[callfunc].first.size() + func_args[callfunc].second.size())),
                gen("stackpointer -yyy")
            );
        }
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("continued_argument.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        generate3AC(n->children[2]);

        n->code = merge(2,
            n->children[0]->code,
            n->children[2]->code
        );
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    CHECK("continued_argument.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        n->code = merge();
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }
    
    CHECK("argument.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("argument.3")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("argument.4")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;
    }
    CHECK("argument.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);
        if(debug3ac) cout << "[3AC]: "<<"Hi guys"<<endl;

        generate3AC(n->children[2]);

        if(debug3ac) cout << "[3AC]: "<<"Hellow World"<<endl;

        k2n[*(n->children[0]->val)] = x;
        n2c[x] = n->children[2]->val;
        x++;

        n->code = merge();
        
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }
    CHECK("argument.5")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        generate3AC(n->children[0]);

        n2c[x] = n->children[0]->val;
        x++;

        n->code = merge(1,
            n->children[0]->code
        );
        
        n->val = n->children[0]->val;
        
        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

    }

    CHECK("comp_iter.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";

        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("comp_for.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }
    CHECK("comp_for.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }CHECK("comp_if.1")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }CHECK("comp_if.2")
    {
        if(debug3ac) cout << "[3AC]: "<<"Entered "<<n->name<<" (" << n->debug_type << ")\n";
        
        cout << "[3AC ERROR]: "<<"Feature Not Supported : " << n->type << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}

        return -1;

    }


    // ****************************************** TERMINALS IN THE GRAMMAR ***********************************************
    
    else {
        // This case should never happen in the program flow.
        if(debug3ac) cout << "[3AC]: "<<"Entered " << n->name << " (" << n->debug_type << ")\n";
        
        if(DEBUG_3AC_OUTSIDE_VERBOSE) cout << "[3AC]: "<< "Error : child-name not found - "<< n->name<<" (" << n->type <<")" << "\n";

        if(after3ac) cout << "[3AC]: " << "Getting Out of " << n->name << "(" << n->debug_type << ")\n";
        if(printcode) {printCode(n);}
    }


    return 0;
}

/*********************************** FUNCTION DEFINITIONS *********************************************************/


#endif // GEN_3AC_CPP

