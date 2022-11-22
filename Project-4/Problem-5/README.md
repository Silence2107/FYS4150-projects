
# Problem 5 manual

To evaluate the burn-in time, the programme is run with increasing number of MC cycles, monitoring the average energy and magnetization per spin. For info on the code, refer to Project-4/Problem-4.

Qualitative analysis can be done by repeating the study at T=1.0J/KB and T=2.4J/kB, both in the case of an ordered and unordered system as starting initial states. 

- first, the programme is compiled according to instructions, which will produce an .exe file; by default, the programme assumed a random state as initial.
- the programme is then executed varying the number of MC cycles performed, at both temperatures. This can be conventiently done in one step running the p4-5a.sh bash script in the command line 
- the script will collect the results for energy and magnetization in output csv files;
- steps above are repeated recompiling the programme such to start from an ordered state.i
- the results can be plotted with a Python script, running in the command line: 
  
`python3 plotter.py --files output-ord-T1-e.csv output-ord-T2-e.csv output-rand-T1-e.csv output-rand-T2-e.csv --output plot-e.pdf  --labels "T=1.0J/kB(ord)" "T=2.4J/kB(ord)" "T=1.0J/kB(unord)" "T=2.4J/kB(unord)" --lstyle "solid" "solid" "dashed" "dashed" --lcolor b r b r`

(for the energy and analogously for the magnetization)
- two plots should be obtained, displaying the time evolution of energy and magnetization at different conditions.

