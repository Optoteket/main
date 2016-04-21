#include "WeekendTaskClass.h"


void WeekendTask::find_avail_workers(){
 avail_workers.clear();

  for (int i=0; i < (int) workers->size(); i++){   
    if ((*workers)[i].get_current_avail(week,day,shift) > 0 && (*workers)[i].get_pos() >= qualification){
      Task_worker task_worker;
      task_worker.worker = &(*workers)[i];
      task_worker.temp_worker = (*workers)[i];
      task_worker.temp_worker_cost = task_worker.temp_worker.find_costs(week,sat,0);
      avail_workers.push_back(task_worker);
    }
  }
  //cout << "In task: available workers:" << endl;
}


