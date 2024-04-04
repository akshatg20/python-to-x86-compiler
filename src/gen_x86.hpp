#ifndef GEN_X86_HPP
#define GEN_X86_HPP

#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

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

struct ActivationRecord {
  vector<int> intParams;            // integer/pointer parameters
  vector<float> floatParams;        // floating-point parameters
  int returnAddr;                   // address to which function returns to
  ActivationRecord *controlLink;    // pointer to the activation record of the caller
  int prevBasePointer;              // previous address of the base pointer
  vector<int> savedVarInt;          // variables saved from caller, integer
  vector<float> savedVarFloat;      // variables saved from caller, floating
  vector<int> tempVarInt;           // temp values used during the function call, integer
  vector<float> tempVarFloat;       // temp values used during the function call, floating
};
typedef struct ActivationRecord ActivationRecord;

/*********************************** DATA STORAGE STRUCTURES ******************************************************/

/*********************************** FUNCTION DECLARATIONS ********************************************************/

// All functions that you want to declare should go here.

class RunTimeEnv {
private:
  stack<ActivationRecord> controlStack;             // holds the activation frames
  int stackPtr;                                     // points to the top of the stack, stored in %rsp
  int basePtr;                                      // used as a reference to access local variables etc., usually stored in %rbp
  int instrPtr;                                     // points to the address of the next instruction, stored in %rip
  int rvInt;                                        // integer return value from function, stored in %rax
  float rvFloat;                                    // float return value, stored in usually %xmm0-%xmm1

public:
  // Constructor
  RunTimeEnv(int stackPtr = 0x100000, int basePtr = 0x100000, int instrPtr = 0x0, int rvInt = 0, int rvFloat = 0.0) {
      this->stackPtr = stackPtr;
      this->basePtr = basePtr;
      this->instrPtr = instrPtr;
      this->rvInt = rvInt;
      this->rvFloat = rvFloat;
  }

  // function call
  void callFunction(vector<int> intParams, vector<float> floatParams, int returnAddr, int funcAddr);

  // function setup
  void setUpFunction();

  // saving callee-saved registers
  void saveRegs(vector<int> savedVarInt, vector<float> savedVarFloat);

  // function cleanup
  void cleanupFunction(int rvInt = 0, float rvFloat = 0.0);

};

/*********************************** FUNCTION DECLARATIONS ********************************************************/

#endif // GEN_X86_HPP
