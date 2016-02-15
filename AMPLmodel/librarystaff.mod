# Model file
# Master Thesis: Work Distribution of a Heterogeneous Library Staff - A Personnel Task Scheduling Problem
# Master Students: Claes Arvidson and Emelie Karlsson
# First version: 2016-02-09

### Sets ###
set D; #Set of days in a week
set W; #Set of weeks
set I; #Set of staff
set S{D}; #Set of outer shifts in a day, either weekday or weekend day
#set S2; #Set of outer shifts in a weekend day
set J{D}; #Set of total outer task types at a day D
#set J; #Set of all outer tasks types
#set I_qualified{J}; #Set of qualified workers for task type J
set I_weekend; #Set of workers available on week ends.

### Parameters ###
param skill{I} binary; #Staff skill competence for worker i, 0 if Assistant or 1 if Librarian
param avail{I,S{D},D,W} binary; #Worker i available for shift s day d week w
#param inner{I,D,W} binary; #saying if worker i has inner service day d week w
param task_worker_demand{J{D},S{D},D}; #number of workers required for task type j shift s on day d
param qualavail{I,J{D},S{D},D,W} binary; #Worker i qualified and available for task type j shift s day d week w
param meeting{S{D},D,W} binary;

### Variables ###
var x{i in I, j in J[d], s in S[d], d in D, w in W} binary; #1 if worker i is assigned task type j in shift s day d week w
var y{i in I, d in D, w in W} binary; #1 if worker i used day d in week w


### Objective function ###
maximize stand_ins_and_competence:
	A*lowest_stand_in_amount + B*sum;
	

### Constraints ###
subject to task_assign_amount{d in D, s in S[d], j in J[d], w in W}:
	sum{i in I} x[i,j,s,d,w] = task_worker_demand[j,s,d];

subject to single_task_per_day{i in I, d in D, w in W}:
	sum{s in S[d]}(sum {j in J[d]} x[i,j,s,d,w]) <= 1;

#subject to one_task_per_weekend{i in I, d in 6..7, w in W}:
#	sum{s in S2}(sum {j in J[d]} x[i,j,s,d,w]) <= 1;

subject to librarians_at_infodesks{i in I, s in S[d], d in D, w in W}:
	x[i,2,s,d,w] <= skill[i];

subject to find_lowest_stand_in_amount_no_weekends{d in 1..5, s in S[d], j in J[d], w in W}: #RHS: number of qualified workers at work that is available (not assigned to any task). meeting = 1 if any of the divisions has a meeting.
	lowest_stand_in_amount <= sum{i in I} qualavail[i,j,s,d,w]*(1-x[i,j,s,d,w]) + meeting[s,d,w]*M;

#subject to one_weekend_per_five_week{i in I_weekend}:
#	sum{w in W}(sum {d in 6..7}(sum {s in S[d]}(sum {j in J[d]} x[i,j,s,d,w]))) = 2; #Note: Does not mean they are contiguous!


