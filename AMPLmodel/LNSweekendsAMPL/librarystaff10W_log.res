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
MIP Presolve eliminated 65933 rows and 32532 columns.
MIP Presolve modified 58169 coefficients.
Reduced MIP has 12066 rows, 12821 columns, and 59156 nonzeros.
Reduced MIP has 12629 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4101119e+07 after 0.34 sec. (467.34 ticks)
Probing fixed 1316 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.03 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 3852 rows and 2234 columns.
MIP Presolve modified 12 coefficients.
Reduced MIP has 7995 rows, 10368 columns, and 35980 nonzeros.
Reduced MIP has 10181 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.03 sec. (10.59 ticks)
Clique table members: 16513.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.11 sec. (92.22 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.41011e+07     2800.0000     3011  100.01%
      0     0      400.0000   138  -5.41011e+07      400.0000     3011  100.00%
*     0+    0                      -999607.0000      400.0000     3011  100.04%
*     0+    0                      -299922.0000      400.0000     3011  100.13%
*     0+    0                          400.0000      400.0000     3011    0.00%
      0     0        cutoff            400.0000      400.0000     3011    0.00%
Elapsed time = 0.76 sec. (787.98 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.31 sec. (229.60 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.31 sec. (229.60 ticks)

Times (seconds):
Input =  0.05999
Solve =  1.19182
Output = 0.043993
CPLEX 12.5.0.0: optimal integer solution; objective 400
3011 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 6 times. 

display ax;
ax :=
;

option log_file '';
