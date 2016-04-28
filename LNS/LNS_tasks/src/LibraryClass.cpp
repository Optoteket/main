// Library class

#include "Constants.h"
#include "LibraryClass.h"
#include "WorkerClass.h"

using namespace std;

/************* Library constructor **************/
Library::Library(ofstream* r_file) {
  cout << "Library constructor" << endl;

  //TODO: take files as input
  resfile = r_file;
  task_list = vector<SingleTask> ();

  //Costs
  cost_total_stand_ins.val = 0;
  cost_total_stand_ins.count = 0;

  //Weights
  weight[0] = 2;
  weight[1] = 1;

  //Num avail day workers
  for(int p=0; p<NUM_POSITIONS; p++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	num_avail_day_workers[p][w][d] = 0;
      }
    }
  }

  //Worker demand, current demand, num avail workers, avail demand diff
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
    	for (int l=0; l<NUM_TASKS; l++){
	  //Reset worker demand
	  worker_demand[i][j][k][l] = 0;
	  current_demand[i][j][k][l] = 0;
	  //Reset num avail workers
	  for (int m=no_position; m < NUM_POSITIONS; m++){
	    num_avail_workers[m][i][j][k] = 0;
	    avail_demand_diff[m][i][j][k] = 0;
	  }
	}
      }
    }
  }

  //Read demand from demand file
  read_demand();
  
  //Create workers in library from worker file
  create_workers();

  //Find weekend workers
  find_weekend_workers();
}
/********* Library function: create initial solution ********/

void Library::create_initial_solution(){

  /**************** TESTING **************/

  //Set weekends
  find_all_weekend_tasks();
  cout << "Task list size: " << weekend_task_list.size() << endl;
  for(int h=0; h < (int) weekend_task_list.size(); h++){
    cout << weekend_task_list[h].get_week() << endl;
  }
  print_num_avail_workers();
  set_all_weekend_tasks();

  exit(0);

  while(!compare_avail_demand()){
    cerr << "Demand not filled." << endl;
    find_all_weekend_tasks();
    set_all_weekend_tasks();
  }
  
  print_num_avail_workers();
  print_avail_demand_diff();

  exit(0);

  /**************** END TESTING **************/

  //Loop until a feasible and pseudo-optimal solution is found

  int MAX_WEEKEND_IT = 10;

  while(cost_total_stand_ins.count < MAX_WEEKEND_IT){

    //Find new random solution
    find_all_weekend_tasks();
    set_all_weekend_tasks();
    
    //Find lowest number of stand ins day at library
    if (compare_avail_demand()){

      //Find min num of assistants and librarians
      find_sum_stand_ins();
      int lowest_num_ass = find_min_stand_ins(Ass);
      cout << "Minimum num of assistants: " << lowest_num_ass << endl;
      int lowest_num_lib = find_min_stand_ins(Lib);
      cout << "Minimum num of librarians: " << lowest_num_lib << endl;

      //Find cost for stand ins
      int cost_min_num_stand_ins =  weight[0]*lowest_num_lib + weight[1]*lowest_num_ass;

      //Check if a new maximum num of stand ins is found
      if (cost_min_num_stand_ins > cost_total_stand_ins.val){
  	cost_total_stand_ins.val = cost_min_num_stand_ins;
  	cost_total_stand_ins.count = 0;
      }
      //If the same as before, increment count
      else if (cost_min_num_stand_ins == cost_total_stand_ins.val)
  	cost_total_stand_ins.count++;
    }
  }

  // Distribute rest of tasks
  set_tasks();

  //destroy_weekend(25);
  //repair_weekend();

}


/************ Library function: find sum stand ins *********/

void Library::find_sum_stand_ins(){
  for(int p=0; p<NUM_POSITIONS; p++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	num_avail_day_workers[p][w][d] = 0;
      }
    }
  }

  for(int i=0; i<(int) worker_list.size(); i++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	  if(worker_list[i].get_current_avail_day(w,d) != 0)
	    num_avail_day_workers[worker_list[i].get_pos()][w][d]++;
      }
    }
  }
}

/************* Library function: find min stand ins **********/

