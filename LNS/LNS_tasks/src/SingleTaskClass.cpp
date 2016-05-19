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
  total_cost = demand + qualification - 5*avail_diff;
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
    //Set temp worker
    avail_workers[i]->temp_worker = *avail_workers[i]->worker;
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
  if((int) avail_workers.size() >= orig_demand){
    for(int i=0; i< orig_demand; i++){
      //Place worker
      avail_workers[i]->worker->set_task(week,day,shift,type);
      //cout << "Placed worker with cost: " << avail_workers[i]->temp_cost 
      //   << "(" << avail_workers[i]->worker->get_ID() <<")" << endl;

      //Add to list of placed workers
      set_placed_workers(avail_workers[i]);

      //Recalculate task cost
      demand--;
      set_costs();
    }
  }
  else {
    cerr << "Error in SingleTask: not enough workers to place on task!" << endl;
    cout << "Error in SingleTask: Not enough workers to place on task!" << endl;
  }
}

void SingleTask::place_a_worker(Worker* worker){
  worker->set_task(week,day,shift,type);
}

bool SingleTask::check_feasibility(){
  for(int i=0; i < (int) placed_workers.size(); i++){
    //If there are several tasks placed the same day, the schedule is infeasible
    if(placed_workers[i]->temp_cost >= 100)
      return false;
  } 
  return true;
}

/*********** SingleTask: get functions *********/

int SingleTask::get_day() const{
  return day;
}

int SingleTask::get_shift() const{
  return shift;
}

void SingleTask::print_worker_costs() {
  cout << "Available workers cost: " << week << ", " << day << ", " << shift << " qual: " << get_qualification() << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i]->temp_cost << " ";
  }
  cout << endl;
}
