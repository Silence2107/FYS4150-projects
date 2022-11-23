# Problem 4 manual
Implement Ising model with Monte Carlo.

## Usage
#4a generic MCMC program
- Compile the code with `g++ -O3 problem4.cpp -o problem4.exe ../src/* -I../include/ -std=c++11 -larmadillo`
- Run the code with `./problem4.exe <L width of lattice> <T temperature in J/Kb> <Number MC cycles>`

- Note: To fully reproduce the data for Problem 4 and 5, it's required to switch between ordered and unordered initialization.
- We did not parameterize this, so the way to do it is to manually change row saying
	imat latticeMatrix = initOrderedSpinMatrix(L);
  to 
    imat latticeMatrix = initUnorderedSpinMatrix(L, uniform_dist, generator);
  at row 52 if problem4.cpp. Sorry for the inconvenience on that. 

#4b calculate and print analythical results
- Compile the code with `g++ problem4b.cpp -o problem4b.exe ../src/* -I../include/ -std=c++11`
- Run the code with `./problem4b.exe <T temperature in J/Kb>`

#Examples on command lines 
Commands to produce first page of Appendix B in report
`./problem4.exe 8 1 100`
`./problem4.exe 8 4 100`

#Specificly to compare 4B values for temperatures T=1 for different number cycles, then for T=2.
#problem4b.exe being the analytical and problem4.exe being the numeric.
#The commands lines below where used to produce the data for problem 4b/c, presented in Appendix B of the report.
`./problem4b.exe 1`
`./problem4.exe 2 1 100`
`./problem4.exe 2 1 1000`
`./problem4.exe 2 1 10000`
`./problem4.exe 2 1 100000`
`./problem4.exe 2 1 1000000`
`./problem4.exe 2 1 10000000`
`./problem4b.exe 2`
`./problem4.exe 2 2 100`
`./problem4.exe 2 2 1000`
`./problem4.exe 2 2 10000`
`./problem4.exe 2 2 100000`
`./problem4.exe 2 2 1000000`
`./problem4.exe 2 2 10000000`
