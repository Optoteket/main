// Library class

//#include "Constants.h"
#include "LibraryClass.h"
//#include "WorkerClass.h"

using namespace std;

/************* Library constructor **************/
Library::Library(ofstream* r_file) {
  cout << "Library constructor" << endl;

  //TODO: take files as input
  resfile = r_file;
  task_list = vector<SingleTask> ();

  //Costs
  library_max_cost = 0;

  //Num avail day workers
  for(int p=0; p<NUM_POSITIONS; p++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	//num_avail_day_workers[p][w][d] = 0;
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
}
/********* Library function: create initial solution ********/

void Library::create_initial_solution(){
  //Clear workers
  worker_list.clear();
  weekend_workers.clear();
  best_sol_workers.clear();

  //Clear task workers
  destroyed_wend_workers.clear();
  destroyed_task_workers.clear();

  //Clear tasks
  task_list.clear();
  weekend_task_list.clear();

  //Clear objective function
  weekend_objective_function.clear();

  //Read demand from demand file
  read_demand();

  //Create workers in library from worker file
  create_workers();

  //Find weekend workers
  find_weekend_workers();

}

/********* Library function: optimize weekends ********/


void Library::optimize_weekends(int iterations, int percent, double weights[3]){
  weekend_objective_function.clear();

  //Destroy and repair all weekends
  destroy_weekend(100, "perm");
  repair_weekend("perm");

  //Find library cost
  set_library_cost("perm", weights);

  //Solution improvement loop
  for (int i=0; i < iterations; i++){

    //Save original solution
    orig_workers.clear();
    for(int j=0; j<(int) worker_list.size(); j++){
      orig_workers.push_back(worker_list[j]); 
    }
    orig_library_cost = library_cost;

    //Save current demand
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int t = 0; t < NUM_TASKS; t++){
	    orig_demand[w][d][s][t] = current_demand[w][d][s][t];
	  }
	}
      }
    }

    //Destroy and repair weekends
    //remove_weekday_tasks();
    //destroy_weekend(percent, "perm");
    //repair_weekend("perm");

    bool feasible = false;
    while(!feasible){
     //Destroy and repair until feasible
      remove_weekday_tasks();

      destroy_weekend(percent, "perm");
      repair_weekend("perm");

      //Place tasks and check feasibility
      place_BokB();
      feasible = compare_avail_demand("perm");
      if(feasible){
	feasible = set_evening_tasks();
      }
    }

    //Calculate library cost of solution
    set_library_cost("perm", weights);
    //temp_library_cost = library_cost;


    //Find exponential cooling
    double T = 0.7*pow(0.96, (double)100.0*i/(1.0*iterations));
    double cost_diff = abs(library_cost - orig_library_cost);
    double exp_val = exp(-(cost_diff/(1.0*T)));
    double random_num = (double)(rand() % 100 +1)*0.01;

    //Accept a solution if better or with exp probability
    if(library_cost >= orig_library_cost || random_num < exp_val){

      //Deteriorating solutions print
      if(random_num < exp_val && !(library_cost >= orig_library_cost)){
      	cerr << "Iteration: "<< (int) weekend_objective_function.size() << " T:" << T 
      	     << " Cost diff:" << cost_diff << " Exponential cooling:"
      	     << exp_val << " Random val: " << random_num << " Library cost: " << temp_library_cost << endl;
      	cerr << "temp_library_cost: " << temp_library_cost << endl;
      	cerr << "library_cost: " << library_cost << endl;
      }

      cerr << "************* Solution accepted ************" << endl;
      //use_temp_solution();

      //Set permanent costs
      //set_library_cost("perm", weights);
      cerr << "library_cost: " << library_cost << endl;

      if(library_cost > library_max_cost){
	library_max_cost = library_cost;
	cerr << "************ Saved best solution: " << library_cost << endl;
	cerr << "Min avail day ass: " << min_avail_day[Ass] << " Min avail day lib: " << min_avail_day[Lib] 
	     << " Min avail ass: " << min_avail[Ass] << " Min avail lib: " 
	     << min_avail[Lib] << endl;
	cerr <<"Library max cost: " << library_max_cost << " Library current cost: " << library_cost << endl;

	//Save globally best solution 
	best_sol_workers.clear();
	for(int j=0; j<(int) worker_list.size(); j++){
	  best_sol_workers.push_back(worker_list[j]); 
	}
      }
    }
    else {
      //Else, take back old solution
      worker_list.clear();
      for(int j=0; j<(int) orig_workers.size(); j++){
	worker_list.push_back(orig_workers[j]); 
      }
      library_cost = orig_library_cost;

      //Take back current demand
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    for(int t = 0; t < NUM_TASKS; t++){
	      current_demand[w][d][s][t] = orig_demand[w][d][s][t];
	    }
	  }
	}
      }
    }
    //Push back library cost
    weekend_objective_function.push_back(library_cost);
    cerr << "avail_day_cost: " << avail_day_cost << endl;
    cerr << "avail_cost: " << avail_cost << endl;
    cerr << "num_avail_cost: " << avail_cost << endl;
    cerr << "Perm library_cost: " << library_cost << endl;
    cout << "Perm library_cost: " << library_cost << endl;
  }
  
  //Overwrite solution if better solution is saved
  if (library_cost < library_max_cost){
    cout << "************ Reload best solution ************" << endl;
    worker_list.clear();
    for(int i=0; i<(int) best_sol_workers.size(); i++){
      worker_list.push_back(best_sol_workers[i]); 
    }

    //Reset current demand
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int t = 0; t < NUM_TASKS; t++){
	    current_demand[w][d][s][t] = worker_demand[w][d][s][t];
	  }
	}
      }
    }

    //Subtract with current workers
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int i=0; i < (int)worker_list.size(); i++){
	    if(worker_list[i].get_current_task(w,d,s) > 0)
	      current_demand[w][d][s][worker_list[i].get_current_task(w,d,s)]--;
	  }
	}
      }
    }

    set_library_cost("perm", weights);
  }

  //Write statistical information
  write_stat();

  print_num_avail_workers();
  print_current_demand();

  cout << "Min avail day ass/lib: " << min_avail[Ass] << ", " << min_avail[Lib] 
       << " Min avail ass/lib: " << min_avail[Ass] << ", "<< min_avail[Lib]
       << " Min num avail ass/lib: " << min_num_avail[Ass] << ", " << min_num_avail[Lib] << endl;
  cout <<"Library max cost: " << library_max_cost << " Library current cost: " << library_cost << endl;
  *resfile << library_cost << endl;
  //destroy_tasks(100,"perm");
  //repair_tasks("perm");
  //set_tasks();
}

/************ Library function: set library costs ***********/

void Library::set_library_cost(string mode, double weight[3]){
  set_avail_day_cost(mode);
  //set_avail_contribution_cost(mode);
  set_avail_cost(mode);
  set_num_avail_cost();
  //int weight_[3];
  //weight_[0]=10;
  //weight_[1]=2;
  //weight_[2]=0;

  if(mode == "perm"){
    library_cost = weight[0]*avail_day_cost
      + weight[1]*avail_cost
      + weight[2]*num_avail_cost
      + (weight[0]/10)*avail_day_average
      + (weight[1]/10)*avail_average
      + (weight[2]/10)*num_avail_average
      ;
    
    //Print cost
    // cerr << "avail_day_cost: " << avail_day_cost << endl;
    // cerr << "avail_cost: " << avail_cost << endl;
    // cerr << "num_avail_cost: " << avail_cost << endl;
    // cout << "Perm library_cost: " << library_cost << endl;
  }
  else if(mode == "temp"){
    temp_library_cost = weight[0]*temp_avail_day_cost 
      + weight[1]*temp_avail_cost
      ;
    //cerr << "temp_avail_day_cost: " << temp_avail_day_cost << endl;
    //cerr << "temp_avail_cost: " << temp_avail_cost << endl;
  } 
}

