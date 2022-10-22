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
    Particle particle1(-5.3, 1, {-3.1, 1.2, -2.2}, {0, 0, 0}), particle2(4.2, 3, {1, 2.1, 1}, {-1, 1, -1});
    // add a few particles
    //trap.add_particle(particle1);
    //trap.add_particle(particle2);

	//For now just evolve a few steps. Result will be printed. To be developed further.
    //trap.evolve_forward_Euler(0.01);
    //trap.evolve_forward_Euler(0.01);
    //trap.evolve_forward_Euler(0.01);

    //trap.particle_numbers();

}
