#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h> //Might be needed for exit(1) on some compilers!
#include <sstream>
#include <iomanip>
#include "Workers.h"
#include "Blocks.h"
#include "Library.h"
using namespace std;

int main() {
	//create a list of worker objects. myworkers[0], myworkers[1] etc.
// 	Worker aworker(1, "Ben", "not_boss", "lib", "Child", "Normal_PL", "No_weekends", "HB", "No");
// 	cout << aworker.getName() << endl;
	Library lib;
	lib.createWorkers();
	lib.printDemand();
	lib.getWorker(1).getAvail_matrix();
	lib.printTask_avail();
//	cout << lib.getTask_avail(0,0,0) << endl;
	//lib.createBlockpool();
	cout << "Number of blocks created are: " << lib.getNum_blocks() << endl;
	Block block1(3);
	block1.setWeektype("Weekend");
	cout << block1.getWeektype() << endl;
	
	//myblocks[1].getTask_matrix();
   	//myworkers[38].getAvail_matrix();

	return 0;
}