/************* Library function: set_evening_tasks ************/

bool Library::set_evening_tasks(){
  task_list.clear();
  destroyed_task_workers.clear();

  //Find evening tasks
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_WEEKDAYS; d++){
      for(int t=Exp; t<NUM_TASKS; t++){
	int demand = current_demand[w][d][3][t];
	if(demand > 0){
	  //Find avail (workers with at least min qualification)
	  int min_qual = find_position_req(t);
	  int avail_demand_diff = 0;
	  for(int pos=min_qual; pos < NUM_POSITIONS; pos++){
	    avail_demand_diff += num_avail_workers[pos][w][d][3];
	  }
	  avail_demand_diff -= demand;
	  cout << "Task avail demand diff: " << avail_demand_diff << endl;

	  //Create single task if demand == avail
	  //if(avail_demand_diff == 0){
	    SingleTask task {find_position_req(t),w,d,3,demand,avail_demand_diff,t};
	    task_list.push_back(task);
	    //}
	}
      }
    }
  }
  cout << "Number of tasks to repair: " << task_list.size() << endl;

  //Shuffle and sort according to qualification requirement
  random_shuffle(task_list.begin(), task_list.end());
  sort(task_list.begin(), task_list.end(), Task::max_qual());

  //Find evening workers
  for(int t=0; t<(int) task_list.size(); t++){
    SingleTask* current_task = &task_list[t];
    int week = current_task->get_week();
    int day = current_task->get_day();
    int shift = current_task->get_shift();
    int task = current_task->get_type();
    for(int i=0; i<(int) worker_list.size(); i++){
      Worker* worker = &worker_list[i];
      //Push back all available workers
      if(worker->get_current_avail(week,day,shift) >= current_task->get_qualification()){
	TaskWorker t_worker;
	t_worker.worker = worker;
	t_worker.temp_worker = *worker;
	destroyed_task_workers.push_back(t_worker);
      }
    }
    //Place workers
    current_task->place_workers(&destroyed_task_workers);

    //Check if solution is feasible
    if(current_task->check_feasibility() == false){
      return false;
    }

    destroyed_task_workers.clear();

    //Update current demand
    current_demand[week][day][shift][task] 
      -= current_task->get_demand();
  }
  find_num_avail_workers();
  return true;
}

/************* Library function: remove weekday tasks ************/

void Library::remove_weekday_tasks(){
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	if(!(d==fri and s==3)){
	  for(int i=0; i < (int)worker_list.size(); i++){
	    worker_list[i].remove_task(w,d,s);
	  }
	  for(int t = 0; t < NUM_TASKS; t++){
	    current_demand[w][d][s][t]= worker_demand[w][d][s][t];
	  }
	}
      }
    }
  }
}

/************* Library function: set num avail cost ************/
void Library::set_num_avail_cost(){
  int local_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];
  int min_avail_cost = 100;
  int min_num_ass = 0;
  int min_num_lib = 0;
  int week;
  int day;

  //Reset variables
  for(int p = 0; p < NUM_POSITIONS; p++){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_WEEKDAYS; d++){
	local_avail_workers[p][w][d]=0;	   
      }
    }
  }

  //Find all available librarians and assistants
  for(int i=0; i < (int)worker_list.size(); i++){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_WEEKDAYS; d++){
	bool found = false;
	for(int s = 0; s < NUM_SHIFTS-1; s++){
	  if(!found && worker_list[i].get_current_avail(w,d,3) == no_task){
	    if(worker_list[i].get_current_avail(w,d,s)>=Lib){
	      found = true;
	      local_avail_workers[Lib][w][d]++;
	    }
	    else if(worker_list[i].get_current_avail(w,d,s)==Ass){
	      found = true;
	      local_avail_workers[Ass][w][d]++;
	    }
	  }	   
	}
      }
    }
  }

  num_avail_average = 0.0;
  for(int p = Ass; p <= Lib; p++){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_WEEKDAYS; d++){
	num_avail_average +=local_avail_workers[p][w][d];
      }
    }
  }
  num_avail_average/=(2*NUM_WEEKS*NUM_WEEKDAYS);


    //Find worst day
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	//Temporary cost of stand ins
	int temp_cost = 2.0*local_avail_workers[Lib][w][d] 
	  + 1.0*local_avail_workers[Ass][w][d];
	//Find minimum cost of stand ins
	if(temp_cost < min_avail_cost){
	  min_avail_cost = temp_cost;
	  min_num_ass = local_avail_workers[Ass][w][d];
	  min_num_lib = local_avail_workers[Lib][w][d];
	  week = w;
	  day = d;
	}
      }
    }


    num_avail_cost = min_avail_cost;
    min_num_avail[Ass] = min_num_ass;
    min_num_avail[Lib] = min_num_lib;
    cout << "Perm num avail cost: " << num_avail_cost << ". Ass: " 
	 << min_num_ass << ". Lib: "
	 << min_num_lib << ". week: " << week << " day: " << day << "." << endl;
}


/************ Library function: set avail cost ***********/
void Library::set_avail_cost(string mode){
  //int local_avail_demand_diff[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS][NUM_SHIFTS];
  //int local_demand[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS][NUM_SHIFTS-1];
  int local_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS][NUM_SHIFTS-1];
  int min_avail_cost = 100;
  int min_num_ass = 0;
  int min_num_lib = 0;
  int week;
  int day;
  int shift;

  //Reset variables
  for(int p = 0; p < NUM_POSITIONS; p++){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_WEEKDAYS; d++){
	for(int s = 0; s < NUM_SHIFTS-1; s++){
	  local_avail_workers[p][w][d][s]=0;
	}	   
      }
    }
  }

  //Find all available librarians and assistants
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_WEEKDAYS; d++){
	for(int s = 0; s < NUM_SHIFTS-1; s++){
	  for(int i=0; i < (int)worker_list.size(); i++){
	    if(worker_list[i].get_current_avail(w,d,s)>=Lib
	       && worker_list[i].get_current_avail(w,d,3) == no_task)
	      local_avail_workers[Lib][w][d][s]++;
	    else if(worker_list[i].get_current_avail(w,d,s)==Ass
		    && worker_list[i].get_current_avail(w,d,3) == no_task)
	      local_avail_workers[Ass][w][d][s]++;
	  }	   
	}
      }
    }

  //Adjust with temporary workers
  if (mode == "temp"){
      for(int w = 0; w < NUM_WEEKS; w++){
  	for(int d = 0; d < NUM_WEEKDAYS; d++){
  	  for(int s = 0; s < NUM_SHIFTS-1; s++){
  	    for(int i=0; i<(int) destroyed_wend_workers.size(); i++){
  	      Worker* worker = destroyed_wend_workers[i].worker;
  	      Worker* temp_worker = &destroyed_wend_workers[i].temp_worker;
	      
  	      if(worker->get_current_avail(w,d,s) > 0){
  		local_avail_workers[worker->get_pos()][w][d][s]--; 
  	      }
	
  	      if(temp_worker->get_current_avail(w,d,s) > 0){
  		local_avail_workers[temp_worker->get_pos()][w][d][s]++; 
  	      }
  	    }
  	  }
  	}
      }
  }


  //Find worst day
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_WEEKDAYS; d++){
      for(int s=0; s<NUM_SHIFTS-1; s++){
	//Temporary cost of stand ins
	int temp_cost = 2.0*local_avail_workers[Lib][w][d][s] 
	  + 1.0*local_avail_workers[Ass][w][d][s];
	//Find minimum cost of stand ins
	if(temp_cost < min_avail_cost){
	  min_avail_cost = temp_cost;
	  min_num_ass = local_avail_workers[Ass][w][d][s];
	  min_num_lib = local_avail_workers[Lib][w][d][s];
	  week = w;
	  day = d;
	  shift = s;
	}
      }
    }
  }

  //Write to global variable
  if(mode == "perm"){
    avail_average=0.0;
    for(int p=0; p<NUM_POSITIONS; p++){
      for(int w=0; w<NUM_WEEKS; w++){
	for(int d=0; d<NUM_WEEKDAYS; d++){
	  for(int s=0; s<NUM_SHIFTS-1; s++){
	    num_weekday_avail_workers[p][w][d][s] = local_avail_workers[p][w][d][s];
	    avail_average += local_avail_workers[p][w][d][s];
	  }
	}
      }
    }
    avail_average/=(2*NUM_WEEKS*NUM_WEEKDAYS*NUM_SHIFTS-1);
  }

  if(mode == "temp"){
    temp_avail_cost = min_avail_cost; 
    //cout << "Temp avail cost: " << temp_avail_cost << ". Ass: " 
    //	 << min_num_ass << ". Lib: "
    //	 << min_num_lib << ". week: " << week << " day: " << day << " shift: " << shift << "." << endl;
  }
  if(mode == "perm"){
    avail_cost = min_avail_cost;
    min_avail[Ass] = min_num_ass;
    min_avail[Lib] = min_num_lib;
    cout << "Perm avail cost: " << avail_cost << ". Ass: " 
	 << min_num_ass << ". Lib: "
	 << min_num_lib << ". week: " << week << " day: " << day << " shift: " << shift << "." << endl;
  }

}


