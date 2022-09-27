#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"

#include <iomanip>

// TODO: Move this declaration to a h-file.
void jacobi_rotate(arma::mat &A, arma::mat &R, size_t k, size_t l);

int main()
{
    double eps = 1.0 * pow(10, -8);
    double h = 0.1;
    int N = 4;

    arma::mat R = arma::mat(N, N).fill(1.000);
    arma::mat A {{1, 0, 0, 0.5}, {0, 1, -0.7, 0}, {0, -0.7, 1, 0}, {0.5, 0, 0, 1}};

    double max;
    // While max off diag value above threshold
    do
    {
        size_t k, l;
        std::cout << A << std::endl;
        max = fabs(abs_max_offdiag_for_symmetric(A, k, l));

        jacobi_rotate(A, R, k, l);

    } while (max > eps);

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
    std::cout << std::setprecision(4) << R << std::endl;

    return 0;
}
