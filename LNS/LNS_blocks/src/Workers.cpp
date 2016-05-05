#include "Workers.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include <cmath>

//Default Constructor
Worker::Worker() {
	this->init();
	
}

//Body of the default constructor
void Worker::init(){
	newID = 0;
	newName = " ";
	newBoss = " ";
	newQual = " ";
	newDep = " ";
	newPL = " ";
	newWeekend = " ";
	newHB = " ";
	newFreeday = " ";
	newRot = 0;
	newWeekend_week = 0;
	tasks_assigned = 0;
	num_PL = 0;
	for (int w=0; w<NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				worker_avail[w][d][s] = 0;
				LOW_assigned[w][d][s] = 0;
			}
		}
	}
	for (int w=0; w<NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS-2; d++){
			stand_in[w][d] = 0;
			stand_in_avail[w][d] = 0;
		}
	}
	weekend_blocks_avail = vector<Block*>();
	weekday_blocks_avail = vector<Block*>();
	weekrest_blocks_avail = vector<Block*>();
	weekday_cost_vector = vector<Weekday_cost>();
	weekend_cost_vector = vector<Weekend_cost>();
	weekrest_cost_vector = vector<Weekrest_cost>();
	for (int i=0; i<3; i++){
		block_types_added[i] = 0; //initially no blocks added to person, [0 0 0]. [1 0 0] means Wends added
	}
}

//Copy Constructor
Worker::Worker(const Worker& obj){
	init();
	newID = obj.newID;
	newName = obj.newName;
	newBoss = obj.newBoss;
	newQual = obj.newQual;
	newDep = obj.newDep;
	newPL = obj.newPL;
	newWeekend = obj.newWeekend;
	newHB = obj.newHB;
	newFreeday = obj.newFreeday;
	newRot = obj.newRot;
	newWeekend_week = obj.newWeekend_week;
	tasks_assigned = obj.tasks_assigned;
	num_PL = obj.num_PL;
	for (int w=0; w<NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				worker_avail[w][d][s] = obj.worker_avail[w][d][s];
			}
		}
	}
	for (int w=0; w< NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS-2; d++){
			stand_in[w][d] = obj.stand_in[w][d];
			stand_in_avail[w][d] = obj.stand_in[w][d];
			for(int s=0; s<NUM_SHIFTS; s++){
				LOW_assigned[w][d][s] = obj.LOW_assigned[w][d][s];
			}
		}
	}
	weekend_blocks_avail.reserve(obj.weekend_blocks_avail.size());
	for(unsigned int i=0; i<obj.weekend_blocks_avail.size(); i++){
		weekend_blocks_avail.push_back(obj.weekend_blocks_avail.at(i));
	}
	weekday_blocks_avail.reserve(obj.weekday_blocks_avail.size());
	for(unsigned int i=0; i<obj.weekday_blocks_avail.size(); i++){
		weekday_blocks_avail.push_back(obj.weekday_blocks_avail.at(i));
	}
	weekrest_blocks_avail.reserve(obj.weekrest_blocks_avail.size());
	for(unsigned int i=0; i<obj.weekrest_blocks_avail.size(); i++){
		weekrest_blocks_avail.push_back(obj.weekrest_blocks_avail.at(i));
	}
	for(unsigned int i=0; i<obj.weekend_cost_vector.size(); i++){
		weekend_cost_vector.push_back(obj.weekend_cost_vector.at(i));
	}
	for(unsigned int i=0; i<obj.weekrest_cost_vector.size(); i++){
		weekrest_cost_vector.push_back(obj.weekrest_cost_vector.at(i));
	}
	for(unsigned int i=0; i<obj.weekday_cost_vector.size(); i++){
		weekday_cost_vector.push_back(obj.weekday_cost_vector.at(i));
	}
	
	cout << "\n\n\n\n A copy of worker has been initialized, make sure everything is copied! \n\n\n\n\n" << endl;
}

