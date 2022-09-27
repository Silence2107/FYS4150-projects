
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"
//#include "../include/jacobi_rotate.h"

#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>

int main(int argc, char **argv)
{

    if (argc > 4)
    {
        throw std::invalid_argument("Usage: ./problem5 <size N of A> <eps> <max iterations>");
    }

    //Read program parameters, with default values N=10, eps=1e-8 and maxIterations=1e5 if not specified. 
    double N = argc > 1 ? atof(argv[1]) : 10;
    double eps = argc > 2 ? atof(argv[2]) : 1.0 * pow(10, -8);
    int maxIterations = argc > 2 ? atof(argv[3]) : 100000;

    double h=1.0/(N+1); //Because given in the task is N=n-1 and h=1/N

    // initialize random
    srand(time(0));

    arma::mat R = arma::mat(N, N).eye();

    // Generating matrix A that corresponds to the actual differential equation to solve, with step length as specified by parameters. 
    arma::mat A=create_tridiagonal(N, h);

    // Symmetrize the matrix by reflecting the upper triangle to lower triangle
    //A = arma::symmatu(A);

    // compare with Armadillo
    arma::vec eigval_arma;
    arma::mat R_arma;
    arma::eig_sym(eigval_arma, R_arma, A);
/*
    std::cout << "A:" << std::endl;
    std::cout << std::setprecision(4) << A << std::endl;
*/

    int actualIterations;
    bool converged;
        
        // get eigenvalues from the diag of A
    arma::vec eigval = arma::vec(N);

    jacobi_eigensolver(A, eps, eigval, R, maxIterations, actualIterations, converged);
/*
    // print
    std::cout << std::endl
              << "Eigenvalues from the Jacobi rotation method:" << std::endl;
    std::cout << std::setprecision(4) << eigval << std::endl;

    std::cout << std::endl
              << "Eigenvectors from the Jacobi rotation method:" << std::endl;
    std::cout << std::setprecision(4) << arma::normalise(R) << std::endl;


    std::cout << std::endl
              << "Eigenvalues from Armadillo:" << std::endl;
    std::cout << std::setprecision(4) << eigval_arma << std::endl;

    std::cout << std::endl
              << "Eigenvectors from Armadillo:" << std::endl;
    std::cout << std::setprecision(4) << R_arma << std::endl;
*/
    std::cout << "Converged=" << converged << " after " << actualIterations << " iterations" << std::endl;

    return 0;
}
