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
MIP Presolve eliminated 65872 rows and 32426 columns.
MIP Presolve modified 58162 coefficients.
Reduced MIP has 12144 rows, 12924 columns, and 59501 nonzeros.
Reduced MIP has 12732 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4101031e+07 after 0.33 sec. (462.03 ticks)
Probing fixed 1414 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.06 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 3924 rows and 2341 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8002 rows, 10365 columns, and 35965 nonzeros.
Reduced MIP has 10178 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.27 ticks)
Clique table members: 15946.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.17 sec. (126.80 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.41010e+07     2800.0000     3581  100.01%
      0     0      200.0000   314  -5.41010e+07      200.0000     3581  100.00%
*     0+    0                     -1299816.0000      200.0000     3581  100.02%
*     0+    0                          200.0000      200.0000     3581    0.00%
      0     0        cutoff            200.0000      200.0000     3581    0.00%
Elapsed time = 0.81 sec. (896.97 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.37 sec. (342.32 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.37 sec. (342.32 ticks)

Times (seconds):
Input =  0.059991
Solve =  1.3188
Output = 0.046992
CPLEX 12.5.0.0: optimal integer solution; objective 200
3581 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 3 times. 

display ax;
ax :=
;

option log_file '';
