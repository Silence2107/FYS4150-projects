
#include "../include/schrodinger_2d_solver.h"
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

    // 2. Dirichlet boundary conditions + 0 potential basically means that we simulate an infinite well
    // If we start with infinite well eigenstate, we should get the same eigenstate after some time, disregarding time phase
    // We can check this by comparing the probability densities everywhere on the grid

    std::cout << "\n Test 2. \n";

    Nx = 10, Ny = 10;
    
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
    
    // 3. Last but not least, you can use cached version of the solver, which takes responsibility of saving the time evolution
    // and allows you to get the solution at any time you want. This is useful for example when you want to plot the solution,
    // however memory consumption is higher than usual, so use it wisely
    std::cout << "\n Test 3. \n";

    // here is how you create a cached function. This monstrosity is just a function's parameter list, excluding Cache's &
    auto cached_solver = CachedFunc<arma::cx_vec, arma::cx_cube, const arma::cx_vec &, const std::function<double(double, double)> &, 
        double, size_t, size_t, size_t, const arma::vec &, const arma::vec &>(schrodinger_solver_cached);
    // let's compare with results from the previous test
    auto psi_new_cached = psi_old; 
    // perform time evolution
    for (size_t i = 0; i < 10; ++i)
    {
        // only the first call is expensive, the rest is just a lookup (for as long as you request for a solution at precomputed times)
        psi_new_cached = cached_solver(psi_new_cached, V_func, dt, Nx, Ny, 10, x_bound, y_bound);
    }
    // calculate probability densities
    arma::mat psi_new_cached_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_new_cached_prob(i, j) = std::norm(psi_new_cached(flatten_index(i, j, Nx - 2)));
        }
    }
    // stats
    psi_new_cached_prob.print("psi_new_cached_prob = ");
    std::cout << "avg. relative error = " << arma::accu(arma::abs(psi_new_prob - psi_new_cached_prob) / psi_new_prob)/((Nx-2)*(Ny-2)) << std::endl;
}