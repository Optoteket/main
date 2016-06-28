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
MIP Presolve eliminated 65540 rows and 32282 columns.
MIP Presolve modified 57718 coefficients.
Reduced MIP has 12487 rows, 13097 columns, and 62164 nonzeros.
Reduced MIP has 12905 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4401039e+07 after 0.33 sec. (471.12 ticks)
Probing fixed 1492 vars, tightened 1 bounds.
Probing changed sense of 48 constraints.
Probing time = 0.03 sec. (14.43 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 4228 rows and 2462 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8018 rows, 10394 columns, and 36053 nonzeros.
Reduced MIP has 10207 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.65 ticks)
Clique table members: 16738.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.14 sec. (118.66 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44010e+07     2900.0000     3352  100.01%
      0     0      400.0000   265  -5.44010e+07      400.0000     3352  100.00%
*     0+    0                          400.0000      400.0000     3352    0.00%
      0     0        cutoff            400.0000      400.0000     3352    0.00%
Elapsed time = 0.82 sec. (864.43 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.38 sec. (298.08 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.38 sec. (298.08 ticks)

Times (seconds):
Input =  0.060989
Solve =  1.3388
Output = 0.044992
CPLEX 12.5.0.0: optimal integer solution; objective 400
3352 MIP simplex iterations
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
