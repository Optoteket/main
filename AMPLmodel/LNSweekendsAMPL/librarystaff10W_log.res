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
MIP Presolve eliminated 57261 rows and 32413 columns.
MIP Presolve modified 57979 coefficients.
Reduced MIP has 12185 rows, 12946 columns, and 60165 nonzeros.
Reduced MIP has 12754 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4301332e+07 after 0.31 sec. (456.60 ticks)
Probing fixed 1400 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.17 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 3949 rows and 2334 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8015 rows, 10391 columns, and 36063 nonzeros.
Reduced MIP has 10204 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.68 ticks)
Clique table members: 16862.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.15 sec. (120.84 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.43013e+07     2800.0000     3474  100.01%
      0     0      400.0000   189  -5.43013e+07      400.0000     3474  100.00%
*     0+    0                      -799602.0000      400.0000     3474  100.05%
*     0+    0                          400.0000      400.0000     3484    0.00%
      0     0        cutoff            400.0000      400.0000     3484    0.00%
Elapsed time = 0.79 sec. (877.45 ticks, tree = 0.00 MB)

GUB cover cuts applied:  1
Clique cuts applied:  4
Mixed integer rounding cuts applied:  1
Zero-half cuts applied:  5
Gomory fractional cuts applied:  2

Root node processing (before b&c):
  Real time             =    0.36 sec. (327.62 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.36 sec. (327.62 ticks)

Times (seconds):
Input =  0.052991
Solve =  1.3198
Output = 0.038994
CPLEX 12.5.0.0: optimal integer solution; objective 400
3484 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 10 times. 

display ax;
ax :=
;

option log_file '';
