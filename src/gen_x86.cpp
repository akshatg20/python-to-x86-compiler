#ifndef GEN_X86_CPP
#define GEN_X86_CPP

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <fstream>
#include <cmath>
#include <regex>

#ifndef GEN_X86_HPP
#include "gen_x86.hpp"
#endif
#ifndef SYMBOL_TABLE_HPP
#include "symbol_table.hpp"
#endif
#ifndef UTILS_HPP
#include "utils.hpp"
#endif
using namespace std;

#define CHECK(z) else if(type == z)

extern char* inputfile_path;
extern RegisterAllocation* regAlloc;
extern unordered_map<string, SymbolTable*> labelMap;
extern int typeset_3ac_code(string);

int LFE_ctr = 0;                                              // counter to set LFE0, LFE1 etc. 
int LFX_ctr = 0;                                              // counter to set LFX0, etc.  
int LC_ctr = 0;                                               // counter to keep track of LC0,LC1 etc.  
int param_ctr = 0;       

char* name;                                                   // string which holds the current label in use
string func_name = "";                                        // string which holds the current function_name in use
string label_name = "";                                       // string which holds the current label in use
unordered_map<string,int> temp_x86;                           // stores type of variable  
stack<string> funcParams;                                     // stores the variable names of the parameters in a function
unordered_map< string,vector<string> > ump;                   // stores the string literals used in a particular function scope
unordered_map< string, unordered_map<string,int> > varType;   // for each function scope, stores the type of value stored in a variable
unordered_map< string,string> str_to_label;                   // stores which .LC a string is present in
string prevParam;                                             // stores the last param which was encountered during the first pass  
unordered_map< string,int> isPrintParam;                      // checks if a param is part of a print call
unordered_map< string,int > isReturnParam;                    // check if a variable is a return value from a function
unordered_map< string,int> numParamsInFunc;                   // stores the number of parameters in each function  


int lineno = 0;                                               // used for debugging
int offset_ctr = 0;                                           // used for debugging  
int DEBUG_X86_INSIDE_VERBOSE = 0;                             // used for debugging  
int DEBUG_X86_OUTSIDE_VERBOSE = 0;                            // used for debugging  

LRU* lru;                                                     // used for register allocation  

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.
 

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.
int x86_first_pass(string code,string prevLine);
int get_3AC_form(vector<string> words);
void gen_x86_prologue(FILE* of);
void gen_x86_func_preset(vector<string> words, FILE* of);
void gen_x86_function_block_label(vector<string> words, FILE* of);
void gen_x86_func_prologue(FILE* of);
void gen_x86_imm_assign(vector<string> words, FILE* of);
void gen_x86_string_assign(string line, FILE* of);
void gen_x86_simple_assign(vector<string> words, FILE* of);
void gen_x86_uncond_jmp(vector<string> words, FILE* of);
void gen_x86_cond_jmp(vector<string> words, FILE* of, int type);
void gen_x86_semi_assign(vector<string> words, FILE* of, int type);
void gen_x86_exponent(string regSrc,string newReg, FILE* of, int exponent);
void gen_x86_return(FILE* of);
void gen_x86_func_epilogue( FILE* of);
void gen_x86_self_assign(vector<string> words, FILE* of, int type);
void gen_x86_param_push(vector<string> words, FILE* of);
void gen_x86_stackpointer_inc(FILE* of);
void gen_x86_stackpointer_dec(FILE* of);
void gen_x86_print_call(FILE* of);
void gen_x86_func_call(vector<string> words, FILE* of);
void gen_x86_bin_op(vector<string> words, FILE* of, int type);
void gen_x86_popparam(vector<string> words, FILE* of);
void gen_x86_ret_val_push(vector<string> words, FILE* of);
void gen_x86_array_assign(vector<string> words, FILE* of);
void gen_x86_right_idx(vector<string> words, FILE* of);
void gen_x86_left_idx(vector<string> words, FILE* of);                  
void gen_x86_address_assign(vector<string> words, FILE* of);            // not needed
void gen_x86_left_ptr(vector<string> words, FILE* of);                  // not needed
void gen_x86_right_ptr(vector<string> words, FILE* of);                 // not needed
void gen_x86_both_ptr(vector<string> words, FILE* of);                  // not needed
void gen_x86_both_idx(vector<string> words, FILE* of);                  
void gen_x86_unary_neg(vector<string> words, FILE* of);                 // not tested
void gen_x86_unary_bitwise_not(vector<string> words, FILE* of);         // not tested
void gen_x86_bool_assign(vector<string> words, FILE* of, int type);     // not tested
void gen_x86_simple_cond_jump(vector<string> words, FILE* of);          // not tested


/*********************************** LRU SCHEME FUNCTIONS *********************************************************/

