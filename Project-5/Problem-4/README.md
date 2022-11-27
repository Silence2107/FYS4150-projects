# Problem 4 manual
Setting up initial condition, by setting wave function to a chosen wave packet shape. 
In this folder we test the functionality in a unit test setting, first setting up condition and then running some steps in the solver.
Output to in inspected manually for now. 

# Usage
Small programs for unit testing thereof. 
- Compile the code with 
	`g++ initialize_unit_test.cpp -o initialize_unit_test.exe ../src/* -I../include/ -std=c++17 -larmadillo`
	`g++ -O3 speed_test.cpp -o speed_test.exe ../src/* -I../include/ -std=c++17 -larmadillo`

- Run the code with 
	`./initialize_unit_test.exe`
	`./speed_test.exe`