/************ Library function: set avail contribution cost *********/

void Library::set_avail_contribution_cost(string mode){
  double local_num_avail_workers_average[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];
  double min_avail_cost = 100.0;
  double min_num_ass = 0.0;
  double min_num_lib = 0.0;
  int week;
  int day;

  for(int w=0; w<NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int p = 0; p < NUM_POSITIONS; p++){
	local_num_avail_workers_average[p][w][d] = 0;
      }
    }
  }

  //Find worker availability contribution shift 0-1
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int i=0; i<(int) worker_list.size(); i++){
	local_num_avail_workers_average[worker_list[i].get_pos()][w][d] 
	  += (double)((double)worker_list[i].get_current_avail(w,d,0)
		      + (double)worker_list[i].get_current_avail(w,d,1)
		      + (double)worker_list[i].get_current_avail(w,d,2)
		      )/(3.0*worker_list[i].get_pos());
      }
    }
  }

  //Find diff for temporarily placed workers
  if(mode == "temp"){
    for(int i=0; i<(int) destroyed_wend_workers.size(); i++){
      Worker* worker = destroyed_wend_workers[i].worker;
      Worker* temp_worker = &destroyed_wend_workers[i].temp_worker;

      for(int w=0; w<NUM_WEEKS; w++){
	for(int d=0; d<NUM_WEEKDAYS; d++){
	  //Reduce with real worker
	  local_num_avail_workers_average[worker->get_pos()][w][d] -= 
	    (double)((double)worker->get_current_avail(w,d,0)
		     + (double)worker->get_current_avail(w,d,1)
		     + (double)worker->get_current_avail(w,d,2)
		     )/(3.0*worker->get_pos());
	  //Add temporary worker
	  local_num_avail_workers_average[temp_worker->get_pos()][w][d]+=
	    (double)((double)temp_worker->get_current_avail(w,d,0)
		     + (double)temp_worker->get_current_avail(w,d,1)
		     + (double)temp_worker->get_current_avail(w,d,2)
		     )/(3.0*worker->get_pos());
	}
      }
    }
  }
 
  //Find worst day
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_WEEKDAYS; d++){
      //Temporary cost of stand ins
      double temp_cost = 2.0*local_num_avail_workers_average[Lib][w][d] 
	+ 1.0*local_num_avail_workers_average[Ass][w][d];
      //Find minimum cost of stand ins
      if(temp_cost < min_avail_cost){
	min_avail_cost = temp_cost;
	min_num_ass = local_num_avail_workers_average[Ass][w][d];
	min_num_lib = local_num_avail_workers_average[Lib][w][d];
	week = w;
	day = d;
      }
    }
  }

  //Write to global variable
  if(mode == "perm"){
    for(int p=0; p<NUM_POSITIONS; p++){
      for(int w=0; w<NUM_WEEKS; w++){
	  for(int d=0; d<NUM_WEEKDAYS; d++){
	    num_avail_workers_average[p][w][d] = local_num_avail_workers_average[p][w][d];
	  }
	}
      }
    }
  

    if(mode == "temp"){
      temp_avail_contribution_cost = min_avail_cost; 
      //cout << "Temp availability contribution cost: " << avail_contribution_cost << ". Ass: " 
      //   << min_num_ass << ". Lib: "
      //   << min_num_lib << ". week: " << week << " day: " << day << "." << endl;
    }
    if(mode == "perm"){
      avail_contribution_cost = min_avail_cost;
      min_contribution[Ass] = min_num_ass;
      min_contribution[Lib] = min_num_lib;
      cout << "Perm availability contribution cost: " << avail_contribution_cost << ". Ass: " 
	   << min_num_ass << ". Lib: "
	   << min_num_lib << ". week: " << week << " day: " << day << "." << endl;
    }
}

/************** Library function: write stat ************/

void Library::write_stat(){
  string stat_file_dir;
  stringstream stat_file_path;
  stat_file_dir = "../target/statistics/";
  stat_file_path << stat_file_dir << "statfile" << ".csv"; 
  stringstream stat_file2_path;
  stat_file2_path << stat_file_dir << "statfile2" << ".csv"; 
  stringstream objective_file_path;
  objective_file_path << stat_file_dir << "obj_func_val" << ".csv"; 

  ofstream stat_file(stat_file_path.str().c_str());
  int count = 0;
  //Print statistics to stat_file
  if (stat_file.is_open()) {
    stat_file << "Weekday count, Avail day ass, Avail day lib" << endl;
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	count++;
	stat_file << count << ",";
	stat_file << num_avail_day_workers[Ass][w][d] << ",";
	stat_file << num_avail_day_workers[Lib][w][d] << endl;

      }
    }
  }
  else cerr << "Unable to open file" << endl;

  ofstream stat_file2(stat_file2_path.str().c_str());
  count = 0;
  if (stat_file2.is_open()) {
    stat_file2 << "Shift count, Avail ass, Avail lib" << endl;
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	for(int s=0; s<NUM_SHIFTS-1; s++){
	  count++;
	  stat_file2 << count << ",";
	  stat_file2 << num_weekday_avail_workers[Ass][w][d][s] << ",";
	  stat_file2 << num_weekday_avail_workers[Lib][w][d][s] << endl;
	}
      }
    }
  }
  else cerr << "Unable to open file" << endl;

  ofstream obj_file(objective_file_path.str().c_str());
  if (obj_file.is_open()) {
    obj_file << "Iteration, weekend objective function" << endl;
    for(int i=0; i < (int) weekend_objective_function.size(); i++){
      obj_file << i << ",";
      obj_file << weekend_objective_function[i] << endl;
    }
  }
  else cerr << "Unable to open file" << endl;
}


/************ Library function: set avail day cost *********/

