
#include "../include/eigen_linalg.h"

#include <armadillo>
#include <stdexcept>
#include <cmath>

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