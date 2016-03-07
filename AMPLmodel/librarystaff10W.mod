# Model file
# Master Thesis: Work Distribution of a Heterogeneous Library Staff - A Personnel Task Scheduling Problem
# Master Students: Claes Arvidson and Emelie Karlsson
# First version: 2016-02-09

#################################### Sets ########################################################################
set D; #Set of days in a week
set W; #Set of weeks
set I; #Set of staff
set S{D}; #Set of outer shifts in a day, either weekday or weekend day
set J{D}; #Set of total outer task types at a day D
#set I_qualified{J}; #Set of qualified workers for task type J
set I_weekend_avail; #Set of workers available for weekend work. Subset of I
#set I_weekend{W}; #Set of workers available on weekend w. Subset of I_weekend_avail
set I_lib; #Set of librarians
set I_ass; #Set of assistants
set V; #Set of possible week rotations (shift the week by 1..10 steps)
set I_lib_on_wheels; #Set of librarians available to work in library on wheels (Bokbussen)
set I_free_day; #Set of workers that shall be assigned a free weekday per week

set Workers;


#################################### Parameters ########################################################################
#param meeting{S{D},D,W} binary;
#param inner{I,D,W} binary; #saying if worker i has inner service day d week w
param avail_day{i in I, w in W, d in D} binary; #1 if worker i is available day d, week w
param task_worker_demand{d in D, s in S[d], j in J[d]} integer; #number of workers required for task type j shift s on day d
param qualavail{i in I,w in W, d in D, s in S[d], j in J[d]} binary; #Worker i qualified and available for task type j shift s day d week w
param lib_on_wheels_worker_demand{w in W,d in D,s in S[d]} integer; #number of workers required for library on wheels week w, day d, shift s
param lib_on_wheels_avail{i in I_lib,w in W,d in D,s in S[d]} binary; #1 if a librarian is available to work in library on wheels week w, day d, shift s

param Shift_list{Workers}; #used to visualize results in terminal, see .run file
param stand_in_day_d{I, W, 1..5}; #used to print number of stand-ins for each day
param N1l := 40; #The bigger, the more priority to maximize librarian stand-ins
param N1a := 20; #The bigger, the more priority to maximize assistants stand-ins
param N2 := 1; #Prioritize similar weeks
param N3 := 1; #Prioritize varied time of shifts

#################################### Variables ########################################################################
var r{i in I, w in W} binary; #1 if person i has a rotation (phase shift) of w weeks, 0 otherwise
var h1{i in I, w in W} binary; #1 if worker i works weekend 1 in week w
var h2{i in I, w in W} binary; #1 if worker i works weekend 2 in week w
var x{i in I, w in W, d in D, s in S[d], j in J[d]} binary; #1 if worker i is assigned task type j in shift s day d week w
var z{i in I_weekend_avail, w in W, d in D, s in S[d], j in J[d]} binary; #1 if x = 1 and h = 1, 0 else
var stand_in_lib{i in I_lib, w in W, d in D} binary; #1 if (h[i,v]*qualavail[i,(w-v+5) mod 5 +1,d,s,j]) = 1 and x[i,w,d,s,j] = 0. First term is if a worker is working a weekend
var stand_in_ass{i in I_ass, w in W, d in D} binary; #1 if (h[i,v]*qualavail[i,(w-v+5) mod 5 +1,d,s,j]) = 1 and x[i,w,d,s,j] = 0. First term is if a worker is working a weekend
var y{i in I, w in W, d in 1..5, s in 1..3} binary; #1 if worker i works week w, day d, shift s. No weekends and no evenings
var lowest_stand_in_amount_lib integer; # Lowest number of stand-in workers at any shift
var lowest_stand_in_amount_ass integer; # Lowest number of stand-in workers at any shift
var shifts_that_differ_between_weeks{i in I, w in W, w_prime in W, d in 1..5, s in 1..3} binary; #Shift that differ between different weeks for a worker at a certain shift
var hb{i in I, w in W} binary; #1 if a person i works in HB week w
var working_friday_evening{i in I, w in W} binary; #1 if a person works weekend but not in HB
var num_days_with_same_shift{i in I, w in W, s in 1..3} integer;
#var diff_num_same_shifts{i in I, w in W, s in 1..2, s_prime in 2..3} integer;
#var total_sum_of_shift_differences integer;
#var help_with_max_abs[i,w,s,s_prime] integer;




