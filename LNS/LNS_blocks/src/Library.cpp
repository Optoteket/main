#include "Library.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>

Library::Library() {
	for (int w=0; w< NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				for (int t=0; t<NUM_TASKS; t++){
					demand[w][d][s][t] = 0;
				}
			}
		}
	}
	readDemand();
	//createWorkers(39);
	
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

vector <string> Library::get_info_vector(int info_type) { //1 = ID, 2 = Name, 3 = Boss, 4 = Qual, 5 = Dep, 6 = PL, 7 = Weekend, 8 = HB, 9 = free_day
	ifstream inFile("./src/data/workers5W.txt");
	string wInfo;
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
		//Read until a line
		getline( inFile, readline);
		line_read_num++; //the line read is number: line_read_num
		//cout << "info_type is: " << info_type << endl;
		switch (info_type)
		{
			case 1: //ID
			{
				if(line_read_num == 6+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 2: //Name
			{
				if(line_read_num == 7+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 3: //Boss
			{
				if(line_read_num == 10+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 4: //Qualifications
			{
				if(line_read_num == 5+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 5: //Department
			{
				if(line_read_num == 8+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 6: //PL_amount
			{
				if(line_read_num == 11+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 7: //Weekend
			{
				if(line_read_num == 9+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 8: //HB
			{
				if(line_read_num == 12+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 9: //Free_day
			{
				if(line_read_num == 13+152*workers_counted)
				{
					//Assign the Info of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
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
	vector <string> ID_vector;
	vector <string> name_vector;
	vector <string> boss_vector;
	vector <string> qual_vector;
	vector <string> dep_vector;
	vector <string> pl_vector;
	vector <string> weekend_vector;
	vector <string> hb_vector;
	vector <string> freeday_vector;
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	ID_vector = get_info_vector(1);
	
	//cout << info_vector.back() << endl;
}