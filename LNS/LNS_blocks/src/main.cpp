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
	lib.createWorkers(); //Creating myworkers[39]
	
	
	cout << "Worker 1's availability matrix is: "<< endl;
	lib.getWorker(1).getAvail_matrix();
	
	//Assign all the blocks to workers. Note: does apparently not assign them correctly (only copies?)
	lib.assign_blocks_to_workers();
// 	lib.assign_blocks_to_workers(lib.get_block_vector());
	
	//***Print weekend, weekday and weekrest vect for all 39 workers***
// 	vector<Block> test_output;
// 	//cout << lib.getWorker(1).getName() << endl;
// 	for(int i=1; i<=39; i++){
// 		test_output = lib.getWorker(i).getweekend_vect();
// 		cout << "Worker " << i << " has the following weekend blocks assigned to it: ";
// 		for(unsigned int m=0; m<test_output.size(); m++){
// 			cout << test_output.back().getID() << " ";
// 			test_output.pop_back();
// 		}
// 		cout << endl;
// 	}
	
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

	
	//***Test of string compare***
	string type1;
	string type2;
	string type3;
	type1 = "weekend";
	type2 = "weekday";
	type3 = "weekrest";
	if (type1 == "weekend"){
		cout << "Its identical" << endl;
	}
	
	return 0;
}




