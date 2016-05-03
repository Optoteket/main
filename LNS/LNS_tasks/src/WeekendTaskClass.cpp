#include "WeekendTaskClass.h"

/********** WeekendTask: Constructor *********/

WeekendTask::WeekendTask(int q, int w, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list)  : Task (q, w, worker_demand, avail_diff, task_type, w_list){

  set_costs();
  avail_workers = vector<TaskWorker*> ();

}

/********** WeekendTask: Find avail workers ************/

void WeekendTask::find_avail_workers(vector<TaskWorker>* a_workers, string mode){
  avail_workers.clear();

  // cout << "Available workers: " << endl;
  // for (int i=0; i < (int) a_workers->size(); i++){
  //   cout << (*a_workers)[i]->get_ID() << endl;
  // }
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


/********** WeekendTask: Place cheapest worker ************/

void WeekendTask::place_cheapest_worker(vector<TaskWorker>* a_workers){
  //find_avail_workers(a_workers, mode);
 
  //Find cost for workers if task is placed
  temp_place_workers();

  //Shuffle, sort according to lib->ass qualfication
  random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);
  sort(avail_workers.begin(), avail_workers.end());
  //print_worker_costs();

  //Print available workers
  cout << "Available workers: " << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i]->worker->get_ID() << endl;
  }
 
  //cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() << " at weekend task w:" << week << " type " <<

  //Choose cheapest worker
  avail_workers[0]->worker->set_current_weekend(week,type);
  set_placed_worker(avail_workers[0]);

  //Recalculate task cost
  demand--;
  set_costs();
  //return avail_workers[0].worker->get_pos();

}


/********** WeekendTask: Place a worker ************/

void WeekendTask::place_a_worker(vector<TaskWorker>* a_workers, string mode){
 
  while(demand > 0){
    find_avail_workers(a_workers, mode);

    //Shuffle, sort according to lib/ass qualfication
    random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);

    //Place permanent workers
    if(mode == "perm"){
      //Print available workers
      print_avail_workers();

      //cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() 
      // << " at weekend task w:" << week << " type " << endl;

      //Choose cheapest worker
      avail_workers[0]->worker->set_current_weekend(week,type);
      set_placed_worker(avail_workers[0]);
      set_placed_workers(avail_workers[0]);
      demand--;
    }

    //Place temporary workers
    else if (mode == "temp"){
      //Print available workers
      print_avail_workers();

      //cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() 
      //<< " at weekend task w:" << week << " type " << endl;

      //Choose cheapest worker
      avail_workers[0]->temp_worker.set_current_weekend(week,type);
      set_placed_worker(avail_workers[0]);
      set_placed_workers(avail_workers[0]);
      demand--;
    }
  }
}




/********** WeekendTask: Temp place workers ************/

void WeekendTask::temp_place_workers(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    TaskWorker* task_worker = avail_workers[i];

    //Set weekend task
    task_worker->temp_worker.set_current_weekend(week,type);
    task_worker->temp_worker.set_weekend_task(type);   
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
