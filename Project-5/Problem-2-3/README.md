# Problem 2-3 manual
Solvers for Shrödinger equation with Crank Nicelson scheme. 

# Usage
Small programs for unit testing thereof. 
- Compile the code with 
	`g++ crank_nicolson_unit_test.cpp -o crank_nicolson_unit_test.exe ../src/* -I../include/ -std=c++17 -larmadillo`
	`g++ solver_unit_test.cpp -o solver_unit_test.exe ../src/* -I../include/ -std=c++17 -larmadillo`
- Run the code with 
	` ./solver_unit_test.exe`
	` ./crank_nicolson_unit_test.exe`
