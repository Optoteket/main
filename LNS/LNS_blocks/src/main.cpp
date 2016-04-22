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
	Library lib;
	lib.printDemand();
	lib.printTask_avail();
	cout << "Number of blocks created are: " << lib.getNum_blocks() << endl;
	cout << "Blocks created in main are: " << lib.getNum_blocks() << endl;
	cout << "Size of block_vector is: " << lib.get_block_vector().size() << endl;
	lib.create_all_blocks();
	cout << "block_vector size is: " << lib.get_block_vector().size() << endl;
	 //***Print all combinations of schedules***
// 	for (unsigned int i=0; i<lib.get_block_vector().size(); i++){
// 		lib.get_block_vector().at(i).getTask_matrix();
// 	}

	
	lib.createWorkers(); //Creating myworkers[39]
	
	
	//***Test of block_assignment if correct***
// 	int j = 36;
// 	int b_id = 1;
// 	cout << "here" << endl;
// 	lib.get_block_vector().at(b_id).getTask_matrix();
// // 	lib.get_block_vector().back().getTask_matrix();
// 	cout << "here" << endl;
// 	cout << "Worker: " << j << " has " << lib.getWorker(j).getweekend_vect().size() << " " << lib.getWorker(j).getweekday_vect().size() << " " << lib.getWorker(j).getweekrest_vect().size() << " in sizes" << endl;
// 	cout << "Qualification for worker " << j << " is: " << lib.getWorker(j).getQual() << endl;
// 	cout << "Weekend type for the worker is: " << lib.getWorker(j).getWeekend() << endl;
// 	cout << "Worker " << j << "'s availability matrix is: "<< endl;
// 	lib.getWorker(j).getAvail_matrix();
// 	lib.assign_block(&lib.get_block_vector().at(b_id), j);
// 	cout << "Worker: " << j << " has " << lib.getWorker(j).getweekend_vect().size() << " " << lib.getWorker(j).getweekday_vect().size() << " " << lib.getWorker(j).getweekrest_vect().size() << " in sizes" << endl;
	
	
	//***Assign all the blocks to workers***
	lib.assign_blocks_to_workers();
 	lib.print_weekblocks_avail_worker(23, "weekend");
	
	//***Assign rotation to the workers***
	lib.assign_rot_to_workers();
// 	for(int i=0; i<4; i++){
// 		lib.get_block_vector().at(i).getTask_matrix();
// 		cout << "num tasks for block nr " << i << " is: " << lib.get_block_vector().at(i).getnum_tasks() << endl;
// 	}
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
	
	//***Create initial solution: Empty weeks for all workers***
	lib.initial_add_blocks_to_workers();
	
	//***Calculate and print tasks_filled matrix***
// 	lib.calculate_tasks_filled();
// 	lib.print_tasks_filled();

	int k = 3;
// 	//***Add a few blocks to some workers and calculate tasks_filled again***
	cout << "worker number " << k << " has " << lib.getWorker(k).getblocks_assigned().size() << " blocks assigned" << endl;
	cout << "worker number " << k << " has weekend week at index: " << lib.getWorker(k).getWeekend_week() << endl;
	cout << "worker number " << k << " has " << lib.getWorker(k).getweekend_vect().size() << " weekend blocks avail" << endl;
	cout << "worker number " << k << " has " << lib.getWorker(k).getweekrest_vect().size() << " weekrest blocks avail" << endl;
	cout << "worker number " << k << " has " << lib.getWorker(k).getweekday_vect().size() << " weekday blocks avail" << endl;
// 	
// 	int wend_week = lib.getWorker(k).getWeekend_week();
// 	if(
	for(int k=1; k<=39; k++){
	lib.getWorker(k).add_block_to_worker("weekend", 1);
	lib.getWorker(k).add_block_to_worker("weekrest", 0);
	}
// 	lib.getWorker(k).add_block_to_worker("weekday", 4);
// 	lib.getWorker(k).add_block_to_worker("weekday", 5);
// 	lib.getWorker(k).add_block_to_worker("weekday", 6);
// 	cout << "worker number " << k << " has now " << lib.getWorker(k).getblocks_assigned().size() << " blocks assigned" << endl;
	cout << "Worker " << k << " has been assigned following blocks" << endl;
	lib.print_weekblocks_assigned_worker(k, "weekend"); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
	lib.print_weekblocks_assigned_worker(k, "weekrest"); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
	lib.print_weekblocks_assigned_worker(k, "weekday"); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
	lib.calculate_tasks_filled();
	lib.print_tasks_filled();

	std::vector<int> myvector (3,100);
	std::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();
	int modulo = (5+2+3+4) % 2;
	std::vector<int> anothervector (2,400);
	myvector.insert (it+modulo,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
	std::cout << ' ' << *it;
	std::cout << '\n';
	return 0;
}




