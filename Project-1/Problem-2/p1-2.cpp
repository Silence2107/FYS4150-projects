#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>


double ux(double x);
int n=100;

int main ()
{
    // create vectors of values 0 to 1 every 1/n
    std::vector<double> x(n+1);  
    std::vector<double> ux_out(n+1);  

    std::string filename = "out_p1-2.csv";
    std::ofstream ofile;
    ofile.open(filename);

    for (double i = 0.; i < x.size(); i++)
    {
      x[i] = i/(n); // assign x values
      ux_out[i] = ux(x[i]); // calculate u(x)

      ofile << std::setprecision(2) << std::scientific << x[i] << "," << ux_out[i] << std::endl; //print to file
    }

  ofile.close();

    return 0;
}


double ux(double x)
{
    return 1 - (1 - exp(-10))*x - exp(-10*x);
}