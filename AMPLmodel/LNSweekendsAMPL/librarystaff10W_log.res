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
MIP Presolve eliminated 57794 rows and 32218 columns.
MIP Presolve modified 57587 coefficients.
Reduced MIP has 11587 rows, 12207 columns, and 56854 nonzeros.
Reduced MIP has 12206 binaries, 1 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -1849.000000 after 0.34 sec. (499.56 ticks)
Probing fixed 1816 vars, tightened 0 bounds.
Probing changed sense of 36 constraints.
Probing time = 0.03 sec. (14.16 ticks)
Cover probing fixed 14 vars, tightened 23 bounds.
MIP Presolve eliminated 4414 rows and 2993 columns.
MIP Presolve modified 2 coefficients.
Reduced MIP has 6856 rows, 8897 columns, and 30273 nonzeros.
Reduced MIP has 8896 binaries, 1 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (9.28 ticks)
Clique table members: 17597.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.12 sec. (91.09 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                          627.0000    51000.0000     2817     --- 
      0     0    15000.0000   453      627.0000    15000.0000     2817     --- 
*     0+    0                        13000.0000    15000.0000     2820   15.38%
      0     0    15000.0000    11    13000.0000      Fract: 1     2820   15.38%
*     0+    0                        15000.0000    15000.0000     2820    0.00%
      0     0        cutoff          15000.0000    15000.0000     2820    0.00%
Elapsed time = 0.89 sec. (961.11 ticks, tree = 0.00 MB)

Gomory fractional cuts applied:  1

Root node processing (before b&c):
  Real time             =    0.43 sec. (361.21 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.43 sec. (361.21 ticks)

Times (seconds):
Input =  0.05699
Solve =  1.26481
Output = 0.037995
CPLEX 12.5.0.0: optimal integer solution; objective 15000
2820 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 6 times. 

option log_file '';
