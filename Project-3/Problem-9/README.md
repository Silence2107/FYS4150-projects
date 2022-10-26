# Problem 9 manual

Simulates a trap consisting of singly charged Calsium ions. Switching off Coulomb interactions is done in random_ca.cpp file where it says
`trap.enable_particle_interaction([]const Particle &p1, const Particle &p2)` 
by replacing 
`return 1.389 * 100000.0 / arma::dot(p1.r - p2.r, p1.r - p2.r) * p1.q * p2.q * arma::normalise(p2.r - p1.r); });`
with
`return arma::vec({0, 0, 0}); });` 


Compile for any amplitude or frequency range:

`g++ random_ca.cpp -o random_ca.out ../src/* -I../include/ -std=c++11 -larmadillo -O4`

Run:

`./random_ca_out`


Make plot for last particle in the xy plane:

`python3 plotter3.py --csv "last_particle.csv"`

Plot the fraction of particles trapped as a function of frequency:

`python3 plotter3_fraction.py --csv "fraction.csv"`
