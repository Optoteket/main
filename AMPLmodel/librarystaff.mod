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
#set I_qualified{J}; #Set of qualified workers for task type J
#set I_weekend; #Set of workers available on week ends.

### Parameters ###
param skill{I}; #Staff skill competence for worker i, 0 if Assistant or 1 if Librarian
param avail{i in I, w in W, d in D, s in S[d]} binary; #Worker i available for shift s day d week w
#param inner{I,D,W} binary; #saying if worker i has inner service day d week w
param task_worker_demand{d in D, s in S[d], j in J[d]} integer; #number of workers required for task type j shift s on day d
param qualavail{i in I,w in W, d in D, s in S[d], j in J[d]} binary; #Worker i qualified and available for task type j shift s day d week w
#param meeting{S{D},D,W} binary;

### Variables ###
var x{i in I, w in W, d in D, s in S[d], j in J[d]} binary; #1 if worker i is assigned task type j in shift s day d week w
var y{i in I, w in W, d in D} binary; #1 if worker i used day d in week w
var lowest_stand_in_amount integer; # Lowest number of stand-in workers at any shift


### Objective function ###
maximize stand_ins_and_competence:
	lowest_stand_in_amount;


### Constraints ###
subject to task_assign_amount{w in W, d in D, s in S[d], j in J[d]}:
	sum{i in I} x[i,w,d,s,j] = task_worker_demand[d,s,j];

subject to single_task_per_day{i in I, w in W, d in D}:
	sum{s in S[d]}(sum {j in J[d]} x[i,w,d,s,j]) <= 1;

#subject to one_task_per_weekend{i in I, w in W, d in 6..7}:
#	sum{s in S2}(sum {j in J[d]} x[i,w,d,s,j]) <= 1;

subject to librarians_at_infodesks{i in I, w in W, d in D, s in S[d]}:
	x[i,w,d,s,2] <= skill[i];

subject to find_lowest_stand_in_amount_no_weekends{w in W, d in 1..5, s in S[d], j in J[d]}: #RHS: number of qualified workers at work that is available (not assigned to any task). meeting = 1 if any of the divisions has a meeting.
	lowest_stand_in_amount <= sum{i in I} qualavail[i,w,d,s,j]*(1-x[i,w,d,s,j]); 		#+ meeting[s,d,w]*M;


#subject to one_weekend_per_five_week{i in I_weekend}:
#	sum{w in W}(sum {d in 6..7}(sum {s in S[d]}(sum {j in J[d]} x[i,w,d,s,j]))) = 2; #Note: Does not mean they are contiguous!


