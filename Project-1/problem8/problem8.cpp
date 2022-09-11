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

    if (argc < 3)
    {
        throw std::invalid_argument("Usage: ./problem8 <output file log10 absolute error> <output file log10 relative error>");
    }

    std::string fpathAbsolute = argc > 1 ? argv[1] : "abs_error.csv";
    std::string fpathRelative = argc > 2 ? argv[2] : "rel_error.csv";

    while (std::cin)
    {
        // code reused from https://anderkve.github.io/FYS3150/book/introduction_to_cpp/read_from_file.html
        getline(std::cin, line);
        // std::cout << line << std::endl;

        // std::cout << "lenght = " << line.length();
        //  Skip lines with "#" at the first position
        if (line.length() < 1 || line.at(0) == '#')
        {
            continue;
        }
        else
        {
            // Parse the string (line) and interpret it as three
            // double variables (x, y, f)
            std::stringstream mysstream(line);
            mysstream >> x >> y >> f;

            // Save the three values in a new vector in input_data
            std::vector<double> triplet = {x, y, f};
            input_data.push_back(triplet);
        }
    };
/*
    // reused some code from https://stackoverflow.com/questions/1784573/iterator-for-2d-vector
    for (int i = 0; i < input_data.size(); i++)
    {
        std::vector<double> y = input_data[i];
        for (int j = 0; j < y.size(); j++)
        {
            std::cout << y[j] << " ";
        }
        std::cout << std::endl;
    }
*/
    std::ofstream ofileAbsoluteError;
    ofileAbsoluteError.open(fpathAbsolute);
    std::ofstream ofileRelativeError;
    //ofileRelativeError.open("rel_error.csv");
    ofileRelativeError.open(fpathRelative);

    for (int i = 0; i < input_data.size(); i++)
    {
        // A very small number near machine precision. Use this number later to check for equality to zero within a finite margin.
        double epsilon = 0.000000000000001; // 1e-15
        std::vector<double> data_row = input_data[i];

        double xValue = data_row[1];
        double yValue = data_row[2];

        double exactValue = exactSolution(xValue);
        // std::cout << "Exakt: " << exactValue << std::endl;

        double error = (exactValue - yValue);
        double absoluteError = fabs(exactValue - yValue);

        // std::cout << "x: " << xValue << " y:" << yValue << " u:" << exactValue << " error:" << error << " abs error:" << absoluteError << std::endl;

        double log10Error = 0.0;
        double log10RelativeError = 0.0;
        // Avoid division by zero by only computing error if divisor is not zero or very close to zero.
        if (fabs(exactValue) > epsilon)
        {
            log10Error = log10(absoluteError);
            log10RelativeError = log10(absoluteError / fabs(exactValue));

            ofileAbsoluteError << std::setprecision(2) << std::scientific << xValue << "\t" << log10Error << std::endl;         // print to file
            ofileRelativeError << std::setprecision(2) << std::scientific << xValue << "\t" << log10RelativeError << std::endl; // print to file
        }
        /*
                std::cout << "Error: " << absoluteError << " Log abs error: " << log10Error << " Log rel error: " << log10RelativeError << std::endl;
                // std::cout << "Error: " << error << "Log abs error: " << log10Error << "Log rel error: " << log10RelativeError << std::endl;
                std::cout << std::endl;
        */
    }

    ofileAbsoluteError.close();
    ofileRelativeError.close();

    return 0;
}
