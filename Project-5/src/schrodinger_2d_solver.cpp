
#include "../include/schrodinger_2d_solver.h"
#include "../include/auxiliaries.h"

#include <armadillo>

std::tuple<arma::cx_mat, arma::cx_mat> generateCrankNicolsonAB(const arma::mat &V, double dt, double dx, double dy, size_t Nx, size_t Ny)
{

    auto im_time_step = arma::cx_double(0, 1) * dt;

    // first introduce A and B matrices
    arma::cx_mat A = arma::zeros<arma::cx_mat>((Nx - 2) * (Ny - 2), (Nx - 2) * (Ny - 2));
    arma::cx_mat B = arma::zeros<arma::cx_mat>((Nx - 2) * (Ny - 2), (Nx - 2) * (Ny - 2));

    // fill them
    for (size_t col = 0; col < (Nx - 2) * (Ny - 2); col++)
    {
        auto indices = unflatten_index(col, Nx - 2); // unflattened indices related to grid
        size_t row;
        // first fill the diagonal elements of A and B; 1 + i*dt/(dx^2) + i*dt/(dy^2) + i*dt/2*V
        row = col; // basically, flatten_index(indices(0), indices(1), Nx-2)
        A(row, col) = 1.0 + im_time_step / (dx * dx) + im_time_step / (dy * dy) +
                      im_time_step / 2.0 * V(indices(0), indices(1));
        B(row, col) = 1.0 - im_time_step / (dx * dx) - im_time_step / (dy * dy) -
                      im_time_step / 2.0 * V(indices(0), indices(1));
        // off-diagonals are simple, except for the boundaries; let's work with row variable to make it less confusing
        if (indices(0) >= 1) // I do not want size_t/flattener to fail
        {
            row = flatten_index(indices(0) - 1, indices(1), Nx - 2);
            if (row >= 0)
            {
                A(row, col) = -im_time_step / (2.0 * dx * dx);
                B(row, col) = im_time_step / (2.0 * dx * dx);
            }
        }
        row = flatten_index(indices(0) + 1, indices(1), Nx - 2);
        if (row < (Nx - 2) * (Ny - 2))
        {
            A(row, col) = -im_time_step / (2.0 * dx * dx);
            B(row, col) = im_time_step / (2.0 * dx * dx);
        }
        if (indices(1) >= 1)
        {
            row = flatten_index(indices(0), indices(1) - 1, Nx - 2);
            if (row >= 0)
            {
                A(row, col) = -im_time_step / (2.0 * dy * dy);
                B(row, col) = im_time_step / (2.0 * dy * dy);
            }
        }
        row = flatten_index(indices(0), indices(1) + 1, Nx - 2);
        if (row < (Nx - 2) * (Ny - 2))
        {
            A(row, col) = -im_time_step / (2.0 * dy * dy);
            B(row, col) = im_time_step / (2.0 * dy * dy);
        }
        // else is zero already
    }

    return std::make_tuple(A, B);
}

arma::cx_vec schrodinger_solver(const arma::cx_vec &psi, const arma::mat &V, double dt, size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound)
{
    double x_min = x_bound(0), x_max = x_bound(1);
    double y_min = y_bound(0), y_max = y_bound(1);

    double dx = (x_max - x_min) / (Nx - 1), dy = (y_max - y_min) / (Ny - 1);

    arma::cx_mat A, B;
    std::tie(A, B) = generateCrankNicolsonAB(V, dt, dx, dy, Nx, Ny);
    //Or if we switch to C++ 17 we can just do: auto [A, B] = generateCrankNicolsonAB(V, dt, dx, dy, Nx, Ny);

    // now it takes to solve A psi_new = B * psi
    return arma::solve(A, B * psi);
}

arma::cx_vec schrodinger_solver(const arma::cx_vec &psi, const std::function<double(double, double)> &V, double dt, size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound)
{
    //discretize the potential
    arma::mat V_discrete = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    double x_min = x_bound(0), x_max = x_bound(1);
    double y_min = y_bound(0), y_max = y_bound(1);
    double dx = (x_max - x_min) / (Nx - 1), dy = (y_max - y_min) / (Ny - 1);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            V_discrete(i, j) = V(x_min + (i + 1) * dx, y_min + (j + 1) * dy);
        }
    }
    return schrodinger_solver(psi, V_discrete, dt, Nx, Ny, x_bound, y_bound);
}

arma::cx_vec schrodinger_solver_cached(arma::cx_cube &cache, const arma::cx_vec &psi, const std::function<double(double, double)> &V, double dt, size_t Nx, size_t Ny, size_t Nt, const arma::vec &x_bound, const arma::vec &y_bound)
{
    if (cache.is_empty())
    {
        cache = arma::cx_cube(Nx - 2, Ny - 2, Nt);
        // fill the cache with time evolution
        arma::cx_vec psi_temp = psi;
        for (size_t t = 0; t < Nt; t++)
        {
            cache.slice(t) = arma::reshape(schrodinger_solver(psi_temp, V, dt, Nx, Ny, x_bound, y_bound), Nx - 2, Ny - 2);
            psi_temp = arma::vectorise(cache.slice(t));
        }
    }
    if (cache.n_slices < Nt)
    {
        // fill the cache with further time evolution
        arma::cx_vec psi_temp = arma::vectorise(cache.slice(cache.n_slices - 1));
        for (size_t t = cache.n_slices; t < Nt; t++)
        {
            cache.slice(t) = arma::reshape(schrodinger_solver(psi_temp, V, dt, Nx, Ny, x_bound, y_bound), Nx - 2, Ny - 2);
            psi_temp = arma::vectorise(cache.slice(t));
        }
    }
    return arma::vectorise(cache.slice(Nt - 1));
}