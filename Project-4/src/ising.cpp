#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>

// for writing to file
#include <string>
#include <fstream>

#include "../include/ising.h"

// We make the namespaces implicit now - benefit of short notation outweights risk for confusion/clashes.
//In h-file we use the full namespace though, in order to not force every cpp-file to do this. 
using namespace std;
using namespace arma;

/*** Initialized an unordered state, every spin is set to a random number, +1 or -1 with 50% chance.
 *   	L: The width/height of the square matrix to produce. 
 * 		uniform_dist: An initialized uniform_real_distribution. 
 *      generator: A mt19937 for which the seed should be set. 
 */
imat initUnorderedSpinMatrix(size_t L, uniform_real_distribution<double> &uniform_dist, mt19937 &generator)
{
	//Start by creating an ordered Matrix, then randomly modify spins. 
	imat A = initOrderedSpinMatrix(L);
	for (int i = 0; i < L; ++i)
	{
		for (int j = 0; j < L; ++j)
		{
			double r = uniform_dist(generator);
			//Give every element in the Matrix a 50% chance to become -1 instead of 1. 
			if (r < 0.5)
			{
				A(i, j) = -1;
			}
		}
	}
	return A;
}

/*** Initialize an ordered state, every spin is set to the same state (+1). Parameters:
 *   	L: The width/height of the square matrix to produce. 
 */
imat initOrderedSpinMatrix(size_t L)
{
	return imat(L, L).ones(); // Armadillo matrix of signed integers since we only store spins -1 and 1.
}

/*** Precompute exp(-beta*deltaE) for the only 5 possible values of deltaE, and for a given T.
 */
vector<double> precomputeExpBeta(double T){
	double beta = 1.0/T; 
	vector<double> precomputedExpBeta(5);
	precomputedExpBeta[0] = exp(-beta * -8);
	precomputedExpBeta[1] = exp(-beta * 4);
	precomputedExpBeta[2] = exp(-beta * 0);
	precomputedExpBeta[3] = exp(-beta * 4);
	precomputedExpBeta[4] = exp(-beta * 8);
	return precomputedExpBeta;
}

/*** Fetch precomputed exp(-beta*deltaE) by a fancy smart lookup in previous table.
 *   Method inline for optimization. Not in h-file because only meant to be called from this file. 
 *   Grouped together here with precomputeExpBeta above, so we should remember to update code in both if we update either. 
 */
inline double getPrecomputedExpBeta(vector<double>precomputedExpBeta, int deltaE){
	//Index calculation turns -8 into index 0, -4 into index 1 etc. Oppositive to how assigned in precomputeExpBeta.
	return precomputedExpBeta[2+deltaE/4];
}

/*** Helper function to performOneMonteCarloUpdate. 
 *   Separates the logic of acceptance to it's own function. Not intended to be called from other files. 
 * */
bool metropolisAcceptRejectDecision(double energyDifference, double beta, uniform_real_distribution<double> &uniform_dist, mt19937 &generator, vector<double>& precomputedExpBeta)
{
	int accept = 0; // Default to reject and see if we find reason to accept.
	if (energyDifference <= 0.0)
	{
		// From page 404 in Mortens lecture notes we get a more efficient algorithm by immediately accepting all changes to lower energy state.
		accept = 1;
	}
	else
	{
		// For flip to higher energy, use the other formula from page 404 in Mortens lecture notes.
		// This should make the result converge to a Boltzmann distribution, and also ensure ergodicity because there is a small probability to
		// increase even to the highest allowed but unlikely states.
		double r = uniform_dist(generator);
		double probabilityRatio = 0.0;
		//As suggested in problem 2b, avoid repeatedly calling exp() by calculating the only 5 possible values beforehand.
		if(precomputedExpBeta.size()>0)   //Check if precomputed values are available, otherwise we need to compute now. 
		{
			probabilityRatio = getPrecomputedExpBeta(precomputedExpBeta, energyDifference);
		}
		else
		{
			//TODO: might be possible to delete this case eventually. 
			probabilityRatio = exp(-beta * energyDifference);
		}
		if (probabilityRatio > r)
		{
			accept = 1;
		}
	}
	return accept;
}

/*** Perform one Monte Carlo update using The Metropolis Algorithm.
 *   One spin site as chosen at random, and then another random check is made to decide if spin should flip, taking Boltzmann statistics into account.
 *   Logic taken from section 12.5 of Morten's lecture notes.
 *   Nomenclature clarification: As this is a single lattice update attempt, one "Monte Carlo cycle" requires N calls to this method.
 */
