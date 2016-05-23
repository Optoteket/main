### To do: Integrate h1 and h2 into H[i,w,h]

# Model file
# Master Thesis: Work Distribution of a Heterogeneous Library Staff - A Personnel Task Scheduling Problem
# Master Students: Claes Arvidson and Emelie Karlsson
# First version: 2016-02-09

# Possible Test: Use max 4 tasks per week OR 4 tasks on average:

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
#subject to average_shifts_a_week{i in I}:
#	shifts_worked[i] = sum{w in W}(sum{d in 1..5}(sum{s in S[d]}(sum{j in J[d]} x[i,w,d,s,j])))/10;

#subject to not_more_than_four_shifts_a_week{i in I}:
#	shifts_worked[i] <= 4;
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 




##############################################################################################################
####################################### MATHEMATICAL MODEL ###################################################
##############################################################################################################


#################################### Sets ########################################################################
set D; #Set of days in a week
set W; #Set of weeks
set I; #Set of staff
set Dep; #Set of departments
set S{D}; #Set of outer shifts in a day, either weekday or weekend day
set J{D}; #Set of total outer task types at a day D
set I_dep{Dep}; #Set of departments
set I_lib; #Set of librarians
set I_ass; #Set of assistants
set V; #Set of possible week rotations (shift the week by 1..10 steps)
set I_LOW; #Set of librarians available to work in library on wheels (Bokbussen)
set I_free_day; #Set of workers that shall be assigned a free weekday per week
set I_odd_even; #Set of all workers with odd or even weeks
set I_weekend_avail; #Set of workers available for weekend work.
set I_big_meeting; #Set of all workers that attend big meetings
set I_no_PL; #Set of workers not working on PL
set I_many_PL; #Set of workers working 3-4 rimes PL in 10 weeks
 
set Workers; #Only used to present results

                            
#################################### Parameters ########################################################################
#param meeting{S{D},D,W} binary;
param avail_day{i in I, w in W, d in D} binary; #1 if worker i is available day d, week w
param task_demand{d in D, s in S[d], j in J[d]} integer; #number of workers required for task type j shift s on day d
param qualavail{i in I,w in W, d in D, s in S[d], j in J[d]} binary; #Worker i qualified and available for task type j shift s day d week w
param LOW_demand{w in W,d in D,s in S[d]} integer; #number of workers required for library on wheels week w, day d, shift s

param Shift_list{Workers}; #used to visualize results in terminal, see .run file
param LOW_list{Workers};
param PL_list{Workers};
param min_lib;
param min_ass;
param times_same_sol;

#Objective function parameters
param stand_in_day_d{I, W, 1..5}; #used to print number of stand-ins for each day
param N1 := 100; #Prioritize total number of stand ins
param N1l := 2; #The bigger, the more priority to maximize librarian stand-ins
param N1a := 1; #The bigger, the more priority to maximize assistants stand-ins
param N2 := 1; #Prioritize similar weeks
param NA := 100000; #Cost of an artificial worker

#################################### Variables ########################################################################
var r{i in I, w in W} binary; #1 if person i has a rotation (phase shift) of w weeks, 0 otherwise
var H{i in I, w in W, h in 1..2} binary; #1 if worker i works weekend h in week w
var x{i in I, w in W, d in D, s in S[d], j in J[d]} binary; #1 if worker i is assigned task type j in shift s day d week w
var ax{w in W, d in D, s in S[d], j in J[d]} integer, >=0; #1 if artificial worker i is assigned task type j in shift s day d week w
var stand_in_lib{i in I_lib, w in W, d in D} binary; #1 if (h[i,v]*qualavail[i,(w-v+5) mod 5 +1,d,s,j]) = 1 and x[i,w,d,s,j] = 0. First term is if a worker is working a weekend
var stand_in_ass{i in I_ass, w in W, d in D} binary; #1 if (h[i,v]*qualavail[i,(w-v+5) mod 5 +1,d,s,j]) = 1 and x[i,w,d,s,j] = 0. First term is if a worker is working a weekend
var y{i in I, w in W, d in 1..5, s in 1..3} binary; #1 if worker i works week w, day d, shift s. No weekends and no evenings
var stand_in_lib_tot{w in W, d in 1..5} integer; # Lowest number of stand-in workers at any day
var stand_in_ass_tot{w in W, d in 1..5} integer; # Lowest number of stand-in workers at any day
var stand_in_min_tot integer; # Lowest total number of stand in workers at any day
var hb{i in I, w in W} binary; #1 if a person i works in HB week w
var friday_evening{i in I, w in W} binary; #1 if a person works weekend but not in HB
var shift_differ_weeks{i in I, w in 1..5, d in 1..5, s in 1..3} binary;
var M_big{w in W, d in 1..5, s in 1..4} binary; #1 if a big meeting is placed on this week, day, shift, 0 otherwise
var meeting{w in W, d in 1..5, s in 1..3, dep in 1..3} binary; #1 if a child meeting is placed on this week, day, shift, 0 otherwise
var working_a_shift{i in I, w in W, d in 1..5} binary;
var shifts_worked{i in I};
var shifts_that_differ integer;


