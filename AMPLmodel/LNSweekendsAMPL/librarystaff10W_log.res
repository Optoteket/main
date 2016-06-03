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
MIP Presolve eliminated 65670 rows and 32412 columns.
MIP Presolve modified 57881 coefficients.
Reduced MIP has 12354 rows, 12965 columns, and 61310 nonzeros.
Reduced MIP has 12773 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4301129e+07 after 0.33 sec. (470.27 ticks)
Probing fixed 1382 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.28 ticks)
Cover probing fixed 0 vars, tightened 4 bounds.
MIP Presolve eliminated 4100 rows and 2339 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8015 rows, 10387 columns, and 36037 nonzeros.
Reduced MIP has 10200 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.78 ticks)
Cover probing fixed 0 vars, tightened 1 bounds.
Clique table members: 16380.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.17 sec. (138.29 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.43011e+07     3000.0000     3583  100.01%
      0     0      599.0000   306  -5.43011e+07      599.0000     3583  100.00%
*     0+    0                     -2099409.0000      599.0000     3583  100.03%
*     0+    0                          599.0000      599.0000     3583    0.00%
      0     0        cutoff            599.0000      599.0000     3583    0.00%
Elapsed time = 0.95 sec. (886.32 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.51 sec. (322.61 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.51 sec. (322.61 ticks)

Times (seconds):
Input =  0.06099
Solve =  1.60676
Output = 0.044993
CPLEX 12.5.0.0: optimal integer solution; objective 599
3583 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 15 times. 

display ax;
ax :=
;

option log_file '';
