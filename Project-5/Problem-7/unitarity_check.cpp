
#include "../include/auxiliaries.h"
#include "../include/many_slit_initializer.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/schrodinger_2d_solver.h"
#include "../include/file_io.h"

#include <armadillo>
#include <iostream>
#include <functional>
#include <string>
#include <cmath>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <double_slit_on={0,1}>" << std::endl;
        return 1;
    }

    bool double_slit_on = std::stoi(argv[1]);

    // Set up the grid and simulation parameters
    size_t Nx = 201,
           Ny = 201;
    arma::vec x_bound = {0, 1},
              y_bound = {0, 1};
    double dt = 2.5E-5,
           t_max = 0.008;
    size_t Nt = static_cast<long>(t_max / dt);
    // slit parameters
    double x_center_slit = 0.5, y_center_slit = 0.5;
    double x_slit_width = 0.02,
           y_slit_width = 0.05,
           y_slit_spacing = 0.05;
    double wall_potential = 1.0E10;
    size_t n_slits = 2;
    // wave packet parameters
    double x_center_pack = 0.25,
           y_center_pack = 0.5,
           x_spread = 0.05,
           y_spread = 0.1,
           px = 200,
           py = 0;

    std::function<double(double, double)> potential;

    if (double_slit_on)
        potential = [&](double x, double y) {
            return many_slit_potential(x, y, x_center_slit, y_center_slit, x_slit_width, y_slit_width, y_slit_spacing, n_slits, wall_potential);
        };
    else
        potential = [&](double x, double y){
            return 0;
        };
    
    std::cout << "Potential is " << (double_slit_on ? "double slit" : "infinite well") << std::endl;
    
    arma::cx_vec psi = initialize_particle_wavefunction(Nx, Ny, x_bound, y_bound, x_center_pack, y_center_pack, x_spread, y_spread, px, py);

    // Save integrated densities to a file
    std::string outf = "probability_of_time.txt";

    // Now we can check unitarity
    std::vector<double> probabilities(Nt),
                        times(Nt);
    for (size_t i = 0; i < Nt; i++)
    {
        std::cout << "Processing time step " << i << " of " << Nt << std::endl;
        psi = schrodinger_solver(psi, potential, dt, Nx, Ny, x_bound, y_bound);
        probabilities[i] = pow(arma::norm(psi), 2);
        times[i] = i * dt;
    }

    two_columns_to_csv(outf, times, probabilities);
}