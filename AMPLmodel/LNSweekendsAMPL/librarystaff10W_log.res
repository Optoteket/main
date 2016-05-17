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
MIP Presolve eliminated 58997 rows and 31427 columns.
MIP Presolve modified 58530 coefficients.
Reduced MIP has 11533 rows, 13706 columns, and 57227 nonzeros.
Reduced MIP has 13705 binaries, 1 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -1792.000000 after 0.42 sec. (610.76 ticks)
Probing fixed 1827 vars, tightened 0 bounds.
Probing changed sense of 82 constraints.
Probing time = 0.04 sec. (19.59 ticks)
Cover probing fixed 0 vars, tightened 33 bounds.
MIP Presolve eliminated 3445 rows and 2214 columns.
MIP Presolve modified 10 coefficients.
Reduced MIP has 8011 rows, 11415 columns, and 36610 nonzeros.
Reduced MIP has 11414 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.01 sec. (3.12 ticks)
Clique table members: 6707.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (103.18 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                        -1792.0000    22000.0000     3151     --- 
      0     0     4000.0000   217    -1792.0000     4000.0000     3151  323.21%
*     0+    0                         4000.0000     4000.0000     3151    0.00%
      0     0        cutoff           4000.0000     4000.0000     3151    0.00%
Elapsed time = 0.87 sec. (1025.19 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.30 sec. (282.20 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.30 sec. (282.20 ticks)

Times (seconds):
Input =  0.054991
Solve =  1.34379
Output = 0.037994
CPLEX 12.5.0.0: optimal integer solution; objective 4000
3151 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 0
min_ass = 4

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 24 times. 

option log_file '';
