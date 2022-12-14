# Problem 7 manual
From theoretical viewpoint, the total probability of the system is conserved and normalized to 1. We check the unitarity of the wave function, i.e. we check whether (when) the normalization of the wave function decline from 1.

# Usage
- Compile the code with 
	`g++ unitarity_check.cpp -o unitarity_check.exe ../src/* -I../include/ -std=c++17 -larmadillo`
- For usage, run the code with 
    `./unitarity_check.exe <double_slit_on=(0,1) a.k.a. (false,true)>`
    - The code will generate a .txt file with the norm of the wave function for each time step.
- For plotting, see
	`python3 ./plot_prob_of_t.py --file probability_of_time.txt`
