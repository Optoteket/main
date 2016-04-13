// Library class

#include "Constants.h"
#include "LibraryClass.h"
#include "WorkerClass.h"

using namespace std;

/************* Library constructor **************/
Library::Library() {

  //TODO: take files as input

  cout << "Library constructor" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
    	for (int l=0; l<NUM_TASKS; l++){
	  //Reset worker demand
	  worker_demand[i][j][k][l] = 0;
	  temp_demand[i][j][k][l] = 0;
	  //Reset num avail workers
	  for (int m=0; m<=bokb; m++){
	    num_avail_workers[m][i][j][k] = 0;
	  }
	}
      }
    }
  }


  //Read demand from demand file
  read_demand();
  print_demand();
  
  //Create workers in library from worker file
  create_workers();
  //display_worker_avail();

  //Categorize workers
  find_weekend_workers();
}

/********* Library function: create initial solution ********/

void Library::create_initial_solution(){

  //Shuffle weekend workers
  shuffle_workers();

  //Loop through schedule until feasible availability found
  while(!demand_filled()){
    shuffle_workers();
    cout << "Demand not filled." << endl;
  }

  print_avail_demand_diff();
  cout << "Demand filled!" << endl;
  //display_worker_avail();

  //Distribute tasks
  //set_weekend_tasks();
  

 }


void Library::set_weekend_tasks(){

  // for(int i = 0; i < subset.weekend_workers.size(); i++){
  //   Worker* worker = subset.weekend_workers[i];
  //   int weekend_index = worker->get_current_weekend()-1;
  //   cout << weekend_index << endl;
    

  //   //Set all librarian weekends
  //   switch (worker->get_avail(weekend_index,4,3))
  //     case 
  //   if(worker->get_avail(weekend_index,4,3) ==2){
  //     worker->set_task(weekend_index,4,3,Info);
  //     if(worker->get_avail(weekend_index,5,0) ==2 && worker->get_avail(weekend_index,6,0) ==2){
  // 	worker->set_task(weekend_index,4,3,Info);
  // 	worker->set_task(weekend_index,5,0,Info);
  // 	worker->set_task(weekend_index,6,0,Info);}
  //   }
  //   //Set all librarian weekends
  //   else if(worker->get_avail(weekend_index,4,3) ==1 &&
  // 	    worker->get_avail(weekend_index,5,0) ==1 &&
  // 	    worker->get_avail(weekend_index,6,0) ==1){
  //     worker->set_task(weekend_index,4,3,Exp);
  //     worker->set_task(weekend_index,5,0,Exp);
  //     worker->set_task(weekend_index,6,0,Exp);
  //   }


  //   worker->display_tasks();
  //   worker->display_avail();
  // }



}



/********** Library function: create workers *******/

void Library::create_workers(){
  ifstream worker_file ("../src/data/workers5W.txt");
    
  if (worker_file.fail())
    {
      cout << "Error: Could not read worker file" << endl;
    }
  //else cout << "Worker file opened." << endl;

  vector<string> input_vector {};
  string input;

  while(getline(worker_file, input)){

    //Create a new worker when all empty line is detected
    if(input.size() < 2){
      create_a_worker(input_vector);
    }
    
    // Read all lines for a worker
    else{
      input_vector.push_back(input); 
    }
  }
}


/********** Library function: create a worker *******/

void Library::create_a_worker(vector<string>& input_vector){

  //Worker identity input
  string worker_position = input_vector[0];
  int worker_ID = atoi(input_vector[1].c_str());
  string worker_name = input_vector[2];
  string worker_department = input_vector[3];
  string worker_weekend = input_vector[4];
  string worker_boss = input_vector[5];
  string worker_PL_type = input_vector[6];
  string worker_HB_type = input_vector[7];
  string worker_freeday = input_vector[8];
  int worker_avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  input_vector.erase (input_vector.begin(),input_vector.begin()+10);
	
  //Availability input
  for (int i=0; i < (int) input_vector.size(); i++){
    vector<string> line_vector {};
    string input = input_vector[i];

    //Week
    size_t pos = input.find(",");
    line_vector.push_back(input.substr(0,pos));
    input = input.substr(pos+1);

    //Day
    pos = input.find (",");
    line_vector.push_back(input.substr(0,pos));
    input = input.substr(pos+1);

    //Task
    pos = input.find(" ");
    line_vector.push_back(input.substr(0,pos));
    input = input.substr(pos+1);

    //Availability
    pos = input.find(" ");
    line_vector.push_back(input.substr(pos+1));	  
    input = input.substr(pos+1);
	  
    try{
      int week = atoi(line_vector[0].c_str())-1;
      int day = atoi(line_vector[1].c_str())-1;
      int task = atoi(line_vector[2].c_str())-1;
      int avail_val = atoi(line_vector[3].c_str());
      if (line_vector.size() == 4){
	worker_avail[week][day][task] = avail_val;
      }
      else cout << "Error: wrong number of arguments from avail file." << endl;
    } 
    catch(invalid_argument&) {
      cout << "Error: avail argument not of right type" << endl;
    }
    catch(out_of_range&) {
      cout << "Error: avail argument out of range" << endl;
    }
	  
  }

  //Create worker
  Worker worker {worker_position, worker_ID, worker_name, worker_department, worker_weekend, worker_boss, worker_PL_type, worker_HB_type, worker_freeday, worker_avail};
  worker_list.push_back(worker);
  input_vector.clear();

  worker.display_tasks();
}



/************ Library function: num weekend workers *****/

