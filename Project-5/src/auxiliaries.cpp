
#include "../include/auxiliaries.h"

#include <functional>
#include <armadillo>

size_t flatten_index(size_t i, size_t j, size_t Nx)
{
    return i * Nx + j;
}

arma::uvec unflatten_index(size_t k, size_t Nx)
{
    arma::uvec index(2);
    index(0) = k / Nx;
    index(1) = k % Nx;
    return index;
}

std::tuple<double, double> find_dx_and_dy(size_t Nx, size_t Ny, const arma::vec &x_bound, const arma::vec &y_bound)
{
    double x_min = x_bound(0), x_max = x_bound(1);
    double y_min = y_bound(0), y_max = y_bound(1);
    double dx = (x_max - x_min) / (Nx - 1), dy = (y_max - y_min) / (Ny - 1);
    return std::make_tuple(dx, dy);
}

arma::cx_mat unflatten_matrix(arma::cx_mat psi_flat, size_t w, size_t h)
{
    arma::cx_mat psi_mat = arma::zeros<arma::cx_mat>(w, h);
    for (size_t i = 0; i < w - 2; i++)
    {
        for (size_t j = 0; j < h; j++)
        {
            psi_mat(i, j) = psi_flat(flatten_index(i, j, w));
        }
    }
    return psi_mat;
}

arma::mat probability_matrix(arma::cx_mat psi)
{
    arma::cx_mat psiConjugate = arma::conj(psi); // Complex conjugate.
    arma::cx_mat prob = psi % psiConjugate;      // Element-wise multiplication
    return arma::real(prob);                     // By now prob only contains real numbers, due to multiplication with complex conjugate. This call effectively only changes type.
}
