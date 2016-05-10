#include "WeekendTaskClass.h"

/********** WeekendTask: Constructor *********/

WeekendTask::WeekendTask(int q, int w, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list)  : Task (q, w, worker_demand, avail_diff, task_type, w_list){

  set_costs();
  avail_workers = vector<TaskWorker*> ();

}

/********** WeekendTask: Find avail workers ************/

void WeekendTask::find_avail_workers(vector<TaskWorker>* a_workers, string mode){
  avail_workers.clear();

  //Find destroyed temporary workers
  if(mode == "perm"){
    for (int i=0; i < (int) a_workers->size(); i++){
      TaskWorker* task_worker = &(*a_workers)[i];
      Worker* worker = task_worker->worker;

      //if((type == HB && worker->get_HB_type()!= no_HB) 
      //   || (type != HB &&worker->get_HB_type()!= only_HB)){
      if (!worker->has_weekend_task() && worker->get_pos() >= qualification){
	avail_workers.push_back(task_worker);
      }
      //}
    }
  }

  //Find destroyed permanent workers
  else if (mode == "temp"){
    for (int i=0; i < (int) a_workers->size(); i++){
      TaskWorker* task_worker = &(*a_workers)[i];
      Worker temp_worker = task_worker->temp_worker;

      //if((type == HB && worker->get_HB_type()!= no_HB) 
      //   || (type != HB &&worker->get_HB_type()!= only_HB)){
      if (!temp_worker.has_weekend_task() && temp_worker.get_pos() >= qualification){
	avail_workers.push_back(task_worker);
      }
      //}
    }
  }
}


/********** WeekendTask: Place a worker ************/

void WeekendTask::place_workers(vector<TaskWorker>* a_workers, string mode){
 
  while(demand > 0){
    find_avail_workers(a_workers, mode);

    //Shuffle
    random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);

    //Place permanent workers
    if(mode == "perm"){

      //Choose a random worker
      avail_workers[0]->worker->set_current_weekend(week,type);
      set_placed_worker(avail_workers[0]);
      set_placed_workers(avail_workers[0]);
      demand--;
    }

    //Place temporary workers
    else if (mode == "temp"){

      //Choose random worker
      avail_workers[0]->temp_worker.set_current_weekend(week,type);
      set_placed_worker(avail_workers[0]);
      set_placed_workers(avail_workers[0]);
      demand--;
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
    cout << avail_workers[i]->temp_cost << " ";
  }
  cout << endl;
}

void WeekendTask::print_avail_workers(){
  //Print available workers
  cout << "Available workers: " << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i]->worker->get_ID() << endl;
  } 
}
