#include "Library.h"
#include "Blocks.h"
#include "Workers.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include <cstdlib> //rand, srand
#include <algorithm>
#include <time.h> //time

Library::Library() {
	num_blocks = 0;
	for (int d=0; d<NUM_DAYS; d++){
		for (int s=0; s<NUM_SHIFTS; s++){
			for (int j=0; j<NUM_TASKS; j++){
				task_assign_avail[d][s][j] = 0; //Used to see if task j is available for assignment day d, shift s
				for (int w=0; w<NUM_WEEKS; w++){
					demand[w][d][s][j] = 0; //initialize as 0
					demand_differ[w][d][s][j] = 0; //initialize as 0
					tasks_filled[w][d][s][j] = 0;
					num_lib_assigned[w][d][s][j] = 0; //used to see if more are needed to be assigned a shift
					num_ass_assigned[w][d][s][j] = 0;
				}
			}
		}
	}
	readDemand();
	//createWorkers();
	for (int w=0; w<NUM_WEEKS; w++){
		HB_assigned[w] = 0;
		lib_per_rot[w] = 0;
		ass_per_rot[w] = 0;
		for(int d=0; d<NUM_DAYS-2; d++){
			stand_in_amount[w][d] = 0;
		}
	}
	lowest_cost_IDs = vector<int>();
	workers_destroyed = vector<int>();
	lowest_cost = 0;
	setTask_avail();
	//printTask_avail();
	
}


Library::~Library() {
	
}

int Library::getNum_lib_assigned(int w, int d, int s, int j) const{
	return num_lib_assigned[w][d][s][j];
}
int Library::getNum_ass_assigned(int w, int d, int s, int j) const{
	return num_ass_assigned[w][d][s][j];
}


int Library::getDemand(int week, int day, int shift, int task) const{
	return demand[week][day][shift][task];
}

void Library::setDemand(int week, int day, int shift, int task, int amount) {
	if (week == 1)
	{
		demand[week-1][day-1][shift-1][task-1] += amount;
		demand[week+1][day-1][shift-1][task-1] += amount;
		demand[week+3][day-1][shift-1][task-1] += amount;
	}
	else if(week == 2)
	{
		demand[week-1][day-1][shift-1][task-1] += amount;
		demand[week+1][day-1][shift-1][task-1] += amount;
	}
	else{
		cerr << "Error in inserting weeks in demand. Only week = 1 or week = 2 allowed" << endl;
	}
}
void Library::setDemand(int week, int day, int shift, string task, int amount) {
	task_type task_enum;
	if(task == "Exp"){
		task_enum = block;
	}
	else if (task == "Info"){
		task_enum = block;
	}
	else if (task == "PL"){
		task_enum = PL;
	}
	else if (task == "HB"){
		task_enum = HB;
	}
	else{
		task_enum = BokB;
	}
	
	if (week == 1)
	{
		demand[week-1][day-1][shift-1][task_enum-1] += amount;
		demand[week+1][day-1][shift-1][task_enum-1] += amount;
		demand[week+3][day-1][shift-1][task_enum-1] += amount;
	}
	else if(week == 2)
	{
		demand[week-1][day-1][shift-1][task_enum-1] += amount;
		demand[week+1][day-1][shift-1][task_enum-1] += amount;
	}
	else{
		cerr << "Error in inserting weeks in demand. Only week = 1 or week = 2 allowed" << endl;
	}
	
}

//Reads the demand from file "demand5w.txt" and set the matrix demand[w][d][s][t]
void Library::readDemand() {
	ifstream inFile("./src/data/demand5W.txt");
	
	//Checking for open Error
	if (inFile.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}
	
	vector<string> input_vector; 
	string readline, integer_string, demand_string, task;
	int week, day, shift, amount;
	while( inFile.good() )
	{
		//Read until an "=" is found and assign all availability
		getline( inFile, readline);
		input_vector.clear(); //input_vector contains the integers "week" "day" "shift" read from a line
		size_t found = readline.find("="); //Find the character with an "="
		size_t pos = readline.find (",");
		if(found != string::npos) //separate a readline if containing an "="
		{
			integer_string = readline.substr(0,found-1); //getting the string "1,1,1,Exp"
			demand_string = readline.substr(found+2); //getting the demand number as string
			//separate all three integers in integer_string into input_vector
			while(pos != string::npos)
			{
				input_vector.push_back(integer_string.substr(0,pos)); //adds everything that appears before the first ","
				integer_string = integer_string.substr(pos+1); //Everything after the "," is in the new integer_string
				pos = integer_string.find(","); //Find the position of the next "," in the new readline
			}
			//Add the last integer (as string) to input_vector
			input_vector.push_back(integer_string.substr(0,pos));
			
			amount = atoi(demand_string.c_str());
			
			task = input_vector.back();
			input_vector.pop_back();
			
			shift = atoi(input_vector.back().c_str());
			input_vector.pop_back();
			
			day = atoi(input_vector.back().c_str());
			input_vector.pop_back();
			
			week = atoi(input_vector.back().c_str());
			input_vector.pop_back();
			
			setDemand(week,day,shift,task,amount);
			//cout << "For w,d,s,j the demand is: " << week << " " << day << " " << shift << " " << task << " = " << demand_string << endl;
		}
	}
}

void Library::printDemand() {
	cout << "The big columns represent demand for: block (Exp+Info), PL, HB, BokB" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int j=0; j<NUM_TASKS; j++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << demand[w][d][s][j] << " ";
				}
				cout << "  \t";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}

vector <string> Library::get_info_vector() { //1 = ID, 2 = Name, 3 = Boss, 4 = Qual, 5 = Dep, 6 = PL, 7 = Weekend, 8 = HB, 9 = free_day
	ifstream inFile("./src/data/workers5W.txt");
	//Checking for open Error
	if (inFile.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}
	
	int line_read_num = 0;
	int workers_counted = 0;
	vector<string> input_vector;
	string readline;
	while( inFile.good() )
	{
		//Read a line
		getline( inFile, readline);
		line_read_num++; //the line read is number: line_read_num
		//cout << "info_type is: " << info_type << endl;
		if(line_read_num == 1+152*workers_counted)
		{
			for(int i = 0; i<9; i++)
			{
				//cout << readline << endl;
				input_vector.push_back(readline);
				getline( inFile, readline);
				line_read_num++; //the line read is number: line_read_num
			}
		}
		size_t found_new_worker = readline.find ("avail:");
		if(found_new_worker != string::npos) //A line is read containing "avail:"
		{
			workers_counted++;
		}
	}
	return input_vector;
}

//vector <string> get_info_vector(int info_type) { //1 = ID, 2 = Name, 3 = Boss, 4 = Qual, 5 = Dep, 6 = PL, 7 = Weekend, 8 = HB, 9 = free_day
//Worker::Worker(int id, string name, string boss, string qualification, string department, string pl, string weekend, string hb, string free_day) {
//Function to create 39 workers with all information.
void Library::createWorkers() {
	vector <string> info_vector;
	info_vector = get_info_vector();
	int ID = 0;
	string Name, Boss, Qual, Dep, PL, Weekend, HB, Freeday;
	for (int i=num_workers-1; i>=0; i--)
	{
		//cout << "\n Printing information gathered from info_vector:" << endl;
		Freeday = info_vector.back();
		info_vector.pop_back();
		HB = info_vector.back();
		info_vector.pop_back();
		PL = info_vector.back();
		info_vector.pop_back();
		Boss = info_vector.back();
		info_vector.pop_back();
		Weekend = info_vector.back();
		info_vector.pop_back();
		Dep = info_vector.back();
		info_vector.pop_back();
		Name = info_vector.back();
		info_vector.pop_back();
		ID = atoi(info_vector.back().c_str());
		info_vector.pop_back();
		Qual = info_vector.back();
		info_vector.pop_back();
		Worker aworker(ID, Name, Boss, Qual, Dep, PL, Weekend, HB, Freeday);
		myworkers[ID-1] = aworker; //Place the workers in order starting with: myworkers[0] is worker with ID 1.
	}
	setAvail_worker();
}


