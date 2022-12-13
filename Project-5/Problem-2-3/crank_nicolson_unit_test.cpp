#include "../include/schrodinger_2d_solver.h"
#include "../include/auxiliaries.h"

#include <iostream>
#include <armadillo>
#include <complex>

using namespace std;
using namespace complex_literals;

void compare_and_assert(string matrixName, const arma::sp_cx_mat &C, size_t i, size_t j, complex<double> expected)
{
    static const double epsilon = 1.0e-15;

    complex<double> actual = C(i, j);
    double error = norm(expected - actual);

    if (error < epsilon)
    {
        cout << "  Test ok!" << endl;
    }
    else
    {
        cerr << "Failed unit test. Value at " << matrixName << "(" << i << "," << j << ")=" << actual << " expected: " << expected << endl;
    }
}

tuple<size_t, complex<double>, complex<double>> calc_a_k_b_k(const arma::mat &V, size_t i, size_t j, double dt, size_t Nx, complex<double> r)
{
    // By having another function here in the tests that also calculate a_k independent from the algoritm in the function we test,
    // we have some extra safe guard in detecting possible errors. (Either by typo in either file, or if future refactor accidently changes behaviour).
    size_t k = flatten_index(i, j, Nx - 2);
    complex<double> a_k = 1.0 + 4.0 * r + 1i * dt * V(i, j) / 2.0;
    complex<double> b_k = 1.0 - 4.0 * r - 1i * dt * V(i, j) / 2.0;
    cout << "k=" << k << ", ak=" << a_k << ", bk=" << b_k << endl;
    return make_tuple(k, a_k, b_k);
}

int main()
{
    // unit test for Crank Nicolson part of schrodinger_solver

    size_t Nx = 5, Ny = 5;
    arma::vec x_bound = {0, 1}, y_bound = {0, 1};

    // Better randomize V_matr now, because if set to zeroes way to make elements in A and B are equal and tests could succeed by accident.
    arma::mat V_matr = arma::mat(Nx - 2, Ny - 2, arma::fill::randu);

    double dt = 0.0001;

    cout << "\n Test 1. \n";

    double x_min = x_bound(0), x_max = x_bound(1);
    double y_min = y_bound(0), y_max = y_bound(1);

    double dx = (x_max - x_min) / (Nx - 1), dy = (y_max - y_min) / (Ny - 1);

    auto&& [A, B] = generate_crank_nicolson_A_and_B(V_matr, dt, dx, dy, Nx, Ny);

    // Testing a couple arbitrary values from matrces for expected values.
    // For now only one value from each matrix we know should be r and -r.
    // r is defined as i*dt/(2h^2) or for rectangular case i*dt/(2dxdy)
    // This could/should be extended to check more elemenets.
    complex<double> r = 1i * dt / (2 * dx * dy); // should be 8.000e-04 * 1i;

    compare_and_assert("A", A, 3, 0, -r);
    compare_and_assert("B", B, 3, 0, r);

    // Calculate some a_k for more tests.
    auto [k11, a11, b11] = calc_a_k_b_k(V_matr, 1, 1, dt, Nx, r);
    auto [k21, a21, b21] = calc_a_k_b_k(V_matr, 2, 1, dt, Nx, r);
    auto [k12, a12, b12] = calc_a_k_b_k(V_matr, 1, 2, dt, Nx, r);
    auto [k20, a20, b20] = calc_a_k_b_k(V_matr, 2, 0, dt, Nx, r);
    
    compare_and_assert("A", A, k11, k11, a11);
    compare_and_assert("A", A, k21, k21, a21);
    compare_and_assert("A", A, k12, k12, a12);
    compare_and_assert("A", A, k20, k20, a20);

    compare_and_assert("B", B, k11, k11, b11);
    compare_and_assert("B", B, k21, k21, b21);
    compare_and_assert("B", B, k12, k12, b12);
    compare_and_assert("B", B, k20, k20, b20);
}