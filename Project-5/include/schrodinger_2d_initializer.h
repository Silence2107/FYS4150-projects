#ifndef SCHRODINGER_2D_INITIALIZER_H
#define SCHRODINGER_2D_INITIALIZER_H

#include <armadillo>
#include <functional>

/// @brief A function that initializes a matrix for a start state of a particle wave function, given some physical properties.
/// Result is also normalized. 
/// @param dx Step length in x direction (for square matrix this is generally called h)
/// @param dy Step length in y direction
/// @param Nx Number of grid points in x direction (for square matrix this is generally called M)
/// @param Ny Number of grid points in y direction
/// @return A c++ standard tuple containin two Armadillo matrices
arma::cx_mat initialize_particle_wavefunction(size_t Nx, size_t Ny, double dx, double dy, double x_center, double y_center, double x_spread, double y_spread, double px, double py);

#endif