################################## OBJECTIVE FUNCTION ###################################################################

maximize objective: #Maximize stand-ins and create schedules with similar weeks for each worker
	N1l*lowest_stand_in_amount_lib
	+ N1a*lowest_stand_in_amount_ass
	- N2*sum{i in I}(sum{w in 1..9}(sum{w_prime in (w+1)..10}(sum{d in 1..5}(sum{s in 1..3} shifts_that_differ_between_weeks[i,w,w_prime,d,s]))))
	;

#################################### CONSTRAINTS ########################################################################

######################## Task demand for workers #####################################
#number of workers to be assigned to different task types at different shifts (shall work for all days 1..7)
subject to task_assign_amount_weekdays{w in W, d in 1..5,s in S[d], j in {'Exp', 'Info', 'PL'}}:
	sum{i in I} x[i,w,d,s,j] = task_worker_demand[d,s,j];

subject to task_assign_amount_weekends{w in W, d in 6..7,s in S[d], j in J[d]}:
	sum{i in I} x[i,w,d,s,j] = task_worker_demand[d,s,j];

#subject to task_assign_amount_library_on_wheels{w in W, d in 1..5,s in S[d]}:
#	sum{i in I_lib_on_wheels} x[i,w,d,s,'LOW'] = lib_on_wheels_worker_demand[w,d,s];

######################## Maximum one task per day #####################################
#Stating that a worker can only be assigned one (outer) task per day (weekends included) where they are available. Library on wheels not included
subject to max_one_task_per_day_weekday{i in I, w in W, d in 1..5}:
	sum{s in S[d]}(sum {j in {'Exp','Info','PL'}} x[i,w,d,s,j]) <= 1;

subject to max_one_task_per_day_weekend{i in I, w in W, d in 6..7}:
	sum{s in S[d]}(sum {j in J[d]} x[i,w,d,s,j]) <= 1;

######################## Maximum one 'PL' per week and maximum two per five weeks #####################################
#Allowing a worker i to only work with 'Plocklistan' once per week
subject to max_one_PL_per_week{i in I, w in W}:
	sum{d in 1..5} x[i,w,d,1,'PL'] <= 1;

#Allowing a worker i maximum two 'PL' per five weeks
subject to max_two_PL_per_five_first_weeks{i in I}:
	sum{w in 1..5}(sum{d in 1..5} x[i,w,d,1,'PL']) <= 2;
subject to max_two_PL_per_five_last_weeks{i in I}:
	sum{w in 6..10}(sum{d in 1..5} x[i,w,d,1,'PL']) <= 2;

####################### Week rotation and weekend constraints #########################
#Stating number of weeks worker i:s schedule is phase shifted
subject to rotation_of_week{i in I}:
	sum{w in W} r[i,w] = 1;

#Allowing a "weekend-worker" to work a maximum of two weekends per ten weeks
subject to first_weekend_happening_max_once{i in I_weekend_avail}:
	sum{w in W} h1[i,w] <= 1;
subject to second_weekend_happening_max_once{i in I_weekend_avail}:
	sum{w in W} h2[i,w] <= 1;

#Rotate the schedule so weekend work is at week w. If worker i does not work weekend (h1 = h2 = 0) then the rotation is free.
subject to rotation_demand{i in I, w in W}:
	r[i,w] >= h1[i,w];

#if weekend two is 1 for a week w, then rotation r shall be shifted by 5. e.g. h2[i,7] = 1 then r[i,2] = 1, if h2[i,2] = 1 then r[i,7] = 1
subject to rotation_demand2{i in I, w in W}:
	r[i,(w+4) mod 10 + 1] >= h2[i,w];