//Assigns avail for all workers
void Library::setAvail_worker() {
	ifstream inFile("./src/data/workers5W.txt");
	
	//Checking for open Error
	if (inFile.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}
	

	vector<string> input_vector; 
	string readline;
	string integer_string;
	string avail_string;
	int wID = 0;
	//string wID;
	int line_read_num = 0;
	int workers_counted = 0;
 	int week, day, shift;
	while( inFile.good() )
	{
		//Read until an "=" is found and assign all availability
		getline( inFile, readline);
		line_read_num++; //the line read is number: line_read_num
		input_vector.clear(); //input_vector contains the integers "week" "day" "shift" read from a line
		if(line_read_num == 2+152*workers_counted)
		{
			//Assign the ID of the worker that is being read (not in order)
			wID = atoi(readline.c_str());
		}
		
		//update workers_counted if "avail:" is found
		size_t found_new_worker = readline.find ("avail:");
		if(found_new_worker != string::npos) //A line is read containing "avail:"
		{
			workers_counted++;
		}
		
		size_t found = readline.find("="); //Find the character with an "="
		size_t pos = readline.find (",");
		if(found != string::npos) //separate a readline if containing an "="
		{
			
			integer_string = readline.substr(0,found-1); //getting the string "1,1,1"
			avail_string = readline.substr(found+2); //getting the avail number as strings
			//separate all three integers in integer_string into input_vector
			while(pos != string::npos)
			{
				input_vector.push_back(integer_string.substr(0,pos)); //adds everything that appears before the first ","
				integer_string = integer_string.substr(pos+1); //Everything after the "," is in the new integer_string
				pos = integer_string.find(","); //Find the position of the next "," in the new readline
			}
			//Add the last integer (as string) to input_vector
			input_vector.push_back(integer_string.substr(0,pos));
			
			shift = atoi(input_vector.back().c_str());
			input_vector.pop_back();
			day = atoi(input_vector.back().c_str());
			input_vector.pop_back();
			week = atoi(input_vector.back().c_str());
			input_vector.pop_back();
			//Assign the availability to the workers
			int AVAIL = atoi(avail_string.c_str());
			myworkers[wID-1].setAvail(week-1, day-1, shift-1, AVAIL);
		}
	}
}

void Library::setTask_avail(){
	//BokB not added here
	for(int j=1; j<=4; j++){
		switch(j){
			case 1 :{ //1 = No task
				for(int d=0; d<5; d++){ //Only avail day 1-5 => task_assign_avail[d=0:4]
					task_assign_avail[d][0][j-1] = 1;
				}
				break;
			}
			case 2:{ //2 = Block ('Exp' or 'Info')
				for(int d=0; d<NUM_DAYS; d++){
					for(int s=0; s<NUM_SHIFTS; s++){
						if(d >= 5){
							task_assign_avail[d][0][j-1] = 1;
						}
						else{
							task_assign_avail[d][s][j-1] = 1;
						}
					}
				}
				break;
			}
			case 3:{ //3 = PL
				for(int d=0; d<5; d++){ //Only avail day 1-5 => task_assign_avail[d=0:4]
					task_assign_avail[d][0][j-1] = 1;
				}
				break;
			}
			case 4:{ //4 = HB
				for(int d=5; d<NUM_DAYS; d++){
					task_assign_avail[d][0][j-1] = 1;
				}
				break;
			}
// 			case 5:{ //5 = BokB DIFFER FOR DIFFERENT WEEKS
// 				for(int d=5; d<NUM_DAYS; d++){
// 					task_assign_avail[d][1][j-1] = 1;
// 				}
// 				break;
// 			}
		}
	}
}

void Library::printTask_avail(){
	cout << "The matrices represent task assignment availability for: No task, Block, PL, HB, BokB" << endl;
	for (int s=0; s< NUM_SHIFTS; s++){
		for (int j=0; j<NUM_TASKS; j++){
			for (int d=0; d< NUM_DAYS; d++){
				cout << task_assign_avail[d][s][j] << " ";
			}
			cout << "\t";
		}
		cout << endl;
	}
}

int Library::getTask_avail(int d, int s, int j) const{
	return task_assign_avail[d][s][j];
}

Worker& Library::getWorker(int i){
	return myworkers[i-1];
}