void LRU::addNode(Node* node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void LRU::deleteNode(Node* node) {
    Node *delprev = node->prev;
    Node *delnext = node->next;
    delprev->next = delnext;
    delnext->prev = delprev;
}

LRU::LRU(int capacity) : cap(capacity) {
    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
}

LRU::LRU(vector<string> &vec) {
    cap = vec.size();

    setRegister(vec);

    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
}

void LRU::setRegister(vector<string> regs) 
{
    for(int i = 0; i < regs.size(); i++) {
        int idx = i + 1;  // Assuming unique numeric id for simplicity
        keyToReg[idx] = regs[i];
        put2(idx, idx);  // Initialize the LRU with dummy values
    }
}

string LRU::getLeastRecentlyUsed() 
{
    if (tail->prev == head) {
        return "No entries in cache";
    }
    Node* lru = tail->prev;
    return keyToReg[lru->key];
}

void LRU::put(string reg) 
{
    int key = 0;
    // Finding the key for the register
    for (auto &pair : keyToReg) 
    {
        if (pair.second == reg) {
            key = pair.first;
            break;
        }
    }
    put2(key, key);  // Using key as value for simplicity
}

void LRU::put2(int key, int value) 
{
    if(mp.count(key)) 
    {
        Node* existingNode = mp[key];
        deleteNode(existingNode);
        existingNode->value = value;
        addNode(existingNode);
    } 
    else 
    {
        if(mp.size() == cap) {
            Node* lru = tail->prev;
            deleteNode(lru);
            mp.erase(lru->key);
            delete lru;
        }
        Node* newNode = new Node(key, value);
        mp[key] = newNode;
        addNode(newNode);
    }
}


/*********************************** LRU SCHEME FUNCTIONS *********************************************************/


/*********************************** REGISTER ALLOCATION FUNCTIONS *********************************************************/

RegisterAllocation::RegisterAllocation() {

    regs = new RegisterSet();

    // set all register values to zero
    this->regs->rax = 0;
    this->regs->rdi = 0;
    this->regs->rsi = 0;
    this->regs->rdx = 0;
    this->regs->rcx = 0;
    this->regs->r8 = 0;
    this->regs->r9 = 0;
    this->regs->r10 = 0;
    this->regs->r11 = 0;
    this->regs->r12 = 0;
    this->regs->r13 = 0;
    this->regs->r14 = 0;
    this->regs->r15 = 0;
    this->regs->rsp = 0;
    this->regs->rbx = 0;
    this->regs->rbp = 0;
    this->regs->rip = 0;
    this->regs->eflags = 0;

    // Setup the LRU Eviction policy
    this->local_var_eviction = new LRU(13);

    // mark each register as empty
    this->isRegFilled["%rax"] = false;
    this->isRegFilled["%rdi"] = false;         
    this->isRegFilled["%rsi"] = false;
    this->isRegFilled["%rdx"] = false;
    this->isRegFilled["%r8"] = false;
    this->isRegFilled["%r9"] = false;
    this->isRegFilled["%r10"] = false;
    this->isRegFilled["%r11"] = false;
    this->isRegFilled["%r12"] = false;
    this->isRegFilled["%r13"] = false;
    this->isRegFilled["%r14"] = false;
    this->isRegFilled["%r15"] = false;
    this->isRegFilled["%rcx"] = false;
    this->isRegFilled["%rbx"] = false;
    this->isRegFilled["%rip"] = false;

    // mark each register as empty
    this->isRegFilled["%eax"] = false;
    this->isRegFilled["%edi"] = false;         
    this->isRegFilled["%esi"] = false;
    this->isRegFilled["%edx"] = false;
    this->isRegFilled["%r8d"] = false;
    this->isRegFilled["%r9d"] = false;
    this->isRegFilled["%r10d"] = false;
    this->isRegFilled["%r11d"] = false;
    this->isRegFilled["%r12d"] = false;
    this->isRegFilled["%r13d"] = false;
    this->isRegFilled["%r14d"] = false;
    this->isRegFilled["%r15d"] = false;
    this->isRegFilled["%ecx"] = false;
    this->isRegFilled["%ebx"] = false;

    // mark each register as empty
    this->isRegFilled["%ax"] = false;
    this->isRegFilled["%di"] = false;         
    this->isRegFilled["%si"] = false;
    this->isRegFilled["%dx"] = false;
    this->isRegFilled["%r8w"] = false;
    this->isRegFilled["%r9w"] = false;
    this->isRegFilled["%r10w"] = false;
    this->isRegFilled["%r11w"] = false;
    this->isRegFilled["%r12w"] = false;
    this->isRegFilled["%r13w"] = false;
    this->isRegFilled["%r14w"] = false;
    this->isRegFilled["%r15w"] = false;
    this->isRegFilled["%cx"] = false;
    this->isRegFilled["%bx"] = false;

    // mark each register as empty
    this->isRegFilled["%al"] = false;
    this->isRegFilled["%dil"] = false;         
    this->isRegFilled["%sil"] = false;
    this->isRegFilled["%dl"] = false;
    this->isRegFilled["%r8b"] = false;
    this->isRegFilled["%r9b"] = false;
    this->isRegFilled["%r10b"] = false;
    this->isRegFilled["%r11b"] = false;
    this->isRegFilled["%r12b"] = false;
    this->isRegFilled["%r13b"] = false;
    this->isRegFilled["%r14b"] = false;
    this->isRegFilled["%r15b"] = false;
    this->isRegFilled["%cl"] = false;
    this->isRegFilled["%bl"] = false;

    return;
}

void RegisterAllocation::setRTV(string regName, string varName) {
    this->regToVar[regName] = varName;
    this->local_var_eviction->put(regName);
    return;
}

void RegisterAllocation::setVTR(string regName, string varName) {
    this->varToReg[varName] = regName;
    this->local_var_eviction->put(regName);
    return;
}

string RegisterAllocation::getRegName(string varName, int flag) {
    // return this->varToReg[varName];
    if(varToReg.find(varName) == varToReg.end()) {
        // if(flag) printf("[REGISTER ALLOCATION ERROR]: Passed variable not present in any register\n");
        return "NULL";
    }
    string key = this->varToReg[varName];
    this->local_var_eviction->put(key);
    return key;
}

string RegisterAllocation::getVarName(string regName) {
    if(this->regToVar.find(regName) == this->regToVar.end()) {
        printf("[REGISTER ALLOCATION ERROR]: Passed register doesn't hold any value\n");
        return "NULL";
    }
    this->local_var_eviction->put(regName);
    return this->regToVar[regName];
}

int RegisterAllocation::getRegVal(string regName) {
    if(this->isRegFilled.find(regName) == this->isRegFilled.end()) {
        printf("[REGISTER ALLOCATION ERROR]: Register entry not found in hash table\n");
        return -2;
    }
    else if(this->isRegFilled[regName] == false) {
        printf("[REGISTER ALLOCATION ERROR]: Register is empty\n");
        return -1;
    }
    else {
        if(regName == "%rax") return this->regs->rax;
        else if(regName == "%rdi") return this->regs->rdi;
        else if(regName == "%rsi") return this->regs->rsi;
        else if(regName == "%rdx") return this->regs->rdx;
        else if(regName == "%rcx") return this->regs->rcx;
        else if(regName == "%r8") return this->regs->r8;
        else if(regName == "%r9") return this->regs->r9;
        else if(regName == "%r10") return this->regs->r10;
        else if(regName == "%r11") return this->regs->r11;
        else if(regName == "%r12") return this->regs->r12;
        else if(regName == "%r13") return this->regs->r13;
        else if(regName == "%r14") return this->regs->r14;
        else if(regName == "%r15") return this->regs->r15;
        else if(regName == "%rsp") return this->regs->rsp;
        else if(regName == "%rbx") return this->regs->rbx;
        else if(regName == "%rbp") return this->regs->rbp;
        else if(regName == "%rip") return this->regs->rip;
        else if(regName.size() >= 8) {
            int pos = regName.find('%');
            string regNameTemp = regName.substr(pos+1);
            regNameTemp.pop_back();
            if(regNameTemp == "rbp") return this->regs->stc_loc[regName];
            else {
                printf("[REGISTER ALLOCATION ERROR]: Unknown register entry used -- 2\n");
                return -2;
            }
        }
        else {
            printf("[REGISTER ALLOCATION ERROR]: Unknown register entry used\n");
            return -2;
        }
    }
    this->local_var_eviction->put(regName);
    return 0;
}

int RegisterAllocation::setRegVal(string regName, int val) {
    if( (this->isRegFilled.find(regName) == this->isRegFilled.end()) || (this->isRegFilled[regName] == false) ) {
        this->isRegFilled[regName] = true;
    }
    this->local_var_eviction->put(regName);

    // set the actual value also
    if(regName == "%rax") this->regs->rax = val;
    else if(regName == "%rdi")  this->regs->rdi = val;
    else if(regName == "%rsi")  this->regs->rsi = val;
    else if(regName == "%rdx")  this->regs->rdx = val;
    else if(regName == "%rcx")  this->regs->rcx = val;
    else if(regName == "%r8")  this->regs->r8 = val;
    else if(regName == "%r9")  this->regs->r9 = val;
    else if(regName == "%r10")  this->regs->r10 = val;
    else if(regName == "%r11")  this->regs->r11 = val;
    else if(regName == "%r12")  this->regs->r12 = val;
    else if(regName == "%r13")  this->regs->r13 = val;
    else if(regName == "%r14")  this->regs->r14 = val;
    else if(regName == "%r15")  this->regs->r15 = val;
    else if(regName == "%rsp")  this->regs->rsp = val;
    else if(regName == "%rbx")  this->regs->rbx = val;
    else if(regName == "%rbp")  this->regs->rbp = val;
    else if(regName == "%rip")  this->regs->rip = val;
    else if(regName.size() >= 8) {
        int pos = regName.find('%');
        string regNameTemp = regName.substr(pos+1);
        regNameTemp.pop_back();
        if(regNameTemp == "rbp") this->regs->stc_loc[regName] = val;
        else {
            printf("[REGISTER ALLOCATION ERROR]: Unknown register entry used -- 2\n");
            return -1;
        }
    }
    else {
        printf("[REGISTER ALLOCATION ERROR]: Unknown register entry used\n");
        return -1;
    }
    return 0;
}

int run_x86() {
    return 0;
}

string RegisterAllocation::auxiliary_allocateReg(int context, int* flag, int flag_64_bit) {
    // in case registers need to be allocated for function arguments
    (*flag) = 0;
    
    if(context == FUNC_ARG) {
        if(isRegFilled["%rdi"] == false) {
            isRegFilled["%rdi"] = true;
            isRegFilled["%edi"] = true;
            isRegFilled["%di"] = true;
            isRegFilled["%dil"] = true;
            if(flag_64_bit == 0) return "%edi";
            else return "%rdi";
        }
        else if(isRegFilled["%rsi"] == false) {
            isRegFilled["%rsi"] = true;
            isRegFilled["%esi"] = true;
            isRegFilled["%si"] = true;
            isRegFilled["%sil"] = true;
            if(flag_64_bit == 0) return "%esi";
            else return "%rsi";
        }
        else if(isRegFilled["%rdx"] == false) {
            isRegFilled["%rdx"] = true;
            isRegFilled["%edx"] = true;
            isRegFilled["%dx"] = true;
            isRegFilled["%dl"] = true;
            if(flag_64_bit == 0) return "%edx";
            else return "%rdx";
        }
        else if(isRegFilled["%rcx"] == false) {
            isRegFilled["%rcx"] = true;
            isRegFilled["%ecx"] = true;
            isRegFilled["%cx"] = true;
            isRegFilled["%cl"] = true;
            if(flag_64_bit == 0) return "%ecx";
            else return "%rcx";
        }
        else if(isRegFilled["%r8"] == false) {
            isRegFilled["%r8"] = true;
            isRegFilled["%r8d"] = true;
            isRegFilled["%r8w"] = true;
            isRegFilled["%r8b"] = true;
            if(flag_64_bit == 0) return "%r8d";
            else return "%r8";
        }     
        else if(isRegFilled["%r9"] == false) {
            isRegFilled["%r9"] = true;
            isRegFilled["%r9d"] = true;
            isRegFilled["%r9w"] = true;
            isRegFilled["%r9b"] = true;
            if(flag_64_bit == 0) return "%r9d";
            else return "%r9";
        }  
        else {
            /* code required for cases of more than 6 arguments */
            printf("[REGISTER ALLOCATION ERROR]: Functionality for more than 6 function arguments not provided yet\n");
            return "NULL";
        } 
    }

    else if(context == LOCAL_VAL) {
        // order of preference: rbx, r10, r11, r12, r13, r14, r15, r9, r8, rcx, rdx, rsi, rdi
        if(isRegFilled["%rbx"] == false) {
            isRegFilled["%rbx"] = true;
            isRegFilled["%ebx"] = true;
            isRegFilled["%bx"] = true;
            isRegFilled["%bl"] = true;
            if(flag_64_bit == 0) return "%ebx";
            else return "%rbx";
        }
        else if(isRegFilled["%r10"] == false) {
            isRegFilled["%r10"] = true;
            isRegFilled["%r10d"] = true;
            isRegFilled["%r10w"] = true;
            isRegFilled["%r10b"] = true;
            if(flag_64_bit == 0) return "%r10d";
            else return "%r10";
        }
        else if(isRegFilled["%r11"] == false) {
            isRegFilled["%r11"] = true;
            isRegFilled["%r11d"] = true;
            isRegFilled["%r11w"] = true;
            isRegFilled["%r11b"] = true;
            if(flag_64_bit == 0) return "%r11d";
            else return "%r11";
        }
        else if(isRegFilled["%r12"] == false) {
            isRegFilled["%r12"] = true;
            isRegFilled["%r12d"] = true;
            isRegFilled["%r12w"] = true;
            isRegFilled["%r12b"] = true;
            if(flag_64_bit == 0) return "%r12d";
            else return "%r12";
        }
        else if(isRegFilled["%r13"] == false) {
            isRegFilled["%r13"] = true;
            isRegFilled["%r13d"] = true;
            isRegFilled["%r13w"] = true;
            isRegFilled["%r13b"] = true;
            if(flag_64_bit == 0) return "%r13d";
            else return "%r13";
        }     
        else if(isRegFilled["%r14"] == false) {
            isRegFilled["%r14"] = true;
            isRegFilled["%r14d"] = true;
            isRegFilled["%r14w"] = true;
            isRegFilled["%r14b"] = true;
            if(flag_64_bit == 0) return "%r14d";
            else return "%r14";
        } 
        else if(isRegFilled["%r15"] == false) {
            isRegFilled["%r15"] = true;
            isRegFilled["%r15d"] = true;
            isRegFilled["%r15w"] = true;
            isRegFilled["%r15b"] = true;
            if(flag_64_bit == 0) return "%r15d";
            else return "%r15";
        }
        else if(isRegFilled["%r9"] == false) {
            isRegFilled["%r9"] = true;
            isRegFilled["%r9d"] = true;
            isRegFilled["%r9w"] = true;
            isRegFilled["%r9b"] = true;
            if(flag_64_bit == 0) return "%r9d";
            else return "%r9";
        }
        else if(isRegFilled["%r8"] == false) {
            isRegFilled["%r8"] = true;
            isRegFilled["%r8d"] = true;
            isRegFilled["%r8w"] = true;
            isRegFilled["%r8b"] = true;
            if(flag_64_bit == 0) return "%r8d";
            else return "%r8";
        }     
        else if(isRegFilled["%rcx"] == false) {
            isRegFilled["%rcx"] = true;
            isRegFilled["%ecx"] = true;
            isRegFilled["%cx"] = true;
            isRegFilled["%cl"] = true;
            if(flag_64_bit == 0) return "%ecx";
            else return "%rcx";
        }
        else if(isRegFilled["%rdi"] == false) {
            isRegFilled["%rdi"] = true;
            isRegFilled["%edi"] = true;
            isRegFilled["%di"] = true;
            isRegFilled["%dil"] = true;
            if(flag_64_bit == 0) return "%edi";
            else return "%rdi";
        }
        else if(isRegFilled["%rsi"] == false) {
            isRegFilled["%rsi"] = true;
            isRegFilled["%esi"] = true;
            isRegFilled["%si"] = true;
            isRegFilled["%sil"] = true;
            if(flag_64_bit == 0) return "%esi";
            else return "%rsi";
        }
        else if(isRegFilled["%rdx"] == false) {
            isRegFilled["%rdx"] = true;
            isRegFilled["%edx"] = true;
            isRegFilled["%dx"] = true;
            isRegFilled["%dl"] = true;
            if(flag_64_bit == 0) return "%edx";
            else return "%rdx";
        }  
        else {
            (*flag) = 1;
            string usage_reg = local_var_eviction->getLeastRecentlyUsed();
            return usage_reg;
        }
    }

    else if(context == FUNC_RTN) {
        if(isRegFilled["%rax"] == false) {
            isRegFilled["%rax"] = true;
            isRegFilled["%eax"] = true;
            isRegFilled["%ax"] = true;
            isRegFilled["%al"] = true;
            if(flag_64_bit == 0) return "%eax";
            else return "%rax";
        }
        else {
            printf("[REGISTER ALLOCATION ERROR]: %%rax register not empty to store return value from function\n");
            return "NULL";
        }
    }

    else if(context == DIV) {
        if(isRegFilled["%rdx"] == false) {
            isRegFilled["%rdx"] = true;
            isRegFilled["%edx"] = true;
            isRegFilled["%dx"] = true;
            isRegFilled["dbl"] = true;
            if(flag_64_bit == 0) return "%edx";
            else return "%rdx";
        }
        else {
            printf("[REGISTER ALLOCATION ERROR]: %%rdx register not empty to store return value from div operator\n");
            return "NULL";
        }
    }

    printf("[REGISTER ALLOCATION ERROR]: unknown context passed to register allocator\n");
    return "NULL";
}

string RegisterAllocation::allocateReg(int context, int flag_64_bit) {
    int flag = 0;
    string regName = auxiliary_allocateReg(context, &flag, flag_64_bit);
    if(flag == 0) {
        this->local_var_eviction->put(regName);
        return regName;
    }
    else {
        string valName = this->regToVar[regName];
        return regName;
    }
}

string RegisterAllocation::getFuncArgs(int paramNo) {
    switch (paramNo) {
        case 1:
            return "%edi";
            break;
        case 2:
            return "%esi";
            break;
        case 3:
            return "%edx";
            break;
        case 4:
            return "%ecx";
            break;
        case 5:
            return "%r8d";
            break;
        case 6:
            return "%r9d";
            break;
        default:
            printf("[x86 FUNCTION ARGUMENT ERROR]: more than 6 arguments passed to function\n");
            return "NULL";
            break;
    }
}

void RegisterAllocation::flushRegs(int context) {
    switch (context)
    {
    case FUNC_ARG: {   
        isRegFilled["%edi"] = false;
        isRegFilled["%esi"] = false;
        isRegFilled["%edx"] = false;
        isRegFilled["%ecx"] = false;
        isRegFilled["%r8d"] = false;
        isRegFilled["%r9d"] = false;
        isRegFilled["%rdi"] = false;
        isRegFilled["%rsi"] = false;
        isRegFilled["%rdx"] = false;
        isRegFilled["%rcx"] = false;
        isRegFilled["%r8"] = false;
        isRegFilled["%r9"] = false;
        break;
    }
    case LOCAL_VAL: {
        isRegFilled["%edi"] = false;
        isRegFilled["%esi"] = false;
        isRegFilled["%edx"] = false;
        isRegFilled["%ecx"] = false;
        isRegFilled["%r8d"] = false;
        isRegFilled["%r9d"] = false;
        isRegFilled["%ebx"] = false;
        isRegFilled["%r10d"] = false;
        isRegFilled["%r11d"] = false;
        isRegFilled["%r12d"] = false;
        isRegFilled["%r13d"] = false;
        isRegFilled["%r14d"] = false;
        isRegFilled["%r15d"] = false;
        isRegFilled["%eax"] = false;
        isRegFilled["%rdi"] = false;
        isRegFilled["%rsi"] = false;
        isRegFilled["%rdx"] = false;
        isRegFilled["%rcx"] = false;
        isRegFilled["%r8"] = false;
        isRegFilled["%r9"] = false;
        isRegFilled["%rbx"] = false;
        isRegFilled["%r10"] = false;
        isRegFilled["%r11"] = false;
        isRegFilled["%r12"] = false;
        isRegFilled["%r13"] = false;
        isRegFilled["%r14"] = false;
        isRegFilled["%r15"] = false;
        isRegFilled["%rax"] = false;        
        break;
    }
    case FUNC_RTN: {
        isRegFilled["%eax"] = false;
        isRegFilled["%rax"] = false;
        break;
    }
    default:
        printf("[REGISTER FLUSH ERROR]: unknown context passed\n");
        break;
    }
}

/*********************************** REGISTER ALLOCATION FUNCTIONS *********************************************************/


/*********************************** X86_64 GENERATION FUNCTIONS *********************************************************/

string convert_to_64_bit(string s) {
    if(s=="%eax")
        return "%rax";
    else if(s=="%edi")
        return "%rdi";
    else if(s=="%esi")
        return "%rsi";
    else if(s=="%edx")
        return "%rdx";
    else if(s=="%ecx")
        return "%rcx";
    else if(s=="%r8d")
        return "%r8";
    else if(s=="%r9d")
        return "%r9";
    else if(s=="%r10d")
        return "%r10";
    else if(s=="%r11d")
        return "%r11";
    else if(s=="%esp")
        return "%rsp";
    else if(s=="%ebx")
        return "%rbx";
    else if(s=="%ebp")
        return "%rbp";
    else if(s=="%r12d")
        return "%r12";
    else if(s=="%r13d")
        return "%r13";
    else if(s=="%r14d")
        return "%r14";
    else if(s=="%r15d")
        return "%r15";
    else
        return "Shashwat";
}

// function to generate complete x86_64 code
int generate_x86(string code_3ac, FILE* of) {
    // First pass of x86
    string prevLine = "";
    int flag = x86_first_pass(code_3ac,prevLine);

    // cout << "here" << endl;

    if(flag < 0) {
        printf("[x86_64 GENERATION ERROR]: Error in first pass of x86\n");
        return -1;
    }

    lineno = 0;

    // Prologue of any x86_64 assembly code
    gen_x86_prologue(of);

    // cout << "here" << endl;


    // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "x86 generation started\n";

    int offset = 0;
    while(offset < code_3ac.length()) {
        if(DEBUG_X86_OUTSIDE_VERBOSE) {
            cout << "\n############################################################\n";
            cout << "\nSecond Pass: lineno = " << ++lineno << endl;
        }
        string line = ret_line(code_3ac, offset);
        if(DEBUG_X86_OUTSIDE_VERBOSE) cout << line << endl;
        offset = offset + line.length() + 1;
        vector<string> words = convertToWords(line);
        int type = get_3AC_form(words);

        if(false) {
            continue;
        }
        CHECK(FUNC_LABEL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("FUNC_LABEL passed\n");
            gen_x86_func_preset(words,of);
        }
        CHECK(LABEL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("LFB_LABEL passed\n");
            gen_x86_function_block_label(words,of);
        }
        CHECK(FUNC_BEGIN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("beginfunc passed\n");
            gen_x86_func_prologue(of);
        }
        CHECK(IMM_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("immediate assign stmt passed\n");
            gen_x86_imm_assign(words,of);
        }
        CHECK(STRING_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("string assign stmt passed\n");
            gen_x86_string_assign(line,of);
        }
        CHECK(ARRAY_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("array assign stmt passed\n");
            gen_x86_array_assign(words,of);
        }       
        CHECK(RGHT_IDX_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("array index right stmt passed\n");
            gen_x86_right_idx(words,of);
        } 
        CHECK(LEFT_IDX_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("array index left stmt passed\n");
            gen_x86_left_idx(words,of);
        } 
        CHECK(ADDRESS_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("address assign stmt passed\n");
            gen_x86_address_assign(words,of);
        }  
        CHECK(PTR_ASSIGN_RGHT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("ptr assign right stmt passed\n");
            gen_x86_right_ptr(words,of);
        } 
        CHECK(PTR_ASSIGN_LEFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("ptr assign left stmt passed\n");
            gen_x86_left_ptr(words,of);
        }  
        CHECK(BOTH_IDX_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("both idx assign stmt passed\n");
            gen_x86_both_idx(words,of);
        }
        CHECK(PTR_ASSIGN_BOTH) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("both ptr assign stmt passed\n");
            gen_x86_both_ptr(words,of);
        }        
        CHECK(PTR_ASSIGN_LEFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("ptr assign left stmt passed\n");
            gen_x86_left_ptr(words,of);
        }                                                              
        CHECK(SIMPLE_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("simple assign stmt passed\n");
            gen_x86_simple_assign(words,of);
        } 
        CHECK(UNARY_SUB_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("unary neg assign stmt passed\n");
            gen_x86_unary_neg(words,of);
        }    
        CHECK(UNARY_BIT_NOT_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("unary bitwise not assign stmt passed\n");
            gen_x86_unary_bitwise_not(words,of);
        }           
        CHECK(UNARY_NOT_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("unary not assign stmt passed\n");
            gen_x86_unary_bitwise_not(words,of);
        }           
        CHECK(UNCOND_JMP) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("unconditional jump stmt passed\n");
            gen_x86_uncond_jmp(words,of);
        }
        CHECK(COND_JMP) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("simple conditional jump stmt passed\n");
            gen_x86_simple_cond_jump(words,of);            
        }        
        CHECK(COND_JMP_LT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("conditional jump LT stmt passed\n");
            gen_x86_cond_jmp(words,of,COND_JMP_LT);            
        }
        CHECK(COND_JMP_GT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("conditional jump GT stmt passed\n");
            gen_x86_cond_jmp(words,of,COND_JMP_GT);            
        }
        CHECK(COND_JMP_LTE) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("conditional jump LTE stmt passed\n");
            gen_x86_cond_jmp(words,of,COND_JMP_LTE);            
        }
        CHECK(COND_JMP_GTE) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("conditional jump GTE stmt passed\n");
            gen_x86_cond_jmp(words,of,COND_JMP_GTE);            
        }
        CHECK(COND_JMP_EQ) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("conditional jump EQ stmt passed\n");
            gen_x86_cond_jmp(words,of,COND_JMP_EQ);            
        }       
        CHECK(COND_JMP_NEQ) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("conditional jump NEQ stmt passed\n");
            gen_x86_cond_jmp(words,of,COND_JMP_NEQ);            
        }           
        CHECK(SEMI_ADD) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn + stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_ADD);   
        }   
        CHECK(SEMI_SUB) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn - stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_SUB);   
        }
        CHECK(SEMI_MUL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn * stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_MUL);   
        }                                      
        CHECK(SEMI_DIV) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn / stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_DIV);   
        }        
        CHECK(SEMI_FLOOR_DIV) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn // stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_FLOOR_DIV);   
        }        
        CHECK(SEMI_POWER) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn ** stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_POWER);   
        }        
        CHECK(SEMI_BIT_AND) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn & stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_BIT_AND);   
        }
        CHECK(SEMI_BIT_OR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn | stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_BIT_OR);   
        }                
        CHECK(SEMI_BIT_XOR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn ^ stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_BIT_XOR);   
        }        
        CHECK(SEMI_REM) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "semi assgn %" << "stmt passed\n";      
            gen_x86_semi_assign(words,of,SEMI_REM);   
        }        
        CHECK(SEMI_LEFT_SHIFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn << stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_LEFT_SHIFT);   
        }        
        CHECK(SEMI_RGHT_SHIFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn >> stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_RGHT_SHIFT);   
        }        
        CHECK(SEMI_AND) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn && stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_AND);   
        }        
        CHECK(SEMI_OR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("semi assgn || stmt passed\n");
            gen_x86_semi_assign(words,of,SEMI_OR);   
        }    
        CHECK(IMM_ADD) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn + stmt passed\n");
            gen_x86_self_assign(words,of,IMM_ADD);   
        }   
        CHECK(IMM_SUB) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn - stmt passed\n");
            gen_x86_self_assign(words,of,IMM_SUB);   
        }
        CHECK(IMM_MUL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn * stmt passed\n");
            gen_x86_self_assign(words,of,IMM_MUL);   
        }                                      
        CHECK(IMM_DIV) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn / stmt passed\n");
            gen_x86_self_assign(words,of,IMM_DIV);   
        }        
        CHECK(IMM_FLOOR_DIV) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn // stmt passed\n");
            gen_x86_self_assign(words,of,IMM_FLOOR_DIV);   
        }        
        CHECK(IMM_POWER) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn ** stmt passed\n");
            gen_x86_self_assign(words,of,IMM_POWER);   
        }        
        CHECK(IMM_BIT_AND) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn & stmt passed\n");
            gen_x86_self_assign(words,of,IMM_BIT_AND);   
        }
        CHECK(IMM_BIT_OR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn | stmt passed\n");
            gen_x86_self_assign(words,of,IMM_BIT_OR);   
        }                
        CHECK(IMM_BIT_XOR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn ^ stmt passed\n");
            gen_x86_self_assign(words,of,IMM_BIT_XOR);   
        }        
        CHECK(IMM_REM) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "imm assgn %" << "stmt passed\n"; 
            gen_x86_self_assign(words,of,IMM_REM);   
        }        
        CHECK(IMM_LEFT_SHIFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn << stmt passed\n");
            gen_x86_self_assign(words,of,IMM_LEFT_SHIFT);   
        }        
        CHECK(IMM_RGHT_SHIFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn >> stmt passed\n");
            gen_x86_self_assign(words,of,IMM_RGHT_SHIFT);   
        }        
        CHECK(IMM_AND) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn && stmt passed\n");
            gen_x86_self_assign(words,of,IMM_AND);   
        }        
        CHECK(IMM_OR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("imm assgn || stmt passed\n");
            gen_x86_self_assign(words,of,IMM_OR);   
        }     
        CHECK(BIN_ADD) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op + stmt passed\n");
            gen_x86_bin_op(words,of,BIN_ADD);   
        }   
        CHECK(BIN_SUB) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op - stmt passed\n");
            gen_x86_bin_op(words,of,BIN_SUB);   
        }
        CHECK(BIN_MUL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op * stmt passed\n");
            gen_x86_bin_op(words,of,BIN_MUL);   
        }                                      
        CHECK(BIN_DIV) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op / stmt passed\n");
            gen_x86_bin_op(words,of,BIN_DIV);   
        }        
        CHECK(BIN_FLOOR_DIV) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op // stmt passed\n");
            gen_x86_bin_op(words,of,BIN_FLOOR_DIV);   
        }        
        CHECK(BIN_POWER) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op ** stmt passed\n");
            gen_x86_bin_op(words,of,BIN_POWER);   
        }        
        CHECK(BIN_BIT_AND) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op & stmt passed\n");
            gen_x86_bin_op(words,of,BIN_BIT_AND);   
        }
        CHECK(BIN_BIT_OR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op | stmt passed\n");
            gen_x86_bin_op(words,of,BIN_BIT_OR);   
        }                
        CHECK(BIN_BIT_XOR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op ^ stmt passed\n");
            gen_x86_bin_op(words,of,BIN_BIT_XOR);   
        }        
        CHECK(BIN_REM) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "bin op %" << "stmt passed\n"; 
            gen_x86_bin_op(words,of,BIN_REM);   
        }        
        CHECK(BIN_LEFT_SHIFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op << stmt passed\n");
            gen_x86_bin_op(words,of,BIN_LEFT_SHIFT);   
        }        
        CHECK(BIN_RGHT_SHIFT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op >> stmt passed\n");
            gen_x86_bin_op(words,of,BIN_RGHT_SHIFT);   
        }        
        CHECK(BIN_AND) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op && stmt passed\n");
            gen_x86_bin_op(words,of,BIN_AND);   
        }        
        CHECK(BIN_OR) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bin op || stmt passed\n");
            gen_x86_bin_op(words,of,BIN_OR);   
        }    
        CHECK(BOOL_ASSIGN_EQ) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bool assign eq stmt passed\n");
            gen_x86_bool_assign(words,of,BOOL_ASSIGN_EQ);
        }    
        CHECK(BOOL_ASSIGN_NEQ) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bool assign neq stmt passed\n");
            gen_x86_bool_assign(words,of,BOOL_ASSIGN_NEQ);
        } 
        CHECK(BOOL_ASSIGN_LT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bool assign lt stmt passed\n");
            gen_x86_bool_assign(words,of,BOOL_ASSIGN_LT);
        } 
        CHECK(BOOL_ASSIGN_GT) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bool assign gt stmt passed\n");
            gen_x86_bool_assign(words,of,BOOL_ASSIGN_GT);
        } 
        CHECK(BOOL_ASSIGN_LTE) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bool assign lte stmt passed\n");
            gen_x86_bool_assign(words,of,BOOL_ASSIGN_LTE);
        } 
        CHECK(BOOL_ASSIGN_GTE) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("bool assign gte stmt passed\n");
            gen_x86_bool_assign(words,of,BOOL_ASSIGN_GTE);
        }                                           
        CHECK(PARAM_PUSH) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("param push stmt passed\n");
            gen_x86_param_push(words,of);
        }    
        CHECK(RET_PARAM_PUSH) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("return value push stmt passed\n");
            gen_x86_ret_val_push(words,of);            
        }
        CHECK(PARAM_ASSIGN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("popparam stmt passed\n");
            gen_x86_popparam(words,of);
        }  
        CHECK(STACK_PTR_INC) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("stackpointer +xxx stmt passed\n");
            gen_x86_stackpointer_inc(of); 
        }
        CHECK(STACK_PTR_DEC) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("stackpointer -yyy stmt passed\n");
            gen_x86_stackpointer_dec(of); 
        }      
        CHECK(PRINT_CALL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("call print stmt passed\n");
            gen_x86_print_call(of);            
        } 
        CHECK(FUNC_CALL) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("call func stmt passed\n");
            gen_x86_func_call(words,of);            
        }   
        CHECK(FUNC_RETURN) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("return stmt passed\n");
            gen_x86_return(of);            
        }    
        CHECK(FUNC_END) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("endfunc passed\n");
            gen_x86_func_epilogue(of);                        
        } 
        CHECK(EMPTY_LINE) {
            if(DEBUG_X86_OUTSIDE_VERBOSE) printf("empty line passed\n");
            continue;
        } 
        if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "\n############################################################\n"; 
    }

    fclose(of);
    return 0; // Shows successful run of the x86 generation
}

