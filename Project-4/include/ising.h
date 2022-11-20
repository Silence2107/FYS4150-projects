#ifndef FILE_IO_H
#define FILE_IO_H

#include <iostream>
#include <armadillo>

/*** Initialized an unordered state, every spin is set to a random number, +1 or -1 with 50% chance.
 *   	L: The width/height of the square matrix to produce. 
 * 		uniform_dist: An initialized uniform_real_distribution. 
 *      generator: A mt19937 for which the seed should be set. 
 */
arma::imat initUnorderedSpinMatrix(size_t L, std::uniform_real_distribution<double>& uniform_dist, std::mt19937& generator);

/*** Initialize an ordered state, every spin is set to the same state (+1). Parameters:
 *   	L: The width/height of the square matrix to produce. 
 */
arma::imat initOrderedSpinMatrix(size_t L);

/*** Perform one Monte Carlo update using The Metropolis Algorithm.
 *   One spin site as chosen at random, and then another random check is made to decide if spin should flip, taking Boltzmann statistics into account.
 *   Logic taken from section 12.5 of Morten's lecture notes.
 *   Nomenclature clarification: As this is a single lattice update attempt, one "Monte Carlo cycle" requires N calls to this method.
 */
void performOneMonteCarloUpdate(arma::imat &A, size_t L, double beta, std::uniform_real_distribution<double> &uniform_dist, std::mt19937 &generator, std::vector<double>& precomputedExpBeta);


/*** Perform one Monte Carlo update using The Metropolis Algorithm.
 *   The same as the method above but does not utlize the new precomputed beta feature so this one is slower.
 */
void performOneMonteCarloUpdate(arma::imat& A, size_t L, double beta, std::uniform_real_distribution<double>& uniform_dist, std::mt19937& generator);

/*** Calculates energy averaged per site.
 *   The energy is returned in units of coupling constant J. 
 */
//double calculateAverageEnergy(arma::imat& A, size_t L);
//double calculateAverageMagnetization(arma::imat& A, size_t L);

/*** Calculates total energy.
 *   The energy is returned in units of coupling constant J.
 */
double calculateTotalEnergy(arma::imat &A, size_t L);

/*** Calculates total magnetization.
 *   The unit is just the same dimensionless unit as spins.
 */
double calculateTotalAbsoluteMagnetization(arma::imat &A, size_t L);

/*** Precompute exp(-beta*deltaE) for the only 5 possible values of deltaE, and for a given T.
 */
std::vector<double> precomputeExpBeta(double T);

#endif
