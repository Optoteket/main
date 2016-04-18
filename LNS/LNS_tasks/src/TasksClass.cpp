#include "Constants.h"
#include "LibraryClass.h"
#include "WorkerClass.h"
#include "TaskClass.h"


Task::Task(int q, int w, int d, int t, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list){
  type = task_type;
  qual_workers = w_list;
  qualification = q;
  week= w;
  day = d;
  shift = t;
  demand = worker_demand;
  cost_avail_diff = avail_diff;
  set_costs(demand, avail_diff);

  find_avail_workers();

}

void Task::update_worker_costs(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    //Task_worker* task_worker = &avail_worker[i];
    avail_workers[i].worker_cost = avail_workers[i].worker->find_costs(week,day,shift);
  }
}

void Task::place_cheapest_worker(){ 
  
  //Update the costs of the workers
  update_worker_costs();

  //Sort according to cheapest
  sort(avail_workers.begin(), avail_workers.end());
  print_worker_costs();

 
  cout << "Placed worker " << avail_workers[0].worker->get_ID() << " at task w:" << week << " d:" << day << " s:" << shift << endl;

  //Choose cheapest
  avail_workers[0].worker->set_task(week,day,shift,type);
  avail_workers.erase(avail_workers.begin());

}

void Task::find_avail_workers(){
  for (int i=0; i < (int) qual_workers->size(); i++){
    //cout << "Availability of task worker: " << (*qual_workers)[i]->get_avail(week,day,shift) << endl;
    if ((*qual_workers)[i].get_avail(week,day,shift) > 0 && (*qual_workers)[i].get_pos() >= qualification){
      Task_worker task_worker;
      //Worker* worker = (*qual_workers)[i];
      task_worker.worker = &(*qual_workers)[i];
      task_worker.worker_cost = task_worker.worker->find_costs(week,day,shift);
      //cout << "Worker cost: " << task_worker.worker-> find_costs(week,day,shift) << endl; //TO DO: function, get cost
      avail_workers.push_back(task_worker);
      //cout << "Avail worker id: " << avail_workers[avail_workers.size()-1].worker->get_ID() << endl;
      //cout << "In task: available workers:" << (*qual_workers)[i]->get_ID() << endl;
      //task_worker.worker->display_avail();
      //task_worker.worker->display_avail_day();
    }
  }

  //cout << "In task: available workers:" << endl;
}

/*********** Set functions **********/

void Task::set_costs(int c1, int c2){
  total_cost = 3*cost_avail_diff - demand;
}


/*********** Get functions *********/

int Task::get_cost() const{
  return total_cost;
}

int Task::get_demand() const{
  return demand;
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

/*********** Print functions ***********/

void Task::print_worker_costs() {
  cout << "Available workers: " << endl;
  for (int i=0; i < (int) avail_workers.size(); i++){
    cout << avail_workers[i].worker_cost << endl;
  }
}

int Task::num_avail_workers(){
  return avail_workers.size();
}