int Library::find_min_stand_ins(int type){
  int temp_max = 100;
  int return_val=0;
  int week = 0;
  int day = 0;
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_WEEKDAYS; d++){
      //Temporary cost of stand ins
      int temp_val = weight[0]*num_avail_day_workers[Lib][w][d] + weight[1]*num_avail_day_workers[Ass][w][d];
      //Find minimum cost of stand ins
      if(temp_val < temp_max){
	temp_max = temp_val;
	return_val = num_avail_day_workers[type][w][d];
	week = w;
	day = d;
      }
    }
  }
  cout << type << " type min stand ins for week: " << week << " day: " << day << "." << endl;
  return return_val;
}

/*****************************************************/
/****************** WEEKEND RELATED ******************/
/*****************************************************/



/*********** Library function: find all weekend tasks ************/

void Library::find_all_weekend_tasks(){

  //Remove all weekends for workers
  for (int i=0; i< (int) weekend_workers.size(); i++){
    weekend_workers[i]->remove_weekend();
  }

  //Reset worker demand
  for(int w=0; w <NUM_WEEKS; w++){
    for(int d=0; d <NUM_DAYS; d++){
      for(int s=0; s <NUM_SHIFTS; s++){
	for (int t=Exp; t<NUM_TASKS; t++){
	  current_demand[w][d][s][t] = worker_demand[w][d][s][t];
	}
      }
    }
  }

  //Find statistical information for task cost
  find_num_avail_workers();
  find_avail_demand_diff();

  //Push all weekend tasks to weekend_task_list
  for (int w=0; w <NUM_WEEKS; w++){
    for (int t=Exp; t<NUM_TASKS; t++){
      //Find demand for task
      int weekend_demand = worker_demand[w][sat][0][t];
      //int weekend_demand = get_current_demand(w,sat,0,t);
      if(weekend_demand > 0){

	//Find avail diff for task
	int avail_diff = avail_demand_diff[find_position_req(t)][w][sat][0];

	weekend_task_list.push_back(WeekendTask 
				    {find_position_req(t), w, weekend_demand, avail_diff, t, &worker_list});
      }
    } 
  }
}

/***************** Library function: set all weekend tasks **************/
void Library::set_all_weekend_tasks(){
  int count=0;
  //Sort tasks according to cheapest task
  random_shuffle(weekend_task_list.begin(),weekend_task_list.end());
  sort(weekend_task_list.begin(),weekend_task_list.end());

  while((int) weekend_task_list.size() !=0 ){

    //Place cheapest worker at task
    WeekendTask* current_task = &weekend_task_list[0];
    current_task->place_cheapest_worker(&weekend_workers);
    //cout << "Weekend placed. Position " << current_task->get_placed_worker_pos() << " task type: " << current_task->get_type() << endl;

    //TODO: fix this
    //weekend_update_avail_demand
    //(current_task->get_placed_worker_pos(), current_task->get_week(), current_task->get_type());
    //cerr << count << endl;
    //cout << "Weekend task distributed" << endl;
    count++;

    //Erase task from list of tasks
    if (current_task->get_demand() == 0){
      weekend_task_list.erase(weekend_task_list.begin());
    }
  }
  cout << count << " weekend tasks placed" << endl;

  //Find statistical information for task cost
  find_num_avail_workers();
  find_avail_demand_diff();
}



/*********** Library function: destroy weekends ******/
void Library::destroy_weekend(int percent){
  //Sort according to worker costs
  vector<Worker*> temp_list = weekend_workers;
  sort(temp_list.begin(),temp_list.end(),Worker::p_comp());
  
  //Print sorted workers
  for(int h=0; h < (int) temp_list.size(); h++){
    cout << temp_list[h]->get_cost_sum() << " ID: " <<temp_list[h]->get_ID() << endl;
  }

  //Delete weekend task
  double num_tasks = 0.01*(double)percent*(double)temp_list.size();
  int destroy_amount = (((int)(num_tasks + (double)NUM_WEEKS/2.0)/NUM_WEEKS) *NUM_WEEKS);
  cout << "Num tasks to destroy: "<< destroy_amount << endl;
  for(int i = 0; i<destroy_amount; i++){
    cout << "Destroyed worker: " << temp_list.back()->get_ID() << " Weekend: " << temp_list.back()->get_current_weekend() << endl;;
    destroy_a_weekend(temp_list.back());
    temp_list.pop_back();

    //Add weekend task
  }
}

