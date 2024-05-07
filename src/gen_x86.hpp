#ifndef GEN_X86_HPP
#define GEN_X86_HPP

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
using namespace std;

// used for 3AC lexer

#define UNARY_OP_ASSIGN 1              //  x = op y
#define BINARY_OP_ASSIGN 2             //  x = y op z
#define UNCOND_JMP 3                   //  goto L
#define COND_JMP 4                     //  if x goto L
#define COND_JMP_OP 5                  //  if x op y goto L
#define PARAM_PUSH 6                   //  param x
#define FUNC_CALL 7                    //  call f,n
#define FUNC_RETURN 8                  //  return
#define FUNC_BEGIN 9                   //  beginfunc
#define FUNC_END 10                    //  endfunc
#define STACK_PTR_INC 11               //  stackpointer +xxx
#define FUNC_CALL_ASSIGN 12            //  y = call p,n
#define RGHT_IDX_ASSIGN 13             //  y = x[i]
#define LEFT_IDX_ASSIGN 14             //  x[i] = y
#define ADDRESS_ASSIGN 15              //  x = &y
#define PTR_ASSIGN_LEFT 16             //  *x = y
#define PTR_ASSIGN_RGHT 17             //  x = *y      
#define LABEL 18                       //  .LFB0:
#define FUNC_RETURN_VAL 19             //  return x
#define STACK_PTR_DEC 20               //  stackpointer -yyy
#define UNARY_ADD_ASSIGN 21            //  x = +y
#define UNARY_SUB_ASSIGN 22            //  x = -y
#define UNARY_NOT_ASSIGN 23            //  x = !y
#define UNARY_BIT_NOT_ASSIGN 24        //  x = ~y
#define PARAM_ASSIGN 25                //  x = popparam
#define BOTH_IDX_ASSIGN 26             //  x[i] = y[i]
#define PTR_ASSIGN_BOTH 27             //  *x = *y
#define COND_JMP_LT 28                 //  if x < y goto L
#define COND_JMP_GT 29                 //  if x > y goto L
#define COND_JMP_EQ 30                 //  if x == y goto L
#define COND_JMP_LTE 31                //  if x <= y goto L
#define COND_JMP_GTE 32                //  if x >= y goto L
#define BIN_ADD 33                     //  x = y + z
#define BIN_SUB 34                     //  x = y - z
#define BIN_MUL 35                     //  x = y * z
#define BIN_DIV 36                     //  x = y / z
#define BIN_FLOOR_DIV 37               //  x = y // z
#define BIN_POWER 38                   //  x = y ** z
#define BIN_BIT_AND 39                 //  x = y & z
#define BIN_BIT_OR 40                  //  x = y | z 
#define BIN_BIT_XOR 41                 //  x = y ^ z 
#define BIN_REM 42                     //  x = y % z 
#define BIN_LEFT_SHIFT 43              //  x = y << z
#define BIN_RGHT_SHIFT 44              //  x = y >> z 
#define BIN_AND 45                     //  x = y && z
#define BIN_OR 46                      //  x = y || z 
#define SIMPLE_ASSIGN 47               //  x = y
#define IMM_ASSIGN 48                  //  x = 3
#define SYMTABLE_ASSIGN 49             //  x = symtable(..)  
#define STRING_ASSIGN 50               //  x = "hello"
#define FUNC_LABEL 51                  //  _Z4mainv:
#define PRINT_CALL 52                  //  call print,3
#define IMM_ADD 53                     //  x = x + 1
#define IMM_SUB 54                     //  x = x - 1
#define IMM_MUL 55                     //  x = x * 1
#define IMM_DIV 56                     //  x = x / 1
#define IMM_FLOOR_DIV 57               //  x = x // 1
#define IMM_POWER 58                   //  x = x ** 1
#define IMM_BIT_AND 59                 //  x = x & 1
#define IMM_BIT_OR 60                  //  x = x | 1 
#define IMM_BIT_XOR 61                 //  x = x ^ 1 
#define IMM_REM 62                     //  x = x % 1 
#define IMM_LEFT_SHIFT 63              //  x = x << 1
#define IMM_RGHT_SHIFT 64              //  x = x >> 1 
#define IMM_AND 65                     //  x = x && 1
#define IMM_OR 66                      //  x = x || 1 
#define SEMI_ADD 67                     //  x = y + 1
#define SEMI_SUB 68                     //  x = y - 1
#define SEMI_MUL 69                     //  x = y * 1
#define SEMI_DIV 70                     //  x = y / 1
#define SEMI_FLOOR_DIV 71               //  x = y // 1
#define SEMI_POWER 72                   //  x = y ** 1
#define SEMI_BIT_AND 73                 //  x = y & 1
#define SEMI_BIT_OR 74                  //  x = y | 1 
#define SEMI_BIT_XOR 75                 //  x = y ^ 1 
#define SEMI_REM 76                     //  x = y % 1 
#define SEMI_LEFT_SHIFT 77              //  x = y << 1
#define SEMI_RGHT_SHIFT 78              //  x = y >> 1 
#define SEMI_AND 79                     //  x = y && 1
#define SEMI_OR 80                      //  x = y || 1 
#define EMPTY_LINE 81                   // empty line
#define COND_JMP_NEQ 82                 // if x != y goto L
#define RET_PARAM_PUSH 83               // paramret x
#define ARRAY_ASSIGN 84                 // x = [ 2, 3, 4 , 6 ]
#define BOOL_ASSIGN_NEQ 85              // x = y != z
#define BOOL_ASSIGN_LT 86               // x = y < z
#define BOOL_ASSIGN_GT 87               // x = y > z
#define BOOL_ASSIGN_LTE 88              // x = y <= z
#define BOOL_ASSIGN_GTE 89              // x = y >= z
#define BOOL_ASSIGN_EQ 90               // x = y == z

