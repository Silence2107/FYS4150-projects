# Problem 8 manual
Running parallellized code over a range of temperatures, to produce data for plots showing quantities of interest. 
Quantities as usual being energy, magnetization, specific heat capacity and susceptibility.

## Usage
- Compile the code with `g++ -O3 problem8.cpp -o problem8.exe ../src/* -I../include/ -std=c++11 -larmadillo -fopenmp`
- Run the code with `./problem8.exe <L width of lattice> <Number MC cycles>`

Examples on command lines 

Suggested small function test (quick run, sample data file that fits on screen)
`./problem8.exe 20 1000`

Commands for producing plots for report will take significant time to run.
To be filled in here.

