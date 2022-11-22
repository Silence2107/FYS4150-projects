
# Problem 6 manual

## Compiling the solution for problem 6

For any N the following is implemented:

### C++

Compile code with
`g++ p2-4-w.cpp ../src/*.cpp -o problem9.exe -larmadillo -I../include`

Executing the program
'./problem9.exe'

Three output files are produced:

a) 'x hat': all the scaled x values
b) 'jacobs_eigenvalues': eigenvalues
c) 'jacobs_eigenvectors': eigenvectors or equivalently the normalized R matrix

### Python

plots.pnyb file is then executed on Jupyter lab and produces two plots, one for the discretized and one for the analytical solution.
