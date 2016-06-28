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
MIP Presolve eliminated 65778 rows and 32399 columns.
MIP Presolve modified 57937 coefficients.
Reduced MIP has 12229 rows, 12961 columns, and 60554 nonzeros.
Reduced MIP has 12769 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4401033e+07 after 0.32 sec. (466.07 ticks)
Probing fixed 1414 vars, tightened 2 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.22 ticks)
Cover probing fixed 0 vars, tightened 6 bounds.
MIP Presolve eliminated 3996 rows and 2355 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8008 rows, 10381 columns, and 36031 nonzeros.
Reduced MIP has 10194 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.41 ticks)
Clique table members: 16498.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.16 sec. (140.32 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.44010e+07     2700.0000     3558  100.00%
      0     0      600.0000   254  -5.44010e+07      600.0000     3558  100.00%
*     0+    0                          600.0000      600.0000     3558    0.00%
      0     0        cutoff            600.0000      600.0000     3558    0.00%
Elapsed time = 0.85 sec. (898.06 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.42 sec. (337.92 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.42 sec. (337.92 ticks)

Times (seconds):
Input =  0.05699
Solve =  1.38579
Output = 0.043993
CPLEX 12.5.0.0: optimal integer solution; objective 600
3558 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 3
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 15 times. 

display ax;
ax :=
;

option log_file '';
