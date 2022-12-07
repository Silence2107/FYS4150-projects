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

    double T = 0.008; // Short end time of simulation, this is for Problem 7.
    // double T = 0.02; // Longer end time of simulation, this is for Problem 8.

    int number_of_slits = 2; // Default value, it will be relevant to use 0, 1 and 3 later.
    //size_t grid_size = 200;  // 200 for good accuracy, but will take long time. Consider 50 or 100 for quicker tests. Assuming square, not worrying about rectangle grid for now.
    size_t grid_size = 100;

    return perform_simulation(number_of_slits, T, grid_size);
}

double hard_coded_slit(double x, double y, int number_of_slits)
{
    // initialize potential to simulate wall
    static double x_center = 0.5, y_center = 0.5;
    static double x_slit_width = 0.02,
                  y_slit_width = 0.05,
                  y_slit_spacing = 0.05;
    static int wall_potential = 1000000; // approximate wall to a very large potential

    return many_slit_potential(x, y, x_center, y_center, x_slit_width, y_slit_width, y_slit_spacing, number_of_slits, wall_potential);
}

int perform_simulation(int number_of_slits, double T, size_t grid_size)
{
    // Adding 1, so for grid of 200 steps, use matrix of 201*201
    size_t Nx = grid_size + 1, Ny = grid_size + 1;

    arma::vec x_bound = {0, 1}, y_bound = {0, 1};

    double dt = 0.000025; // fine dt is REQUIRED for reasonable results, however be mindful about stability
    size_t Nt = 1 + T / dt;

    cout << "Iteration number to run: " << Nt << endl;

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
    arma::cx_vec psi_old = initialize_particle_wavefunction(Nx, Ny, x_bound, y_bound, 0.25, 0.5, 0.05, 0.05, 200.0, 0.0);
    // Parameter list meaning x_center=0.25, y_center=0.5, spread x=0.05, spread y=0.05, px=200, py=0.

    // print psi_old as matrix
    arma::cx_mat psi_old_mat = arma::zeros<arma::cx_mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_old_mat(i, j) = psi_old(flatten_index(i, j, Nx - 2));
        }
    }

    // Setting up an Armadillo cube object, to store the probability in x/y-plane for each t.
    arma::cube probabilities_all_time_steps = arma::cube(Nx - 2, Ny - 2, Nt);

    // perform time evolution
    auto psi_new = schrodinger_solver(psi_old, V_func, dt, Nx, Ny, x_bound, y_bound);
    for (size_t t = 0; t < Nt; ++t)
    {
        psi_new = schrodinger_solver(psi_new, V_func, dt, Nx, Ny, x_bound, y_bound);

        // calculate probability densities
        arma::mat psi_new_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
        for (size_t i = 0; i < Nx - 2; i++)
        {
            for (size_t j = 0; j < Ny - 2; j++)
            {
                psi_new_prob(i, j) = std::norm(psi_new(flatten_index(i, j, Nx - 2)));
            }
        }
        probabilities_all_time_steps.slice(t) = psi_new_prob;
    }

    // Save the cube in binary Armadillo format. This gives efficient storing of huge 3D data, and can be read by Python pyarma.
    probabilities_all_time_steps.save("data3d.out");

    // calculate probability densities
    arma::mat psi_old_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    arma::mat psi_new_prob = arma::zeros<arma::mat>(Nx - 2, Ny - 2);
    for (size_t i = 0; i < Nx - 2; i++)
    {
        for (size_t j = 0; j < Ny - 2; j++)
        {
            psi_old_prob(i, j) = std::norm(psi_old(flatten_index(i, j, Nx - 2)));
            psi_new_prob(i, j) = std::norm(psi_new(flatten_index(i, j, Nx - 2)));

            //Squaring the results since norm is square root of the value we want: psi conjugate*psi
            psi_old_prob(i, j) = (psi_old_prob(i, j)*psi_old_prob(i, j));
            psi_new_prob(i, j) = (psi_new_prob(i, j)*psi_new_prob(i, j));
        }
    }

    std::cout << "new_norm = " << arma::norm(psi_new) << std::endl;

    // save the matrix to a csv file
    psi_old_prob.save("init_prob.csv", arma::csv_ascii);
    psi_new_prob.save("final_prob.csv", arma::csv_ascii);

    // stats
    // psi_old_prob.print("psi_old_prob = ");
    // psi_new_prob.print("psi_new_prob = ");
    std::cout << "avg. relative error = " << arma::accu(arma::abs(psi_old_prob - psi_new_prob) / psi_old_prob) / ((Nx - 2) * (Ny - 2)) << std::endl;

    return 0;
}
