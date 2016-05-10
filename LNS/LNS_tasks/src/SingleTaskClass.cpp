#include "SingleTaskClass.h"

/********** SingleTask: Constructor ************/

SingleTask::SingleTask(int q, int w, int d, int s, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list)  : Task (q, w, worker_demand, avail_diff, task_type, w_list) {

  set_costs();
  day = d;
  shift = s;
}

/********** SingleTask: Set costs ************/

void SingleTask::set_costs(){
  if(type == BokB)
    total_cost = -10*avail_diff + 500;
  else total_cost = -10*avail_diff + demand;
}

/********** SingleTask: Find avail workers ************/

void SingleTask::find_avail_workers(vector<TaskWorker>* a_workers){
  avail_workers.clear();

  for (int i=0; i < (int) workers->size(); i++){ 
    TaskWorker* task_worker = &(*a_workers)[i];
    Worker* worker = task_worker->worker;

    //Add if worker is available and qualified
    if (worker->get_current_avail(week,day,shift) >= qualification){
      avail_workers.push_back(task_worker);
      //TaskWorker task_worker;
      // task_worker.worker = &(*workers)[i];
      // task_worker.temp_worker = (*workers)[i];
      // task_worker.temp_cost = task_worker.temp_worker.get_cost(week,day);
      // avail_workers.push_back(task_worker);
    }
  }
  //cout << "In task: available workers:" << endl;
}
/********** SingleTask: Temp place workers ************/

void SingleTask::temp_place_workers(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    //Set task
    avail_workers[i]->temp_worker.set_task(week,day,shift,type);
    //Set temp_cost as difference in cost by placing task
    avail_workers[i]->temp_cost = 
      avail_workers[i]->temp_worker.get_cost(week,day) - avail_workers[i]->worker->get_cost(week,day);
  }
}


/********** SingleTask: Place cheapest worker ************/

void SingleTask::place_workers(vector<TaskWorker>* a_workers){
  find_avail_workers(a_workers);
  
  //Find cost for workers if task is placed
  temp_place_workers();

  //Sort according to cheapest
  random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);
  sort(avail_workers.begin(), avail_workers.end(), TaskWorker::p_min_cost());

  //Print avail workers
  print_worker_costs();
 
  cout << "Placed worker " << avail_workers[0]->temp_worker.get_ID() << " at task w:" << week << " d:" << day << " s:" << shift << endl;

  //Place cheapest workers
  for(int i=0; i< orig_demand; i++){
    avail_workers[i]->worker->set_task(week,day,shift,type);
  }
  //set_placed_worker(avail_workers[0]);

  //Recalculate task cost
  demand--;
  set_costs();
}



/*********** SingleTask: get functions *********/

int SingleTask::get_day() const{
  return day;
}

int SingleTask::get_shift() const{
  return shift;
}

void SingleTask::print_worker_costs() {
  cout << "Available workers: " << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i]->temp_cost << " ";
  }
  cout << endl;
}
