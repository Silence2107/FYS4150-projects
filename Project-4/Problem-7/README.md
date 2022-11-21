# Problem 7 manual
Running parallellized code for many temperatures.

## Usage
- Compile the code with `g++ -O3 problem7.cpp -o problem7.exe ../src/* -I../include/ -std=c++11 -larmadillo -fopenmp`
- Run the code with `./problem7.exe <L width of lattice> <Number MC cycles>`

Examples on command lines 
`./problem7.exe 20 10000`