void Library::create_all_blocks() {
	int num_shifts[NUM_SHIFTS]; //Only for weekdays (max 2 shifts at the same hour per week)
	for(int i=0; i<NUM_SHIFTS; i++){
		num_shifts[i] = 0;
	}
	int num_blocks_to_create = 0;
	int sum_PL = 0, sum_evenings = 0, shift_flag = 0;
	int blocks = 0;
	//int s[NUM_DAYS];
	for(int s1=1; s1<=NUM_SHIFTS; s1++){
		for(int j1=0; j1<3; j1++){ //if avail for no task, block or PL, not checking BokB
			if(task_assign_avail[1-1][s1-1][j1] == 1){
				//Loop another day
				for(int s2=1; s2<=NUM_SHIFTS; s2++){
					for(int j2=0; j2<3; j2++){
						if(task_assign_avail[2-1][s2-1][j2] == 1){
							//Loop another day
							for(int s3=1; s3<=NUM_SHIFTS; s3++){
								for(int j3=0; j3<3; j3++){
									if(task_assign_avail[3-1][s3-1][j3] == 1){
										//Loop another day
										for(int s4=1; s4<=NUM_SHIFTS; s4++){
											for(int j4=0; j4<3; j4++){
												if(task_assign_avail[4-1][s4-1][j4] == 1){
													//Loop another day
													for(int s5=1; s5<=NUM_SHIFTS; s5++){ //Does NOT include friday afternoons!
														for(int j5=0; j5<3; j5++){
															if(task_assign_avail[5-1][s5-1][j5] == 1){
// 																blocks++;
																//Loop another day ***Saturday*** s6 == 1
																for(int j6=0; j6<3; j6++){ //j=3 means HB in task_assign_avail. No check for task_assign_avail since all are avail.
																	for(int j7=0; j7<3; j7++){
																		if(j6 == j7){
																			blocks++; //Check the upper limit of blocks
																			if((s5 == 4 && j5 == 1 && j5 == j6) || (s5 == 1 && j6 == 0) || ((s5 == 2 || s5 == 3) && j5 == 1 && j6 == 0) || (s5 == 1 && j5 == 0 && j6 == 2)){
// 																				if(j1 == j2 && j2 == j3 && j3 == j4 && j4 == 0 && j5 == j6 && j6 == j7 && j5 == 1){
// 																					cout << "Creating a weekend 'block', 'block', 'block' at block index: " << num_blocks_to_create << endl;
// 																				}
																				
																				//Calculate the sums
																				if(j1 == 2){sum_PL++;}
																				if(j2 == 2){sum_PL++;}
																				if(j3 == 2){sum_PL++;}
																				if(j4 == 2){sum_PL++;}
																				if(j5 == 2){sum_PL++;}
																				if(j1 != 0 && s1 == 4){sum_evenings++;} //Does not include fridays
																				if(j2 != 0 && s2 == 4){sum_evenings++;}
																				if(j3 != 0 && s3 == 4){sum_evenings++;}
																				if(j4 != 0 && s4 == 4){sum_evenings++;}
																				if(j1 != 0){num_shifts[s1]++;} //do not include "No task" in the max amount of shifts
																				if(j2 != 0){num_shifts[s2]++;} //Only for weekdays are the shifts included for
																				if(j3 != 0){num_shifts[s3]++;}
																				if(j4 != 0){num_shifts[s4]++;}
																				if(j5 != 0){num_shifts[s5]++;}
																				
																				//Set flag for num_shifts
																				for(int i=0; i<NUM_SHIFTS; i++){
																					if(num_shifts[i] > 2){shift_flag = 1;}
																				}
																				//Create blocks
																				if(!(sum_PL > 1) && !(sum_evenings > 1) && shift_flag == 0){
																					Block a_block(block_vector.size()); //Create the object with ID, starting at 0
																					//cout << s1 << ", " << j1 << ", " <<  s2 << ", " << j2 << ", " << s3 << ", " << j3 << ", " << s4 << ", " << j4 << ", " << s5 << ", " << j5 << ", " << j6 << ", " << j7 << endl;
																					assign_tasks_to_block(a_block, s1, j1, s2, j2, s3, j3, s4, j4, s5, j5, j6, j7);
																					a_block.setnum_tasks();
																					block_vector.push_back(a_block);
// 																					cout << "block_vector size is: " << block_vector.size() << endl;
// 																					cout << "num_blocks_to_create is: " << num_blocks_to_create << endl;
																					num_blocks_to_create++;
																				}
																				//Reset all the variables for next iteration
																				sum_PL = 0;
																				sum_evenings = 0;
																				shift_flag = 0;
																				for(int i=0; i<NUM_SHIFTS; i++){
																					num_shifts[i] = 0;
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "Number of blocks to create are: " << num_blocks_to_create << endl;
	cout << "maximum number of combinations for 7 days are: " << blocks << endl;
	num_blocks = num_blocks_to_create; //Assign the "global variable" in the Library class
}

void Library::assign_tasks_to_block(Block& block, int s1, int j1, int s2, int j2, int s3, int j3, int s4, int j4, int s5, int j5, int j6, int j7){
// 	for(int i=0; i<5; i++){
// 		block.setTask(i,s[i],j[i],1);
// 	}
	int num_of_blocks = 0;
	int num_of_PL = 0;
	block.setTask(1, s1, j1, 1); //s == 1,2,3,4; j = 0,1,2 (no task, Block, PL, HB if weekend)
	block.setTask(2, s2, j2, 1);
	block.setTask(3, s3, j3, 1);
	block.setTask(4, s4, j4, 1);
	block.setTask(5, s5, j5, 1);
	if(j6 != 2){
		block.setTask(6, 1, j6, 1);
	}
	else{block.setTask(6, 1, j6+1, 1);} //j6 == 3 means HB
	if(j7 != 2){
		block.setTask(7, 1, j7, 1);
	}
	else{block.setTask(7, 1, j7+1, 1);} //j7 == 3 means HB
		
	//set num_tasks for weekdays and num_PL
	if(j1 == 1){
		num_of_blocks++;}
	else if(j1 == 2){
		num_of_PL++;}
	if(j2 == 1){
		num_of_blocks++;}
	else if(j2 == 2){
		num_of_PL++;}
	if(j3 == 1){
		num_of_blocks++;}
	else if(j3 == 2){
		num_of_PL++;}
	if(j4 == 1){
		num_of_blocks++;}
	else if(j4 == 2){
		num_of_PL++;}
	if(j5 == 1){
		num_of_blocks++;}
	else if(j5 == 2){
		num_of_PL++;}
	//Set the number of tasks assigned
// 	block.setnum_tasks(num_of_blocks+num_of_PL);
	block.setnum_Blocks(num_of_blocks);
	block.setnum_PL(num_of_PL);
	//Weekend assigned?
	if(j6 != 0){block.setWeektype("weekend");}
	//HB assigned?
	if(j6 == 2){block.setnum_HB(1);}
}

void Library::assign_blocks_to_workers(){ //using Worker myworkers[39], vector<Block> block_vector. 
	for(int i=0; i<num_workers; i++){
		for(unsigned int n = 0; n<block_vector.size(); n++){
			assign_block(&block_vector.at(n), i+1);
		}
		cout << "Worker: " << i+1 << " has " << myworkers[i].getweekend_vect().size() << " " << myworkers[i].getweekrest_vect().size() << " " << myworkers[i].getweekday_vect().size() << " in sizes" << endl;
	}
	
}

void Library::assign_block(Block* block, int worker_id){ //assign the block to the worker if ok availability. worker_id a number between 1 to 39
	int is_lib = 0;
	int w_check_error[3]; //0 for week w if no errors are found
	for (int w=0; w<3; w++){w_check_error[w] = 0;}
	if(myworkers[worker_id-1].getQual().compare(0,3,"lib") == 0){
		is_lib = 1;
	}else{is_lib = 0;}
// 	cout << "getAvail is: " << myworkers[worker_id-1].getAvail(0,0,3) << " getTask is: " << block.getTask(0,3,1) << endl;
	for (int w=0; w<3; w++){ //Check for weekend week (w = 0), weekrest week (w = 1) and weekday week (w = 2)
		w_check_error[w] = 0; //Reset when looking at a new week
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				if(w == 0 && myworkers[worker_id-1].getWeekend().compare(0,7,"weekend") == 0 && (d == 5 || d == 6) && s == 0){ //weekend worker on a weekend
					if(block->getTask(d,s,1) == 0 && block->getTask(d,s,3) == 0){ //if wend worker and no weekend assigned to the block
						w_check_error[w] = 1;
					}
				}else if(w == 0 && week_empty_of_tasks(block)){w_check_error[w] = 0;}
				for (int j=1; j<=4; j++){ //Only checking for Block, PL and HB (now also LOW)
					if(j == 1){ //Block
						if(myworkers[worker_id-1].getAvail(w,d,s) < block->getTask(d,s,j) || (w == 0 && (d == 5 || d == 6) && s == 0 && myworkers[worker_id-1].getHB().compare(0,7,"only_HB") == 0 && block->getTask(d,s,j) == 1)){
							w_check_error[w] = 1;
						}
					}
					else if(j == 2){ //PL
						if(block->getTask(d,s,j) == 1){ //A PL is assigned to block
							//check the three consecutive shifts, s = 1, 2, 3
							if(!(myworkers[worker_id-1].getAvail(w,d,s) == 1 && myworkers[worker_id-1].getAvail(w,d,s+1) == 1 && getWorker(worker_id).getAvail(w,d,s+2) == 1) || myworkers[worker_id-1].getPL().compare(0,5,"no_PL") == 0){
								w_check_error[w] = 1;
							}
						}
					}
					else if(j == 3){ //HB
						if((d == 5 || d == 6) && s == 0){ //HB only occuring on weekends at shift 0. ('optimizing' code)
							if(block->getTask(d,s,j) == 1 && is_lib == 0){
								w_check_error[w] = 1; //Error for all weeks, due to being "ass"
							}
							else if( (myworkers[worker_id-1].getAvail(w,d,s) < block->getTask(d,s,j)) || (w == 0 && myworkers[worker_id-1].getHB().compare(0,5,"no_HB") == 0 && block->getTask(d,s,j) == 1) ){ //lib nonavail or not avail for HB
								w_check_error[w] = 1;
							}
						}
					}
// 					else if(j == 4){ //LOW
// 						//Remove blocks for LOW-workers with tasks the days they have LOW
// 						switch(worker_id){
// 							case 14 :{ //Prevent tasks on wednesdays
// // 								if(d == 2 && (block->getTask(d,s,1) == 1 || block->getTask(d,s,2) == 1) ){
// // 									w_check_error[w] = 1;
// // 								}
// 								break;
// 							}
// 							case 17 :{ //Prevent tasks on fridays (not evenings!)
// // 								if(d == 4 && (s==0 || s == 1 || s == 2) && (block->getTask(d,s,1) == 1 || block->getTask(d,s,2) == 1) ){
// // 									w_check_error[w] = 1;
// // 								}
// 								break;
// 							}
// 							case 25 :{ //Prevent tasks on mondays and thursdays
// // 								if((d == 0 || d == 3) && (block->getTask(d,s,1) == 1 || block->getTask(d,s,2) == 1) ){
// // 									w_check_error[w] = 1;
// // 								}
// // 								break;
// 							}
// 							case 36 :{ //Prevent tasks on mondays, wednesdays, thursdays and fridays (not evenings!)
// // 								if((d == 0 || d == 2 || d == 3) && (block->getTask(d,s,1) == 1 || block->getTask(d,s,2) == 1) ){
// // 									w_check_error[w] = 1;
// // 								}
// // 								if(d == 4 && (s==0 || s == 1 || s == 2) && (block->getTask(d,s,1) == 1 || block->getTask(d,s,2) == 1) ){
// // 									w_check_error[w] = 1;
// // 								}
// 								break;
// 							}
// 							case 37 :{ //Prevent tasks on wednesdays
// // 								if(d == 2 && (block->getTask(d,s,1) == 1 || block->getTask(d,s,2) == 1) ){
// // 									w_check_error[w] = 1;
// // 								}
// 								break;
// 							}
// 						}
// 					}
				}
			}
		}
// 		for(int x=0; x<3; x++){cout << w_check_error[x] << " ";}
// 		cout << endl;
		if(w_check_error[w] == 0){
			//Need to know for which w (if all or just some) that are okay.
			if(w == 0){ //for the worker: Access the vector with weekend blocks and add the block to it
				myworkers[worker_id-1].add_block_avail("weekend",block); //block is a pointer here
// 				myworkers[worker_id-1].getweekend_vect().push_back(block);
// 				cout << "Pushing back a weekend block!!!" << endl;
// 				cout << "Size is now: " << myworkers[worker_id-1].getweekend_vect().size() << endl;
			} else if(w == 1){
// 				myworkers[worker_id-1].getweekrest_vect().push_back(block);
				myworkers[worker_id-1].add_block_avail("weekrest",block); //block is a pointer here
// 				cout << "Pushing back a weekrest block!!!" << endl;
// 				cout << "Size is now: " << myworkers[worker_id-1].getweekrest_vect().size() << endl;
			} else if(w == 2){
// 				myworkers[worker_id-1].getweekday_vect().push_back(block);
				myworkers[worker_id-1].add_block_avail("weekday",block); //block is a pointer here
// 				cout << "Pushing back a weekday block!!!" << endl;
// 				cout << "Size is now: " << myworkers[worker_id-1].getweekday_vect().size() << endl;
			}
		}
	}
// 	cout << "Worker: " << worker_id << " has " << myworkers[worker_id-1].getweekend_vect().size() << " " << myworkers[worker_id-1].getweekday_vect().size() << " " << myworkers[worker_id-1].getweekrest_vect().size() << " in sizes" << endl;
	return; //Block has been assigned to the available vectors for the worker
}

void Library::print_weekblocks_avail_worker(int worker_id, string type){
	cout << "Weekblocks available for worker " << worker_id << " is:" << endl;
	if(type == "weekend"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getWeekend_cost_vector().size(); n++){
			myworkers[worker_id-1].getWeekend_cost_vector().at(n).block->getTask_matrix();
		}
	} else if(type == "weekday"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getWeekday_cost_vector().size(); n++){
			myworkers[worker_id-1].getWeekday_cost_vector().at(n).block->getTask_matrix();
		}
	} else if(type == "weekrest"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getWeekrest_cost_vector().size(); n++){
			myworkers[worker_id-1].getWeekrest_cost_vector().at(n).block->getTask_matrix();
		}
	} else{
		cerr << "Not a valid string as inargument" << endl;
	}
}

void Library::print_all_weekblocks_avail_worker(int worker_id, string type){
	cout << "Weekblocks available for worker " << worker_id << " is:" << endl;
	if(type == "weekend"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getblock_avail_vect(type).size(); n++){
			myworkers[worker_id-1].getblock_avail_vect(type).at(n)->getTask_matrix();
		}
	} else if(type == "weekday"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getblock_avail_vect(type).size(); n++){
			myworkers[worker_id-1].getblock_avail_vect(type).at(n)->getTask_matrix();
		}
	} else if(type == "weekrest"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getblock_avail_vect(type).size(); n++){
			myworkers[worker_id-1].getblock_avail_vect(type).at(n)->getTask_matrix();
		}
	} else{
		cerr << "Not a valid string as inargument" << endl;
	}
}


void Library::print_weekblocks_assigned_worker(int worker_id, string str){
	int weekend_week = 0;
	weekend_week = myworkers[worker_id-1].getWeekend_week();
	if(str == "weekend"){
		if(myworkers[worker_id-1].getblocks_assigned().size() == 5){
			cout << "Weekend block assigned:" << endl;
			myworkers[worker_id-1].getblocks_assigned().at(weekend_week)->getTask_matrix();
		}
	} else if(str == "weekrest"){
		if(myworkers[worker_id-1].getblocks_assigned().size() == 5){
			cout << "Weekrest block assigned:" << endl;
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+1) % 5)->getTask_matrix();
		}
	} else if(str == "weekday"){
		if(myworkers[worker_id-1].getblocks_assigned().size() == 5){
			cout << "Weekday blocks assigned:" << endl;
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+2) % 5)->getTask_matrix(); //first weekday
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+3) % 5)->getTask_matrix(); //second weekday
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+4) % 5)->getTask_matrix(); //third weekday
		}
	} else{
		cerr << "Not a valid string as inargument" << endl;
	}
}

void Library::print_all_weekblocks_assigned_worker(int worker_id){
	int weekend_week = 0;
	weekend_week = myworkers[worker_id-1].getWeekend_week();
	if(myworkers[worker_id-1].getblocks_assigned().size() == 5){
		cout << "Weekend block assigned:" << endl;
		myworkers[worker_id-1].getblocks_assigned().at(weekend_week)->getTask_matrix();
		cout << "Weekrest block assigned:" << endl;
		myworkers[worker_id-1].getblocks_assigned().at((weekend_week+1) % 5)->getTask_matrix();
		cout << "Weekday blocks assigned:" << endl;
		myworkers[worker_id-1].getblocks_assigned().at((weekend_week+2) % 5)->getTask_matrix(); //first weekday
		myworkers[worker_id-1].getblocks_assigned().at((weekend_week+3) % 5)->getTask_matrix(); //second weekday
		myworkers[worker_id-1].getblocks_assigned().at((weekend_week+4) % 5)->getTask_matrix(); //third weekday
	}
}





bool Library::week_empty_of_tasks(Block* block){ //Returns true if there are "no tasks" Monday - Sunday
	int num_ones = 0;
	for(int d = 0; d<NUM_DAYS; d++){
		num_ones += block->getTask(d,0,0);
	}
	if(num_ones == 7){
		return true;
	}
	else{
		return false;
	}
}

int Library::getNum_blocks() const{
	return num_blocks;
}
void Library::setNum_blocks(int num) {
	num_blocks = num;
}
vector<Block>& Library::get_block_vector(){
	return block_vector;
}

void Library::assign_rot_to_workers(){
	cout << "in assign_rot_to_workers" << endl;
	int min_lib_per_rot;
	int min_ass_per_rot;
	int rand_week = 0;
	int temp_min = 0;
	bool not_seven_per_weekend = true;
	int counter = 0;
	
	cout << "lib_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << lib_per_rot[w] << " ";
	}
	cout << endl;
	cout << "ass_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << ass_per_rot[w] << " ";
	}
	cout << endl;
	while(not_seven_per_weekend){ //Extra function to make sure there are always 7 workers each weekend
		min_ass_per_rot = 0;
		min_lib_per_rot = 0;
		counter = 0;
		for(int w=0; w<NUM_WEEKS; w++){lib_per_rot[w] = 0; ass_per_rot[w] = 0;} //initialize as 0
		myworkers[14-1].setWeekend_week(2-1);
		lib_per_rot[2-1]++; //All are weekend workers
		myworkers[17-1].setWeekend_week(4-1);
		lib_per_rot[4-1]++;
		myworkers[25-1].setWeekend_week(2-1);
		lib_per_rot[2-1]++;
		myworkers[36-1].setWeekend_week(3-1);
		lib_per_rot[3-1]++;
		myworkers[37-1].setWeekend_week(3-1);
		lib_per_rot[3-1]++;
		
		for(int i=1; i<=num_workers; i++){
			if(i != 14 && i != 17 && i != 25 && i != 36 && i != 37){
				while(true){
					rand_week = rand() % 5; //generates a random number between 0 to 4
					if(myworkers[i-1].getQual().compare(0,3,"lib") == 0){
						if(lib_per_rot[rand_week] == min_lib_per_rot){
							myworkers[i-1].setWeekend_week(rand_week);
							if(myworkers[i-1].getWeekend().compare(0,7,"weekend") == 0){ //Only count if a weekend worker
								lib_per_rot[rand_week]++;
							}
							temp_min = 777;
							for(int w=0; w<NUM_WEEKS; w++){ //Update min_worker_per_rot
								if(lib_per_rot[w] <= temp_min){
									temp_min = lib_per_rot[w];
								}
							}
							min_lib_per_rot = temp_min;
							break;
						}
					}
					else if(myworkers[i-1].getQual().compare(0,3,"ass") == 0){
						if(ass_per_rot[rand_week] == min_ass_per_rot){
							myworkers[i-1].setWeekend_week(rand_week);
							if(myworkers[i-1].getWeekend().compare(0,7,"weekend") == 0){ //Only count if a weekend worker
								ass_per_rot[rand_week]++;
							}
							temp_min = 777;
							for(int w=0; w<NUM_WEEKS; w++){ //Update min_worker_per_rot
								if(ass_per_rot[w] <= temp_min){
									temp_min = ass_per_rot[w];
								}
							}
							min_ass_per_rot = temp_min;
							break;
						}
					} else{cerr << "Should never be here in Library::assign_rot_to_workers" << endl;
					break;}
				}
			}
		}
		
		//Print when 7 workers found
		for(int w=0; w<NUM_WEEKS; w++){
			if(lib_per_rot[w] + ass_per_rot[w] == 7){
// 				cout << "found 7 workers for week " << w << endl;
				counter++;
			}
		}
		
		//Exit while loop
		if(counter == 5){
			not_seven_per_weekend = false;
		}
	}
	
	
	cout << "lib_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << lib_per_rot[w] << " ";
	}
	cout << endl;
	cout << "ass_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << ass_per_rot[w] << " ";
	}
	cout << endl;
	return;
}

