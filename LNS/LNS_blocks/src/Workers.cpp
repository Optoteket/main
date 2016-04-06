#include "Workers.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>

Worker::Worker() {
	newID = 0;
	newName = " ";
	newBoss = " ";
	newQual = " ";
	newDep = " ";
	newPL = " ";
}

Worker::Worker(int id, string name, string boss, string qualification, string department, string pl) {
	newID = id;
	newName = name;
	newBoss = boss;
	newQual = qualification;
	newDep = department;
	newPL = pl;
}

Worker::~Worker() {
	
}

int Worker::getID() const{
	return newID;
}
string Worker::getName() const{
	return newName;
}
string Worker::getBoss() const{
	return newBoss;
}
string Worker::getQual() const{
	return newQual;
}
string Worker::getDep() const{
	return newDep;
}
string Worker::getPL() const{ //Enumerate??
	return newPL;
}

// int Worker::getAvail(int week, int day, int shift) const{
// 	ifstream inFile("./src/data/librarystaff5W.txt");
// 	//Checking for open Error
// 	if (inFile.fail()) {
// 		cerr << "Error opening the file!" << endl;
// 		exit(1);
// 	}
// 
// 	int avail;
// 	
// 	string readline;
// 	string integer_string;
// 	string avail_string;
// 	string first_integer_as_string;
// 	string second_integer_as_string;
// 	string third_integer_as_string;
// 	while( inFile.good() )
// 	{
// 		getline( inFile, readline);
// 		size_t found = readline.find("=");
// 		size_t pos = readline.find(",");
// 		if(found != string::npos)
// 		{
// 			//while (pos != string::npos){
// 			integer_string = readline.substr(0,found-1); //getting the string "1,1,1"
// 			avail_string = readline.substr(found+1); //avail_string = "1" or "0"
// 			if(pos != string::npos)
// 			{
// 				first_integer_as_string = integer_string.substr(0,pos);
// 				second_integer_as_string = integer_string.substr(pos
// 			}
// 		}
// 	}
// }

void Worker::setID(int id) {
	newID = id;
}
void Worker::setName(string name) {
	newName = name;
}
void Worker::setBoss(string boss) {
	newBoss = boss;
}
void Worker::setQual(string qual) {
	newQual = qual;
}
void Worker::setDep(string dep) {
	newDep = dep;
}
void Worker::setPL(string pl) {
	newPL = pl;
}

// void Worker::setAvail() {
// 	ifstream inFile(avail_file);
// 	
// 	//Checking for open Error
// 	if (inFile.fail()) {
// 		cerr << "Error opening the file!" << endl;
// 		exit(1);
// 	}
// 	
// 
// 	vector<int> vec; 
// 	//int a, b, c;
// 	string readline;
// 	string integer_string;
// 	string avail_string;
// 	int myID = getID();
// 	while( inFile.good() )
// 	{
// 		getline( inFile, readline);
// 		//cout<< "\n" << readline <<"\n";
// 		size_t found = readline.find("="); //Find the character with an '='
// 		size_t pos = readline.find (",");
// 		if(found != string::npos)
// 		{
// 			//while (pos != string::npos){
// 			integer_string = readline.substr(0,found-1); //getting the string "1,1,1"
// 			avail_string = readline.substr(found+1); //getting the avail number as strings
// 			cout << integer_string << endl;
// 			cout << avail_string << endl;
// 		}
// 		
// 		//Write the avail for [w,d,s] to worker_avail[w][d][s]
// 		for (int w=0; w<NUM_WEEKS; w++){
// 			for(int d=0; d<NUM_DAYS; d++){
// 				for(int s=0; s<NUM_SHIFTS; s++){
// 					worker_avail[w][d][s] = atoi(avail_string);
// 				}
// 			}
// 		}
// // 		cout<< "\n" << readline <<"\n";
// 
// // 		std::stringstream ss(readline);
// // 		string word;
// 	
// 	}
// 	cout << count << endl;
// }

