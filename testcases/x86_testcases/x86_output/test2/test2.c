#include <stdio.h>

void main2() {
    int x = 10;
    for(int i=0; i<(x+1); i++) {
        int val = 1;
        for(int j=0;j<i;j++) val = (val*(j+1));
        printf("Value of factorial of ");
        printf("%d", i);
        printf(" is equal to ");
        printf("%d", val);
        printf("\n");
    }
    return;
}

int main() {
    main2();
    return 0;
}