void Library::assign_a_rot_to_worker(int i){ //Assign a new random weekend for the worker (>= 36 workers already assigned)
// 	int lib_per_rot[NUM_WEEKS];
// 	int ass_per_rot[NUM_WEEKS];
	int five_libs_assigned = 0;
	int rand_week = 0;
	for(int w=0; w<NUM_WEEKS; w++){
		if(lib_per_rot[w] == 5){five_libs_assigned = 1;}
	}
	
	while(true){ //Find a week that needs assignments
// 		srand(time(NULL));
		rand_week = rand() % 5; //generates a random number between 0 to 4
		if(lib_per_rot[rand_week] + ass_per_rot[rand_week] < 7 || myworkers[i-1].getWeekend().compare(0,10,"no_weekend") == 0){
			if(myworkers[i-1].getQual().compare(0,3,"ass") == 0 && ass_per_rot[rand_week] <= 2){
				break;
			}else if(myworkers[i-1].getQual().compare(0,3,"lib") == 0 && five_libs_assigned == 1 && lib_per_rot[rand_week] < 4){
				break;
			}else if(myworkers[i-1].getQual().compare(0,3,"lib") == 0 && five_libs_assigned == 0 && lib_per_rot[rand_week] < 5){
				break;
			}
		}
	}
	cout << "rand_week is: " << rand_week << endl;
	
	//Librarian
	if(myworkers[i-1].getQual().compare(0,3,"lib") == 0){
		if(five_libs_assigned == 1){ //a week has already been assigned 5 libs
			if(lib_per_rot[rand_week] + ass_per_rot[rand_week] < 7 && lib_per_rot[rand_week] < 4){
				//Assign weekend and count
				myworkers[i-1].setWeekend_week(rand_week);
				if(myworkers[i-1].getWeekend().compare(0,7,"weekend") == 0){ //Only count if a weekend worker
					lib_per_rot[rand_week]++;
				}
			}
		}
		else if(five_libs_assigned == 0){
			if(lib_per_rot[rand_week] + ass_per_rot[rand_week] < 7 && lib_per_rot[rand_week] < 5){
				//Assign weekend and count
				myworkers[i-1].setWeekend_week(rand_week);
				if(myworkers[i-1].getWeekend().compare(0,7,"weekend") == 0){ //Only count if a weekend worker
					lib_per_rot[rand_week]++;
				}
			}
		}
	}
	
	//Assistant
	else if(myworkers[i-1].getQual().compare(0,3,"ass") == 0){
		if(lib_per_rot[rand_week] + ass_per_rot[rand_week] < 7 && ass_per_rot[rand_week] <= 2){
			//Assign weekend and count
			myworkers[i-1].setWeekend_week(rand_week);
			if(myworkers[i-1].getWeekend().compare(0,7,"weekend") == 0){ //Only count if a weekend worker
				ass_per_rot[rand_week]++;
			}
		}
	}
	cout << "Assigned a rot to worker " << i << endl;
	cout << "New weekend assignment is: " << endl;
	print_weekends_assigned();
}

