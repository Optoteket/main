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
			case 1 :{ //1 = Exp
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
			case 2:{ //2 = Info
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

//change output to vector<Block>?
//Copy constructor needed here??
void Library::createBlockpool(){
	int b_ID = 1;
	vector<int> existing_combs_on_days;
	int combs = 0;
	block_vector.clear();
	//vector<int> days_assigned;
	//num_tasks should be from 0 to 5. 0 to 7 if weekends are included. PROBLEM: when tasks == 0.
	for(int tasks = 2; tasks<=2; tasks++){ //combs any nr of [1 45 810 7290 32805 59049]
		//Need to reset vectors here?
		combs = get_all_day_combinations(tasks, NUM_DAYS-2); //Only looking at 5 days!
		cout << "Number of combinations for " << tasks << " tasks are: " << combs << endl;
		existing_combs_on_days.push_back(combs); //save in vector
		if(tasks != 0){
			task_array3D.resize(combs); //Set number of rows in 3D array
			for (int i = 0; i < combs; ++i) {
				task_array3D[i].resize(tasks); //Set number of rows in 2D sub-array
				for (int j = 0; j < tasks; ++j){
					task_array3D[i][j].resize(3); //Set number of columns in 2D sub-array = [d s j]
				}
			}
			assign_task_array3D(combs, tasks);
		}
		//Create combs number of block objects
		int col1 = 0, col2 = 0, col3 = 0;
		for(int x=0; x<combs; x++){
			//Create class
			Block block(b_ID); //Create block nr: b_ID. Note: destroys after the for-loop. Add to vector existing in Library: private?
			for(int row=0; row<tasks; row++){
				col1 = task_array3D[x][row][0];
				col2 = task_array3D[x][row][1];
				col3 = task_array3D[x][row][2];
				block.setTask(col1, col2, col3, 1);
			}
			block.setnum_tasks(tasks);
			b_ID++;
			
			//Assign task combination
// 			assign_unique_task_combination(block);
			block_vector.push_back(block);
		}
	}
	//Print the vector
	cout << "existing_combs_on_days = [ ";
	for(unsigned int i=0; i<existing_combs_on_days.size(); i++){
		cout << existing_combs_on_days[i] << " ";
	}
	cout << "]" << endl;
	setNum_blocks(b_ID-1); //Set num_blocks in library class to the number of blocks created
	cout << "#Blocks created: " << getNum_blocks() << endl;
	cout << "Size of block_vector in Library.cpp is: " << block_vector.size() << endl;
	return;
}

void Library::assign_task_array3D(int combs, int tasks){
	int combinations_created = 0;
	vector<int> one_day_comb_vect;
	int day_combs; //Number of combinations possible with 'tasks' days e.g. [1 2 3], [1 2 4] etc if tasks==3
	day_combs = num_day_combinations_array[tasks];
	cout << "Day combinations are: " << day_combs << endl;
	for (int n=0; n<day_combs; n++){ //n<day_combs task_array3D should be combs long
		get_day_comb_nr(tasks, n); //Assign 'combination_nr' for combination number 'n'
		one_day_comb_vect = combination_nr; //example: [1 2 3]
		cout << "one_day_comb_vect size is: " << one_day_comb_vect.size() << endl;
		cout << "one_day_comb_vect contains: ";
		for(unsigned int i=0; i<one_day_comb_vect.size(); i++){
			cout << one_day_comb_vect[i] << " ";
		}
		cout << endl;
// 		for(int m=1; m<=calculate_combinations(one_day_comb_vect); m++){
		assign_all_combinations(0,tasks); //Each function call shall produce 81 assignments (when tasks==2)
// 			for(int s=1; s<=NUM_SHIFTS; s++){
// 				for(int j=0; j<1; j++){ //Only 'Exp'
// 					for(int d=0; d<tasks; d++){
// 						if(task_assign_avail[one_day_comb_vect[d]-1][s-1][j] == 1){
// 							for(int x=0; x<3; x++){
// 								switch(x){
// 									case 0:
// 										task_array3D[m+m*n-1][d][x] = one_day_comb_vect[d]; //task_array3D[combs][d][x]
// 										cout << "Assigning task_array3D[element=" << m+m*n-1 << "][row=" << d << "][x=" << x << "] = " << one_day_comb_vect[d] << " (day)" << endl;
// 										break;
// 									case 1:
// 										task_array3D[m+m*n-1][d][x] = s;
// 										cout << "Assigning task_array3D[element=" << m+m*n-1 << "][row=" << d << "][x=" << x << "] = " << s << " (shift)" << endl;
// 										break;
// 									case 2:
// 										task_array3D[m+m*n-1][d][x] = j;
// 										cout << "Assigning task_array3D[element=" << m+m*n-1 << "][row=" << d << "][x=" << x << "] = " << j << " (task type, 0 = 'Exp', 1 = 'Info)\n" << endl;
// 										break;
// 								}
// 							}
// 						}
// 					}
// 					//combinations_created++;
// 				}
// 			}
// 		}
	}
	cout << "***Combinations created are: " << combinations_created << " ***" << endl;
}

void Library::assign_all_combinations(int tasks_num, vector<int> one_day_comb_vect, int current_day){ //tasks_num decides number of recursive calls
	global_iteration_counter++;
	rec_count++;
	//Assign a task that day
	for(int s=1; s<=2; s++){
		for(int j=0; j<2; j++){ //Only 'Exp' and 'Info'
			if(task_assign_avail[one_day_comb_vect[current_day]-1][s-1][j] == 1){
				for(x=0; x<3; x++){
					switch(x){
						case 0:
							task_vect[rec_count-1][current_day][0][x] = one_day_comb_vect[current_day];
							break;
						case 1:
							task_vect[rec_count-1][current_day][0][x] = s;
							break;
						case 2:
							task_vect[rec_count-1][current_day][0][x] = j;
							break;
					}
				}
			}
		}
	}
	
	//if tasks_num is 1, then first iteration has already been made
	if(tasks_num == 1){
		assign_the_3D_array(); //using pushbacks on int vectors
		return;
	}
	
	//Call again for next day until tasks_num == 1
	for(int n=1; n<=tasks_num-1; n++){//Number of times calling recursively
		assign_all_combinations(tasks_num-1, one_day_comb_vect, day+1);
	}
	
	
	
}

// for(int d=0; d<tasks; d++){
// 	if(task_assign_avail[one_day_comb_vect[d]-1][s-1][j] == 1){
// 		for(int x=0; x<3; x++){
// 			switch(x){
// 				case 0:
// 					task_array3D[m+m*n-1][d][x] = one_day_comb_vect[d]; //task_array3D[combs][d][x]
// 					cout << "Assigning task_array3D[element=" << m+m*n-1 << "][row=" << d << "][x=" << x << "] = " << one_day_comb_vect[d] << " (day)" << endl;
// 					break;
// 				case 1:
// 					task_array3D[m+m*n-1][d][x] = s;
// 					cout << "Assigning task_array3D[element=" << m+m*n-1 << "][row=" << d << "][x=" << x << "] = " << s << " (shift)" << endl;
// 					break;
// 				case 2:
// 					task_array3D[m+m*n-1][d][x] = j;
// 					cout << "Assigning task_array3D[element=" << m+m*n-1 << "][row=" << d << "][x=" << x << "] = " << j << " (task type, 0 = 'Exp', 1 = 'Info)\n" << endl;
// 					break;
// 			}
// 		}
// 	}
// }
// //combinations_created++;

//function to assign 'combination_nr' in the class Library
void Library::get_day_comb_nr(int tasks, int num_comb){ //tasks == 0 gives empty vector
	days.clear();
	cout << "num_comb to find: " << num_comb << endl;
	combination.clear();
	int k = tasks;
	times_in_fcn = 0;
	for(int i=0; i<NUM_DAYS-2; ++i){ //doing this for 5 days not 7
		days.push_back(i+1);
	}
	create_combinations_as_vect(0,k,num_comb);
	return;
}

void Library::create_combinations_as_vect(int offset, int k, int num_comb){ //k=tasks
	if (k == 0){
		cout << "combination contains here: ";
		for(unsigned int j=0; j<combination.size(); j++){
			cout << combination[j] << " ";
		}
		cout << endl;
		cout << "num_comb = " << num_comb << " times_in_fcn = " << times_in_fcn << endl;
		//in here after each combination has been created?
		if(num_comb == times_in_fcn){
			combination_nr = combination;
		}
		times_in_fcn++;
		return;
	}
	for (unsigned int i = offset; i <= days.size() - k; ++i) {
		combination.push_back(days[i]);
		create_combinations_as_vect(i+1, k-1, num_comb);
		combination.pop_back();
	}
}





//Creates vectors containing combinations of days
int Library::get_all_day_combinations(int num_tasks_to_assign, int num_days){
	//reset the 'private' variable when function call
	num_combinations_total = 0;
	num_day_combinations = 0;
	days.clear();
	combination.clear();
	//int day_vector[num_tasks_to_assign]; //[d1=0, d2=0, ...]
	if(num_tasks_to_assign == 0){
		num_combinations_total = 1;
		num_day_combinations_array[0] = 1;
		//cout << "The total number of combinations are here: " << num_combinations_total << endl; 
		return num_combinations_total;
	}
	else{
		int k = num_tasks_to_assign;
		for(int i=0; i<num_days; ++i){
			days.push_back(i+1);
		}
		create_combinations(0,k);
		//cout << "The total number of combinations are here: " << num_combinations_total << endl;
// 		num_day_combinations = combination.size(); //?
// 		cout << "num_day_combinations are here: " << num_day_combinations << endl;
		num_day_combinations_array[num_tasks_to_assign] = num_day_combinations;
		return num_combinations_total;
	}
}

void Library::create_combinations(int offset, int k){ //k=num_tasks_to_assign
	if (k == 0){
		//in here after each combination has been created
		num_day_combinations++;
		num_combinations_total += calculate_combinations(combination); //num_combinations_total private in Lib. Does this one update?
		print_comb_vector(combination);
		cout << "number of day combinations are: " << num_day_combinations << endl;
		cout << "number of combinations in total are: " << num_combinations_total << endl;
		return;
	}
	for (unsigned int i = offset; i <= days.size() - k; ++i) {
		combination.push_back(days[i]);
		create_combinations(i+1, k-1);
		combination.pop_back();
	}
}

void Library::print_comb_vector(const vector<int>& v) {
  static int count = 0;
  cout << "combination no " << (++count) << ": [ ";
  for (unsigned int i = 0; i < v.size(); ++i) { cout << v[i] << " "; }
  cout << "] " << endl;
}

int Library::calculate_combinations(const vector<int>& vect){ //Calculates number of combinations for a vector of days e.g. [1 2 3]
	int days_in_vector;
	vector<int> daily_avail_vect;
	int avail_day_num = 0;
	int num_combinations = 0;
	days_in_vector = vect.size();
	//cout << "Number of days in vector are: " << days_in_vector << endl;
	for(int d=0; d<days_in_vector; d++){
		avail_day_num = 0;
		for(int s=0; s<NUM_SHIFTS; s++){
			for(int j=0; j<3; j++){
				if(task_assign_avail[d][s][j] == 1){ //Only assign if avail. j = 0,1,2 (exp,info,pl)
					avail_day_num++;
					//cout << "avail_day_num = " << avail_day_num << endl;
				}
			}
		}
		daily_avail_vect.push_back(avail_day_num);
	}
	unsigned int loop_iteration_number = daily_avail_vect.size();
	//cout << "daily_avail_vect has: " << loop_iteration_number << " elements" << endl;
	//Calculate the number of combinations
	for(unsigned int i=0; i<loop_iteration_number; i++){
		if(i==0){
			num_combinations = daily_avail_vect.back();
			daily_avail_vect.pop_back();
		}
		else{
			num_combinations = num_combinations*daily_avail_vect.back();
			daily_avail_vect.pop_back();
		}
	}
	cout << "Number of combinations of a combination vector are: " << num_combinations << endl;
	return num_combinations;
}




bool Library::is_day_blocked(vector<int> blocked_vector, int day){ //Return true if day is blocked
	int day_to_check = 0;
	for(unsigned int i=0; i<blocked_vector.size(); i++){
		day_to_check = blocked_vector.back();
		blocked_vector.pop_back();
		if(day == day_to_check){
			return true;
		}
	}
	return false;
}

int Library::getNum_blocks() const{
	return num_blocks;
}

int Library::getNum_day_combinations() const{
	return num_day_combinations;
}


void Library::setNum_blocks(int num) {
	num_blocks = num;
}

void Library::setNum_day_combinations(int num) {
	num_day_combinations = num;
}
vector<Block> Library::get_block_vector(){
	return block_vector;
}
