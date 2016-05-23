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
MIP Presolve eliminated 57340 rows and 32578 columns.
MIP Presolve modified 57740 coefficients.
Reduced MIP has 12120 rows, 12794 columns, and 60105 nonzeros.
Reduced MIP has 12602 binaries, 192 generals, 0 SOSs, and 0 indicators.
Found incumbent of value -5.3901006e+07 after 0.32 sec. (472.60 ticks)
Probing fixed 1238 vars, tightened 0 bounds.
Probing changed sense of 48 constraints.
Probing time = 0.03 sec. (14.14 ticks)
Cover probing fixed 0 vars, tightened 4 bounds.
MIP Presolve eliminated 3870 rows and 2168 columns.
MIP Presolve modified 13 coefficients.
Reduced MIP has 8012 rows, 10388 columns, and 36045 nonzeros.
Reduced MIP has 10201 binaries, 187 generals, 0 SOSs, and 0 indicators.
Probing fixed 0 vars, tightened 1 bounds.
Probing time = 0.02 sec. (10.68 ticks)
Clique table members: 16666.
MIP emphasis: balance optimality and feasibility.
MIP search method: dynamic search.
Parallel mode: deterministic, using up to 8 threads.
Root relaxation solution time = 0.17 sec. (125.97 ticks)

        Nodes                                         Cuts/
   Node  Left     Objective  IInf  Best Integer    Best Bound    ItCnt     Gap

*     0+    0                      -5.39010e+07   -97100.0000     3400   99.82%
      0     0   -99400.0000   302  -5.39010e+07   -99400.0000     3400   99.82%
*     0+    0                       -99400.0000   -99400.0000     3400    0.00%
      0     0        cutoff         -99400.0000   -99400.0000     3400    0.00%
Elapsed time = 0.90 sec. (986.68 ticks, tree = 0.00 MB)

Root node processing (before b&c):
  Real time             =    0.47 sec. (422.63 ticks)
Parallel b&c, 8 threads:
  Real time             =    0.00 sec. (0.00 ticks)
  Sync time (average)   =    0.00 sec.
  Wait time (average)   =    0.00 sec.
                          ------------
Total (root+branch&cut) =    0.47 sec. (422.63 ticks)

Times (seconds):
Input =  0.056991
Solve =  1.57376
Output = 0.037994
CPLEX 12.5.0.0: optimal integer solution; objective -99400
3400 MIP simplex iterations
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
5 5 1 LOW   1
;

option log_file '';