################################## OBJECTIVE FUNCTION ###################################################################

maximize objective: #Maximize stand-ins and create schedules with similar weeks for each worker
	#N1l*stand_in_lib_min + N1a*stand_in_ass_min - N2*shifts_that_differ;
	N1*stand_in_min_tot - N2*shifts_that_differ - NA*(sum{w in W} (sum{d in D} (sum{s in S[d]} (sum{j in J[d]} ax[w,d,s,j]))));

#################################### CONSTRAINTS ########################################################################

######################## Task demand for workers #####################################
#number of workers to be assigned to different task types at different shifts (shall work for all days 1..7), except when there is a big meeting
subject to task_assign_amount_weekdays{w in 1..5, d in 1..5,s in S[d], j in J[d] diff {'LOW'}}:
	(sum{i in I} x[i,w,d,s,j]) + ax[w,d,s,j]= (1-M_big[w,d,s])*task_demand[d,s,j];

subject to task_assign_amount_weekends{w in 1..5, d in 6..7,s in S[d], j in J[d]}:
	(sum{i in I} x[i,w,d,s,j]) + ax[w,d,s,j]= task_demand[d,s,j];

subject to task_assign_amount_library_on_wheels{w in 1..5, d in 1..5 ,s in S[d]}:
	(sum{i in I} x[i,w,d,s,'LOW']) + ax[w,d,s,'LOW'] = LOW_demand[w,d,s];


######################## Maximum 4 shifts per week #########################################

subject to max_four_shifts_per_week{i in I diff {36}, w in W}:
	sum{d in 1..5}(sum{s in S[d]}(sum{j in J[d]} x[i,w,d,s,j])) <= 4;

######################## Big meeting constraints #########################################
# Big meeting constraints
subject to one_big_meeting_per_five_weeks:
	sum{w in 1..5} M_big[w,1,1] = 1;

subject to two_big_meetings_per_ten_weeks{w in 1..5}:
	M_big[w+5,1,1] = M_big[w,1,1];

subject to all_other_times_no_meeting:
	sum{w in W}(sum{d in 1..5}(sum{s in S[d]} M_big[w,d,s])) = 2;

#subject to no_other_tasks_when_meeting_if_boss{i in I diff I_big_meeting, w in W}:
#	sum {s in 1..3} (sum{j in {'Exp','Info','PL'}} x[i,w,1,s,j]) <= (1-M_big[w,1,1]);

######################## Department meeting constraints #########################
#Departments 1..3 have meetings once in 5 weeks
#subject to one_meeting_per_five_weeks{dep in 1..3}:
#	sum{w in 1..5}(sum{d in 1..5}(sum{s in 1..3} meeting[w,d,s,dep])) = 1;

#Departments 1..3 have meetings twice in 10 weeks
#subject to two_meetings_per_ten_weeks{dep in 1..3, w in 1..5, d in 1..5, s in 1..3}:
#	meeting[w+5,d,s,dep] = meeting[w,d,s,dep];

