#include <stdio.h>

int factorial(int x) {
    if(x <= 1) return 1;
    else if(x == 2) return 2;
    else if(x == 3) return 6;
    else if(x < 10) {
        int val = 1;
        for(int i = 1; i <= x; i++) val = (val * i);
        return val;
    }
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
