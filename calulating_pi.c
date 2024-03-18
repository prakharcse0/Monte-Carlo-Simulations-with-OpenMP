#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_SAMPLES 1000000

int main() {
    int num_samples_inside_circle = 0;
    double x, y, distance_squared;
    
    #pragma omp parallel for private(x, y, distance_squared) reduction(+:num_samples_inside_circle)
    for (int i = 0; i < NUM_SAMPLES; i++) {
        x = (double)rand() / RAND_MAX; // Random x-coordinate between 0 and 1
        y = (double)rand() / RAND_MAX; // Random y-coordinate between 0 and 1
        
        distance_squared = x * x + y * y; // Distance from the origin squared
        
        if (distance_squared <= 1.0) { // If the point lies inside the unit circle
            num_samples_inside_circle++;
        }
    }
    
    double pi_estimate = 4.0 * num_samples_inside_circle / NUM_SAMPLES;
    
    printf("Estimated value of pi: %f\n", pi_estimate);
    
    return 0;
}
