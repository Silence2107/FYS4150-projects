#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"

#include <iomanip>

int main()
{

    double eps = 1.0 * pow(10, -8);
    double h = 0.1;
    int N = 6;
    double t;

    arma::mat R = arma::mat(N, N).fill(1.000);
    arma::mat A{{1, 0, 0, 0.5, 0, 0.5}, {0, -0.4, -0.7, 0, -0.7, 0}, {0, -0.7, 1, 0, 1, 0}, {0.5, 0, 0, 1, -0.5, 1}, {0, -0.7, 1, -0.5, 0, -0.7}, {0.5, 0, 0, 1, -0.7, -0.9}};

    double max;
    // While max off diag value above threshold
    do
    {
        size_t k, l;
        std::cout << A << std::endl;
        max = fabs(abs_max_offdiag_for_symmetric(A, k, l));

        // initialise A_mp1 and R_mp1 matrices
        arma::mat A_mp1 = arma::mat(N, N).fill(0.000);
        arma::mat R_mp1 = arma::mat(N, N).fill(0.000);

        // calculate tau, t, c, s

        double tau = (A(l, l) - A(k, k)) / (2 * A(k, l));

        if (tau > 0)
        {
            t = -tau + pow(1 + pow(tau, 2), .5);
        }
        else
        {
            t = -tau - pow(1 + pow(tau, 2), .5);
        }

        double c = 1 / (pow((1 + pow(t, 2)), 0.5));
        double s = c * t;

        // transform current A matrix: A^(m+1)=S_m^T*A^m*S_m, by updating elements
        A_mp1(k, k) = A(k, k) * pow(c, 2) - 2 * A(k, l) * c * s + A(l, l) * pow(s, 2);
        A_mp1(l, l) = A(l, l) * pow(c, 2) + 2 * A(k, l) * c * s + A(k, k) * pow(s, 2);
        A_mp1(k, l) = 0;
        A_mp1(l, k) = 0;

        for (int i = 0; i < N; i++)
        {
            if (i != k || i == l)
            {
                A_mp1(i, k) = A(i, k) * c - A(i, l) * s;
                A_mp1(k, l) = A_mp1(i, k);
                A_mp1(i, l) = A(i, l) * c + A(i, k) * s;
                A_mp1(l, i) = A_mp1(i, l);
            }
        }

        // update rotation marix
        for (int i = 0; i < N; i++)
        {
            R_mp1(i, k) = R(i, k) * c - R(i, l) * s;
            R_mp1(i, l) = R(i, l) * c - R(i, k) * s;
        }

        // update A_m and R_m for new loop
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A(i, j) = A_mp1(i, j);
                R(i, j) = A_mp1(i, j);
            }
        }
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