void Library::print_weekends_assigned(){
	cout << "lib_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << lib_per_rot[w] << " ";
	}
	cout << endl;
	cout << "ass_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << ass_per_rot[w] << " ";
	}
	cout << endl;
}

void Library::calculate_HB_assigned(){
//assign the variable HB_assigned[NUM_WEEKS] if tasks_filled for weekend is greater than 0.
	for(int w=0; w<NUM_WEEKS; w++){
		if(tasks_filled[w][5][0][2] > 0 && tasks_filled[w][6][0][2] > 0){
			HB_assigned[w] = 1;
		}
	}
}

void Library::calculate_tasks_filled(){
//Calculate which tasks has been assigned to workers for specific weeks
//Also calculating #libs and #ass per shift that is assigned
	clear_tasks_filled();
	calculate_LOW_filled(); //Separate matrices for each LOW-worker
	for(int i=0; i<num_workers; i++){
		for(int w=0; w<NUM_WEEKS; w++){
			for(int d=0; d<NUM_DAYS; d++){
				for(int s=0; s<NUM_SHIFTS; s++){
					for(int j=0; j<NUM_TASKS-1; j++){ //For Block, PL, HB (BokB not added here)
						tasks_filled[w][d][s][j] += myworkers[i].getblocks_assigned().at(w)->getTask(d,s,j+1);
						if(myworkers[i].getblocks_assigned().at(w)->getTask(d,s,j+1) == 1){
							if(myworkers[i].getQual().compare(0,3,"lib") == 0){
								num_lib_assigned[w][d][s][j]++;
							}
							else{
								num_ass_assigned[w][d][s][j]++;
							}
						}
					}
				}
			}
		}
	}
}
void Library::clear_tasks_filled(){
	for(int w=0; w<NUM_WEEKS; w++){
		for(int d=0; d<NUM_DAYS; d++){
			for(int s=0; s<NUM_SHIFTS; s++){
				for(int j=0; j<NUM_TASKS-1; j++){ //For Block, PL, HB. Dont clear BokB
					tasks_filled[w][d][s][j] = 0;
					num_lib_assigned[w][d][s][j] = 0;
					num_ass_assigned[w][d][s][j] = 0;
				}
			}
		}
	}
}

void Library::print_tasks_filled(){
	calculate_tasks_filled();
	cout << "These matrices represent all tasks filled with workers: block, PL, HB, BokB" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int j=0; j<NUM_TASKS; j++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << tasks_filled[w][d][s][j] << " ";
				}
				cout << "  \t";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}

void Library::print_num_workers(string type){
	if(type == "lib"){
		cout << "Number of librarians assigned: block, PL, HB, BokB" << endl;
		for (int w=0; w< NUM_WEEKS; w++){
			for (int s=0; s< NUM_SHIFTS; s++){
				for (int j=0; j<NUM_TASKS; j++){
					for (int d=0; d< NUM_DAYS; d++){
						cout << num_lib_assigned[w][d][s][j] << " ";
					}
					cout << "  \t";
				}
				cout << endl;
			}
			cout << endl << endl;
		}
	}else if(type == "ass"){
		cout << "Number of assistants assigned: block, PL, HB, BokB" << endl;
		for (int w=0; w< NUM_WEEKS; w++){
			for (int s=0; s< NUM_SHIFTS; s++){
				for (int j=0; j<NUM_TASKS; j++){
					for (int d=0; d< NUM_DAYS; d++){
						cout << num_ass_assigned[w][d][s][j] << " ";
					}
					cout << "  \t";
				}
				cout << endl;
			}
			cout << endl << endl;
		}
	}
}


void Library::initial_add_blocks_to_workers(){ //Add empty weeks to all workers
	for(int i=0; i<39; i++){
		for(int n=0; n<5; n++){ //add 5 empty blocks per worker
			myworkers[i].init_add_block_to_worker();
		}
	}
}

void Library::calculate_demand_differ(){ //Calculate the difference between Library demand vs tasks filled by workers
	for(int w=0; w<NUM_WEEKS; w++){
		for(int d=0; d<NUM_DAYS; d++){
			for(int s=0; s<NUM_SHIFTS; s++){
				for(int j=0; j<NUM_TASKS; j++){
					demand_differ[w][d][s][j] = demand[w][d][s][j] - tasks_filled[w][d][s][j];
				}
			}
		}
	}
}

void Library::print_demand_differ(){
	calculate_demand_differ();
	cout << "Demand difference in the library for: block, PL, HB, BokB" << endl;
	cout << "Negative values means overstaffing, positive means lack of workers" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int j=0; j<NUM_TASKS; j++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << demand_differ[w][d][s][j] << " ";
				}
				cout << "  \t";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}

void Library::calculate_demand(){ //Updates tasks_filled, demand_differ (+ LOW-assigned) and HB_assigned 
	calculate_tasks_filled();
	calculate_demand_differ();
	calculate_HB_assigned();
}

void Library::calculate_all_week_costs_for_worker(string type, int w_id, int count){
	int calculate = 1;
	if(type == "weekrest"){
		//Clear vector
		myworkers[w_id-1].clear_cost_vector(type);
		//Calculate costs iff the block does not overlap with assigned LOW
		int w = (myworkers[w_id-1].getWeekend_week()+1) % 5; //due to weekrest
		for(unsigned int n=0; n<myworkers[w_id-1].getweekrest_vect().size(); n++){
			calculate = check_if_collision(n,w_id,w,type); //returns 0 if a task collides with LOW
			if(calculate == 1){
				myworkers[w_id-1].calculate_week_cost(myworkers[w_id-1].getweekrest_vect().at(n), type, demand_differ, num_lib_assigned, num_ass_assigned, HB_assigned, count);
			}else{
// 				cout << "Collision with LOW!" << endl;
			}
		}
	} else if(type == "weekday"){
		//Clear vector
		myworkers[w_id-1].clear_cost_vector(type);
		//Calculate costs
		int w = (myworkers[w_id-1].getWeekend_week()+1+count) % 5; //due to weekday
		for(unsigned int n=0; n<myworkers[w_id-1].getweekday_vect().size(); n++){
			calculate = check_if_collision(n,w_id,w,type); //returns 0 if a task collides with LOW
			if(calculate == 1){
				myworkers[w_id-1].calculate_week_cost(myworkers[w_id-1].getweekday_vect().at(n), type, demand_differ, num_lib_assigned, num_ass_assigned, HB_assigned, count);
			}else{
// 				cout << "Collision with LOW!" << endl;
			}
		}
	} else if(type == "weekend"){
		//Clear vector
		myworkers[w_id-1].clear_cost_vector(type);
		//Calculate costs
		int w = myworkers[w_id-1].getWeekend_week(); //due to weekend
		for(unsigned int n=0; n<myworkers[w_id-1].getweekend_vect().size(); n++){
			calculate = check_if_collision(n,w_id,w,type); //returns 0 if a task collides with LOW
			if(calculate == 1){
				myworkers[w_id-1].calculate_week_cost(myworkers[w_id-1].getweekend_vect().at(n), type, demand_differ, num_lib_assigned, num_ass_assigned, HB_assigned, count);
			}else{
// 				cout << "Collision with LOW!" << endl;
			}
		}
	}
	
	else{cerr << "\n\nWrong 'type' as argument in calculate_all_week_costs_for_worker\n\n" << endl; return;}
}

