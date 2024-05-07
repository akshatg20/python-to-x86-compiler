#include <stdio.h>

// Define structures for Rectangle and Circle
typedef struct {
    int width;
    int height;
} Rectangle;

typedef struct {
    int radius;
} Circle;

// Function prototypes
int rectangle_area(Rectangle rect);
float circle_area(Circle circle);

int main() {
    // Creating instances of Rectangle and Circle
    Rectangle rect = {5, 4};
    Circle circle = {3};

    // Calculating areas and printing
    printf("Area of Rectangle: %d\n", rectangle_area(rect));
    printf("Area of Circle: %f\n", circle_area(circle));

    return 0;
}

// Function definitions
int rectangle_area(Rectangle rect) {
    return rect.width * rect.height;
}

float circle_area(Circle circle) {
    return 3.14 * circle.radius * circle.radius;
}
