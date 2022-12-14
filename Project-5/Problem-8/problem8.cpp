#include "../include/schrodinger_2d_solver.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"
#include "../include/many_slit_initializer.h"
#include <iostream>
#include <armadillo>

using namespace std;

int perform_simulation(int number_slits, double T, size_t grid_size);
double hard_coded_slit(double x, double y, int number_of_slits);

int main()
{
    // TODO: These things would be better to parametrize with argc,argv.

    double T = 0.002; // Time limit specified in problem 8

    int number_of_slits = 2; // Default value, it will be relevant to use 0, 1 and 3 later.

	//200x200 grid for x,y, meaning 201 x,y-points respectively. 
	//This is equivalent to saying h=0.005, also specified in problem 8.
    size_t grid_size = 200; 

    return perform_simulation(number_of_slits, T, grid_size);
}

double hard_coded_slit(double x, double y, int number_of_slits)
{
    // initialize potential to simulate wall
    static double x_center = 0.5, y_center = 0.5;
    static double x_slit_width = 0.02,
                  y_slit_width = 0.05,
                  y_slit_spacing = 0.05;
    static double wall_potential = 1e10; // approximate wall to a very large potential. Number specified as v_0 in problem 8.

    return many_slit_potential(x, y, x_center, y_center, x_slit_width, y_slit_width, y_slit_spacing, number_of_slits, wall_potential);
}

int perform_simulation(int number_of_slits, double T, size_t grid_size)
{
    // Adding 1, so for grid of 200 steps, use matrix of 201*201
    size_t Nx = grid_size + 1, Ny = grid_size + 1;

    arma::vec x_bound = {0, 1}, y_bound = {0, 1};

	//dt=2.5e-5 specified in problem 8. We have also seen that larger time steps diverges quickly from norm 1. 
    double dt = 0.000025; 
	
	//Number of time steps. +1 because we include both t=0 and t=T, so one more than number of steps. 
    size_t Nt = 1 + T / dt;

    cout << "Number of iterations to run: " << Nt << endl;

    // Making a function pointer to potential function, using function above with hardcoded values, except number of slits.
    auto V_func =
        [&number_of_slits](double x, double y)
    {
        if (number_of_slits == 0)
        {
            // Number of slits zero is used to mean no wall (so not a completely blocking wall).
            // This is intended for the part of Problem 7 when we are asked to run without potential.
            return 0.0;
        }
        else
        {
            // For non-zero number of slits we calculate an actual potential.
            return hard_coded_slit(x, y, number_of_slits);
        }
    };

    // Initialize wave function psi.
    // Picking some physical values for the wave packet.
    // For this unit test we could really use anything. However the numbers below are taken from an actual sample run we will do later.
    arma::cx_vec psi_old = initialize_particle_wavefunction(Nx, Ny, x_bound, y_bound, 0.25, 0.5, 0.05, 0.20, 200.0, 0.0);
    // Parameter list meaning x_center=0.25, y_center=0.5, spread x=0.05, spread y=0.20, px=200, py=0.
	//Numbers from problem 8. Noting difference is higher spread in y than previous problems. 

    // Setting up an Armadillo cube object, to store the probability in x/y-plane for each t.
    arma::cube probabilities_all_time_steps = arma::cube(Nx - 2, Ny - 2, Nt);

    // perform time evolution
    auto psi_new = psi_old;//schrodinger_solver(psi_old, V_func, dt, Nx, Ny, x_bound, y_bound);
    
    for (size_t t = 0; t < Nt; ++t)
    {
		//cout << "t="  << t << " time " << t*dt << endl;
        psi_new = schrodinger_solver(psi_new, V_func, dt, Nx, Ny, x_bound, y_bound);

        // calculate probability densities
        arma::cx_mat psi_new_mat = unflatten_matrix(psi_new, Nx - 2, Ny - 2);
        probabilities_all_time_steps.slice(t) = probability_matrix(psi_new_mat);
        // save the probabiltiy matrix to a csv file, for time stemps of even 50s, to have still images for a rough time progression.
		double currentTime = t*dt;
        //if (currentTime==0.0 || currentTime==1.0 || currentTime==2.0)
		if (t%40 == 0) // With our values of dt this check will hit times 0, 0.001 and 0.002 as requested.
        {
			cout << " ===== Storing probability for time value " << currentTime << endl;
            char filename[100];
            sprintf(filename, "prob%d.csv", (int)t);
            cout << "Completed " << t << " iterations. Saving current state to file " << filename << endl;
            probability_matrix(psi_new_mat).save(filename, arma::csv_ascii);
        }
    }

    // Save the cube in binary Armadillo format. This gives efficient storing of huge 3D data, and can be read by Python pyarma.
    probabilities_all_time_steps.save("data3d.out");

    std::cout << "new_norm = " << arma::norm(psi_new) << std::endl;

    // calculate probability densities

    arma::cx_mat psi_new_mat = unflatten_matrix(psi_new, Nx - 2, Ny - 2);
    arma::cx_mat psi_old_mat = unflatten_matrix(psi_old, Nx - 2, Ny - 2);

    auto psi_old_prob = probability_matrix(psi_old_mat);
    auto psi_new_prob = probability_matrix(psi_new_mat);

    std::cout << "avg. relative error = " << arma::accu(arma::abs(psi_old_prob - psi_new_prob) / psi_old_prob) / ((Nx - 2) * (Ny - 2)) << std::endl;

    return 0;
}
