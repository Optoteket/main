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
	  current_demand[i][j][k][l] = 0;
	  //Reset num avail workers
	  for (int m=0; m<=Bokb; m++){
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
  find_lib_workers();
  find_ass_workers();

  // worker_list = vector<Worker>();
  //weekend_workers = vector<Worker*>();

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
  set_weekend_tasks();
  print_avail_demand_diff();
  //print_current_demand();
  set_tasks();

 }


/************* Library function: set evening tasks ************/

void Library::set_tasks(){
  
  find_task_costs(Lib);
    //Find cost_remaining_tasks
    //

}

// void Library::find_avail_lib(int week, int day, int shift, Shift* shift){

//   for (int i =0; i < (int) lib_workers.size(); i++){
//     if (lib_workers[i]->get_avail() < 0 ){
//       shift->shift_worker->worker->lib_workers[i];
//       shift->avail_workers.push_back(&shift_workerlib_workers[i]);
//     }
//   }
// }

void Library::print_task_costs(){
  for (int i=0; i < (int) task_list.size(); i++){
    cout << task_list[i].get_cost() << endl;
  }
}

void min_cost_element(){
  
}

void Library::find_task_costs(int type){
  
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_DAYS-2; d++){
      for(int s=0; s<NUM_SHIFTS; s++){
	if(!(s == 3 && d == 4)){
	  if(type == Lib){
	    int demand = worker_demand[w][d][s][Info];
	    if(demand > 0){
	      //cout << "Demand of librarians!" << endl;
	      int avail_demand_diff = num_avail_workers[Lib][w][d][s] - current_demand[w][d][s][Info];

	      //Create a task, push to list
	      Task task {Lib,w,d,s,demand,avail_demand_diff,&lib_workers};
	      task_list.push_back(task);

	      //Sort tasks according to cheapest
	      //Print cost of tasks
	    }
	  }
	}
      }  
    } 
  }
  print_task_costs();
}

/************* Library function: update avail demand ************/

void Library::weekend_update_avail_demand(int pos, int weekend, int task){
  //Saturaday
  dec_current_demand(weekend, 5, 0, task);
  dec_num_avail_workers(pos, weekend, 5, 0);

  //Sunday
  dec_current_demand(weekend, 6, 0, task);
  dec_num_avail_workers(pos, weekend, 6, 0);

  //Fiday if HB  
  if (task != HB){
    dec_current_demand(weekend, 4, 3, task);
    dec_num_avail_workers(pos, weekend, 4, 3);
  }

}

/**************  Library function: set weekend tasks ***********/

void Library::set_weekend_tasks(){

  if(staff_work_whole_weekends){
    //Set librarian weekends
    int demand;
    int next_worker = 0;
    vector<Worker*> list = weekend_lib;
    int num_workers = (int) list.size();

    for (int j=Lib; j > no_worker; --j){
      for(int i = NUM_TASKS; i >=0; --i){
	//If done with librarians, start with assistants
	if (next_worker >= num_workers){
	  list = weekend_ass;
	  next_worker = 0;
	  num_workers =  (int) list.size();
	  break;
	}
	for(int w=0; w<NUM_WEEKS; w++){
	  if (next_worker >= num_workers){
	    break;
	  }
	  demand = get_current_demand(w,5,0,i);
	  for (int d=0; d<demand; d++){
	    Worker* worker = list[next_worker];
	    worker->set_weekend_task(i);
	    weekend_update_avail_demand(j, w, i);
	    worker->display_tasks();
	    //worker->display_all_current_avail();
	    next_worker++;
	    if (next_worker >= num_workers){
	      break;
	    }
	  }
	}
      }
    }
  }
  else cout << "Error: in set_weekend_tasks. Not implemented feature!" << endl;

  //print_current_demand();
  //print_avail_demand_diff();
    //display_worker_avail();

 // cout << "Changed schedule workers:" << endl;
 // cout << "Num changed workers: " << changed_schedule.size() << endl;
 // for (int i=0; i < (int) changed_schedule.size(); i++){
 //   cout << changed_schedule[i]->get_ID() << endl;
 //  }

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

  //worker.display_tasks();
}



