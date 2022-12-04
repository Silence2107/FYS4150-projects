# Problem 5 manual
Next step is to prepare grounds for many-slit simulations. With a library addon we can prepare a unit test for the many-slit simulation. Here we only make sure the potential we simulate is set up correctly on the grid.

# Usage
The code is mostly confined to the `many_slit_potential_unit_test.sh` script. Typical usage is
```
./many_slit_potential_unit_test.sh -n 2 -f temp.pdf
```
, where the `-n` flag sets the number of slits and the `-f` flag sets the output file. The output file is a pdf file with the potential plotted.

Should you have desire to simulate more flexible slits, you are welcome to change corresponding settings in the `many_slit_potential_unit_test.cpp` script.

P.S. The script is not quick due to recompilations, but it is not the point of this exercise.