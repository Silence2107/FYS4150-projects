Compile:
g++ problem8.cpp -o problem8

Run example:
./problem8 < ./sol_nsteps100.txt


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