//Overload Constructor
Worker::Worker(int id, string name, string boss, string qualification, string department, string pl, string weekend, string hb, string free_day) {
	this->init();
	newID = id;
	newName = name;
	newBoss = boss;
	newQual = qualification;
	newDep = department;
	newPL = pl;
	newWeekend = weekend;
	newHB = hb;
	newFreeday = free_day;
}

//Destructor
Worker::~Worker() {
	
}

// *** GET Functions ***
int Worker::getID() const{
	return newID;
}
string Worker::getName() const{
	return newName;
}
string Worker::getBoss() const{
	return newBoss;
}
string Worker::getQual() const{
	return newQual;
}
string Worker::getDep() const{
	return newDep;
}
string Worker::getPL() const{ //Enumerate??
	return newPL;
}
string Worker::getWeekend() const{
	return newWeekend;
}
string Worker::getHB() const{
	return newHB;
}
string Worker::getFreeday() const{
	return newFreeday;
}
int Worker::getAvail(int week, int day, int shift) const{
	return worker_avail[week][day][shift];
}
void Worker::getAvail_matrix() const{
	for (int w=0; w< NUM_WEEKS; w++){
		cout << "Week " << w << endl;
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int d=0; d< NUM_DAYS; d++){
				cout << worker_avail[w][d][s] << " ";
			}
		cout << endl;
		}
		cout << endl;
	}
}
void Worker::print_assigned_LOW() const{
	cout << "weekend for worker " << newID << " occurs at week " << newWeekend_week << endl;
	for (int w=0; w< NUM_WEEKS; w++){
		cout << "LOW assigned week " << w << " for worker " << newID << endl;
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int d=0; d< NUM_DAYS-2; d++){
				cout << LOW_assigned[w][d][s] << " ";
			}
		cout << endl;
		}
		cout << endl;
	}
}
vector<Block*> Worker::getweekend_vect() const{
	return weekend_blocks_avail;
}
vector<Block*> Worker::getweekday_vect() const{
	return weekday_blocks_avail;
}
vector<Block*> Worker::getweekrest_vect() const{
	return weekrest_blocks_avail;
}
vector<Block*> Worker::getblock_avail_vect(string type) const{
	vector<Block*> empty_vect;
	if(type == "weekend"){return weekend_blocks_avail;}
	else if(type == "weekrest"){return weekrest_blocks_avail;}
	else if(type == "weekday"){return weekday_blocks_avail;}
	else{cerr << "Wrong inargument in getblock_avail_vect" << endl; return empty_vect;}
}

vector<Block*> Worker::getblocks_assigned() const{
	return blocks_assigned;
}
int Worker::getRot() const{
	return newRot;
}
int Worker::getWeekend_week() const{
	return newWeekend_week;
}
vector<Worker::Weekend_cost> Worker::getWeekend_cost_vector() const{
	return weekend_cost_vector;
}
vector<Worker::Weekrest_cost> Worker::getWeekrest_cost_vector() const{
	return weekrest_cost_vector;
}
vector<Worker::Weekday_cost> Worker::getWeekday_cost_vector() const{
	return weekday_cost_vector;
}



int Worker::get_block_types_added(int block_nr) const{
	return block_types_added[block_nr];
}
int Worker::check_all_block_types_added() const{
	int count = 0;
	for(int n=0; n<3; n++){
		if(block_types_added[n] == 1){
			count++;
		}
	}
	if(count == 3){return 1;}
	else{return 0;}
}

int Worker::get_LOW_assigned(int w, int d, int s) const{
	return LOW_assigned[w][d][s];
}

int Worker::get_num_PL_assigned(){
	int PL_amount = 0;
	for(unsigned int n=0; n<blocks_assigned.size(); n++){
		PL_amount += blocks_assigned.at(n)->getnum_PL();
	}
	return PL_amount;
}


