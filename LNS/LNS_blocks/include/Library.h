#ifndef __LIBRARY_H_INCLUDED__
#define __LIBRARY_H_INCLUDED__

#include <iostream>
#include <vector>
#include "Workers.h"
#include "Blocks.h"
using namespace std;

class Library {
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
	bool is_empty_of_tasks(Block*);
	void print_weekblocks_avail_worker(int, string);
	void print_weekblocks_assigned_worker(int, string);
	void assign_rot_to_workers();
	void calculate_tasks_filled();
	void print_tasks_filled();
private:
	//Member variables
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	static const int NUM_TASKS = 4; //Block, PL, HB, BokB
	int num_blocks; //Number of blocks created
	int num_workers;
	int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	int demand_differ[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	int tasks_filled[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; //INITIALIZE AS 0
	enum task_type{block, PL, HB, BokB};
	Worker myworkers[39]; //Create 39 workers in library class. Array is from 0->38
	int task_assign_avail[NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	vector<Block> block_vector; //A vector with all the blocks created
	
};





#endif
