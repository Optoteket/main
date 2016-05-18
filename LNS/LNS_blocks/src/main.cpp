#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include <cstdlib> //rand() function
#include <time.h> //clock_t, clock, CLOCKS_PER_SEC
#include "Constants.h"
#include "Workers.h"
#include "Blocks.h"
#include "Library.h"

using namespace std;




int main() {
	clock_t t;
	float time = 0;
	float time2 = 0;
	int count_new_sol = 0;
	int best_solution = 9999999; //Initialized as high value
	ofstream outFile("./target/results.txt");
	//Checking for open Error
	if (outFile.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}
	ofstream outdata("./target/Plotdata.txt");
	//Checking for open Error
	if (outdata.fail()) {
		cerr << "Error opening the file!" << endl;
		exit(1);
	}
	ofstream outobjfcn("./target/objfcn.txt");
	ofstream outfeasible("./target/feasible.txt");
	ofstream outstandins("./target/standins.txt");
	ofstream outmaxmin("./target/maxmin.txt");
	Library lib;
	lib.create_all_blocks();
	cout << "block_vector size is: " << lib.get_block_vector().size() << endl; //Why differ to #blocks to create?

	lib.createWorkers(); //Creating myworkers[39]
	
	
	//***Assign all the blocks to workers***
	lib.assign_blocks_to_workers(outFile); //And print to result file
//  	lib.print_all_weekblocks_avail_worker(23, "weekend", cout);
// 	return 0;
	
	//***Assign rotation to the workers***
	lib.assign_rot_to_workers();
// 	return 0;
	
	
	//***Set stand_in_avail***
	for(int i=1; i<=num_workers; i++){
		lib.getWorker(i).set_stand_in_avail();
	}
// 	lib.getWorker(p).print_stand_in_matrix();
	
	
	//***Create initially: Empty weeks for all workers***
	lib.initial_add_blocks_to_workers();
	
	
	
	lib.calculate_tasks_filled();
	lib.calculate_HB_assigned(); //Calculates which days that already have one or more HB assigned.
	cout << "printing tasks_filled" << endl;
	lib.print_tasks_filled(cout);
// 	return 0;
	lib.print_demand_differ(cout);
	
	//*** Print all available blocks for a worker ***
// 	lib.print_weekblocks_avail_worker(36, "weekday", cout);
	
	//*** Print cost for a weekday block ***
// 	int p = 23; //p = 8 or 9 good test subjects, 36 good for wend HB, 23 for only HB, 24 for PL and stand-ins
// 	string mytype = "weekend";
// 	lib.calculate_all_week_costs_for_worker(mytype,p);
// 	lib.print_cost_vector(mytype,p);

// 	//***Find the lowest cost in the vector***'
// 	lib.print_cost_vector(mytype,p);
// 	lib.find_lowest_cost_in_vector(mytype,p);
	
	
	//***Assign Library On Wheels for the regarding workers***
	lib.assign_LOW();
	
	//***Create initial solution!***
// 	cout << "Before create_initial_solution" << endl;
// 	return 0;
	lib.create_initial_solution();
// 	lib.getWorker(36).print_assigned_LOW();
// 	//Print ID for worker 1s assigned weekend
// 	cout << lib.getWorker(1).getblocks_assigned().at(lib.getWorker(1).getWeekend_week())->getID() << endl;

	//***Print assigned blocks for a few workers
// 	for(int k=16;k<=20;k++){
// 	cout << "Worker " << k << " has been assigned following blocks" << endl;
// 	lib.print_weekblocks_assigned_worker(k, "weekend", cout); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
// 	lib.print_weekblocks_assigned_worker(k, "weekrest", cout); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
// 	lib.print_weekblocks_assigned_worker(k, "weekday", cout); //prints the blocks of type "weekend", "weekrest" or "weekday" if 5 assigned
// 	cout << "\n" << endl;
// 	}
	
	cout << "The total cost after the initial solution is: " << lib.evaluate_solution(cout).at(1) << endl;
	
	lib.print_num_workers("lib", cout);
	lib.print_num_workers("ass", cout);
// 	lib.print_demand(cout);
// 	lib.print_tasks_filled(cout);
// 	lib.print_all_weekblocks_avail_worker(21, "weekrest", cout);
// 	lib.getWorker(36).print_assigned_LOW();

	////Find the worker with wrongly added weekend! -> worker nr 23 and **25** wrong due to "Only HB" and assigned after
// 	for(int i=1; i<=num_workers; i++){
// 		if(lib.getWorker(i).getblocks_assigned().at(lib.getWorker(i).getWeekend_week())->getID() == 0){
// 			cout << "Worker is: " << i << endl;
// 		}
// 		
// 		if(lib.getWorker(i).getQual().compare(0,3,"lib") == 0){
// 			cout << "Librarian " << i << " is assigned following weekend block at week " << lib.getWorker(i).getWeekend_week() << endl;
// 			lib.getWorker(i).getblocks_assigned().at(lib.getWorker(i).getWeekend_week())->getTask_matrix();
// 		}
// 	}
	
	
// // 	int p = 36;
// 	int destroy_cost = 0;
// 	cout << "\n\n\nDestroy/Repair test starting here\n\n\n" << endl;
// // 	lib.print_weekends_assigned(cout);
// // 	lib.print_all_weekblocks_assigned_worker(p, cout);
// 	lib.print_demand_differ(cout);
// 	cout << "The total cost after the new solution is: " << lib.evaluate_solution(cout).at(1) << endl;
// // 	cout << "Worker " << p << " is working weekend at week: " << lib.getWorker(p).getWeekend_week() << endl;
// // 	lib.destroy(p);
// 	lib.destroy(3);
// 	cout << "\nAfter destroy!\n" << endl;
// 	lib.calculate_demand(); //Update the tasks_filled and demand_differences
// 	destroy_cost = lib.evaluate_solution(cout).at(1);
// 	cout << "The total cost after the new solution is: " << destroy_cost << endl;
// 	
// // 	lib.print_demand_differ(cout);
// // 	lib.print_weekends_assigned(cout);
// // 	lib.print_tasks_filled(cout);
// 	cout << "before repair" << endl;
// 	lib.repair(); //need to calculate new demand_differences! Need to calculate new costs ???
// 	cout << "After repair" << endl;
// // 	cout << "Worker " << p << " is working weekend at week (after repair): " << lib.getWorker(p).getWeekend_week() << endl;
// 	lib.calculate_demand(); //Update the tasks_filled and demand_differences
// // 	cout << "The total cost after the new solution is: " << lib.evaluate_solution(cout).at(1) << endl;
// 	cout << "Destroy_cost is: " << destroy_cost << endl;
// 	cout << "Repair-increment is: " << lib.get_increment() << endl;
// 	cout << "New solution should be: " << destroy_cost+lib.get_increment() << " but it is: " << lib.evaluate_solution(cout).at(1) << endl;
// 	return 0;
// // 	cout << "Weekblocks assigned to the worker is now: " << endl;
// // 	lib.print_all_weekblocks_assigned_worker(p, cout);
// // 	lib.print_demand_differ(cout);
// // 	lib.print_weekends_assigned(cout);
// // 	cout << "worker " << p << " works weekend at week: " << lib.getWorker(p).getWeekend_week() << endl;
// // 	return 0;

// 	lib.getWorker(p).print_tasks_assigned_worker(); //unrotated
// // 	lib.getWorker(p).print_assigned_LOW();
// 	
// 	lib.print_stand_ins(cout);
// 	cout << "Total number of stand_ins are: " << lib.get_sum_stand_ins() << endl;
// 	cout << "Lowest number of stand_ins are: " << lib.get_lowest_stand_in() << endl;
// // 	lib.getWorker(p).print_stand_in_matrix();
// // 	lib.getWorker(p).getAvail_matrix();
// 	cout << "Before Destroy/Repair" << endl;
// 	return 0;
	
	//***DESTROY AND REPAIR LOOP!***
	int stop_time = 65000;
	int t_updated;
	int current_solution = 0;
	int iter_count = 0;
	vector<int> output_vector;
	STAND_IN_COST = LOW_PRIORITY;
	outdata << "objfcn\tfeasible\tstandins\tmaxmin" << endl;
	while(time < stop_time){ //54000 means 17-08, 239400 means fri 13.37 - mon 8.07
		t_updated = 0;
		t = clock(); //Start counting
		output_vector.clear();
		if(time <= stop_time/3){ //Phase 1
			STAND_IN_COST = LOW_PRIORITY;
			cout << "Inside Phase 1" << endl;
		}else if(time > stop_time/3 && time < 2*stop_time/3){ //Phase 2
			STAND_IN_COST = HIGH_PRIORITY;
			cout << "Inside Phase 2" << endl;
		}else if(time >= 2*stop_time/3){ //Phase 3, middle priority
			STAND_IN_COST = MIDDLE_PRIORITY;
			cout << "Inside Phase 3" << endl;
		}
		//Destroy and update
		lib.destroy(3);
		lib.calculate_demand();
		//Repair (updates are inside the repair)
		lib.repair();
		lib.calculate_demand();
		
		
		output_vector = lib.evaluate_solution(cout); //Total objfcn, feasible_cost, #stand-ins, max-min-stand-in
		//Print all values to plotdata.txt
		outdata << output_vector.at(0) << "\t" << output_vector.at(1) << "\t" << output_vector.at(2) << "\t" << output_vector.at(3) << endl;
		outobjfcn << output_vector.at(0) << endl;
		outfeasible << output_vector.at(1) << endl;
		outstandins << output_vector.at(2) << endl;
		outmaxmin << output_vector.at(3) << endl;
		
		
		current_solution = output_vector.at(1); //Feasible cost from objective function
		if(current_solution < best_solution){
			best_solution = current_solution;
			count_new_sol++;
			//Print best solution to file!
			outFile << "\n\n\n***Best iteration number: " << count_new_sol << "***" << endl;
			outFile << "Best solution so far is " << lib.evaluate_solution(outFile).at(1) << endl;//Print everything with evaluate_solution
			t = clock() - t;
			time2 = time + (float)t/CLOCKS_PER_SEC;
			outFile << "Time where new best solution found is: " << time2 << endl;
			t_updated = 1;
			//0=total_cost, 1=total_eval_cost, 2=sum_stand_ins, 3=maxmin, 4=demand_tot_cost
			//5=demand_lib_cost, 6=demand_ass_cost, 7=demand_PL_cost, 8=demand_HB_cost, 9=demand_evening_cost
			//10=PL_amount_cost, 11=no_weekend_cost
			if(best_solution < 2000 && output_vector.at(1) > 0 && output_vector.at(4) > 0 &&
				output_vector.at(5) == 0 && output_vector.at(6) == 0 && output_vector.at(7) == 0 &&
				output_vector.at(8) == 0 && output_vector.at(9) == 0 && output_vector.at(10) == 0 &&
				output_vector.at(11) == 0){
				outFile << "Entering final phase!" << endl;
				
			}
		}
		if(t_updated == 0){
			t = clock() - t; //in TICKS
		}
		time += (float)t/CLOCKS_PER_SEC; //As float value
		cout << "\n\n\ntime is: " << time << "\n\n" << endl;
		iter_count++;
		
	}
	
// 	cout << "it took " << ((float)time)/CLOCKS_PER_SEC << " seconds to execute the program" << endl;
	cout << "Number of iterations during the run: " << iter_count << endl;
	cout << "Highest lowest number of stand-in for each day is: " << lib.get_max_min_stand_in() << endl;
	cout << "Best solution found was: " << best_solution << endl;
	cout << "Found " << count_new_sol << " new solutions during iteration" << endl;
	outFile << "\n\nFound " << count_new_sol << " new solutions during iteration" << endl;
	outFile << "Number of iterations during the run: " << iter_count << endl;
	outFile << "Best solution found was: " << best_solution << endl;
	
	outFile.close();
	outdata.close();
	cout << "End of main" << endl;
	return 0;
}