// *** SET Functions ***
void Worker::setID(int id) {
	newID = id;
}
void Worker::setName(string name) {
	newName = name;
}
void Worker::setBoss(string boss) {
	newBoss = boss;
}
void Worker::setQual(string qual) {
	newQual = qual;
}
void Worker::setDep(string dep) {
	newDep = dep;
}
void Worker::setPL(string pl) {
	newPL = pl;
}
void Worker::setWeekend(string weekend) {
	newWeekend = weekend;
}
void Worker::setHB(string hb) {
	newHB = hb;
}
void Worker::setFreeday(string free_day) {
	newFreeday = free_day;
}
void Worker::setAvail(int w, int d, int s, int A) {
	worker_avail[w][d][s] = A;
}

void Worker::setRot(int rot){
	newRot = rot;
}

void Worker::setWeekend_week(int weekend){
	newWeekend_week = weekend;
}

void Worker::set_block_types_added(int block_type_to_add, int value){
	block_types_added[block_type_to_add] = value;
}

void Worker::set_LOW_assigned(int w, int d, int s, int value){
	LOW_assigned[w][d][s] = value;
}

void Worker::setStand_in_avail(){
	for(int w=0; w<NUM_WEEKS; w++){
		for(int d=0; d<NUM_DAYS-2; d++){
			if(worker_avail[w][d][0] == 1 && worker_avail[w][d][1] == 1 && worker_avail[w][d][2] == 1){
				stand_in_avail[w][d] = 1;
			}
		}
	}
}
void Worker::getStand_in_matrix() const{
	for (int w=0; w< NUM_WEEKS; w++){
		cout << "Stand-in available week " << w << endl;
		for (int d=0; d<NUM_DAYS-2; d++){
			cout << stand_in_avail[w][d] << " ";
		}
		cout << endl;
	}
}

void Worker::clear_cost_vector(string type){
	if(type == "weekend"){weekend_cost_vector.clear();}
	else if(type == "weekrest"){weekrest_cost_vector.clear();}
	else if(type == "weekday"){weekday_cost_vector.clear();}
}


void Worker::add_block_avail(string type, Block* block) { //type == "weekend", "weekday" or "weekrest". Function: Adds a block to block vectors
	if(type == "weekend"){
		weekend_blocks_avail.push_back(block);
	} else if(type == "weekday"){
		weekday_blocks_avail.push_back(block);
	} else if(type == "weekrest"){
		weekrest_blocks_avail.push_back(block);
	} else {cout << "No match were found in 'add_block_avail'" << endl;}
}

void Worker::init_add_block_to_worker(){
	blocks_assigned.push_back(weekend_blocks_avail.at(0)); //Adding the empty week (FIRST ELEMENT in weekend_blocks_avail, but also weekrest and weekday vects)
	return;
}

void Worker::add_block_to_worker(string type, int week_id, int day){
	if(type == "weekend"){
		blocks_assigned.at(newWeekend_week) = weekend_blocks_avail.at(week_id); //add wend block nr 'week_id' to the worker at its wend week
	} else if(type == "weekrest"){
		blocks_assigned.at((newWeekend_week+1) % 5) = weekrest_blocks_avail.at(week_id);
	} else if(type == "weekday"){ //Need to know if weekday 1, 2 or 3 shall be inserted!
		if(day == 1){
			blocks_assigned.at((newWeekend_week+2) % 5) = weekday_blocks_avail.at(week_id);
			blocks_assigned.at((newWeekend_week+2) % 5)->setWday_block_number(day); //What if same block multiple times here?
		} else if(day == 2){
			blocks_assigned.at((newWeekend_week+3) % 5) = weekday_blocks_avail.at(week_id);
			blocks_assigned.at((newWeekend_week+3) % 5)->setWday_block_number(day); //What if same block multiple times here?
		} else if(day == 3){
			blocks_assigned.at((newWeekend_week+4) % 5) = weekday_blocks_avail.at(week_id);
			blocks_assigned.at((newWeekend_week+4) % 5)->setWday_block_number(day); //What if same block multiple times here?
		}
	} else {cout << "No match were found in 'add_block_to_worker'" << endl;}
	return;
}


