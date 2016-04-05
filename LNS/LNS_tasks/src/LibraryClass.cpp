// Library class

#include <vector>
#include <iostream>
#include <vector>
#include <fstream>

#include "LibraryClass.h"

//const int Library::NUM_WEEKS = 5;
//const int Library::NUM_DAYS = 7;

using namespace std;

/********  ************/
void Library::read_demand(){
  vector<string> input_vector;
  string input;  

  ifstream demand_file ("./src/data/demand5W.txt");

  if (demand_file.fail())
    {
      cout << "Error: Could not read failed" << endl;
    }

  //Get line and find first space    
  getline(demand_file, input);
  cout << input << endl;
  input_vector.clear();
  size_t pos = input.find(",");

  //Write all words separated by space to input_vector
  while (pos != string::npos){
    input_vector.push_back(input.substr(0,pos));
    input = input.substr(pos+1);
    cout << input << endl;
    pos = input.find (",");
  }
  //Write last word to input_vector
  input_vector.push_back(input.substr(0,pos));
} 

void Library::print_demand(
			   //int array[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]
){
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
    	for (int l=0; l< NUM_TASKS; l++){
	  cout << week_worker_demand[i][k][j][l] << " ";
	}
	cout << "   ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

Library::Library() {
  cout << "Library " << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
    	for (int l=0; l<NUM_TASKS; l++){

      week_worker_demand[i][j][k][l] = 0;
      //cout << week_worker_demand << endl;
	}
      }
    }
  }
}





