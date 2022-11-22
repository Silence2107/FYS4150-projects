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

int main(int argc, char **argv)
{

	if (argc > 4)
	{
		throw std::invalid_argument("Usage: ./ising.exe <L width of lattice> <T temperature in J/Kb> <Number MC cycles>");
	}

	// Read program parameters, with default values L=2, eps=1e-8 and maxIterations=1e5 if not specified.
	// L is the width and height of the square lattice of spin sites we calculate on.
	size_t L = argc > 1 ? atof(argv[1]) : 2;
	// For temperature T, unit is J/Kb where J is the coupling constant and Kb is Boltzmann's constant.
	// See more in https://anderkve.github.io/FYS3150/book/projects/project4.html
	double T = argc > 2 ? atof(argv[2]) : 1.0;
	// How many Monte Carlo cylces to run before actually start recording samples.
	int monteCarlCyclesToRun = argc > 3 ? atof(argv[3]) : 1000;

	double beta = 1.0 / T; // The standard beta of statistical physics 1/TKb but with the units chosen in this program Kb is already counted in.
	size_t N = L * L;	   // Total number of sites in lattice.

	// TODO: Use later: int burnInNumber = 0;  //How many Monte Carlo cylces to run before actually start recording samples.

	// Random number setup in the way recommended for parallell computing, at https://github.com/anderkve/FYS3150/blob/master/code_examples/random_number_generation/main_rng_in_class_omp.cpp
	//  Use the system clock to get a base seed
	unsigned int base_seed = chrono::system_clock::now().time_since_epoch().count();
	// Member variables that hold a <random> generator
	// and distribution (uniform distribution [0,1)).
	mt19937 generator;
	uniform_real_distribution<double> uniform_dist = uniform_real_distribution<double>(0.0, 1.0);
	// generator.seed(my_seed);  //TODO: Once we get to parallellization we will use thread number here.
	generator.seed(base_seed);

	// Setting a random starting matrix. The other alternative is initOrderedSpinMatrix, that will be useful for problem 5b.
	imat latticeMatrix = initUnorderedSpinMatrix(L, uniform_dist, generator);

	// Show the Matrix in stdout, only if small enough to easily fit screen.
	if (L < 10)
	{
		cout << "Before:" << endl;
		cout << setprecision(4) << latticeMatrix << endl;
	}

	// Set up vectors to store physical quantities for each Monte Carlo cycle.
	std::vector<double> everyE(monteCarlCyclesToRun);
	std::vector<double> everyE2(monteCarlCyclesToRun);
	std::vector<double> everyM(monteCarlCyclesToRun);
	std::vector<double> everyM2(monteCarlCyclesToRun);

	for (int i = 0; i < monteCarlCyclesToRun; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// Each Monte Carlo "cycle" is N attempted updates (also called Monte Carl samplings).
			// Note that N is the number of sites, but it does not mean we attempt every site. The randomness might attempt the same site
			// multiple times but this is what we want, as it avoids unwanted correlation between transitions.
			performOneMonteCarloUpdate(latticeMatrix, L, beta, uniform_dist, generator);
		}

		// Every Monto Carl cycle produces one sample. We calculate the avarage and variance of energy and magnetization
		// by storing the value of E, E^2, M and M^2 here, for each loop step, i a vector.
		// TODO: Make sure this is the correct approach. I'm alittle unsure of avarage is to be taken over these samples, or if we should
		// have taken avarage over every single N update inside function performOneMonteCarloUpdate.

		double E = calculateTotalEnergy(latticeMatrix, L);
		double M = calculateTotalAbsoluteMagnetization(latticeMatrix, L);

		// We could also optimize just keep the total sum, and perform addition in each loop step, but to start with it is useful to be able to plot everything.
		everyE[i] = E / N;
		everyM[i] = M / N;
		everyE2[i] = everyE[i]*everyE[i];
		everyM2[i] = everyM[i]*everyM[i];
	}

	// Now we can calculate avarage values of quantities and quantities squared.
	double averageE = std::accumulate(everyE.begin(), everyE.end(), 0.0) / monteCarlCyclesToRun;
	double averageM = std::accumulate(everyM.begin(), everyM.end(), 0.0) / monteCarlCyclesToRun;
	double averageE2 = std::accumulate(everyE2.begin(), everyE2.end(), 0.0) / monteCarlCyclesToRun;
	double averageM2 = std::accumulate(everyM2.begin(), everyM2.end(), 0.0) / monteCarlCyclesToRun;

	//Multiplication with N is done last here, actually canceling the fact that we divided with N^2 before,
	//(whereas the real formula has division by N) so now we get back to the correct factor of Ns.
	//The reason is just that it seems more numerically stable in this way. 
	double energyPerSite = averageE;
	double specificHeatPerSite = (averageE2 - averageE * averageE) / (T * T) * N;
	double magnetizationPerSite = averageM;
	double magneticSusceptibilityPerSite = (averageM2 - averageM * averageM) / T * N;

	if (L < 10)
	{
		cout << "After:" << endl;
		cout << setprecision(4) << latticeMatrix << endl;
	}

	//Increasing precision again before printing interesting quantities. Otherwise too few decimals to compare with analytical result.
	cout << setprecision(8);

	cout << "All states Average energy (per spin site): " << energyPerSite << endl;
	//cout << "Last state Average energy (per spin site): " << calculateTotalEnergy(latticeMatrix, L) / (L * L) << endl;

	cout << "All states Average magnetization (per spin site): " << magnetizationPerSite << endl;
	//cout << "Last state Average magnetization (per spin site): " << calculateTotalAbsoluteMagnetization(latticeMatrix, L) / (L * L) << endl;

	cout << "Specific heat capacity (per spin site): " << specificHeatPerSite << endl;
	cout << "Susceptibility (per spin site): " << magneticSusceptibilityPerSite << endl;

	return 0;
}
