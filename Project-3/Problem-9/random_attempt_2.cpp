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

    double f = 1.0;

    PenningTrap trap(B0, V0*(1+f), dCharacteristicDimension);

    arma::arma_rng::set_seed(1000);
    //arma::vec r = arma::vec(3).randu()*0.1*500; //arma::vec("20 0 20");
    //arma::vec v = arma::vec(3).randu()*0.1*500; //arma::vec("0 25 0");

for (int i = 1; i <= 50; i++){

  arma::vec r = arma::vec(3).randu()*0.1*500; //arma::vec("20 0 20");
  arma::vec v = arma::vec(3).randu()*0.1*500; //arma::vec("0 25 0");

  Particle particle(Ca40charge, Ca40mass, r, v);
  trap.add_particle(particle);

}

    /*
      double endTime = 50; // 50 microseconds
      double dt = 0.1;
    */
    double endTime = 500; // 50 microseconds
    double dt = 0.01;

    double n = endTime / dt;
    std::vector<double> x1(n + 1);
    std::vector<double> y1(n + 1);
    std::vector<double> z1(n + 1);

    std::vector<double> x2(n + 1);
    std::vector<double> y2(n + 1);


    std::vector<double> ang(3);
    ang[0] = 0.5; ang[1] = 1.5; ang[2] = 2.0;
    std::vector<double> frac(3);



    for (int i = 0; i < n; i++)
    {

        // Store particles x and y coordinate after each step, for later plotting.
        x1[i] = trap.particles()[49].r[0];
        y1[i] = trap.particles()[49].r[1];
        z1[i] = trap.particles()[49].r[2];

        trap.evolve_RK4(dt);
        trap.V0() = V0 * (1 + f*cos(1.0*n*dt));
        // trap.evolve_RK4(dt);
        //  x2[i] = trap.particles()[1].r[0];
        //  y2[i] = trap.particles()[1].r[1];
    }

    x1[n] = trap.particles()[49].r[0];
    y1[n] = trap.particles()[49].r[1];
    z1[n] = trap.particles()[49].r[2];

    two_columns_to_csv("particle1.csv", x1, y1, ",", false, 7);
    std::cout << trap.particle_numbers() << std::endl;
    // two_columns_to_csv("particle2.csv", x2, y2);
}
