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
	void createBlocks();
	void setNum_blocks(int);
	void setNum_day_combinations(int);
	vector <string> get_info_vector();
	
	void setAvail_worker(Worker[39]);
	Worker getWorker(int i) const;
	void setTask_avail();
	void printTask_avail();
	void createBlockpool();
	//int calculate_num_combinations(int);
	bool is_day_blocked(vector<int>, int);
	int get_all_day_combinations(int, int);
	void create_combinations(int, int);
	void print_comb_vector(const vector<int>&);
	int calculate_combinations(const vector<int>&);

private:
	//Member variables
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	static const int NUM_TASKS = 5;
	int num_blocks; //Number of blocks created
	int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	//int demand_differ[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	enum task_type{Exp, Info, PL, HB, BokB};
	Worker myworkers[39]; //Create 39 workers in library class. Array is from 0->38
	int task_assign_avail[NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	vector<Block> block_vector;
	int num_day_combinations; //#combinations found when num_tasks_to_assign tasks are considered
	vector<int> days; //a vector with all days, [1 2 3 4 5] if looking at 5 days.
	vector<int> combination; //'num_tasks_to_assign' long and a combination of those days e.g. [1 2 4]
	int num_combinations_total; //#combinations for all day combinations of a fix number e.g. 3 days (=3 tasks)
	vector<vector<vector<int> > > task_array3D; //3D array with all task combinations for a fix number of days
};





#endif
