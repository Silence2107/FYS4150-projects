#include "../include/schrodinger_2d_solver.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>

int main()
{
    // unit test for initializing wave function. Then also running schrodinger_solver to check if it stays normalized.

    size_t Nx = 5, Ny = 5;
    arma::vec x_bound = {0, 1}, y_bound = {0, 1};

    double dt = 0.000025; // fine dt is REQUIRED for reasonable results, however be mindful about stability
    //double T = 0.008;     // End time of simulation.
    double T  = 0.0001;     // End time of simulation.
    size_t Nt = T / dt;

    // Temporary zero potential. TODO: Insert code from problem 5.
    auto V_func = [](double x, double y) { return 0.0; };

    // Initialize wave function psi.
    // Picking some physical values for the wave packet.
    // For this unit test we could really use anything. However the numbers below are taken from an actual sample run we will do later.
    arma::cx_vec psi_old = initialize_particle_wavefunction(Nx, Ny, x_bound, y_bound, 0.25, 0.5, 0.05, 0.05, 200.0, 0.0);

    // 1. check that the norm of the solution is preserved
    std::cout << "\n Test 1. \n";
    // print psi_old as matrix
    arma::cx_mat psi_old_mat = arma::zeros<arma::cx_mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_old_mat(i, j) = psi_old(flatten_index(i, j, Nx - 2));
        }
    }

    // Setting up an Armadillo cube object, to store the probability in x/y-plane for each t.
    arma::cube probabilities_all_time_steps = arma::cube(Nx - 2, Ny - 2, Nt);

    // perform time evolution
    auto psi_new = schrodinger_solver(psi_old, V_func, dt, Nx, Ny, x_bound, y_bound);
    for (size_t t = 0; t < Nt; ++t)
    {
        psi_new = schrodinger_solver(psi_new, V_func, dt, Nx, Ny, x_bound, y_bound);

        // calculate probability densities
        arma::mat psi_new_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
        for (size_t i = 0; i < Nx - 2; i++)
        {
            for (size_t j = 0; j < Ny - 2; j++)
            {
                psi_new_prob(i, j) = std::norm(psi_new(flatten_index(i, j, Nx - 2)));
            }
        }
        probabilities_all_time_steps.slice(t) = psi_new_prob;
    }

    // Save the cube in binary Armadillo format. This gives efficient storing of huge 3D data, and can be read by Python pyarma.
    probabilities_all_time_steps.save("data3d.out");

    // calculate probability densities
    arma::mat psi_old_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    arma::mat psi_new_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_old_prob(i, j) = std::norm(psi_old(flatten_index(i, j, Nx - 2)));
            psi_new_prob(i, j) = std::norm(psi_new(flatten_index(i, j, Nx - 2)));
        }
    }

    // stats
    psi_old_prob.print("psi_old_prob = ");
    psi_new_prob.print("psi_new_prob = ");
    std::cout << "avg. relative error = " << arma::accu(arma::abs(psi_old_prob - psi_new_prob) / psi_old_prob) / ((Nx - 2) * (Ny - 2)) << std::endl;
}
