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
using namespace std;
using namespace arma;

imat initRandomSpinMatrix(size_t L, uniform_real_distribution<double> &uniform_dist, mt19937 &generator)
{
	imat A = imat(L, L).ones(); // Armadillo matrix of signed integers since we only store spins -1 and 1.
	for (int i = 0; i < L; ++i)
	{
		for (int j = 0; j < L; ++j)
		{
			double r = uniform_dist(generator);
			if (r < 0.5)
			{
				A(i, j) = -1;
			}
		}
	}
	return A;
}

/*** Perform one Monte Carlo update using The Metropolis Algorithm.
 *   One spin site as chosen at random, and then another random check is made to decide if spin should flip, taking Boltzmann statistics into account.
 *   Logic taken from section 12.5 of Morten's lecture notes.
 *   Nomenclature clarification: As this is a single lattice update attempt, one "Monte Carlo cycle" requires N calls to this method.
 */
void performOneMonteCarloUpdate(imat &A, size_t L, double beta, uniform_real_distribution<double> &uniform_dist, mt19937 &generator)
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
	int spinAbove = A((randomRow - 1) % L, randomCol); // Modulus operator % makes the period boundary condition work, both ways.
	int spinBelow = A((randomRow + 1) % L, randomCol);
	int spinLeft = A(randomRow, (randomCol - 1) % L);
	int spinRight = A(randomRow, (randomCol + 1) % L);
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
	int accept = 0; // First decide if it's an accept or a reject.
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
		double probabilityRatio = exp(-beta * energyDifference);
		// TODO: As suggested in problem 2b, avoid repeatedly calling exp() by calculating the only 5 possible values beforehand, and store in some table.
		// cout << "Comparing probability ratio " << probabilityRatio << " to random number " << r << endl;
		if (probabilityRatio > r)
		{
			accept = 1;
		}
	}
	if (accept)
	{
		// In case of accept, update spin to the new (flipped) state.
		// Otherwise it's a reject and new state is just equal to old state, and no matrix change.
		A(randomRow, randomCol) = newSpin;
	}

	// cout << "Randomly updating (" << randomRow << "," <<  randomCol << ")." << endl;
	// cout << "Energy difference: " << energyDifference << " accept: " << (accept>0?"yes":"no") << endl;
}

/*** Calculates energy averaged per site.
 *   The energy is returned in units of coupling constant J.
 */
double calculateAverageEnergy(imat &A, size_t L)
{
	long totalEnergy = 0; // We do not need double until the division in the last step.

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
	return ((double)totalEnergy) / (L * L); // Divide with number of sites to get average.
}

double calculateAverageMagnetization(imat &A, size_t L)
{
	long totalSpin = 0; // We do not need double until the division in the last step.

	// First we need the total energy of the system, calculated as sum of interaction energy of all sites.
	// Loop over every single site in lattice and sum up energy due to interaction with neighbors.
	for (int i = 0; i < L; ++i)
	{
		for (int j = 0; j < L; ++j)
		{
			totalSpin += A(i, j);
		}
	}
	return fabs(((double)totalSpin) / (L * L)); // Divide with number of sites to get average.
}
