#include "../include/schrodinger_2d_solver.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>

int main()
{
    // unit test for initializing wave function. Then also running schrodinger_solver to check if it stays normalized. 

    size_t Nx = 10, Ny = 10;
    arma::vec x_bound = {0, 1}, y_bound = {0, 1};
    arma::mat V_matr = arma::zeros<arma::mat>(Nx - 2, Ny - 2);

    double dt = 0.0001; // fine dt is REQUIRED for reasonable results, however be mindful about stability

    // initialize psi
    double x_min = x_bound(0), x_max = x_bound(1);  //TODO: these 3 lines getting duplicate. Refactor somehow, maybe into auxilaries.
    double y_min = y_bound(0), y_max = y_bound(1);
    double dx = (x_max - x_min) / (Nx - 1), dy = (y_max - y_min) / (Ny - 1);

    //Picking some physical values for the wave packet. 
    //For this unit test we could really use anything. However the numbers below are taken from an actual sample run we will do later.
    arma::cx_vec psi_old = initialize_particle_wavefunction(Nx, Ny, dx, dy, 0.25, 0.5, 0.05, 0.05, 200.0, 0.0);

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
    psi_old_mat.print("psi_old_mat = ");
    // invoke update
    auto psi_new = schrodinger_solver(psi_old, V_matr, dt, Nx, Ny, x_bound, y_bound);
    for (size_t i = 0; i < 10; ++i)
    {
        psi_new = schrodinger_solver(psi_new, V_matr, dt, Nx, Ny, x_bound, y_bound);
    }
    // print psi_new as matrix
    arma::cx_mat psi_new_mat = arma::zeros<arma::cx_mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_new_mat(i, j) = psi_new(flatten_index(i, j, Nx - 2));
        }
    }
    psi_new_mat.print("psi_new_mat = "); // should be at least a bit localized
    // check that the norm is preserved (should be close to 1 at reasonable dt and grid size)
    std::cout << "new_norm = " << arma::norm(psi_new) << std::endl;
}