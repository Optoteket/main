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
MIP Presolve eliminated 65902 rows and 32443 columns.
MIP Presolve modified 58212 coefficients.
Reduced MIP has 12093 rows, 12906 columns, and 59236 nonzeros.
Reduced MIP has 12714 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4100929e+07 after 0.34 sec. (461.02 ticks)
Probing fixed 1411 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.09 ticks)
MIP Presolve eliminated 3888 rows and 2328 columns.
MIP Presolve modified 12 coefficients.
Reduced MIP has 7993 rows, 10366 columns, and 35967 nonzeros.
Reduced MIP has 10179 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (11.33 ticks)
Clique table members: 16653.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.16 sec. (114.12 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.41009e+07     3000.0000     3358  100.01%
      0     0      599.0000   324  -5.41009e+07      599.0000     3358  100.00%
*     0+    0                     -2399425.0000      599.0000     3358  100.02%
*     0+    0                          599.0000      599.0000     3358    0.00%
      0     0        cutoff            599.0000      599.0000     3358    0.00%
Elapsed time = 0.86 sec. (849.72 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.41 sec. (297.67 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.41 sec. (297.67 ticks)

Times (seconds):
Input =  0.05999
Solve =  1.48777
Output = 0.043993
CPLEX 12.5.0.0: optimal integer solution; objective 599
3358 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 14 times. 

display ax;
ax :=
;

option log_file '';