// stores string literals used
int x86_first_pass(string code, string prevLine) {
    int offset = 0;
    string func_ctxt;

    while(offset < code.length()) {
        lineno++;
        string line = ret_line(code,offset);
        // cout << "At first pass : lineno = " << lineno << endl;
        // cout << line << endl;
        offset += line.length() + 1;
        vector<string> words = convertToWords(line);
        int type = get_3AC_form(words);

        // error case
        if(type == -1) {
            printf("[x86 FIRST PASS ERROR]: Error in getting correct 3AC form at lineno %d\n",lineno);
            // exit(-1);
            return -1;
        }
        else if(type == FUNC_LABEL) {
            func_ctxt = line;
            func_ctxt.pop_back();
        }
        else if(type == SIMPLE_ASSIGN) {
            temp_x86[words[0]] = TYPE_VAR;
        }
        else if(type == BOOL_ASSIGN_GT) {
            temp_x86[words[0]] = BOOL_ASSIGN_GT;
        }
        else if(type == BOOL_ASSIGN_GTE) {
            temp_x86[words[0]] = BOOL_ASSIGN_GTE;
        }
        else if(type == BOOL_ASSIGN_LT) {
            temp_x86[words[0]] = BOOL_ASSIGN_LT;
        }
        else if(type == BOOL_ASSIGN_LTE) {
            temp_x86[words[0]] = BOOL_ASSIGN_LTE;
        }        
        else if(type == BOOL_ASSIGN_NEQ) {
            temp_x86[words[0]] = BOOL_ASSIGN_NEQ;
        }
        else if(type == BOOL_ASSIGN_EQ) {
            temp_x86[words[0]] = BOOL_ASSIGN_EQ;
        }        
        else if(type == STRING_ASSIGN) {

            // if(DEBUG_X86_OUTSIDE_VERBOSE) {
            //     cout << "#############  INSIDE_FIRST_PASS  ###############\n";
            //     cout << "key = " << words[0] << endl;
            //     cout << "#############  INSIDE_FIRST_PASS  ###############\n";
            // }

            int pos;
            if(words[2][0] == '\"')
                pos = line.find('\"');
            else 
                pos = line.find('\'');
            string str_first_pass = line.substr(pos+1); 
            str_first_pass.pop_back();
            temp_x86[words[0]] = TYPE_STR_LITERAL;
            ump[func_ctxt].push_back(str_first_pass);
            LC_ctr++;
        }
        else if(type == RGHT_IDX_ASSIGN) {
            temp_x86[words[0]] = TYPE_VAR;
        }
        else if(type == ARRAY_ASSIGN) {
            temp_x86[words[0]] = TYPE_ARRAY_LITERAL;
        }
        else if(type == IMM_ASSIGN) {
            vector<string> words = convertToWords(line);
            temp_x86[words[0]] = TYPE_INT_LITERAL;
        }
        else if(type == PARAM_PUSH) {
            int pos = words[1].find('[');
            if(pos != string::npos) {
                temp_x86[words[1]] = TYPE_VAR;

            }
            prevParam = words[1];
        }
        else if(type == PRINT_CALL) {
            if(temp_x86.find(prevParam) == temp_x86.end()) {
                printf("[x86 FIRST PASS ERROR]: Previous param not present in variable-type hashmap at lineno %d\n",lineno);
                return -1;
            }
            if(temp_x86[prevParam] == TYPE_INT_LITERAL || temp_x86[prevParam] == TYPE_VAR) {
                string str_first_pass = "%d";
                ump[func_ctxt].push_back(str_first_pass);
                isPrintParam[prevParam] = 1;
                str_to_label[prevParam] = ".LC" + to_string(LC_ctr++);
                // if(DEBUG_X86_OUTSIDE_VERBOSE) {
                //     cout << "#############  INSIDE_FIRST_PASS  ###############\n";
                //     cout << "key = " << prevParam << endl;
                //     cout << "#############  INSIDE_FIRST_PASS  ###############\n";
                // }
            }
        }

        else if(type == PARAM_ASSIGN) {
            vector<string> words2 = convertToWords(prevLine);
            if(get_3AC_form(words2) == STACK_PTR_DEC) {
                isReturnParam[words[0]] = 1;
            }
        }
        else if(type == FUNC_END) {
            varType[func_ctxt] = temp_x86;                          
            temp_x86.clear();

        }

        prevLine = line;
    }

    return 0;    
} 

