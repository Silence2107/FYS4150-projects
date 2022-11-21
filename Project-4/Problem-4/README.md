# Problem 4 manual
Implement Ising model with Monte Carlo.

## Usage
- Compile the code with `g++ -O3 problem4.cpp -o problem4.exe ../src/* -I../include/ -std=c++11 -larmadillo`
- Run the code with `./problem4.exe <L width of lattice> <T temperature in J/Kb> <Number MC cycles>`

Examples on command lines 
`./problem4.exe 2`
`./problem4.exe 2 1 100`
`./problem4.exe 8 1 100`
`./problem4.exe 8 4 100`
`./problem4.exe 50 1 1000`
`./problem4.exe 50 1 10000`