void Worker::calculate_week_cost(Block* blockobj, string type, int diff_in_demand[5][7][4][4],int assigned_libs[5][7][4][4],int assigned_ass[5][7][4][4], int HB_asgn[5], int count){ //Create one struct object from this function
	int total_cost = 0;
	int PL_cost = 0;
	int demand_cost = 0;
	int stand_in_cost = 0;
	//Weekend specific costs
	int num_wends_five_weeks_cost = 0; //add cost if weekend worker and not assigned any wend
	int HB_assigned_cost = 0; //add cost if HB already assigned that weekend (rotation dependent)
	
	PL_cost = calculate_PL_cost(blockobj);
	demand_cost = calculate_demand_cost(blockobj, type, diff_in_demand, assigned_libs, assigned_ass, count);
	stand_in_cost = calculate_stand_in_cost(blockobj, type, count);
	num_wends_five_weeks_cost = calculate_num_wends_cost(blockobj);
	HB_assigned_cost = calculate_HB_assign_cost(blockobj, HB_asgn);
	if(type == "weekrest"){
		total_cost = PL_cost + demand_cost + stand_in_cost;
// 		cout << "in weekrest, total_cost = " << total_cost << " PL_cost = " << PL_cost << " demand_cost = " << demand_cost << " stand_in_cost = " << stand_in_cost << endl;
// 		cout << "Total_cost: " << total_cost << endl;
		Weekrest_cost weekrest_block;
		weekrest_block.wrest_cost = total_cost;
		weekrest_block.block = blockobj;
		weekrest_cost_vector.push_back(weekrest_block);
	} else if(type == "weekday"){
		total_cost = PL_cost + demand_cost + stand_in_cost;
// 		cout << "in weekrest, total_cost = " << total_cost << " PL_cost = " << PL_cost << " demand_cost = " << demand_cost << " stand_in_cost = " << stand_in_cost << endl;
// 		cout << "Total_cost: " << total_cost << endl;
		Weekday_cost weekday_block;
		weekday_block.wday_cost = total_cost;
		weekday_block.block = blockobj;
		weekday_cost_vector.push_back(weekday_block);
	} else if(type == "weekend"){
		total_cost = PL_cost + demand_cost + stand_in_cost + num_wends_five_weeks_cost + HB_assigned_cost;
// 		cout << "in weekrest, total_cost = " << total_cost << " PL_cost = " << PL_cost << " demand_cost = " << demand_cost << " stand_in_cost = " << stand_in_cost << " num_wends_five_weeks_cost = " << num_wends_five_weeks_cost << "HB_assigned_cost = " << HB_assigned_cost << endl;
// 		cout << "Total_cost: " << total_cost << endl;
		Weekend_cost weekend_block;
		weekend_block.wend_cost = total_cost;
		weekend_block.block = blockobj;
		weekend_cost_vector.push_back(weekend_block);
	}
	else{cerr << "\n\nWrong 'type' as argument in calculate_week_cost. Either 'weekday' or 'weekrest' availabile \n\n" << endl;return;} 
}

