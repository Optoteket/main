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
#include <cstdlib>

Library::Library() {
	num_blocks = 0;
	num_workers = 39;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				for (int j=0; j<NUM_TASKS; j++){
					demand[w][d][s][j] = 0; //initialize as 0
					demand_differ[w][d][s][j] = 0; //initialize as 0
					tasks_filled[w][d][s][j] = 0;
				}
			}
		}
	}
	readDemand();
	//createWorkers();
	for (int d=0; d<NUM_DAYS; d++){
		for (int s=0; s<NUM_SHIFTS; s++){
			for (int j=0; j<NUM_TASKS; j++){
				task_assign_avail[d][s][j] = 0; //Used to see if task j is available for assignment day d, shift s
			}
		}
	}
	setTask_avail();
	//printTask_avail();

}


Library::~Library() {
	
}

int Library::getDemand(int week, int day, int shift, int task) const{
	return demand[week-1][day-1][shift-1][task-1];
}

void Library::setDemand(int week, int day, int shift, int task, int amount) { //Block: task = 1, PL: task = 2, HB: task = 3, BoKB: task = 4
	if (week == 1)
	{
		demand[week-1][day-1][shift-1][task] += amount;
		demand[week+1][day-1][shift-1][task] += amount;
		demand[week+3][day-1][shift-1][task] += amount;
	}
	else if(week == 2)
	{
		demand[week-1][day-1][shift-1][task] += amount;
		demand[week+1][day-1][shift-1][task] += amount;
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
		demand[week-1][day-1][shift-1][task_enum] += amount;
		demand[week+1][day-1][shift-1][task_enum] += amount;
		demand[week+3][day-1][shift-1][task_enum] += amount;
	}
	else if(week == 2)
	{
		demand[week-1][day-1][shift-1][task_enum] += amount;
		demand[week+1][day-1][shift-1][task_enum] += amount;
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
			cout << "For w,d,s,j the demand is: " << week << " " << day << " " << shift << " " << task << " = " << demand_string << endl;
		}
	}
}