void Library::find_weekend_workers(){
  for(int i = 0; i < (int) worker_list.size(); i++){
    Worker worker = worker_list[i];
    //cout << worker.get_avail(w,d,s) << endl;
    if (worker.get_weekend().compare("weekend") != (int) worker.get_weekend().npos){
      subset.weekend_workers.push_back(&worker_list[i]); 
      //cout << "Weekend worker ID: " << worker.get_ID() << endl;
    }
    //else if (!worker.get_weekend().compare("no_weekend")) cout << "Error: in find_weekend_work." << endl;
  }


  // cout << "Weekend workers:" << endl;
  // for (int i=0; i < subset.weekend.size(); i++){
  //   cout << subset.weekend[i]->get_ID() << endl;
  // }

  cout << "Num of weekend workers: " << subset.weekend_workers.size() << endl;

  //shuffle_workers();

}

/****************** Library function: check_weekend_demand ***/

//Check if demand on weekend is higher or lower than number of weekend workers
int Library::check_weekend_demand(){
  int weekend_demand = 0;
  
  for (int i=0; i < NUM_WEEKS; i++){
    for (int j=0; j < NUM_SHIFTS; j++){
      for (int k=Exp; k <= BokB; k++){
	weekend_demand += worker_demand[i][6][j][k];
      }
    }
  }

  if (weekend_demand < (int) subset.weekend_workers.size()) return weekend_demand;
  else return subset.weekend_workers.size();

}

/************ Library function: shuffle workers  *****/

int myrandom (int i) {return rand()%i;}

void Library::shuffle_workers(){
  //int weekends_to_distribute = 0;
  vector<Worker*> shuffled_list;
  shuffled_list = subset.weekend_workers;
  random_shuffle(shuffled_list.begin(), shuffled_list.end(), myrandom);


  //Redistribute weekends
  for (int i=0; i < check_weekend_demand(); i++){
    shuffled_list[i]->set_weekend((i % NUM_WEEKS) + 1);
    //cout << subset.weekend_workers[i]->get_weekend() << endl;
  }

}


/************ Library function: num avail workers *****/

void Library::find_num_avail_workers(){

  for(int t = Exp; t <= Info; t++){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  num_avail_workers[t][w][d][s] = 0;
	}
      }
    }
  } 
 
  for(int i = 0; i < (int) worker_list.size(); i++){
	
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  //cout << worker.get_avail(w,d,s) << endl;
	  if (worker_list[i].get_avail(w,d,s) == lib){
	    num_avail_workers[lib][w][d][s] += 1; 
	  }
	  else if (worker_list[i].get_avail(w,d,s) == ass){
	    num_avail_workers[ass][w][d][s] += 1; 
	  }
	}
      }
    } 
  }
}

/************ Library function: cost, avail demand *****/

bool Library::demand_filled(){
  bool return_var = true;
  find_num_avail_workers();

  //Find diff between avail and demand
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_DAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	avail_demand_diff[w][d][s] =  num_avail_workers[lib][w][d][s] - worker_demand[w][d][s][Info] - worker_demand[w][d][s][HB]; 	
	if (avail_demand_diff[w][d][s] < 0) {
	  return false;
	}  
	avail_demand_diff[w][d][s] +=  num_avail_workers[ass][w][d][s] - worker_demand[w][d][s][Exp] - worker_demand[w][d][s][PL];
	if (avail_demand_diff[w][d][s] < 0) {
	   return false;
	 }
      }
    }
  }
  return return_var;
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

/************* Library get functions **********/
int Library::get_demand(int week, int day, int shift, int task){
  return worker_demand[week][day][shift][task];
}

/************ Library set functions ************/

void Library::set_demand(int week, int day, int shift, int task, int value){
  worker_demand[week][day][shift][task] = value;
} 

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
  worker_demand[week][day][shift][enum_task] = value;
} 

/*********************************************************/
/****************** PRINT FUNCTIONS **********************/
/*********************************************************/
void Library::print_demand(
){
  cout << "Library demand of workers" << endl;
  cout << "Tasks: Exp, Info, PL, HB, BokB" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
    	for (int l=0; l< NUM_TASKS; l++){
	  cout << worker_demand[i][k][j][l] << " ";
	}
	cout << "   ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

void Library::print_workers(){
  cout << "Library workers:" << endl;
  for (int i=0; i < (int) worker_list.size(); i++){
    cout << worker_list[i].get_ID() << endl;
  }
}

void Library::print_avail_demand_diff(){

  cout << "Total num of available workers (lib and ass):" << endl;
  cout << "Tasks:( Exp,) Info, (PL, HB, BokB)" << endl;
  
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for(int m = ass; m<=lib; m++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << num_avail_workers[m][i][k][j] << " ";
	  //cout << avail_demand_diff[i][k][j] << " ";
	}
	cout << "    ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }


  cout << "Avail demand diff:" << endl;
  cout << "Tasks:( Exp,) Info, (PL, HB, BokB)" << endl;
  
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
	//cout << num_avail_workers[m][i][k][j] << " ";
	cout << avail_demand_diff[i][k][j] << "  ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

void Library::print_worker_avail(int id, int w_a[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]){
  cout << "Worker_avail for " << id << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
	cout << w_a[i][k][j] << " ";
      }
      cout << endl;
    }
    cout << endl << endl; 
  }
}


void Library::display_worker_avail(){
  for(int i=0; i < (int) worker_list.size(); i++){
    worker_list[i].display_avail();
  }
}




