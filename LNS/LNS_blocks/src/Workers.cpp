#include "Workers.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>

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


void Worker::calculate_week_cost(Block* blockobj, string type, int diff_in_demand[5][7][4][5],int assigned_libs[5][7][4],int assigned_ass[5][7][4]){ //Create one struct object from this function
	int total_cost = 0;
	int PL_cost = 0;
	int demand_cost = 0;
	int stand_in_cost = 0;
	if(blockobj->getnum_PL() > 0){
		PL_cost = calculate_PL_cost(blockobj); //check if PL already assigned that day and if worker avail for more PL assignments
	}
	demand_cost = calculate_demand_cost(blockobj, diff_in_demand, assigned_libs, assigned_ass);
	stand_in_cost = calculate_stand_in_cost(blockobj);
	total_cost = PL_cost + demand_cost + stand_in_cost;
	if(type == "weekrest"){
		Weekrest_cost weekrest_block;
		weekrest_block.wrest_cost = total_cost;
		weekrest_block.block = blockobj;
		weekrest_cost_vector.push_back(weekrest_block);
	} else if(type == "weekday"){
		Weekday_cost weekday_block;
		weekday_block.wday_cost = total_cost;
		weekday_block.block = blockobj;
		weekday_cost_vector.push_back(weekday_block);
		
	} else{cerr << "\n\nWrong 'type' as argument in calculate_week_cost. Either 'weekday' or 'weekrest' availabile \n\n" << endl;return;} 
}

int Worker::calculate_PL_cost(Block* block){
	int temp_cost = 0;
	if(newPL.compare(0,11,"standard_PL") == 0 && num_PL+block->getnum_PL() > 3){ //getnum_PL <= 1, num_PL <= 4(?)
		temp_cost += PL_AMOUNT_COST*(num_PL+block->getnum_PL()-3);
	}else if(newPL.compare(0,7,"many_PL") == 0 && num_PL+block->getnum_PL() > 4){ //getnum_PL <= 1, num_PL <= 4(?)
		temp_cost += PL_AMOUNT_COST*(num_PL+block->getnum_PL()-4);
	}else if(newPL.compare(0,7,"many_PL") == 0 && num_PL+block->getnum_PL() < 3){ //getnum_PL <= 1, num_PL <= 4(?)
		temp_cost += PL_AMOUNT_COST*(3-(num_PL+block->getnum_PL()));
	}else{cerr << "Error in compare of string in calculate_PL_cost!!! \n\n\n" << endl; return 0;}
	return temp_cost;
}

int Worker::calculate_demand_cost(Block* block, int diff_in_demand[5][7][4][5], int assigned_libs[5][7][4], int assigned_ass[5][7][4]){
	int temp_cost = 0;
	for(int d=0; d<block->getNUM_DAYS()-2; d++){ //Only weekdays
		for(int s=0; s<block->getNUM_SHIFTS(); s++){
			if(block->getTask(d,s,1) == 1){ //get Block tasks
				int w = (newWeekend_week+block->getWday_block_number()+1) % 5; //The week in consideration
				int demand_diff = diff_in_demand[w][d][s][1];
				if(demand_diff <= 0){
					if(s == 0){
						if(newQual.compare(0,3,"lib") == 0 && assigned_libs[w][d][s] >= 2){ //optimally 2 lib (2 at B)
							temp_cost += DEMAND_COST_OVERQUAL*(assigned_libs[w][d][s]+1-2); //+1 since there are another task in the block obj.
						}
						else if(newQual.compare(0,3,"ass") == 0 && assigned_ass[w][d][s] >= 3){//optimally 3 ass (2 at B, 1 at PL)
							temp_cost += DEMAND_COST_OVERSTAFF*(assigned_libs[w][d][s]+1-3); 
						} else{cerr << "Error in compare of string in calculate_demand_cost!!! \n\n\n" << endl;}
					}
					else{
						if(newQual.compare(0,3,"lib") == 0 && assigned_libs[w][d][s] >= 3){ //optimally 3 lib (3 at B)
							temp_cost += DEMAND_COST_OVERQUAL*(assigned_libs[w][d][s]+1-3); //+1 since there are another task in the block obj.
						}
						else if(newQual.compare(0,3,"ass") == 0 && assigned_ass[w][d][s] >= 3){//optimally 3 ass (3 at B)
							temp_cost += DEMAND_COST_OVERSTAFF*(assigned_libs[w][d][s]+1-3); 
						} else{cerr << "Error in compare of string in calculate_demand_cost!!! \n\n\n" << endl; return 0;}
					}
				}
			}
		}
	}
	return temp_cost;
}

int Worker::calculate_stand_in_cost(Block* block){
	int temp_cost = 0;
	for(int d=0; d<block->getNUM_DAYS()-2; d++){
		if(block->not_assigned(d) == 1 && stand_in_avail[2][d] == 1){ //week == 2 means weekday week
			temp_cost += STAND_IN_COST;
		}
	}
	return temp_cost;
}

void Worker::calculate_weekend_cost(Block* blockobj, int diff_in_demand[5][7][4][5],int assigned_libs[5][7][4],int assigned_ass[5][7][4]){ //Create one struct object from this function
	int total_cost = 0;
	int demand_cost = 0;
	demand_cost = calculate_demand_cost(blockobj, diff_in_demand, assigned_libs, assigned_ass);
	total_cost = demand_cost;
	Weekend_cost weekend_block;
	weekend_block.wend_cost = total_cost;
	weekend_block.block = blockobj;
	weekend_cost_vector.push_back(weekend_block);
}





