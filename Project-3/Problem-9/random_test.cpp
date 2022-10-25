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
  int endTime = 100;
  double dt = 0.001;
  double n = endTime / dt;

    //GENERATE THE PARTICLES
    double B0 = 9.65e1;
    double V0 = 2.41e6;
    double dCharacteristicDimension = 500;
    double Ca40mass = 40;  // 40u
    double Ca40charge = 1; // 1 elementary charge



    arma::arma_rng::set_seed(1000);

    int particles = 1; //particle numbers


        //initializations
        std::vector<double> wv(116);                 //angular frequencies
        wv[0] = 0.2;
        std::vector<double> fraction(116);           //fraction of particles

        std::vector<double> x(n + 1);
        std::vector<double> y(n + 1);

        double f = 0.0;  //AMPLITUDE




for (int i = 0; i < 116; i++){
  wv[i+1] = 0.02 + wv[i];
  PenningTrap trap(B0, V0*(1+f), dCharacteristicDimension);

  for (size_t j = 0; j < particles; j++){

    arma::vec r = arma::vec(3).randu()*0.1*trap.d();
    arma::vec v = arma::vec(3).randu()*0.1*trap.d();

    x[0] = r(0);
    y[0] = r(1);

    Particle particle(Ca40charge, Ca40mass, r, v);
    trap.add_particle(particle); }

    for (int k = 1; k <= n; k++){
      trap.evolve_RK4(dt);
      x[k] = trap.particles()[0].r[0];
      y[k] = trap.particles()[0].r[1];
      trap.V0() = V0 * (1 + f*cos(wv[i]*k*dt));

  fraction[i] = trap.particle_numbers(); ///(1.0*particles);
}}


    //write the values to file
    two_columns_to_csv("fraction.csv", wv, fraction, " ", false, 7);

    //XY
    two_columns_to_csv("xy", x, y, " ", false, 7);


}
