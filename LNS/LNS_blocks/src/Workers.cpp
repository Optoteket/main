#include "Workers.h"

Worker::Worker() {
	newID = 0;
	newName = " ";
	newBoss = " ";
	newQual = " ";
	newDep = " ";
	newPL = " ";
}

Worker::Worker(int id, string name, string boss, string qualification, string department, string pl) {
	newID = id;
	newName = name;
	newBoss = boss;
	newQual = qualification;
	newDep = department;
	newPL = pl;
}

Worker::~Worker() {
	
}

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