#Ensuring that if a worker i is working weekend w then they will work saturday and sunday in week w
subject to two_days_weekends{i in I_weekend_avail, w in W}:
	sum {s in S[6]}(sum {j in J[6]} x[i,w,6,s,j]) + sum {s in S[7]}(sum {j in J[7]} x[i,w,7,s,j]) = 2*h1[i,w] + 2*h2[i,w];

subject to same_tasks_on_weekends{i in I_weekend_avail, w in W, j in J[7]} :
	sum{s in S[6]} x[i,w,6,s,j] = sum{s in S[7]} x[i,w,7,s,j]; #s = 1 for weekends anyhow


######################### Friday constraints #################################
subject to friday_added_to_the_weekend{i in I_weekend_avail, w in W}:
	sum {j in {'Exp', 'Info', 'PL'}} x[i,w,5,4,j] = working_friday_evening[i,w];

#assigns hb to 1 if a worker is working in HB on saturday (and sunday)
subject to assign_hb{i in I_weekend_avail, w in W}:
	hb[i,w] = x[i,w,6,1,'HB'];

#Help constraints. working_friday_evening = 1 if worker i works weekend w, but does not work in HB
subject to help_constraint_friday_weekend1_1{i in I_weekend_avail, w in W}:
	working_friday_evening[i,w] >= h1[i,w] + (1 - hb[i,w]) - 1;

subject to help_constraint_friday_weekend2_1{i in I_weekend_avail, w in W}:
	working_friday_evening[i,w] >= h2[i,w] + (1 - hb[i,w]) - 1;

subject to help_constraint_friday_weekend1_2{i in I_weekend_avail, w in W}:
	working_friday_evening[i,w] <= h1[i,w] + h2[i,w];

subject to help_constraint_friday_weekend3{i in I_weekend_avail, w in W}:
	working_friday_evening[i,w] <= (1 - hb[i,w]);





######################### First objective function constraints: Stand-in constraints #################################
#Finding the lowest stand-in amount of all shifts and at a specific task type where weekends, big meetings and evening shifts are discarded
subject to find_lowest_stand_in_amount_no_weekends_no_evenings_lib{w in W, d in 1..5}: #RHS: number of qualified workers at work that is available & not assigned to any task.
	lowest_stand_in_amount_lib <= sum{i in I_lib} stand_in_lib[i,w,d]; 		#+ meeting[s,d,w]*M; 

#A worker is a stand-in if he/she is available, qualified and is not already scheduled. Takes schedule rotation into account
subject to find_avail_not_working_day_lib{i in I_lib, w in W, d in 1..5}:
	stand_in_lib[i,w,d] >= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]) + (1-sum{s in 1..4}(sum{j in J[d]} x[i,w,d,s,j])) - 1; #Available and not working any shift day d. Note: ADD LOW here??

### Help constraints for qualavail and not scheduled ###
subject to help_constraint2_lib{i in I_lib, w in W, d in 1..5}:
	stand_in_lib[i,w,d] <= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]);

subject to help_constraint3_lib{i in I_lib, w in W, d in 1..5}:
	stand_in_lib[i,w,d] <= 1-sum{s in 1..4}(sum{j in J[d]} x[i,w,d,s,j]); # Note: ADD LOW here??

### Stand-ins for assistants
#Finding the lowest stand-in amount of all shifts and at a specific task type where weekends, big meetings and evening shifts are discarded
subject to find_lowest_stand_in_amount_no_weekends_no_evenings_ass{w in W, d in 1..5}: #RHS: number of qualified workers at work that is available & not assigned to any task.
	lowest_stand_in_amount_ass <= sum{i in I_ass} stand_in_ass[i,w,d]; 		#+ meeting[s,d,w]*M; 

#A worker is a stand-in if he/she is available, qualified and is not already scheduled. Takes schedule rotation into account
subject to find_avail_not_working_day_ass{i in I_ass, w in W, d in 1..5}:
	stand_in_ass[i,w,d] >= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]) + (1-sum{s in 1..4}(sum{j in {'Exp', 'PL'}} x[i,w,d,s,j])) - 1; #Available and not working any shift day d.

