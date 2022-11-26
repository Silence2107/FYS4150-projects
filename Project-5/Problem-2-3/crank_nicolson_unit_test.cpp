
#include "../include/schrodinger_2d_solver.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>
#include <complex>

using namespace std;
using namespace std::complex_literals;

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

    std::complex<double> rExpected = 8.000e-04 * 1i;

    std::complex<double> error1 = rExpected - (-A(3,0));
    std::complex<double> error2 = rExpected - (B(3,0));

    double epsilon = 1.0e-15;

    if(std::norm(error1) < epsilon && std::norm(error2) < epsilon)
    {
        std::cout << "Test ok!" << std::endl;
    }
}