#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>

arma::vec eigval;
arma::mat eigvec;
int N = 6;
double h=0.1;
double h2=pow(h,2);

int main() { 

    double a=-1/h2, d=2/h2; 
    // build tridiag matrix
    arma::mat A = arma::mat(6,6).fill(0.000); 

    //A(0,0)=d; A(0,1)=a; A(N-1,N-1)=d;

   // for (int i=1; i < N-1; i++) {
    //    A(i,i) = d;
    //    A(i,i-1) = a; 
    //    A(i,i+1) = a; 
   // }

    //print A matrix
    std::cout <<  "A matrix:" << std::endl;
   for (int i=0; i < N-1; i++) {
         for (int n=0; n < N-1; n++) {
        std::cout << A(i,n) << " ";
    }
    std::cout << std::endl ;
   }

    arma::eig_sym(eigval, eigvec, A); //solves Av=lv

    // print eigenvalues
   // std::cout << std::endl <<  "eigenvalues:" << std::setprecision(10) << std::endl;
   // std::cout << eigval << std::endl;
    
    return 0;

}
