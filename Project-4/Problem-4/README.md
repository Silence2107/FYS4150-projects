# Problem 4 manual
Implement Ising model with Monte Carlo.

## Usage
#4a generic MCMC program
- Compile the code with `g++ -O3 problem4.cpp -o problem4.exe ../src/* -I../include/ -std=c++11 -larmadillo`
- Run the code with `./problem4.exe <L width of lattice> <T temperature in J/Kb> <Number MC cycles>`

#4b calculate and print analythical results
- Compile the code with `g++ problem4b.cpp -o problem4b.exe ../src/* -I../include/ -std=c++11`
- Run the code with `./problem4b.exe <T temperature in J/Kb>`

Examples on command lines 
`./problem4.exe 2`
`./problem4.exe 2 1 100`
`./problem4.exe 8 1 100`
`./problem4.exe 8 4 100`
`./problem4.exe 50 1 1000`
`./problem4.exe 50 1 10000`

#Specificly to compare 4B values for temperatures T=1 for different number cycles, then for T=2.
`./problem4.exe 2 1 100`
`./problem4.exe 2 1 10000`
`./problem4b.exe 1`
`./problem4.exe 2 2 10000`
`./problem4b.exe 2`
