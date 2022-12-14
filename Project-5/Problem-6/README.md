# Problem 6 manual
Putting together everything from Problems 1-5 to a complete solver, albeit still with only hard coded physical values. 
Basically running 2 slits, gaussian initial wave packet, 0.008 seconds (change code to 0.02 seconds for longer simulation requested in problem 8).
Setting gridsize approx 100, but we'll probably need to go to 200 for proper accuracy.

# Usage
Small programs for unit testing thereof. 
- Compile the code with 
	`g++ problem6.cpp -o problem6.exe ../src/* -I../include/ -std=c++17 -larmadillo`
- Run the code with 
	`./problem6.exe`
	`python3 ./plot_file.py`
	`python3 ./plot_many_timesteps.py`
Then look at generated .pdf files. 
