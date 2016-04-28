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
vector<Block*> Worker::getweekend_vect() const{
	return weekend_blocks_avail;
}
vector<Block*> Worker::getweekday_vect() const{
	return weekday_blocks_avail;
}
vector<Block*> Worker::getweekrest_vect() const{
	return weekrest_blocks_avail;
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
vector<Worker::Weekend_cost> Worker::getWeekend_cost_vector(){
	return weekend_cost_vector;
}
vector<Worker::Weekrest_cost> Worker::getWeekrest_cost_vector() const{
	return weekrest_cost_vector;
}
vector<Worker::Weekday_cost> Worker::getWeekday_cost_vector() const{
	return weekday_cost_vector;
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
		blocks_assigned.at(newWeekend_week) = weekend_blocks_avail.at(week_id); //should use insert at Weekend_week instead of push_back.
	} else if(type == "weekrest"){
		blocks_assigned.at((newWeekend_week+1) % 5) = weekrest_blocks_avail.at(week_id);
	} else if(type == "weekday"){ //Need to know if weekday 1, 2 or 3 shall be inserted!
		if(day == 1){
			blocks_assigned.at((newWeekend_week+2) % 5) = weekday_blocks_avail.at(week_id);
			blocks_assigned.at((newWeekend_week+2) % 5)->setWday_block_number(day);
		} else if(day == 2){
			blocks_assigned.at((newWeekend_week+3) % 5) = weekday_blocks_avail.at(week_id);
			blocks_assigned.at((newWeekend_week+3) % 5)->setWday_block_number(day);
		} else if(day == 3){
			blocks_assigned.at((newWeekend_week+4) % 5) = weekday_blocks_avail.at(week_id);
			blocks_assigned.at((newWeekend_week+4) % 5)->setWday_block_number(day);
		}
	} else {cout << "No match were found in 'add_block_to_worker'" << endl;}
	return;
}


void Worker::calculate_week_cost(Block* blockobj, string type, int diff_in_demand[5][7][4][5],int assigned_libs[5][7][4][4],int assigned_ass[5][7][4][4], int HB_asgn[5]){ //Create one struct object from this function
	int total_cost = 0;
	int PL_cost = 0;
	int demand_cost = 0;
	int stand_in_cost = 0;
	//Weekend specific costs
	int num_wends_five_weeks_cost = 0; //add cost if weekend worker and not assigned any wend
	int wend_demand_cost = 0; //amount of lib/ass that weekend as well as HB demand
	int HB_assigned_cost = 0; //add cost if HB already assigned that weekend (rotation dependent)
	
	if(blockobj->getnum_PL() > 0){
		PL_cost = calculate_PL_cost(blockobj); //check if PL already assigned that day and if worker avail for more PL assignments
	}
	if(blockobj->getnum_Blocks() > 0){
		demand_cost = calculate_demand_cost(blockobj, diff_in_demand, assigned_libs, assigned_ass);
	}
	stand_in_cost = calculate_stand_in_cost(blockobj, type);
	num_wends_five_weeks_cost = calculate_num_wends_cost(blockobj);
// 	wend_demand_cost = calculate_wend_demand_cost(blockobj);
	HB_assigned_cost = calculate_HB_assign_cost(blockobj, HB_asgn);
	if(type == "weekrest"){
		total_cost = PL_cost + demand_cost + stand_in_cost;
		cout << "Total_cost: " << total_cost << endl;
		Weekrest_cost weekrest_block;
		weekrest_block.wrest_cost = total_cost;
		weekrest_block.block = blockobj;
		weekrest_cost_vector.push_back(weekrest_block);
		cout << "size is now: " << weekrest_cost_vector.size() << endl;
	} else if(type == "weekday"){
		total_cost = PL_cost + demand_cost + stand_in_cost;
		cout << "Total_cost: " << total_cost << endl;
		Weekday_cost weekday_block;
		weekday_block.wday_cost = total_cost;
		weekday_block.block = blockobj;
		weekday_cost_vector.push_back(weekday_block);
		cout << "size is now: " << weekday_cost_vector.size() << endl;
	} else if(type == "weekend"){
		total_cost = PL_cost + demand_cost + stand_in_cost + num_wends_five_weeks_cost + wend_demand_cost + HB_assigned_cost;
		cout << "Total_cost: " << total_cost << endl;
		Weekend_cost weekend_block;
		weekend_block.wend_cost = total_cost;
		weekend_block.block = blockobj;
		weekend_cost_vector.push_back(weekend_block);
		cout << "size is now: " << weekend_cost_vector.size() << endl;
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
		temp_cost += -PL_GOOD_COST*block->getnum_PL(); //Negative cost!
	}
	if(temp_cost != 0){cout << "in calculate_PL_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calculate_demand_cost(Block* block, int diff_in_demand[5][7][4][5], int assigned_libs[5][7][4][4], int assigned_ass[5][7][4][4]){
	int temp_cost = 0;
	for(int d=0; d<block->getNUM_DAYS()-2; d++){ //Only weekdays
		for(int s=0; s<block->getNUM_SHIFTS(); s++){
			int w = (newWeekend_week+block->getWday_block_number()+1) % 5; //The week in consideration. WORKS FOR WEEKEND?
			if(block->getTask(d,s,1) == 1){ //get all "Block" tasks (j = 1 here)
				cout << "here i am d = " << d << " s = " << s << endl;
				//if type == "weekend"
				cout << "diff_in_demand = " << diff_in_demand[w][d][s][0]-1 << endl;
				if(diff_in_demand[w][d][s][0]-1 > 0){ //Add negative cost when positive demand_differ (too few workers assigned)
					if(s == 0){ //certain demand first shift
						temp_cost += calc_temp_cost(2,w,d,s,assigned_libs,assigned_ass);
						//Costs for TOO FEW WORKERS (negative)
						temp_cost += -DEMAND_FEW_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-4);
					}
					else{ //regular demand all other shifts
						temp_cost += calc_temp_cost(3,w,d,s,assigned_libs,assigned_ass);
						//Costs for TOO FEW WORKERS
						temp_cost += -DEMAND_FEW_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-6);
					}
				}
				else if(diff_in_demand[w][d][s][0]-1 < 0){ //Add cost when negative demand_differ (too many workers assigned)
					if(s == 0){ //certain demand first shift
						temp_cost += calc_temp_cost(2,w,d,s,assigned_libs,assigned_ass);
						//Costs for TOO MANY WORKERS
						temp_cost += DEMAND_MANY_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-4);
					}
					else{ //regular demand all other shifts
						temp_cost += calc_temp_cost(3,w,d,s,assigned_libs,assigned_ass);
						//Costs for TOO MANY WORKERS
						temp_cost += DEMAND_MANY_TOT; //*(assigned_libs[w][d][s][1]+assigned_ass[w][d][s][1]+1-6);
					}
				}
			}
			if(block->getTask(d,s,2) == 1){ //get all "PL" tasks
				if(diff_in_demand[w][d][s][1]-1 < 0){
					if(newQual.compare(0,3,"lib") == 0){
						temp_cost += DEMAND_PL_OVERSTAFF_LIB;
					}
					else if(newQual.compare(0,3,"ass") == 0){
						temp_cost += DEMAND_PL_OVERSTAFF_ASS;
					}
				}
			}
			if(block->getTask(d,s,0) == 1){ //get all "no task" tasks
				//Add a lower cost if diff_in_demand for all shifts and tasks that day is < 0
				//Add a higher cost if diff_in_demand for all shifts and tasks that day is > 0
				//NEW: Add no costs for this? Due to negative costs exist now
			}
			
		}
	}
	if(temp_cost != 0){cout << "in calculate_demand_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calc_temp_cost(int demand, int w, int d, int s, int assigned_libs[5][7][4][4], int assigned_ass[5][7][4][4]){
	int tmp_cst = 0;
	//Costs for LIBRARIANS
	if(newQual.compare(0,3,"lib") == 0 && assigned_libs[w][d][s][1]+1 < demand){
		tmp_cst = -DEMAND_FEW_LIBS;  //*(demand-assigned_libs[w][d][s][1]) added if steeper steps if further away from demand
	}
	else if(newQual.compare(0,3,"lib") == 0 && assigned_libs[w][d][s][1]+1 > demand){
		tmp_cst = DEMAND_MANY_LIBS;
	}
	//Costs for ASSISTANTS
	if(newQual.compare(0,3,"ass") == 0 && assigned_ass[w][d][s][1]+1 < demand){
		tmp_cst = -DEMAND_FEW_ASS;
	}
	else if(newQual.compare(0,3,"ass") == 0 && assigned_ass[w][d][s][1]+1 > demand){
		tmp_cst = DEMAND_MANY_ASS;
	}
	return tmp_cst;
}