// lexer for 3AC
int get_3AC_form(vector<string> words) {

    // we need to handle string assign beforehand
    if(words.size() >= 3 && words[2][0] == '\"') return STRING_ASSIGN;
    if(words.size() >= 3 && words[2][0] == '\'') return STRING_ASSIGN; 

    // we need to handle array assign beforehand
    if(words.size() >= 4 && words[2] == "[" && words[words.size()-1] == "]") return ARRAY_ASSIGN;

    switch (words.size()) {

    case 0: {
        return EMPTY_LINE;
        break;
    }

    case 1: {
        // possible cases : beginfunc, endfunc, return , .L1:
        // cout << "here\n";
        // cout << words[0][0] << "\n" << words[0][words[0].size()-1] << "\n";
        if(words[0] == "beginfunc") return FUNC_BEGIN;
        else if(words[0] == "endfunc") return FUNC_END;
        else if(words[0] == "return") return FUNC_RETURN;
        else if(words[0][0] == '.' && words[0][words[0].size()-1] == ':') return LABEL;
        else if( (words[0] == "main:") || ( words[0][0] == '_' && words[0][words[0].size()-1] == ':' )) return FUNC_LABEL;
        break;
    }

    case 2: {
        // possible cases : goto L, param x, return x, call f,n , stackpointer +xxx/-yyy
        if(words[0] == "goto") return UNCOND_JMP;
        else if(words[0] == "param") return PARAM_PUSH;
        else if(words[0] == "paramret") return RET_PARAM_PUSH;
        else if(words[0] == "return") return FUNC_RETURN_VAL;
        else if(words[0] == "call") {
            if(words[1].size() > 5 && words[1].substr(0,5) == "print") return PRINT_CALL;
            else return FUNC_CALL;
        }
        else if(words[0] == "stackpointer") {
            if(words[1][0] == '+') return STACK_PTR_INC;
            else if(words[1][0] == '-') return STACK_PTR_DEC;
        } 
        break;
    }

    case 3: {
        // possible cases: x = y, x = -y, y = x[i], x = &y, *x = y, x = *y, x = popparam
        if(words[1] == "=") {

            string wordLeft = words[0];                 // left word
            string wordRight = words[2];                // right word
            char lL = wordLeft[wordLeft.size()-1];      // last letter of left word
            char rL = wordRight[wordRight.size()-1];    // last letter of right word
            char lS = wordLeft[0];                      // first letter of left word
            char rS = wordRight[0];                     // first letter of right word

            // x = op y

            if(words[0] == words[2]) return EMPTY_LINE;

            if(rS == '+') return UNARY_ADD_ASSIGN;
            if(rS == '-') return UNARY_SUB_ASSIGN;
            if(rS == '!') return UNARY_NOT_ASSIGN;
            if(rS == '~') return UNARY_BIT_NOT_ASSIGN;
            if(rS == '&') return ADDRESS_ASSIGN;

            // x = popparam
            if(wordRight == "popparam") return PARAM_ASSIGN;
            
            // x[i] = y[i]
            if(lL == ']' && rL == ']') return BOTH_IDX_ASSIGN;
            // x[i] = y
            if(lL == ']' && rL != ']') return LEFT_IDX_ASSIGN;
            // x = y[i]
            if(lL != ']' && rL == ']') return RGHT_IDX_ASSIGN;

            // *x = *y
            if(lS == '*' && rS == '*') return PTR_ASSIGN_BOTH;
            // x = *y
            if(lS != '*' && rS == '*') return PTR_ASSIGN_RGHT;
            // *x = y
            if(lS == '*' && rS != '*') return PTR_ASSIGN_LEFT;

            // x = 3
            if(rS <= '9' && rS >= '0') return IMM_ASSIGN;

            // x = symtable(..)
            if(wordRight.size() > 8 && wordRight.substr(0,8) == "symtable") return SYMTABLE_ASSIGN;
            
            // x = y
            else return SIMPLE_ASSIGN;
            break;
        }

        case 4: {
            // possible cases: if x goto L, y = call p,n
            if(words[0] == "if" || words[0] == "ifFalse") return COND_JMP;
            else if(words[2] == "call") {
                if(words[3].size() > 5 && words[3].substr(0,5) == "print") return PRINT_CALL;
                else return FUNC_CALL_ASSIGN;
            }
            break;
        }

        case 5: {

            // boolean assign cases
            if(words[3] == "!=") return BOOL_ASSIGN_NEQ;
            if(words[3] == "<") return BOOL_ASSIGN_LT;
            if(words[3] == ">") return BOOL_ASSIGN_GT;
            if(words[3] == "<=") return BOOL_ASSIGN_LTE;
            if(words[3] == ">=") return BOOL_ASSIGN_GTE;
            if(words[3] == "==") return BOOL_ASSIGN_EQ;

            // possible cases: x = y op z, x = x op 3
            if(words[1] == "=" && words[0] == words[2] && (words[4][0] <= '9' && words[4][0] >= '0') ) {
                if(words[3] == "+") return IMM_ADD;
                if(words[3] == "-") return IMM_SUB; 
                if(words[3] == "*") return IMM_MUL;
                if(words[3] == "/") return IMM_DIV;
                if(words[3] == "//") return IMM_FLOOR_DIV;
                if(words[3] == "**") return IMM_POWER;
                if(words[3] == "&") return IMM_BIT_AND;
                if(words[3] == "|") return IMM_BIT_OR;
                if(words[3] == "^") return IMM_BIT_XOR;
                if(words[3] == "%") return IMM_REM;
                if(words[3] == "<<") return IMM_LEFT_SHIFT;
                if(words[3] == ">>") return IMM_RGHT_SHIFT;
                if(words[3] == "&&") return IMM_AND;
                if(words[3] == "||") return IMM_OR;
            }

            else if(words[1] == "="  && (words[4][0] <= '9' && words[4][0] >= '0')) {
                if(words[3] == "+") return SEMI_ADD;
                if(words[3] == "-") return SEMI_SUB; 
                if(words[3] == "*") return SEMI_MUL;
                if(words[3] == "/") return SEMI_DIV;
                if(words[3] == "//") return SEMI_FLOOR_DIV;
                if(words[3] == "**") return SEMI_POWER;
                if(words[3] == "&") return SEMI_BIT_AND;
                if(words[3] == "|") return SEMI_BIT_OR;
                if(words[3] == "^") return SEMI_BIT_XOR;
                if(words[3] == "%") return SEMI_REM;
                if(words[3] == "<<") return SEMI_LEFT_SHIFT;
                if(words[3] == ">>") return SEMI_RGHT_SHIFT;
                if(words[3] == "&&") return SEMI_AND;
                if(words[3] == "||") return SEMI_OR;                
            }
            
            else if(words[1] == "=") {
                if(words[3] == "+") return BIN_ADD;
                if(words[3] == "-") return BIN_SUB; 
                if(words[3] == "*") return BIN_MUL;
                if(words[3] == "/") return BIN_DIV;
                if(words[3] == "//") return BIN_FLOOR_DIV;
                if(words[3] == "**") return BIN_POWER;
                if(words[3] == "&") return BIN_BIT_AND;
                if(words[3] == "|") return BIN_BIT_OR;
                if(words[3] == "^") return BIN_BIT_XOR;
                if(words[3] == "%") return BIN_REM;
                if(words[3] == "<<") return BIN_LEFT_SHIFT;
                if(words[3] == ">>") return BIN_RGHT_SHIFT;
                if(words[3] == "&&") return BIN_AND;
                if(words[3] == "||") return BIN_OR;
            }
            break;
        }

        case 6: {
            // possible cases: if x op y goto L
            if(words[0] == "if") {
                if(words[2] == "<") return COND_JMP_LT;
                if(words[2] == ">") return COND_JMP_GT;
                if(words[2] == "<=") return COND_JMP_LTE;
                if(words[2] == ">=") return COND_JMP_GTE;
                if(words[2] == "==") return COND_JMP_EQ;
                if(words[2] == "!=") return COND_JMP_NEQ;
            }
            else if(words[0] == "ifFalse") {
                if(words[2] == "<") return COND_JMP_GTE;
                if(words[2] == ">") return COND_JMP_LTE;
                if(words[2] == "<=") return COND_JMP_GT;
                if(words[2] == ">=") return COND_JMP_LT;
                if(words[2] == "==") return COND_JMP_NEQ;
                if(words[2] == "!=") return COND_JMP_EQ;
            }
            break;
        }
    }
    
    default: {
            printf("[X86_64 ERROR]: Unknown 3AC formatting encountered\n");
            // exit(-1);
            return -1;
        }

    }

    // control shouldn't reach here
    return 0;
}