void performOneMonteCarloUpdate(imat &A, size_t L, double beta, uniform_real_distribution<double> &uniform_dist, mt19937 &generator, vector<double>& precomputedExpBeta)
{

	// Step 1. Generate a candidate state S'
	// Step 1.1 Pick a random spin (lattice site)
	int randomRow = (int)(L * uniform_dist(generator));
	int randomCol = (int)(L * uniform_dist(generator));
	// Step 1.2 Flip it (storing in local variable - we don't update the actual matrix until acceptance check).
	int oldSpin = A(randomRow, randomCol);
	int newSpin = -oldSpin;

	// Step 2. Find value of P(S')/P(Si) in an efficient way.
	// Total energy of system would require to calculate the sum of all lattice energies, but since we for this algorithm only need the difference
	// between old and new state of this particular lattice.
	// This also takes into account the notion that we should not double count neighbor interactions. The way we do this with going 4 directions from
	// the changed spin makes this correct in this case. If we instead had looped over all lattices we would have only compared right and down instead.
	// Side note: for the special case 2*2 lattice this still leads to double counting in principle, but we keep the algorithm equivalent regardless,
	// as this also makes most sense for the comparasion with analytical results.
	// Modulus operator % makes the period boundary condition work. To make it work both ways +L is needed because how modulus treat negative numbers.
	int spinAbove = A((randomRow - 1 + L) % L, randomCol); 
	int spinBelow = A((randomRow + 1 + L) % L, randomCol);
	int spinLeft = A(randomRow, (randomCol - 1 + L) % L);
	int spinRight = A(randomRow, (randomCol + 1 + L) % L);
	int sumOfNeightborSpins = spinLeft + spinRight + spinAbove + spinBelow;
	// Recall that total energy is the sum of all products -J*Sk*Sl with J coupling contant and Sk,Sl neighbors.
	// For local energy change, only take the sum of all products of flipped spin with it's 4 neighbor spins.
	// Also J is unity with our units chosen. Thus "local energy" is simply this product (note minus sign from the physical formula):
	double oldLocalEnergy = -oldSpin * sumOfNeightborSpins;
	double newLocalEnergy = -newSpin * sumOfNeightborSpins;
	double energyDifference = newLocalEnergy - oldLocalEnergy;
	// Now the probability ratio is equal to ratio of exp(-beta*energy)/Z before and after but Z cancels and the exponentials can be combined to
	// just exp(-beta*energyDifference). But we wait a few lines calculating this since it's not certain we even need this.

	// Step 3. Generate r ~ U(0,1) and carry out accept/reject steps.
	bool accept = metropolisAcceptRejectDecision(energyDifference, beta, uniform_dist, generator, precomputedExpBeta);
	if (accept)
	{
		// In case of accept, update spin to the new (flipped) state.
		// Otherwise it's a reject and new state is just equal to old state, and no matrix change.
		A(randomRow, randomCol) = newSpin;
	}

	// cout << "Randomly updating (" << randomRow << "," <<  randomCol << ")." << endl;
	// cout << "Energy difference: " << energyDifference << " accept: " << (accept>0?"yes":"no") << endl;
}

/*** Perform one Monte Carlo update using The Metropolis Algorithm.
 *   One spin site as chosen at random, and then another random check is made to decide if spin should flip, taking Boltzmann statistics into account.
 *   Logic taken from section 12.5 of Morten's lecture notes.
 *   Nomenclature clarification: As this is a single lattice update attempt, one "Monte Carlo cycle" requires N calls to this method.
 */
void performOneMonteCarloUpdate(imat &A, size_t L, double beta, uniform_real_distribution<double> &uniform_dist, mt19937 &generator){
	vector<double> emptyVector(0);
	return performOneMonteCarloUpdate(A, L, beta, uniform_dist, generator, emptyVector);
}

/*** Calculates total energy.
 *   The energy is returned in units of coupling constant J.
 */
double calculateTotalEnergy(imat &A, size_t L)
{
	long totalEnergy = 0; // We do not need double until the last step.

	// First we need the total energy of the system, calculated as sum of interaction energy of all sites.
	// Loop over every single site in lattice and sum up energy due to interaction with neighbors.
	for (int i = 0; i < L; ++i)
	{
		for (int j = 0; j < L; ++j)
		{
			int thisSpin = A(i, j);
			int spinBelow = A((i + 1) % L, j);
			int spinRight = A(i, (j + 1) % L);
			// The idea is similar to the partial energies in performOneMonteCarloUpdate, but here we instead only
			// calculate interactions going right and down, and thus avoid double counting.
			// The modulus operator % again make the periodic boundary condition work as it should.
			totalEnergy += -thisSpin * (spinRight + spinBelow);
		}
	}
	return (double)totalEnergy; 
}

/*** Calculates total magnetization.
 *   The unit is just the same dimensionless unit as spins.
 */
double calculateTotalAbsoluteMagnetization(imat &A, size_t L)
{
	long totalSpin = 0; // We do not need double until the last step.

	// First we need the total energy of the system, calculated as sum of interaction energy of all sites.
	// Loop over every single site in lattice and sum up energy due to interaction with neighbors.
	for (int i = 0; i < L; ++i)
	{
		for (int j = 0; j < L; ++j)
		{
			totalSpin += A(i, j);
		}
	}
	return fabs(((double)totalSpin)); 
}
