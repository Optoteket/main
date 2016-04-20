#include "WeekendTaskClass.h"


void WeekendTask::find_avail_workers(){
  avail_workers.clear();
  // int fri = 4;
  // int sat = 5;
  // int sun = 6;
  // int first_shift = 0;

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

int WeekendTask::get_something(){
  return cost_demand;

}