/************ Library function: weekend workers *****/

void Library::find_weekend_workers(){
  for(int i = 0; i < (int) worker_list.size(); i++){
    Worker worker = worker_list[i];
    //cout << worker.get_avail(w,d,s) << endl;
    if (worker.get_weekend().compare("weekend") != (int) worker.get_weekend().npos){
      if (worker.get_pos().find("lib",0,3) == 0){
	weekend_lib.push_back(&worker_list[i]);
      }
      else if(worker.get_pos().find("ass",0,3) == 0){
	weekend_ass.push_back(&worker_list[i]);	
      }
      else cout << "Error: in find_weekend_workers. No worker type." << endl;
      weekend_workers.push_back(&worker_list[i]); 
      //cout << "Weekend worker ID: " << worker.get_ID() << endl;
    }
    //else if (!worker.get_weekend().compare("no_weekend")) cout << "Error: in find_weekend_work." << endl;
  }


  // cout << "Weekend workers:" << endl;
  // for (int i=0; i < weekend.size(); i++){
  //   cout << weekend[i]->get_ID() << endl;
  // }

  cout << "Num of weekend workers: " << weekend_workers.size() << endl;
  cout << "Num of lib weekend workers: " << weekend_lib.size() << endl;
  cout << "Num of ass weekend workers: " << weekend_ass.size() << endl;
}

/************ Library function: lib workers *****/

void Library::find_lib_workers(){
  for(int i = 0; i < (int) worker_list.size(); i++){
    Worker worker = worker_list[i];
    if (worker.get_pos().find("lib",0,3) == 0){
      lib_workers.push_back(&worker_list[i]); 
    }
  }

  cout << "Num of lib workers: " << lib_workers.size() << endl;
}

/************ Library function: ass workers *****/

void Library::find_ass_workers(){
  for(int i = 0; i < (int) worker_list.size(); i++){
    Worker worker = worker_list[i];
    if (worker.get_pos().find("ass",0,3) == 0){
      ass_workers.push_back(&worker_list[i]); 
    }
  }

  cout << "Num of ass workers: " << ass_workers.size() << endl;
}

/****************** Library function: check_weekend_demand ***/

//Check if demand on weekend is higher or lower than number of weekend workers
int Library::check_weekend_demand(){
  int weekend_demand = 0;
  
  for (int i=0; i < NUM_WEEKS; i++){
    for (int j=0; j < NUM_SHIFTS; j++){
      for (int k=Exp; k <= BokB; k++){
	weekend_demand += worker_demand[i][5][j][k];
      }
    }
  }

  if (weekend_demand < (int) weekend_workers.size()) return weekend_demand;
  else return weekend_workers.size();

}

/************ Library function: shuffle workers  *****/

int myrandom (int i) {return rand()%i;}

void Library::shuffle_workers(){
  // vector<Worker*> shuffled_list;
  // shuffled_list = weekend_workers;
  // random_shuffle(shuffled_list.begin(), shuffled_list.end(), myrandom);

  //vector<Worker*> shuffled_list_lib;
  //shuffled_list_lib = weekend_lib;
  random_shuffle(weekend_lib.begin(), weekend_lib.end(), myrandom);

  //vector<Worker*> shuffled_list_ass;
  //shuffled_list_ass = weekend_ass;
  random_shuffle(weekend_ass.begin(), weekend_ass.end(), myrandom);

  //Redistribute weekends
  for (int i=0; i < check_weekend_demand(); i++){
    int index;
    //Distribute librarian weekends first
    if (i < (int) weekend_lib.size()){
      index = i;
      weekend_lib[index]->set_weekend((i % NUM_WEEKS) + 1);
    }
    //Distribute assistant weekend second
    else{
      index=i-weekend_lib.size();
      weekend_ass[index]->set_weekend((i % NUM_WEEKS) + 1);
    }
    //cout << weekend_workers[i]->get_weekend() << endl;
  }

}


/************ Library function: num avail workers *****/