void Library::set_avail_day_cost(string mode){
  int local_num_avail_day_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];
  int max_cost = 100;
  int min_num_ass = 0;
  int min_num_lib = 0;
  int week;
  int day;

  for(int p=0; p<NUM_POSITIONS; p++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	local_num_avail_day_workers[p][w][d] = 0;
      }
    }
  }

  //Find number of available stand ins at different days
  for(int i=0; i<(int) worker_list.size(); i++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	Worker* worker = &worker_list[i];
	//Worker available shifts 1-4, after evening tasks have been distributed
	if(worker->get_current_avail(w,d,0) > 0 && worker->get_current_avail(w,d,1) > 0 &&
	   worker->get_current_avail(w,d,2) > 0 && worker->get_current_task(w,d,3) == no_task){
	  local_num_avail_day_workers[worker->get_pos()][w][d]++;
	}
	//if(worker_list[i].get_avail_day(w,d))
	// local_num_avail_day_workers[worker_list[i].get_pos()][w][d]++;
      }
    }
  }


  if(mode == "temp"){

    //Find number of available stand ins at different days
    for(int i=0; i<(int) destroyed_wend_workers.size(); i++){
      Worker* worker = destroyed_wend_workers[i].worker;
      Worker* temp_worker = &destroyed_wend_workers[i].temp_worker;

      for(int w=0; w<NUM_WEEKS; w++){
	for(int d=0; d<NUM_WEEKDAYS; d++){
	  //Reduce with real worker
	  if(worker->get_avail_day(w,d))
	    local_num_avail_day_workers[worker->get_pos()][w][d]--;
	  //Add temporary worker
	  if(temp_worker->get_avail_day(w,d))
	    local_num_avail_day_workers[temp_worker->get_pos()][w][d]++;
	}
      }
    }
  }

  // if(mode == "perm"){

  //   for(int p=0; p<NUM_POSITIONS; p++){
  //     for(int w=0; w<NUM_WEEKS; w++){
  // 	for(int d=0; d<NUM_WEEKDAYS; d++){
  // 	  num_avail_day_workers[p][w][d] = 0;
  // 	}
  //     }
  //   }
  //   //Find number of available stand ins at different days
  //   for(int i=0; i<(int) worker_list.size(); i++){
  //     for(int w=0; w<NUM_WEEKS; w++){
  // 	for(int d=0; d<NUM_WEEKDAYS; d++){
  // 	  //Worker available shifts 1-3, friday evening tasks ignored
  // 	  if(worker_list[i].get_avail_day(w,d))
  // 	    num_avail_day_workers[worker_list[i].get_pos()][w][d]++;
  // 	}
  //     }
  //   }
  // }

  //Find lowest number of Ass and Lib avail day workers
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	//Temporary cost of stand ins
	int temp_cost = 2*local_num_avail_day_workers[Lib][w][d] 
	  + 1*local_num_avail_day_workers[Ass][w][d];
	//Find minimum cost of stand ins
	if(temp_cost < max_cost){
	  max_cost = temp_cost;
	  min_num_ass = local_num_avail_day_workers[Ass][w][d];
	  min_num_lib = local_num_avail_day_workers[Lib][w][d];
	  week = w;
	  day = d;
	}
      }
    }

  //Write to global variable
  if(mode == "perm"){
    for(int p=0; p<NUM_POSITIONS; p++){
      for(int w=0; w<NUM_WEEKS; w++){
	  for(int d=0; d<NUM_WEEKDAYS; d++){
	    num_avail_day_workers[p][w][d] = local_num_avail_day_workers[p][w][d];
	  }
	}
      }
    }

  avail_day_average=0.0;
  for(int p=Ass; p<=Lib; p++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	avail_day_average += local_num_avail_day_workers[p][w][d];
      }
    }
  }
  avail_day_average/=(2*NUM_WEEKS*NUM_WEEKDAYS);

  if(mode == "temp"){
    temp_avail_day_cost = 2*min_num_lib + 1*min_num_ass;
    //cout << "Temp avail day cost: " << avail_day_cost << ". Ass: " << min_num_ass << ". Lib: " 
    //	 << min_num_lib << ". week: " << week << " day: " << day << "." << endl;
  }
  if(mode == "perm"){
    avail_day_cost = 2*min_num_lib + 1*min_num_ass;
    min_avail_day[Ass] = min_num_ass;
    min_avail_day[Lib] = min_num_lib;
    cout << "Perm avail day cost: " << avail_day_cost << ". Ass: " << min_num_ass << ". Lib: " 
	 << min_num_lib << ". week: " << week << " day: " << day << "." << endl;
  }
}

/************* Library function: find min stand ins **********/

int Library::find_min_stand_ins(int num_avail_day_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS], int type){
  int temp_max = 100;
  int return_val=0;
  int week = 0;
  int day = 0;
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_WEEKDAYS; d++){
      //Temporary cost of stand ins
      int temp_val = 2*num_avail_day_workers[Lib][w][d] + 1*num_avail_day_workers[Ass][w][d];
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


/*********** Library function: use temp solution ********/
void Library::use_temp_solution(){
  //Apply destroy on real workers
  for(int i=0; i < (int) destroyed_wend_workers.size(); i++){
    //Get the real worker
    TaskWorker* task_worker = &destroyed_wend_workers[i];
    Worker* worker = task_worker->worker;
      
    //Remove its weekends
    worker->remove_weekend();
  }

  //Repair solution
  //Set current demand
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_DAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	for(int t = 0; t < NUM_TASKS; t++){
	  current_demand[w][d][s][t] = temp_current_demand[w][d][s][t];
	}
      }
    }
  }

  //Set all weekend tasks
  while(weekend_task_list.size() > 0){
    WeekendTask* current_task = &weekend_task_list[0];

    //Get the placed workers at current task
    vector<TaskWorker*>* task_workers = current_task->get_placed_workers();

    for(int i=0; i < (int) task_workers->size(); i++){
      //TaskWorker* task_worker = current_task->get_placed_worker();
      Worker* worker = (*task_workers)[i]->worker;
      Worker* temp_worker = &(*task_workers)[i]->temp_worker;
      
      //Set weekend for real worker
      worker->set_current_weekend(temp_worker->get_current_weekend()-1,temp_worker->get_weekend_task());
      //cout << "Worker: " << worker->get_ID() 
      //   << " permanently placed at weekend: " << worker->get_current_weekend() << endl;
    }

    //Remove weekend task when all workers are permanently placed
    weekend_task_list.erase(weekend_task_list.begin());  
  }
  //Find number of available workers
  find_num_avail_workers();
}

/*********** Library function: destroy weekends ******/
void Library::destroy_weekend(int percent, string mode){

  //"Use temp": Apply destroy on real workers
  if (mode == "use_temp"){
    for(int i=0; i < (int) destroyed_wend_workers.size(); i++){
      //Get the real worker
      TaskWorker* task_worker = &destroyed_wend_workers[i];
      Worker* worker = task_worker->worker;
      
      //Remove its weekends
      worker->remove_weekend();
    }
  }

  //Else destroy temporarily or permanently
  else {
    //Clear all destroyed weekend workers
    destroyed_wend_workers.clear();
    weekend_task_list.clear();

    //Set temporary demand
    if(mode == "temp"){
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    for(int t = 0; t < NUM_TASKS; t++){
	      temp_current_demand[w][d][s][t] = current_demand[w][d][s][t];
	    }
	  }
	}
      }
    }

    //Create task workers
    vector<TaskWorker> task_worker_list;

    for(int i=0; i < (int) weekend_workers.size(); i++){
      TaskWorker a_worker;
      a_worker.worker = weekend_workers[i];
      a_worker.temp_worker = *weekend_workers[i];
      a_worker.temp_cost = a_worker.worker->get_cost_sum();
      task_worker_list.push_back(a_worker);
    }

    //Sort according to worker costs
    random_shuffle(task_worker_list.begin(), task_worker_list.end(), myrandom);

    //Print sorted workers
    cout << "Task workers in destroy: " << endl;
    //for(int h=0; h < (int) task_worker_list.size(); h++){
    //cout << task_worker_list[h].temp_cost << " ID: " << task_worker_list[h].worker->get_ID() << endl;
    //}

    //Delete weekend task, multiple of 5 of the work force
    double num_tasks = 0.01*(double)percent*(double)task_worker_list.size();
    int destroy_amount = (((int)(num_tasks + (double)NUM_WEEKS/2.0)/NUM_WEEKS) *NUM_WEEKS);
    cout << "Num tasks to destroy: "<< destroy_amount << endl;

    //Remove weekends for workers
    for(int i = 0; i<destroy_amount; i++){
      // cout << "Destroyed worker: " << task_worker_list.back().worker->get_ID() << " Weekend: " 
      // 	   << task_worker_list.back().worker->get_current_weekend() << endl;

      //Destroy a workers weekend
      destroy_a_weekend(task_worker_list.back(), mode);

      //Remove worker from worker list
      task_worker_list.pop_back();
    }

    // for(int i=0; i < (int)destroyed_wend_workers.size(); i++){
    //   cout <<  " ID: " << destroyed_wend_workers[i]->get_ID() << endl;
    // }

    //Find and push all free weekends
    for (int w=0; w <NUM_WEEKS; w++){
      for (int t=Exp; t<NUM_TASKS; t++){
	//Find demand for task
	int weekend_demand = 0;
	if (mode == "perm")
	  weekend_demand = current_demand[w][sat][0][t];
	else if (mode == "temp")
	  weekend_demand = temp_current_demand[w][sat][0][t];
	if(weekend_demand > 0){

	  //Find avail diff for task
	  int avail_diff = avail_demand_diff[find_position_req(t)][w][sat][0];

	  weekend_task_list.push_back(WeekendTask 
				      {find_position_req(t), w, weekend_demand, avail_diff, t});
	}
      } 
    }
  }
}


