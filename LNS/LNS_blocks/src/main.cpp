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

	
	lib.createWorkers(); //Creating myworkers[39]
	
	
	//***Test of block_assignment if correct***
// 	int j = 23;
// 	int b_id = 0;
// 	cout << "here" << endl;
// 	lib.get_block_vector().at(b_id).getTask_matrix();
// // 	lib.get_block_vector().back().getTask_matrix();
// 	cout << "here" << endl;
// 	cout << "Worker: " << j << " has " << lib.getWorker(j).getweekend_vect().size() << " " << lib.getWorker(j).getweekday_vect().size() << " " << lib.getWorker(j).getweekrest_vect().size() << " in sizes" << endl;
// 	cout << "Qualification for worker " << j << " is: " << lib.getWorker(j).getQual() << endl;
// 	cout << "Weekend type for the worker is: " << lib.getWorker(j).getWeekend() << endl;
// 	cout << "Worker " << j << "'s availability matrix is: "<< endl;
// 	lib.getWorker(j).getAvail_matrix();
// 	lib.assign_block(lib.get_block_vector().at(b_id), j);
// 	cout << "Worker: " << j << " has " << lib.getWorker(j).getweekend_vect().size() << " " << lib.getWorker(j).getweekday_vect().size() << " " << lib.getWorker(j).getweekrest_vect().size() << " in sizes" << endl;
	
	
	//Assign all the blocks to workers. Note: does apparently not assign them correctly (only copies?)
	lib.assign_blocks_to_workers();
	lib.print_weekblocks_assigned_worker(36, "weekend");
	
	lib.assign_rot_to_workers();
	
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
	
	return 0;
}




