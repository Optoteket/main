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
MIP Presolve eliminated 65525 rows and 32277 columns.
MIP Presolve modified 57723 coefficients.
Reduced MIP has 12497 rows, 13097 columns, and 62290 nonzeros.
Reduced MIP has 12905 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4301138e+07 after 0.33 sec. (466.29 ticks)
Probing fixed 1499 vars, tightened 2 bounds.
Probing changed sense of 48 constraints.
Probing time = 0.03 sec. (14.51 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 4241 rows and 2468 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8019 rows, 10392 columns, and 36056 nonzeros.
Reduced MIP has 10205 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.52 ticks)
Clique table members: 16647.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.16 sec. (128.84 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.43011e+07     2900.0000     3533  100.01%
      0     0      600.0000   413  -5.43011e+07      600.0000     3533  100.00%
*     0+    0                          600.0000      600.0000     3533    0.00%
      0     0        cutoff            600.0000      600.0000     3533    0.00%
Elapsed time = 0.88 sec. (891.57 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.44 sec. (330.62 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.44 sec. (330.62 ticks)

Times (seconds):
Input =  0.057991
Solve =  1.53777
Output = 0.043993
CPLEX 12.5.0.0: optimal integer solution; objective 600
3533 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 14 times. 

display ax;
ax :=
;

option log_file '';
