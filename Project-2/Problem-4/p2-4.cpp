#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"

double eps=1.0*pow(10,-8);
double h=0.1;
int N=6;
arma::mat A=create_tridiagonal(N, h);

int main() { 
    arma::mat A_1 = create_tridiagonal(N, h);
    //arma::mat A {{1, 0, 0, 0.5}, {0, 1, -0.7, 0}, {0, -0.7, 1, 0}, {0.5, 0, 0, 1}};
    //std::vector<size_t> pos(2);
    //auto max = abs_max_offdiag_for_symmetric(A, pos[0], pos[1]);

    std::cout << A(1,1);

   // k=pos[0]; l=pos[1];

    //double abs_max = abs(max);

    //arma::mat A_m = ... ; 

   // while  ( abs_max > eps) {

  //      double tau = (A_m(l,l)-A_m(k,k))/(2*A_m(k,l)) ;
   //     double tan ;
    

   //     i++;
   // }
    

    return 0;
}