model /edu/emeka813/MasterThesis/AMPLmodel/LNSweekendsAMPL/librarystaff10W.mod;   # Read model file 
data /edu/emeka813/MasterThesis/AMPLmodel/LNSweekendsAMPL/librarystaff10W.dat;    # Read data file 

#expand > /edu/emeka813/MasterThesis/AMPLmodel/LNSweekendsAMPL/librarystaff.res; # Writes all results to file

############################## Add timer parameters #########################
param time_elapsed;
param end;
let time_elapsed := _ampl_time + _total_solve_elapsed_time;

################################# Solve ####################################
solve;
CPLEX 12.5.0.0: timing 1
mipdisplay 2
time = 237600
MIP Presolve eliminated 65865 rows and 32424 columns.
MIP Presolve modified 58148 coefficients.
Reduced MIP has 12151 rows, 12926 columns, and 59600 nonzeros.
Reduced MIP has 12734 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4401231e+07 after 0.32 sec. (460.73 ticks)
Probing fixed 1416 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.12 ticks)
Cover probing fixed 0 vars, tightened 4 bounds.
MIP Presolve eliminated 3935 rows and 2343 columns.
MIP Presolve modified 12 coefficients.
Reduced MIP has 7997 rows, 10364 columns, and 35950 nonzeros.
Reduced MIP has 10177 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.40 ticks)
Clique table members: 16300.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (114.05 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44012e+07     2900.0000     3395  100.01%
      0     0      600.0000   188  -5.44012e+07      600.0000     3395  100.00%
*     0+    0                      -899406.0000      600.0000     3395  100.07%
*     0+    0                          600.0000      600.0000     3534    0.00%
      0     0        cutoff            600.0000      600.0000     3534    0.00%
Elapsed time = 0.77 sec. (849.79 ticks, tree = 0.00 MB)

Clique cuts applied:  8
Cover cuts applied:  4
Mixed integer rounding cuts applied:  4
Zero-half cuts applied:  10
Gomory fractional cuts applied:  2

Root node processing (before b&c):
  Real time             =    0.34 sec. (296.38 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.34 sec. (296.38 ticks)

Times (seconds):
Input =  0.05999
Solve =  1.21781
Output = 0.043994
CPLEX 12.5.0.0: optimal integer solution; objective 600
3534 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 16 times. 

display ax;
ax :=
;

option log_file '';
