#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include "Workers.h"
using namespace std;

int main() {
	ifstream inFile;
	inFile.open("./src/data/librarystaff5W.txt");
	//Checking for open Error
	if (inFile.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}
	int count = 0;
	string line;
	if (inFile.good())
	{
		while (!inFile.good())
		{
			getline(inFile, line);
			if (line == "lib")
			{
				count++;
			}
		}
		inFile.close();
		cout << count << endl;
	}
	else cout << "End of file \n";
	
	return 0;
	
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
   return 0;
}