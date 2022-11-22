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
./problem8.exe 20 500000
./problem8.exe 40 500000
./problem8.exe 60 500000
./problem8.exe 80 500000
./problem8.exe 100 500000

Create plot with commands like (for each csv-file):
python3 ./plotter3.py  --csv specificheat40.csv
However,at the time of this writing Python script must me manually edited between runs to get the wanted axis units, etc.

Alternativaly the notebook file plotter_notebook.ipynb located in sampledata folder may be used.