// generates the x86 for the start of any code
void gen_x86_prologue(FILE* of) {
    if(strlen(inputfile_path) == 0) {
        return;
    }
    else {
        char* fileName = getFileName(inputfile_path);
        fprintf(of,"\t.file\t\"%s\"\n\n",fileName);
    }
}

// this function generates the pre-requisites before a function call in x86, should be passed the "func_label" 3AC code
void gen_x86_func_preset(vector<string> words, FILE* of) {
    func_name = words[0];              // func_name = _Z4mainv:
    func_name.pop_back();              // func_name = _Z4mainv
    param_ctr = 0;

    // created a char* for printf
    name = str_to_char(func_name);
    // cout << name << "\n";

    // get the string literals used in this function
    vector<string> literals = vector<string>();

    // get the literals if present in the hash map
    if(ump.find(func_name) != ump.end()) literals = ump[func_name];

    if(literals.size() > 0) fprintf(of,"\t.text\n\t.section\t.rodata\n");

    for(int i = 0; i < literals.size(); i++) {
        fprintf(of,".LC%d:\n",i);
        fprintf(of,"\t.string \"%s\"\n",str_to_char(literals[i]));
        str_to_label[literals[i]] = ".LC" + to_string(i);
        if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "String = " << literals[i] << "  ::  Label = " << str_to_label[literals[i]] << endl;
    }

    name = str_to_char(func_name);
    fprintf(of,"\t.text\n");
    fprintf(of,"\t.globl %s\n",str_to_char(func_name));
    fprintf(of,"\t.type  %s, @function\n",str_to_char(func_name));
    fprintf(of,"%s:\n",str_to_char(func_name));
    // cout << str_to_char(func_name) << "\n";
}

// this function generates the function block label, should be passed labels like .LFB0:
void gen_x86_function_block_label(vector<string> words, FILE* of) {
    words[0] = regex_replace(words[0], regex("::"), ":");
    char* labelName = str_to_char(words[0]);
    
    fprintf(of,"%s\n",labelName);

    label_name = words[0];
    label_name.pop_back();

    // if(words[0].substr(0,4) == ".LFB") {
    //     label_name = words[0];
    //     label_name.pop_back();
    // }

}

// this function generates the x86 for function prologue, should be passed the "beginfunc" line
void gen_x86_func_prologue(FILE* of) {
    fprintf(of,"\t.cfi_startproc\n\tendbr64\n");
    fprintf(of,"\tpushq %%rbp\n");
    fprintf(of,"\t.cfi_def_cfa_offset 16\n\t.cfi_offset 6, -16\n");
    fprintf(of,"\tmovq %%rsp, %%rbp\n");
    fprintf(of,"\t.cfi_def_cfa_register 6\n");

    if(labelMap.find(label_name) != labelMap.end()) {
        SymbolTable* currTable_x86 = labelMap[label_name];
        ActivationRecord* ar = currTable_x86->funcRecord;

        int stackMemAlloc = ar->stackMemAlloc + 8;          // additional 8 bytes allocated
        fprintf(of,"\tsubq $%d, %%rsp\n",stackMemAlloc);

    }



    // check the activation record for any parameters to push
    // ar = currTable_x86->funcRecord;

    // if(ar->numParams > 0) {
    //     for(int i = 0; i < ar->params.size(); i++) {
    //         // find an empty register in context of a function argument being passed
    //         string regName = regAlloc->findEmptyReg(FUNC_ARG);
    //         char* regname = str_to_char(regName);

    //         fprintf(of,"\tpushq %s\n",regname);
    //     }
    // }


    // if(func_name != "main") {
    //     int stackMemAlloc = ar->stackMemAlloc + 8;          // additional 8 bytes allocated
    //     fprintf(of,"\tsubq $%d, %%rsp\n",stackMemAlloc);
    // }

    // if(func_name != "main") fprintf(of,"\tsubq $0, %%rsp\n");
}

// generates x86 code for immediate assignment statements (like x = 4)
void gen_x86_imm_assign(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_imm_assign\n");
        return;
    }


    // get the name of the variable and its offset
    string varName = words[0];
    // get the immediate value which is to be stored in the variable
    int imm = stoi(words[2]);


    if(words[0][0] == '$') {
        string regName = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(regName,varName);
        regAlloc->setVTR(regName,varName);
        fprintf(of,"\tmovl $%d, %s\n",imm,str_to_char(regName));

        if(DEBUG_X86_OUTSIDE_VERBOSE) {
            cout << "Register: " << regAlloc->getRegName(varName) << endl;
            cout << "Variable: " << regAlloc->getVarName(regName) << endl;
        }
        return;
    }



    SymbolTable* currTable_x86 = labelMap[label_name];
    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "current label = " << label_name << endl;
        cout << "Symbol table = " << currTable_x86->name << endl;
    }

    // STentry* entry_x86 = lookup(varName);
    // cout << "here" << endl;

    ActivationRecord* ar = currTable_x86->funcRecord;
    int offset = ar->tempVars[varName];
    // int offset = entry_x86->offset;

    // cout << "here" << endl;

    // get the register required for this immediate assignment
    // offset_ctr += 4;
    string str_offset = to_string(offset);
    string regName = "-" + str_offset + "(%rbp)";

    // print the x86
    fprintf(of,"\tmovl $%d, %s\n",imm,str_to_char(regName));


    // set the variable and register hash map
    regAlloc->setRTV(regName,varName);
    regAlloc->setVTR(regName,varName);


    // set the values stored in the registers
    // regAlloc->setRegVal(regName,imm);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "Register: " << regAlloc->getRegName(varName) << endl;
        cout << "Variable: " << regAlloc->getVarName(regName) << endl;
    }
}

// generates x86 code for array assignment like ( arr = [ 3, 2 , 3 , 1 ] )
void gen_x86_array_assign(vector<string> words, FILE* of) {
    if(words.size() < 5) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_array_assign\n");
        return;
    }
    string varName = words[0];
    string regName;

    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "array name = " << varName << endl;

    SymbolTable* currTable_x86 = labelMap[label_name];
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "symbol table  = " << currTable_x86->name << endl;
    // cout << "here" << endl;
    ActivationRecord* ar = currTable_x86->funcRecord;
    // cout << "here" << endl;
    int offset = ar->tempVars[varName];
    // cout << "here" << endl;
    

    for(int i = 3; i < words.size()-1; i = i+2) {
        regName = "-" + to_string(offset) + "(%rbp)";
        offset -= 4;
        if(words[i][0] <= '9' && words[i][0] >= '0')
            if(words[i] != regName) {
                fprintf(of,"\tmovl $%s, %s\n",str_to_char(words[i]),str_to_char(regName));
            }
        else {
            string tempReg = regAlloc->getRegName(words[i]);
            if(tempReg != regName) {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(tempReg),str_to_char(regName));
            }
        }

        string tempName;
        if(i == 3) tempName = varName + "[-]";
        else tempName = varName + "[" + to_string(i-4) + "]";
        regAlloc->setRTV(tempName,regName);
        regAlloc->setVTR(tempName,regName);

        // store the base address of the array
        if(i == 4) {
            regAlloc->setRTV(regName,varName);
            regAlloc->setVTR(regName,varName);
        }
    }

}

// generates x86 code for indexed array assignment like (x = array[i])
void gen_x86_right_idx(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_right_idx\n");
        return;
    }    

    string destVar = words[0];
    string destReg;
    if(destVar[0] == '$') {
        destReg = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(destReg,destVar);
        regAlloc->setVTR(destReg,destVar);
    }
    else destReg = regAlloc->getRegName(destVar);

    int pos = words[2].find('[');
    string srcVar = words[2].substr(0,pos);
    string idx = words[2].substr(pos+1);
    idx.pop_back();

    if(idx[0] >= '0' && idx[0] <= '9') {
        srcVar = words[2];
        string srcReg = regAlloc->getRegName(srcVar);

        if(DEBUG_X86_OUTSIDE_VERBOSE) {
            cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
            cout << "srcVAR = " << srcVar << ", srcReg = " << srcReg << endl;
        }

        if(srcReg != destReg) {
            fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
        }
        return;
    }

    string srcReg = regAlloc->getRegName(srcVar);
    string idxReg = regAlloc->getRegName(idx);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
        cout << "srcVAR = " << srcVar << ", srcReg = " << srcReg << endl;
        cout << "idx = " << idx << ", idxReg = " << idxReg << endl;
    }

    string tempReg = regAlloc->allocateReg(LOCAL_VAL);
    string tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
    if(idxReg != tempReg) {
        fprintf(of,"\tmovl %s, %s\n",str_to_char(idxReg),str_to_char(tempReg));
    }
    fprintf(of,"\tcltq\n");
    string tempReg_64 = convert_to_64_bit(tempReg);
    string tempReg2_64 = convert_to_64_bit(tempReg2);
    fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
    if(srcReg != tempReg) {
        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(tempReg));
    }
    fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
    if(tempReg != destReg) {
        fprintf(of,"\tmovl %s, %s\n",str_to_char(tempReg),str_to_char(destReg));
    }
}

// generates x86 code for left indexed array assignment like array[i] = x
void gen_x86_left_idx(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_left_idx\n");
        return;
    }

    string srcVar = words[2];
    string srcReg = regAlloc->getRegName(srcVar);

    int pos = words[0].find('[');
    string destVar = words[0].substr(0,pos);
    string idx = words[0].substr(pos+1);
    idx.pop_back();

    if(idx[0] >= '0' && idx[0] <= '9') {
        destVar = words[2];
        string destReg = regAlloc->getRegName(destVar);

        if(DEBUG_X86_OUTSIDE_VERBOSE) {
            cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
            cout << "srcVAR = " << srcVar << ", srcReg = " << srcReg << endl;
        }

        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
        return;
    }

    string destReg = regAlloc->getRegName(destVar);
    string idxReg = regAlloc->getRegName(idx);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
        cout << "srcVAR = " << srcVar << ", srcReg = " << srcReg << endl;
        cout << "idx = " << idx << ", idxReg = " << idxReg << endl;
    }

    /* more needs to be completed */
    string tempReg = regAlloc->allocateReg(LOCAL_VAL);
    string tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
    fprintf(of,"\tmovl %s, %s\n",str_to_char(idxReg),str_to_char(tempReg));
    fprintf(of,"\tcltq\n");
    string tempReg_64 = convert_to_64_bit(tempReg);
    string tempReg2_64 = convert_to_64_bit(tempReg2);
    fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
    fprintf(of,"\tmovl %s, %s\n",str_to_char(destReg),str_to_char(tempReg));
    fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
    fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(tempReg));

}

