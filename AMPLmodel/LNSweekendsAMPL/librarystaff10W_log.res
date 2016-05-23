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
MIP Presolve eliminated 65920 rows and 32577 columns.
MIP Presolve modified 57740 coefficients.
Reduced MIP has 12121 rows, 12796 columns, and 60109 nonzeros.
Reduced MIP has 12604 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.3901006e+07 after 0.33 sec. (481.17 ticks)
Probing fixed 1238 vars, tightened 0 bounds.
Probing changed sense of 48 constraints.
Probing time = 0.03 sec. (14.14 ticks)
Cover probing fixed 0 vars, tightened 4 bounds.
MIP Presolve eliminated 3871 rows and 2169 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8012 rows, 10389 columns, and 36046 nonzeros.
Reduced MIP has 10202 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.68 ticks)
Clique table members: 16666.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.17 sec. (115.12 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.39010e+07     2900.0000     3298  100.01%
      0     0      600.0000   350  -5.39010e+07      600.0000     3298  100.00%
*     0+    0                     -2399425.0000      600.0000     3298  100.03%
*     0+    0                          600.0000      600.0000     3298    0.00%
      0     0        cutoff            600.0000      600.0000     3298    0.00%
Elapsed time = 0.92 sec. (989.02 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.48 sec. (416.38 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.48 sec. (416.38 ticks)

Times (seconds):
Input =  0.055991
Solve =  1.61275
Output = 0.042993
CPLEX 12.5.0.0: optimal integer solution; objective 600
3298 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 15 times. 

display ax;
ax :=
;

option log_file '';
