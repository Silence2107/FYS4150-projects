Compile:
g++ problem8.cpp -o problem8

Run example:
./problem8 < ./sol_nsteps100.txt


Example for creating plot:
python plotter.py --csv abs_error.csv --y 'log10(abs error)' --output p1-8-abs100.pdf --title 'Error for nStep=10' 



