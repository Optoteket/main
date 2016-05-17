#include "TaskClass.h"

/*********** Task: Constructor ***********/

Task::Task(int q, int w, int w_demand, int a_diff, int t_type){
  type = t_type;
  qualification = q;
  week= w;
  demand = w_demand;
  orig_demand = w_demand;
  avail_diff = a_diff;

  avail_workers = vector<TaskWorker*> ();
  placed_workers = vector<TaskWorker*> ();
  avail_workers.clear();
  placed_workers.clear();

}

/*********** Task function: Temp place workers ******/

void Task::temp_place_workers(){
}

/*********** Task function: Place cheapest worker ****/


void Task::place_cheapest_worker(){
}

/********* Task function: find available workers ********/

void Task::find_avail_workers(){
}

/*********** Set functions **********/

void Task::set_costs(){
}

// void Task::set_placed_worker(TaskWorker* worker){
//   placed_worker = worker;
// }

void Task::set_placed_workers(TaskWorker* worker){
  placed_workers.push_back(worker);
}

bool Task::check_feasibility(){
  for(int i=0; i < (int) placed_workers.size(); i++){
    //If there are several tasks placed the same day, the schedule is infeasible
    if(placed_workers[i]->temp_cost >= 100)
      return false;
  } 
  return true;
}


/*********** Get functions *********/

int Task::get_cost() const{
  return total_cost;
}

int Task::get_demand() const{
  return orig_demand;
}

int Task::get_avail_diff() const {
  return avail_diff;
}

int Task::get_week() const{
  return week;
}

int Task::get_type() const{
  return type;
}

int Task::get_qualification() const{
  return qualification;
}

// int Task::get_placed_worker_pos(){
//   return placed_worker->worker->get_pos();
// }

// TaskWorker* Task::get_placed_worker(){
//   return placed_worker;
// }

vector<TaskWorker*>* Task::get_placed_workers(){
  return &placed_workers;
}

/*********** Print functions ***********/

void Task::print_worker_costs() {
  cout << "Available workers: " << endl;
  //for (int i=0; i < (int) avail_workers.size(); i++){
  //cout << avail_workers[i].temp_cost << " ";
  //}
  cout << endl;
}

int Task::num_avail_workers(){
  //return avail_workers.size();
  return 5;
}
