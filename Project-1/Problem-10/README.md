# Problem 2 manual

## Comparing timings
 
The timings required by each algorithm are extracted using the chrono library. This is achieved by adding the following lines:

`auto t1 = std::chrono::high_resolution_clock::now();`

and

`auto t2 = std::chrono::high_resolution_clock::now();`

`double duration_seconds = std::chrono::duration<double>(t2 - t1).count();`

`std::cout << std::fixed << std::setprecision(5) << duration_seconds << std::endl; `

at the start and end of the algorithms, respectively (solve_tridiag_general.cpp and solve_tridiag_special.cpp files). The time required is then stored in the `duration_seconds` variable, which will be printed in the console. Compiling the code as described in the instructions of Problem 7 and 9:

`g++ path/to/solve_tridiag_general.cpp -o path/to/solve_tridiag_general.out path/to/src/*.cpp -I ./path/to/include`

To produce more statistically meaningul data, for each given discretization number the timings are collected re running the algorithms a number of times (in this case 100). This can be done with a loop, with the following command line to execute the code:

`for f in {1..100}; do ./path/to/solve_tridiag_general.out < discretization > <output_file = "output.csv"> >> <out_timings = "timings-g-discretization.csv" >; done `

(and similarly for the special algorithm). Note that the output, that is the time required by the algorithm, is redirected to an additional output file. The timings will be collected in each timings*.csv file, then averaged with: `awk '{ total += $1 } END { print total/NR }'  timings-{g-or-s}-discretization.csv `

Additionally, all the timings for different discretization numbers can be collected into one unique file with: `paste -d ',' timings-{file1}.csv timings-{file2}.csv {...}  > timings-{g-or-s}.csv `



