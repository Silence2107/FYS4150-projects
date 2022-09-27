
# Problem 5 manual

## Formulation

- Now let’s look at how many similarity transformations we need before we reach a result where all non-diagonal matrix elements are close to zero.

## Implementation

- The function is implemented in p2-5.cpp but the bulf of functionality is reused from functions implemented in previous problems. 
    - Compile with `g++ p2-5.cpp ../src/*.cpp -o problem5 -larmadillo -I../include`
    - Run with `./problem5 <size N of A> <eps> <max iterations>`
	
## Collected run commands for producing data in the report
./problem5 6 0.00000001 100000
./problem5 10 0.00000001 100000
./problem5 20 0.00000001 100000
./problem5 30 0.00000001 100000
./problem5 60 0.00000001 100000
./problem5 100 0.00000001 100000
./problem5 200 0.00000001 100000
./problem5 300 0.00000001 200000

To use the output you need to copy it from the terminal. 
Example output:
Converged=1 after 6246 iterations
Here 1 is indicating that it actually converged. If Converged=0 try increasing <max iterations> parameter and run again. 
