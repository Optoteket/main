#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include "Workers.h"
#include "Blocks.h"
#include "Library.h"
using namespace std;
void setAvail_worker(Worker[39]);

int main() {
	//create a list of worker objects. myworkers[0], myworkers[1] etc.
	Worker myworkers[39];
	setAvail_worker(myworkers);
	Worker aworker(1, "Ben", "not_boss", "lib", "Child", "Normal_PL", "No_weekends", "HB", "No");
	cout << aworker.getName() << endl;
	cout << myworkers[0].getName() << endl;
	myworkers[0].setName("Kent");
	cout << myworkers[0].getName() << endl;
	myworkers[0] = aworker;
	cout << myworkers[0].getName() << " ID is: " << myworkers[0].getID() << endl;
//	myworkers[0] = 
	Library lib;
	lib.createWorkers();
//	lib.printDemand();
//	vector<string> All_Info;
//  	All_Info = get_info_vector(4); //1 = Qualifications, 2 = ID, 3 = Name, 4 = Department, 5 = Weekends, 6 = Boss?, 7 = PL, 8 = HB, 9 = free_day?
// 	cout << "The last information in the vector is: " << All_Info.back() << endl;
	
	//Block myblocks[3];
	//myblocks[1].getTask_matrix();
   	//myworkers[38].getAvail_matrix();

	return 0;
}

//Assigns avail for all workers
void setAvail_worker(Worker myworkers[39]) {
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
		if(line_read_num == 6+152*workers_counted)
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


