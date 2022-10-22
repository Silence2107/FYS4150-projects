# Problem 8 manual
Runs a test of forward Euler method, resulting in XY plot of the particle-free solution

## Usage
Compile:

`g++ solve_forward_euler.cpp -o euler.out ../src/* -I../include/ -std=c++11 -larmadillo`

Run:

./euler.out

Make plot:

`python3 plotter3.py --csv "path_to_csv_file=particle1.csv"`