/*********** Library function: destroy a weekend ******/

void Library::destroy_a_weekend(Worker* worker){
  //Add weekend task to list of tasks to be distributed 
  weekend_task_list.push_back(WeekendTask{worker->get_pos(),worker->get_current_weekend(),1,0,worker->get_weekend_task(), &worker_list});
  
  //Remove task from worker
  worker->remove_weekend();

  //Collect destroyed worker
  dest_wend_workers.push_back(worker);
  
}


/*********** Library function: repair weekend tasks ******/

void Library::repair_weekend(){

  //int total_avail[NUM_WEEKS][NUM_DAYS-2][NUM_SHIFTS];

  WeekendTask* current_task = &weekend_task_list[0];
  current_task->place_cheapest_worker(&dest_wend_workers);

  //Send destroyed workers to weekend_tasks
  //Find cheapest worker for all tasks
  
  //int total_avail[WEEK][DAY][SHIFT] (check if filled)
  //int total_stand_in[WEEK][DAY]
  //find cost

  //Repair for cheapest of all cheapest

}

// /************* Library function: update avail demand ************/

// void Library::weekend_update_avail_demand(int pos, int weekend, int task){
//   //Saturaday
//   dec_current_demand(weekend, sat, 0, task);
//   dec_num_avail_workers(pos, weekend, sat, 0);

//   //Sunday
//   dec_current_demand(weekend, sun, 0, task);
//   dec_num_avail_workers(pos, weekend, sun, 0);

//   //Fiday if HB  
//   if (task != HB || !no_friday_when_HB){
//     dec_current_demand(weekend, fri, 3, task);
//     dec_num_avail_workers(pos, weekend, fri, 3);
//   }

// }

/******************************************************/
/***************** WEEKDAY RELATED ********************/
/******************************************************/

/*********** Library function: find tasks ************/

void Library::find_tasks(int type){
  
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_DAYS-2; d++){
      for(int s=0; s<NUM_SHIFTS; s++){
	if(type == Lib){
	  int demand = current_demand[w][d][s][Info];
	    if(demand > 0){
	      int avail_demand_diff = num_avail_workers[Lib][w][d][s] - current_demand[w][d][s][Info];
	      SingleTask task {Lib,w,d,s,demand,avail_demand_diff,Info,&worker_list};
	      task_list.push_back(task);
	  }
	}
	else if(type == Ass){
	  for (int task_type=Exp; task_type <=PL; task_type++){
	    int demand = current_demand[w][d][s][task_type];
	      if(demand > 0){
	      int avail_demand_diff = num_avail_workers[Ass][w][d][s] + num_avail_workers[Lib][w][d][s] 
		- current_demand[w][d][s][task_type];

	      //Create a task, push to list
	      SingleTask task {Ass,w,d,s,demand,avail_demand_diff,task_type,&worker_list};
	      task_list.push_back(task);
	    }
	  }
	}
      }  
    } 
  }
}


/************* Library function: set tasks ************/
void Library::set_tasks(){
  
  for (int type=Lib; type >=Ass; type--){
    cout << "Type: " << type << endl;

    //Find library tasks to be distributed
    find_tasks(type);
    cout << "Number of tasks: " << task_list.size() << endl;

    //Sort tasks according to cheapest
    sort(task_list.begin(),task_list.end());

    while((int) task_list.size() !=0 ){
      cout << "Task List Size: " << task_list.size() << endl;
      SingleTask* current_task = &task_list[0];
      cout << "Demand at task: " << current_task->get_demand() << " at task type " 
	   << current_task->get_type() << endl;

      //Place cheapest worker at current task
      current_task->place_cheapest_worker();
      //cout << "Type of worker placed: " << worker_type << endl;      

      dec_current_demand
     	(current_task->get_week(), current_task->get_day(),current_task->get_shift(), current_task->get_type());
      dec_num_avail_workers
      	(current_task->get_placed_worker_pos(),  current_task->get_week(), current_task->get_day(), 
      	 current_task->get_shift());

      //Erase task from list of tasks, otherwise sort to get cheapest
      if (current_task->get_demand() == 0){
	task_list.erase(task_list.begin());
      }
      // OBS cost innefficient!
      //else sort(task_list.begin(),task_list.end());
    }
  }
  find_num_avail_workers();
  find_avail_demand_diff();
}

