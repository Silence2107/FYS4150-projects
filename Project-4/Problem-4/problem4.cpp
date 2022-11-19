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

	imat latticeMatrix = initRandomSpinMatrix(L, uniform_dist, generator);

	if (L < 10)
	{
		cout << "Before:" << endl;
		cout << setprecision(4) << latticeMatrix << endl;
	}
	for (int i = 0; i < monteCarlCyclesToRun; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// Each Monte Carlo "cycle" is N attempted updates.
			// Note that N is the number of sites, but it does not mean we attempt every site. The randomness might attempt the same site
			// multiple times but this is what we want, as it avoids unwanted correlation between transitions.
			performOneMonteCarloUpdate(latticeMatrix, L, beta, uniform_dist, generator);
		}
		if ((i + 1) % 10 == 0)
		{
			cout << (i + 1) << " iterations run" << endl;
		}
		// double avgEnergy = calculateAverageEnergy(latticeMatrix, L);
		// double avgMagnetization = calculateAverageMagnetization(latticeMatrix, L);
		// TODO: For specificHeat and magneticSusceptibility, need to store each of these avgEnergy and avgMagnetization
		// in a vector here, to later calculate standard deviation of these.
	}

	if (L < 10)
	{
		cout << "After:" << endl;
		cout << setprecision(4) << latticeMatrix << endl;
	}

	cout << "Average energy: " << calculateAverageEnergy(latticeMatrix, L) << endl;
	cout << "Average magnetization: " << calculateAverageMagnetization(latticeMatrix, L) << endl;

	return 0;
}
