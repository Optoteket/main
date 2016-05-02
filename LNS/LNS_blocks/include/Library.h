#ifndef __LIBRARY_H_INCLUDED__
#define __LIBRARY_H_INCLUDED__

#include <iostream>
#include <vector>
#include "Workers.h"
#include "Blocks.h"
using namespace std;

class Library {
private:
	//Member variables
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	static const int NUM_TASKS = 4; //No task, Block, PL, HB, (BokB)
	int num_blocks; //Number of blocks created
	int num_workers; //39 workers in the library
	int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	
	int tasks_filled[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS+1];
	enum task_type{no_task, block, PL, HB, BokB};
	Worker myworkers[39]; //Create 39 workers in library class. Array is from 0->38
	int task_assign_avail[NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	vector<Block> block_vector; //A vector with all the blocks created
	
	
	int demand_differ[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS+1]; //OK as public? only one Library object
	int num_lib_assigned[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //Tasks: Block, PL, HB, BokB
	int num_ass_assigned[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //initialize as 0 and add to constructor

 	int HB_assigned[NUM_WEEKS]; //1 if assigned week w, 0 else
 	
 	//Find lowest block cost in vector
	vector<int> lowest_cost_IDs;
	int lowest_cost;

public:
	//Default Constructor
	Library();
	
	
	//Destructor
	~Library();
	
	//Accessor Functions
	int getDemand(int, int, int, int) const;
// 	int getDemand_differ(
	int getNum_blocks() const;
	int getTask_avail(int, int, int) const;
	int getNum_day_combinations() const;
	
	int getNum_lib_assigned(int, int, int, int) const;
	int getNum_ass_assigned(int, int, int, int) const;
	
	//Mutator functions
	void setDemand(int, int, int, int, int);
	void setDemand(int, int, int, string, int);
	
	void readDemand();
	void printDemand();
	void createWorkers();
// 	void createBlocks();
	void setNum_blocks(int);
	void setNum_day_combinations(int);
	vector <string> get_info_vector();
	vector <Block>& get_block_vector();
	
	
	void setAvail_worker();
	Worker& getWorker(int i);
	void setTask_avail();
	void printTask_avail();
	void create_all_blocks();
	void assign_tasks_to_block(Block&, int, int, int, int, int, int, int, int, int, int, int, int);
	void assign_blocks_to_workers();
	void assign_block(Block*, int);
	bool week_empty_of_tasks(Block*);
	void print_weekblocks_avail_worker(int, string);
	void print_weekblocks_assigned_worker(int, string);
	void assign_rot_to_workers();
	void calculate_tasks_filled();
	void print_tasks_filled();
	void clear_tasks_filled();
	void print_num_workers(string);
	void initial_add_blocks_to_workers();
	void calculate_demand_differ();
	void print_demand_differ();
	void calculate_all_week_costs_for_worker(string, int, int); //"weekrest" or "weekday" and worker_id as arguments
	
	void calculate_HB_assigned();
	
	void find_lowest_cost_in_vector(string, int);
	void print_cost_vector(string, int);

	void create_initial_solution();
	void add_best_blocks_to_initial_solution(string, int, int = 0); //Type, current_worker, count (optiona)



};





#endif
