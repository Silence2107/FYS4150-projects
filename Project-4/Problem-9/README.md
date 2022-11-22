# Problem 9 manual
Fitting final for the research is to extract critical temperature based on lattice size fit. 

## Usage
- Extraction is done via `histogen.py` script, which uses ROOT as a base for plotting and fitting.
- The script is handmade and requires premade cv(T) datasets to be present in the same directory. Should you have desire to check it in practice, you need the following:
    - `cv(T)_L{20,30,40,50,60,80,100}_fine.csv` files, which are the output of the previous problem.
    - pyROOT installed in the system
    - The script generates two figures, as well as a bunch of fit information in the terminal.
    - The script is not supposed to be user-friendly. Invokation is parameter-free.

