#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include "Workers.h"
using namespace std;

int main() {
	ifstream inFile("./src/data/librarystaff5W.txt");
	//Checking for open Error
	if (inFile.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}


	vector<int> vec; 
	//int a, b, c;
	string readline;
	string integer_string;
	string avail_string;
	int count = 0;
	while( inFile.good() )
	{
		getline( inFile, readline);
		//cout<< "\n" << readline <<"\n";
		size_t found = readline.find("=");
		size_t pos = readline.find (" ");
		if(found != string::npos)
		{
			//while (pos != string::npos){
			integer_string = readline.substr(0,found-1); //getting the string "1 1 1"
			avail_string = readline.substr(found+1);
			cout << integer_string << endl;
			//if '=' is found, then read the integers a b c = d
			cout << found << endl;
			cout << "an '=' found at: " << found << '\n';
		}
	
	}
	cout << count << endl;
	return 0;
}

