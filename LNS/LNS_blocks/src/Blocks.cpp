#include "Blocks.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>

Block::Block() {
	newID = 0;
	newWeektype = " ";
	newHB = " ";
	for (int w=0; w< NUM_WEEKS; w++){
		for (int s=0; s< NUM_SHIFTS; s++){
			for (int d=0; d< NUM_DAYS; d++){
				for (int j=0; j<NUM_TASKS; j++){
					tasks_assigned[w][d][s][j] = 0;
				}
			}
		}
	}
}

Block::Block(int id, string weektype, string hb) {
	newID = id;
	newWeektype = weektype;
	newHB = hb;
}

Block::Block(int id) {
	newID = id;
}

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


int Block::getTask(int day, int shift, int tasks) const{ //1 if assigned the task, 0 else
	return tasks_assigned[day][shift][tasks];
}

void Block::getTask_matrix() const{
	//for (int w=0; w< NUM_WEEKS; w++){
	for (int s=0; s< NUM_SHIFTS; s++){
		for (int j=0; j<NUM_TASKS; j++){
			for (int d=0; d< NUM_DAYS; d++){
				cout << tasks_assigned[d][s][j] << " ";
			}
			cout << "\t";
		}
		cout << endl;
	}
		//cout << endl << endl;
	//}
}

void Block::setID(int id) {
	newID = id;
}
void Block::setWeektype(string weektype) {
	newWeektype = weektype;
}
void Block::setHB(string hb) {
	newHB = hb;
}
void Block::setTask(int d, int s, int j, int A) {
	tasks_assigned[d][s][j] = A;
}



