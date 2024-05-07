#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define ShiftReduceParser structure
typedef struct {
    const char* srname;
} ShiftReduceParser;

// Define LR0Parser structure
typedef struct {
    ShiftReduceParser super;
    const char* lr0name;
} LR0Parser;

// Define CLRParser structure
typedef struct {
    ShiftReduceParser super;
    const char* clrname;
} CLRParser;

// Define LALRParser structure
typedef struct {
    CLRParser super;
    const char* lalrname;
} LALRParser;

// Function to print names
void print_name(LALRParser* obj) {
    printf("SLR name:\n");
    printf("%s\n", obj->super.srname);
    printf("CLR name:\n");
    printf("%s\n", obj->super.clrname);
    printf("LALR name:\n");
    printf("%s\n", obj->lalrname);
}

int main() {
    // Create LALRParser object
    LALRParser obj;
    obj.super.super.srname = "Shift-Reduce";
    obj.super.clrname = "CLR";
    obj.lalrname = "LALR";

    // Print names
    print_name(&obj);

    return 0;
}
