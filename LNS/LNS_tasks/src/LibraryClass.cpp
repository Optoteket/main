// Library class

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "LibraryClass.h"
#include "WorkerClass.h"

using namespace std;

/********** Library function: create workers *******/

void Library::create_workers(){
  ifstream worker_file ("../src/data/workers5W.txt");
    
  if (worker_file.fail())
    {
      cout << "Error: Could not read worker file" << endl;
    }

  vector<string> input_vector;
  string input;

  while(getline(worker_file, input)){

    //Create a new worker when all data has been read 
    if(input.size()<2){
       	string worker_position = input_vector[0];
       	int worker_ID = atoi(input_vector[1].c_str());
       	string worker_name = input_vector[2];
       	string worker_department = input_vector[3];
       	string worker_weekend = input_vector[4];
       	string worker_boss = input_vector[5];
       	string worker_PL_type = input_vector[6];
       	string worker_HB_type = input_vector[7];
       	string worker_freeday = input_vector[8];

       	//Create worker
       	Worker worker {worker_position, worker_ID, worker_name, worker_department, worker_weekend, worker_boss, worker_PL_type, worker_HB_type, worker_freeday};


       	input_vector.erase (input_vector.begin(),input_vector.begin()+10);

       	//Read availability, set in worker
       	for (int i=0; i < input_vector.size(); i++){
       	  vector<string> line_vector;
       	  //Take current line
       	  input = input_vector[i];
       	  size_t pos = input.find(",");

       	  //Write all words separated by space to input_vector
       	  while (pos != string::npos){
       	    line_vector.push_back(input.substr(0,pos));
       	    input = input.substr(pos+1);
       	    pos = input.find (",");
       	  }

       	  //Write task to input_vector
       	  pos = input.find(" ");
       	  line_vector.push_back(input.substr(0,pos));
       	  input = input.substr(pos+1);

       	  //Write 0 or 1 to input_vector
       	  pos = input.find(" ");
       	  line_vector.push_back(input.substr(pos+1));
       	  input = input.substr(pos+1);

      	  if (line_vector.size() == 4){
       	    worker.set_avail(atoi(line_vector[0].c_str())-1, atoi(line_vector[1].c_str())-1, atoi(line_vector[2].c_str())-1,  atoi(line_vector[3].c_str()));
       	  }
       	  else cout << "Error: wrong number of arguments from avail file." << endl;

	  
       	}
      
	//worker.print_avail();
	worker_list.push_back(worker);
       	//worker_list.print_avail();
	input_vector.clear();
    }
      
    else{
      // Read all lines for a worker
      input_vector.push_back(input); 
    }
  }
  // for (int i=0; i < worker_list.size(); i++){
  //   worker_list[i].print_avail();
  // }
  
  print_workers();
}

/************ Library function: cost, avail demand *****/

int Library::cost_avail_demand_diff(){

  enum position {
    lib,
    ass
  };

  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_DAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	num_avail[lib][w][d][s]=0; 
	//cout << "Avail!" << endl;
      }
    }
  }
  
  //num_avail[2][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  print_avail_demand_diff();


  for(int i = 0; i < worker_list.size(); i++){
    Worker worker = worker_list[i];
    worker.print_avail();
    //cout << worker.get_pos() << endl;
     if(worker.get_pos().compare("lib")){
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    //cout << worker.get_avail(w,d,s) << endl;
	    if (worker.get_avail(w,d,s) == 1){
	      num_avail[lib][w][d][s] += 1; 
	      //cout << "Avail: ID: " << worker.get_ID() << " " << w << ", " << d << ", " << s << endl;
	      //cout << num_avail[lib][w][d][s] << endl;
	    }
	  }
	}
      }
    }
 
    //Add check if BokB!
    else cout << "Error: undefined worker position in cost_avail_demand_diff." << endl;
  }
  print_avail_demand_diff();
}


/************* Library function: print workers ********/

void Library::print_workers(){
  cout << "Library workers:" << endl;
  for (int i=0; i < worker_list.size(); i++){
    cout << worker_list[i].get_ID() << endl;
  }
}

void Library::print_avail_demand_diff(){
  cout << "Number of available workers (lib):" << endl;
  cout << "Tasks:( Exp,) Info, (PL, HB, BokB)" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
	 cout << num_avail[0][i][k][j] << " ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}


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
  cout << "Library constructor" << endl;
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





