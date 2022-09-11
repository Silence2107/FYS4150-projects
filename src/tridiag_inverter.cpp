#include "../include/tridiag_inverter.h"

#include <vector>
//#include <iostream>

std::vector<double> tridiag_inverter_general(const std::vector<double> &subdiag, const std::vector<double> &diag, const std::vector<double> &superdiag, const std::vector<double> &rhs)
{
    size_t n = diag.size();
    std::vector<double> v(n); // The solution vector
    std::vector<double> c(n - 1); // new superdiagonal
    std::vector<double> g(n); // new right hand side
    c[0] = superdiag[0] / diag[0];
    g[0] = rhs[0] / diag[0];
    for (size_t i = 1; i < n - 1; ++i)
    {
        c[i] = superdiag[i] / (diag[i] - subdiag[i - 1] * c[i - 1]);
        g[i] = (rhs[i] - subdiag[i - 1] * g[i - 1]) / (diag[i] - subdiag[i - 1] * c[i - 1]);
        //g[i] = (rhs[i] - subdiag[i - 1] * g[i - 1]) / (diag[i] - subdiag[i - 1] * superdiag[i - 1]);
    }
    g[n - 1] = (rhs[n - 1] - subdiag[n - 2] * g[n - 2]) / (diag[n - 1] - subdiag[n - 2] * c[n - 2]);
    v[n - 1] = g[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        v[i] = g[i] - c[i] * v[i + 1];
    }
    return v;
}


//Special algorithm
std::vector<double> tridiag_inverter_special(const std::vector<double> &subdiag, const std::vector<double> &diag, const std::vector<double> &superdiag, const std::vector<double> &rhs)
{
    size_t n = diag.size();
    std::vector<double> v(n); // The solution vector
    std::vector<double> g(n - 1); // new right hand side
    std::vector<double> b(n - 1);

    //Defining g1 and b1 (the first main diagonal value)
    g[0] = rhs[0];
    b[0] = 2; //the first diagonal value defined
    double row_op = 0.5; //first row operation

    //Looping from i=1 to i=n-2
    for (size_t i = 1; i < n - 1; ++i)
    {
        g[i] = g[i] + g[i - 1]*row_op;
        row_op = (i + 1 / i + 2);
    }

    g[n - 1] = g[n - 2] + rhs[n - 1];

    //Backward substitution

    //Looping from i=1 to i=n-2
    for (size_t i = 1; i < n - 1; ++i)
    {
        b[i] = (i + 1)/i; //for the next for loop
    }

    v[n - 1] = g[n - 1]/b[n - 1];

    for (int i = n - 2; i >= 0; --i)
    {
        v[i] = (g[i] + v[i + 1])/b[i];
    }
    return v;
}
