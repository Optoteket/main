model /edu/emeka813/MasterThesis/LNS/LNS_tasks/src/LNSweekendsAMPL/librarystaff10W.mod;   # Read model file 
data /edu/emeka813/MasterThesis/LNS/LNS_tasks/src/LNSweekendsAMPL/librarystaff10W.dat;    # Read data file 

#expand > /edu/emeka813/MasterThesis/LNS/LNS_tasks/src/LNSweekendsAMPL/librarystaff.res; # Writes all results to file

############################## Add timer parameters #########################
param time_elapsed;
param end;
let time_elapsed := _ampl_time + _total_solve_elapsed_time;

################################# Solve ####################################
solve;
CPLEX 12.5.0.0: timing 1
mipdisplay 2
time = 237600
MIP Presolve eliminated 65860 rows and 32499 columns.
MIP Presolve modified 58106 coefficients.
Reduced MIP has 12141 rows, 12856 columns, and 59671 nonzeros.
Reduced MIP has 12664 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4201221e+07 after 0.32 sec. (465.58 ticks)
Probing fixed 1337 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.23 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 3923 rows and 2264 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 7994 rows, 10368 columns, and 35963 nonzeros.
Reduced MIP has 10181 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.32 ticks)
Clique table members: 16255.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.15 sec. (116.27 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.42012e+07     2500.0000     3281  100.00%
      0     0      400.0000   143  -5.42012e+07      400.0000     3281  100.00%
*     0+    0                     -1099608.0000      400.0000     3281  100.04%
*     0+    0                          400.0000      400.0000     3281    0.00%
      0     0        cutoff            400.0000      400.0000     3281    0.00%
Elapsed time = 0.76 sec. (801.93 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.33 sec. (244.82 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.33 sec. (244.82 ticks)

Times (seconds):
Input =  0.058991
Solve =  1.22181
Output = 0.042994
CPLEX 12.5.0.0: optimal integer solution; objective 400
3281 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 8 times. 

display ax;
ax :=
;

option log_file '';
