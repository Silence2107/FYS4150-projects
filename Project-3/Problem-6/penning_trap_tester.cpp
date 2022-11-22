
#include "../include/penning_trap.h"
#include "../include/particle.hpp"

#include <functional>
#include <vector>
#include <armadillo>
#include <cmath>
#include <iostream>

int main()
{
    PenningTrap trap(1, 1, 1);
    Particle particle1(-5.3, 1, {-3.1, 1.2, -2.2}, {0, 0, 0}), particle2(4.2, 3, {1, 2.1, 1}, {-1, 1, -1});
    // add a few particles
    trap.add_particle(particle1);
    trap.add_particle(particle2);
    // switch on the interaction
    trap.enable_particle_interaction([](const Particle &p1, const Particle &p2)
                                     {
        // Coulomb force
        return 1.389 * 100000.0 / arma::dot(p1.r - p2.r, p1.r - p2.r) * p1.q * p2.q * arma::normalise(p2.r - p1.r); });
    std::cout << trap.interaction_force_on_a_particle(1, particle2); // interaction force on particle2 due to particle1
    trap.add_particle(Particle(1, 1, {0, 0, 0}, {0, 0, 0})); // add a third particle
    // calculate force on particle2 due to particle1 and particle3, but with changed position of particle2

    std::cout << trap.interaction_force_on_a_particle(1, particle2); // for reference
    std::cout << trap.interaction_force_on_a_particle(1, {1.1, 2.0, 1.1}, {-1, 1, -1}); //manually changed position
    particle2.r = {1.1, 2.0, 1.1};
    std::cout << trap.interaction_force_on_a_particle(1, particle2); // same as above, but invokes the other overload

    //switch off the interaction
    trap.enable_particle_interaction([](const Particle &, const Particle &)
                                     { return arma::vec({0, 0, 0}); });

    std::cout << trap.interaction_force_on_a_particle(1, particle2); // zero vector now

    // external force field
    std::cout << trap.external_force_field({1, 2, 3}, {1, 2, 3}, 1);
}