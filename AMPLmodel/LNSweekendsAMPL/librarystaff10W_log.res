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
MIP Presolve eliminated 56773 rows and 32162 columns.
MIP Presolve modified 57566 coefficients.
Reduced MIP has 12677 rows, 13199 columns, and 63681 nonzeros.
Reduced MIP has 13009 binaries, 190 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4501345e+07 after 0.33 sec. (475.35 ticks)
Probing fixed 1559 vars, tightened 2 bounds.
Probing changed sense of 50 constraints.
Probing time = 0.03 sec. (14.49 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 4412 rows and 2579 columns.
MIP Presolve modified 17 coefficients.
Reduced MIP has 8004 rows, 10359 columns, and 35946 nonzeros.
Reduced MIP has 10175 binaries, 184 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.46 ticks)
Clique table members: 16678.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (100.71 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.45013e+07     2800.0000     3246  100.01%
      0     0      400.0000    88  -5.45013e+07      400.0000     3246  100.00%
*     0+    0                      -999603.0000      400.0000     3246  100.04%
*     0+    0                          400.0000      400.0000     3246    0.00%
      0     0        cutoff            400.0000      400.0000     3246    0.00%
Elapsed time = 0.75 sec. (878.42 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.31 sec. (307.68 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.31 sec. (307.68 ticks)

Times (seconds):
Input =  0.052992
Solve =  1.19882
Output = 0.038994
CPLEX 12.5.0.0: optimal integer solution; objective 400
3246 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 8 times. 

display ax;
ax :=
;

option log_file '';
