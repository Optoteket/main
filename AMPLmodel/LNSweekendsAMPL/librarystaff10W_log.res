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
MIP Presolve eliminated 57242 rows and 31961 columns.
MIP Presolve modified 56938 coefficients.
Reduced MIP has 12152 rows, 12474 columns, and 61111 nonzeros.
Reduced MIP has 12473 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing fixed 1954 vars, tightened 2 bounds.
Probing changed sense of 38 constraints.
Probing time = 0.03 sec. (14.38 ticks)
Cover probing fixed 14 vars, tightened 22 bounds.
MIP Presolve eliminated 4935 rows and 3221 columns.
MIP Presolve modified 2 coefficients.
Reduced MIP has 6856 rows, 8892 columns, and 30211 nonzeros.
Reduced MIP has 8891 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (9.11 ticks)
Clique table members: 17168.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (85.05 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                        -1629.0000    24000.0000     2795     --- 
*     0+    0                          553.0000    24000.0000     2795     --- 
      0     0     5999.0000   181      553.0000     5999.0000     2795  984.81%
*     0+    0                         4999.0000     5999.0000     2818   20.00%
      0     0     5999.0000    32     4999.0000       Cuts: 9     2818   20.00%
      0     0     5999.0000    96     4999.0000      Cuts: 29     2867   20.00%
*     0+    0                         5999.0000     5999.0000     2867    0.00%
      0     0        cutoff           5999.0000     5999.0000     2867    0.00%
Elapsed time = 0.92 sec. (983.53 ticks, tree = 0.00 MB)

GUB cover cuts applied:  3
Clique cuts applied:  12
Cover cuts applied:  3
Zero-half cuts applied:  1
Gomory fractional cuts applied:  3

Root node processing (before b&c):
  Real time             =    0.47 sec. (381.78 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.47 sec. (381.78 ticks)

Times (seconds):
Input =  0.054992
Solve =  1.63075
Output = 0.038995
CPLEX 12.5.0.0: optimal integer solution; objective 5999
2867 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 16 times. 

option log_file '';