#No task can be performed when there is a department meeting
#subject to no_task_when_meeting{dep in 1..3, i in I_dep[dep], w in W, d in 1..5, s in 1..3, j in J[d]}:
#	meeting[w,d,s,dep] + x[i,w,d,s,j] <= 1;

#No meeting when PL in the morning shift
#subject to no_meeting_if_PL{dep in 1..3, i in I_dep[dep], w in W, d in 1..5, s in 1..3}:
#	meeting[w,d,2,dep] + meeting[w,d,3,dep] + x[i,w,d,1,'PL'] <= 1;

#All staff must be available during the meeting, except 39 who is never available
#subject to all_must_be_qualavail{dep in 1..3, i in I_dep[dep] diff {39}, w in W, d in 1..5, s in 1..3}:
#	meeting[w,d,s,dep] <= sum{v in V} (r[i,v]*qualavail[i,(w-v+10) mod 10 +1,d,s,'Exp']);

##################### One meeting per week constraint #######################################
#subject to max_one_meeting_per_week{dep in 1..3, i in I_big_meeting union I_dep[dep], w in W}:
#	M_big[w,1,1] + sum{d in 1..5}(sum{s in 1..3} meeting[w,d,s,dep]) <= 1;

######################## Maximum one task per day #####################################
#Stating that a worker can at maximum perform one task per shift
subject to only_LOW{i in I, w in W, d in D, s in S[d]}:
	sum {j in J[d]} x[i,w,d,s,j] <= 1;

#Stating that a worker performing library on wheels cannot perform another task that day, Mon-Thur
subject to only_one_task_per_day{i in I, w in W, d in 1..4, s2 in S[d]}:
	sum{s in S[d]}(sum {j in {'Exp','Info','PL'}} x[i,w,d,s,j]) <= 1 - x[i,w,d,s2,'LOW'];

#Stating that a worker performing can only have one library task at Fridays.
subject to only_LOW_friday{i in I, w in W}:
	sum{s in S[5]}(sum {j in {'Exp','Info','PL'}} x[i,w,5,s,j]) <= 1;

#Stating that a worker performing library on Friday morning can only have a task in the evning.
subject to two_tasks_if_LOW_friday_morning{i in I, w in W, s in 1..3}:
	(sum {j in {'Exp','Info','PL'}} x[i,w,5,s,j])  <= 1 - x[i,w,5,1,'LOW'];

subject to max_one_task_per_day_weekend{i in I, w in W, d in 6..7}:
	sum{s in S[d]}(sum {j in J[d]} x[i,w,d,s,j]) <= 1;

subject to max_one_task_per_evening_not_fridays{i in I diff {36}, w in W}:
	sum{d in 1..4}(sum{j in J[d]} x[i,w,d,4,j]) <= 1;

######################## PL constraints #####################################
#Allowing a worker i to only work with 'Plocklistan' once per week
subject to max_one_PL_per_week{i in I, w in W}:
	sum{d in 1..5} x[i,w,d,1,'PL'] <= 1;

#Not working at PL
subject to no_work_on_PL{i in I_no_PL, w in W, d in 1..5, s in S[d]}:
	x[i,w,d,s,'PL'] = 0;

#Working many times at PL, min 3
subject to many_work_on_PL_min{i in I_many_PL}:
	sum{w in W}(sum{d in 1..5} x[i,w,d,1,'PL']) >= 3;

#Working many times at PL, max 4
subject to many_work_on_PL_max{i in I_many_PL}:
	sum{w in W}(sum{d in 1..5} x[i,w,d,1,'PL']) <= 4;

#Working regular num times at PL, max 3
subject to regular_work_on_PL_max{i in I diff I_no_PL diff I_many_PL}:
	sum{w in W}(sum{d in 1..5}x[i,w,d,1,'PL']) <= 3;

####################### Week rotation and weekend constraints #########################

#Stating the week where the evening shall be rotated to
subject to rotation_of_week{i in I}:
	sum{w in W} r[i,w] = 1;

#Allowing a "weekend-worker" to work two weekends per ten weeks
subject to weekend_happening_max_once{i in I_weekend_avail, h in 1..2}:
	sum{w in W} H[i,w,h] <= 1;

