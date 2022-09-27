
#include "../include/eigen_linalg.h"

#include <armadillo>
#include <stdexcept>
#include <cmath>
#include <stdexcept>

double abs_max_offdiag_for_symmetric(const arma::mat &A, size_t &row, size_t &col)
{
    // if matrix has no more than one element, we have nothing to do
    if (A.n_elem <= 1)
        throw std::invalid_argument("Matrix has no off-diagonal elements");
    // Otherwise, at least A[1,0] or A[0,1] exists, but for symmetric matrices they both exist and are equal
    double max{A(0, 1)}; // placeholder for the largest element
    row = 0;
    col = 1; // placeholder for positions of the largest element
    // Now let's loop over the matrice's upper diagonal and see if we can find a larger element
    for (size_t i = 0; i < A.n_rows; ++i)
        for (size_t j = i + 1; j < A.n_cols; ++j)
            if (fabs(A(i, j)) > fabs(max))
            {
                max = A(i, j);
                row = i;
                col = j;
            }
    // Now we may be sure max element is found
    return max;
}

void jacobi_rotate(arma::mat &A, arma::mat &R, size_t k, size_t l)
{
    // Obtain size directly from input matrix
    int N = A.n_rows;
    double t;

    // new A and R matrices initialized to current A and R
    arma::mat A_mp1 = A;
    arma::mat R_mp1 = R;

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
        if (i != k && i != l)
        {
            A_mp1(i, k) = A(i, k) * c - A(i, l) * s;
            A_mp1(k, i) = A_mp1(i, k);
            A_mp1(i, l) = A(i, l) * c + A(i, k) * s;
            A_mp1(l, i) = A_mp1(i, l);
        }
    }

    // update rotation marix
    for (int i = 0; i < N; i++)
    {
        R_mp1(i, k) = R(i, k) * c - R(i, l) * s;
        R_mp1(i, l) = R(i, l) * c + R(i, k) * s;
    }

    // update A & R
    A = A_mp1;
    R = R_mp1;
}

void jacobi_eigensolver(const arma::mat &A, double eps, arma::vec &eigenvalues, arma::mat &eigenvectors,
                        const int maxiter, int &iterations, bool &converged)
{
    // Obtain size directly from input matrix, and check it's square (could be optimized away later).
    if (A.n_rows != A.n_cols)
        throw std::invalid_argument("Matrix is not square");
    int N = A.n_rows;

    // initialize eigenvalues and eigenvectors
    eigenvalues = arma::vec(N);
    eigenvectors = arma::mat(N, N);

    // initialize A and R matrices
    arma::mat A_m = A;
    arma::mat R_m = arma::eye(N, N);

    // initialize iteration counter
    iterations = 0;

    size_t k, l; // indices of max off-diagonal element

    // loop until max off-diagonal element is smaller than eps
    while (true)
    {
        // initialize max off-diagonal element
        double max_offdiag = fabs(abs_max_offdiag_for_symmetric(A_m, k, l));

        if (max_offdiag < eps)
        {
            converged = true;
            break;
        }
        if (iterations >= maxiter)
        {
            converged = false;
            break;
        }

        // rotate A and R matrices
        jacobi_rotate(A_m, R_m, k, l);

        // update iteration counter
        ++iterations;
    }

    // update eigenvalues and eigenvectors
    for (int i = 0; i < N; i++)
    {
        eigenvalues(i) = A_m(i, i);
        eigenvectors.col(i) = R_m.col(i);
    }
    
    // sort eigenvalues and eigenvectors
    arma::uvec indices = arma::sort_index(eigenvalues);
    eigenvalues = eigenvalues.elem(indices);
    eigenvectors = eigenvectors.cols(indices);
}