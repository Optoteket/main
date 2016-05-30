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
MIP Presolve eliminated 65647 rows and 32321 columns.
MIP Presolve modified 57997 coefficients.
Reduced MIP has 12366 rows, 13045 columns, and 60936 nonzeros.
Reduced MIP has 12853 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4501135e+07 after 0.33 sec. (465.64 ticks)
Probing fixed 1491 vars, tightened 1 bounds.
Probing changed sense of 48 constraints.
Probing time = 0.03 sec. (14.28 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 4127 rows and 2444 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8006 rows, 10368 columns, and 35961 nonzeros.
Reduced MIP has 10181 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.65 ticks)
Clique table members: 16497.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.15 sec. (112.64 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.45011e+07     2900.0000     3298  100.01%
      0     0      400.0000   293  -5.45011e+07      400.0000     3298  100.00%
*     0+    0                     -1799606.0000      400.0000     3298  100.02%
*     0+    0                          400.0000      400.0000     3298    0.00%
      0     0        cutoff            400.0000      400.0000     3298    0.00%
Elapsed time = 0.89 sec. (904.60 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.44 sec. (345.28 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.44 sec. (345.28 ticks)

Times (seconds):
Input =  0.056991
Solve =  1.45878
Output = 0.043994
CPLEX 12.5.0.0: optimal integer solution; objective 400
3298 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 10 times. 

display ax;
ax :=
;

option log_file '';
