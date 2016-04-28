#include "WeekendTaskClass.h"

/********** WeekendTask: Constructor *********/

WeekendTask::WeekendTask(int q, int w, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list)  : Task (q, w, worker_demand, avail_diff, task_type, w_list){

  set_costs();
  avail_workers = vector<Task_worker> ();

}

/********** WeekendTask: Find avail workers ************/

void WeekendTask::find_avail_workers(vector<Worker*>* a_workers){
  avail_workers.clear();

  // cout << "Available workers: " << endl;
  // for (int i=0; i < (int) a_workers->size(); i++){
  //   cout << (*a_workers)[i]->get_ID() << endl;
  // }

  for (int i=0; i < (int) a_workers->size(); i++){
    Worker* worker = (*a_workers)[i];
    //if((type == HB && worker->get_HB_type()!= no_HB) 
    //   || (type != HB &&worker->get_HB_type()!= only_HB)){
      if (worker->get_current_weekend() == 0 && worker->get_pos() >= qualification){
	Task_worker task_worker;
	task_worker.worker = worker;
	task_worker.temp_worker = *worker;
	task_worker.temp_cost = task_worker.temp_worker.get_cost(week,sat);      
	//task_worker.temp_cost = task_worker.temp_worker.find_temp_costs(week,sat,0);
	avail_workers.push_back(task_worker);
      }
      //}
  }
}


/********** WeekendTask: Place cheapest worker ************/

void WeekendTask::place_cheapest_worker(vector<Worker*>* a_workers){
  find_avail_workers(a_workers);
 
  //Find cost for workers if task is placed
  temp_place_workers();

  //Shuffle, sort according to lib/ass qualfication
  random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);
  sort(avail_workers.begin(), avail_workers.end());
  //print_worker_costs();

  //Print available workers
  // cout << "Available workers: " << endl;
  // for (int i=0; i < (int) avail_workers.size(); i++){
  //   cout << avail_workers[i].worker->get_ID() << endl;
  // }
 
  //cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() << " at weekend task w:" << week << " type " <<

  //Choose cheapest worker
  avail_workers[0].worker->set_current_weekend(week+1,type);
  set_placed_worker(avail_workers[0].worker);

  //Recalculate task cost
  demand--;
  set_costs();
  //return avail_workers[0].worker->get_pos();

}

/********** WeekendTask: Temp place workers ************/

void WeekendTask::temp_place_workers(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    Task_worker task_worker = avail_workers[i];

    //Set weekend task
    task_worker.temp_worker.set_current_weekend(week+1);
    task_worker.temp_worker.set_weekend_task(type);

    //Remove weekrest tasks
    //task_worker.temp_worker.remove_weekrest_tasks();
    
    //TODO: check if right week
    //Find new availability and stand in availability
    for(int w=0; w<NUM_WEEKS; w++){
      for (int d=0; d<NUM_DAYS-2; d++){
	for (int s=0; s<NUM_SHIFTS; s++){
	  task_worker.temp_avail[w][d][s] = task_worker.temp_worker.get_current_avail
	    (task_worker.temp_worker.get_current_weekend()-1,d,s);
	}
	task_worker.temp_stand_in_avail[w][d] = task_worker.temp_worker.get_avail_day
	  (task_worker.temp_worker.get_current_weekend()-1,d);
      }  
    } 

    
    
  }
}

/*********** Set functions **********/

void WeekendTask::set_costs(){
  total_cost = - qualification;
}


void WeekendTask::print_worker_costs() {
  cout << "Worker costs: " << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i].temp_cost << " ";
  }
  cout << endl;
}
