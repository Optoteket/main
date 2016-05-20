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
MIP Presolve eliminated 57167 rows and 32376 columns.
MIP Presolve modified 58021 coefficients.
Reduced MIP has 12278 rows, 12983 columns, and 60605 nonzeros.
Reduced MIP has 12791 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4401034e+07 after 0.32 sec. (456.92 ticks)
Probing fixed 1446 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.26 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 4046 rows and 2388 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8006 rows, 10369 columns, and 35976 nonzeros.
Reduced MIP has 10182 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.39 ticks)
Clique table members: 16554.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.16 sec. (127.99 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44010e+07     2600.0000     3493  100.00%
      0     0      600.0000   379  -5.44010e+07      600.0000     3493  100.00%
*     0+    0                          600.0000      600.0000     3493    0.00%
      0     0        cutoff            600.0000      600.0000     3493    0.00%
Elapsed time = 0.94 sec. (972.78 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.51 sec. (422.55 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.51 sec. (422.55 ticks)

Times (seconds):
Input =  0.052992
Solve =  1.67975
Output = 0.036994
CPLEX 12.5.0.0: optimal integer solution; objective 600
3493 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 14 times. 

display ax;
ax :=
;

option log_file '';
