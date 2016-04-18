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

Library::Library() {
	num_day_combinations = 0;
	num_combinations_total = 0;
	num_blocks = 0;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				for (int j=0; j<NUM_TASKS; j++){
					demand[w][d][s][j] = 0; //
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

void Library::setDemand(int week, int day, int shift, int task, int amount) { //Exp: task = 1, Info: task = 2 etc
	if (week == 1)
	{
		demand[week-1][day-1][shift-1][task] = amount;
		demand[week+1][day-1][shift-1][task] = amount;
		demand[week+3][day-1][shift-1][task] = amount;
	}
	else if(week == 2)
	{
		demand[week-1][day-1][shift-1][task] = amount;
		demand[week+1][day-1][shift-1][task] = amount;
	}
	else{
		cerr << "Error in inserting weeks in demand. Only week = 1 or week = 2 allowed" << endl;
	}
}
void Library::setDemand(int week, int day, int shift, string task, int amount) {
	task_type task_enum;
	if(task == "Exp"){
		task_enum = Exp;
	}
	else if (task == "Info"){
		task_enum = Info;
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
		demand[week-1][day-1][shift-1][task_enum] = amount;
		demand[week+1][day-1][shift-1][task_enum] = amount;
		demand[week+3][day-1][shift-1][task_enum] = amount;
	}
	else if(week == 2)
	{
		demand[week-1][day-1][shift-1][task_enum] = amount;
		demand[week+1][day-1][shift-1][task_enum] = amount;
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
	cout << "The big columns represent: Exp, Info, PL, HB, BokB" << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int t=0; t<NUM_TASKS; t++){
				for (int d=0; d< NUM_DAYS; d++){
					cout << demand[w][d][s][t] << " ";
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
	int ID, num_workers = 39;
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
		myworkers[i] = aworker;
	}
	setAvail_worker(myworkers);
}


//Assigns avail for all workers
void Library::setAvail_worker(Worker myworkers[39]) {
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
// 	int number_of_workers_in_total = 39;
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
			//cout << wID << endl;
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
			//cout << "Trying to type in: " << week << " " << day << " " << shift << " " << AVAIL << endl;
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
	cout << "The matrices represent task assignment availability for: Exp, Info, PL, HB, BokB" << endl;
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

Worker Library::getWorker(int i) const{
	return myworkers[i-1];
}

void Library::create_all_blocks() {
	int num_shifts[NUM_SHIFTS]; //Only for weekdays
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
																					Block a_block(num_blocks_to_create+1); //Create the object with ID
																					assign_tasks_to_block(a_block, s1, j1, s2, j2, s3, j3, s4, j4, s5, j5, j6, j7);
																					block_vector.push_back(a_block);
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

//need to send in a pointer Block* ?
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
	block.setnum_tasks(num_of_blocks+num_of_PL);
	block.setnum_Blocks(num_of_blocks);
	block.setnum_PL(num_of_PL);
	//Weekend assigned?
	if(j6 != 0){block.setWeektype("weekend");}
	//HB assigned?
	if(j6 == 2){block.setnum_HB(1);}
}

void Library::assign_blocks_to_workers(){
	
}


int Library::getNum_blocks() const{
	return num_blocks;
}


void Library::setNum_blocks(int num) {
	num_blocks = num;
}

vector<Block> Library::get_block_vector(){
	return block_vector;
}
