#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_SAMPLES 1000000

// Function to be integrated
double f(double x) {
    return x * x; // Example function: f(x) = x^2
}

int main() {
    double integral = 0.0;
    double sum = 0.0;
    double x;
    
    #pragma omp parallel private(x) reduction(+:sum)
    {
        #pragma omp for
        for (int i = 0; i < NUM_SAMPLES; i++) {
            x = (double)rand() / RAND_MAX; // Random x-coordinate between 0 and 1
            sum += f(x);
        }
    }
    
    integral = sum / NUM_SAMPLES;
    
    printf("Estimated value of the integral: %f\n", integral);
    
    return 0;
}