int Library::check_if_collision(unsigned int n, int worker, int week, string type){
	int calc = 1;
	for(int d=0; d<NUM_DAYS-2; d++){
		for(int s=0; s<NUM_SHIFTS; s++){
			for(int j=1; j<=2; j++){ //Block and PL
				if(myworkers[worker-1].getblock_avail_vect(type).at(n)->getTask(d,s,j)==1 && myworkers[worker-1].get_LOW_assigned(week,d,s) == 1){
					calc = 0;
				}
			}
		}
	}
	return calc;
}

void Library::find_lowest_cost_in_vector(string type, int w_id){
	lowest_cost = 999999; //initialize as a high number after each function call
	lowest_cost_IDs.clear(); //Clear vector containing indices of block with lowest cost
	if(type == "weekend"){
		for(unsigned int n=0; n<myworkers[w_id-1].getWeekend_cost_vector().size(); n++){
			//Check if lower
			if(myworkers[w_id-1].getWeekend_cost_vector().at(n).wend_cost < lowest_cost){
				lowest_cost = myworkers[w_id-1].getWeekend_cost_vector().at(n).wend_cost;
				lowest_cost_IDs.clear();
				lowest_cost_IDs.push_back(myworkers[w_id-1].getWeekend_cost_vector().at(n).block->getID());
			//Check if equal (then add to vector or equals)
			}else if(myworkers[w_id-1].getWeekend_cost_vector().at(n).wend_cost == lowest_cost){
				lowest_cost_IDs.push_back(myworkers[w_id-1].getWeekend_cost_vector().at(n).block->getID());
			}
		}
	}else if(type == "weekday"){
		for(unsigned int n=0; n<myworkers[w_id-1].getWeekday_cost_vector().size(); n++){
			//Check if lower
			if(myworkers[w_id-1].getWeekday_cost_vector().at(n).wday_cost < lowest_cost){
				lowest_cost = myworkers[w_id-1].getWeekday_cost_vector().at(n).wday_cost;
				lowest_cost_IDs.clear();
				lowest_cost_IDs.push_back(myworkers[w_id-1].getWeekday_cost_vector().at(n).block->getID());
			//Check if equal (then add to vector or equals)
			}else if(myworkers[w_id-1].getWeekday_cost_vector().at(n).wday_cost == lowest_cost){
				lowest_cost_IDs.push_back(myworkers[w_id-1].getWeekday_cost_vector().at(n).block->getID());
			}
		}
	}else if(type == "weekrest"){
		for(unsigned int n=0; n<myworkers[w_id-1].getWeekrest_cost_vector().size(); n++){
			//Check if lower
			if(myworkers[w_id-1].getWeekrest_cost_vector().at(n).wrest_cost < lowest_cost){
				lowest_cost = myworkers[w_id-1].getWeekrest_cost_vector().at(n).wrest_cost;
				lowest_cost_IDs.clear();
				lowest_cost_IDs.push_back(myworkers[w_id-1].getWeekrest_cost_vector().at(n).block->getID());
			//Check if equal (then add to vector or equals)
			}else if(myworkers[w_id-1].getWeekrest_cost_vector().at(n).wrest_cost == lowest_cost){
				lowest_cost_IDs.push_back(myworkers[w_id-1].getWeekrest_cost_vector().at(n).block->getID());
			}
		}
	}
// 	cout << "The lowest cost found is: " << lowest_cost << endl;
// 	cout << "It occured for block ID(s): ";
// 	for(unsigned int j=0; j<lowest_cost_IDs.size(); j++){
// 		cout << lowest_cost_IDs.at(j) << " ";
// 	}
// 	cout << endl;
}

void Library::print_cost_vector(string type, int w_id){
	cout << "The costs for worker " << w_id << " is: " << endl;
	if(type == "weekend"){
		for(unsigned int n=0; n<myworkers[w_id-1].getWeekend_cost_vector().size(); n++){
			//Print each value to terminal
			cout << myworkers[w_id-1].getWeekend_cost_vector().at(n).wend_cost << endl;
// 			cout << myworkers[w_id-1].getWeekend_cost_vector().at(n).block->getID() << endl;
		}
	}else if(type == "weekday"){
		for(unsigned int n=0; n<myworkers[w_id-1].getWeekday_cost_vector().size(); n++){
			//Print each value to terminal
			cout << myworkers[w_id-1].getWeekday_cost_vector().at(n).wday_cost << endl;
// 			cout << myworkers[w_id-1].getWeekend_cost_vector().at(n).block->getID() << endl;
		}
	}else if(type == "weekrest"){
		for(unsigned int n=0; n<myworkers[w_id-1].getWeekrest_cost_vector().size(); n++){
			//Print each value to terminal
			cout << myworkers[w_id-1].getWeekrest_cost_vector().at(n).wrest_cost << endl;
// 			cout << myworkers[w_id-1].getWeekend_cost_vector().at(n).block->getID() << endl;
		}
	}
}


void Library::create_initial_solution(){
	vector<int> worker_vector;
	for(int i=0; i<num_workers; i++){
		worker_vector.push_back(i+1);
	}
	cout << "work_vect is: " << worker_vector.at(0) << endl;
	cout << "size is: " << worker_vector.size() << endl;
	int current_worker_index = 0;
	int current_worker = 0;
	int block_type_to_add = 0;
	string type = " ";
	while(worker_vector.size() != 0){
		current_worker_index = rand() % worker_vector.size(); //A number between 0-[size()-1]
		current_worker = worker_vector.at(current_worker_index);
		block_type_to_add = rand() % 3; //A number between 0-2, 0 means wend, 1 weekrest and 2 weekday
		while(myworkers[current_worker-1].get_block_types_added(block_type_to_add) == 1){ //Find a block-type to add
			block_type_to_add = rand() % 3; //Note: only workers that still need blocks added are still in vector.
		}
		if(block_type_to_add == 0){ //error due to being 0?
			type = "weekend";
		}else if(block_type_to_add == 1){
			type = "weekrest";
		}else if(block_type_to_add == 2){
			type = "weekday";
		}
// 		cout << "type is: " << type << endl;
		//SEARCH FOR ERRORS!
// 			if(current_worker == 25 && type == "weekend"){
// 				add_best_blocks_to_worker(type, current_worker);
// 				calculate_all_week_costs_for_worker(type,current_worker, 0);
// 				find_lowest_cost_in_vector(type,current_worker);
// // 				print_cost_vector(type,current_worker);
// // 				print_weekblocks_avail_worker(current_worker, type);
// 				print_weekblocks_assigned_worker(current_worker, type);
// 				cout << "The block already added to nr 23 is: " << endl;
// 				print_weekblocks_assigned_worker(23, type);
// 				return;
// 			}
		
		//Add for week type: "type"
		if(type != "weekday"){
// 			cout << "Add a " << type << " block" << endl;
			add_best_blocks_to_worker(type, current_worker);
			//Update tasks_filled, demand_differ and HB assigned
			calculate_tasks_filled();
			calculate_demand_differ();
			calculate_HB_assigned();
			
			
		}else{
			//Loop three times!
			for(int count=1; count<=3; count++){
				add_best_blocks_to_worker(type, current_worker, count);
				//Update tasks_filled and demand_differ
				calculate_tasks_filled(); //change to: add_tasks_filled(..)?
				calculate_demand_differ();
				
			}
		}
		//Tag that this week type has been assigned to the worker
		myworkers[current_worker-1].set_block_types_added(block_type_to_add,1);
		
// 		print_weekblocks_assigned_worker(current_worker, type);
		if(myworkers[current_worker-1].check_all_block_types_added() == 1){
		//Remove current_worker-1 from the vector worker_vector i.e. remove current_worker_index from vector			
			worker_vector.erase(worker_vector.begin()+current_worker_index);
		}
	}
	cout << "vector size is now: " << worker_vector.size() << endl;
	print_tasks_filled();
	print_demand_differ();
}


