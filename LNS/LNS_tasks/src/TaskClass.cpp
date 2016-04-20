#include "TaskClass.h"

/*********** Task: Constructor ***********/

Task::Task(int q, int w, int d, int s, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list){
  type = task_type;
  workers = w_list;
  qualification = q;
  week= w;
  day = d;
  shift = s;
  cost_demand = worker_demand;
  cost_avail_diff = avail_diff;
  set_costs();

}

/*********** Task function: Update worker costs ******/

void Task::update_temp_worker_costs(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    avail_workers[i].temp_worker.set_task(week,day,shift,type);
    avail_workers[i].temp_worker_cost = avail_workers[i].temp_worker.find_costs(week,day,shift);
  }
}

/*********** Task function: Place cheapest worker ****/


int Task::place_cheapest_worker(){

  find_avail_workers();
  
  //Find cost for workers if task is placed
  update_temp_worker_costs();

  //Sort according to cheapest
  random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);
  sort(avail_workers.begin(), avail_workers.end());
  print_worker_costs();
 
  cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() << " at task w:" << week << " d:" << day << " s:" << shift << endl;

  //Choose cheapest worker
  avail_workers[0].worker->set_task(week,day,shift,type);

  //Recalculate task cost
  cost_demand--;
  set_costs();
  return avail_workers[0].worker->get_pos();

}

/********* Task function: find available workers ********/

void Task::find_avail_workers(){
  avail_workers.clear();

  for (int i=0; i < (int) workers->size(); i++){   
    if ((*workers)[i].get_current_avail(week,day,shift) > 0 && (*workers)[i].get_pos() >= qualification){
      Task_worker task_worker;
      task_worker.worker = &(*workers)[i];
      task_worker.temp_worker = (*workers)[i];
      task_worker.temp_worker_cost = task_worker.temp_worker.find_costs(week,day,shift);
      avail_workers.push_back(task_worker);
    }
  }
  //cout << "In task: available workers:" << endl;
}

/*********** Set functions **********/

void Task::set_costs(){
  total_cost = 3*cost_avail_diff - cost_demand;
}

// void Task::set_costs(int  avail_demand[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS], 
// 		     int  current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]){
//   total_cost = 3*avail_demand[qualification][week][day][shift] - current_demand[week][day][shift][type];
// }


/*********** Get functions *********/

int Task::get_cost() const{
  return total_cost;
}

int Task::get_demand() const{
  return cost_demand;
}

int Task::get_week() const{
  return week;
}

int Task::get_day() const{
  return day;
}

int Task::get_shift() const{
  return shift;
}

int Task::get_type() const{
  return type;
}

int Task::get_qualification() const{
  return qualification;
}

/*********** Print functions ***********/

void Task::print_worker_costs() {
  cout << "Available workers: " << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i].temp_worker_cost << " ";
  }
  cout << endl;
}

int Task::num_avail_workers(){
  return avail_workers.size();
}
