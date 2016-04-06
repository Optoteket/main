// Library class

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "LibraryClass.h"

using namespace std;

/******** Library function: read demand ************/
void Library::read_demand(){
  vector<string> input_vector;
  string input;  
  ifstream demand_file ("../src/data/demand5W.txt");

  if (demand_file.fail())
    {
      cout << "Error: Could not read demand file" << endl;
    }

  while(getline(demand_file, input)){  
    input_vector.clear();
    size_t pos = input.find(",");

    //Write all words separated by space to input_vector
    while (pos != string::npos){
      input_vector.push_back(input.substr(0,pos));
      input = input.substr(pos+1);
      pos = input.find (",");
    }
    //Write task to input_vector
    pos = input.find(" ");
    input_vector.push_back(input.substr(0,pos));
    input = input.substr(pos+1);

    //Write 0 or 1 to input_vector
    pos = input.find(" ");
    input_vector.push_back(input.substr(pos+1));
    input = input.substr(pos+1);

    // for (int i=0; i < input_vector.size(); i++){
    //   cout << input_vector[i] << endl;
    // }

    if (input_vector.size() == 5){
      set_demand(atoi(input_vector[0].c_str())-1, atoi(input_vector[1].c_str())-1, atoi(input_vector[2].c_str())-1,  input_vector[3], atoi(input_vector[4].c_str()));
    }
    else cout << "Error: wrong number of values from demand file."<< endl;
  }

  //Add week one to weeks three and five
  for (int i = 0; i < NUM_DAYS; i++){
    for (int j = 0; j < NUM_SHIFTS; j++){
      for (int k = 0; k < NUM_TASKS; k++){
  	int first_week_value = get_demand(0,i,j,k);
  	set_demand(2,i,j,k,first_week_value);
	set_demand(4,i,j,k,first_week_value);
	int second_week_value = get_demand(1,i,j,k);
	set_demand(3,i,j,k,second_week_value);
      }
    }
  }

}

/************* Library function: get_demand **********/
int Library::get_demand(int week, int day, int shift, int task){
  return week_worker_demand[week][day][shift][task];
}

/************ Library function: set_demand ************/
void Library::set_demand(int week, int day, int shift, int task, int value){
  week_worker_demand[week][day][shift][task] = value;
} 

/************ Library function: set_demand ************/
void Library::set_demand(int week, int day, int shift, string task, int value){
  task_type enum_task;
  if (task == "Exp"){
    enum_task = Exp; 
  }
  else if (task == "Info"){
    enum_task = Info;
  }
  else if (task == "PL"){
    enum_task = PL;
  }
  else if (task == "HB"){
    enum_task = HB; 
  }
  else {
    enum_task = BokB;
    //Not added feature yet.
  }
  week_worker_demand[week][day][shift][enum_task] = value;
} 

/************* Library function print_demand ************/
void Library::print_demand(
){
  cout << "Library demand of workers" << endl;
  cout << "Tasks: Exp, Info, PL, HB, BokB" << endl;
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

/************* Library constructor **************/
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





