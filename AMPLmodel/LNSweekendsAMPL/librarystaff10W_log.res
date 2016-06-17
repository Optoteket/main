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
MIP Presolve eliminated 65799 rows and 32397 columns.
MIP Presolve modified 58116 coefficients.
Reduced MIP has 12203 rows, 12959 columns, and 60067 nonzeros.
Reduced MIP has 12767 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4101132e+07 after 0.32 sec. (462.58 ticks)
Probing fixed 1430 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.22 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 3970 rows and 2360 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8014 rows, 10380 columns, and 36023 nonzeros.
Reduced MIP has 10193 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.32 ticks)
Clique table members: 16226.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.20 sec. (150.08 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.41011e+07     2700.0000     3626  100.00%
      0     0      600.0000   208  -5.41011e+07      600.0000     3626  100.00%
*     0+    0                     -1699410.0000      600.0000     3626  100.04%
*     0+    0                      -299400.0000      600.0000     3644  100.20%
      0     0      600.0000    28  -299400.0000       Cuts: 4     3644  100.20%
*     0+    0                      -199401.0000      600.0000     3644  100.30%
      0     0      600.0000    62  -199401.0000      Cuts: 24     3690  100.30%
*     0+    0                       -99406.0000      600.0000     3690  100.60%
*     0+    0                          600.0000      600.0000     3690    0.00%
      0     0        cutoff            600.0000      600.0000     3690    0.00%
Elapsed time = 1.10 sec. (1100.53 ticks, tree = 0.00 MB)

Clique cuts applied:  6
Cover cuts applied:  2
Mixed integer rounding cuts applied:  2
Zero-half cuts applied:  6
Gomory fractional cuts applied:  2

Root node processing (before b&c):
  Real time             =    0.67 sec. (545.51 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.67 sec. (545.51 ticks)

Times (seconds):
Input =  0.055991
Solve =  1.9707
Output = 0.043993
CPLEX 12.5.0.0: optimal integer solution; objective 600
3690 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 15 times. 

display ax;
ax :=
;

option log_file '';
