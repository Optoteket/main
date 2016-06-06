#ifndef __LIBRARY_H_INCLUDED__
#define __LIBRARY_H_INCLUDED__

#include <iostream>
#include <vector>
#include "Constants.h"
#include "Workers.h"
#include "Blocks.h"

using namespace std;

class Library {
private:
	//Member variables
// 	string avail_file = "./src/data/workers5W.txt";
	int num_blocks; //Number of blocks created
	int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	
	int tasks_filled[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //No tasks
	enum task_type{no_task, block, PL, HB, BokB};
	Worker myworkers[39]; //Create 39 workers in library class. Array is from 0->38
	int task_assign_avail[NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	vector<Block> block_vector; //A vector with all the blocks created
	
	int stand_in_amount[NUM_WEEKS][NUM_DAYS-2]; //stand_in_amount[w][d] = num
	int lib_stand_in_amount[NUM_WEEKS][NUM_DAYS-2];
	int ass_stand_in_amount[NUM_WEEKS][NUM_DAYS-2];
	
	int demand_differ[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //
	int num_lib_assigned[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //Tasks: Block, PL, HB, BokB
	int num_ass_assigned[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //initialize as 0 and add to constructor

 	int HB_assigned[NUM_WEEKS]; //1 if assigned week w, 0 else
 	
	int lib_per_rot[NUM_WEEKS];
	int ass_per_rot[NUM_WEEKS];
 	
 	//Find lowest block cost in vector
	vector<int> lowest_cost_IDs;
	int lowest_cost;
	int increment;
	vector<int> workers_destroyed;
	int max_min_stand_in;

public:
	//Default Constructor
	Library();
	
	
	//Destructor
	~Library();
	
	//Accessor Functions
	int getDemand(int, int, int, int) const;
	int getNum_blocks() const;
	int getTask_avail(int, int, int) const;
	int getNum_day_combinations() const;
	
	int getNum_lib_assigned(int, int, int, int) const;
	int getNum_ass_assigned(int, int, int, int) const;
	
	//Mutator functions
	void setDemand(int, int, int, int, int);
	void setDemand(int, int, int, string, int);
	
	void readDemand(); //Reads demand from file
	void print_demand(ostream&); //Prints the demand to terminal
	void createWorkers();
// 	void createBlocks();
	void setNum_blocks(int);
	void setNum_day_combinations(int);
	vector <string> get_info_vector();
	vector <Block>& get_block_vector();
	int get_max_min_stand_in() const;
	int get_increment() const;
	vector<int> get_workers_destroyed() const;
	
	void setAvail_worker();
	Worker& getWorker(int i);
	void setTask_avail();
	void printTask_avail();
	void create_all_blocks();
	void assign_tasks_to_block(Block&, int, int, int, int, int, int, int, int, int, int, int, int);
	void assign_blocks_to_workers(ostream&);
	void assign_block(Block*, int);
	bool week_empty_of_tasks(Block*);
	void print_weekblocks_avail_worker(int, string, ostream&);
	void print_all_weekblocks_avail_worker(int, string, ostream&);
	void print_weekblocks_assigned_worker(int, string, ostream&);
	void print_all_weekblocks_assigned_worker(int, ostream&);
	void assign_rot_to_workers();
	void assign_a_rot_to_worker(int);
	void print_weekends_assigned(ostream&);
	void calculate_tasks_filled();
	void print_tasks_filled(ostream&);
	void clear_tasks_filled();
	void calculate_LOW_filled();
	void clear_calculate_LOW_filled();
	void print_num_workers(string, ostream&);
	void initial_add_blocks_to_workers();
	void calculate_demand_differ();
	int get_demand_differ(int, int, int, int) const;
	void print_demand_differ(ostream&);
	
	
	//*** Updates all demands and tasks filled ***
	void calculate_demand();
	
	void calculate_all_week_costs_for_worker(string, int, int); //"weekrest" or "weekday" and worker_id as arguments
	
	void calculate_HB_assigned();
	
	void calculate_stand_ins();
	void print_stand_ins(ostream&);
	int get_sum_stand_ins();
	vector<int> get_lowest_stand_in();
	int get_num_stand_ins(int, int);
	
	void find_lowest_cost_in_vector(string, int);
	void print_cost_vector(string, int);

	void create_initial_solution();
	void add_best_blocks_to_worker(string, int, int = 0); //Type, current_worker, count (optional)
	
	void assign_LOW();
	int check_if_collision(unsigned int, int, int, string);
	
	//*** Evaluate solution ***
	vector<int> evaluate_solution(ostream&);
	
	//*** DESTROY AND REPAIR ***
	void destroy(int);
	void destroy(vector<int>);
	void repair();
	void destroy_repair_one_week_at_the_time();
	

	
// 	void print_results(ostream&, int, int, int);

};





#endif
