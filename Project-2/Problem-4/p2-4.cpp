
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"

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

    // probe jacobi algorithm
    
    // Generate random N*N matrix
    arma::mat A = arma::mat(N, N).randn();

    // Symmetrize the matrix by reflecting the upper triangle to lower triangle
    A = arma::symmatu(A);

    // compare with Armadillo
    arma::vec eigval_arma, eigval_jacobi;
    arma::mat R_arma, R_jacobi;
    arma::eig_sym(eigval_arma, R_arma, A);

    std::cout << "A:" << std::endl;
    std::cout << std::setprecision(4) << A << std::endl;

    double max;
    
    int iters; // number of iterations
    bool conv; // convergence flag
    jacobi_eigensolver(A, eps, eigval_jacobi, R_jacobi, 1000, iters, conv);

    // print
    std::cout << std::endl
              << "Eigenvalues from the Jacobi rotation method:" << std::endl;
    std::cout << std::setprecision(4) << eigval_jacobi << std::endl;

    std::cout << std::endl
              << "Eigenvectors from the Jacobi rotation method:" << std::endl;
    std::cout << std::setprecision(4) << arma::normalise(R_jacobi) << std::endl;

    std::cout << std::endl
              << "Eigenvalues from Armadillo:" << std::endl;
    std::cout << std::setprecision(4) << eigval_arma << std::endl;

    std::cout << std::endl
              << "Eigenvectors from Armadillo:" << std::endl;
    std::cout << std::setprecision(4) << R_arma << std::endl;

    return 0;
}
