#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <armadillo>

class Particle {

public:
  double q, m;
  arma::vec r = arma::vec(3);
  arma::vec v = arma::vec(3);

public:
   Particle(double q_inp, double m_inp, const arma::vec &r_inp, const arma::vec &v_inp): q(q_inp), m(m_inp), r(r_inp), v(v_inp)
  {
    std::cout << "Particle with:" << std::endl ;
    std::cout << "- charge: " << q << " e" << std::endl ;
    std::cout << "- mass: " << m << " u" << std::endl ;
    std::cout << "- position: (" << r(0) << ", " << r(1) << ", " << r(2) << ")" << " \u03BCm" << std::endl ;
    std::cout << "- velocity: (" << v(0) << ", " << v(1) << ", " << v(2) << ")" << " \u03BCm/\u03BCs"<< std::endl ;
  };
};

#endif