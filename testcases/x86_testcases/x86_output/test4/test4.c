#include <stdio.h>

int array_sum(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + array[i];
    }
    return sum;
}

void main2() {
    int array[] = {1, 2, 3, 4, 7, 20, -4, 5};
    int length = 8;
    int sum = array_sum(array, length);
    printf("The array is given by");
    printf("\n");
    for (int i = 0; i < length; i++) {
        printf("%d", array[i]);
        printf("\n");
    }
    printf("The sum of array elements is ");
    printf("%d", sum);
    printf("\n");
    return;
}

int main() {
    main2();
    return 0;
}