/*********** Library function: destroy a weekend ******/

void Library::destroy_a_weekend(TaskWorker& t_worker, string mode){
  //Worker* worker = t_worker.worker;
  //Worker* temp_worker = t_worker->temp_worker;
  
  //Destroy worker weekend permanently
  if (mode == "perm"){
    Worker* worker = t_worker.worker;
    //If weekend task is to be removed, increase demand at library
    if(worker->has_weekend_task()){
      current_demand[worker->get_current_weekend()-1][sat][0][worker->get_weekend_task_type()]++;
      current_demand[worker->get_current_weekend()-1][sun][0][worker->get_weekend_task_type()]++;

      if(worker->get_weekend_task_type() != HB){
	current_demand[worker->get_current_weekend()-1][fri][3][worker->get_weekend_task_type()]++;
      }
      //Remove task from worker
      worker->remove_weekend();
    }
    //Collect destroyed worker
    destroyed_wend_workers.push_back(t_worker);
  }

  //Destroy worker weekend temporarily
  else if (mode == "temp"){
    Worker* temp_worker = &t_worker.temp_worker;
    //If weekend task is to be removed, increase demand at library
    if(temp_worker->has_weekend_task()){
      temp_current_demand[temp_worker->get_current_weekend()-1][sat][0][temp_worker->get_weekend_task_type()]++;
      temp_current_demand[temp_worker->get_current_weekend()-1][sun][0][temp_worker->get_weekend_task_type()]++;

      if(temp_worker->get_weekend_task_type() != HB){
	temp_current_demand[temp_worker->get_current_weekend()-1][fri][3][temp_worker->get_weekend_task_type()]++;
      }

      //Remove task from worker
      temp_worker->remove_weekend();
 
    }

    //Collect destroyed worker
    destroyed_wend_workers.push_back(t_worker);
  }
}



/*********** Library function: find temp num avail workers ********/

void Library::find_temp_num_avail_workers(){ 

  find_num_avail_workers();

  //Set temporary demand num avail workers
  for(int p = 0; p < NUM_POSITIONS; p++)
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_DAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	  temp_num_avail_workers[p][w][d][s] = num_avail_workers[p][w][d][s];
      }
    }
  }

  for(int i=0; i < (int) destroyed_wend_workers.size(); i++){
    Worker* worker = destroyed_wend_workers[i].worker;
    Worker* temp_worker = &destroyed_wend_workers[i].temp_worker;

    //Remove worker if avail
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  if (worker->get_current_avail(w,d,s) == BBlib){
	    temp_num_avail_workers[BBlib][w][d][s]--; 
	  }
	  else if (worker->get_current_avail(w,d,s) == Lib){
	    temp_num_avail_workers[Lib][w][d][s]--; 
	  }
	  else if (worker->get_current_avail(w,d,s) == Ass){
	    temp_num_avail_workers[Ass][w][d][s]--; 
	  }
	}
      }
    }
 
    //Add temporary worker if avail
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  if (temp_worker->get_current_avail(w,d,s) == BBlib){
	    temp_num_avail_workers[BBlib][w][d][s]++; 
	  }
	  else if (temp_worker->get_current_avail(w,d,s) == Lib){
	    temp_num_avail_workers[Lib][w][d][s]++; 
	  }
	  else if (temp_worker->get_current_avail(w,d,s) == Ass){
	    temp_num_avail_workers[Ass][w][d][s]++; 
	  }
	}
      }
    }
  }
}



/*********** Library function: repair weekend tasks ******/

void Library::repair_weekend(string mode){

  //Sort tasks according to cheapest task, ie librarian qualification tasks first
 

  //Permanently repair the weekend
  if(mode == "perm"){
    //Sort tasks according to cheapest task, ie librarian qualification tasks first
    random_shuffle(weekend_task_list.begin(),weekend_task_list.end(), myrandom);
    sort(weekend_task_list.begin(),weekend_task_list.end());

    while(weekend_task_list.size() > 0){
      WeekendTask* current_task = &weekend_task_list[0];

      //Place a worker at random
      current_task->place_workers(&destroyed_wend_workers, mode);

      //Get a placed worker
      vector<TaskWorker*>* task_workers = current_task->get_placed_workers();
      TaskWorker* task_worker = (*task_workers)[0];
      Worker* worker = task_worker->worker;

      //Depending on placed weekend, reduce demand 
      current_demand[worker->get_current_weekend()-1][sat][0][worker->get_weekend_task_type()] 
	-= current_task->get_demand();
      current_demand[worker->get_current_weekend()-1][sun][0][worker->get_weekend_task_type()]
	-= current_task->get_demand();

      if(worker->get_weekend_task_type() != HB){
	current_demand[worker->get_current_weekend()-1][fri][3][worker->get_weekend_task_type()]
	  -= current_task->get_demand();
      }

      //Find number of available workers
      find_num_avail_workers();

      //Remove weekend task
      weekend_task_list.erase(weekend_task_list.begin());  
    }
  }

  //Temporarily repair the weekend
  else if (mode == "temp"){
    //Sort tasks according to cheapest task, ie librarian qualification tasks first
    random_shuffle(weekend_task_list.begin(),weekend_task_list.end(), myrandom);
    sort(weekend_task_list.begin(),weekend_task_list.end());

    int list_size = (int) weekend_task_list.size();
    for(int i =0; i < list_size; i++){
      WeekendTask* current_task = &weekend_task_list[i];

      //Place all workers at random
      current_task->place_workers(&destroyed_wend_workers, mode);

      //Get a placed worker
      vector<TaskWorker*>* task_workers = current_task->get_placed_workers();
      TaskWorker* task_worker = (*task_workers)[0];
      Worker* worker = &task_worker->temp_worker;

      //Depending on placed weekend, reduce demand
      temp_current_demand[worker->get_current_weekend()-1][sat][0][worker->get_weekend_task_type()]
	-= current_task->get_demand();
      temp_current_demand[worker->get_current_weekend()-1][sun][0][worker->get_weekend_task_type()]
	-= current_task->get_demand();

      if(worker->get_weekend_task_type() != HB){
	temp_current_demand[worker->get_current_weekend()-1][fri][3][worker->get_weekend_task_type()]
	  -= current_task->get_demand();
      }
    }
    //Increase the number of available workers
    find_temp_num_avail_workers();
  }


  //Use temporary solution as permanent
  else if (mode == "use_temp"){

    //Set current demand
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    for(int t = 0; t < NUM_TASKS; t++){
	      current_demand[w][d][s][t] = temp_current_demand[w][d][s][t];
	    }
	  }
	}
      }

    //Set all weekend tasks
    while(weekend_task_list.size() > 0){
      WeekendTask* current_task = &weekend_task_list[0];

      //Get the placed workers at current task
      vector<TaskWorker*>* task_workers = current_task->get_placed_workers();

      for(int i=0; i < (int) task_workers->size(); i++){
	//TaskWorker* task_worker = current_task->get_placed_worker();
	Worker* worker = (*task_workers)[i]->worker;
	Worker* temp_worker = &(*task_workers)[i]->temp_worker;
      
	//Set weekend for real worker
	worker->set_current_weekend(temp_worker->get_current_weekend()-1,temp_worker->get_weekend_task());
      }

      //Remove weekend task when all workers are permanently placed
      weekend_task_list.erase(weekend_task_list.begin());  
    }
    //Find number of available workers
    find_num_avail_workers();
  }
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

