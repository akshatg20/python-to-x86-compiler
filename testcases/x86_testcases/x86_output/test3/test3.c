#include <stdio.h>

int factorial(int x) {
    if(x <= 1) return 1;
    else return (x * factorial(x-1));
}

void main2() {
    int x = 10;
    for(int i=0; i < (x+1); i++) {
        int y = factorial(i);
        printf("Value of factorial of ");
        printf("%d", i);
        printf(" is equal to ");
        printf("%d", y);
        printf("\n");
    }
    return;
}

int main() {
    main2();
    return 0;
}