#Rotate the schedule so weekend work is at week w. If worker i does not work weekend (H[i,w,1] = H[i,w,2] = 0) then the rotation is free.
subject to rotation_demand{i in I, w in W}:
	r[i,w] >= H[i,w,1];

#Only rotate even numbers for the workers with demands of odd and even weeks
subject to only_even_rotations{i in I_odd_even, w in 1..5}:
	r[i,2*w] = 0;

#if weekend two is 1 for a week w, then rotation r shall be shifted by 5. e.g. h2[i,7] = 1 then r[i,2] = 1, if h2[i,2] = 1 then r[i,7] = 1
subject to rotation_demand2{i in I, w in W}:
	r[i,(w+4) mod 10 + 1] >= H[i,w,2];

#Ensuring that if a worker i is working weekend w then they will work saturday and sunday in week w
subject to two_days_weekends{i in I_weekend_avail, w in W}:
	sum {s in S[6]}(sum {j in J[6]} x[i,w,6,s,j]) + sum {s in S[7]}(sum {j in J[7]} x[i,w,7,s,j]) = 2*(sum{h in 1..2} H[i,w,h]);	 # h1[i,w] + 2*h2[i,w];

subject to same_tasks_on_weekends{i in I_weekend_avail, w in W, j in J[7]} :
	sum{s in S[6]} x[i,w,6,s,j] = sum{s in S[7]} x[i,w,7,s,j]; #s = 1 for weekends anyhow


######################### Friday/weekend constraints #################################
subject to friday_added_to_the_weekend{i in I_weekend_avail, w in W}:
	sum {j in {'Exp', 'Info', 'PL'}} x[i,w,5,4,j] = friday_evening[i,w];

#assigns hb to 1 if a worker is working in HB on Saturday (and Sunday)
subject to assign_hb{i in I_weekend_avail, w in W}:
	hb[i,w] = x[i,w,6,1,'HB'];

#Help constraints. working_friday_evening = 1 if worker i works weekend w, but does not work in HB
subject to help_constraint_friday_weekend1{i in I_weekend_avail, w in W, h in 1..2}:
	friday_evening[i,w] >= H[i,w,h] + (1 - hb[i,w]) - 1;

subject to help_constraint_friday_weekend2{i in I_weekend_avail, w in W}:
	friday_evening[i,w] <= sum{h in 1..2} H[i,w,h];

subject to help_constraint_friday_weekend3{i in I_weekend_avail, w in W}:
	friday_evening[i,w] <= (1 - hb[i,w]);

#HB constraints
subject to max_two_days_at_HB_per_ten_weeks{i in I_lib diff {23}}:
	sum{w in W}(sum{d in 6..7} x[i,w,d,1,'HB']) <= 2;

#Workers who only work at HB when they are due for weekend work
subject to worker_not_assigned_exp_info{w in W}:
	sum{d in 6..7}sum{j in {'Exp','Info'}} x[23,w,d,1,j] = 0;


######################### First objective function constraints: Stand-in constraints #################################
#Find day with lowest lib and ass stand in value (weighted #lib + #ass) to maximize in obj function
subject to find_total_min_num_stand_ins{w in W, d in 1..5}:
	stand_in_min_tot <= (N1l*(sum{i in I_lib} stand_in_lib[i,w,d]) + N1a*(sum{i in I_ass} stand_in_ass[i,w,d]));

#Finding the lowest stand-in amount of all shifts and at a specific task type where weekends, big meetings and evening shifts are discarded
subject to find_lowest_stand_in_amount_no_weekends_no_evenings_lib{w in W, d in 1..5}: #RHS: number of qualified workers at work that is available & not assigned to any task.
	stand_in_lib_tot[w,d] = sum{i in I_lib} stand_in_lib[i,w,d]; 		#+ meeting[s,d,w]*M; 

subject to working_shift_in_a_day{i in I, w in W, d in 1..5}:
	working_a_shift[i,w,d] >= sum{s in 1..3}(sum{j in J[d]} x[i,w,d,s,j]);

subject to working_shift_in_an_evening{i in I, w in W, d in 1..5}:
	working_a_shift[i,w,d] >= sum{j in J[d]} x[i,w,d,4,j];

