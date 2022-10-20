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
  double Ca40mass = 66.52948e-24;
  double Ca40charge = 1.602176e-19;

  PenningTrap trap(1, 1, 1);
  Particle particle1(Ca40charge, Ca40mass, {20e-6, 0, 20 - 6}, {0, 25 - 6, 0}),
      particle2(Ca40charge, Ca40mass, {25 - 6, 25 - 6, 0}, {0, 40 - 6, 5 - 6});
  // add a few particles
  trap.add_particle(particle1);
  trap.add_particle(particle2);

  double endTime = 50e-6; // 50 microseconds
  double dt = 0.1e-6;

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