/******************************************************/
/******************* INIT RELATED *********************/
/******************************************************/

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
  Worker worker 
  {worker_position, worker_ID, worker_name, worker_department, 
      worker_weekend, worker_boss, worker_PL_type, worker_HB_type, 
      worker_freeday, worker_avail};
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
      if (worker.get_pos() == Lib){
	weekend_lib.push_back(&worker_list[i]);
      }
      else if(worker.get_pos() == Ass){
	// OLD: (worker.get_pos().find("ass",0,3) == 0){
	weekend_ass.push_back(&worker_list[i]);	
      }
      else cout << "Error: in find_weekend_workers. No worker type." << endl;
      weekend_workers.push_back(&worker_list[i]); 
      //cout << "Weekend worker ID: " << worker.get_ID() << endl;
    }
    //else if (!worker.get_weekend().compare("no_weekend")) cout << "Error: in find_weekend_work." << endl;
  }

  cout << "Num of weekend workers: " << weekend_workers.size() << endl;
  cout << "Num of lib weekend workers: " << weekend_lib.size() << endl;
  cout << "Num of ass weekend workers: " << weekend_ass.size() << endl;
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

/******************************************************/
/****************** OUTPUT RELATED ********************/
/******************************************************/

/************* Library function: write results ******************/
void Library::write_results(){
  if(resfile->is_open())
    {
      for(int h=0; h < (int) worker_list.size(); h++){
	//worker_list[i].get_current_tasks();  
	*resfile << "Worker:" << worker_list[h].get_ID() << endl;
	*resfile << "Weekend:" << worker_list[h].get_current_weekend() << endl;
	for (int j=0; j< NUM_SHIFTS; j++){
	  for (int i=0; i< NUM_WEEKS; i++){
	    for (int k=0; k< NUM_DAYS; k++){
	      *resfile << worker_list[h].get_current_task(i,k,j) << " ";
	    }
	    *resfile << "   ";
	  }
	  *resfile << endl; 
	}
	*resfile << endl << endl;
      

	  	*resfile << "Availability for worker " << worker_list[h].get_ID() << endl;	
		for (int j=0; j< NUM_SHIFTS; j++){
		  for (int i=0; i< NUM_WEEKS; i++){
		    for (int k=0; k< NUM_DAYS; k++){
		      *resfile << worker_list[h].get_current_avail(i,k,j) << " ";
		    }
		    *resfile << "   ";
		  }
		  *resfile << endl; 
		}
		*resfile << endl << endl;
      }
    }
}

/******************************************************/
/****************** DEMAND RELATED ********************/
/******************************************************/


/************ Library function: num avail workers *****/

void Library::find_num_avail_workers(){

  //Reset available workers
  for(int t = Ass; t < NUM_POSITIONS; t++){
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
	   if (worker_list[i].get_current_avail(w,d,s) == BBlib){
	    num_avail_workers[BBlib][w][d][s]++; 
	  }
	  if (worker_list[i].get_current_avail(w,d,s) == Lib){
	    num_avail_workers[Lib][w][d][s]++; 
	  }
	  else if (worker_list[i].get_current_avail(w,d,s) == Ass){
	    num_avail_workers[Ass][w][d][s]++; 
	  }
	}
      }
    } 
  }
}


/************ Library function: avail demand diff  *****/

