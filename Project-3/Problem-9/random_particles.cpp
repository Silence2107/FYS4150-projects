#include "../include/penning_trap.h"
#include "../include/particle.h"

#include <functional>
#include <vector>
#include <armadillo>
#include <cmath>
#include <iostream>

int main()
{
    PenningTrap trap(1, 1, 1);

    arma::arma_rng::set_seed(1000);

    int particles = 2; //particle numbers

    for (size_t i = 0; i < particles; i++){

      //generate random position and velocity according to a normal distribution
      arma::vec r = arma::vec(3).randn()*0.1*trap.d();
      arma::vec v = arma::vec(3).randn()*0.1*trap.d();

      //generate particle and add it to the system
      Particle particle(-5.3, 1, r, v);
      trap.add_particle(particle);
    }
}
