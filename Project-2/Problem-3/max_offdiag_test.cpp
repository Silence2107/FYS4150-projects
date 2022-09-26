
#include "../include/eigen_linalg.h"
#include <armadillo>
#include <iostream>
#include <vector>

int main()
{
    arma::mat A {{1, 0, 0, 0.5}, {0, 1, -0.7, 0}, {0, -0.7, 1, 0}, {0.5, 0, 0, 1}};
    std::vector<size_t> pos(2);
    auto max = abs_max_offdiag_for_symmetric(A, pos[0], pos[1]);
    std::cout << "Max by abs. offdiag. element is " << max << " at position (" << pos[0] << ", " << pos[1] << ")" << std::endl;
}