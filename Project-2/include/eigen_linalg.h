
#ifndef EIGEN_LINALG_H
#define EIGEN_LINALG_H

#include<armadillo>
#include<vector>

/// @brief This function finds the largest (by abs val) off-diagonal element in a symmetric matrix
/// @param A Input matrix (expected to be symmetric, no check is performed)
/// @param row Output row index of the largest element (pass by ref); row < col
/// @param col Output column index of the largest element (pass by ref); row < col
/// @return A[row, col]
/// @note It does not have a lot of sense to put this function in outer scope, but for academic purposes we will
double abs_max_offdiag_for_symmetric(const arma::mat &A, size_t &row, size_t &col);

#endif
