# Problem 6 manual
Let's put this MC generator to use. The following code runs the simulation multiple times to produce a dataframe with various means. We specifically build a few energy histograms out of it.

## Usage
Following lines assume you are in the `Problem-6` directory..

- Compile the code with `g++ problem6.cpp -o problem6.out ../src/* -I../include/ -std=c++11 -larmadillo -On`
    - High optimization level is advisable, but mind that on some machines it may cause the code to crash.
- Generate a dataframe with `./temperature_dataframe.sh <L width of lattice> <T temperature in J/Kb> <Number MC cycles> <Number of runs>`
    - A dataframe is created at `pwd`. Make sure to have write permissions. If you want to use a different location, change the `temperature_dataframe.sh` file.
- Finally, one can generate histograms with use of a `histogen.py` file. The one uses ROOT 6.24+ for running, which is only done for quality purpose. If you have pyROOT installed and want to probe the script, make sure to check parameter list with `python3 histogen.py --help`, as well as make sure to be ready to finetune the script to your needs.
