#include "../include/schrodinger_2d_solver.h"
#include "../include/schrodinger_2d_initializer.h"
#include "../include/auxiliaries.h"
#include "../include/many_slit_initializer.h"
#include "../include/file_io.h"
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

    // 200x200 grid for x,y, meaning 201 x,y-points respectively.
    // This is equivalent to saying h=0.005, also specified in problem 8.
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
    static double wall_potential = 1e10; // approximate wall to a very large potential. Number specified as v_0 in problem 8.

    return many_slit_potential(x, y, x_center, y_center, x_slit_width, y_slit_width, y_slit_spacing, number_of_slits, wall_potential);
}

int perform_simulation(int number_of_slits, double T, size_t grid_size)
{
    // Adding 1, so for grid of 200 steps, use matrix of 201*201
    size_t Nx = grid_size + 1, Ny = grid_size + 1;

    arma::vec x_bound = {0, 1}, y_bound = {0, 1};

    // dt=2.5e-5 specified in problem 8. We have also seen that larger time steps diverges quickly from norm 1.
    double dt = 0.000025;

    // Number of time steps. +1 because we include both t=0 and t=T, so one more than number of steps.
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
    // Numbers from problem 8. Noting difference is higher spread in y than previous problems.

    // perform time evolution
    auto psi_new = psi_old;
    for (size_t t = 0; t < Nt; ++t)
    {
        // cout << "t="  << t << " time " << t*dt << endl;
        if (t != 0) // Special case because we want to store initial conditition as first slice/outputfile.
        {
            psi_new = schrodinger_solver(psi_new, V_func, dt, Nx, Ny, x_bound, y_bound);
        }

        // calculate probability densities
        arma::cx_mat psi_new_mat = unflatten_matrix(psi_new, Nx - 2, Ny - 2);

        // save the probabiltiy matrix to a csv file, for time stemps of even 50s, to have still images for a rough time progression.
        double currentTime = t * dt;

        if (t == 80) // This is t=0.002 the requested time to check probability at screen in problem 9.
        {
            // We want to pick out all probabilities along y, at the line x=0.8 where we state that the screen is located.
            // This is done by finding the colunm of the matrix matchines this, knowing columns ranges from x and y 0 to 1.
            size_t column_number_representing_location_of_screen = 0.8 * Nx;

            cout << "Picking out matrix row " << column_number_representing_location_of_screen << endl;

            // auto probability_column_at_screen = probability_matrix(psi_new_mat.col(column_number_representing_location_of_screen));
            auto probability_column_at_screen = probability_matrix(psi_new_mat.row(column_number_representing_location_of_screen));
            cout << probability_column_at_screen << endl;
            cout << "norm:" << arma::norm(probability_column_at_screen) << endl;
            probability_column_at_screen = probability_column_at_screen / arma::norm(probability_column_at_screen);
            cout << probability_column_at_screen << endl;
            cout << "size y" << probability_column_at_screen.size() << endl;

            double h = 1.0 / grid_size;
            // auto x_vector = arma::linspace(h, 1.0-h, h);
            auto x_vector = arma::regspace(h, h, 1.0);

            cout << "h=" << h << " to " << (1.0 - h) << " X_vector is " << x_vector << endl;
            cout << "size x" << x_vector.size() << endl;

            std::vector<double> probabilities(Ny),
                y_values(Ny);
            for (size_t i = 0; i < Ny; i++)
            {
                // std::cout << "Processing time step " << i << " of " << Nt << std::endl;
                // psi = schrodinger_solver(psi, potential, dt, Nx, Ny, x_bound, y_bound);
                if (i == 0 || i == Ny - 1)
                {
                    probabilities[i] = 0.0;
                }
                else
                {
                    probabilities[i] = probability_column_at_screen[i - 1];
                }
                y_values[i] = i * h;
            }
            // normalize probability by the area under the curve
            double sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
            for (size_t i = 0; i < Ny; ++i)
            {
                probabilities[i] /= (sum * h);
            }

            two_columns_to_csv("screen.csv", y_values, probabilities);
        }
    }

    // Final normal should be reasonably close to 1. Problem 7 dealth more with monitoring this over every time step.
    std::cout << "Final norm = " << arma::norm(psi_new) << std::endl;

    return 0;
}