void Library::printDemand() {
	cout << "The big columns represent demand for: block (Exp+Info), PL, HB, BokB" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int j=1; j<NUM_TASKS; j++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << demand[w][d][s][j] << " ";
				}
				cout << "\t";
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
	int num_shifts[NUM_SHIFTS]; //Only for weekdays
	for(int i=0; i<NUM_SHIFTS; i++){
		num_shifts[i] = 0;
	}
	int num_blocks_to_create = 0;
	int sum_PL = 0, sum_evenings = 0, shift_flag = 0;
	int blocks = 0;
	//int s[NUM_DAYS];
	for(int s1=1; s1<=NUM_SHIFTS; s1++){
		for(int j1=0; j1<3; j1++){
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

void Library::assign_blocks_to_workers(){ //using Worker myworkers[39], vector<Block> block_vector. Need a copy of block_vector so it isnt ruined for each worker
	cout << "here " << block_vector.size() << endl;
	for(int i=0; i<num_workers; i++){
		for(unsigned int n = 0; n<block_vector.size(); n++){
			assign_block(&block_vector.at(n), i+1);
		}
		cout << "Worker: " << i+1 << " has " << myworkers[i].getweekend_vect().size() << " " << myworkers[i].getweekday_vect().size() << " " << myworkers[i].getweekrest_vect().size() << " in sizes" << endl;
	}
	
}

void Library::assign_block(Block* block, int worker_id){ //worker_id a number between 1 to 39
// 	cout << "The number of tasks the block has is: " << block.getnum_tasks() << endl;
	int is_lib = 0;
	int w_check_error[3]; //0 for week w if no errors are found
	for (int w=0; w<3; w++){w_check_error[w] = 0;}
	if(myworkers[worker_id-1].getQual().compare(0,3,"lib") == 0){
		is_lib = 1;
	}
	else{is_lib = 0;}
// 	cout << "getAvail is: " << myworkers[worker_id-1].getAvail(0,0,3) << " getTask is: " << block.getTask(0,3,1) << endl;
	for (int w=0; w<3; w++){ //Check for weekend week, weekday week and week_rest week (w=0,1,2)
		w_check_error[w] = 0; //Reset when looking at a new week
		for (int d=0; d< NUM_DAYS; d++){
			for (int s=0; s< NUM_SHIFTS; s++){
				if(w == 0 && myworkers[worker_id-1].getWeekend().compare(0,7,"weekend") == 0 && (d == 5 || d == 6) && s == 0){ //weekend worker on a weekend
					if(block->getTask(d,s,1) == 0 && block->getTask(d,s,3) == 0){ //if wend worker and no weekend assigned to the block
// 						cout << "Found error: 0 for week: " << w << endl;
						w_check_error[w] = 1;
					}
				}else if(w == 0 && week_empty_of_tasks(block)){w_check_error[w] = 0;}
				for (int j=1; j<=3; j++){ //Only checking for Block, PL and HB
					if(j == 1){ //Block
						if(myworkers[worker_id-1].getAvail(w,d,s) < block->getTask(d,s,j)){
// 							cout << "Found error: 1 for week: " << w << endl;
							w_check_error[w] = 1;
						}
					}
					else if(j == 2){ //PL
						if(block->getTask(d,s,j) == 1){ //A PL is assigned to block
							//check the three consecutive shifts, s = 1, 2, 3
							if(!(myworkers[worker_id-1].getAvail(w,d,s) == 1 && myworkers[worker_id-1].getAvail(w,d,s+1) == 1 && getWorker(worker_id).getAvail(w,d,s+2) == 1)){
// 								cout << "Found error: 2 for week: " << w << endl;
								w_check_error[w] = 1;
							}
						}
					}
					else if(j == 3){ //HB
						if((d == 5 || d == 6) && s == 0){ //HB only occuring on weekends at shift 0. ('optimizing' code)
							if(block->getTask(d,s,j) == 1 && is_lib == 0){
// 								cout << "Found error: 3 for week: " << w << endl;
								w_check_error[w] = 1; //Error for all weeks, due to being "ass"
							}
							else if(myworkers[worker_id-1].getAvail(w,d,s) < block->getTask(d,s,j)){
// 								cout << "Found error: 4 for week: " << w << endl;
								w_check_error[w] = 1;
							}
						}
					}
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
// 				myworkers[worker_id-1].getweekday_vect().push_back(block);
				myworkers[worker_id-1].add_block_avail("weekday",block); //block is a pointer here
// 				cout << "Pushing back a weekday block!!!" << endl;
// 				cout << "Size is now: " << myworkers[worker_id-1].getweekday_vect().size() << endl;
			} else if(w == 2){
// 				myworkers[worker_id-1].getweekrest_vect().push_back(block);
				myworkers[worker_id-1].add_block_avail("weekrest",block); //block is a pointer here
// 				cout << "Pushing back a weekrest block!!!" << endl;
// 				cout << "Size is now: " << myworkers[worker_id-1].getweekrest_vect().size() << endl;
			}
		}
	}
// 	cout << "Worker: " << worker_id << " has " << myworkers[worker_id-1].getweekend_vect().size() << " " << myworkers[worker_id-1].getweekday_vect().size() << " " << myworkers[worker_id-1].getweekrest_vect().size() << " in sizes" << endl;
	return; //Block has been assigned to the available vectors for the worker
}

void Library::print_weekblocks_avail_worker(int worker_id, string str){
	if(str == "weekend"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getweekend_vect().size(); n++){
			myworkers[worker_id-1].getweekend_vect().at(n)->getTask_matrix();
		}
	} else if(str == "weekday"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getweekday_vect().size(); n++){
			myworkers[worker_id-1].getweekday_vect().at(n)->getTask_matrix();
		}
	} else if(str == "weekrest"){
		for(unsigned int n=0; n<myworkers[worker_id-1].getweekrest_vect().size(); n++){
			myworkers[worker_id-1].getweekrest_vect().at(n)->getTask_matrix();
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
			cout << "Weekend block:" << endl;
			myworkers[worker_id-1].getblocks_assigned().at(weekend_week)->getTask_matrix();
		}
	} else if(str == "weekrest"){
		if(myworkers[worker_id-1].getblocks_assigned().size() == 5){
			cout << "Weekrest block:" << endl;
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+1) % 5)->getTask_matrix();
		}
	} else if(str == "weekday"){
		if(myworkers[worker_id-1].getblocks_assigned().size() == 5){
			cout << "Weekday blocks:" << endl;
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+2) % 5)->getTask_matrix(); //first weekday
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+3) % 5)->getTask_matrix(); //second weekday
			myworkers[worker_id-1].getblocks_assigned().at((weekend_week+4) % 5)->getTask_matrix(); //third weekday
		}
	} else{
		cerr << "Not a valid string as inargument" << endl;
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
	int workers_per_rot[5];
	for(int w=0; w<NUM_WEEKS; w++){workers_per_rot[w] = 0;} //initialize as 0
	int min_worker_per_rot = 0;
	int rand_week = 0;
	int temp_min = 0;
	for(int i=1; i<=num_workers; i++){
		while(true){
			rand_week = rand() % 5; //generates a random number between 0 to 4
			if(workers_per_rot[rand_week] == min_worker_per_rot){
				myworkers[i-1].setWeekend_week(rand_week);
				if(myworkers[i-1].getWeekend().compare(0,7,"weekend") == 0){ //Only count if a weekend worker
					workers_per_rot[rand_week]++;
				}
				temp_min = workers_per_rot[0];
				for(int w=1; w<NUM_WEEKS; w++){ //Update min_worker_per_rot
					if(workers_per_rot[w] < temp_min){
						temp_min = workers_per_rot[w];
					}
				}
				min_worker_per_rot = temp_min;
				break;
			}
		}
		
	}
	cout << "workers_per_rot = ";
	for(int w=0; w<NUM_WEEKS; w++){
		cout << workers_per_rot[w] << " ";
	}
	cout << endl;
	return;
}

void Library::calculate_tasks_filled(){ //Calculate which tasks has been assigned to workers for specific weeks
	for(int i=0; i<num_workers; i++){ //element should represent week when assigned 5 elements
		for(unsigned int element=0; element<myworkers[i].getblocks_assigned().size(); element++){
			for(int d=0; d<NUM_DAYS; d++){
				for(int s=0; s<NUM_SHIFTS; s++){
					for(int j=0; j<NUM_TASKS; j++){
						tasks_filled[element][d][s][j] += myworkers[i].getblocks_assigned().at(element)->getTask(d,s,j);
					}
				}
			}
		}
	}
}

void Library::print_tasks_filled(){
	cout << "These matrices represent the all tasks with the filled worker amount at: No task, block, PL, HB" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int j=0; j<NUM_TASKS; j++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << tasks_filled[w][d][s][j] << " ";
				}
				cout << "\t";
			}
			cout << endl;
		}
		cout << endl << endl;
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
				for(int j=1; j<NUM_TASKS; j++){
					demand_differ[w][d][s][j] = demand[w][d][s][j] - tasks_filled[w][d][s][j];
				}
			}
		}
	}
}

void Library::print_demand_differ(){
	cout << "Represenation of demand difference in the library for: No task, block, PL, HB" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int j=1; j<NUM_TASKS; j++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << demand_differ[w][d][s][j] << " ";
				}
				cout << "\t";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}





