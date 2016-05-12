#include "SingleTaskClass.h"

/********** SingleTask: Constructor ************/

SingleTask::SingleTask(int q, int w, int d, int s, int w_demand, int a_diff, int t_type)  
  : Task (q, w, w_demand, a_diff, t_type){

  set_costs();
  day = d;
  shift = s;
}

/********** SingleTask: Set costs ************/

void SingleTask::set_costs(){
  //Tasks with high cost distributed first
  if(type == BokB)
    //Thursday evening
    //if(day==3 && shift==3)
    //total_cost = 505;
  //Wednesday evening
  //else if (day==4 && shift==3)
  //  total_cost = 504;
  //Monday morning
  //else if (day==0 && shift==0)
  //  total_cost = 503;
  //else
  //  total_cost = 500;
  total_cost = -5*avail_diff + 500;
  else total_cost = demand + qualification - 5*avail_diff;
}

/********** SingleTask: Find avail workers ************/

void SingleTask::find_avail_workers(vector<TaskWorker>* a_workers){
  avail_workers.clear();

  for (int i=0; i < (int) a_workers->size(); i++){ 
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
  //print_worker_costs();
 
  //cout << "Placed worker " << avail_workers[0]->temp_worker.get_ID() << " at task w:" << week << " d:" << day << " s:" << shift << endl;

  //Place cheapest workers
  for(int i=0; i< orig_demand; i++){
    avail_workers[i]->worker->set_task(week,day,shift,type);
  }

  //Recalculate task cost
  demand--;
  set_costs();
}

void SingleTask::place_a_worker(Worker* worker){
  worker->set_task(week,day,shift,type);
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
