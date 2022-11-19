# Problem 4 manual
Implement Ising model with Monte Carlo.

## Usage
- Compile the code with `g++ ising.cpp -o ising.exe ../src/* -I../include/ -std=c++11 -larmadillo`
- Run the code with `./ising.exe <L width of lattice> <T temperature in J/Kb> <Number MC cycles>`

Examples on command lines 
`./ising.out 2`
`./ising.out 2 1 100`
`./ising.out 50 1 1000`
`./ising.out 50 1 10000`

