
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"
#include "../include/jacobi_rotate.h"

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

    // initialize random
    srand(time(0));

    arma::mat R = arma::mat(N, N).eye();
    // Generate random N*N matrix
    arma::mat A = arma::mat(N, N).randn();

    // Symmetrize the matrix by reflecting the upper triangle to lower triangle
    A = arma::symmatu(A);

    // compare with Armadillo
    arma::vec eigval_arma;
    arma::mat R_arma;
    arma::eig_sym(eigval_arma, R_arma, A);

    std::cout << "A:" << std::endl;
    std::cout << std::setprecision(4) << A << std::endl;

    double max;
    // While max off diag value above threshold
    do
    {
        size_t k, l;
        //std::cout << A << std::endl;
        max = fabs(abs_max_offdiag_for_symmetric(A, k, l));
        if (max < eps)
        {
            break;
        }
        jacobi_rotate(A, R, k, l);

    } while (true);

    // get eigenvalues from the diag of A
    arma::vec eigval = arma::vec(N);

    for (int i = 0; i < N; i++)
    {
        eigval(i) = A(i, i);
    }

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
