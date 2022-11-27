#include "../include/schrodinger_2d_solver.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>

int main()
{
    // unit test for schrodinger_solver

    size_t Nx = 5, Ny = 5;
    arma::vec x_bound = {0, 1}, y_bound = {0, 1};
    arma::mat V_matr = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    arma::cx_vec psi_old = arma::zeros<arma::cx_vec>((Nx - 2) * (Ny - 2));

    // psi_old
    psi_old(0) = 1.0;
    double dt = 0.0001; // fine dt is REQUIRED for reasonable results, however be mindful about stability

    // normalize psi
    psi_old = psi_old / arma::norm(psi_old);

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