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

    //Initialize wave function psi.
    //Picking some physical values for the wave packet. 
    //For this unit test we could really use anything. However the numbers below are taken from an actual sample run we will do later.
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
	
	

    // 2. Dirichlet boundary conditions + 0 potential basically means that we simulate an infinite well
    // If we start with infinite well eigenstate, we should get the same eigenstate after some time, disregarding time phase
    // We can check this by comparing the probability densities everywhere on the grid

    std::cout << "\n Test 2. \n";

    Nx = 10, Ny = 10;
    
	arma::cube probabilities_all_time_steps = arma::cube(Nx - 2, Ny - 2, Nt);;
	
    // disregard normalization as for now
    auto lowest_eigenstate = [](double x, double y) { return std::sin(M_PI * x) * std::sin(M_PI * y); };
    // also, probe schrodinger_solver overload with a potential function instead of a vector! No need to discretize it
    auto V_func = [](double x, double y) { return 0.0; };
    psi_old = arma::zeros<arma::cx_vec>((Nx - 2) * (Ny - 2));
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_old(flatten_index(i, j, Nx - 2)) = lowest_eigenstate(x_bound(0) + (x_bound(1) - x_bound(0)) * (i + 1) / Nx, y_bound(0) + (y_bound(1) - y_bound(0)) * (j + 1) / Ny);
        }
    }
    // normalize psi
    psi_old = psi_old / arma::norm(psi_old);
    psi_new = psi_old;
    // perform time evolution
    for (size_t i = 0; i < 10; ++i)
    {
        psi_new = schrodinger_solver(psi_new, V_func, dt, Nx, Ny, x_bound, y_bound);
    }
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
    std::cout << "avg. relative error = " << arma::accu(arma::abs(psi_old_prob - psi_new_prob) / psi_old_prob)/((Nx-2)*(Ny-2)) << std::endl;


}