void Library::add_best_blocks_to_worker(string type, int current_worker, int count){
	//Add best block for block type "type"
	//Calculate the best block to add
	int block_index_to_add = 0;
	calculate_all_week_costs_for_worker(type,current_worker, count);
	find_lowest_cost_in_vector(type,current_worker);
	
	//pick a random ID if multiple index give same cost
	block_index_to_add = lowest_cost_IDs.at(rand() % lowest_cost_IDs.size());
// 	cout << "block index to add is: " << block_index_to_add << endl;
// 	cout << "Size of the vector is: " << myworkers[current_worker-1].getblock_avail_vect(type).size() << endl;
	//Find and add the best one using block_index_to_add
	for(unsigned int element=0; element<myworkers[current_worker-1].getblock_avail_vect(type).size(); element++){
		if(myworkers[current_worker-1].getblock_avail_vect(type).at(element)->getID() == block_index_to_add){
			//Check if correct by printing cost vector and available blocks!
					if(current_worker == 24 && type == "weekday" && count == 3){
					print_cost_vector(type,current_worker);
					print_weekblocks_avail_worker(current_worker, type);}
			myworkers[current_worker-1].add_block_to_worker(type, element, count);
		}
	}
	//Update tasks_filled and demand_difference after a new insertion
	
}

void Library::assign_LOW(){ //Assign library on wheels to the workers in question: 14, 17, 25, 36, 37
	for(int i=1; i<=num_workers; i++){
		for(int w=0; w<NUM_WEEKS; w++){ //w = 0-4
			for(int d=0; d<5; d++){
				for(int s=0; s<NUM_SHIFTS; s++){
					//Monday morning
					if(i == 25 && d == 0 && s == 0 && (w == 0 || w == 2)){
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1); //happening two times: wend_week and wend_week+2
					}else if(i == 36 && d == 0 && s == 0 && (w == 0 || w == 2 || w == 3)){
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1); //three times. wend_week, wend_week+2, wend_week+3
					}
					//Wednesday noon
					if(i == 14 && d == 2 && s == 3 && (w == 0 || w == 2)){
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1);
					}else if(i == 37 && d == 2 && s == 3 && (w == 0 || w == 2 || w == 3)){
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1);
					}
					//Thursday noon
					if(i == 25 && d == 3 && s == 3 && w != 1){//All weeks except its weekrest week
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1);
					}else if(i == 36 && d == 3 && s == 3 && w == (myworkers[25-1].getWeekend_week()+1)%5){//only when worker 25 has weekrest
						myworkers[i-1].set_LOW_assigned(w,d,s,1); //Check this one!
					}
					//Friday morning
					if(i == 17 && d == 4 && s == 0 && (w == 2 || w == 4)){
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1);
					}else if(i == 36 && d == 4 && s == 0 && w == 2){
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w)%5,d,s,1);
					}
					//Rest
					if(i == 36 && (((d == 0 && s == 3) && (w == 0 || w == 2 || w == 4))  || (d == 2 && s == 0) || (d == 3 && s == 0)) ){//mon noon, wed morning and thursday morning
						myworkers[i-1].set_LOW_assigned((myworkers[i-1].getWeekend_week()+w-2)%5,d,s,1);
					}
				}
			}
		}
	}
}

void Library::calculate_LOW_filled(){ //Sum all LOW assigned to the workers to see if filling demand
	//Clear calculate_LOW_filled
	clear_calculate_LOW_filled();
	for(int i=0; i<num_workers; i++){
		for(int w=0; w<NUM_WEEKS; w++){
			for(int d=0; d<NUM_DAYS; d++){
				for(int s=0; s<NUM_SHIFTS; s++){
					tasks_filled[w][d][s][3] += myworkers[i].get_LOW_assigned(w,d,s);
				}
			}
		}
	}
}

void Library::clear_calculate_LOW_filled(){
	for(int w=0; w<NUM_WEEKS; w++){
		for(int d=0; d<NUM_DAYS; d++){
			for(int s=0; s<NUM_SHIFTS; s++){
				tasks_filled[w][d][s][3] = 0;
			}
		}
	}
}

int Library::evaluate_solution(){//Add all costs together and return the total cost. Stand-ins not included here
	int total_cost = 0;
	int demand_tot_cost = 0;
	int demand_lib_cost = 0;
	int demand_ass_cost = 0;
	int demand_PL_cost = 0;
	int demand_HB_cost = 0;
	int demand_evening_cost = 0;
	int PL_amount_cost = 0;
	int no_weekend_cost = 0;
	
	int upper_limit = 0;
	int lower_limit = 0;
	//Demand cost+qualifications, #PL, #HB, (LOW?)
	for(int w=0; w<NUM_WEEKS; w++){
		for(int d=0; d<NUM_DAYS; d++){
			for(int s=0; s<NUM_SHIFTS;s++){
				//***DEMAND TOT COSTS***
				if(demand_differ[w][d][s][0] > 0){ //Understaffing Exp/Info
					if(num_lib_assigned[w][d][s][0] - demand[w][d][s][0]/2 < 0){//not enough libs => add two costs
						if(s != 3){demand_tot_cost += demand_differ[w][d][s][0]*DEMAND_FEW_TOT;
						}else{demand_evening_cost += demand_differ[w][d][s][0]*DEMAND_EVENING_COST;}
						demand_lib_cost += abs(num_lib_assigned[w][d][s][0]-demand[w][d][s][0]/2)*DEMAND_FEW_LIBS;
					}else{
						if(s != 3){demand_tot_cost += demand_differ[w][d][s][0]*DEMAND_FEW_TOT;
						}else{demand_evening_cost += demand_differ[w][d][s][0]*DEMAND_EVENING_COST;}
					}
				}else if(demand_differ[w][d][s][0] < 0){//Overstaffing Exp/Info
					if(num_lib_assigned[w][d][s][0] - demand[w][d][s][0]/2 < 0){//not enough libs => add two costs
						if(s != 3){demand_tot_cost += demand_differ[w][d][s][0]*DEMAND_FEW_TOT;
						}else{demand_evening_cost += demand_differ[w][d][s][0]*DEMAND_EVENING_COST;}
						demand_lib_cost += abs(num_lib_assigned[w][d][s][0]-demand[w][d][s][0]/2)*DEMAND_FEW_LIBS;
					}else{
						if(s != 3){demand_tot_cost += demand_differ[w][d][s][0]*DEMAND_FEW_TOT;
						}else{demand_evening_cost += demand_differ[w][d][s][0]*DEMAND_EVENING_COST;}
					}
				}else if(demand_differ[w][d][s][0] == 0 && //Feasible total amount of workers
					(num_lib_assigned[w][d][s][0] - demand[w][d][s][0]/2) < 0){ //not enough libs => add one cost
					demand_lib_cost += abs(num_lib_assigned[w][d][s][0]-demand[w][d][s][0]/2)*DEMAND_FEW_LIBS;
				}
				
			}
			
			//***DEMAND PL COSTS***
			if(demand_differ[w][d][0][1] > 0){ //Understaffing PL
				//take average of the two as cost
				demand_PL_cost += demand_differ[w][d][0][1]*(int)(DEMAND_PL_BAD_LIB+DEMAND_PL_BAD_ASS)/2;
			}
			if(demand_differ[w][d][0][1] < 0){ //Overstaffing PL
				//1 assistant is what is preferred
				demand_PL_cost += num_lib_assigned[w][d][0][1]*DEMAND_PL_BAD_LIB + (num_ass_assigned[w][d][0][1]-1)*DEMAND_PL_BAD_ASS;
			}
			
			
			//***DEMAND HB COSTS***
			if(demand_differ[w][d][0][2] > 0){ //Wrong demand at HB (only librarians in HB, Checking understaffing)
				demand_HB_cost += demand_differ[w][d][0][2]*DEMAND_HB_OVERSTAFF;
			}else if(demand_differ[w][d][0][2] < 0){ //Too many workers
				demand_HB_cost += abs(demand_differ[w][d][0][2])*DEMAND_HB_OVERSTAFF;
			}
			
		}
	}
	for(int i=0; i<num_workers; i++){
		//***PL AMOUNT PER WORKER COSTS***
		//Calculate lower and upper limit for each worker
		if(myworkers[i].getPL().compare(0,11,"standard_PL") == 0){lower_limit = 0; upper_limit = 3;}
		else if(myworkers[i].getPL().compare(0,5,"no_PL") == 0){lower_limit = 0; upper_limit = 0;}
		else if(myworkers[i].getPL().compare(0,7,"many_PL") == 0){lower_limit = 3; upper_limit = 4;}
		//Calculate costs
		if(myworkers[i].get_num_PL_assigned() < lower_limit){
			PL_amount_cost += (lower_limit - myworkers[i].get_num_PL_assigned())*PL_VIOLATE_COST;
// 			cout << "lower limit for worker " << i+1 << ": " << lower_limit - myworkers[i].get_num_PL_assigned() << " too few" << endl;
		}else if(myworkers[i].get_num_PL_assigned() > upper_limit){
			PL_amount_cost += (myworkers[i].get_num_PL_assigned() - upper_limit)*PL_VIOLATE_COST;
// 			cout << "upper limit for worker " << i+1 << ": " <<  myworkers[i].get_num_PL_assigned() - upper_limit << " too many" << endl;
		}
		
// 		cout << "#PL for worker " << i+1 << " is: " << myworkers[i].get_num_PL_assigned() << endl;
		
		//***EMPTY WEEKEND COSTS***
		//Check if weekend block is 0
		if(myworkers[i].getblocks_assigned().at(myworkers[i].getWeekend_week())->getID() == 0){
			//Add cost
			no_weekend_cost += NO_WEEKEND_COST;
		}
	}
	total_cost = demand_tot_cost + demand_lib_cost + demand_ass_cost + demand_PL_cost + demand_HB_cost + demand_evening_cost + PL_amount_cost + no_weekend_cost;
	cout << "demand_tot_cost = " << demand_tot_cost << endl;
	cout << "demand_lib_cost (too few or too many) = " << demand_lib_cost << endl;
	cout << "demand_ass_cost = " << demand_ass_cost << endl;
	cout << "demand_PL_cost = " << demand_PL_cost << endl;
	cout << "demand_HB_cost = " << demand_HB_cost << endl;
	cout << "demand_evening_cost = " << demand_evening_cost << endl;
	cout << "PL_amount_cost = " << PL_amount_cost << endl;
	cout << "no_weekend_cost = " << no_weekend_cost << endl;
	return total_cost;
}
// static const int STAND_IN_COST = 5;

