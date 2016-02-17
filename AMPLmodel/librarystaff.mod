# Model file
# Master Thesis: Work Distribution of a Heterogeneous Library Staff - A Personnel Task Scheduling Problem
# Master Students: Claes Arvidson and Emelie Karlsson
# First version: 2016-02-09

### Sets ###
set D; #Set of days in a week
set W; #Set of weeks
set I; #Set of staff
set S{D}; #Set of outer shifts in a day, either weekday or weekend day
set J{D}; #Set of total outer task types at a day D
#set I_qualified{J}; #Set of qualified workers for task type J
#set I_weekend_avail; #Set of workers available for weekend work. Subset of I
#set I_weekend{W}; #Set of workers available on weekend w. Subset of I_weekend_avail
set I_lib; #Set of librarians
set I_ass; #Set of assistants


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
var h{i in I_weekend_avail, w in W} binary; #1 if worker i works weekend in week w


### Objective function ###
maximize stand_ins_and_competence:
	lowest_stand_in_amount;


### Constraints ###
#number of workers to be assigned to different task types at different shifts (shall work for all days 1..7)
subject to task_assign_amount{w in W, d in D, s in S[d], j in J[d]}:
	sum{i in I} x[i,w,d,s,j] = task_worker_demand[d,s,j];

#Stating that a worker can only be assigned one (outer) task per day (weekends included)
subject to max_one_task_per_day{i in I, w in W, d in D}:
	sum{s in S[d]}(sum {j in J[d]} x[i,w,d,s,j]) <= 1;

#subject to one_task_per_weekend{i in I, w in W, d in 6..7}:
#	sum{s in S[d]}(sum {j in J[d]} x[i,w,d,s,j]) <= 1;

#Assigning that assistants can not be assigned to Info desks in any day
subject to librarians_at_infodesks{i in I_ass, w in W, d in D, s in S[d]}:
	x[i,w,d,s,'Info'] = 0;

#Assigning that assistants can not be assigned to Hageby during weekends
subject to librarians_at_infodesks{i in I_ass, w in W, d in 6..7, s in S[d]}:
	x[i,w,d,s,'HB'] = 0;

#Finding the lowest stand-in amount of all shifts and at a specific task type where weekends, big meetings and evening shifts are discarded
subject to find_lowest_stand_in_amount_no_weekends{w in W, d in 1..5, s in 1..3, j in J[d]}: #RHS: number of qualified workers at work that is available (not assigned to any task). meeting = 1 if any of the divisions has a meeting.
	lowest_stand_in_amount <= sum{i in I} qualavail[i,w,d,s,j]*(1-x[i,w,d,s,j]); 		#+ meeting[s,d,w]*M;

#Allowing a worker to only work one weekend per five weeks
subject to one_weekend_per_five_weeks{i in I_weekend_avail}:
	sum{w in W} h[i,w] = 1;

#subject to one_weekend_per_five_week{i in I_weekend_avail}:
#	sum{w in W}(sum {d in 6}(sum {s in S[d]}(sum {j in J[d]} (x[i,w,d-1,4,j] + x[i,w,d,s,j] + x[i,w,d+1,s,j])*h[i,w] ))) = 3; #task type j can vary but not the week..? #problem that S[6] := 1 and not S[6] := 1 2 3 4? 


