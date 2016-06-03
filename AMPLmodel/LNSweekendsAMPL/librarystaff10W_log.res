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
MIP Presolve eliminated 65347 rows and 32173 columns.
MIP Presolve modified 57565 coefficients.
Reduced MIP has 12660 rows, 13185 columns, and 63626 nonzeros.
Reduced MIP has 12995 binaries, 190 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.4501242e+07 after 0.33 sec. (481.83 ticks)
Probing fixed 1537 vars, tightened 2 bounds.
Probing changed sense of 50 constraints.
Probing time = 0.03 sec. (14.53 ticks)
Cover probing fixed 0 vars, tightened 7 bounds.
MIP Presolve eliminated 4391 rows and 2549 columns.
MIP Presolve modified 17 coefficients.
Reduced MIP has 8008 rows, 10375 columns, and 35993 nonzeros.
Reduced MIP has 10191 binaries, 184 generals, 0 SOSs, and 0 indicators.
Probing time = 0.02 sec. (10.52 ticks)
Clique table members: 17103.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.15 sec. (113.57 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.45012e+07     2600.0000     3386  100.00%
      0     0      400.0000   349  -5.45012e+07      400.0000     3386  100.00%
*     0+    0                          400.0000      400.0000     3386    0.00%
      0     0        cutoff            400.0000      400.0000     3386    0.00%
Elapsed time = 0.91 sec. (938.20 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.47 sec. (361.24 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.47 sec. (361.24 ticks)

Times (seconds):
Input =  0.055992
Solve =  1.56476
Output = 0.043992
CPLEX 12.5.0.0: optimal integer solution; objective 400
3386 MIP simplex iterations
0 branch-and-bound nodes
Tried aggregator 3 times
option log_file '';
display min_lib, min_ass;
min_lib = 2
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 6 times. 

display ax;
ax :=
;

option log_file '';