// generates x86 code for both indexed array assignment like (x[i] = y[i])
void gen_x86_both_idx(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_both_idx\n");
        return;
    }

    string srcReg, destReg, destIdxReg, srcIdxReg, tempReg, tempReg2;

    int pos1 = words[0].find('[');
    string destVar = words[0].substr(0,pos1);
    string destIdx = words[0].substr(pos1+1);
    destIdx.pop_back();

    int pos2 = words[2].find('[');
    string srcVar = words[2].substr(0,pos2);
    string srcIdx = words[2].substr(pos2+1);
    srcIdx.pop_back();

    destReg = regAlloc->getRegName(destVar);
    srcReg = regAlloc->getRegName(srcVar);

    if( (destIdx[0] >= '0' && destIdx[0] <= '9') && (srcIdx[0] >= '0' && srcIdx[0] <= '9') ) {
        srcVar = words[2];
        destVar = words[0];
        destReg = regAlloc->getRegName(destVar);
        srcReg = regAlloc->getRegName(srcVar);
        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
        return;
    }

    else if(srcIdx[0] >= '0' && srcIdx[0] <= '9') {
        srcVar = words[2];
        srcReg = regAlloc->getRegName(srcVar);
        destIdxReg = regAlloc->getRegName(destIdx);   

        tempReg = regAlloc->allocateReg(LOCAL_VAL);
        tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
        fprintf(of,"\tmovl %s, %s\n",str_to_char(destIdxReg),str_to_char(tempReg));
        fprintf(of,"\tcltq\n");
        string tempReg_64 = convert_to_64_bit(tempReg);
        string tempReg2_64 = convert_to_64_bit(tempReg2);
        fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
        fprintf(of,"\tmovl %s, %s\n",str_to_char(destReg),str_to_char(tempReg));
        fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(tempReg));
        return;
    }

    else if(destIdx[0] >= '0' && destIdx[0] <= '9') {
        destVar = words[2];
        destReg = regAlloc->getRegName(destVar);
        srcIdxReg = regAlloc->getRegName(srcVar);   

        tempReg = regAlloc->allocateReg(LOCAL_VAL);
        tempReg2 = regAlloc->allocateReg(LOCAL_VAL);    

        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcIdxReg),str_to_char(tempReg));
        fprintf(of,"\tcltq\n");
        string tempReg_64 = convert_to_64_bit(tempReg);
        string tempReg2_64 = convert_to_64_bit(tempReg2);
        fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(tempReg));
        fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
        fprintf(of,"\tmovl %s, %s\n",str_to_char(tempReg),str_to_char(destReg));     
        return;       
    }

    destIdxReg = regAlloc->getRegName(destIdx);
    srcIdxReg = regAlloc->getRegName(srcIdx);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
        cout << "srcVAR = " << srcVar << ", srcReg = " << srcReg << endl;
        cout << "destidx = " << destIdx << ", idxReg = " << destIdxReg << endl;
        cout << "srcidx = " << srcIdx << ", idxReg = " << srcIdxReg << endl;
    }

    string tempReg3 = regAlloc->allocateReg(LOCAL_VAL);    

    fprintf(of,"\tmovl %s, %s\n",str_to_char(destIdxReg),str_to_char(tempReg));
    fprintf(of,"\tcltq\n");
    string tempReg_64 = convert_to_64_bit(tempReg);
    string tempReg2_64 = convert_to_64_bit(tempReg2);
    fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
    fprintf(of,"\tmovl %s, %s\n",str_to_char(destReg),str_to_char(tempReg));
    fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));

    fprintf(of,"\tmovl %s, %s\n",str_to_char(srcIdxReg),str_to_char(tempReg3));
    fprintf(of,"\tcltq\n");
    string tempReg3_64 = convert_to_64_bit(tempReg3);
    tempReg2_64 = convert_to_64_bit(tempReg2);
    fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg3_64),str_to_char(tempReg2_64));
    fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(tempReg3));
    fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg3));

    fprintf(of,"\tmovl %s, %s\n",str_to_char(tempReg3),str_to_char(tempReg));
}

// generates x86 code for statemetns like (*x = *y)
void gen_x86_both_ptr(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_both_ptr\n");
        return;
    }   

    string srcVar = words[2];
    string srcReg = regAlloc->getRegName(srcVar);

    string destVar = words[0];
    string destReg = regAlloc->getRegName(destVar);

}

// generates x86 code for address assign statements (x = &y)
void gen_x86_address_assign(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_address_assign\n");
        return;
    }

    string srcVar = words[2];
    string srcReg = regAlloc->getRegName(srcVar);

    string destVar = words[0];
    string destReg;
    if(destVar[0] == '$') {
        destReg = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(destReg,destVar);
        regAlloc->setVTR(destReg,destVar);
    }
    else destReg = regAlloc->getRegName(destVar); 


}

// generates x86 code for left pointer statements (*x = y)
void gen_x86_left_ptr(vector<string> words, FILE* of){
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_left_ptr\n");
        return;
    }

    string srcVar = words[2];
    string srcReg = regAlloc->getRegName(srcVar);

    string destVar = words[0];
    string destReg = regAlloc->getRegName(destVar);
}

// generates x86 code for right pointer statements (x = *y)
void gen_x86_right_ptr(vector<string> words, FILE* of){
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_right_ptr\n");
        return;
    }

    string srcVar = words[2];
    string srcReg = regAlloc->getRegName(srcVar);

    string destVar = words[0];
    string destReg;
    if(destVar[0] == '$') {
        destReg = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(destReg,destVar);
        regAlloc->setVTR(destReg,destVar);
    }
    else destReg = regAlloc->getRegName(destVar);


}

// generates x86 code for boolean assign statements like (x = y != z)
void gen_x86_bool_assign(vector<string> words, FILE* of, int type) {
    if(words.size() != 5) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_bool_assign\n");
        return;
    }

    string var2 = words[2];
    string var3 = words[4];
    string reg2 = regAlloc->getRegName(var2);
    string reg3;
    if(var3[0] >= '0' && var3[0] <= '9') reg3 = "$" + var3;
    else reg3 = regAlloc->getRegName(var3);

    string var1 = words[0];
    string reg1;

    if(var1[0] == '$') {
        reg1 = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(reg1,var1);
        regAlloc->setVTR(reg1,var1);
    }
    else {
        reg1 = regAlloc->getRegName(var1);
    }

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "reg1 = " << reg1 << ", var1 = " << var1 << endl;
        cout << "reg2 = " << reg2 << ", var2 = " << var2 << endl;
        cout << "reg3 = " << reg3 << ", var3 = " << var3 << endl;
    }

    if(reg2[0] == '-' && reg3[0] == '-') {
        string tempReg = regAlloc->allocateReg(LOCAL_VAL);
        fprintf(of,"\tmovl %s, %s\n",str_to_char(reg3),str_to_char(tempReg));
        fprintf(of,"\tcmpl %s, %s\n",str_to_char(tempReg),str_to_char(reg2));

    }
    else fprintf(of,"\tcmpl %s, %s\n",str_to_char(reg3),str_to_char(reg2));

    switch (type)
    {
    case BOOL_ASSIGN_EQ:  {
        fprintf(of,"\tsete %%al\n");
        break;
    }
    case BOOL_ASSIGN_NEQ: {
        fprintf(of,"\tsetne %%al\n");
        break;
    }
    case BOOL_ASSIGN_LT: {
        fprintf(of,"\tsetl %%al\n");
        break;
    }
    case BOOL_ASSIGN_GT: {
        fprintf(of,"\tsetg %%al\n");
        break;
    }   
    case BOOL_ASSIGN_LTE: {
        fprintf(of,"\tsetle %%al\n");
        break;
    }    
    case BOOL_ASSIGN_GTE: {
        fprintf(of,"\tsetge %%al\n");
        break;
    }     
    default:
        break;
    }

    fprintf(of,"\tmovsbl %%al, %%eax\n");
    fprintf(of,"\tmovl %%eax, %s\n",str_to_char(reg1));
}

// generates x86 code for string assignment statements (like x = "hello")
void gen_x86_string_assign(string line, FILE* of) {
    // now str_to_label[x] = .LC0 , for example

    vector<string> words = convertToWords(line);

    int pos;
    if(words[2][0] == '\"')
        pos = line.find('\"');
    else 
        pos = line.find('\'');
    string str_second_pass = line.substr(pos+1); 
    str_second_pass.pop_back();

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "string = " << str_second_pass << endl;
        cout << "String Label stored = " << str_to_label[str_second_pass] << endl;
    }


    str_to_label[words[0]] = str_to_label[str_second_pass];
}

// generated x86 code for simple assignment statements like (x = y)
void gen_x86_simple_assign(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_string_assign\n");
        return;
    }

    string srcVar = words[2];
    string destVar = words[0];
    string destReg;
    string srcReg = regAlloc->getRegName(srcVar);

    if(regAlloc->getRegName(destVar) == "NULL") {
        if(destVar[0] == '$')
            destReg = regAlloc->allocateReg(LOCAL_VAL);
        else {
            SymbolTable* currTable_x86 = labelMap[label_name];
            ActivationRecord* ar = currTable_x86->funcRecord;
            int offset = ar->tempVars[destVar];
            string str_offset = to_string(offset);
            destReg = "-" + str_offset + "(%rbp)";
        }
        regAlloc->setRTV(destReg,destVar);
        regAlloc->setVTR(destReg,destVar);
    }
    else destReg = regAlloc->getRegName(destVar);

    // if source variable is a temporary, allocate a new register
    // if(destVar[0] == '$') {
    //     destReg = regAlloc->allocateReg(LOCAL_VAL);
    //     regAlloc->setRTV(destReg,destVar);
    //     regAlloc->setVTR(destReg,destVar);
    // }
    // else {
    //     destReg = regAlloc->getRegName(destVar);
    // }

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "Source Var = " << srcVar << " , Source Reg = " << srcReg << endl;
        cout << "Dest Var = " << destVar << " , Dest Reg  = " << destReg << endl;
        // cout << "Value stored in dest reg = " << regAlloc->getRegVal(destReg) << endl;
    }

    fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
}

// generates x86 code for unary negative assign statements like (x = -y)
void gen_x86_unary_neg(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_right_ptr\n");
        return;
    }

    string srcVar = words[2];
    string srcReg;
    if(srcVar[1] <= '9' && srcVar[1] >= '0') srcReg = "$" + srcVar;
    else srcReg = regAlloc->getRegName(srcVar);

    string destVar = words[0];
    string destReg;
    if(destVar[0] == '$') {
        destReg = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(destReg,destVar);
        regAlloc->setVTR(destReg,destVar);
    }
    else destReg = regAlloc->getRegName(destVar);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
        cout << "srcVAR = " << srcVar << ", srcReg = " << srcReg << endl;
    }

    fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
    fprintf(of,"\tneg %s\n",str_to_char(destReg));
}

// generates x86 code for unary bitwise not assign statements like (x = ~y)
void gen_x86_unary_bitwise_not(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_unary_bitwise_not\n");
        return;
    }

    string srcVar = words[2];
    string srcVar2 = srcVar.substr(1);
    string srcReg;
    if(srcVar[1] <= '9' && srcVar[1] >= '0') srcReg = "$" + srcVar2;
    else srcReg = regAlloc->getRegName(srcVar2);

    string destVar = words[0];
    string destReg;
    if(destVar[0] == '$') {
        destReg = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(destReg,destVar);
        regAlloc->setVTR(destReg,destVar);
    }
    else destReg = regAlloc->getRegName(destVar);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "destVAR = " << destVar << ", destReg = " << destReg << endl;
        cout << "srcVAR = " << srcVar2 << ", srcReg = " << srcReg << endl;
    }

    fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
    fprintf(of,"\tnot %s\n",str_to_char(destReg));
}

// generates x86 code for unconditional jump statements (goto .L1) 
void gen_x86_uncond_jmp(vector<string> words, FILE* of) {
    if(words.size() != 2 || words[0] != "goto") {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_uncond_jmp\n");
        return;
    }
    char* labelName = str_to_char(words[1]);
    fprintf(of,"\tjmp %s\n",labelName);
}

