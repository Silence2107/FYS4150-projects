#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <chrono>

// We make the namespaces implicit now - benefit of short notation outweights risk for confusion/clashes.
using namespace std;
using namespace arma;

int main(int argc, char **argv)
{

	if (argc > 2)
	{
		throw std::invalid_argument("Usage: ./problem4b.exe <Temperature T>");
	}

	// For temperature T, unit is J/Kb where J is the coupling constant and Kb is Boltzmann's constant.
	// See more in https://anderkve.github.io/FYS3150/book/projects/project4.html
	double T = argc > 1 ? atof(argv[1]) : 1.0;

	double beta = 1.0 / T; // The standard beta of statistical physics 1/TKb but with the units chosen in this program Kb is already counted in.

	//Analytic formulas only for the case L=2
	//Note Both J and K_b are always 1 with our units, thus ommited from formulas.
	double Z = 4.0*cosh(8.0*beta) + 12.0;  //Partition function analytical
	double energyPerSiteAnalytical = -8.0*sinh(8.0*beta) / Z;
	double magnetismPerSiteAnalytical = (2.0*exp(8.0*beta)+4.0) / Z; 
	double specificHeatAnalytical = 64.0/(T*T) * (12.0*cosh(8.0*beta)+4) / (Z*Z); 
	double magneticSusceptibilityAnalytical = 8.0*beta/(Z*Z) * (6.0*exp(8.0*beta)+2.0*exp(-8*beta)+6);

	cout << "Analytic calculation for T=" << T << endl;
	cout << "Average energy (per spin site): " << energyPerSiteAnalytical << endl;
	cout << "Average magnetization (per spin site): " << magnetismPerSiteAnalytical << endl;
	cout << "Specific heat capacity: " << specificHeatAnalytical << endl;
	cout << "Susceptibility: " << magneticSusceptibilityAnalytical << endl; 

	int N=4;  //As we are on special case 2*2

	cout << "Specific heat capacity (per spin site): " << specificHeatAnalytical/N << endl;
	cout << "Susceptibility (per spin site): " << magneticSusceptibilityAnalytical/N << endl; 

	return 0;
}
