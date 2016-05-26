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
MIP Presolve eliminated 65713 rows and 32374 columns.
MIP Presolve modified 57832 coefficients.
Reduced MIP has 12298 rows, 12990 columns, and 61082 nonzeros.
Reduced MIP has 12798 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4501235e+07 after 0.33 sec. (461.76 ticks)
Probing fixed 1423 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.35 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 4055 rows and 2374 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8018 rows, 10391 columns, and 36048 nonzeros.
Reduced MIP has 10204 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.03 sec. (10.55 ticks)
Clique table members: 16369.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (102.76 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.45012e+07     2800.0000     3335  100.01%
      0     0      400.0000   130  -5.45012e+07      400.0000     3335  100.00%
*     0+    0                          400.0000      400.0000     3335    0.00%
      0     0        cutoff            400.0000      400.0000     3335    0.00%
Elapsed time = 0.79 sec. (825.09 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.35 sec. (268.83 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.35 sec. (268.83 ticks)

Times (seconds):
Input =  0.061989
Solve =  1.3088
Output = 0.044994
CPLEX 12.5.0.0: optimal integer solution; objective 400
3335 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 5 times. 

display ax;
ax :=
;

option log_file '';
