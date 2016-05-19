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
MIP Presolve eliminated 57811 rows and 32261 columns.
MIP Presolve modified 57503 coefficients.
Reduced MIP has 11588 rows, 12182 columns, and 56986 nonzeros.
Reduced MIP has 12181 binaries, 1 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -1850.000000 after 0.34 sec. (498.61 ticks)
Probing fixed 1759 vars, tightened 0 bounds.
Probing changed sense of 37 constraints.
Probing time = 0.03 sec. (14.08 ticks)
Cover probing fixed 14 vars, tightened 23 bounds.
MIP Presolve eliminated 4378 rows and 2924 columns.
MIP Presolve modified 2 coefficients.
Reduced MIP has 6897 rows, 8945 columns, and 30449 nonzeros.
Reduced MIP has 8944 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (9.28 ticks)
Clique table members: 17480.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.11 sec. (87.79 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                         -367.0000    51000.0000     2802     --- 
      0     0    10000.0000   403     -367.0000    10000.0000     2802     --- 
*     0+    0                        10000.0000    10000.0000     2802    0.00%
      0     0        cutoff          10000.0000    10000.0000     2802    0.00%
Elapsed time = 0.71 sec. (833.01 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.26 sec. (235.45 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.26 sec. (235.45 ticks)

Times (seconds):
Input =  0.051992
Solve =  0.891865
Output = 0.037994
CPLEX 12.5.0.0: optimal integer solution; objective 10000
2802 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 6 times. 

option log_file '';
