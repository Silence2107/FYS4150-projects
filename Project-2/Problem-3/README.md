
# Problem 3 manual

## Formulation

- Write a library function that finds maximum (by abs. val.) offdiagonal element of `arma::mat` and returns its value and its indices.
- Run a simple test

## Implementation

- The function is implemented in `eigen_linalg` library by the name of `abs_max_offdiag_for_symmetric`.
- Test a function by running `max_offdiag_test.cpp` file, which verifies it for a given matrix.
    - Compile with `g++ max_offdiag_test.cpp path/to/src/*.cpp -o path/to/your/executable -larmadillo -I./path/to/include`
    - Run with `./path/to/your/executable`