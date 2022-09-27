
#ifndef JACOBI_ROTATE_H
#define JACOBI_ROTATE_H

#include <armadillo>

/// @brief Performs a single Jacobi rotation, to "rotate away"
// the off-diagonal element at A[k,l]
/// @param A matrix to rotate at current state
/// @param R rotation matrix at current state
/// @param k row/col rotational index
/// @param l another row/col rotational index
/// @note 
/// Code structure as suggested in task https://anderkve.github.io/FYS3150/book/projects/project2.html
/// Algoritm based partially on lecture notes and partially on page 218-220 of
/// Morten Hjorth-Jensen, Computational Physics, Lecture Notes Fall 2015
/// https://raw.githubusercontent.com/CompPhysics/ComputationalPhysics/master/doc/Lectures/lectures2015.pdf
void jacobi_rotate(arma::mat &A, arma::mat &R, size_t k, size_t l);

#endif