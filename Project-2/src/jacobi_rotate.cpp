#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>

// Performs a single Jacobi rotation, to "rotate away"
// the off-diagonal element at A(k,l).
void jacobi_rotate(arma::mat &A, arma::mat &R, int k, int l)
{
    // Code structure as suggested in task Morten Hjorth-Jensen, Computational Physics, Lecture Notes Fall 2015
    // Algoritm based partially on page 218-220 of Morten Hjorth-Jensen, Computational Physics, Lecture Notes Fall 2015
    // https://raw.githubusercontent.com/CompPhysics/ComputationalPhysics/master/doc/Lectures/lectures2015.pdf

    if (A.n_rows != A.n_cols)
        throw std::invalid_argument("Matrix is not square");

    int N = A.n_rows;
    double t;

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
    A_mp1(l, l) = A(l, l) * pow(s, 2) + 2 * A(k, l) * c * s + A(k, k) * pow(s, 2);
    A_mp1(k, l) = 0;
    A_mp1(l, k) = 0;

    for (int i = 0; i < N; i++)
    {
        if (i != k || i == l)
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

    // update A_m and R_m for new loop
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A(i, j) = A_mp1(i, j);
            R(i, j) = R_mp1(i, j);
        }
    }
}