/*********** Library function: place_BokB ************/

void Library::place_BokB(){
  find_num_avail_workers();

  Worker* worker14;
  Worker* worker17;
  Worker* worker25;
  Worker* worker36;
  Worker* worker37;

  for(int i=0; i< (int) worker_list.size(); i++){
    if(worker_list[i].get_ID() == 25)
      worker25 = &worker_list[i];
    else if(worker_list[i].get_ID() == 14)
      worker14 = &worker_list[i];
    else if(worker_list[i].get_ID() == 17)
      worker17 = &worker_list[i];
    else if(worker_list[i].get_ID() == 36)
      worker36 = &worker_list[i];
    else if(worker_list[i].get_ID() == 37)
      worker37 = &worker_list[i];
  }



  //Find Thursday evening tasks
 task_list.clear();
  for(int w=0; w<NUM_WEEKS; w++){
    int demand = current_demand[w][3][3][BokB];
    if(demand > 0){
      //Find avail (workers with at least min qualification)
      int avail_demand_diff = num_avail_workers[BBlib][w][3][3] - demand;
      cout << "Task avail demand diff: " << avail_demand_diff << endl;
      //Create single task
      SingleTask task {find_position_req(BokB),w,3,3,demand,avail_demand_diff,BokB};
      task_list.push_back(task);
    }
  }

  //Place Thursday evening task
  for(int i=0; i< (int) worker_list.size(); i++){
    //if(worker_list[i].get_ID() == 25){
      for(int t=0; t < (int)task_list.size(); t++){
	//Worker* worker = &worker_list[i];
	SingleTask* current_task = &task_list[t];
	int week = current_task->get_week();
	int day = current_task->get_day();
	int shift = current_task->get_shift();

	cout << "Worker 25, to place at BB: " << worker25-> get_current_avail(week, day, shift) <<
	  current_task->get_qualification() << endl;

	if(worker25-> get_current_avail(week, day, shift) == current_task->get_qualification()){
	  current_task->place_a_worker(worker25);
	  cout << "BokB placed!" << endl;
	  current_demand[week][day][shift][BokB]--;
	}
	// }
    }
  }

  //Find Wednesday evening tasks
 task_list.clear();
  for(int w=0; w<NUM_WEEKS; w++){
    int demand = current_demand[w][2][3][BokB];
    if(demand > 0){
      //Find avail (workers with at least min qualification)
      int avail_demand_diff = num_avail_workers[BBlib][w][2][3] - demand;
      cout << "Task avail demand diff: " << avail_demand_diff << endl;
      //Create single task
      SingleTask task {find_position_req(BokB),w,2,3,demand,avail_demand_diff,BokB};
      task_list.push_back(task);
    }
  }

  //Place Wednesday evening task
  for(int t=0; t < (int)task_list.size(); t++){
    SingleTask* current_task = &task_list[t];
    int week = current_task->get_week();
    int day = current_task->get_day();
    int shift = current_task->get_shift();

    //Worker qualified and week before is not BokB
    if(worker14-> get_current_avail(week, day, shift) == current_task->get_qualification() && 
       worker14-> get_current_task(((NUM_WEEKS + (week-1)) % NUM_WEEKS),day,shift) != BokB){
      //Place
      current_task->place_a_worker(worker14);
      cout << "BokB placed: " << worker14->get_ID() << endl;
      current_demand[week][day][shift][BokB]--;
    }
    else if (worker37-> get_current_avail(week, day, shift) == current_task->get_qualification() && 
	     worker37-> get_current_task(((NUM_WEEKS + (week-1)) % NUM_WEEKS),day,shift) != BokB){
      //Place
      current_task->place_a_worker(worker37);
      cout << "BokB placed: " << worker37->get_ID() << endl;
      current_demand[week][day][shift][BokB]--;
    }
  }

  //Find Wednesday evening tasks
  task_list.clear();
  for(int w=0; w<NUM_WEEKS; w++){
    int demand = current_demand[w][0][0][BokB];
    if(demand > 0){
      //Find avail (workers with at least min qualification)
      int avail_demand_diff = num_avail_workers[BBlib][w][0][0] - demand;
      cout << "Task avail demand diff: " << avail_demand_diff << endl;
      //Create single task
      SingleTask task {find_position_req(BokB),w,0,0,demand,avail_demand_diff,BokB};
      task_list.push_back(task);
    }
  }


  //Place Monday morning task
  for(int t=0; t < (int)task_list.size(); t++){
    SingleTask* current_task = &task_list[t];
    int week = current_task->get_week();
    int day = current_task->get_day();
    int shift = current_task->get_shift();

    //Worker qualified and week before is not BokB
    if(worker25-> get_current_avail(week, day, shift) == current_task->get_qualification() && 
       worker25-> get_current_task(((NUM_WEEKS + (week-1)) % NUM_WEEKS),day,shift) != BokB){
      //Place
      current_task->place_a_worker(worker25);
      cout << "BokB placed: " << worker25->get_ID() << endl;
      current_demand[week][day][shift][BokB]--;
    }
    else if (worker36-> get_current_avail(week, day, shift) == current_task->get_qualification() && 
	     worker36-> get_current_task(((NUM_WEEKS + (week-1)) % NUM_WEEKS),day,shift) != BokB &&
	     worker25->get_current_task(week,day,0) != BokB){
      //Place
      current_task->place_a_worker(worker36);
      cout << "BokB placed: " << worker36->get_ID() << endl;
      current_demand[week][day][shift][BokB]--;
    }
  }


  //Find rest BokB tasks
  task_list.clear();
  for(int w=0; w<NUM_WEEKS; w++){
    for(int d=0; d<NUM_WEEKDAYS; d++){
      for(int s=0; s<NUM_SHIFTS; s++){
  	int demand = current_demand[w][d][s][BokB];
  	if(demand > 0){
  	  //Find avail (workers with at least min qualification)
  	  int avail_demand_diff = num_avail_workers[BBlib][w][d][s] - demand;
  	  cout << "Task avail demand diff: " << avail_demand_diff << endl;

  	  //Create single task
  	  SingleTask task {find_position_req(BokB),w,d,s,demand,avail_demand_diff,BokB};
  	  task_list.push_back(task);
  	}
      }
    }
  }

  //Place worker 36 if possible
  for(int t=0; t < (int)task_list.size(); t++){
    SingleTask* current_task = &task_list[t];
    int week = current_task->get_week();
    int day = current_task->get_day();
    int shift = current_task->get_shift();
    
    if(worker36->get_current_avail(week,day,shift) == current_task->get_qualification()){
      //Place
      current_task->place_a_worker(worker36);
      cout << "BokB placed: " << worker36->get_ID() << endl;
      current_demand[week][day][shift][BokB]--;
    }
    else if (worker17->get_current_avail(week,day,shift) == current_task->get_qualification()){
      //Place
      current_task->place_a_worker(worker17);
      cout << "BokB placed: " << worker17->get_ID() << endl;
      current_demand[week][day][shift][BokB]--;
    }
  }

}

