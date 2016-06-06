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
MIP Presolve eliminated 65693 rows and 32369 columns.
MIP Presolve modified 57820 coefficients.
Reduced MIP has 12324 rows, 13001 columns, and 61225 nonzeros.
Reduced MIP has 12809 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4400935e+07 after 0.32 sec. (464.68 ticks)
Probing fixed 1433 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.36 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 4081 rows and 2385 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8011 rows, 10384 columns, and 36031 nonzeros.
Reduced MIP has 10197 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.60 ticks)
Clique table members: 16754.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.14 sec. (106.23 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44009e+07     2800.0000     3232  100.01%
      0     0      600.0000   290  -5.44009e+07      600.0000     3232  100.00%
*     0+    0                          600.0000      600.0000     3232    0.00%
      0     0        cutoff            600.0000      600.0000     3232    0.00%
Elapsed time = 0.89 sec. (912.14 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.46 sec. (352.94 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.46 sec. (352.94 ticks)

Times (seconds):
Input =  0.05699
Solve =  1.48577
Output = 0.042994
CPLEX 12.5.0.0: optimal integer solution; objective 600
3232 MIP simplex iterations
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
