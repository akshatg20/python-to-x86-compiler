#include <stdio.h>

// Function to perform binary search on an array
int binarySearch(int array[], int x, int low, int high) {
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (array[mid] == x) {
            return mid;
        } else if (array[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Main function to run the binary search
int main() {
    int array[] = {3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array) / sizeof(array[0]);
    int result = binarySearch(array, 4, 0, size - 1);

    if (result != -1) {
        printf("Element is present at index: %d\n", result);
    } else {
        printf("Element is not present\n");
    }

    return 0;
}