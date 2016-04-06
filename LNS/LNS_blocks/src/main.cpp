#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include "Workers.h"
using namespace std;
void setAvail_worker(Worker*);
vector <string> get_info_vector(int);

int main() {
	//create a list of worker objects. worker_list[1], worker_list[2] etc.
	Worker myworkers[40];
	setAvail_worker(myworkers);
	vector<string> All_Info;
 	All_Info = get_info_vector(4); //1 = Qualifications, 2 = ID, 3 = Name, 4 = Department, 5 = Weekends, 6 = Boss?, 7 = PL, 8 = HB, 9 = free_day?
	cout << "The last information in the vector is: " << All_Info.back() << endl;
//   	myworkers[39].setAvail(1,0,2,4);
//  	myworkers[39].setAvail(0,0,0,1);
//  	myworkers[39].setAvail(2,2,1,2);
// 	int avail = myworkers[1].getAvail(1,1,1);
//   	myworkers[38].getAvail_matrix();
// 	cout << "Next availability matrix" << endl;
 	myworkers[39].getAvail_matrix();

 	//myworkers[38].getAvail_matrix();
	return 0;
}

//Assigns avail for all workers
void setAvail_worker(Worker* myworkers) {
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
			cout << wID << endl;
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
// 			if (wID == 39)
// 			{
				cout << "Trying to type in: " << week << " " << day << " " << shift << " " << AVAIL << endl;
 				//if (week >= 1 && day == 4 && shift == 3){
				myworkers[wID].setAvail(week-1, day-1, shift-1, AVAIL);
				//myworkers[wID].setAvail(week-1,day-1,shift-1,AVAIL);
 				//}
// 			}
		}
	}
}


vector <string> get_info_vector(int info_type) { //1 = Qualifications, 2 = ID, 3 = Name, 4 = Department, 5 = Weekends, 6 = Boss?, 7 = PL, 8 = HB, 9 = free_day?
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
			case 1: //Qualifications
			{
				if(line_read_num == 5+152*workers_counted)
				{
					//Assign the Info = Qualifications of the worker that is being read
					wInfo = readline;
					cout << wInfo << endl;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 2: //ID
			{
				if(line_read_num == 6+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					cout << wInfo << endl;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 3: //Name
			{
				if(line_read_num == 7+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 4: //Department
			{
				if(line_read_num == 8+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 5: //Weekends
			{
				if(line_read_num == 9+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 6: //Boss?
			{
				if(line_read_num == 10+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 7: //PL_amount
			{
				if(line_read_num == 11+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 8: //HB
			{
				if(line_read_num == 12+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
					wInfo = readline;
					input_vector.push_back(wInfo);
				}
			}
			break;
			case 9: //Free_day?
			{
				if(line_read_num == 13+152*workers_counted)
				{
					//Assign the Info = ID of the worker that is being read
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

