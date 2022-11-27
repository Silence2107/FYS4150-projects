#include "../include/schrodinger_2d_solver.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>

using namespace std;
using namespace std::chrono;

/** 
 * Declarion two functions defined further down in file.
 * They consist of old methods copied from schrodinger_2d_solver.cpp, names prefixed by dense_.
 * Copying the previous version of Crank Nicolson function with the plan to keep this for comparision, and modify the original for improvements.
 */
std::tuple<arma::cx_mat, arma::cx_mat> dense_generate_crank_nicolson_A_and_B(const arma::mat &V, double dt, double dx, double dy, size_t Nx, size_t Ny);
arma::cx_vec dense_schrodinger_solver(const arma::cx_vec &psi, const arma::mat &V, double dt, size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound);

/*** This program is for comparing preformance between solving for dense or sparse matrices
     The actual Crank Nicolson algoritm under the shared source folder ../src were modified to use
     sparse matrices.
     Meanwhile a copy of the old version of that function was copied to this file as it used to be,
     only to be used for running performance comparisions, and prove sparse matrices is a good idea.
*/
int main()
{
    // unit test for initializing wave function. Then also running schrodinger_solver to check if it stays normalized.

    size_t Nx = 30, Ny = 30;
    arma::vec x_bound = {0, 1}, y_bound = {0, 1};
    arma::mat V_matr = arma::zeros<arma::mat>(Nx - 2, Ny - 2);

    int numIterations = 1000;
    int numWarmUpIterations = 50;

    double dt = 0.0001; // fine dt is REQUIRED for reasonable results, however be mindful about stability

    // Initialize wave function psi.
    // Picking some physical values for the wave packet.
    // For this unit test we could really use anything. However the numbers below are taken from an actual sample run we will do later.
    arma::cx_vec psi_old = initialize_particle_wavefunction(Nx, Ny, x_bound, y_bound, 0.25, 0.5, 0.05, 0.05, 200.0, 0.0);

    // print psi_old as matrix
    arma::cx_mat psi_old_mat = arma::zeros<arma::cx_mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_old_mat(i, j) = psi_old(flatten_index(i, j, Nx - 2));
        }
    }


    // Warmup, to avoid second test looking faster just because some memory handling behind the scenes or something
    // just makes things faster after the first few iterations. 
    {
        std::cout << "\n Warming up.\n";
        auto start = high_resolution_clock::now(); // Record starting time.
        // invoke update
        auto psi_new = schrodinger_solver(psi_old, V_matr, dt, Nx, Ny, x_bound, y_bound);
        for (size_t i = 0; i < numWarmUpIterations - 1; ++i)
        {
            psi_new = dense_schrodinger_solver(psi_new, V_matr, dt, Nx, Ny, x_bound, y_bound);
        }
        auto stop = high_resolution_clock::now(); // Record ending time.
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Warm up time " << duration.count() << " microseconds." << endl;
    }

    // Measure time performance on older dense matrix code. Making a code block for simple reuse if variable declarations later.
    {
        std::cout << "\n Test 1. Timing of dense matrix solving.\n";
        auto start = high_resolution_clock::now(); // Record starting time.
        // invoke update
        auto psi_new = schrodinger_solver(psi_old, V_matr, dt, Nx, Ny, x_bound, y_bound);
        for (size_t i = 0; i < numIterations - 1; ++i)
        {
            psi_new = dense_schrodinger_solver(psi_new, V_matr, dt, Nx, Ny, x_bound, y_bound);
        }
        auto stop = high_resolution_clock::now(); // Record ending time.
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by dense matrix solving " << numIterations << " iterations: " << duration.count() << " microseconds." << endl;
    }

    // Do the same with the new sparse algoritm
    {
        std::cout << "\n Test 2. Timing of sparse matrix solving.\n";
        auto start = high_resolution_clock::now(); // Record starting time.
        // invoke update
        auto psi_new = dense_schrodinger_solver(psi_old, V_matr, dt, Nx, Ny, x_bound, y_bound);
        for (size_t i = 0; i < numIterations - 1; ++i)
        {
            psi_new = schrodinger_solver(psi_new, V_matr, dt, Nx, Ny, x_bound, y_bound);
        }
        auto stop = high_resolution_clock::now(); // Record ending time.
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by sparse matrix solving " << numIterations << " iterations: " << duration.count() << " microseconds." << endl;
    }
}

std::tuple<arma::cx_mat, arma::cx_mat> dense_generate_crank_nicolson_A_and_B(const arma::mat &V, double dt, double dx, double dy, size_t Nx, size_t Ny)
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

arma::cx_vec dense_schrodinger_solver(const arma::cx_vec &psi, const arma::mat &V, double dt, size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound)
{
    auto [dx, dy] = find_dx_and_dy(Nx, Ny, x_bound, y_bound);

    auto [A, B] = dense_generate_crank_nicolson_A_and_B(V, dt, dx, dy, Nx, Ny);

    // now it takes to solve A psi_new = B * psi
    return arma::solve(A, B * psi);
}
