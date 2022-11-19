#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>

//for writing to file
#include <string>
#include <fstream>


//Following convention in examples like https://github.com/anderkve/FYS3150/blob/master/code_examples/random_number_generation/main_rng_in_class_omp.cpp
//we now consider us ready to use implicit namespaces. 
using namespace std;
using namespace arma;

imat initRandomSpinMatrix(size_t L, uniform_real_distribution<double> uniform_dist, mt19937 generator)
{
	imat A = imat(L, L).ones();
	
	for (int i = 0; i < L; ++i)
    {
        for (int j = 0; j < L; ++j)
        {
			
			double r = uniform_dist(generator);
			if (r < 0.5)
			{
				A(i,j) = -1;
			}
            //cout << spin[i][j] << "    ";
        }
    //    cout << endl;
    }

	return A;
}

/*** Perform one cycle of Monte Carlo update using The Metropolis Algorithm.
 *   One spin site as chosen at random, and then another random check is made to decide if spin should flip, taking Boltzmann statistics into account. 
 *   Logic taken from section 12.5 of Morten's lecture notes. 
 */
void performOneMonteCarloCycle(imat& A, size_t L, double beta, uniform_real_distribution<double> uniform_dist, mt19937 generator){
	int randomRow = (L*uniform_dist(generator));
	int randomCol = (L*uniform_dist(generator));
	
	cout << "Randomly updating (" << randomRow << "," <<  randomCol << ")." << endl;
	
	A(randomRow, randomCol) = 2.0;
}

int main()
{

    //double eps = 1.0 * pow(10, -8);
    //double h = 0.1;
    //int N = 10;
	size_t L = 2; //Hard lattice size 2 for now. TODO: parameterize
	
	//size_t N=L*L;
	
	double T = 1.0;  //Hard coded temperature 1 for now. TODO: parameterize
	//Unit is J/Kb where J is the coupling constant mentioned in https://anderkve.github.io/FYS3150/book/projects/project4.html and Kb is Boltzmann's constant. 
	
	double beta = 1.0/T;  //The standard beta of statistical physics 1/TKb but with the units chosen in this program Kb is already counted in. 

	//Random number setup in the way recommended for parallell computing, at https://github.com/anderkve/FYS3150/blob/master/code_examples/random_number_generation/main_rng_in_class_omp.cpp
	// Use the system clock to get a base seed
	unsigned int base_seed = chrono::system_clock::now().time_since_epoch().count();
	// Member variables that hold a <random> generator 
	// and distribution (uniform distribution [0,1)).
	mt19937 generator;
	uniform_real_distribution<double> uniform_dist = uniform_real_distribution<double>(0.0 ,1.0);
	//my_walker.generator.seed(my_seed);
	generator.seed(base_seed);
  
	imat Aints = initRandomSpinMatrix(L, uniform_dist, generator);
	
	performOneMonteCarloCycle(Aints, L, beta, uniform_dist, generator);
	
    // initialize random
    //srand(time(0));
/*
    arma::mat R = arma::mat(L, N).eye();
    // Generate random N*N matrix
    arma::mat A = arma::mat(N, N).randn();*/
	//arma::imat Aints = arma::imat(L, L).ones();//randn();
	
	
    std::cout << "Aints:" << std::endl;
    std::cout << std::setprecision(4) << Aints << std::endl;
	
    return 0;
}
