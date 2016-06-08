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
MIP Presolve eliminated 65331 rows and 32161 columns.
MIP Presolve modified 57566 coefficients.
Reduced MIP has 12680 rows, 13201 columns, and 63704 nonzeros.
Reduced MIP has 13011 binaries, 190 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4501245e+07 after 0.34 sec. (480.94 ticks)
Probing fixed 1549 vars, tightened 1 bounds.
Probing changed sense of 50 constraints.
Probing time = 0.03 sec. (14.57 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 4405 rows and 2564 columns.
MIP Presolve modified 17 coefficients.
Reduced MIP has 8015 rows, 10377 columns, and 36018 nonzeros.
Reduced MIP has 10193 binaries, 184 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.49 ticks)
Clique table members: 16993.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.17 sec. (134.49 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.45012e+07     2700.0000     3534  100.00%
      0     0      599.0000   348  -5.45012e+07      599.0000     3534  100.00%
*     0+    0                     -1999409.0000      599.0000     3534  100.03%
*     0+    0                          599.0000      599.0000     3534    0.00%
      0     0        cutoff            599.0000      599.0000     3534    0.00%
Elapsed time = 0.97 sec. (981.88 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.51 sec. (406.22 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.51 sec. (406.22 ticks)

Times (seconds):
Input =  0.06099
Solve =  1.64875
Output = 0.044994
CPLEX 12.5.0.0: optimal integer solution; objective 599
3534 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 10 times. 

display ax;
ax :=
;

option log_file '';
