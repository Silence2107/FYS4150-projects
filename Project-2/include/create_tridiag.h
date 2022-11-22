#ifndef CREATE_TRIDIAGONAL
#define CREATE_TRIDIAGONAL

#include <armadillo>
#include <cmath>

/// @brief Creates a problem-specific tridiagonal matrix with N elements and structure -1/h^2, 2/h^2, -1/h^2
/// @param N Size of matrix
/// @param h Step size that is used for elements calculation
/// @return Tridiagonal matrix
arma::mat create_tridiagonal(int N, double h);

#endif