void Library::find_avail_demand_diff(){

  for(int t=BBlib; t>=Ass; t--){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  if(t == BBlib){
	    avail_demand_diff[t][w][d][s] =  
	      num_avail_workers[BBlib][w][d][s] 
	      -current_demand[w][d][s][BokB]; 	
	  }
	  else if(t == Lib){
	    avail_demand_diff[t][w][d][s] =  
	      num_avail_workers[BBlib][w][d][s] + num_avail_workers[Lib][w][d][s] 
	      -current_demand[w][d][s][Info] - current_demand[w][d][s][HB]; 	
	  }
	  else if (t == Ass){
	    avail_demand_diff[t][w][d][s] = 
	      num_avail_workers[BBlib][w][d][s] + avail_demand_diff[Lib][w][d][s] + num_avail_workers[Ass][w][d][s] 
	      - current_demand[w][d][s][Exp] - current_demand[w][d][s][PL];
	  }
	}
      }
    }
  }
}


/************ Library function: compare avail demand *****/

bool Library::compare_avail_demand(){
  
  //Find available workers
  find_num_avail_workers();
  int diff[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  //Find diff between avail and demand for BBlibrarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	diff[w][d][s] =  num_avail_workers[BBlib][w][d][s] - current_demand[w][d][s][BokB];
	if (diff[w][d][s] < 0) {
	  return false;
	}  
      }
    }
  }
  //Find diff between avail and demand for librarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	diff[w][d][s] +=  num_avail_workers[Lib][w][d][s] - current_demand[w][d][s][Info] - current_demand[w][d][s][HB]; 	
	if (diff[w][d][s] < 0) {
	  return false;
	}  
      }
    }
  }
  //Find diff between avail and demand for assistants and rest of librarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	diff[w][d][s] +=  num_avail_workers[Ass][w][d][s] - current_demand[w][d][s][Exp] - current_demand[w][d][s][PL];
	if (diff[w][d][s] < 0) {
	   return false;
	 }
      }
    }
  }

  find_avail_demand_diff();
  return true;
}


/************* Library get functions **********/
int Library::get_demand(int week, int day, int shift, int task){
  return worker_demand[week][day][shift][task];
}

int Library::get_current_demand(int week, int day, int shift, int task){
  return current_demand[week][day][shift][task];
}


/************ Library dec functions ************/
void Library::dec_num_avail_workers(int pos, int week, int day, int shift){
  if (num_avail_workers[pos][week][day][shift]-1 >= 0){
    num_avail_workers[pos][week][day][shift]--;
  }
  else {
    cerr << "Error: in dec_num_avail_workers, week: "<< week << " day: " << day
	 << " shift: " << shift << " pos: " << pos << ". Not enough available workers!" << endl;
    //cerr << "Available: " << num_avail_workers[pos][week][day][shift] << endl;
  }
}

void Library::dec_current_demand(int week, int day, int shift, int task){
  if (current_demand[week][day][shift][task]-1 >= 0){
    current_demand[week][day][shift][task]--;
  }
  else {
    cerr << "Error: in dec_current_demand, week: "<< week << " day: " << day
	 << " shift: " << shift << ". Not enough demand workers!" << endl;
    //cerr << "Demand: " << current_demand[week][day][shift][task] << endl;
  }
}

/************ Library set functions ************/
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
    cerr << "Error: invalid task type in set_demand." << endl;
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

void Library::print_num_avail_workers(){
  cout << "Total num of available workers (Ass, Lib, BBlib):" << endl;
  
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for(int m = Ass; m< NUM_POSITIONS; m++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << num_avail_workers[m][i][k][j] << " ";
	}
	cout << "    ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}


void Library::print_avail_demand_diff(){
  cout << "Avail demand diff:" << endl;
  cout << "Tasks: Ass tasks (Exp, PL),    Lib tasks (Info, HB),     BBlib tasks (BokB)" << endl;
 
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int t=Ass; t<=BBlib; t++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << avail_demand_diff[t][i][k][j] << " ";
	}
	cout << "    ";
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

void Library::print_task_costs(){
  for (int i=0; i < (int) task_list.size(); i++){
    cout << "Cost of task: " << i << ": "<< task_list[i].get_cost() << ". "<< task_list[i].num_avail_workers() << " avail workers" << endl;
  }
}



