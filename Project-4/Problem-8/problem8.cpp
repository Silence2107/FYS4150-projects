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

#include "omp.h" // OpenMP header

#include "../include/ising.h"

// We make the namespaces implicit now - benefit of short notation outweights risk for confusion/clashes.
using namespace std;
using namespace arma;

int main(int argc, char **argv)
{

	if (argc > 4)
	{
		throw std::invalid_argument("Usage: ./ising.exe <L width of lattice> <Number MC cycles>");
	}

	// Read program parameters, with default values L=2, eps=1e-8 and maxIterations=1e5 if not specified.
	// L is the width and height of the square lattice of spin sites we calculate on.
	size_t L = argc > 1 ? atof(argv[1]) : 2;
	//	// For temperature T, unit is J/Kb where J is the coupling constant and Kb is Boltzmann's constant.
	//	// See more in https://anderkve.github.io/FYS3150/book/projects/project4.html
	//	double T = argc > 2 ? atof(argv[2]) : 1.0;
	// How many Monte Carlo cylces to run before actually start recording samples.
	int monteCarlCyclesToRun = argc > 2 ? atof(argv[2]) : 1000;

	size_t N = L * L; // Total number of sites in lattice.

	// TODO: Use later: int burnInNumber = 0;  //How many Monte Carlo cylces to run before actually start recording samples.

	// Random number setup in the way recommended for parallell computing, at https://github.com/anderkve/FYS3150/blob/master/code_examples/random_number_generation/main_rng_in_class_omp.cpp
	//  Use the system clock to get a base seed
	unsigned int base_seed = chrono::system_clock::now().time_since_epoch().count();
	// Member variables that hold a <random> generator
	// and distribution (uniform distribution [0,1)).

#pragma omp parallel // Start parallel region
	{
		// Which thread is this?
		int thread_id = omp_get_thread_num();

		// Create a <random> generator and distribution (uniform distribution [0,1) ).
		// private to this thread
		mt19937 generator;
		uniform_real_distribution<double> uniform_dist = uniform_real_distribution<double>(0.0, 1.0);

		// Seed the generator with a seed that is unique for this thread
		unsigned int my_seed = base_seed + thread_id;
		generator.seed(my_seed);

		int numTempSteps = 11;
		double tempStep = 0.1;
		double startTemp = 1.5;
#pragma omp for
		// for(double T=1.0; T<=4; T+=0.1)
		for (int t = 0; t < numTempSteps; ++t)
		// for (double T = 1.9; T <= 2.5; T += 0.1)
		{
			// Looping over integers because that works better with OpenMP and then turn integers into double type temperature.
			double T = startTemp + t * tempStep;

			double beta = 1.0 / T; // The standard beta of statistical physics 1/TKb but with the units chosen in this program Kb is already counted in.

			// Setting a random starting matrix. The other alternative is initOrderedSpinMatrix, that will be useful for problem 5b.
			imat latticeMatrix = initUnorderedSpinMatrix(L, uniform_dist, generator);

			// Set up vectors to store physical quantities for each Monte Carlo cycle.
			std::vector<double> everyE(monteCarlCyclesToRun);
			std::vector<double> everyE2(monteCarlCyclesToRun);
			std::vector<double> everyM(monteCarlCyclesToRun);
			std::vector<double> everyM2(monteCarlCyclesToRun);

			vector<double> precomputedExpBeta = precomputeExpBeta(T);

			for (int i = 0; i < monteCarlCyclesToRun; i++)
			{
				for (int j = 0; j < N; j++)
				{
					// Each Monte Carlo "cycle" is N attempted updates (also called Monte Carl samplings).
					// Note that N is the number of sites, but it does not mean we attempt every site. The randomness might attempt the same site
					// multiple times but this is what we want, as it avoids unwanted correlation between transitions.
					performOneMonteCarloUpdate(latticeMatrix, L, beta, uniform_dist, generator, precomputedExpBeta);
				}

				// Every Monto Carl cycle produces one sample. We calculate the avarage and variance of energy and magnetization
				// by storing the value of E, E^2, M and M^2 here, for each loop step, i a vector.
				// TODO: Make sure this is the correct approach. I'm alittle unsure of avarage is to be taken over these samples, or if we should
				// have taken avarage over every single N update inside function performOneMonteCarloUpdate.

				double E = calculateTotalEnergy(latticeMatrix, L);
				double M = calculateTotalAbsoluteMagnetization(latticeMatrix, L);

				// We could also optimize just keep the total sum, and perform addition in each loop step, but to start with it is useful to be able to plot everything.
				everyE[i] = E;
				everyM[i] = M;
				everyE2[i] = E * E;
				everyM2[i] = M * M;
			}

			// Now we can calculate avarage values of quantities and quantities squared.
			double averageE = std::accumulate(everyE.begin(), everyE.end(), 0.0) / monteCarlCyclesToRun;
			double averageM = std::accumulate(everyM.begin(), everyM.end(), 0.0) / monteCarlCyclesToRun;
			double averageE2 = std::accumulate(everyE2.begin(), everyE2.end(), 0.0) / monteCarlCyclesToRun;
			double averageM2 = std::accumulate(everyM2.begin(), everyM2.end(), 0.0) / monteCarlCyclesToRun;

			double energyPerSite = averageE / N;
			double magnetizationPerSite = averageM / N;

			double specificHeatPerSite = (averageE2 - averageE * averageE) / (T * T * N * N);
			double magneticSusceptibilityPerSite = (averageM2 - averageM * averageM) / (T * N * N);

#pragma omp critical // <-- Code in a "ciritical block" is only run one thread at a time. Avoids garbled screen output.
			{
				cout << "=====================================================================" << endl;
				cout << "For temperature T=" << T << endl;
				cout << "All states Average energy (per spin site): " << energyPerSite << endl;

				cout << "All states Average magnetization (per spin site): " << magnetizationPerSite << endl;

				cout << "Specific heat capacity (per spin site): " << specificHeatPerSite << endl;
				cout << "Susceptibility (per spin site): " << magneticSusceptibilityPerSite << endl;
			}
		} // End parallelized loop over T

	} // End entire parallel region

	return 0;
}
