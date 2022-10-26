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

    PenningTrap trap(B0, V0, dCharacteristicDimension);
    //Create the two desired particles.
    Particle particle1(Ca40charge, Ca40mass, {20, 0, 20}, {0, 25, 0}),
        particle2(Ca40charge, Ca40mass, {25, 25, 0}, {0, 40, 5});
    //A the partciles to the trap.
    trap.add_particle(particle1);
    trap.add_particle(particle2);
    
    double endTime = 50; // 50 microseconds
    double dt = 0.001;

    double n = endTime / dt;

    //Set up vectors to store all values during evolving, to be used for plot later.
    std::vector<double> time(n + 1);

    std::vector<double> x1(n + 1);
    std::vector<double> y1(n + 1);
    std::vector<double> z1(n + 1);

    std::vector<double> x2(n + 1);
    std::vector<double> y2(n + 1);
    std::vector<double> z2(n + 1);
    
    for (int i = 0; i < n; i++)
    {

        // Store all time steps.
        time[i] = i*dt;

        // Store particles x and y coordinate for both particles.
        x1[i] = trap.particles()[0].r[0];
        y1[i] = trap.particles()[0].r[1];
        z1[i] = trap.particles()[0].r[2];

        x2[i] = trap.particles()[1].r[0];
        y2[i] = trap.particles()[1].r[1];
        z2[i] = trap.particles()[1].r[2];
        
        trap.evolve_RK4(dt);
    }

    //Store the last evolving step after the loop. Number of values are n+1 while loop only goes n times. 
    time[n] = n*dt;

    x1[n] = trap.particles()[0].r[0];
    y1[n] = trap.particles()[0].r[1];
    z1[n] = trap.particles()[0].r[2];
    
    x2[n] = trap.particles()[1].r[0];
    y2[n] = trap.particles()[1].r[1];
    z2[n] = trap.particles()[1].r[2];

    two_columns_to_csv("particle1xy.csv", x1, y1, ",", false, 7);
    two_columns_to_csv("particle1z.csv", time, z1, ",", false, 7);
    two_columns_to_csv("particle2xy.csv", x1, y1, ",", false, 7);
    
    three_columns_to_csv("particle1xyz.csv", x1, y1, z1, ",", false, 7);

}
