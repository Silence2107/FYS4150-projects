#include "../include/schrodinger_2d_solver.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>
#include <complex>

using namespace std;
using namespace std::complex_literals;

void compare_and_assert(string matrixName, arma::cx_mat &C, int i, int j, std::complex<double> expected)
{
    static const double epsilon = 1.0e-15;

    std::complex<double> actual = C(i, j);
    double error = std::norm(expected - actual);

    if (error < epsilon)
    {
        std::cout << "  Test ok!" << std::endl;
    }
    else
    {
        std::cerr << "Failed unit test. Value at " << matrixName << "(" << i << "," << j << ")=" << actual << " expected: " << expected << std::endl;
    }
}

int main()
{
    // unit test for Crank Nicolson part of schrodinger_solver

    size_t Nx = 5, Ny = 5;
    arma::vec x_bound = {0, 1}, y_bound = {0, 1};
    arma::mat V_matr = arma::zeros<arma::mat>(Nx - 2, Ny - 2);

    double dt = 0.0001;

    std::cout << "\n Test 1. \n";

    double x_min = x_bound(0), x_max = x_bound(1);
    double y_min = y_bound(0), y_max = y_bound(1);

    double dx = (x_max - x_min) / (Nx - 1), dy = (y_max - y_min) / (Ny - 1);

    auto [A, B] = generate_crank_nicolson_A_and_B(V_matr, dt, dx, dy, Nx, Ny);

    // Testing a couple arbitrary values from matrces for expected values.
    // For now only one value from each matrix we know should be r and -r.
    // r is defined as i*dt/(2h^2) or for rectangular case i*dt/(2dxdy)
    // This could/should be extended to check more elemenets.
    std::complex<double> rExpected = 1i * dt / (2 * dx * dy); // should be 8.000e-04 * 1i;

    // Calculate a_4 for another test.
    size_t k = flatten_index(1, 1, Nx - 2); // is 4
    //cout << "k is " << k << endl;
    int i = 1, j = 1;
    std::complex<double> a_k = 1.0 + 4.0 * rExpected + 1i * dt * V_matr(i, j) / 2.0;
    //cout << "a_k is " << a_k << endl;

    compare_and_assert("A", A, 3, 0, -rExpected);
    compare_and_assert("B", B, 3, 0, rExpected);
    compare_and_assert("A", A, 3, 3, a_k);
}