#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include "../include/create_tridiag.h"

arma::vec eigval;
arma::mat eigvec;
double h=0.1;
double N=6;
double h2=pow(h,2);
double a=1/h2, d=-1/h2;

int main() { 

    arma::mat A=create_tridiagonal(N, h);

    //print A matrix
    // std::cout <<  "A matrix:" << std::endl;
    //for (int i=0; i < N ; i++) {
    //      for (int n=0; n < N; n++) {
    //     std::cout << A(i,n) << " ";
    // }
    // std::cout << std::endl ;
    // }

    //solves Av=lv
    arma::eig_sym(eigval, eigvec, A); 

    // analytical solution
    arma::vec eigval_an = arma::vec(N).fill(0.000); 
    arma::mat eigvec_an = arma::mat(N,N).fill(0.000); 

    double k = M_PI/(N+1);

    for (int i=0; i < N ; i++) {
       eigval_an(i) = d+ 2*a*cos((i+1)*k);
       
        for (int j=0; j < N ; j++ ) {
            eigvec_an(j,i) = sin((i+1)*k*(j+1));
        }

    }

    //normalise
    arma::mat norm_eigvec = normalise(eigvec);
    arma::mat norm_eigvec_an = normalise(eigvec_an);

    // print eigenvalues
   std::cout << std::endl <<  "Eigenvalues from Armadillo:" << std::endl;
   std::cout  << std::scientific << std::setprecision(5)  << eigval << std::endl;

   std::cout << std::endl <<  "Eigenvalues as analytical solution:" << std::endl;
   std::cout  << std::scientific << std::setprecision(5)  << eigval_an << std::endl;
   arma::mat test1 = normalise(eigvec);

    // print eigenvectors
   std::cout << std::endl <<  "Eigenvectors from Armadillo:" << std::endl;
   std::cout  << std::scientific << std::setprecision(5)  << norm_eigvec << std::endl;

   std::cout << std::endl <<  "Eigenvectors as analytical solution:" << std::endl;
   std::cout  << std::scientific << std::setprecision(5)  << norm_eigvec_an << std::endl;


}
