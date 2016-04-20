#ifndef __WORKERS_H_INCLUDED__
#define __WORKERS_H_INCLUDED__

#include <iostream>
#include <vector>
#include "Blocks.h"
using namespace std;

class Worker {
public:
	//Default Constructor
	Worker();
	
	//Overload Constructors
	Worker(int, string, string, string, string, string, string, string, string);
	
	//Destructor
	~Worker();
	
	//Accessor Functions
	int getID() const;
		//Returns the ID of the worker
	string getName() const;
		//Returns the name of the worker
	string getBoss() const;
		//Returns whether the worker is a boss or not "Yes" or "No"
	string getQual() const;
		//Returns whether the worker is a librarian or assistant, "Lib" or "Ass"
	string getDep() const;
		//Returns the department, "Child", "Media", "Adult" or "None"
	string getPL() const;
	
	int getAvail(int, int, int) const;
		//Returns the amount of PL a worker shall be assigned.
	string getWeekend() const;
		//Returns whether a worker is to be assigned weekends "no_weekend" or "weekend"
	string getHB() const;
		//Returns "standard_HB", "no_HB" or "only_HB". "standard_HB" means max 1 per 5 weeks(10 weeks)
	string getFreeday() const;
		//Returns "no_freeday" or "freeday". "freeday" means 1 freeday with no tasks per week(?)
	void getAvail_matrix() const;
	vector<Block*> getweekend_vect() const;
	vector<Block*> getweekday_vect() const;
	vector<Block*> getweekrest_vect() const;
	
	//Mutator functions
	void setID(int);
	void setName(string);
	void setBoss(string);
	void setQual(string);
	void setDep(string);
	void setPL(string);
	void setAvail(int, int, int, int); //Input: w, d, s and A = availability
	void setWeekend(string);
	void setHB(string);
	void setFreeday(string);
	
// 	void setweekend_vect(vector<int>); //vector<Block> !
// 	void setweekday_vect(vector<int>);
// 	void setweekrest_vect(vector<int>);
	
	void createBlocks();
	
	void add_block(string, Block*);
	


private:
	//Member variables
	int newID;
	string newName;
	string newBoss;
	string newQual;
	string newDep;
	string newPL;
	string newWeekend;
	string newHB;
	string newFreeday;
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	int worker_avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
	int stand_in[NUM_WEEKS][NUM_DAYS-2]; //stand_in[w,s] = 1 if stand-in, 0 else
	vector<Block*> weekend_blocks_avail; //weekend_blocks_avail: [block.ID(1) block.ID(8) block.ID(36)] i.e. blocks a worker is avail for
	vector<Block*> weekday_blocks_avail; //blocks available are dependent on availability, weekend worker, pl-demand etc.
	vector<Block*> weekrest_blocks_avail; //Note: Create vector<Block*> instead of new blocks assigned to vectors?
	int rotation; //a number between 1-5 (0-4?) saying how many rotations have been allowed
	int weekend_element; //a number between 1-5 stating where the weekend occurs
	int weekend_week; //a number representing the index of the weekend block
	int tasks_assigned; //the number of tasks a worker is assigned in total. (max 4/v)
	
};





#endif
