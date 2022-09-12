Compile code for problem 8:
g++ problem8.cpp -o problem8

As input for Problem 8 we need to run the solution for Problem 7 multiple times to generate data files.
Note the matrix size as parameter is a number ending with 9. This is n. 
I however name the output file 1 digit larger, eg 10. This is nStep.
This might be confusing but seems to be the convention used in course material, so we try to follow it. 

./solve_tridiag_general.out 9        7_10.txt
./solve_tridiag_general.out 99       7_100.txt
./solve_tridiag_general.out 999      7_1000.txt
./solve_tridiag_general.out 9999     7_10000.txt
./solve_tridiag_general.out 99999    7_100000.txt
./solve_tridiag_general.out 999999   7_1000000.txt
./solve_tridiag_general.out 9999999  7_10000000.txt
./solve_tridiag_general.out 99999999 7_100000000.txt


Move all these txt-files from directory Problem-7 to Problem-8. 

Since code for 7 outputs comma character as separator, and problem 8 assumes blank space as separator, run a command to replace this in all files.
sed -i 's/,/ /g' 7_*.txt

Then continue running problem 8 executable:

./problem8 abs_e4.txt rel_e4.txt < 7_10000.txt
./problem8 abs_e3.txt rel_e3.txt < 7_1000.txt
./problem8 abs_e2.txt rel_e2.txt < 7_100.txt
./problem8 abs_e1.txt rel_e1.txt < 7_10.txt
./problem8 abs_e5.txt rel_e5.txt < 7_100000.txt
./problem8 abs_e6.txt rel_e6.txt < 7_1000000.txt
./problem8 abs_e7.txt rel_e7.txt < 7_10000000.txt


Example for creating plot:
python plotter.py --csv abs_error.csv --y 'log10(abs error)' --output p1-8-abs100.pdf --title 'Error for nStep=10' 


python plotter.py --csv abs_e1.txt --y 'log10(abs error)' --output p1-8-abs10.pdf --title 'Error for nStep=e1' 
python plotter.py --csv abs_e2.txt --y 'log10(abs error)' --output p1-8-abs100.pdf --title 'Error for nStep=e2' 
python plotter.py --csv abs_e3.txt --y 'log10(abs error)' --output p1-8-abs1000.pdf --title 'Error for nStep=e3' 
python plotter.py --csv abs_e4.txt --y 'log10(abs error)' --output p1-8-abs10000.pdf --title 'Error for nStep=e4' 
python plotter.py --csv abs_e5.txt --y 'log10(abs error)' --output p1-8-abs100000.pdf --title 'Error for nStep=e5' 
python plotter.py --csv abs_e6.txt --y 'log10(abs error)' --output p1-8-abs1000000.pdf --title 'Error for nStep=e6' 
python plotter.py --csv abs_e7.txt --y 'log10(abs error)' --output p1-8-abs10000000.pdf --title 'Error for nStep=e7' 

python plotter.py --csv rel_e1.txt --y 'log10(rel error)' --output p1-8-rel10.pdf --title 'Relative Error for nStep=e1' 
python plotter.py --csv rel_e2.txt --y 'log10(rel error)' --output p1-8-rel100.pdf --title 'Relative Error for nStep=e2' 
python plotter.py --csv rel_e3.txt --y 'log10(rel error)' --output p1-8-rel1000.pdf --title 'Relative Error for nStep=e3' 
python plotter.py --csv rel_e4.txt --y 'log10(rel error)' --output p1-8-rel10000.pdf --title 'Relative Error for nStep=e4' 
python plotter.py --csv rel_e5.txt --y 'log10(rel error)' --output p1-8-rel100000.pdf --title 'Relative Error for nStep=e5' 
python plotter.py --csv rel_e6.txt --y 'log10(rel error)' --output p1-8-rel1000000.pdf --title 'Relative Error for nStep=e6' 
python plotter.py --csv rel_e7.txt --y 'log10(rel error)' --output p1-8-rel10000000.pdf --title 'Relative Error for nStep=e7' 



python plotter.py --csv abs_e8.txt --y 'log10(abs error)' --output p1-8-abs100000000.pdf --title 'Error for nStep=e4' 


