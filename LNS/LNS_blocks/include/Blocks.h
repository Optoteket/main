#ifndef __BLOCKS_H_INCLUDED__
#define __BLOCKS_H_INCLUDED__

#include <iostream>
using namespace std;

class Block {
private:
	void init(); //Used in default constructor and Overload constructor
	//Member variables
	int newID;
	int wday_block_number; //A number between 0-3, 0 if not a weekday block. 1 if 1st wdayblock, 2 if 2nd, 3 if 3rd
	string newWeektype;
	string newHB;
// 	string avail_file = "./src/data/workers5W.txt";
	static const int NUM_WEEKS = 5;
	static const int NUM_DAYS = 7;
	static const int NUM_SHIFTS = 4;
	static const int NUM_TASKS = 5; //No task, Block, PL, HB, (BokB)
	int tasks_assigned[NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
	//int tasks_assigned_block[NUM_DAYS][NUM_SHIFTS];
	//vector<int> tasks_assigned_block;
	int num_tasks; //number of tasks the block contains
	int num_Blocks; //number of 'Exp' and 'Info' the block contains
	int num_Exp; //number of Exp the block contains
	int num_Info; //number of Info the block contains
	int num_PL; //number of PL the block contains
	int num_HB; //number of HB the block contains

public:
	//Default Constructor
	Block();
	
	//Copy Constructor
	Block(const Block&);
	
	//Overload Constructors
	Block(int, string, string); //ID, weektype, HB
	Block(int, string); //ID, weektype
	Block(int); //ID
	
	//Destructor
	~Block();
	
	//Accessor Functions
	int getID() const;
	int getnum_tasks() const;
	int getnum_Blocks() const;
	int getnum_Exp() const;
	int getnum_Info() const;
	int getnum_PL() const;
	int getnum_HB() const;

	string getWeektype() const;
		//Returns "weekend", "weekrest" or "weekday"
	string getHB() const;
		//Returns "standard_HB", "no_HB" or "only_HB". "standard_HB" means max 1 per 5 weeks(10 weeks)
	void getTask_matrix() const;
		//prints out the entire task matrix to the terminal
	int getTask(int, int, int) const;
	int getNUM_WEEKS() const;
	int getNUM_DAYS() const;
	int getNUM_SHIFTS() const;
	int getNUM_TASKS() const;
	int getWday_block_number() const;
	
	//Mutator functions
	void setID(int);
	void setnum_tasks();
	void setnum_Blocks(int);
	void setnum_Exp(int);
	void setnum_Info(int);
	void setnum_PL(int);
	void setnum_HB(int);
	void setWeektype(string);
	void setHB(string);
	void setTask(int, int, int, int); //Input: w, d, s, j and A = assigned value (0/1)
	void setWday_block_number(int);
	int not_assigned(int);

};





#endif
