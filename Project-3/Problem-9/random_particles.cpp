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

    //for (size_t i = 0; i < m_particles.size(); i++){
    //}

    arma::vec r = arma::vec(3).randn()*0.1*trap.d();
    arma::vec v = arma::vec(3).randn()*0.1*trap.d();

    Particle particle1(-5.3, 1, r, v), particle2(4.2, 3, {1, 2.1, 1}, {-1, 1, -1});
    // add a few particles
    //trap.add_particle(particle1);
    //trap.add_particle(particle2);

}
