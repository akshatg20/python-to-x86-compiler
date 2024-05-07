#include <stdio.h>
#include <stdbool.h>

// Function to perform Bubble Sort
void bubbleSort(int array[], int size) {
    int i, j, temp;
    bool swapped;
    for (i = 0; i < size; i++) {
        swapped = false;
        for (j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Main function to run the program
int main() {
    int data[] = {-2, 45, 0, 11, -9};
    int size = sizeof(data) / sizeof(data[0]);

    bubbleSort(data, size);

    printf("Sorted Array in Ascending Order:\n");
    for (int i = 0; i < size; i++) {
        printf("%d\n", data[i]);
    }

    return 0;
}