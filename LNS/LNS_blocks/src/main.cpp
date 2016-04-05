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


	vector<string> vec;


	string readline;
	size_t found;
	int count = 0;
	while( inFile.good() )
	{
		getline( inFile, readline);
		cout<< "\n" << readline <<"\n";
		found = readline.find("department");
		if(found)
		{
			cout << "It is found!" << endl;
			count++;
			found = 0;
		}
// 		cout<< "\n" << readline <<"\n";

// 		std::stringstream ss(readline);
// 		string word;
	
	}
	cout << count << endl;
	return 0;
}


//Read a line
// 	getline(inFile, readline);
// 	cout<< "\n" << readline <<"\n";
// 	char c;
	//Find if there is an = in the line 'readline'
	
// 	while (getline(ss,times,'='))
// 	{
// 		cout << times << endl;
// 		stringstream ss2(times); //read in week,day,shift to another stringstream
// 		string int_value_as_string;
// 		while (getline(ss2,int_value_as_string,','))
// 		{
// 		}
// 	}
	//Read file line by line words separated by blankspace
// 	while(inFile >> readline) {
// 		if (readline == "Vuxen")
// 		{
// 			count++;
// 		}
// // 		cout << readline << endl;
// 	}
// 	cout << count << endl;
	
// 	if (inFile.good())
// 	{
// 		while (!inFile.good())
// 		{
// 			getline(inFile, line);
// 			if (line == "lib")
// 			{
// 				count++;
// 			}
// 		}
// 		inFile.close();
// 		cout << count << endl;
// 	}
// 	else cout << "End of file \n";
	
// 	return 0;
	
// 	inFile << "Hello world\n";
// 	inFile.close();

// 	int x,y;
// 	inFile >> x >> y;
// 	cout << "Num1: " << x << endl;
// 	return 0;
// 	string name;
	
// 	cout << "Hello world" << endl;
	//Create a worker
// 	Worker worker_1(3, "Bob", "Yes", "Lib", "Child", "Many");
// 	cout << "Frist worker's ID is: " << worker_1.getID() << endl << worker_1.getName() << endl;
// 	cout << "Enter a name" << endl;
// 	cin >> name;
// 	worker_1.setName(name);
// 	cout << "The new name of worker 1 is: " << worker_1.getName() << endl;
//    return 0;
// }