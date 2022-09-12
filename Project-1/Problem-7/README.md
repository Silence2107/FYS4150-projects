
# Problem 7 manual

## Problem 7 description

- Implement a function that solves a tridiagonal system of equations
- Write output to a file
- Superimpose a few of these outputs with exact solutions

## Implementation

- A C++ file `solve_tridiag_general.cpp` uses `tridiag_inverter` and `file_io` libraries to solve a tridiagonal system of equations and write the output to a file.
    - Compilation: `g++ path/to/solve_tridiag_general.cpp -o path/to/solve_tridiag_general.out path/to/src/*.cpp -I./path/to/include`
    - Execution: `./path/to/solve_tridiag_general.out <discretization = "1000"> <output_file = "output.csv">`
- A Python file `plot_superimpose.py` uses these datasets to superimpose a few of these outputs on the same picture.
    - Execution: see `python3 path/to/plot_superimpose.py --help` for full parameters list
- A C++ file `function_to_csv.cpp` is used for producing a dataset for the exact solution.
    - Compilation: `g++ path/to/function_to_csv.cpp -o path/to/function_to_csv.out path/to/src/*.cpp -I./path/to/include`
    - Execution: `./path/to/function_to_csv.out <discretization = "1000"> <output_file = "output.csv">`