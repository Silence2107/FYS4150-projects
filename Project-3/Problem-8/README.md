# Problem 8 manual
Runs a test of forward Euler method, resulting in XY plot of the particle-free solution
Running RK4 both with and without interactions to produce many plots for the reports. 
The C++ programs generate data-files which the Python-scripts plot. 

## Usage
Compile:

`g++ solve_forward_euler.cpp -o euler.out ../src/* -I../include/ -std=c++11 -larmadillo`
`g++ solve_rk4_nointeraction.cpp -o rk4noint.out ../src/* -I../include/ -std=c++11 -larmadillo`
`g++ solve_rk4.cpp -o rk4int.out ../src/* -I../include/ -std=c++11 -larmadillo`

Run (in exactly this order):

`./euler.out`
`./rk4noint.out`
`python3 plot_all_single_plots.py`
`python3 plot_super_imposed.py`
`./rk4int.out`
`python3 plot_super_imposed_interact.py`
