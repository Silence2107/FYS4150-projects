#include <armadillo>
#include <cmath>
#include "../include/create_tridiag.h"

arma::mat create_tridiagonal(int N, double h)

{
    double h2=pow(h,2), a=-1/h2, d=2/h2;

    arma::mat A = arma::mat(N,N).fill(0.000); 

    // set first and last row values
    A(0,0)=d; A(0,1)=a; 
    A(N-1,N-2)=a; A(N-1,N-1)=d;

    //set other rows
    for (int i=1; i < N-1; i++) {
        A(i,i) = d;
        A(i,i-1) = a; 
        A(i,i+1) = a; 
    }
    return A;
}