int Worker::calculate_PL_cost(Block* block){
	int temp_cost = 0;
	//Assign cost if too many or too few PL are assigned to the worker
	if(newPL.compare(0,11,"standard_PL") == 0 && num_PL+block->getnum_PL() > 3){ //getnum_PL <= 1, num_PL <= 4(?)
		temp_cost += PL_VIOLATE_COST*block->getnum_PL();
	}else if(newPL.compare(0,7,"many_PL") == 0 && num_PL+block->getnum_PL() > 4){ //getnum_PL <= 1, num_PL <= 4(?)
		temp_cost += PL_VIOLATE_COST*block->getnum_PL();
	}else if(newPL.compare(0,7,"many_PL") == 0 && num_PL+block->getnum_PL() < 3){ //getnum_PL <= 1, num_PL <= 4(?)
		temp_cost -= PL_GOOD_COST*block->getnum_PL(); //Negative cost!
	}
// 	if(temp_cost != 0){cout << "in calculate_PL_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calculate_demand_cost(Block* block, string type, int diff_in_demand[5][7][4][4], int assigned_libs[5][7][4][4], int assigned_ass[5][7][4][4], int count){
	int temp_cost = 0;
	int w = 0;
	for(int d=0; d<NUM_DAYS; d++){
		for(int s=0; s<NUM_SHIFTS; s++){
			if(type == "weekrest" || type == "weekday"){w = (newWeekend_week+count+1) % 5;} //The week in consideration
			else if(type == "weekend"){w = newWeekend_week;}
			
			if(block->getTask(d,s,1) == 1){ //get all "Block" tasks (j = 1 here)
				if(diff_in_demand[w][d][s][0]-1 >= 0){ //Add negative cost when positive demand_differ (too few workers assigned)
					if(s == 0){ //certain demand first shift
						if(d == 5 || d == 6){temp_cost += calc_temp_cost(4,3,w,d,s,assigned_libs,assigned_ass);}
						else{temp_cost += calc_temp_cost(2,2,w,d,s,assigned_libs,assigned_ass);}
						//Costs for TOO FEW WORKERS (negative)
						temp_cost -= DEMAND_FEW_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-4);
					}
					else{ //regular demand all other shifts
						temp_cost += calc_temp_cost(3,3,w,d,s,assigned_libs,assigned_ass); //Cost for libs/ass
						//Costs for TOO FEW WORKERS
						temp_cost -= DEMAND_FEW_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-6);
						if(s == 3 && d != 4){ //Fridays excluded in the cost
							temp_cost -= DEMAND_EVENING_COST; //More priority on evenings
						}
					}
					
				}
				else if(diff_in_demand[w][d][s][0]-1 < 0){ //Add cost when negative demand_differ (too many workers assigned)
					if(s == 0){ //certain demand first shift
						if(d == 5 || d == 6){temp_cost += calc_temp_cost(4,3,w,d,s,assigned_libs,assigned_ass);}
						else{temp_cost += calc_temp_cost(2,2,w,d,s,assigned_libs,assigned_ass);}
						//Costs for TOO MANY WORKERS
						temp_cost += DEMAND_MANY_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-4);
					}
					else{ //regular demand all other shifts
						temp_cost += calc_temp_cost(3,3,w,d,s,assigned_libs,assigned_ass);
						//Costs for TOO MANY WORKERS
						temp_cost += DEMAND_MANY_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-6);
					}
				}
			}
			if(block->getTask(d,s,2) == 1){ //get all "PL" tasks
				//Understaffing will never occur when a block with PL is assigned.
				if(diff_in_demand[w][d][s][1]-1 < 0){ //Overstaffing
					if(newQual.compare(0,3,"lib") == 0){
						temp_cost += DEMAND_PL_BAD_LIB;
					}
					else if(newQual.compare(0,3,"ass") == 0){
						temp_cost += DEMAND_PL_BAD_ASS;
					}
				}else if(diff_in_demand[w][d][s][1]-1 == 0){ //Good assignment -> Negative cost!
					if(newQual.compare(0,3,"lib") == 0){
						temp_cost -= DEMAND_PL_GOOD_LIB;
					}
					else if(newQual.compare(0,3,"ass") == 0){
						temp_cost -= DEMAND_PL_GOOD_ASS;
					}
				}
			}
			if(s == 0 && d == 6 && block->getTask(d,s,3) == 1){ //get all "HB" tasks
				if(diff_in_demand[w][d][s][2]-1 < 0){
					temp_cost += DEMAND_HB_OVERSTAFF; //Positive cost if overstaffing HB!
				}
				else if(diff_in_demand[w][d][s][2]-1 == 0){
					temp_cost -= DEMAND_HB_OVERSTAFF; //Negative cost if filling up HB!
				}
			}