#A worker is a stand-in if he/she is available for shift 1-3, qualified and is not already scheduled. Takes schedule rotation into account
subject to find_avail_not_working_day_lib{i in I_lib, w in W, d in 1..5}:
	stand_in_lib[i,w,d] >= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]) + (1-working_a_shift[i,w,d]) - 1; #Available and not working any shift day d. Note: ADD LOW here??

### Help constraints for qualavail and not scheduled ###
subject to help_constraint2_lib{i in I_lib, w in W, d in 1..5}:
	stand_in_lib[i,w,d] <= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]);

subject to help_constraint3_lib{i in I_lib, w in W, d in 1..5}:
	stand_in_lib[i,w,d] <= 1-working_a_shift[i,w,d]; # Note: ADD LOW here??


### Stand-ins for assistants
#Finding the lowest stand-in amount of all shifts and at a specific task type where weekends, big meetings and evening shifts are discarded
subject to find_lowest_stand_in_amount_no_weekends_no_evenings_ass{w in W, d in 1..5}: #RHS: number of qualified workers at work that is available & not assigned to any task.
	stand_in_ass_tot[w,d] = sum{i in I_ass} stand_in_ass[i,w,d]; 		#+ meeting[s,d,w]*M; 

#A worker is a stand-in if he/she is available, qualified and is not already scheduled. Takes schedule rotation into account
subject to find_avail_not_working_day_ass{i in I_ass, w in W, d in 1..5}:
	stand_in_ass[i,w,d] >= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]) + (1-sum{s in 1..4}(sum{j in {'Exp', 'PL'}} x[i,w,d,s,j])) - 1; #Available and not working any shift day d.

### Help constraints for qualavail and not scheduled ###
subject to help_constraint2_ass{i in I_ass, w in W, d in 1..5}:
	stand_in_ass[i,w,d] <= sum {v in V} (r[i,v]*avail_day[i,(w-v+10) mod 10 +1,d]);

subject to help_constraint3_ass{i in I_ass, w in W, d in 1..5}:
	stand_in_ass[i,w,d] <= 1-sum{s in 1..4}(sum{j in {'Exp', 'PL'}} x[i,w,d,s,j]);

############### Second objective function constraints: Similar weeks for workers #############

subject to positive_values_of_absX{i in I, w in 1..5, d in 1..5, s in 1..3}:
	shift_differ_weeks[i,w,d,s] >= (y[i,w,d,s]-y[i,w+5,d,s]);

subject to negative_values_of_absX{i in I, w in 1..5, d in 1..5, s in 1..3}:
	shift_differ_weeks[i,w,d,s] >= -(y[i,w,d,s]-y[i,w+5,d,s]);

subject to sum_of_all_shifts_that_differ:
	shifts_that_differ = sum{i in I}(sum{w in 1..5}(sum{d in 1..5}(sum{s in 1..3} shift_differ_weeks[i,w,d,s])));

####################### Only assign if qualified and available ######################

subject to only_assigned_if_qualavail_weekdays{i in I, w in W, d in D, s in S[d], j in J[d]}: #librarians qualified for all: 'Exp', 'Info', 'PL', 'HB'
	x[i,w,d,s,j] <= (sum {v in V} (r[i,v]*qualavail[i,(w-v+10) mod 10 +1,d,s,j]));


###################### Worker shift assignment variable y ##############################
#Variable saying if a worker i is assigned a shift s, not accounting Library on Wheels
subject to assign_y{i in I, w in W, d in 1..5, s in 1..3}:
	y[i,w,d,s] = sum{j in {'Exp', 'Info', 'PL'}} x[i,w,d,s,j];

#Workers that shall be assigned a weekday free from tasks
subject to task_free_weekday{i in I_free_day, w in W}:
	sum{d in 1..5}(1-sum{s in 1..3}(sum{j in J[d]} x[i,w,d,s,j])) >= 1;

######################### Max tasks at same shift time constraint #################################
#Allowing only two shifts at a certain time each week, not accounting Library on Wheels
subject to max_two_shifts_at_same_hours_per_week{i in I, w in W, s in 1..3}:
	sum{d in 1..5} y[i,w,d,s] <= 2;

