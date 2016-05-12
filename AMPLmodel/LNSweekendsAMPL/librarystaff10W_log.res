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
Infeasibility row 'c73750':  0  = 1.

Times (seconds):
Input =  0.052991
Solve =  0.123981
Output = 0.001
CPLEX 12.5.0.0: integer infeasible.
0 MIP simplex iterations
0 branch-and-bound nodes
No basis.
option log_file '';
display min_lib, min_ass;
min_lib = 0
min_ass = 0

printf "The same stand in objective function value occurs: %d times. \n\n", times_same_sol;
The same stand in objective function value occurs: 50 times. 

option log_file '';
