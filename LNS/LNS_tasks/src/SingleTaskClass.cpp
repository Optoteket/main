#include "SingleTaskClass.h"

/********** SingleTask: Constructor ************/

SingleTask::SingleTask(int q, int w, int d, int s, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list)  : Task (q, w, worker_demand, avail_diff, task_type, w_list) {

  day = d;
  shift = s;
}

/********** SingleTask: Set costs ************/

void SingleTask::set_costs(){
  total_cost = 3*avail_diff - demand;
}

/********** SingleTask: Find avail workers ************/

void SingleTask::find_avail_workers(){
  avail_workers.clear();

  for (int i=0; i < (int) workers->size(); i++){   
    if ((*workers)[i].get_current_avail(week,day,shift) > 0 && (*workers)[i].get_pos() >= qualification){
      Task_worker task_worker;
      task_worker.worker = &(*workers)[i];
      task_worker.temp_worker = (*workers)[i];
      task_worker.temp_worker_cost = task_worker.temp_worker.get_cost(week,day);
      avail_workers.push_back(task_worker);
    }
  }
  //cout << "In task: available workers:" << endl;
}

/********** SingleTask: Temp place workers ************/

void SingleTask::temp_place_workers(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    avail_workers[i].temp_worker.set_task(week,day,shift,type);
    avail_workers[i].temp_worker_cost = 
       avail_workers[i].temp_worker.get_cost(week,day) - avail_workers[i].temp_worker_cost;
  }
}

/********** SingleTask: Place cheapest worker ************/

void SingleTask::place_cheapest_worker(){
  find_avail_workers();
  
  //Find cost for workers if task is placed
  temp_place_workers();

  //Sort according to cheapest
  random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);
  sort(avail_workers.begin(), avail_workers.end());
  print_worker_costs();
 
  cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() << " at task w:" << week << " d:" << day << " s:" << shift << endl;

  //Choose cheapest worker
  avail_workers[0].worker->set_task(week,day,shift,type);
  set_placed_worker(avail_workers[0].worker);

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