void Library::destroy(){ //Destroy blocks for 3 random workers (and give new weekend, in repair?)
	int worker_to_destroy = 0;
	int num_workers_to_destroy = 3; //the amount of workers to destroy in destroy function. 3 gives a 7.5% destroy
	bool not_unique = true;
	workers_destroyed.clear();
	vector<int>::iterator it;

	for(int i=0; i<num_workers_to_destroy; i++){
		while(not_unique){ //Loop until a worker that is not already destroyed is found
			worker_to_destroy = rand() % 39 + 1; //Number between 1-39
			it = find(workers_destroyed.begin(), workers_destroyed.end(), worker_to_destroy); //Find int in vector
			if(it == workers_destroyed.end()){ //Searched the vector, value not found.
				workers_destroyed.push_back(worker_to_destroy);
				not_unique = false;
			}
			
		}
		cout << "Worker to destroy: " << worker_to_destroy << endl;
		cout << myworkers[worker_to_destroy-1].getQual() << endl;
		cout << myworkers[worker_to_destroy-1].getWeekend() << endl;
		cout << myworkers[worker_to_destroy-1].getHB() << endl;
		myworkers[worker_to_destroy-1].clear_blocks(); //Assign empty blocks to the worker
		//Remove values from lib_per_rot[w] and ass_per_rot[w] if not a LOW-worker (fixed weekends)
		if(worker_to_destroy != 14 && worker_to_destroy != 17 && worker_to_destroy != 25 && worker_to_destroy != 36 && worker_to_destroy != 37){
			if(myworkers[worker_to_destroy-1].getQual().compare(0,3,"lib") == 0 && myworkers[worker_to_destroy-1].getWeekend().compare(0,7,"weekend") == 0){
				lib_per_rot[myworkers[worker_to_destroy-1].getWeekend_week()]--;
			}else if(myworkers[worker_to_destroy-1].getQual().compare(0,3,"ass") == 0 && myworkers[worker_to_destroy-1].getWeekend().compare(0,7,"weekend") == 0){
				ass_per_rot[myworkers[worker_to_destroy-1].getWeekend_week()]--;
			}
		}
		not_unique = true;
	}
	
}

void Library::destroy(int worker){ //Destroy blocks for one single worker (and give new weekend, in repair?)
	int worker_to_destroy = worker;
	workers_destroyed.clear();
	workers_destroyed.push_back(worker_to_destroy);
	myworkers[worker_to_destroy-1].clear_blocks(); //Assign empty blocks to the worker
	
	//Remove values from lib_per_rot[w] and ass_per_rot[w] if not a LOW-worker (fixed weekends)
	if(worker_to_destroy != 14 && worker_to_destroy != 17 && worker_to_destroy != 25 && worker_to_destroy != 36 && worker_to_destroy != 37){
		if(myworkers[worker_to_destroy-1].getQual().compare(0,3,"lib") == 0 && myworkers[worker_to_destroy-1].getWeekend().compare(0,7,"weekend") == 0){
			lib_per_rot[myworkers[worker_to_destroy-1].getWeekend_week()]--;
		}else if(myworkers[worker_to_destroy-1].getQual().compare(0,3,"ass") == 0 && myworkers[worker_to_destroy-1].getWeekend().compare(0,7,"weekend") == 0){
			ass_per_rot[myworkers[worker_to_destroy-1].getWeekend_week()]--;
		}
	}
}

void Library::repair(){ //Repair solution by assigning a new week rotation(only if not LOW-worker) and then new blocks.
	int weektype_to_add = 0; //0 means "weekend", 1 means "weekrest" and 2 means "weekday"
	int weekday_to_add = 0; //a value between 1-3
	vector<int> block_types_added;
	vector<int> weekdays_added;
	vector<int>::iterator it;
	vector<int>::iterator it2;
	for(unsigned int n=0; n<workers_destroyed.size(); n++){//Selecting a worker 'n' to repair for
		//Check if not a LOW-worker (fixed weekends)
		cout << "before assign a rot to worker" << endl;
		if(workers_destroyed.at(n) != 14 && workers_destroyed.at(n) != 17 && workers_destroyed.at(n) != 25 && workers_destroyed.at(n) != 36 && workers_destroyed.at(n) != 37){
			//Assign rotation to the worker
			assign_a_rot_to_worker(workers_destroyed.at(n)); //a worker between 1-39
		}
		cout << "after assign a rot to worker" << endl;
		block_types_added.clear(); //clear vector with assigned block types
		weekdays_added.clear(); //clear vector with assigned weekday blocks
		//Repair blocks for the worker 'n' regardless if LOW-worker
		while(block_types_added.size() != 3){ //Loop until "weekend", "weekrest" and "weekday" blocks have been added
			while(true){ //Randomize a new unique block type to add
				weektype_to_add = rand() % 3;
				it2 = find(block_types_added.begin(), block_types_added.end(), weektype_to_add);
				if(it2 == block_types_added.end()){ //did not find value in vector
					break; //Breaks true-loop
				}
			}
			switch(weektype_to_add){
				case 0 :{ //add weekend
					add_best_blocks_to_worker("weekend",workers_destroyed.at(n));
					calculate_demand(); //Update demand after new insertion
					block_types_added.push_back(weektype_to_add);
					break;
				}
				case 1 :{ //add weekrest
					add_best_blocks_to_worker("weekrest",workers_destroyed.at(n));
					calculate_demand(); //Update demand after new insertion
					block_types_added.push_back(weektype_to_add);
					break;
				}
				case 2 :{ //add weekdays in a random order
					for(int k=0; k<3; k++){
						while(true){
							weekday_to_add = rand() % 3 + 1; //a value between 1-3
							it = find(weekdays_added.begin(), weekdays_added.end(), weekday_to_add);
							if(it == weekdays_added.end()){ //did not find value in vector
								add_best_blocks_to_worker("weekday",workers_destroyed.at(n),weekday_to_add);
								calculate_demand(); //Update demand after new insertion
								weekdays_added.push_back(weekday_to_add);
								break;
							}
						}
// 						add_best_blocks_to_worker("weekday",workers_destroyed.at(n),k+1); //If add in order!
// 						calculate_demand(); //Update demand after new insertion
					}
					block_types_added.push_back(weektype_to_add);
					break;
				}
			}
// 			cout << "block_types_added size is: " << block_types_added.size() << endl;
		}
	}
}

void Library::calculate_stand_ins(){ //calculate stand_in_amount each day. Save as int matrix. ADD TO: calculate_demand() ?
	for(int w=0; w<NUM_WEEKS; w++){
		for(int d=0; d<NUM_DAYS-2; d++){
			stand_in_amount[w][d] = 0;
		}
	}
	for(int i=1; i<=num_workers; i++){
		for(int w=0; w<NUM_WEEKS; w++){
			for(int d=0; d<NUM_DAYS-2; d++){
				if(myworkers[i-1].get_stand_in_avail(w,d) == 1 && myworkers[i-1].tasks_assigned_day(w,d) == 0){
					stand_in_amount[w][d]++;
				}
			}
		}
	}
}

void Library::print_stand_ins(){
	calculate_stand_ins();
	cout << "Number of stand-ins are for each day of the week:\n" << endl;
	for(int w=0; w<NUM_WEEKS; w++){
		cout << "Week " << w << endl;
		for(int d=0; d<NUM_DAYS-2; d++){
			cout << stand_in_amount[w][d] << " ";
		}
		cout << endl << endl;
	}
}



