#include "../include/penning_trap.h"
#include "../include/particle.hpp"

#include "../include/file_io.h"

#include <functional>
#include <vector>
#include <armadillo>
#include <cmath>
#include <iostream>

int main()
{

  //DEFINE TIME
  int endTime = 500;
  double dt = 0.01;
  double n = endTime / dt;

    //GENERATE THE PARTICLES
    double B0 = 9.65e1;
    double V0 = 2.41e6;
    double dCharacteristicDimension = 500;
    double Ca40mass = 40;  // 40u
    double Ca40charge = 1; // 1 elementary charge

    PenningTrap trap(B0, V0, dCharacteristicDimension);

    arma::arma_rng::set_seed(1000);

    int particles = 100; //particle numbers

    std::vector<double> x1(n + 1);
    std::vector<double> y1(n + 1);

    for (size_t i = 0; i < particles; i++){

      //generate random position and velocity according to a normal distribution
      arma::vec r = arma::vec(3).randu()*0.1*trap.d();
      arma::vec v = arma::vec(3).randu()*0.1*trap.d();

      x1[0] = r(0);
      y1[0] = r(1);

      //generate particle and add it to the system
      Particle particle(Ca40charge, Ca40mass, r, v);
      trap.add_particle(particle);
    }


    //EULER FORWARD WITH TIME DEPENDENT PERTUBATION

    //initializations
    //arma::vec wv = arma::linspace(0.2,2.5,116);       //angular frequencies
    std::vector<double> wv(116);
    wv[0] = 0.2;
    std::vector<double> fraction(116);           //fraction of particles
    //arma::vec fraction = arma::vec(size(wv));

    double f = 0;  //AMPLITUDE

    //calculations
    double V0_start = trap.V0();

    for (int i = 1; i < 117; i++){
      wv[i] = 0.02 + wv[i-1];

      for (int j = 1; j <= n; j++){
        trap.evolve_forward_Euler(dt);
        trap.V0() = V0_start * (1 + f*cos(wv[i-1]*j*dt));      //time dependent potential
      }
      //calculates fraction of particles in trap/ all the particles
      fraction[i] = trap.particle_numbers(); ///(1.0*particles);
    }

    //write the values to file
    two_columns_to_csv("fractions_euler_amp_0_4.csv", wv, fraction, " ", false, 7);

}
