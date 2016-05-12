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
MIP Presolve eliminated 57452 rows and 30665 columns.
MIP Presolve modified 57905 coefficients.
Reduced MIP has 13065 rows, 14453 columns, and 71383 nonzeros.
Reduced MIP has 14452 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing fixed 2449 vars, tightened 1 bounds.
Probing changed sense of 134 constraints.
Probing time = 0.04 sec. (22.28 ticks)
Cover probing fixed 29 vars, tightened 91 bounds.
MIP Presolve eliminated 4862 rows and 2934 columns.
MIP Presolve modified 12 coefficients.
Reduced MIP has 8107 rows, 11423 columns, and 40132 nonzeros.
Reduced MIP has 11422 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.01 sec. (3.06 ticks)
Clique table members: 5886.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.28 sec. (152.78 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                        -1628.0000    23000.0000     3613     --- 
*     0+    0                          500.0000    23000.0000     3613     --- 
      0     0     4000.0000   486      500.0000     4000.0000     3613  700.00%
*     0+    0                         4000.0000     4000.0000     3613    0.00%
      0     0        cutoff           4000.0000     4000.0000     3613    0.00%
Elapsed time = 1.23 sec. (1234.61 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.55 sec. (359.70 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.55 sec. (359.70 ticks)

Times (seconds):
Input =  0.05399
Solve =  2.58061
Output = 0.041993
CPLEX 12.5.0.0: optimal integer solution; objective 4000
3613 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 23 times. 

option log_file '';
