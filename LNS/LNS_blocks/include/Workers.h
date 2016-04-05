#ifndef __WORKERS_H_INCLUDED__
#define __WORKERS_H_INCLUDED__


using namespace std;

class Worker {
public:
	//Default Constructor
	Worker();
	
	//Overload Constructors
	Worker(int, string, string, string, string, string);
	
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
	
	//int getAvail(int, int, int) const;
		//Returns the amount of PL a worker shall be assigned.
// 	string getWeekend() const;
// 		//Returns if the worker is a weekend worker, "Yes" or "No"
// 	string getHB() const;
// 		//Returns "Only", "None" or "Standard" for a worker at HB.
	
	
	//Mutator functions
	void setID(int);
	void setName(string);
	void setBoss(string);
	void setQual(string);
	void setDep(string);
	void setPL(string);
	//void setAvail(); //Input: istream
	
	
	

private:
  //Member variables
  int newID;
  string newName;
  string newBoss;
  string newQual;
  string newDep;
  string newPL;
  //string fileopen = "./src/data/librarystaff5W.txt";
};





#endif
