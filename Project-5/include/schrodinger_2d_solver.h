#ifndef SCHRODINGER_2D_SOLVER_H
#define SCHRODINGER_2D_SOLVER_H

#include <armadillo>
#include <functional>

/// @brief A function that updates a state vector using Crank-Nicolson method for Schrodinger equation;
/// Diriichlet boundary conditions are assumed;
/// hbar = 1, m = 0.5 are assumed unit-free
/// @param psi Wave state vector to be updated (of size (Nx-2)*(Ny-2))
/// @param V Potential matrix (of size (Nx-2)x(Ny-2))
/// @param dt Time step
/// @param Nx Number of grid points in x direction
/// @param Ny Number of grid points in y direction
/// @param x_bound Boundaries in x direction
/// @param y_bound Boundaries in y direction
/// @return Updated wave state vector
arma::cx_vec schrodinger_solver(const arma::cx_vec &psi, const arma::mat &V, double dt, size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound);

/// @brief A function that updates a state vector using Crank-Nicolson method for Schrodinger equation;
/// Diriichlet boundary conditions are assumed;
/// hbar = 1, m = 0.5 are assumed unit-free
/// @param psi Wave state vector to be updated (of size (Nx-2)*(Ny-2))
/// @param V Potential function
/// @param dt Time step
/// @param Nx Number of grid points in x direction
/// @param Ny Number of grid points in y direction
/// @param x_bound Boundaries in x direction
/// @param y_bound Boundaries in y direction
/// @return Updated wave state vector
arma::cx_vec schrodinger_solver(const arma::cx_vec &psi, const std::function<double(double, double)> &V, double dt, size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound);

/// @brief A cache wrapper for schrodinger_solver; All computed timesteps are saved in cache
/// @param cache A storage for state vector evolution. Must be handled by CacheWrapper
/// @param psi Initial wave state vector (of size (Nx-2)*(Ny-2))
/// @param V Potential function
/// @param dt Time step
/// @param Nx Number of grid points in x direction
/// @param Ny Number of grid points in y direction
/// @param Nt Output time (all will be saved to cache)
/// @param x_bound Boundaries in x direction
/// @param y_bound Boundaries in y direction
/// @return Updated wave state vector
arma::cx_vec schrodinger_solver_cached(arma::cx_cube &cache, const arma::cx_vec &psi, const std::function<double(double, double)> &V, double dt, size_t Nx, size_t Ny, size_t Nt, const arma::vec &x_bound, const arma::vec &y_bound);

/// @brief A function that generates the A and B matrices used in the Crank-Nicolson method for Schrodinger equation;
/// Diriichlet boundary conditions are assumed;
/// hbar = 1, m = 0.5 are assumed unit-free
/// @param V Potential matrix (of size (Nx-2)x(Ny-2))
/// @param dt Time step
/// @param dx Step length in x direction (for square matrix this is generally called h)
/// @param dy Step length in y direction
/// @param Nx Number of grid points in x direction (for square matrix this is generally called M)
/// @param Ny Number of grid points in y direction
/// @return A c++ standard tuple containin two Armadillo matrices
std::tuple<arma::cx_mat, arma::cx_mat> generate_crank_nicolson_A_and_B(const arma::mat &V, double dt, double dx, double dy, size_t Nx, size_t Ny);

#endif