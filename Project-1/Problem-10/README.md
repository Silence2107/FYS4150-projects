# Problem 2 manual

## Comparing timings
 
The timings required by each algorithm are extracted using the chrono library. To do so, the algorithms for the special and general algorithms ( are run adding the following lines:
 
`auto t1 = std::chrono::high_resolution_clock::now();`

and

`auto t2 = std::chrono::high_resolution_clock::now();`

`double duration_seconds = std::chrono::duration<double>(t2 - t1).count();`

and the start and end of the algorithms, respectively.

The time required is then stored in the `duration_seconds` variable;



