#ifndef GEN_X86_CPP
#define GEN_X86_CPP

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#ifndef GEN_X86_HPP
#include "gen_x86.hpp"
#endif
using namespace std;

/********************** ASSUMPTIONS FOR THE CONSTRUCTION OF RUNTIME ENVIRONMENT ***********************************/

// Write any assumptions that you take in the comment below
/*

A) I have assumed that the runtime environment has been initialized before-hand, at which stage of the compilation toolchain, i am unsure.

B) Function Call
  Before executing a function, a program pushes all of the parameters for the function onto the stack in the reverse order that they are documented. 
  Then the program issues a call instruction indicating which function it wishes to start. The call instruction does two things:
      -> First it pushes the address of the next instruction, which is the return address, onto the stack.
      -> Then, it modifies the instruction pointer %rip to point to the start of the function.


    Argument N
    ...
    Argument 2
    Argument 1
    Return address <--- (%rsp)

C) Function Setup
    During the setup, the following two instructions are carried out immediately:
        pushl %rbp
        movl %rsp %rbp
    
    Argument N     <--- N*4+4(%rbp)
    ... 
    Argument 2     <--- 16 (%rbp)
    Argument 1     <--- 12(%rbp)
    Return address <--- 4(%rbp)
    Old %rbp       <--- (%rsp) and (%rbp)

D) Saving Registers
    We need to push all the callee-save registers by convention onto the stack. By convention, registers %rax, %rdx, %rcx are classified as 
    caller-save registers, and %rbx, %rsi, and %rdi are classified as callee-save registers. The caller-save registers mean that the caller 
    function is responsible saving these register values because the callee is free to override these register values. On the other hand, 
    the callee-save registers mean that the callee function must save those registers values by pushing them onto the stack before overwritting them, 
    and restore them before the returning because the caller may need these values for its future computations.
*/

/********************** ASSUMPTIONS FOR THE CONSTRUCTION OF RUNTIME ENVIRONMENT ***********************************/

// All required external source files are already included to this code.
// Declare any external variables you want to use here with an "extern" keyword.

RunTimeEnv* Env;          

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

// All variables that you want to declare should go here.

/*********************************** DATA STORAGE ELEMENTS ********************************************************/

/*********************************** FUNCTION DEFINITIONS *********************************************************/

// All functions that you have declared should go here.

void RunTimeEnv::callFunction(vector<int> intParams, vector<float> floatParams, int returnAddr, int funcAddr) {
    // first create a new activation record frame
    ActivationRecord ar;

    // push params and return address
    ar.intParams = intParams;
    ar.floatParams = floatParams;
    ar.returnAddr = returnAddr;

    // set the stack pointer to the return address (top of the frame)
    Env->stackPtr = returnAddr;

    // set the instruction pointer
    Env->instrPtr = funcAddr;

    // push the activation record frame onto the stack
    Env->controlStack.push(ar);

}

void RunTimeEnv::setUpFunction() {
    // get the activation frame at the top
    ActivationRecord* ar = &Env->controlStack.top();

    // save the current base pointer
    ar->prevBasePointer = Env->basePtr;

    // set the current base pointer
    Env->basePtr = Env->stackPtr;
}

void RunTimeEnv::saveRegs(vector<int> savedVarInt, vector<float> savedVarFloat) {
    // get the activation frame at the top
    ActivationRecord* ar = &Env->controlStack.top();

    ar->savedVarInt = savedVarInt;
    ar->savedVarFloat = savedVarFloat;
}

void RunTimeEnv::cleanupFunction(int rvInt, float rvFloat) {
    // get the activation frame at the top
    ActivationRecord* ar = &Env->controlStack.top();

    // save the return values
    Env->rvInt = rvInt;
    Env->rvFloat = rvFloat;

    // yet to complete
}


/*********************************** FUNCTION DEFINITIONS *********************************************************/


#endif // GEN_X86_CPP
