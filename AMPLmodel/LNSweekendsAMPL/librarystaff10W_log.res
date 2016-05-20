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
MIP Presolve eliminated 57253 rows and 32412 columns.
MIP Presolve modified 58099 coefficients.
Reduced MIP has 12188 rows, 12943 columns, and 59953 nonzeros.
Reduced MIP has 12751 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4301233e+07 after 0.32 sec. (455.26 ticks)
Probing fixed 1423 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.15 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 3966 rows and 2355 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8002 rows, 10368 columns, and 35993 nonzeros.
Reduced MIP has 10181 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.46 ticks)
Clique table members: 16296.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.15 sec. (125.15 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.43012e+07     2900.0000     3446  100.01%
      0     0      400.0000   260  -5.43012e+07      400.0000     3446  100.00%
*     0+    0                     -1899618.0000      400.0000     3446  100.02%
*     0+    0                          293.0000      400.0000     3449   36.52%
*     0     0      integral     0      400.0000       Cuts: 6     3449    0.00%
      0     0        cutoff            400.0000      400.0000     3449    0.00%
Elapsed time = 0.86 sec. (893.24 ticks, tree = 0.00 MB)

Clique cuts applied:  2
Cover cuts applied:  1
Mixed integer rounding cuts applied:  1
Gomory fractional cuts applied:  2

Root node processing (before b&c):
  Real time             =    0.43 sec. (345.74 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.43 sec. (345.74 ticks)

Times (seconds):
Input =  0.055991
Solve =  1.47178
Output = 0.040994
CPLEX 12.5.0.0: optimal integer solution; objective 400
3449 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 7 times. 

display ax;
ax :=
;

option log_file '';
