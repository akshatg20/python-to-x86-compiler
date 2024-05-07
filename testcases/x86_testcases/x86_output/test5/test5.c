#include <stdio.h>
#include <stdbool.h>

int add(int x, int y) {
    int ans = x + y;
    return ans;
}

int subtract(int x, int y) {
    int ans = x - y;
    return ans;
}

int multiply(int x, int y) {
    int ans = x * y;
    return ans;
}

int divide(int x, int y) {
    int ans = 0;
    if (y != 0) {
        ans = x / y;
    } else {
        printf("Error: Cannot divide by zero.");
        printf("\n");
    }
    return ans;
}

bool relational(int x, int y) {
    bool ans = (x == y);
    return ans;
}

int assignment(int x, int y) {
    x |= y;
    int ans = x;
    return ans;
}

void main2() {
    int result_add = add(10, 5);
    printf("Result of Addition: ");
    printf("%d", result_add);
    printf("\n");

    int result_subtract = subtract(10, 5);
    printf("Result of Subtraction: ");
    printf("%d", result_subtract);
    printf("\n");

    int result_multiply = multiply(10, 5);
    printf("Result of Multiplication: ");
    printf("%d", result_multiply);
    printf("\n");

    int result_divide = divide(10, 5);
    printf("Result of Division: ");
    printf("%d", result_divide);
    printf("\n");

    bool result_relational = relational(10, 5);
    printf("Result of Relational Operation: ");
    printf("%d", result_relational);
    printf("\n");

    int result_assignment = assignment(10, 5);
    printf("Result of Assignment Operation: ");
    printf("%d", result_assignment);
    printf("\n");

    return;
}

int main() {
    main2();
    return 0;
}