// 			if(block->getTask(d,s,0) == 1){ //get all "no task" tasks
// 				//Add a lower cost if diff_in_demand for all shifts and tasks that day is < 0
// 				//Add a higher cost if diff_in_demand for all shifts and tasks that day is > 0
// 				//NEW: Add no costs for this? Due to negative costs exist now
// 			}
			
		}
	}
// 	if(temp_cost != 0){cout << "in calculate_demand_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calc_temp_cost(int demand_lib, int demand_ass, int w, int d, int s, int assigned_libs[5][7][4][4], int assigned_ass[5][7][4][4]){
	int tmp_cst = 0;
	//Costs for LIBRARIANS
	if(newQual.compare(0,3,"lib") == 0 && assigned_libs[w][d][s][0]+1 <= demand_lib){
		tmp_cst = -DEMAND_FEW_LIBS;  //*(demand-assigned_libs[w][d][s][1]) added if steeper steps if further away from demand
	}
	else if(newQual.compare(0,3,"lib") == 0 && assigned_libs[w][d][s][0]+1 > demand_lib){
		tmp_cst = DEMAND_MANY_LIBS;
	}
	//Costs for ASSISTANTS
	if(newQual.compare(0,3,"ass") == 0 && assigned_ass[w][d][s][0]+1 <= demand_ass){
		tmp_cst = -DEMAND_FEW_ASS;
	}
	else if(newQual.compare(0,3,"ass") == 0 && assigned_ass[w][d][s][0]+1 > demand_ass){
		tmp_cst = DEMAND_MANY_ASS;
	}
	return tmp_cst;
}

int Worker::calculate_stand_in_cost(Block* block, string type, int count){
	int temp_cost = 0;
	for(int d=0; d<NUM_DAYS-2; d++){
		if(type == "weekday"){
			//Assign cost if 'ruining' a stand-in
			if(block->not_assigned(d) == 0 && stand_in_avail[1+count][d] == 1){ //week == 2,3 and 4 means weekday week
				temp_cost += STAND_IN_COST;
			}
		} else if(type == "weekrest"){
			//Assign cost if 'ruining' a stand-in
			if(block->not_assigned(d) == 0 && stand_in_avail[1][d] == 1){ //week == 1 means weekrest week
				temp_cost += STAND_IN_COST;
			}
		} else if(type == "weekend"){
			//Assign cost if 'ruining' a stand-in
			if(block->not_assigned(d) == 0 && stand_in_avail[0][d] == 1){ //week == 0 means weekend week
				temp_cost += STAND_IN_COST;
			}
		}
	}
// 	if(temp_cost != 0){cout << "in calculate_stand_in_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calculate_num_wends_cost(Block* block){ //Add a cost to first block since it has no weekends assigned (for weekend workers)
	int temp_cost = 0;
	int count = 0;
	if(newWeekend.compare(0,7,"weekend") == 0){
		for(int d=5; d<7; d++){
			if(block->getTask(d,0,0) == 1){count++;} //Count if empty task
		}
		if(count == 2){temp_cost = NO_WEEKEND_COST;}
	}
// 	if(temp_cost != 0){cout << "in calculate_num_wends_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calculate_HB_assign_cost(Block* block, int HB_assigned[5]){ //add cost if avail for HB and is weekend worker for blocks with HB. Add negative otherwise
	int cost = 0;
	if(newQual.compare(0,3,"lib") == 0 && newWeekend.compare(0,7,"weekend") == 0 && (newHB.compare(0,11,"standard_HB") == 0 || newHB.compare(0,7,"only_HB") == 0) ){
		if(block->getTask(5,0,3) == 1 && block->getTask(6,0,3) == 1){ //checking if HB assigned to block
			if(HB_assigned[newWeekend_week] == 1){
				//Add cost if librarian, weekend worker, available for HB and HB already assigned that week.
				cost += HB_ASSIGNED_COST;
			}else if(HB_assigned[newWeekend_week] == 0){
				cost -= HB_ASSIGNED_COST;
			}
		}
	}
// 	if(cost != 0){cout << "in calculate_HB_assign_cost. cost is: " << cost << endl;}
	return cost;
}






