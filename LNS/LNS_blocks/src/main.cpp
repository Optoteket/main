#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include "Workers.h"
using namespace std;

//Assigns avail for all workers
void setAvail() {
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
	//int wID = 0;
	string wID;
	int line_read_num = 0;
	int workers_counted = 0;
// 	int number_of_workers_in_total = 39;
// 	int week, day, shift;
	while( inFile.good() )
	{
		//Read until an "=" is found and assign all availability
		getline( inFile, readline);
		line_read_num++; //the line read is number: line_read_num
		input_vector.clear(); //input_vector contains the integers "week" "day" "shift" read from a line
		if(line_read_num == 6+152*workers_counted)
		{
			//Assign the ID of the worker that is being read
			//wID = stoi(readline,nullptr);
			wID = readline;
			cout << wID << endl;
		}
		
		
		size_t found = readline.find("="); //Find the character with an "="
		size_t pos = readline.find (",");
		if(found != string::npos) //separate a readline if containing an "="
		{
			
			integer_string = readline.substr(0,found-1); //getting the string "1,1,1"
			avail_string = readline.substr(found+2); //getting the avail number as strings
			//cout << "the integer string is:" << integer_string << endl;
			//separate all three integers in integer_string into input_vector
			while(pos != string::npos)
			{
				input_vector.push_back(integer_string.substr(0,pos)); //adds everything that appears before the first ","
				//cout << "The integer added to the vector is:" << integer_string.substr(0,pos) << endl;
				integer_string = integer_string.substr(pos+1); //Everything after the "," is in the new integer_string
				//cout << integer_string << endl;
				pos = integer_string.find(","); //Find the position of the next "," in the new readline
			}
			//Add the last integer (as string) to input_vector
			input_vector.push_back(integer_string.substr(0,pos));
			//cout << "The integer added to the vector is:" << integer_string.substr(0,pos) << endl;
			
// 				shift = stoi(input_vector.back(),nullptr);
// 				input_vector.pop_back();
// 				day = stoi(input_vector.back(),nullptr);
// 				input_vector.pop_back();
// 				week = stoi(input_vector.back(),nullptr);
// 				input_vector.pop_back();
			
			//Assign the availability to the workers 
			//worker_list[wID].worker_avail[week][day][shift] = stoi(avail_string,nullptr);
			
		}
		size_t found_new_worker = readline.find ("avail:");
		if(found_new_worker != string::npos) //A line is read containing "avail:"
		{
			workers_counted++;
		}
		
		
	}
}

int main() {
	//create a list of worker objects. worker_list[1], worker_list[2] etc.
	//Worker worker;
	setAvail();
	return 0;
}

