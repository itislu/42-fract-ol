#include <stdio.h>

int mandelbrot(double x0, double y0, int max_iteration) {
    double x = 0.0;
    double y = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    double w = 0.0;
    int iteration = 0;

    while (x2 + y2 <= 4.0 && iteration < max_iteration) {
        x = x2 - y2 + x0;
        y = w - x2 - y2 + y0;
        x2 = x * x;
        y2 = y * y;
        w = (x + y) * (x + y);
        iteration++;
    }

    return iteration;
}

void printColor(int iteration) {
    // Example color mapping (adjust as needed)
    if (iteration == 0) {
        printf("\033[0;30m");  // Black for points in the Mandelbrot set
    } else {
        // Color based on iteration count (adjust as needed)
        int color = 30 + (iteration % 10);  // Modulo to create a repeating pattern
        printf("\033[1;%dm", color);
    }
    printf("*");
    printf("\033[0m");  // Reset color
}

int main() {
    // Example parameters (adjust as needed)
    int width = 109;
    int height = 33;
    double x_min = -2.0;
    double x_max = 1.5;
    double y_min = -1.0;
    double y_max = 1.0;
    int max_iteration = 50;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Map pixel coordinates to complex plane coordinates
            double x0 = x_min + (x_max - x_min) * j / (width - 1.0);
            double y0 = y_min + (y_max - y_min) * i / (height - 1.0);

            int iteration = mandelbrot(x0, y0, max_iteration);
            printColor(iteration);
        }
        printf("\n");
    }

    return 0;
}