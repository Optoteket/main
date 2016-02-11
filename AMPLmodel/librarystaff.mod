# Model file
# Master Thesis: Work Distribution of a Heterogeneous Library Staff - A Personnel Task Scheduling Problem
# Master Students: Claes Arvidson and Emelie Karlsson
# First version: 2016-02-09

### Sets ###
set D; #Set of days in a week
set W; #Set of weeks
set I; #Set of staff
set S; #Set of outer shifts in a day
set J{S}; #Set of total outer tasks at a shift S
set J; #Set of all outer tasks types
#set I_qualified{J}; #Set of qualified workers for task type J

### Parameters ###
param skill{I} binary; #Staff skill competence for worker i, 0 if Assistant or 1 if Librarian
param avail{I,S,D,W} binary; #Worker i available for shift s day d week w
#param inner{I,D,W} binary; #saying if worker i has inner service day d week w
param task_worker_demand{J,S,D}; #number of workers required for task type j shift s on day d
param qualavail{I,J,S,D,W} binary; #Worker i qualified and available for task type j shift s day d week w
param meeting{S,D,W} binary;

### Variables ###
var x{i in I, j in J[s], s in S, d in D, w in W} binary; #1 if worker i is assigned task type j in shift s day d week w
var y{i in I, d in D, w in W} binary; #1 if worker i used day d in week w


### Objective function ###
maximize stand_ins_and_competence:
	A*lowest_stand_in_amount + B*sum;
	

### Constraints ###
subject to task_assign_amount{s in S, j in J[s], d in D, w in W}:
	sum{i in I} x[i,j,s,d,w] = task_worker_demand[j,s,d];

subject to single_task_per_shift{i in I, d in D, w in W}:
	sum{s in S}(sum {j in J[s]} x[i,j,s,d,w]) <= 1;

subject to librarians_at_infodesks{i in I, s in S, d in D, w in W}
	x[i,2,s,d,w] <= skill[i];

subject to find_lowest_stand_in_amount{s in S, j in J[s], d in 1..5, w in W}: #RHS: number of qualified workers at work that is available (not assigned to any task).
	lowest_stand_in_amount <= sum{i in I} qualavail[i,j,s,d,w]*(1-x[i,j,s,d,w]) + meeting[s,d,w]*M;
