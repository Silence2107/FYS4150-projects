
#ifndef EIGEN_LINALG_H
#define EIGEN_LINALG_H

#include <armadillo>
#include <vector>

/// @brief This function finds the largest (by abs val) off-diagonal element in a symmetric matrix
/// @param A Input matrix (expected to be symmetric, no check is performed)
/// @param row Output row index of the largest element (pass by ref); row < col
/// @param col Output column index of the largest element (pass by ref); row < col
/// @return A[row, col]
/// @note It does not have a lot of sense to put this function in outer scope, but for academic purposes we will
double abs_max_offdiag_for_symmetric(const arma::mat &A, size_t &row, size_t &col);

/// @brief Performs a single Jacobi rotation, to "rotate away"
// the off-diagonal element at A[k,l]
/// @param A matrix to rotate at current state (expected square and symmetric, no check is performed)
/// @param R rotation matrix at current state
/// @param k row/col rotational index
/// @param l another row/col rotational index
/// @note
/// Code structure as suggested in task https://anderkve.github.io/FYS3150/book/projects/project2.html
/// Algoritm based partially on lecture notes and partially on page 218-220 of
/// Morten Hjorth-Jensen, Computational Physics, Lecture Notes Fall 2015
/// https://raw.githubusercontent.com/CompPhysics/ComputationalPhysics/master/doc/Lectures/lectures2015.pdf
/// It does not have a lot of sense to put this function in outer scope, but for academic purposes we will
void jacobi_rotate(arma::mat &A, arma::mat &R, size_t k, size_t l);

/// @brief Performs Jacobi rotations until the largest off-diagonal element is smaller than eps
/// @param A matrix to rotate
/// @param eps threshold for the largest off-diagonal element
/// @param eigenvalues vector of eigenvalues (pass by ref)
/// @param eigenvectors matrix of eigenvectors (pass by ref)
/// @param maxiter maximum number of iterations
/// @param iterations number of iterations performed (pass by ref)
/// @param converged true if converged, false otherwise (pass by ref)
/// @note usually we do not need that much details, but ok
void jacobi_eigensolver(const arma::mat &A, double eps, arma::vec &eigenvalues, arma::mat &eigenvectors,
                        const int maxiter, int &iterations, bool &converged);

#endif
