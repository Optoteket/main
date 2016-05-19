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
MIP Presolve eliminated 57695 rows and 32197 columns.
MIP Presolve modified 57361 coefficients.
Reduced MIP has 11691 rows, 12232 columns, and 57846 nonzeros.
Reduced MIP has 12231 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing fixed 1782 vars, tightened 2 bounds.
Probing changed sense of 37 constraints.
Probing time = 0.03 sec. (14.20 ticks)
Cover probing fixed 14 vars, tightened 22 bounds.
MIP Presolve eliminated 4471 rows and 2957 columns.
MIP Presolve modified 2 coefficients.
Reduced MIP has 6907 rows, 8962 columns, and 30529 nonzeros.
Reduced MIP has 8961 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (8.97 ticks)
Clique table members: 17864.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (93.32 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                        -1638.0000    46000.0000     2860     --- 
*     0+    0                         2558.0000    46000.0000     2860     --- 
      0     0     5000.0000   347     2558.0000     5000.0000     2860   95.47%
*     0+    0                         5000.0000     5000.0000     2861    0.00%
      0     0        cutoff           5000.0000     5000.0000     2861    0.00%
Elapsed time = 0.78 sec. (865.30 ticks, tree = 0.00 MB)

Zero-half cuts applied:  1

Root node processing (before b&c):
  Real time             =    0.33 sec. (281.03 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.33 sec. (281.03 ticks)

Times (seconds):
Input =  0.052992
Solve =  1.3438
Output = 0.038994
CPLEX 12.5.0.0: optimal integer solution; objective 5000
2861 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 4 times. 

option log_file '';
