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
MIP Presolve eliminated 57737 rows and 32242 columns.
MIP Presolve modified 57388 coefficients.
Reduced MIP has 11666 rows, 12204 columns, and 57720 nonzeros.
Reduced MIP has 12203 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing fixed 1769 vars, tightened 1 bounds.
Probing changed sense of 38 constraints.
Probing time = 0.03 sec. (14.24 ticks)
Cover probing fixed 14 vars, tightened 24 bounds.
MIP Presolve eliminated 4450 rows and 2937 columns.
Reduced MIP has 6899 rows, 8950 columns, and 30492 nonzeros.
Reduced MIP has 8949 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (9.04 ticks)
Clique table members: 17833.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.10 sec. (82.07 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                        -1636.0000    23000.0000     2673     --- 
*     0+    0                         1548.0000    23000.0000     2673     --- 
      0     0     4000.0000   236     1548.0000     4000.0000     2673  158.40%
*     0+    0                         4000.0000     4000.0000     2673    0.00%
      0     0        cutoff           4000.0000     4000.0000     2673    0.00%
Elapsed time = 0.72 sec. (810.66 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.28 sec. (225.84 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.28 sec. (225.84 ticks)

Times (seconds):
Input =  0.052992
Solve =  1.22481
Output = 0.039993
CPLEX 12.5.0.0: optimal integer solution; objective 4000
2673 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 7 times. 

option log_file '';
