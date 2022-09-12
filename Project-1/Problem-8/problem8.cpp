#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <sstream>
#include <cmath>
#include <math.h>
#include <iomanip>

//Calculate u(x) with the expression given in problem description.
double exactSolution(double x)
{
    return 1.0 - (1.0 - exp(-10.0)) * x - exp(-10.0 * x);
}

int main(int argc, char **argv)
{

    std::string line;
    double x, y, f;

    // A vector of vectors to store the the rows in the input file
    std::vector<std::vector<double>> input_data;

    if (argc > 3)
    {
        throw std::invalid_argument("Usage: ./problem8 <output file log10 absolute error> <output file log10 relative error>");
    }

	//Default output file names. Overwrites if exists. 
    std::string fpathAbsolute = argc > 1 ? argv[1] : "abs_error.csv";
    std::string fpathRelative = argc > 2 ? argv[2] : "rel_error.csv";

    while (std::cin)
    {
        //Code reused from https://anderkve.github.io/FYS3150/book/introduction_to_cpp/read_from_file.html
        //modified to read from stdin instead of file.
        getline(std::cin, line);
        if (line.length() < 1 || line.at(0) == '#')
        {
            continue;
        }
        else
        {
            // Parse the string (line) and interpret it as three
            // double variables (x, y, f)
            std::stringstream mysstream(line);
            mysstream >> x >> y;

            // Save the three values in a new vector in input_data
            std::vector<double> triplet = {x, y};
            input_data.push_back(triplet);
        }
    };

    std::ofstream ofileAbsoluteError;
    ofileAbsoluteError.open(fpathAbsolute);
    std::ofstream ofileRelativeError;
    ofileRelativeError.open(fpathRelative);

    //For problem 8.C we want to find the highest error for each step size. Keeping track of the highest found so far here.
    double highestRelativeErrorFound = 0.0;

    for (int i = 0; i < input_data.size(); i++)
    {
        // A very small number near machine precision. Use this number later to check for equality to zero within a finite margin.
        // TODO: There is probably a predefined constant in math lib for this we should use. 
        double epsilon = 0.000000000000001; // 1e-15
        std::vector<double> data_row = input_data[i];

        double xValue = data_row[0];
        double yValue = data_row[1];

        double exactValue = exactSolution(xValue);

        double error = (exactValue - yValue);
        double absoluteError = fabs(exactValue - yValue);

        // Avoid division by zero by only computing error if divisor is not zero or very close to zero.
        // We could have chosen a default value for these, but we rather just skip these points with no errors in the output altogether. 
        if (fabs(exactValue) > epsilon)
        {
            double log10Error = log10(absoluteError);
            double relativeError = absoluteError / fabs(exactValue);
            double log10RelativeError = log10(relativeError);

            //Print to file. Same settings as in problem 2. 
            ofileAbsoluteError << std::setprecision(2) << std::scientific << xValue << "\t" << log10Error << std::endl;        
            ofileRelativeError << std::setprecision(2) << std::scientific << xValue << "\t" << log10RelativeError << std::endl;

            if(relativeError > highestRelativeErrorFound)
            {
                //Updating highest error so far. Note these are all positive due to calling fabs above.
                highestRelativeErrorFound = relativeError;
            }
        }
    }

	//Simply output this value to stdout. User will have to copy and paste it manually. 
    std::cout << "Highest absolute relative error found was: " << highestRelativeErrorFound << std::endl;
	
    ofileAbsoluteError.close();
    ofileRelativeError.close();

    return 0;
}
