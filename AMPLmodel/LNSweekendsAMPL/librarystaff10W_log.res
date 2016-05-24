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
MIP Presolve eliminated 65847 rows and 32409 columns.
MIP Presolve modified 58150 coefficients.
Reduced MIP has 12170 rows, 12942 columns, and 59771 nonzeros.
Reduced MIP has 12750 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4101131e+07 after 0.33 sec. (460.68 ticks)
Probing fixed 1424 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.12 ticks)
Cover probing fixed 0 vars, tightened 5 bounds.
MIP Presolve eliminated 3943 rows and 2349 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8012 rows, 10378 columns, and 36014 nonzeros.
Reduced MIP has 10191 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.45 ticks)
Clique table members: 16581.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.15 sec. (124.64 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.41011e+07     2800.0000     3370  100.01%
      0     0      400.0000   388  -5.41011e+07      400.0000     3370  100.00%
*     0+    0                          400.0000      400.0000     3370    0.00%
      0     0        cutoff            400.0000      400.0000     3370    0.00%
Elapsed time = 0.93 sec. (935.76 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.49 sec. (382.90 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.49 sec. (382.90 ticks)

Times (seconds):
Input =  0.056991
Solve =  1.60076
Output = 0.044993
CPLEX 12.5.0.0: optimal integer solution; objective 400
3370 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 2

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 9 times. 

display ax;
ax :=
;

option log_file '';
