
#include "../include/many_slit_initializer.h"
#include <armadillo>
#include <cmath>

int main(int argc, char** argv)
{
    // initialize potential to simulate wall

    double x_center = 0.5, y_center = 0.5;
    double x_slit_width = 0.02,
           y_slit_width = 0.05,
           y_slit_spacing = 0.05;
    int wall_potential = 1000000; // approximate wall to a very large potential
    size_t number_of_slits = std::stoi(argv[1]); // number of slits


    // establish the probe potential 
    // (this is how you should do it in the program when you want to use the potential for schrodinger simulation)
    auto specific_double_slit = [&](double x, double y) {
        return many_slit_potential(x, y, x_center, y_center, x_slit_width, y_slit_width, y_slit_spacing, number_of_slits, wall_potential);
    };

    // as per this unit test, I would like to store the potential in a csv matrix, and then plot it via matplotlib

    // create a matrix to store the potential
    arma::mat potential_matrix(100, 100);

    // fill the matrix with the potential
    for (size_t i = 0; i < potential_matrix.n_rows; i++)
    {
        for (size_t j = 0; j < potential_matrix.n_cols; j++)
        {
            potential_matrix(i, j) = specific_double_slit(i / 100.0, j / 100.0);
        }
    }

    // save the matrix to a csv file
    potential_matrix.save("data.csv", arma::csv_ascii);
}