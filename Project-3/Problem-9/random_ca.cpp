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
    double B0 = 9.65e1;
    double V0 = 2.41e6;
    double dCharacteristicDimension = 500;
    double Ca40mass = 40;  // 40u
    double Ca40charge = 1; // 1 elementary charge

    double f = 0.1; //amplitude

    arma::arma_rng::set_seed(1000);

    double endTime = 500; // microseconds
    double dt = 0.001;

    double n = endTime / dt;

    int freq_num = 116;                     //number of frequencies
    int particles = 30;                     //number of particles
    int particle_plot_number = particles-1; //index of last particle

    std::vector<double> ang(freq_num);
    std::vector<double> frac(freq_num);
    std::vector<double> particle_numb(freq_num);

    //generating vector of frequencies
    arma::vec ang_pre = arma::linspace(0.2, 2.5, freq_num);
    for (size_t i = 0; i < ang_pre.size(); i++){
      ang[i] = ang_pre[i];
    }


std::vector<double> x1(n + 1);
std::vector<double> y1(n + 1);
std::vector<double> z1(n + 1);


for (size_t w = 0; w < ang.size(); w++){

    PenningTrap trap(B0, V0*(1+f), dCharacteristicDimension);

    for (int i = 1; i <= particles; i++){

      arma::vec r = arma::vec(3).randu()*0.1*dCharacteristicDimension; //arma::vec("20 0 20");
      arma::vec v = arma::vec(3).randu()*0.1*dCharacteristicDimension; //arma::vec("0 25 0");

      Particle particle(Ca40charge, Ca40mass, r, v);
      trap.add_particle(particle);

      //enable or disable particle interactions
      trap.enable_particle_interaction([](const Particle &p1, const Particle &p2){
        //Coulomb force:
        return 1.389 * 100000.0 / arma::dot(p1.r - p2.r, p1.r - p2.r) * p1.q * p2.q * arma::normalise(p2.r - p1.r); });
        //switch off Coulomb force:
        //return arma::vec({0, 0, 0}); });


      }

    //Forward Euler method, storing xy coordinates for the last particle
    for (int i = 0; i < n; i++)
    {

        // Store particles x and y coordinate after each step, for later plotting.
        x1[i] = trap.particles()[particle_plot_number].r[0];
        y1[i] = trap.particles()[particle_plot_number].r[1];
        z1[i] = trap.particles()[particle_plot_number].r[2];

        trap.evolve_RK4(dt);
        trap.V0() = V0 * (1 + f*cos(ang[w]*i*dt));

    }

      x1[n] = trap.particles()[particle_plot_number].r[0];
      y1[n] = trap.particles()[particle_plot_number].r[1];
      z1[n] = trap.particles()[particle_plot_number].r[2];

      //Particle numbers and fraction calculations
      particle_numb[w] = trap.particle_numbers();
      frac[w] = particle_numb[w]/particles;

      //Printing progress
      std::cout << w+1 << "/" << freq_num << "    " <<
      "Frequency: " << ang[w] << " " << "   Particle numbers: " << trap.particle_numbers() << std::endl;

}

two_columns_to_csv("last_particle.csv", x1, y1, ",", false, 7);
two_columns_to_csv("particle_numbers.csv", ang, particle_numb, ",", false, 7);
two_columns_to_csv("fraction.csv", ang, frac, ",", false, 7);

}
