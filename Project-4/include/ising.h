#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>

arma::imat initRandomSpinMatrix(size_t L, std::uniform_real_distribution<double>& uniform_dist, std::mt19937& generator);

/*** Perform one Monte Carlo update using The Metropolis Algorithm.
 *   One spin site as chosen at random, and then another random check is made to decide if spin should flip, taking Boltzmann statistics into account. 
 *   Logic taken from section 12.5 of Morten's lecture notes. 
 *   Nomenclature clarification: As this is a single lattice update attempt, one "Monte Carlo cycle" requires N calls to this method.
 */
void performOneMonteCarloUpdate(arma::imat& A, size_t L, double beta, std::uniform_real_distribution<double>& uniform_dist, std::mt19937& generator);

/*** Calculates energy averaged per site.
 *   The energy is returned in units of coupling constant J. 
 */
double calculateAverageEnergy(arma::imat& A, size_t L);

double calculateAverageMagnetization(arma::imat& A, size_t L);
