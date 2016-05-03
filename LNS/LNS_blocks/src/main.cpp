#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include <cstdlib> //rand() function
#include "Workers.h"
#include "Blocks.h"
#include "Library.h"
using namespace std;




int main() {
	int num_workers = 39;
	Library lib;
	lib.printDemand();
	lib.printTask_avail();
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
//  	lib.print_weekblocks_avail_worker(23, "weekend");
	
	//***Assign rotation to the workers***
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
	
	
	//***Set stand_in_avail***
	for(int i=1; i<=num_workers; i++){
		lib.getWorker(i).setStand_in_avail();
	}
	
	
	//***Create initial solution: Empty weeks for all workers***
	lib.initial_add_blocks_to_workers();
	
	//***Calculate and print tasks_filled matrix***
// 	lib.calculate_tasks_filled();
// 	lib.print_tasks_filled();

	
// 	//***Add a few blocks to some workers and calculate tasks_filled again***
// 	int k = 24;
// 	cout << "worker number " << k << " has " << lib.getWorker(k).getblocks_assigned().size() << " blocks assigned" << endl;
// 	cout << "worker number " << k << " has weekend week at index: " << lib.getWorker(k).getWeekend_week() << endl;
// 	cout << "worker number " << k << " has " << lib.getWorker(k).getweekend_vect().size() << " weekend blocks avail" << endl;
// 	cout << "worker number " << k << " has " << lib.getWorker(k).getweekrest_vect().size() << " weekrest blocks avail" << endl;
// 	cout << "worker number " << k << " has " << lib.getWorker(k).getweekday_vect().size() << " weekday blocks avail" << endl;
// // 	
// // 	int wend_week = lib.getWorker(k).getWeekend_week();
// 	for(int m=1; m<=num_workers; m++){
// 		unsigned int num_wend = lib.getWorker(m).getweekend_vect().size();
// 		unsigned int num_wrest = lib.getWorker(m).getweekrest_vect().size();
// 		unsigned int num_wday = lib.getWorker(m).getweekday_vect().size();
// 		
// 		lib.getWorker(m).add_block_to_worker("weekend", rand() % num_wend); //[type, weekblock in vector, weekday to add] (only for "weekday")
// 		lib.getWorker(m).add_block_to_worker("weekrest", rand() % num_wrest);
// 		lib.getWorker(m).add_block_to_worker("weekday", rand() % num_wday,1);
// 		lib.getWorker(m).add_block_to_worker("weekday", rand() % num_wday,2);
// 		lib.getWorker(m).add_block_to_worker("weekday", rand() % num_wday,3);
// 	}
// 	
// // 	cout << "worker number " << k << " has now " << lib.getWorker(k).getblocks_assigned().size() << " blocks assigned" << endl;
// 	cout << "Worker " << k << " has been assigned following blocks" << endl;
// 	lib.print_weekblocks_assigned_worker(k, "weekend"); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
// 	lib.print_weekblocks_assigned_worker(k, "weekrest"); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
// 	lib.print_weekblocks_assigned_worker(k, "weekday"); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned



	lib.calculate_tasks_filled();
	lib.calculate_HB_assigned(); //Calculates which days that already have one or more HB assigned.
	cout << "printing tasks_filled" << endl;
	lib.print_tasks_filled();
// 	return 0;
	lib.calculate_demand_differ();
	lib.print_demand_differ();
	
	//*** Print all available blocks for a worker ***
// 	lib.print_weekblocks_avail_worker(36, "weekday");
	cout << "#libs assigned for given shift is: " << lib.getNum_lib_assigned(0,3,0,1) << " #ass is: " << lib.getNum_ass_assigned(0,3,0,1) << endl;
	
	//*** Try to print cost for a weekday block ***
// 	int p = 23; //p = 8 or 9 good test subjects, 36 good for wend HB, 23 for only HB, 24 for PL and stand-ins
// 	string mytype = "weekend";
// 
// 	lib.calculate_all_week_costs_for_worker(mytype,p);
// 	lib.print_cost_vector(mytype,p);
// 	//***Find the lowest cost in the vector***'
// 	lib.print_cost_vector(mytype,p);
// 	lib.find_lowest_cost_in_vector(mytype,p);
	
	
	
// 	cout << "Weekrest for this worker occurs at week: " << (lib.getWorker(p).getWeekend_week()+1) % 5 << endl;
// 	cout << "Weekend occurs at: " << lib.getWorker(p).getWeekend_week() << endl;
// 	lib.print_weekblocks_avail_worker(p, mytype);
// 	lib.getWorker(p).getStand_in_matrix();
	
	//***Assign Library On Wheels for the regarding workers***
	lib.assign_LOW();
	//***Create initial solution!***
	lib.create_initial_solution();
	
	lib.getWorker(36).print_assigned_LOW();
// 	lib.print_weekblocks_avail_worker(36, "weekrest");
	
	
	return 0;
}




