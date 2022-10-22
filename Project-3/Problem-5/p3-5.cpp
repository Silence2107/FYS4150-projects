#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>

#include "../include/particle.hpp"

int main()
{
    // the following call creates a particle, and prints its member fields
    Particle particle1{2.0, 10, {1.2, 0.4, 3.5}, {-0.5, .05, 1.8}, true};

    return 0;
}