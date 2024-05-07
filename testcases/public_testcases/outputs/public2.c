#include <stdio.h>

// Global array of floats
float data[] = {-2.3, 3.14, 0.9, 11, -9.1};
int size = sizeof(data) / sizeof(data[0]);

// Function to compute the minimum value in the array
float compute_min() {
    float min_value = data[0];  // Initialize with the first element
    for (int i = 1; i < size; i++) {
        if (data[i] < min_value) {
            min_value = data[i];
        }
    }
    return min_value;
}

// Function to compute the average of the array
float compute_avg() {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum / size;
}

// Main function to run the program
int main() {
    float min_value = compute_min();
    printf("Minimum value: %f\n", min_value);

    float avg_value = compute_avg();
    printf("Average value: %f\n", avg_value);

    return 0;
}