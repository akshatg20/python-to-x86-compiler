#include <stdio.h>

// Function with more than 6 parameters
int calculate_sum(int a, int b, int c, int d, int e, int f, int g) {
    return a + b + c + d + e + f + g;
}

void main2() {
    // Array assignments and indexing
    int array[7] = {1, 2, 3, 4, 5, 6, 7};
    printf("The value of 3rd number in array is: ");
    printf("%d", array[2]);
    printf("\n");
    array[2] = 10;
    printf("New value of 3rd number in array is: ");
    printf("%d", array[2]);
    printf("\n");

    // Call to function with more than 6 parameters
    int sum_fixed = calculate_sum(0, 1, 2, 3, 4, 5, 6);
    printf("Sum of first 7 whole numbers is: ");
    printf("%d", sum_fixed);
    printf("\n");

    // Call to function with more than 6 parameters
    int sum = calculate_sum(array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
    printf("Sum of array is: ");
    printf("%d", sum);
    printf("\n");

    return;
}

int main() {
    main2();
    return 0;
}
