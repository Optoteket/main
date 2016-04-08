#ifndef __BLOCKS_H_INCLUDED__
#define __BLOCKS_H_INCLUDED__

#include <iostream>
using namespace std;

class Block {
public:
	//Default Constructor
	Block();
	
	//Overload Constructors
	Block(int, string, string);
	
	//Destructor
	~Block();
	
	//Accessor Functions
	int getID() const;
		//Returns the ID of the worker
	string getWeektype() const;
		//Returns 
	string getHB() const;
		//Returns "standard_HB", "no_HB" or "only_HB". "standard_HB" means max 1 per 5 weeks(10 weeks)
	void getTask_matrix() const;
		//prints out the entire task matrix to the terminal
	int getTask(int, int, int, int) const;
		
	
	//Mutator functions
	void setID(int);
	void setWeektype(string);
	void setHB(string);
	void setTask(int, int, int, int, int); //Input: w, d, s, j and A = assigned value (0/1)
	
	int num_tasks; //a number of tasks the block contains
	int num_Exp; //a number of Exp the block contains
	int num_Info; //a number of Info the block contains
	int num_PL; //a number of PL the block contains
	int num_HB; //a number of HB the block contains

private:
	//Member variables
	int newID;
	string newWeektype;
	string newHB;
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	static const int NUM_TASKS = 4;
	int tasks_assigned[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	//int tasks_assigned_block[NUM_DAYS][NUM_SHIFTS];
	vector<int> tasks_assigned_block;
	
};





#endif
