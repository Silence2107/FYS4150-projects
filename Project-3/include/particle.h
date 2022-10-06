#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <armadillo>

class Particle
{
public:
    /// @brief Particle charge
    double q;
    /// @brief Particle mass
    double m;
    /// @brief Particle position
    arma::vec r;
    /// @brief Particle velocity
    arma::vec v;
public:
    Particle(double q, double m, const arma::vec &r, const arma::vec &v): q(q), m(m), r(r), v(v)
    {
        std::cout << "Particle created" << std::endl;
    };
};


#endif