// generates x86 code for simple conditional statements (if x goto L)
void gen_x86_simple_cond_jump(vector<string> words, FILE* of) {
    if(words.size() != 4) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_simple_cond_jump\n");
        return;
    }  

    int flag = (words[0] == "if");
    string labelName = words[3];

    unordered_map<string, int > mp = varType[func_name];
    string regName = regAlloc->getRegName(words[1]);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "varname = " << words[1] << " , regname = " << regName << endl;
        cout << "type of value stored in variable = " << mp[words[1]] << endl;
    }

    if(mp[words[1]] == BOOL_ASSIGN_EQ) {
        if(flag) fprintf(of,"\tje %s\n",str_to_char(labelName));
        else fprintf(of,"\tjne %s\n",str_to_char(labelName));
    }
    else if(mp[words[1]] == BOOL_ASSIGN_NEQ) {
        if(!flag) fprintf(of,"\tje %s\n",str_to_char(labelName));
        else fprintf(of,"\tjne %s\n",str_to_char(labelName));        
    }
    else if(mp[words[1]] == BOOL_ASSIGN_LT) {
        if(flag) fprintf(of,"\tjl %s\n",str_to_char(labelName));
        else fprintf(of,"\tjge %s\n",str_to_char(labelName));        
    }    
    else if(mp[words[1]] == BOOL_ASSIGN_LTE) {
        if(flag) fprintf(of,"\tjle %s\n",str_to_char(labelName));
        else fprintf(of,"\tjg %s\n",str_to_char(labelName));        
    } 
    else if(mp[words[1]] == BOOL_ASSIGN_GT) {
        if(flag) fprintf(of,"\tjg %s\n",str_to_char(labelName));
        else fprintf(of,"\tjle %s\n",str_to_char(labelName));        
    }    
    else if(mp[words[1]] == BOOL_ASSIGN_GTE) {
        if(flag) fprintf(of,"\tjge %s\n",str_to_char(labelName));
        else fprintf(of,"\tjl %s\n",str_to_char(labelName));        
    }       
    else {
        fprintf(of,"\tcmpl%s, $0\n",str_to_char(regName));
        if(flag) fprintf(of,"\tje %s\n",str_to_char(labelName));
        else fprintf(of,"\tjne %s\n",str_to_char(labelName));
    }
    return;
}

// generates x86 code for conditional jump statements (if i <= x goto .L1) 
void gen_x86_cond_jmp(vector<string> words, FILE* of, int type) {
    if(words.size() != 6) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_cond_jmp\n");
        return;
    }

    // get the src variable and its register
    string varSrc = words[1];
    string regSrc = regAlloc->getRegName(varSrc);

    char* regname1 = str_to_char(regSrc);

    // get the dest variable and its register
    string varDest = words[3];

    // in case of immediate value
    if(varDest[0] >= '0' && varDest[0] <='9') {
        fprintf(of,"\tcmpl %s, $%s\n",regname1, str_to_char(varDest));
    }
    else {
        string regDest = regAlloc->getRegName(varDest);
        char* regname2 = str_to_char(regDest);

        if(regSrc[0] == '-' && regDest[0] == '-') {
            string tempReg = regAlloc->allocateReg(LOCAL_VAL);
            fprintf(of,"\tmovl %s, %s\n",str_to_char(regSrc),str_to_char(tempReg));
            fprintf(of,"\tcmpl %s, %s\n",str_to_char(tempReg),regname2);
        }

        fprintf(of,"\tcmpl %s, %s\n",regname1,regname2);
    }


    // get the label to which jump will happen
    string label = words[5];
    char* labelName = str_to_char(label);

    switch (type) {
        case COND_JMP_LT: {
            fprintf(of,"\tjl %s\n",labelName);
            break;
        }

        case COND_JMP_GT: {
            fprintf(of,"\tjg %s\n",labelName);
            break;
        }

        case COND_JMP_EQ: {
            fprintf(of,"\tje %s\n",labelName);
            break;
        }

        case COND_JMP_LTE: {
            fprintf(of,"\tjle %s\n",labelName);
            break;
        }

        case COND_JMP_GTE: {
            fprintf(of,"\tjge %s\n",labelName);
            break;
        }

        case COND_JMP_NEQ: {
            fprintf(of,"\tjne %s\n",labelName);
            break;
        }

        default: {
            printf("[x86_64 ERROR]: Unknown conditional jump statement encountered\n");
            break;
        }
    }
}

// generated x86 code for semi-assign statements (x = y + 1)
void gen_x86_semi_assign(vector<string> words, FILE* of, int type) {
    if(words.size() != 5) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_semi_assign\n");
        return;
    }

    // get the src variable and its register
    string varSrc = words[2];
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Source Variable: " << varSrc << endl;
    string regSrc = regAlloc->getRegName(varSrc);   
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Source Register: " << regSrc << endl;

    // find a new register to move the src variable into before comparison
    string newReg = regAlloc->allocateReg(LOCAL_VAL);
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New Register: " << newReg << endl;

    char* regname1 = str_to_char(regSrc);
    char* regname2 = str_to_char(newReg);
    fprintf(of,"\tmovl  %s, %s\n",regname1,regname2);

    // get the immediate value
    int imm = stoi(words[4]);

    // set the hashmap for register name and variable name in case of temp variable
    if(words[0][0] == '$') {
        regAlloc->setRTV(newReg,words[0]);
        regAlloc->setVTR(newReg,words[0]);
    }

    // set the value stored in the register
    // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Value of src reg: " << regAlloc->getRegVal(regSrc) << endl;
    // regAlloc->setRegVal(newReg,regAlloc->getRegVal(regSrc));
    // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Current value of new reg: " << regAlloc->getRegVal(newReg) << endl;

    switch (type)
    {
        case SEMI_ADD: {
            fprintf(of,"\taddl $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)+imm);
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value of new reg: " << regAlloc->getRegVal(newReg) << endl;
            break;
        }
        case SEMI_SUB: {
            fprintf(of,"\tsubl $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)-imm);
            break;
        }
        case SEMI_MUL: {
            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\timull %s, %s\n",regname3,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)*imm);
            break;
        }
        case SEMI_DIV: {
            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\tidiv %s\n",regname3);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)/imm);
            break;
        }
        case SEMI_FLOOR_DIV: {
            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\tidiv %s\n",regname3);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)/imm);
            break;
        }
        case SEMI_POWER: {
            // call a function to compute exponentiation
            gen_x86_exponent(regSrc,newReg,of,imm);
            // regAlloc->setRegVal(newReg,pow(regAlloc->getRegVal(newReg),imm));
            break;
        }
        case SEMI_REM: {
            // using the idiv operator here, the remainder will be stored in the rdx register

            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\tidiv %s\n",regname3);
            fprintf(of,"\tmovl %%rdx, %s\n",regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)%imm);
            break;
        }
        case SEMI_BIT_AND: {
            fprintf(of,"\tand $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)&imm);
            break;
        }
        case SEMI_BIT_OR: {
            fprintf(of,"\tor $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)|imm);
            break;
        }
        case SEMI_BIT_XOR: {
            fprintf(of,"\txor $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)^imm);
            break;
        }
        case SEMI_LEFT_SHIFT: {
            fprintf(of,"\tshl $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)<<imm);
            break;
        }
        case SEMI_RGHT_SHIFT: {
            fprintf(of,"\tshr $%d, %s\n",imm,regname2);
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)>>imm);
            break;
        }    
        case SEMI_AND: {
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)&&imm);
            break;
        }    
        case SEMI_OR: {
            // regAlloc->setRegVal(newReg,regAlloc->getRegVal(newReg)||imm);
            break;
        }
        default:
            printf("[x86_64 ERROR]: Unknown conditional jump statement encountered\n");
            break;
    }

    // now we need to differentiate between temp = x + 1, and y = x + 1
    // if y = x + 1
    if(words[0][0] != '$') {
        // if(DEBUG_X86_OUTSIDE_VERBOSE) 
        string preVar = words[0];
        string preReg = regAlloc->getRegName(preVar);
        fprintf(of,"\tmovl %s, %s\n",regname2, str_to_char(preReg));
        
        // update the value of this register
        // regAlloc->setRegVal(preReg,regAlloc->getRegVal(newReg));
    }

}

// generates x86 code for power exponentiation statements
void gen_x86_exponent(string regSrc, string newReg, FILE* of, int exponent) {
    if(exponent == 0) return;
    else if(exponent == 1) {
        fprintf(of,"\timull %s, %s\n",str_to_char(newReg),str_to_char(regSrc));
        return;
    }
    else if(exponent%2 == 0) {
        fprintf(of,"\timull %s, %s\n",str_to_char(newReg),str_to_char(newReg));
        gen_x86_exponent(regSrc,newReg,of,exponent/2);
    }
    else {
        fprintf(of,"\timull %s, %s\n",str_to_char(newReg),str_to_char(newReg));
        gen_x86_exponent(regSrc,newReg,of, ((exponent-1)/2) );
    }
}

// generates x86 code for self assignment statements like (x = x + 1)
void gen_x86_self_assign(vector<string> words, FILE* of, int type) {
    if(words.size() != 5) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_self_assign\n");
        return;
    }

    string varName = words[0];
    string regName = regAlloc->getRegName(varName);
    char* regname = str_to_char(regName);
    int imm = stoi(words[4]);

    switch (type)
    {
        case IMM_ADD: {
            fprintf(of,"\taddl $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)+imm);
            break;
        }
        case IMM_SUB: {
            fprintf(of,"\tsubl $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)-imm);
            break;
        }
        case IMM_MUL: {
            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\timull %s, %s\n",regname3,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)*imm);
            break;
        }
        case IMM_DIV: {
            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\tidiv %s\n",regname3);
            fprintf(of,"\tmovl %%eax, %s\n",regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)/imm);
            break;
        }
        case IMM_FLOOR_DIV: {
            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\tidiv %s\n",regname3);
            fprintf(of,"\tmovl %%eax, %s\n",regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)/imm);
            break;
        }
        case IMM_POWER: {
            // call a function to compute exponentiation
            gen_x86_exponent(regName,regName,of,imm);
            // regAlloc->setRegVal(regName,pow(regAlloc->getRegVal(regName),imm));
            break;
        }
        case IMM_REM: {
            // using the idiv operator here, the remainder will be stored in the rdx register

            // get another free register to store the imm value
            string destReg = regAlloc->allocateReg(LOCAL_VAL);
            char* regname3 = str_to_char(destReg);
            fprintf(of,"\tmovl  $%d, %s\n",imm,regname3);
            fprintf(of,"\tidiv %s\n",regname3);
            fprintf(of,"\tmovl %%edx, %s\n",regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)%imm);
            break;
        }
        case IMM_BIT_AND: {
            fprintf(of,"\tand $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)&imm);
            break;
        }
        case IMM_BIT_OR: {
            fprintf(of,"\tor $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)|imm);
            break;
        }
        case IMM_BIT_XOR: {
            fprintf(of,"\txor $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)^imm);
            break;
        }
        case IMM_LEFT_SHIFT: {
            fprintf(of,"\tshl $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)<<imm);
            break;
        }
        case IMM_RGHT_SHIFT: {
            fprintf(of,"\tshr $%d, %s\n",imm,regname);
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)>>imm);
            break;
        }    
        case IMM_AND: {
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)&&imm);
            break;
        }    
        case IMM_OR: {
            // regAlloc->setRegVal(regName,regAlloc->getRegVal(regName)||imm);
            break;
        }
        default:
            printf("[x86_64 ERROR]: Unknown conditional jump statement encountered\n");
            break;
    }    
}