### Help constraints for qualavail and not scheduled ###
subject to help_constraint2_ass{i in I_ass, w in W, d in 1..5}:
	stand_in_ass[i,w,d] <= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]);

subject to help_constraint3_ass{i in I_ass, w in W, d in 1..5}:
	stand_in_ass[i,w,d] <= 1-sum{s in 1..4}(sum{j in {'Exp', 'PL'}} x[i,w,d,s,j]);

####################### Only assign if qualified and available ######################

subject to librarians_only_assigned_if_qualavail_weekdays{i in I_lib, w in W, d in 1..5, s in S[d], j in {'Exp', 'Info', 'PL'}}: #librarians qualified for all: 'Exp', 'Info', 'PL', 'HB'
	x[i,w,d,s,j] <= (sum {v in V} (r[i,v]*qualavail[i,(w-v+10) mod 10 +1,d,s,j]));

subject to librarians_only_assigned_if_qualavail_weekends{i in I_lib, w in W, d in 6..7, s in S[d], j in J[d]}: #librarians qualified for all: 'Exp', 'Info', 'PL', 'HB'. No 'LOW' on weekends either
	x[i,w,d,s,j] <= (sum {v in V} (r[i,v]*qualavail[i,(w-v+10) mod 10 +1,d,s,j]));

subject to assistants_only_assigned_if_qualavail_weekdays{i in I_ass, w in W, d in 1..5, s in S[d], j in {'Exp', 'Info', 'PL'}}: #assistants not qualified for 'Info' on weekdays
	x[i,w,d,s,j] <= (sum {v in V} (r[i,v]*qualavail[i,(w-v+10) mod 10 +1,d,s,j]));

subject to assistants_only_assigned_if_qualavail_weekends{i in I_ass, w in W, d in 6..7, s in S[d], j in J[d]}: #assistants not qualified for 'Info' or 'HB' on weekends, no 'LOW' on weekends either
	x[i,w,d,s,j] <= (sum {v in V} (r[i,v]*qualavail[i,(w-v+10) mod 10 +1,d,s,j]));
### LIBRARY ON WHEELS ###
#subject to lib_on_wheels_constraint{i in I_lib_on_wheels, w in W, d in 1..5, s in S[1]}: #Around five librarians qualified for library on wheels. They _shall_ be assigned their shifts there
#	x[i,w,d,s,'LOW'] = (sum {v in V} (r[i,v]*lib_on_wheels_avail[i,(w-v+10) mod 10 +1,d,s]));


############### Second objective function constraints: Similar weeks for workers #############
subject to positive_values_of_abs{i in I, w in 1..9, w_prime in (w+1)..10, d in 1..5, s in 1..3}:
	shifts_that_differ_between_weeks[i,w,w_prime,d,s] >= (y[i,w,d,s]-y[i,w_prime,d,s]);

subject to negative_values_of_abs{i in I, w in 1..9, w_prime in (w+1)..10, d in 1..5, s in 1..3}:
	shifts_that_differ_between_weeks[i,w,w_prime,d,s] >= -(y[i,w,d,s]-y[i,w_prime,d,s]);


###################### Worker shift assignment ##############################
#Variable saying if a worker i is assigned a shift s, not accounting Library on wheels
subject to assign_y{i in I, w in W, d in 1..5, s in 1..3}:
	y[i,w,d,s] = sum{j in {'Exp', 'Info', 'PL'}} x[i,w,d,s,j];

#Workers that shall be assigned a weekday free from tasks
subject to task_free_weekday{i in I_free_day, w in W}:
	sum{d in 1..5}(1-sum{s in 1..3} y[i,w,d,s]) >= 1;

######################### Time constraints #################################
#Allowing only three shifts at a certain time each week
subject to max_three_shifts_per_week{i in I, w in W, s in 1..3}:
	sum{d in 1..5} y[i,w,d,s] <= 2;