/*********** Library function: destroy tasks ************/

void Library::destroy_tasks(int percent, string mode){
  find_num_avail_workers();
  print_num_avail_workers();
  print_current_demand();
  task_list.clear();

  //Find all tasks
  //for(int i=0; i<=Lib; i++){
    for(int w=0; w<NUM_WEEKS; w++){
      for(int d=0; d<NUM_WEEKDAYS; d++){
	for(int s=0; s<NUM_SHIFTS; s++){
	  for(int t=Exp; t<NUM_TASKS; t++){
	    int demand = current_demand[w][d][s][t];
	    if(demand > 0){
	      //Find avail (workers with at least min qualification)
	      int min_qual = find_position_req(t);
	      int avail_demand_diff = 0;
	      for(int pos=min_qual; pos < NUM_POSITIONS; pos++){
	       avail_demand_diff += num_avail_workers[pos][w][d][s];
	      }
	      avail_demand_diff -= demand;
	      cout << "Task avail demand diff: " << avail_demand_diff << endl;

	      //Create single task
	      SingleTask task {find_position_req(t),w,d,s,demand,avail_demand_diff,t};
	      task_list.push_back(task);
	    }
	  }
	}
      }
    }
    // }
  cout << "Number of tasks to repair: " << task_list.size() << endl;

  //Add all workers as destroyed when more than 200 tasks are present
  if((int) task_list.size() > 200){
    for(int i=0; i< (int) worker_list.size(); i++){
      TaskWorker task_worker;
      task_worker.worker = &worker_list[i];
      task_worker.temp_worker = worker_list[i];
      destroyed_task_workers.push_back(task_worker);
    }
  }
}
/*********** Library function: repair tasks ************/

//OBS no BokB
void Library::repair_tasks(string mode){
  //Sort tasks according to type (BokB, HB, Info, PL, Exp)
  random_shuffle(task_list.begin(),task_list.end(),myrandom);
  sort(task_list.begin(),task_list.end(),SingleTask::max_cost());

  for(int i=0; i < (int)task_list.size(); i++){
    cout << "Type: "<< task_list[i].get_type() << " Cost: " << task_list[i].get_cost() 
	 << " Avail diff: " << task_list[i].get_avail_diff()
	 << " W: " 
	 << task_list[i].get_week() << " D: " 
	 << task_list[i].get_day() << " S: " << task_list[i].get_shift() << endl;
  }
  while((int) task_list.size() !=0 ){
  //for(int i=0; i < 10; i++){
    SingleTask* current_task = &task_list[0];
    
    //Place cheapest workers at task
    current_task->place_workers(&destroyed_task_workers);
    
    //Get the placed worker
    //TaskWorker* task_worker = current_task->get_placed_workers();
    //Worker* worker = task_worker->worker;

    //Depending on placed weekend, reduce demand 
    current_demand[current_task->get_week()][current_task->get_day()][current_task->get_shift()]
      [current_task->get_type()] 
      -= current_task->get_demand();
   

    // //Find number of available workers
    // find_num_avail_workers();

    //Remove task
   task_list.erase(task_list.begin()); 
  }

  find_num_avail_workers();
  //print_num_avail_workers();
  //print_current_demand();

}
// /*********** Library function: find tasks ************/

// void Library::find_tasks(int type){
  
//   for(int w=0; w<NUM_WEEKS; w++){
//     for(int d=0; d<NUM_WEEKDAYS; d++){
//       for(int s=0; s<NUM_SHIFTS; s++){
// 	if(type == Lib){
// 	  int demand = current_demand[w][d][s][Info];
// 	    if(demand > 0){
// 	      int avail_demand_diff = num_avail_workers[Lib][w][d][s] - current_demand[w][d][s][Info];
// 	      SingleTask task {Lib,w,d,s,demand,avail_demand_diff,Info,&worker_list};
// 	      task_list.push_back(task);
// 	  }
// 	}
// 	else if(type == Ass){
// 	  for (int task_type=Exp; task_type <=PL; task_type++){
// 	    int demand = current_demand[w][d][s][task_type];
// 	      if(demand > 0){
// 	      int avail_demand_diff = num_avail_workers[Ass][w][d][s] + num_avail_workers[Lib][w][d][s] 
// 		- current_demand[w][d][s][task_type];

// 	      //Create a task, push to list
// 	      SingleTask task {Ass,w,d,s,demand,avail_demand_diff,task_type,&worker_list};
// 	      task_list.push_back(task);
// 	    }
// 	  }
// 	}
//       }  
//     } 
//   }
// }


// /************* Library function: set tasks ************/
// void Library::set_tasks(){
  
//   for (int type=Lib; type >=Ass; type--){
//     cout << "Type: " << type << endl;

//     //Find library tasks to be distributed
//     //find_tasks(type);
//     cout << "Number of tasks: " << task_list.size() << endl;

//     //Sort tasks according to cheapest
//     sort(task_list.begin(),task_list.end());

//     while((int) task_list.size() !=0 ){
//       cout << "Task List Size: " << task_list.size() << endl;
//       SingleTask* current_task = &task_list[0];
//       cout << "Demand at task: " << current_task->get_demand() << " at task type " 
// 	   << current_task->get_type() << endl;

//       //Place cheapest worker at current task
//       //current_task->place_workers();
//       //cout << "Type of worker placed: " << worker_type << endl;      

//       dec_current_demand
//      	(current_task->get_week(), current_task->get_day(),current_task->get_shift(), current_task->get_type());
//       dec_num_avail_workers
//       	(current_task->get_placed_worker_pos(),  current_task->get_week(), current_task->get_day(), 
//       	 current_task->get_shift());

//       //Erase task from list of tasks, otherwise sort to get cheapest
//       if (current_task->get_demand() == 0){
// 	task_list.erase(task_list.begin());
//       }
//       // OBS cost innefficient!
//       //else sort(task_list.begin(),task_list.end());
//     }
//   }
//   find_num_avail_workers();
//   find_avail_demand_diff("perm");
// }

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
      // if (worker.get_pos() == Lib){
      // 	weekend_lib.push_back(&worker_list[i]);
      // }
      // else if(worker.get_pos() == Ass){
      // 	// OLD: (worker.get_pos().find("ass",0,3) == 0){
      // 	weekend_ass.push_back(&worker_list[i]);	
      // }
      //else cout << "Error: in find_weekend_workers. No worker type." << endl;
      weekend_workers.push_back(&worker_list[i]); 
      //cout << "Weekend worker ID: " << worker.get_ID() << endl;
    }
    //else if (!worker.get_weekend().compare("no_weekend")) cout << "Error: in find_weekend_work." << endl;
  }

  cout << "Num of weekend workers: " << weekend_workers.size() << endl;
  //cout << "Num of lib weekend workers: " << weekend_lib.size() << endl;
  //cout << "Num of ass weekend workers: " << weekend_ass.size() << endl;
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
	  for(int w = 0; w < NUM_WEEKS; w++){
	    for (int k=0; k< NUM_DAYS; k++){
	      *resfile << worker_list[h].get_current_task(w,k,j) << " ";
	    }
	    *resfile << "   ";
	  }
	  *resfile << endl; 
	}
	*resfile << endl << endl;
      

	*resfile << "Availability for worker " << worker_list[h].get_ID() << endl;	
	for (int j=0; j< NUM_SHIFTS; j++){
	  for(int w = 0; w < NUM_WEEKS; w++){
	    for (int k=0; k< NUM_DAYS; k++){
	      *resfile << worker_list[h].get_current_avail(w,k,j) << " ";
	    }
	    *resfile << "   ";
	  }
	  *resfile << endl; 
	}
	*resfile << endl << endl;

	*resfile << "Current avail day for worker " << worker_list[h].get_ID() << endl;	
	  for(int w = 0; w < NUM_WEEKS; w++){
	    for (int k=0; k< NUM_DAYS; k++){
	      *resfile << worker_list[h].get_current_avail_day(w,k) << " ";
	    }
	    *resfile << "   ";
	  }
	  *resfile << endl << endl;

	*resfile << "Avail day for worker " << worker_list[h].get_ID() << endl;	
	for(int w = 0; w < NUM_WEEKS; w++){
	    for (int k=0; k< NUM_DAYS; k++){
	      *resfile << worker_list[h].get_avail_day(w,k) << " ";
	    }
	    *resfile << "   ";
	  }
	  *resfile << endl << endl;
	  *resfile 
	    << "**************************************************************************************" << endl;
      }
    }
}