// generates x86 code for binary operation statements like ( x = y + z)
void gen_x86_bin_op(vector<string> words, FILE* of, int type) {
    if(words.size() != 5) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_self_assign\n");
        return;
    }

    string var1 = words[0];
    string var2 = words[2];
    string var3 = words[4];
    string reg1,reg2,reg3,tempReg,tempReg2;

    reg2 = regAlloc->getRegName(var2);
    reg3 = regAlloc->getRegName(var3);

    if(regAlloc->getRegName(var2) == "NULL" && isArray(var2) == true) {
        string idxName = getArrayIdx(var2);
        string idxReg = regAlloc->getRegName(idxName);
        string var2Base = getArrayBase(var2);
        string var2BaseReg = regAlloc->getRegName(var2Base);
        tempReg = regAlloc->allocateReg(LOCAL_VAL);
        tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
        fprintf(of,"\tmovl %s, %s\n",str_to_char(idxReg),str_to_char(tempReg));
        fprintf(of,"\tcltq\n");
        string tempReg_64 = convert_to_64_bit(tempReg);
        string tempReg2_64 = convert_to_64_bit(tempReg2);
        fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
        fprintf(of,"\tmovl %s, %s\n",str_to_char(var2BaseReg),str_to_char(tempReg));
        fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
        reg2 = tempReg;
    }

    if(regAlloc->getRegName(var3) == "NULL" && isArray(var3) == true) {
        string idxName = getArrayIdx(var3);
        string idxReg = regAlloc->getRegName(idxName);
        string var3Base = getArrayBase(var3);
        string var3BaseReg = regAlloc->getRegName(var3Base);
        tempReg = regAlloc->allocateReg(LOCAL_VAL);
        tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
        fprintf(of,"\tmovl %s, %s\n",str_to_char(idxReg),str_to_char(tempReg));
        fprintf(of,"\tcltq\n");
        string tempReg_64 = convert_to_64_bit(tempReg);
        string tempReg2_64 = convert_to_64_bit(tempReg2);
        fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
        fprintf(of,"\tmovl %s, %s\n",str_to_char(var3BaseReg),str_to_char(tempReg));
        fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
        reg3 = tempReg;
    }


    if(words[0][0] == '$') {
        reg1 = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(reg1,var1);
        regAlloc->setVTR(reg1,var1);
    }
    else reg1 = regAlloc->getRegName(var1);


    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "var1 = " << var1 << "  reg1 = " << reg1 << endl;
        cout << "var2 = " << var2 << "  reg2 = " << reg2 << endl;
        cout << "var3 = " << var3 << "  reg3 = " << reg3 << endl;
    }

    switch (type)
    {
        case BIN_ADD: {
            if(var1 == var2) {
                fprintf(of,"\taddl %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg3)+regAlloc->getRegVal(reg1));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\taddl %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg3)+regAlloc->getRegVal(reg2));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_SUB: {
            if(var1 == var2) {
                fprintf(of,"\tsubl %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)-regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tsubl %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)-regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_MUL: {
            if(var1 == var2) {
                fprintf(of,"\timull %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)*regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\timull %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)*regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_DIV: {
             if(var1 == var2) {
                fprintf(of,"\tidiv %s\n",str_to_char(reg3));
                if(reg1 != "%eax") fprintf(of,"\tmovl %%eax, %s\n",str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)/regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tidiv %s\n",str_to_char(reg3));
                if(reg1 != "%rax") fprintf(of,"\tmovl %%eax, %s\n",str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)/regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_FLOOR_DIV: {
             if(var1 == var2) {
                fprintf(of,"\tidiv %s\n",str_to_char(reg3));
                if(reg1 != "%rax") fprintf(of,"\tmovl %%eax, %s\n",str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)/regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tidiv %s\n",str_to_char(reg3));
                if(reg1 != "%rax") fprintf(of,"\tmovl %%eax, %s\n",str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)/regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_POWER: {
            // // call a function to compute exponentiation
            // gen_x86_exponent(regName,regName,of,imm);
            // // regAlloc->setRegVal(regName,pow(regAlloc->getRegVal(regName),imm));
            break;
        }
        case BIN_REM: {
             if(var1 == var2) {
                fprintf(of,"\tidiv %s\n",str_to_char(reg3));
                if(reg1 != "%rdx") fprintf(of,"\tmovl %%rdx, %s\n",str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)%regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tidiv %s\n",str_to_char(reg3));
                if(reg1 != "%rdx") fprintf(of,"\tmovl %%rdx, %s\n",str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)%regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_BIT_AND: {
            if(var1 == var2) {
                fprintf(of,"\tand %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)&regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tand %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)&regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_BIT_OR: {
            if(var1 == var2) {
                fprintf(of,"\tor %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)|regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tor %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)|regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_BIT_XOR: {
            if(var1 == var2) {
                fprintf(of,"\txor %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)^regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\txor %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)^regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_LEFT_SHIFT: {
            if(var1 == var2) {
                fprintf(of,"\tshl %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)<<regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tshl %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)<<regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        case BIN_RGHT_SHIFT: {
            if(var1 == var2) {
                fprintf(of,"\tshr %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg1)>>regAlloc->getRegVal(reg3));
            }
            else {
                fprintf(of,"\tmovl %s, %s\n",str_to_char(reg2),str_to_char(reg1));
                fprintf(of,"\tshr %s, %s\n",str_to_char(reg3),str_to_char(reg1));
                // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)>>regAlloc->getRegVal(reg3));
            }
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break; 
        }
        case BIN_AND: {
            // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)&&regAlloc->getRegVal(reg3));
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }    
        case BIN_OR: {
            // regAlloc->setRegVal(reg1,regAlloc->getRegVal(reg2)||regAlloc->getRegVal(reg3));
            // if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "New value in " << var1 << " is " << regAlloc->getRegVal(reg1) << endl;
            break;
        }
        default:
            printf("[x86_64 ERROR]: Unknown conditional jump statement encountered\n");
            break;
    }

}

// generates x86 code for parameter push statemetns like (param t1)
void gen_x86_param_push(vector<string> words, FILE* of) {
    string paramName = words[1];

    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "param encountered = " << paramName << endl;

    // get the type of value stored in the param
    unordered_map<string,int> m = varType[func_name];
    int type = m[paramName];
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "type of value stored in param = " << type << endl;

    if(type == TYPE_STR_LITERAL) {
        string destReg = regAlloc->allocateReg(FUNC_ARG, 1);
        string srcReg = str_to_label[paramName] + "(%rip)";
        
        if(DEBUG_X86_OUTSIDE_VERBOSE) {
            cout << "String Label = " << str_to_label[paramName] << endl;
            cout << "Source Reg = " << srcReg << endl;
            cout << "Dest Reg = " << destReg << endl;
        }
        fprintf(of,"\tleaq  %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
    }
    else {

        if(isPrintParam.find(paramName) != isPrintParam.end() && isPrintParam[paramName] == 1) {
            string destReg = regAlloc->allocateReg(FUNC_ARG,1);
            string srcReg = str_to_label[paramName] + "(%rip)";

            if(DEBUG_X86_OUTSIDE_VERBOSE) {
                cout << "String Label = " << str_to_label[paramName] << endl;
                cout << "Source Reg = " << srcReg << endl;
                cout << "Dest Reg = " << destReg << endl;
            }
            fprintf(of,"\tleaq  %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
        }

        string srcReg;

        // if the param is an immediate value
        if(paramName[0] <= '9' && paramName[0] >= '0') srcReg = "$" + paramName;
        // if the param is an array indexed value
        else if(regAlloc->getRegName(paramName) == "NULL" && isArray(paramName) == true) {
            string idxName = getArrayIdx(paramName);
            string idxReg = regAlloc->getRegName(idxName);
            string var2Base = getArrayBase(paramName);
            string var2BaseReg = regAlloc->getRegName(var2Base);
            string tempReg = regAlloc->allocateReg(LOCAL_VAL);
            string tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
            fprintf(of,"\tmovl %s, %s\n",str_to_char(idxReg),str_to_char(tempReg));
            fprintf(of,"\tcltq\n");
            string tempReg_64 = convert_to_64_bit(tempReg);
            string tempReg2_64 = convert_to_64_bit(tempReg2);
            fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
            fprintf(of,"\tmovl %s, %s\n",str_to_char(var2BaseReg),str_to_char(tempReg));
            fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
            srcReg = tempReg;
        }
        else srcReg = regAlloc->getRegName(paramName);


        string destReg = regAlloc->allocateReg(FUNC_ARG);
        if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "dest Reg = " << destReg << endl;
        if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "src Reg = " << srcReg << endl;
        fprintf(of,"\tmovl %s, %s\n",str_to_char(srcReg),str_to_char(destReg));
    }

}

// generates x86 code for return value push statements like (paramret x)
void gen_x86_ret_val_push(vector<string> words, FILE* of) {
    string paramName = words[1];
    string regName;
    
    // if the return value is an immediate value
    if(paramName[0] <= '9' && paramName[0] >= '0') regName = "$" + paramName;
        // if the param is an array indexed value
    else if(regAlloc->getRegName(paramName) == "NULL" && isArray(paramName) == true) {
            string idxName = getArrayIdx(paramName);
            string idxReg = regAlloc->getRegName(idxName);
            string var2Base = getArrayBase(paramName);
            string var2BaseReg = regAlloc->getRegName(var2Base);
            string tempReg = regAlloc->allocateReg(LOCAL_VAL);
            string tempReg2 = regAlloc->allocateReg(LOCAL_VAL);
            fprintf(of,"\tmovl %s, %s\n",str_to_char(idxReg),str_to_char(tempReg));
            fprintf(of,"\tcltq\n");
            string tempReg_64 = convert_to_64_bit(tempReg);
            string tempReg2_64 = convert_to_64_bit(tempReg2);
            fprintf(of,"\tleaq 0(,%s,4), %s\n",str_to_char(tempReg_64),str_to_char(tempReg2_64));
            fprintf(of,"\tmovl %s, %s\n",str_to_char(var2BaseReg),str_to_char(tempReg));
            fprintf(of,"\taddl %s, %s\n", str_to_char(tempReg2),str_to_char(tempReg));
            regName = tempReg;
    }
    else regName = regAlloc->getRegName(paramName);

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "param encountered = " << paramName << endl;
        cout << "register = " << regName << endl;
    }

    fprintf(of,"\tmovl %s, %%eax\n",str_to_char(regName));

}

// generates x86 code to get parameters/return values from popparam statements
void gen_x86_popparam(vector<string> words, FILE* of) {
    if(words.size() != 3) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_popparam\n");
        return;
    }

    string varName = words[0];
    string regName;
    if(varName[0] == '$') {
        regName = regAlloc->allocateReg(LOCAL_VAL);
        regAlloc->setRTV(regName,varName);
        regAlloc->setVTR(regName,varName);
    }
    else regName = regAlloc->getRegName(varName,0);

    if(regName == "NULL") {
        offset_ctr += 4;
        regName = "-" + to_string(offset_ctr) + "(%rbp)";
        regAlloc->setRTV(regName,varName);
        regAlloc->setVTR(regName,varName);
    }

    if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "Src Var = "  << varName << "  Src REg = " << regName << endl;
    }

    // check if popparam is for return value
    if(isReturnParam.find(varName) != isReturnParam.end() && isReturnParam[varName] == 1) {
        if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "return value being popped\n";
        fprintf(of,"\tmovl %%eax, %s\n",str_to_char(regName));
    }
    else {
        param_ctr++;
        string paramReg = regAlloc->getFuncArgs(param_ctr);
        fprintf(of,"\tmovl %s, %s\n",str_to_char(paramReg),str_to_char(regName));
        if(DEBUG_X86_OUTSIDE_VERBOSE) {
        cout << "Dest Reg = " << paramReg << endl;
        }
    }

}

// generates x86 code for stackpointer inc statements
void gen_x86_stackpointer_inc(FILE* of) {
    return;
}

// generates x86 code for stackpointer dec statements
void gen_x86_stackpointer_dec(FILE* of) {
    regAlloc->flushRegs(FUNC_ARG);
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Function argument registers flushed\n";
    regAlloc->flushRegs(FUNC_RTN);
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Function return value registers flushed\n";
    return;
}

// generates x86 code for print call statements like (call print,1)
void gen_x86_print_call(FILE* of) {
    // now set return value to zero, should get %rax from register allocation
    string retReg = regAlloc->allocateReg(FUNC_RTN);
    fprintf(of,"\tmovl $0, %s\n",str_to_char(retReg));
    // regAlloc->setRegVal(retReg,0);

    fprintf(of,"\tcall  printf@PLT\n");
}

// generated x86 code for function call statements like (call f,n)
void gen_x86_func_call(vector<string> words, FILE* of) {
    if(words.size() != 2) {
        printf("[x86_64 ERROR]: wrong line passed to gen_x86_func_call\n");
        return;
    }
    int pos = words[1].find(',');
    string f = words[1].substr(0,pos);
    fprintf(of,"\tcall  %s\n",str_to_char(f));
}

// generates x86 code for return statements
void gen_x86_return(FILE* of) {
    fprintf(of,"\tjmp .LFX%d\n",LFX_ctr);
}

// generates x86 code for function epilogue (concluding part) , should be passed the "endfuc" statement
void gen_x86_func_epilogue(FILE* of) {
    fprintf(of,".LFX%d:\n",LFX_ctr++);
    if(func_name == "main") fprintf(of,"\tmovq $0, %%rax\n");
    else fprintf(of,"\tleave\n");
    if(func_name == "main") fprintf(of,"\tpopq \t%%rbp\n");
    fprintf(of,"\t.cfi_def_cfa 7, 8\n\tret\n\t.cfi_endproc\n");
    fprintf(of,".LFE%d:\n",LFE_ctr++);
    fprintf(of,"\t.size  %s, .-%s\n",str_to_char(func_name),str_to_char(func_name));

    regAlloc->flushRegs(LOCAL_VAL);
    if(DEBUG_X86_OUTSIDE_VERBOSE) cout << "Local registers flushed out\n";
}


/*********************************** X86_64 GENERATION FUNCTIONS *********************************************************/


/*********************************** FUNCTION DEFINITIONS *********************************************************/


#endif // GEN_X86_CPP
