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
MIP Presolve eliminated 66061 rows and 32668 columns.
MIP Presolve modified 57737 coefficients.
Reduced MIP has 11956 rows, 12701 columns, and 59221 nonzeros.
Reduced MIP has 12509 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.3901102e+07 after 0.34 sec. (479.08 ticks)
Probing fixed 1162 vars, tightened 0 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.45 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 3714 rows and 2078 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8013 rows, 10394 columns, and 36067 nonzeros.
Reduced MIP has 10207 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.03 sec. (11.29 ticks)
Clique table members: 16699.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.16 sec. (129.46 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.39011e+07     3000.0000     3325  100.01%
      0     0      599.0000   653  -5.39011e+07      599.0000     3325  100.00%
*     0+    0                       -99403.0000      599.0000     3325  100.60%
*     0+    0                          599.0000      599.0000     3325    0.00%
      0     0        cutoff            599.0000      599.0000     3325    0.00%
Elapsed time = 0.98 sec. (993.05 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.53 sec. (421.88 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.53 sec. (421.88 ticks)

Times (seconds):
Input =  0.05799
Solve =  1.66375
Output = 0.045993
CPLEX 12.5.0.0: optimal integer solution; objective 599
3325 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 11 times. 

display ax;
ax :=
;

option log_file '';
