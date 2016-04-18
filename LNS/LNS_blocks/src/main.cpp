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
	lib.printDemand();
	lib.printTask_avail();
	cout << "Number of blocks created are: " << lib.getNum_blocks() << endl;
	cout << "Blocks created in main are: " << lib.getNum_blocks() << endl;
	cout << "Size of block_vector is: " << lib.get_block_vector().size() << endl;
	lib.create_all_blocks();
	cout << lib.get_block_vector().size() << endl;
	 //***Print all combinations of schedules***
// 	for (unsigned int i=0; i<lib.get_block_vector().size(); i++){
// 		lib.get_block_vector().at(i).getTask_matrix();
// 	}


	lib.get_block_vector().back().getTask_matrix();
	lib.createWorkers();

	cout << "Worker 1's availability matrix is: "<< endl;
	lib.getWorker(3).getAvail_matrix();
	//***Get number of blocks***
// 	int num = 0;
// // 	string type = " ";
// 	for (unsigned int i=0; i<lib.get_block_vector().size(); i++){
// 		num = lib.get_block_vector().at(i).getnum_Blocks();
// 		cout << "#Blocks: " << num << endl;
// 	}
	
	
	
	// 	Block block1(3);
// 	block1.setWeektype("Weekend");
// 	cout << block1.getWeektype() << endl;
	//myblocks[1].getTask_matrix();
   	//myworkers[38].getAvail_matrix();

	return 0;
}




