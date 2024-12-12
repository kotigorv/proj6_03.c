#include <stdio.h>
#include <math.h>

#define EPSILON 1e-7
#define PI 3.141592653589793

// Function to integrate
double f(double x) {
    return x * cos(x * x);
}

// Left rectangles method
double left_rectangles(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

// Right rectangles method
double right_rectangles(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

// Midpoint rectangles method
double midpoint_rectangles(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += f(a + (i + 0.5) * h);
    }
    return h * sum;
}

// Trapezoidal method
double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return h * sum;
}

// Simpson's method
double simpson(double a, double b, int n) {
    if (n % 2 != 0) n++; // Number of intervals must be even
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            sum += 2 * f(a + i * h);
        }
        else {
            sum += 4 * f(a + i * h);
        }
    }
    return (h / 3) * sum;
}

int main() {
    double a = 0.0;
    double b = PI / 2;
    double exact_value = 0.5 * sin(PI); // Analytical solution

    printf("Analytical solution: %.10f\n", exact_value);

    int n = 1;
    double result = 0.0, prev_result;

    // Left rectangles method
    do {
        prev_result = result;
        result = left_rectangles(a, b, n);
        n *= 2;
    } while (fabs(result - prev_result) > EPSILON);
    printf("Left rectangles: %.10f (n = %d)\n", result, n / 2);

    // Right rectangles method
    n = 1;
    do {
        prev_result = result;
        result = right_rectangles(a, b, n);
        n *= 2;
    } while (fabs(result - prev_result) > EPSILON);
    printf("Right rectangles: %.10f (n = %d)\n", result, n / 2);

    // Midpoint rectangles method
    n = 1;
    do {
        prev_result = result;
        result = midpoint_rectangles(a, b, n);
        n *= 2;
    } while (fabs(result - prev_result) > EPSILON);
    printf("Midpoint rectangles: %.10f (n = %d)\n", result, n / 2);

    // Trapezoidal method
    n = 1;
    do {
        prev_result = result;
        result = trapezoidal(a, b, n);
        n *= 2;
    } while (fabs(result - prev_result) > EPSILON);
    printf("Trapezoidal method: %.10f (n = %d)\n", result, n / 2);

    // Simpson's method
    n = 2; // Start with an even number of intervals
    do {
        prev_result = result;
        result = simpson(a, b, n);
        n *= 2;
    } while (fabs(result - prev_result) > EPSILON);
    printf("Simpson's method: %.10f (n = %d)\n", result, n / 2);

    return 0;
}