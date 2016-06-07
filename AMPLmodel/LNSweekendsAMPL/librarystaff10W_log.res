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
MIP Presolve eliminated 65709 rows and 32355 columns.
MIP Presolve modified 57954 coefficients.
Reduced MIP has 12305 rows, 13012 columns, and 61143 nonzeros.
Reduced MIP has 12820 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4400938e+07 after 0.32 sec. (464.71 ticks)
Probing fixed 1447 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.28 ticks)
Cover probing fixed 0 vars, tightened 3 bounds.
MIP Presolve eliminated 4071 rows and 2399 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8005 rows, 10384 columns, and 36033 nonzeros.
Reduced MIP has 10197 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.56 ticks)
Clique table members: 16525.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.13 sec. (98.26 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44009e+07     2800.0000     3152  100.01%
      0     0      200.0000    97  -5.44009e+07      200.0000     3152  100.00%
*     0+    0                          200.0000      200.0000     3152    0.00%
      0     0        cutoff            200.0000      200.0000     3152    0.00%
Elapsed time = 0.78 sec. (925.22 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.35 sec. (365.92 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.35 sec. (365.92 ticks)

Times (seconds):
Input =  0.058991
Solve =  1.3018
Output = 0.044993
CPLEX 12.5.0.0: optimal integer solution; objective 200
3152 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 1
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 5 times. 

display ax;
ax :=
;

option log_file '';
