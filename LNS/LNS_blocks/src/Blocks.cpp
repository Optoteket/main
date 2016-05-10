#include "Blocks.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
//Default constructor
Block::Block() {
	this->init();
	
}

//Body of the default constructor
void Block::init(){
	newID = 0;
	wday_block_number = 0;
	newWeektype = " ";
	newHB = " ";
	num_tasks = 0;
	num_Blocks = 0;
	num_Exp = 0;
	num_Info = 0;
	num_PL = 0;
	num_HB = 0;
	for (int s=0; s< NUM_SHIFTS; s++){
		for (int d=0; d< NUM_DAYS; d++){
			for (int j=0; j<NUM_TASKS; j++){
				tasks_assigned[d][s][j] = 0;
			}
		}
	}
}

//Copy constructor
Block::Block(const Block& obj) {
	newID = obj.newID;
	wday_block_number = obj.wday_block_number;
	newWeektype = obj.newWeektype;
	newHB = obj.newHB;
	num_tasks = obj.num_tasks;
	num_Blocks = obj.num_Blocks;
	num_Exp = obj.num_Exp;
	num_Info = obj.num_Info;
	num_PL = obj.num_PL;
	num_HB = obj.num_HB;
	for (int s=0; s< NUM_SHIFTS; s++){
		for (int d=0; d< NUM_DAYS; d++){
			for (int j=0; j<NUM_TASKS; j++){
				tasks_assigned[d][s][j] = obj.tasks_assigned[d][s][j];
			}
		}
	}
}

//Overload Constructor #1
Block::Block(int id, string weektype, string hb) {
	this->init();
	newID = id;
	newWeektype = weektype;
	newHB = hb;
}

//Overload Constructor #2
Block::Block(int id, string weektype) {
	this->init();
	newID = id;
	newWeektype = weektype;
}

//Overload Constructor #3
Block::Block(int id) {
	this->init();
	newID = id;
}

//Destructor
Block::~Block() {
	
}

int Block::getID() const{
	return newID;
}
string Block::getWeektype() const{
	return newWeektype;
}
string Block::getHB() const{
	return newHB;
}
int Block::getnum_tasks() const{
	return num_tasks;
}
int Block::getnum_Blocks() const{
	return num_Blocks;
}
int Block::getnum_Exp() const{
	return num_Exp;
}
int Block::getnum_Info() const{
	return num_Info;
}
int Block::getnum_PL() const{
	return num_PL;
}
int Block::getnum_HB() const{
	return num_HB;
}
int Block::getTask(int day, int shift, int tasks) const{ //No task, Block, PL, HB, LOW
	return tasks_assigned[day][shift][tasks];
}
void Block::getTask_matrix() const{
	cout << "Block: " << getID() << " The matrices represent the following: No tasks, Block, PL, HB and BokB respectively" << endl;
	for(int s=0; s<NUM_SHIFTS; s++){
		for(int j=0; j<NUM_TASKS; j++){
			for(int d=0; d<NUM_DAYS; d++){
				cout << tasks_assigned[d][s][j] << " ";
			}
			cout << "\t";
		}
		cout << endl;
	}
}
int Block::getNUM_TASKS() const{
	return NUM_TASKS;
}
int Block::getWday_block_number() const{
	return wday_block_number;
}

//Mutator functions
void Block::setID(int id) {
	newID = id;
}
void Block::setnum_tasks() { //Calculate the tasks_assigned matrix.
	int task_count = 0;
	for(int d=0; d<5; d++){ //Only calculating weekday tasks (evenings excluded as well)
		for(int s=0; s<NUM_SHIFTS-1; s++){
			for(int j=1; j<=2; j++){
				if(tasks_assigned[d][s][j] == 1){
					task_count++;
				}
			}
		}
	}
	num_tasks = task_count;
}
void Block::setnum_Blocks(int blocks) {
	num_Blocks = blocks;
}
void Block::setnum_Exp(int exp) {
	num_Exp = exp;
}
void Block::setnum_Info(int info) {
	num_Info = info;
}
void Block::setnum_PL(int pl) {
	num_PL = pl;
}
void Block::setnum_HB(int hb) {
	num_HB = hb;
}

void Block::setWeektype(string weektype) {
	newWeektype = weektype;
}
void Block::setHB(string hb) {
	newHB = hb;
}
void Block::setTask(int d, int s, int j, int A) {
	tasks_assigned[d-1][s-1][j] = A;
}
void Block::setWday_block_number(int wday) {
	wday_block_number = wday;
}

int Block::not_assigned(int d){ //Checking if there are "no task" at day d
	if(tasks_assigned[d][0][0] == 1){return 1;}
	else{return 0;}
}

