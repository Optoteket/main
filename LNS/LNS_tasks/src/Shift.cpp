#include "Constants.h"
#include "LibraryClass.h"
#include "WorkerClass.h"

Library::Task::Task(int q, int w, int d, int t, int demand, int avail_diff, vector<Worker*>*  w_list){
  qual_workers = w_list;
  qualification = q;
  week= w;
  day = d;
  shift = t;
  set_costs(demand, avail_diff);

  find_avail_workers();

}

void Library::Task::find_avail_workers(){
  for (int i=0; i < (int) qual_workers->size(); i++){
    //cout << "Availability of task worker: " << (*qual_workers)[i]->get_avail(week,day,shift) << endl;
    if ((*qual_workers)[i]->get_avail(week,day,shift) > 0 ){
      Task_worker task_worker;
      task_worker.worker = (*qual_workers)[i];
      task_worker.worker_cost = 0;
      avail_workers.push_back(task_worker);
      //cout << "In task: available workers:" << (*qual_workers)[i]->get_ID() << endl;
    }
  }

  //cout << "In task: available workers:" << endl;
}

void Library::Task::set_costs(int c1, int c2){
  cost_demand = c1;
  cost_avail_diff = c2;
  total_cost = 3*cost_avail_diff - cost_demand;
}

int Library::Task::get_cost(){
  return total_cost;
}
