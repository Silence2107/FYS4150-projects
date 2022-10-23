#include "../include/penning_trap.h"
#include "../include/particle.h"

#include "../include/file_io.h"

#include <functional>
#include <vector>
#include <armadillo>
#include <cmath>
#include <iostream>

int main()
{
    PenningTrap trap(1, 1, 1);

    arma::arma_rng::set_seed(1000);

    int particles = 1; //particle numbers

    //for printing
    int endTime = 3;
    double dt = 0.01;
    double n = endTime / dt;
    std::vector<double> x1(n + 1);
    std::vector<double> y1(n + 1);


    for (size_t i = 0; i < particles; i++){

      //generate random position and velocity according to a normal distribution
      arma::vec r = arma::vec(3).randn()*0.1*trap.d();
      arma::vec v = arma::vec(3).randn()*0.1*trap.d();

      x1[0] = r(0);
      y1[0] = r(1);

      //generate particle and add it to the system
      Particle particle(1, 1, r, v);
      trap.add_particle(particle);
    }


    for (size_t i = 1; i < n; i++){
        trap.evolve_forward_Euler_perturbed(dt, i, 1, 1);
        x1[i] = trap.particles()[0].r[0];
        y1[i] = trap.particles()[0].r[1];
        }

        //print particle numbers in the trap
        std::cout << trap.particle_numbers() << std::endl;

    two_columns_to_csv("particle1.csv", x1, y1, ",", false, 7);

    }
