#ifndef __WORKERS_H_INCLUDED__
#define __WORKERS_H_INCLUDED__

#include <iostream>
#include <vector>
#include "Constants.h"
#include "Blocks.h"

using namespace std;

class Worker {

private:
	//Body of Default Constructor
	void init();
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
	int newRot; //a number between 1-5 (0-4?) saying how many rotations have been allowed
	int newWeekend_week; //a number between 0-4 stating where the weekend occurs
	//int weekend_element; //a number representing the index of the weekend block

	int tasks_assigned; //the number of tasks a worker is assigned in total. (max 4/v)
// 	string avail_file = "./src/data/workers5W.txt";
	
	
	
	int worker_avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
	int stand_in[NUM_WEEKS][NUM_DAYS-2]; //stand_in[w,s] = 1 if stand-in, 0 else
	int stand_in_avail[NUM_WEEKS][NUM_DAYS-2]; //1 if avail is 1 for shift 1-3 on a day d, 0 else.
	vector<Block*> weekend_blocks_avail; //weekend_blocks_avail: [block.ID(1) block.ID(8) block.ID(36)] i.e. blocks a worker is avail for
	vector<Block*> weekday_blocks_avail; //blocks available are dependent on availability, weekend worker, pl-demand etc.
	vector<Block*> weekrest_blocks_avail; //Note: Create vector<Block*> instead of new blocks assigned to vectors?
	
	int LOW_assigned[NUM_WEEKS][NUM_DAYS-2][NUM_SHIFTS]; //1 if assigned LOW that day, 0 else
	
	
	int num_PL; //Amount of PL assigned to a worker. no_PL => 0, standard_PL => 0-2(?), many_PL => 3-4(?)
	vector<Block*> blocks_assigned; //Vector with the blocks assigned to the person starting with weekend block (then weekrest, weekday)
// 	int day_blocks_added; //Add to constructor etc!
	
	
	struct Weekend_cost{
		int wend_cost;
		Block* block;
	};
	struct Weekrest_cost{
		int wrest_cost;
		Block* block;
	};
	struct Weekday_cost{
		int wday_cost;
		Block* block;
	};
	
	vector<Weekday_cost> weekday_cost_vector;
	vector<Weekend_cost> weekend_cost_vector;
	vector<Weekrest_cost> weekrest_cost_vector;
	
	int block_types_added[3]; //An array with ones and zeros stating if added. Eg [1 0 1] means Wend added, wrest not added, wdays added
	
public:
	//Default Constructor
	Worker();
	
	//Copy Constructor
	Worker(const Worker&);
	
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
	int getRot() const;
	int getWeekend_week() const;
	void getAvail_matrix() const;
	void getStand_in_matrix() const;
	vector<Block*> getweekend_vect() const;
	vector<Block*> getweekday_vect() const;
	vector<Block*> getweekrest_vect() const;
	vector<Block*> getblock_avail_vect(string) const;
	vector<Block*> getblocks_assigned() const;
	int get_block_types_added(int) const;
	int check_all_block_types_added() const;
	int get_LOW_assigned(int, int, int) const;
	int get_num_PL_assigned();
	void print_assigned_LOW() const;
	
	
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
	void setRot(int);
	void setWeekend_week(int);
	void setStand_in_avail();
	void set_block_types_added(int,int);
	void set_LOW_assigned(int,int,int,int);
	void clear_cost_vector(string); //type as argument "weekend" etc
	
	void createBlocks();
	
	void add_block_avail(string, Block*);
	void add_block_to_worker(string, int, int = 0);
	void init_add_block_to_worker();
// 	void add_block_to_worker(int, string type = ""); //or " "?
// 	struct cost_comp{
// 		bool operator()(Worker const* lhs, Worker const* rhs) const{
// 			return lhs->get_tot_cost() < rhs->get_tot_cost();
// 		}
// 	};
// 	int get_tot_cost() const; //Calculates the cost of inserting a week block to the current solution
	void calculate_week_cost(Block*, string, int[5][7][4][4], int[5][7][4][4], int[5][7][4][4], int[5], int);
	int calculate_PL_cost(Block*);
	int calculate_demand_cost(Block*, string, int[5][7][4][4], int[5][7][4][4], int[5][7][4][4], int);
	int calculate_stand_in_cost(Block*, string, int);
	int calc_temp_cost(int,int,int,int,int, int[5][7][4][4], int[5][7][4][4]);
	int calculate_num_wends_cost(Block*);
	int calculate_HB_assign_cost(Block*, int[5]);
	

	vector<Weekend_cost> getWeekend_cost_vector() const;
	vector<Weekrest_cost> getWeekrest_cost_vector() const;
	vector<Weekday_cost> getWeekday_cost_vector() const;
	
	
	

};





#endif
