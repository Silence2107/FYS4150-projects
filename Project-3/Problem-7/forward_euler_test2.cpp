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
  double B0 = 9.65e1;
  double V0 = 2.41e6;
  double dCharacteristicDimension = 500;
  double Ca40mass = 40; //40u
  double Ca40charge = 1; //1 elementary charge

  PenningTrap trap(B0, V0, dCharacteristicDimension);
  Particle particle1(Ca40charge, Ca40mass, {20, 0, 20}, {0, 25, 0}),
      particle2(Ca40charge, Ca40mass, {25, 25, 0}, {0, 40, 5});
  // add a few particles
  trap.add_particle(particle1);
  trap.add_particle(particle2);

  double endTime = 50; // 50 microseconds
  double dt = 0.1;

  double n = endTime / dt;
  std::vector<double> x1(n + 1);
  std::vector<double> y1(n + 1);

  std::vector<double> x2(n + 1);
  std::vector<double> y2(n + 1);

  for (int i = 0; i < n; i++)
  {
    trap.evolve_forward_Euler(dt);

    // Store particles x and y coordinate after each step, for later plotting.
    x1[i] = trap.particles()[0].r[0];
    y1[i] = trap.particles()[0].r[1];

    x2[i] = trap.particles()[1].r[0];
    y2[i] = trap.particles()[1].r[1];
  }
  two_columns_to_csv("particle1.csv", x1, y1);
  two_columns_to_csv("particle2.csv", x2, y2);
}
