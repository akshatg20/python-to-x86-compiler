#include <stdio.h>

// Commands to run the generated x86
// gcc -c test1.s -o test1.o
// gcc test1.o -o test1
// ./test1

// Commands to generate official x86 of gcc -> Works only on Linux System (Mac has different register allocation conventions)
// gcc -E test1.c -o test1.i
// gcc -S test1.i -o test1.s

void main2() {
    int x = 5;
    for(int i=0; i < (x+1); i++) {
        // int y = factorial_devansh(i);
        printf("Value of factorial of ");
        printf("%d", i);
        printf(" can be found.\n");
    }    
    return;
}

int main() {
    main2();
    return 0;
}
