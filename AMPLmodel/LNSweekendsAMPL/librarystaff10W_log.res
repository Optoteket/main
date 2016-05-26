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
MIP Presolve eliminated 65855 rows and 32421 columns.
MIP Presolve modified 58161 coefficients.
Reduced MIP has 12137 rows, 12925 columns, and 59505 nonzeros.
Reduced MIP has 12733 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4201031e+07 after 0.33 sec. (460.60 ticks)
Probing fixed 1414 vars, tightened 1 bounds.
Probing changed sense of 45 constraints.
Probing time = 0.03 sec. (14.13 ticks)
Cover probing fixed 0 vars, tightened 4 bounds.
MIP Presolve eliminated 3921 rows and 2339 columns.
MIP Presolve modified 12 coefficients.
Reduced MIP has 8005 rows, 10375 columns, and 35989 nonzeros.
Reduced MIP has 10188 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.47 ticks)
Clique table members: 16254.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.17 sec. (130.15 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.42010e+07     2900.0000     3420  100.01%
      0     0      600.0000   448  -5.42010e+07      600.0000     3420  100.00%
*     0+    0                          600.0000      600.0000     3420    0.00%
      0     0        cutoff            600.0000      600.0000     3420    0.00%
Elapsed time = 1.01 sec. (984.73 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.57 sec. (432.04 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.57 sec. (432.04 ticks)

Times (seconds):
Input =  0.05799
Solve =  1.81172
Output = 0.044994
CPLEX 12.5.0.0: optimal integer solution; objective 600
3420 MIP simplex iterations
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