int Worker::calculate_stand_in_cost(Block* block, string type){
	int temp_cost = 0;
	for(int d=0; d<block->getNUM_DAYS()-2; d++){
		if(type == "weekday"){
			//Assign cost if 'ruining' a stand-in
			if(block->not_assigned(d) == 0 && stand_in_avail[2][d] == 1){ //week == 2 means weekday week
				temp_cost += STAND_IN_COST;
			}
		} else if(type == "weekrest"){
			//Assign cost if 'ruining' a stand-in
			if(block->not_assigned(d) == 0 && stand_in_avail[1][d] == 1){ //week == 1 means weekrest week
				temp_cost += STAND_IN_COST;
			}
		}
	}
	if(temp_cost != 0){cout << "in calculate_stand_in_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calculate_num_wends_cost(Block* block){ //Add a cost to first block since it has no weekends assigned (for weekend workers)
	int temp_cost = 0;
	int count = 0;
	if(newWeekend.compare(0,7,"weekend") == 0){
		for(int d=5; d<6; d++){
			if(block->getTask(d,0,0) == 1){count++;} //Count if empty task
		}
		if(count == 2){temp_cost = NO_WEEKEND_COST;}
	}
	if(temp_cost != 0){cout << "in calculate_num_wends_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

int Worker::calculate_HB_assign_cost(Block* block, int HB_assigned[5]){ //add cost if avail for HB and is weekend worker for blocks with HB.
	int temp_cost = 0;
	if(newQual.compare(0,3,"lib") == 0 && newWeekend.compare(0,7,"weekend") == 0 && (newHB.compare(0,11,"standard_HB") == 0 || newHB.compare(0,7,"only_HB") == 0) ){
		if(block->getTask(5,0,3) == 1 && block->getTask(6,0,3) == 1){ //checking if HB assigned to block
			int w = newWeekend_week; //the week where the weekend work occurs (after rotation)
			if(HB_assigned[w] == 1){
				//Add cost if librarian, weekend worker, available for HB and HB already assigned that week.
				temp_cost = HB_ASSIGNED_COST;
			}
		}
	}
	if(temp_cost != 0){cout << "in calculate_HB_assign_cost. Temp_cost is: " << temp_cost << endl;}
	return temp_cost;
}

// int Worker::calculate_wend_demand_cost(Block* block){ //check demand cost for "Block" 
// 	int temp_cost = 0;
// 	
// }