######################## Lib on Wheels constraints #########################
#Worker 25 works on LOW all available Thursdays
subject to 25_works_all_Thursdays:
	sum{w in W} x[25,w,4,4,'LOW'] = 8;

#Workers 25 has LOW every other Monday morning and 36 the other
subject to every_other_monday_morning{w in W}:
	x[36,w,1,4,'LOW'] = 1- x[25,w,1,1,'LOW'];

#Workers 14 and 37, five times in ten weeks
subject to five_times_LOW_in_10_weeks:
	sum {w in W}x[37,w,3,4,'LOW'] = 5;

#Workers 14 and 37 work every second week at LOW
subject to five_times_LOW_in_10_weeks2{w in 1..9}:
	x[37,w,3,4,'LOW'] = 1- x[37,w+1,3,4,'LOW'];

#Worker 36 only works on LOW in evenings
subject to only_LOW_in_evening{w in W, d in 1..4,j in {'Exp', 'Info', 'PL'}}:
	x[36,w,d,4,j] = 0;

######################## Fixed weekends #########################
subject to 3_4_1:
H[3,4,1] + H[3,4,2]= 1;
subject to 4_4_1:
H[4,4,1] + H[4,4,2]= 1;
subject to 5_2_1:
H[5,2,1] + H[5,2,2]= 1;
subject to 7_2_1:
H[7,2,1] + H[7,2,2]= 1;
subject to 8_1_1:
H[8,1,1] + H[8,1,2]= 1;
subject to 9_3_1:
H[9,3,1] + H[9,3,2]= 1;
subject to 12_1_1:
H[12,1,1] + H[12,1,2]= 1;
subject to 13_2_1:
H[13,2,1] + H[13,2,2]= 1;
subject to 14_4_1:
H[14,4,1] + H[14,4,2]= 1;
subject to 16_3_1:
H[16,3,1] + H[16,3,2]= 1;
subject to 17_5_1:
H[17,5,1] + H[17,5,2]= 1;
subject to 19_2_1:
H[19,2,1] + H[19,2,2]= 1;
subject to 23_5_1:
H[23,5,1] + H[23,5,2]= 1;
subject to 24_1_1:
H[24,1,1] + H[24,1,2]= 1;
subject to 25_5_1:
H[25,5,1] + H[25,5,2]= 1;
subject to 27_3_1:
H[27,3,1] + H[27,3,2]= 1;
subject to 31_4_1:
H[31,4,1] + H[31,4,2]= 1;
subject to 32_5_1:
H[32,5,1] + H[32,5,2]= 1;
subject to 36_4_1:
H[36,4,1] + H[36,4,2]= 1;
subject to 37_1_1:
H[37,1,1] + H[37,1,2]= 1;
subject to 38_3_1:
H[38,3,1] + H[38,3,2]= 1;
subject to 1_2_1:
H[1,2,1] + H[1,2,2]= 1;
subject to 6_3_1:
H[6,3,1] + H[6,3,2]= 1;
subject to 10_4_1:
H[10,4,1] + H[10,4,2]= 1;
subject to 11_2_1:
H[11,2,1] + H[11,2,2]= 1;
subject to 15_3_1:
H[15,3,1] + H[15,3,2]= 1;
subject to 18_1_1:
H[18,1,1] + H[18,1,2]= 1;
subject to 20_5_1:
H[20,5,1] + H[20,5,2]= 1;
subject to 22_3_1:
H[22,3,1] + H[22,3,2]= 1;
subject to 26_4_1:
H[26,4,1] + H[26,4,2]= 1;
subject to 29_1_1:
H[29,1,1] + H[29,1,2]= 1;
subject to 30_1_1:
H[30,1,1] + H[30,1,2]= 1;
subject to 33_2_1:
H[33,2,1] + H[33,2,2]= 1;
subject to 35_5_1:
H[35,5,1] + H[35,5,2]= 1;
subject to 39_5_1:
H[39,5,1] + H[39,5,2]= 1;
