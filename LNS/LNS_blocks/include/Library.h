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
	
	//Mutator functions
	void setDemand(int, int, int, int, int);
	void setDemand(int, int, int, string, int);
	
	void readDemand();
	void printDemand();
	void createWorkers();
	void createBlocks();
	void setNum_blocks(int);
	vector <string> get_info_vector();
	
	void setAvail_worker(Worker[39]);
	Worker getWorker(int i) const;
	void setTask_avail();
	void printTask_avail();
	void createBlockpool();
	

private:
	//Member variables
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	static const int NUM_TASKS = 5;
	int num_blocks;
	int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	//int demand_differ[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	enum task_type{Exp, Info, PL, HB, BokB};
	Worker myworkers[39]; //Create 39 workers in library class. Array is from 0->38
	int task_assign_avail[NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
};





#endif
