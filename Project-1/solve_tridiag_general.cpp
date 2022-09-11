
// inverting algorithm
#include "include/tridiag_inverter.h"
// custom file io
#include "include/file_io.h"

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
//#include <iostream>

int main(int argc, char **argv)
{
    if (argc > 3)
    {
        throw std::invalid_argument("Usage: ./solve_tridiag_general <matrix size = 1000> <output file = output.csv>");
    }
    // SETUP ---------------------------------------------------------------
    // Define the discretization size
    size_t n = argc > 1 ? std::stoi(argv[1]) : 1000;
    // Define the output file
    std::string fpath = argc > 2 ? argv[2] : "output.csv";
    // RHS function
    auto rhs_function = [](double x)
    { return 100 * exp(-10 * x); };
    // x boundaries
    double x_min = 0, x_max = 1;
    // y boundaries
    double y_min = 0, y_max = 0;
    // Define the diagonals of the matrix specific to the task
    std::vector<double> subdiag(n - 1, -1);
    std::vector<double> diag(n, 2);
    std::vector<double> superdiag(n - 1, -1);

    // START ---------------------------------------------------------------
    // Define the right hand side of the system specific to the task
    std::vector<double> rhs(n);
    // We also create an x array for the total solution
    std::vector<double> x(n);
    for (size_t i = 0; i < n; ++i)
    {
        // discretize and fill
        double step = (x_max - x_min) / static_cast<double>(n + 1);
        x[i] = x_min + (i + 1) * step;
        rhs[i] = step * step * rhs_function(x[i]);
    }
    rhs[0] += y_min;
    rhs[n - 1] += y_max;

    // ...but use the general algorithm to solve the system
    std::vector<double> v = tridiag_inverter_general(subdiag, diag, superdiag, rhs);

    // for completeness, we also add boundary conditions to the solution
    v.insert(v.begin(), y_min);
    v.push_back(y_max);
    x.insert(x.begin(), x_min);
    x.push_back(x_max);

    // write to file
    two_columns_to_csv(fpath, x, v);
}
