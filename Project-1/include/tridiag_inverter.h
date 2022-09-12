
#ifndef TRIDIAG_INVERTER_H
#define TRIDIAG_INVERTER_H

#include <vector>

/// @brief Solves a tridiagonal system of equations {a,b,c} * v = g using the Thomas algorithm
/// @param subdiag The subdiagonal of the matrix of size n-1
/// @param diag The diagonal of the matrix of size n
/// @param superdiag The superdiagonal of the matrix of size n-1
/// @param rhs The right hand side of the system of size n
/// @return The solution to the system of equations of size n
std::vector<double> tridiag_inverter_general(const std::vector<double> &subdiag, const std::vector<double> &diag, const std::vector<double> &superdiag, const std::vector<double> &rhs);

#endif