// used for register allocation, more contexts need to be added
#define FUNC_ARG 0
#define LOCAL_VAL 1
#define FUNC_RTN 2
#define DIV 3
#define LOCAL_VAL2 4

// used to determine the type of value of stores in a variable
#define TYPE_VAR 0
#define TYPE_STR_LITERAL 1
#define TYPE_INT_LITERAL 2
#define TYPE_ARRAY_LITERAL 3

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

// All classes and structures that you want to declare should go here.

/*

NOTES:

  1. Return value stored in %rax register.
  2. The first six integer/pointer parameters stored in RDI, RSI, RDX, RCX, R8, R9; rest all pushed onto the stack in reverse order.
  3. String parameters are passed by reference using above mentioned registers only.
  4. Float parameters are typically passed in SSE registers, specifically the XMM0-XMM7 registers.
  5. When a function is called, the address of the instruction immediately following the call instruction is pushed onto the call stack.
     This address serves as the return address inside the callee's activation record.
  6. Commonly saved registers include rbx, rsp, rbp, r12-r15, and the SSE registers (xmm6-xmm15) in x86-64 architecture.

*/

struct RegisterSet {
  // 64, 32, 16, 8 bits
  int rax, eax, ax, al;              // return value, callee-owned
  int rdi, edi, di, dil;             // 1st arg, callee-owned
  int rsi, esi, si, sil;             // 2nd arg, callee-owned
  int rdx, edx, dx, dl;              // 3rd arg, callee-owned
  int rcx, ecx, cx, cl;              // 4th-arg, callee-owned
  int r8, r8d, r8w, r8b;             // 5th-arg, callee-owned
  int r9, r9d, r9w, r9b;             // 6th-arg, callee-owned
  int r10, r10d, r10w, r10b;         // scratch/temporay, callee-owned
  int r11, r11d, r11w, r11b;         // scratch/temporay, callee-owned
  int rsp, esp, sp, spl;             // stack pointer, caller-owned
  int rbx, ebx, bx, bl;              // local variable, caller-owned  
  int rbp, ebp, bp, bpl;             // local variable, caller-owned 
  int r12, r12d, r12w, r12b;         // local variable, caller-owned
  int r13, r13d, r13w, r13b;         // local variable, caller-owned
  int r14, r14d, r14w, r14b;         // local variable, caller-owned
  int r15, r15d, r15w, r15b;         // local variable, caller-owned
  int rip;                           // instruction pointer
  int eflags;                        // status/condition code bits
  unordered_map<string,int> stc_loc; // maps the values stored in stack at locations like -4(%rbp)

};
typedef struct RegisterSet RegisterSet;

// Definition for doubly linked list node
class Node {
public:
    int key, value;
    Node *prev, *next;
    Node(int k, int v): key(k), value(v), prev(NULL), next(NULL) {}
};

class LRU {
private:
    int cap;
    unordered_map<int, Node*> mp;
    Node *head, *tail;
    unordered_map<int, string> keyToReg;
    void addNode(Node* node);
    void deleteNode(Node* node);

public:
    LRU(int capacity);
    LRU(vector<string> &vec);
    void setRegister(vector<string> regs);
    string getLeastRecentlyUsed();
    void put(string reg);
    void put2(int key, int value);
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


class RegisterAllocation {
private:
    RegisterSet *regs;                            // set of all registers
    LRU* local_var_eviction;                      // This helps in decision for eviction of registers
    unordered_map<string,string> regToVar;        // mapping of register name to name of variable it holds
    unordered_map<string,string> varToReg;        // mapping of variable name to the register it is held in
    unordered_map<string,bool> isRegFilled;       // maps whether a register is in use or not
    string auxiliary_allocateReg(int context, int* flag, int flag_64_bit = 0);

public:
    // constructor
    RegisterAllocation();

    // function to set regToVar hashmap
    void setRTV(string regName, string varName);

    // function to set varToReg hashmap
    void setVTR(string regName, string varName);

    // function to get regName
    string getRegName(string varName, int flag = 1);

    // function to get varName
    string getVarName(string regName);

    // function to set register value
    int setRegVal(string regName, int val);

    // function to get the value stored in register
    int getRegVal(string regName);

    // function to free up registers 
    void flushRegs(int context);

    // function to get function argument registers from popparam
    string getFuncArgs(int paramsLeft);

    // function to allocate registers
    string allocateReg(int context, int flag_64_bit = 0);
};


/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** FUNCTION DECLARATIONS ********************************************************/

// All functions that you want to declare should go here.

int generate_x86(string code_3ac, FILE* of);

/*********************************** FUNCTION DECLARATIONS ********************************************************/

#endif // GEN_X86_HPP
