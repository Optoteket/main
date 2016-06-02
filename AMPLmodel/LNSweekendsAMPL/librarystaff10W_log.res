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
MIP Presolve eliminated 65473 rows and 32255 columns.
MIP Presolve modified 57661 coefficients.
Reduced MIP has 12556 rows, 13126 columns, and 62797 nonzeros.
Reduced MIP has 12934 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4501239e+07 after 0.32 sec. (470.01 ticks)
Probing fixed 1516 vars, tightened 2 bounds.
Probing changed sense of 48 constraints.
Probing time = 0.03 sec. (14.48 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 4295 rows and 2491 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8020 rows, 10394 columns, and 36066 nonzeros.
Reduced MIP has 10207 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (11.28 ticks)
Cover probing fixed 0 vars, tightened 1 bounds.
Clique table members: 16744.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.21 sec. (153.14 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.45012e+07     3000.0000     3579  100.01%
      0     0      600.0000   423  -5.45012e+07      600.0000     3579  100.00%
*     0+    0                          600.0000      600.0000     3579    0.00%
      0     0        cutoff            600.0000      600.0000     3579    0.00%
Elapsed time = 1.02 sec. (939.18 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.58 sec. (374.20 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.58 sec. (374.20 ticks)

Times (seconds):
Input =  0.055991
Solve =  1.76273
Output = 0.043994
CPLEX 12.5.0.0: optimal integer solution; objective 600
3579 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 12 times. 

display ax;
ax :=
;

option log_file '';
