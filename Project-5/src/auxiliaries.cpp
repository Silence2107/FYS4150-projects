
#include "../include/auxiliaries.h"

#include <functional>
#include <armadillo>

size_t flatten_index(size_t i, size_t j, size_t Nx)
{
    return i*Nx + j;
}

arma::uvec unflatten_index(size_t k, size_t Nx)
{
    arma::uvec index(2);
    index(0) = k/Nx;
    index(1) = k%Nx;
    return index;
}