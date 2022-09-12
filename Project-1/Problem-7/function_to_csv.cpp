#include "../include/file_io.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>

double ux(double x);

int main(int argc, char **argv)
{
  if (argc > 3)
  {
    throw std::invalid_argument("Usage: ./function_to_csv <discretization size = 1000> <output file = output.csv>");
  }
  size_t n = argc > 1 ? std::stoi(argv[1]) : 1000;
  std::string fpath = argc > 2 ? argv[2] : "output.csv";

  // create vectors of values 0 to 1 every 1/n
  std::vector<double> x(n + 1);
  std::vector<double> ux_out(n + 1);

  for (double i = 0.; i < x.size(); i++)
  {
    x[i] = i / n; // assign x values
    ux_out[i] = ux(x[i]);  // calculate u(x)
  }

  // write to file
  two_columns_to_csv(fpath, x, ux_out);

  return 0;
}

double ux(double x)
{
  return 1 - (1 - exp(-10)) * x - exp(-10 * x);
}