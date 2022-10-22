#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <armadillo>

/// @brief Class containing information about a particle.
class Particle
{
public:
    /// @brief particle's charge
    double q;
    /// @brief particle's mass
    double m;
    /// @brief particle's position
    arma::vec r = arma::vec(3);
    /// @brief particle's velocity
    arma::vec v = arma::vec(3);

public:
    /// @brief initializes the particle with the given parameters
    /// @param q particle's charge
    /// @param m particle's mass
    /// @param r particle's position
    /// @param v particle's velocity
    /// @param console_logging whether to log to console; default is false
    Particle(double q_inp, double m_inp, const arma::vec &r_inp, const arma::vec &v_inp, bool console_logging = false)
        : q(q_inp), m(m_inp), r(r_inp), v(v_inp)
    {
        if (console_logging)
        {
            std::cout << "Particle with:" << std::endl;
            std::cout << "- charge: " << q << " e" << std::endl;
            std::cout << "- mass: " << m << " u" << std::endl;
            std::cout << "- position: (" << r(0) << ", " << r(1) << ", " << r(2) << ")"
                      << " \u03BCm" << std::endl;
            std::cout << "- velocity: (" << v(0) << ", " << v(1) << ", " << v(2) << ")"
                      << " \u03BCm/\u03BCs" << std::endl;
        }
    };
};

#endif