#include <stdio.h>

void bubbleSort(int array[], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        int swapped = 0;
        for (j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int data[] = {-2, 45, 0, 11, -9};
    int size = sizeof(data) / sizeof(data[0]);
    
    bubbleSort(data, size);
    
    printf("Sorted Array in Ascending Order:\n");
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\n", data[i]);
    }
    
    return 0;
}