void Library::find_num_avail_workers(){

  //Reset available workers
  for(int t = Exp; t <= Info; t++){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  num_avail_workers[t][w][d][s] = 0;
	}
      }
    }
  } 
 
  //Add available workers
  for(int i = 0; i < (int) worker_list.size(); i++){	
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  //cout << worker.get_avail(w,d,s) << endl;
	  if (worker_list[i].get_avail(w,d,s) == Lib){
	    num_avail_workers[Lib][w][d][s]++; 
	  }
	  else if (worker_list[i].get_avail(w,d,s) == Ass){
	    num_avail_workers[Ass][w][d][s]++; 
	  }
	}
      }
    } 
  }
}

/************ Library function: cost, avail demand *****/

bool Library::demand_filled(){
  find_num_avail_workers();

  //Find diff between avail and demand for librarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_DAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	avail_demand_diff[w][d][s] =  num_avail_workers[Lib][w][d][s] - worker_demand[w][d][s][Info] - worker_demand[w][d][s][HB]; 	
	if (avail_demand_diff[w][d][s] < 0) {
	  return false;
	}  
      }
    }
  }

  //Find diff between avail and demand for assistants
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_DAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	avail_demand_diff[w][d][s] +=  num_avail_workers[Ass][w][d][s] - worker_demand[w][d][s][Exp] - worker_demand[w][d][s][PL];
	if (avail_demand_diff[w][d][s] < 0) {
	   return false;
	 }
      }
    }
  }


  return true;
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
    try{
      if (input_vector.size() == 5){
	int week = atoi(input_vector[0].c_str())-1;
	int day = atoi(input_vector[1].c_str())-1;
	int shift =  atoi(input_vector[2].c_str())-1;
	string task = input_vector[3];
	int num_workers = atoi(input_vector[4].c_str());

	set_demand(week, day, shift, task, num_workers);

      }
      else cout << "Error: wrong number of values from demand file."<< endl;
    } catch(invalid_argument&) {
      cout << "Error: avail argument not of right type" << endl;
    }
    catch(out_of_range&) {
      cout << "Error: avail argument out of range" << endl;
    }
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

int Library::get_current_demand(int week, int day, int shift, int task){
  return current_demand[week][day][shift][task];
}

/************ Library set functions ************/

void Library::dec_num_avail_workers(int pos, int week, int day, int shift){
  if (num_avail_workers[pos][week][day][shift]-1 >= 0){
    num_avail_workers[pos][week][day][shift]--;
  }
  else cout << "Error: in dec_num_avail_workers, not enough available workers!" << endl;
}

void Library::dec_current_demand(int week, int day, int shift, int task){
  if (current_demand[week][day][shift][task]-1 >= 0){
    current_demand[week][day][shift][task]--;
  }
  else cout << "Error: in dec_current_demand, not enough demand!" << endl;
}

void Library::dec_current_weekend_demand(int weekend, int task){
  dec_current_demand(weekend, 5, 0, task);
  dec_current_demand(weekend, 6, 0, task);

  if (task != HB){
     dec_current_demand(weekend, 4, 3, task);
  }
}

void Library::set_demand(int week, int day, int shift, int task, int value){
  worker_demand[week][day][shift][task] = value;
  current_demand[week][day][shift][task] = value;
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
  else if (task == "BokB"){
    enum_task = BokB;
    //Not added feature yet.
  }
  else {
    cout << "Error: invalid task type in set_demand." << endl;
    enum_task = no_task;
  }

  worker_demand[week][day][shift][enum_task] = value;
  current_demand[week][day][shift][enum_task] = value;
} 

/*********************************************************/
/****************** PRINT FUNCTIONS **********************/
/*********************************************************/
void Library::print_demand(){
  cout << "Library demand of workers" << endl;
  cout << "Tasks: Exp, Info, PL, HB, BokB (without no_task)" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
    	for (int l=Exp; l< NUM_TASKS; l++){
	  cout << worker_demand[i][k][j][l] << " ";
	}
	cout << "   ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

void Library::print_current_demand(){
  cout << "Library demand of workers" << endl;
  cout << "Tasks: Exp, Info, PL, HB, BokB (without no_task)" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
    	for (int l=Exp; l< NUM_TASKS; l++){
	  cout << current_demand[i][k][j][l] << " ";
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
      for(int m = Ass; m<=Lib; m++){
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




