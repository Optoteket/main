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
//Felkällor: input_vector{}, copy constructor

// struct Array2D {
// 	Array2D(){
// 		std::cout <<"Array2D constructed\n";
// 		std::vector<std::vector<int> > Arr(3, std::vector<int>(2, 1));
// 	}
// 	~Array2D() {
// 		std::cout <<"Array2D destroyed\n";
// 		if (Arr != NULL)
// 		{
// 			for (int i = 0; i < 3; i++)
// 			{
// 				delete[]Arr[i];
// 			}
// 			delete[]Arr;
// 		}
// 	}
// };

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
	vector<int> blocked_day_vector;
	for (unsigned int i = 0; i<7; i++){
		blocked_day_vector.push_back(i);
	}
	cout << "Last value of the vector is: " << blocked_day_vector.back() << endl;
	cout << "The day is blocked: " << lib.is_day_blocked(blocked_day_vector, 7) << endl;

	
	lib.createBlockpool();
	cout << "Blocks created in main are: " << lib.getNum_blocks() << endl;
	cout << "Size of block_vector is: " << lib.get_block_vector().size() << endl;
// 	int nr = lib.get_all_day_combinations(1,5);
// 	cout << "Number of day combinations found are123: " << nr << endl;
// 	lib.setNum_day_combinations(lib.get_all_day_combinations(1,5));
// 	cout << "Number of day combinations found are: " << lib.getNum_day_combinations() << endl;
	
	
	
// 	vector<vector<vector<int> > > array3D;
// 	int HEIGHT = 5, WIDTH = 3, DEPTH = 7;
// 	array3D.resize(HEIGHT);
// 	for (int i = 0; i < HEIGHT; ++i) {
// 		array3D[i].resize(WIDTH);
// 
// 		for (int j = 0; j < WIDTH; ++j){
// 			array3D[i][j].resize(DEPTH);
// 		}
// 	}
// 	
// 	if (array3D != NULL)
// 	{
// 		for (int i = 0; i < HEIGHT; i++){
// 			for (int j = 0; j < WIDTH; i++){
// 				delete[]array3D[i][j];
// 			}
//   			delete[]array3D[i];
// 	  	}
// 		delete[]array3D;
// 	}
// 	Array2D* array;
// 	array = new Array2D[1];
// 	delete[] array;
	
	
	//Put some values in
// 	array3D[1][2][5] = 6;
// 	array3D[3][1][4] = 5;
	//cout << "in here" << endl;
// 	cout << array3D[1][2][5] << endl;
	//cout << "in here" << endl;
	
	
	// 	Block block1(3);
// 	block1.setWeektype("Weekend");
// 	cout << block1.getWeektype() << endl;
	//int combinations = lib.calculate_num_combinations();
	//cout << "Number of combinations found are: " << combinations << endl;
	//myblocks[1].getTask_matrix();
   	//myworkers[38].getAvail_matrix();

	return 0;
}




