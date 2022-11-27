#ifndef SCHRODINGER_2D_INITIALIZER_H
#define SCHRODINGER_2D_INITIALIZER_H

#include <armadillo>
#include <functional>

/// @brief A function that initializes a vector for a start state of a particle wave function, given some physical properties.
/// The wave function will be in the shape of a wave packet concentrated around some position and momentum.
/// The format of this vector is a flattened Nx*Ny vector, representing the 2D grid in a 1D data type.
/// Result is also normalized, as is customary with wave functions.
/// @param Nx Number of grid points in x direction (for square matrix this is commonly called M)
/// @param Ny Number of grid points in y direction
/// @param dx Step length in x direction (for square matrix this is commonly called h)
/// @param dy Step length in y direction
/// @param x_center Centre of initial wave packet in x direction
/// @param y_center Centre of initial wave packet in y direction
/// @param x_spread Centre of initial wave packet in x direction
/// @param y_spread Centre of initial wave packet in y direction
/// @param px Spread of initial wave packet in x direction
/// @param py Spread of initial wave packet in y direction
/// @param dx Wave packet momentum in x direction
/// @param dy Wave packet momentum in y direction
/// @return A complex Armadillo vector containing the wave function.
arma::cx_vec initialize_particle_wavefunction(size_t Nx, size_t Ny, double dx, double dy, double x_center, double y_center,
                                              double x_spread, double y_spread, double px, double py);

#endif