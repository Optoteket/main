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
//Felkällor: input_vector{}, copy constructor

int main() {
	//create a list of worker objects. myworkers[0], myworkers[1] etc.
// 	Worker aworker(1, "Ben", "not_boss", "lib", "Child", "Normal_PL", "No_weekends", "HB", "No");
// 	cout << aworker.getName() << endl;
	Library lib;
	lib.createWorkers();
	lib.printDemand();
	lib.getWorker(1).getAvail_matrix();
	lib.printTask_avail();
//	cout << lib.getTask_avail(0,0,0) << endl;
	//lib.createBlockpool();
	cout << "Number of blocks created are: " << lib.getNum_blocks() << endl;
	vector<int> blocked_day_vector;
	for (unsigned int i = 0; i<7; i++){
		blocked_day_vector.push_back(i);
	}
	cout << "Last value of the vector is: " << blocked_day_vector.back() << endl;
	cout << "The day is blocked: " << lib.is_day_blocked(blocked_day_vector, 7) << endl;
	lib.setNum_day_combinations(lib.get_all_day_combinations(1,5));
	cout << "Number of day combinations found are: " << lib.getNum_day_combinations() << endl;
	
	//vector<int> v(2);
	//v = {34,23};
// 	int combs = 0;
// 	for(int d1=1; d1<=5; d1++){
// 		for(int d2=d1+1; d2<=5; d2++){
// 			for(int d3=d2+1; d3<=5; d3++){
// 				combs++;
// 			}
// 		}
// 	}
// 	cout << "combs for 3 tasks are: " << combs << endl;
	
	
	// 	Block block1(3);
// 	block1.setWeektype("Weekend");
// 	cout << block1.getWeektype() << endl;
	//int combinations = lib.calculate_num_combinations();
	//cout << "Number of combinations found are: " << combinations << endl;
	//myblocks[1].getTask_matrix();
   	//myworkers[38].getAvail_matrix();

	return 0;
}




