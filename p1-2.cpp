#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>


double ux(double x);
int x_length=20;

int main ()
{
    // create vectors of values 0 to 1 every 0.1 
    std::vector<double> x(x_length+1);  
    std::vector<double> ux_out(x_length+1);  

    std::string filename = "output.csv";
    std::ofstream ofile;
    ofile.open(filename);

    for (double i = 0.; i < x.size(); i++)
    {
      x[i] = i/(x_length); // assign x values
      ux_out[i] = ux(x[i]); // calculate u(x)

      ofile << std::setprecision(2) << std::scientific << x[i] << "\t" << ux_out[i] << std::endl; //print to file
    }

  ofile.close();

    return 0;
}


double ux(double x)
{
    return 1 - (1 - exp(-10))*x - exp(-10*x);
}