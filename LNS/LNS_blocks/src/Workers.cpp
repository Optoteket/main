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
	for (int w=0; w<NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS; d++){
			for (int s=0; s<NUM_SHIFTS; s++){
				worker_avail[w][d][s] = 0;
			}
		}
	}
	for (int w=0; w< NUM_WEEKS; w++){
		for (int d=0; d<NUM_DAYS-2; d++){
			stand_in[w][d] = 0;
		}
	}
// 	weekend_blocks_avail = vector<Block*>();
// 	weekday_blocks_avail = vector<Block*>();
// 	weekrest_blocks_avail = vector<Block*>();
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
	cout << "A copy of worker has been initialized" << endl;
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

void Worker::add_block_avail(string type, Block* block) { //type == "weekend", "weekday" or "weekrest". Function: Adds a block to block vectors
	if(type == "weekend"){
		weekend_blocks_avail.push_back(block);
	} else if(type == "weekday"){
		weekday_blocks_avail.push_back(block);
	} else if(type == "weekrest"){
		weekrest_blocks_avail.push_back(block);
	} else {cout << "No match were found in 'add_block_avail'" << endl;}
}

void Worker::initial_add_blocks_to_workers(){ //Add empty weeks to all workers
	for(int i=0; i<39; i++){
		for(int n=0; n<5; n++){ //add 5 empty blocks per worker
			add_block_to_worker(
		}
	}
}

void Worker::add_block_to_worker(string type, int week_id){
// 	vector<Block*>::iterator it;
	if(type == "weekend"){
// 		it = weekend_blocks_avail.begin();
// 		blocks_assigned.insert(it+newWeekend_week,weekend_blocks_avail.at(week_id));
		blocks_assigned.push_back(weekend_blocks_avail.at(week_id)); //should use insert at Weekend_week instead of push_back.
	} else if(type == "weekrest"){
// 		it = weekrest_blocks_avail.begin();
		blocks_assigned.push_back(weekrest_blocks_avail.at(week_id));
	} else if(type == "weekday"){
// 		it = weekday_blocks_avail.begin();
		blocks_assigned.push_back(weekday_blocks_avail.at(week_id));
	} else {cout << "No match were found in 'add_block_to_worker'" << endl;}
	return;
}




