#include "../include/create_tridiag.h"
#include "../include/eigen_linalg.h"
#include "../include/jacobi_rotate.h"

#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <iomanip>

//for writing to file
#include <string>
#include <fstream>


int main()
{

    double eps = 1.0 * pow(10, -8);
    //double h = 0.1;
    int N = 100;


    // initialize random
    srand(time(0));

    arma::mat R = arma::mat(N, N).eye();
    // Generate random N*N matrix
    arma::mat A = arma::mat(N, N).randn();

    // Symmetrize the matrix by reflecting the upper triangle to lower triangle
    A = arma::symmatu(A);

    // compare with Armadillo
    arma::vec eigval_arma;
    arma::mat R_arma;
    arma::eig_sym(eigval_arma, R_arma, A);

    std::cout << "A:" << std::endl;
    std::cout << std::setprecision(4) << A << std::endl;

    double max;
    // While max off diag value above threshold
    do
    {
        size_t k, l;
        //std::cout << A << std::endl;
        max = fabs(abs_max_offdiag_for_symmetric(A, k, l));
        if (max < eps)
        {
            break;
        }
        jacobi_rotate(A, R, k, l);

    } while (true);

    // get eigenvalues from the diag of A
    arma::vec eigval = arma::vec(N);



//OUTPUT

    std::string filename = "jacobi_eigenvalues.txt";
    std::ofstream ofile;
    ofile.open(filename);

    for (int i = 0; i < N; i++)
    {
        eigval(i) = A(i, i);
        ofile << std::setprecision(4) << eigval(i) << std::endl;
    }

    ofile.close();

    std::string filename2 = "jacobi_eigenvectors.txt";
    std::ofstream ofile2;
    ofile2.open(filename2);

    arma::mat eigvec = arma::normalise(R);

    for (int i = 0; i < N; i++) {
      ofile2 << std::setprecision(4) << eigvec.row(i);
    }
//    << std::endl
    ofile2.close();

    std::string filename3 = "x_hat.txt";
    std::ofstream ofile3;
    ofile3.open(filename3);

    //Define x_hat vector filled with zeros
    arma::vec x_hat = arma::vec(N).fill(0);

    for (int i = 1; i < N; i++) {
      x_hat(i) = x_hat(i-1) + 1/N;
      ofile3 << std::setprecision(4) << x_hat(i) << std::endl;
    }
//    << std::endl
    ofile3.close();


    // print
    std::cout << std::endl
              << "Eigenvalues from the Jacobi rotation method:" << std::endl;
    std::cout << std::setprecision(4) << eigval << std::endl;

    std::cout << std::endl
              << "Eigenvectors from the Jacobi rotation method:" << std::endl;
    std::cout << std::setprecision(4) << arma::normalise(R) << std::endl;


    std::cout << std::endl
              << "Eigenvalues from Armadillo:" << std::endl;
    std::cout << std::setprecision(4) << eigval_arma << std::endl;

    std::cout << std::endl
              << "Eigenvectors from Armadillo:" << std::endl;
    std::cout << std::setprecision(4) << R_arma << std::endl;


    return 0;
}
