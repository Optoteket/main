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
MIP Presolve eliminated 65732 rows and 32371 columns.
MIP Presolve modified 57988 coefficients.
Reduced MIP has 12297 rows, 12992 columns, and 60854 nonzeros.
Reduced MIP has 12800 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4401235e+07 after 0.33 sec. (466.19 ticks)
Probing fixed 1444 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.27 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 4060 rows and 2391 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8007 rows, 10371 columns, and 35991 nonzeros.
Reduced MIP has 10184 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.03 sec. (10.36 ticks)
Clique table members: 16375.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (110.47 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44012e+07     2700.0000     3288  100.00%
      0     0      400.0000   298  -5.44012e+07      400.0000     3288  100.00%
*     0+    0                     -1499605.0000      400.0000     3288  100.03%
*     0+    0                          400.0000      400.0000     3288    0.00%
      0     0        cutoff            400.0000      400.0000     3288    0.00%
Elapsed time = 0.80 sec. (841.52 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.36 sec. (281.86 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.36 sec. (281.86 ticks)

Times (seconds):
Input =  0.055991
Solve =  1.25581
Output = 0.044993
CPLEX 12.5.0.0: optimal integer solution; objective 400
3288 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 7 times. 

display ax;
ax :=
;

option log_file '';