void Library::write_weekend_AMPL_data(){
  string wend_file_path  = "../../../AMPLmodel/LNSweekendsAMPL/weekendinfo.mod";
  ofstream wend_file(wend_file_path.c_str());
  //int count = 0;
  //Print statistics to stat_file
  if (wend_file.is_open()) {
    wend_file << "######################## Fixed weekends #########################" << endl;
    for(int i=0; i< (int) worker_list.size(); i++){
      for(int w = 1; w <= NUM_WEEKS; w++){
	if(worker_list[i].get_current_weekend() ==  w){
	  wend_file << "subject to "<< worker_list[i].get_ID() << "_" 
		    <<  w  << "_" << 1 << ":" << endl;
	  wend_file << "H["<< worker_list[i].get_ID() << "," 
		    << w << "," << 1 << "] + H[" << worker_list[i].get_ID() << "," 
		    << w << "," << 2 << "]= " << 1 << ";" << endl;
	}
      }
    }
  }
  else cerr << "Unable to open file" << endl;
  wend_file.close();

  //Concaternate files
  string orig_file_path = "../../../AMPLmodel/LNSweekendsAMPL/librarystaff10W_orig.mod";
  string resulting_file_path = "../../../AMPLmodel/LNSweekendsAMPL/librarystaff10W.mod";
  ifstream orig_ampl_mod_file(orig_file_path.c_str());
  ifstream same_wend_file(wend_file_path.c_str());
  ofstream res_file (resulting_file_path.c_str());

  res_file << orig_ampl_mod_file.rdbuf() << same_wend_file.rdbuf() ;


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

void Library::find_avail_demand_diff(string mode){
  int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
  int avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  if (mode == "temp"){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int t = 0; t < NUM_TASKS; t++){
	    demand[w][d][s][t] = temp_current_demand[w][d][s][t];
	  }
	}
      }
    }
    for(int p = 0; p < NUM_POSITIONS; p++){
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    avail_workers[p][w][d][s] 
	      = temp_num_avail_workers[p][w][d][s];
	  }
	}
      }
    }
  }
  else if (mode == "perm"){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int t = 0; t < NUM_TASKS; t++){
	    demand[w][d][s][t] = current_demand[w][d][s][t];
	  }
	}
      }
    }
    for(int p = 0; p < NUM_POSITIONS; p++){
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    avail_workers[p][w][d][s] 
	      = num_avail_workers[p][w][d][s];
	  }
	}
      }
    }
  }

  for(int t=BBlib; t>=Ass; t--){
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  if(t == BBlib){
	    avail_demand_diff[t][w][d][s] =  
	      avail_workers[BBlib][w][d][s] 
	      -demand[w][d][s][BokB]; 	
	  }
	  else if(t == Lib){
	    avail_demand_diff[t][w][d][s] =  
	      avail_workers[BBlib][w][d][s] + num_avail_workers[Lib][w][d][s] 
	      -demand[w][d][s][Info] - demand[w][d][s][HB]; 	
	  }
	  else if (t == Ass){
	    avail_demand_diff[t][w][d][s] = 
	      avail_workers[BBlib][w][d][s] + avail_demand_diff[Lib][w][d][s] + num_avail_workers[Ass][w][d][s] 
	      - demand[w][d][s][Exp] - demand[w][d][s][PL];
	  }
	}
      }
    }
  }
}


/************ Library function: compare avail demand *****/

bool Library::compare_avail_demand(string mode){
  
  //Find available workers
  find_num_avail_workers();
  find_avail_demand_diff(mode);

  int diff[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
  int avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  if (mode == "temp"){
    //Find demand
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int t = 0; t < NUM_TASKS; t++){
	    demand[w][d][s][t] = temp_current_demand[w][d][s][t];
	  }
	}
      }
    }

    //Find avail workers
    for(int p = 0; p < NUM_POSITIONS; p++){
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    avail_workers[p][w][d][s] 
	      = temp_num_avail_workers[p][w][d][s];
	  }
	}
      }
    }
  }

  else if (mode == "perm"){
    //Find demand
    for(int w = 0; w < NUM_WEEKS; w++){
      for(int d = 0; d < NUM_DAYS; d++){
	for(int s = 0; s < NUM_SHIFTS; s++){
	  for(int t = 0; t < NUM_TASKS; t++){
	    demand[w][d][s][t] = current_demand[w][d][s][t];
	  }
	}
      }
    }

    //Find avail workers
    for(int p = 0; p < NUM_POSITIONS; p++){
      for(int w = 0; w < NUM_WEEKS; w++){
	for(int d = 0; d < NUM_DAYS; d++){
	  for(int s = 0; s < NUM_SHIFTS; s++){
	    avail_workers[p][w][d][s] 
	      = num_avail_workers[p][w][d][s];
	  }
	}
      }
    }

  }

  //Find diff between avail and demand for BBlibrarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	diff[w][d][s] =  avail_workers[BBlib][w][d][s] - demand[w][d][s][BokB];
	if (diff[w][d][s] < 0) {
	  cerr << "Solution not accepted at BBlib. Week: " << w << ". Day " << d << ". Shift " << s << " ." << endl;
	  return false;
	}  
      }
    }
  }
  //Find diff between avail and demand for librarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	diff[w][d][s] +=  avail_workers[Lib][w][d][s] - demand[w][d][s][Info] - demand[w][d][s][HB]; 	
	if (diff[w][d][s] < 0) {
	  cerr << "Solution not accepted at Lib. Week: " << w << ". Day " << d << ". Shift " << s << " ." << endl;
	  return false;
	}  
      }
    }
  }
  //Find diff between avail and demand for assistants and rest of librarians
  for(int w = 0; w < NUM_WEEKS; w++){
    for(int d = 0; d < NUM_WEEKDAYS; d++){
      for(int s = 0; s < NUM_SHIFTS; s++){
	diff[w][d][s] +=  avail_workers[Ass][w][d][s] - demand[w][d][s][Exp] - demand[w][d][s][PL];
	if (diff[w][d][s] < 0) {
	  cerr << "Solution not accepted at Ass. Week: " << w << ". Day " << d << ". Shift " << s << " ." << endl;
	  return false;
	}
      }
    }
  }

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
  cout << "Tasks: Exp, PL, Info, HB, BokB (without no_task)" << endl;
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

void Library::print_temp_current_demand(){
  cout << "Library demand of workers" << endl;
  cout << "Tasks: Exp, PL, Info, HB, BokB (without no_task)" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
    	for (int l=Exp; l< NUM_TASKS; l++){
	  cout << temp_current_demand[i][k][j][l] << " ";
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

void Library::print_temp_num_avail_workers(){
  cout << "Total num of available workers (Ass, Lib, BBlib):" << endl;
  
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for(int m = Ass; m< NUM_POSITIONS; m++){
	for (int k=0; k< NUM_DAYS; k++){
	  cout << temp_num_avail_workers[m][i][k][j] << " ";
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



