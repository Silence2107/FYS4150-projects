
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"
//#include "../include/jacobi_rotate.h"

#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>

int main()
{
    double eps = 1.0 * pow(10, -8);
    //double h = 0.1;
    int N = 6;
double h=0.1;

    // initialize random
    srand(time(0));

    arma::mat R = arma::mat(N, N).eye();
    // Generate random N*N matrix
    //arma::mat A = arma::mat(N, N).randn();
    arma::mat A=create_tridiagonal(N, h);

    // Symmetrize the matrix by reflecting the upper triangle to lower triangle
    A = arma::symmatu(A);

    // compare with Armadillo
    arma::vec eigval_arma;
    arma::mat R_arma;
    arma::eig_sym(eigval_arma, R_arma, A);

    std::cout << "A:" << std::endl;
    std::cout << std::setprecision(4) << A << std::endl;

    //For checking convergence. Using an arbitrary value 100 for problem 4, will be refined in later tasks.
    int maxIterations = 100;
    int actualIterations;
    bool converged;
        // get eigenvalues from the diag of A
    arma::vec eigval = arma::vec(N);

    jacobi_eigensolver(A, eps, eigval, R, maxIterations, actualIterations, converged);

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

    return 0;
}
