#include "WeekendTaskClass.h"

/********** WeekendTask: Constructor *********/

WeekendTask::WeekendTask(int q, int w, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list)  : Task (q, w, worker_demand, avail_diff, task_type, w_list){

}

/********** WeekendTask: Find avail workers ************/

void WeekendTask::find_avail_workers(vector<Worker*>* a_workers){
  avail_workers.clear();

  for (int i=0; i < (int) a_workers->size(); i++){
    Worker* worker = (*a_workers)[i];
    if (worker->get_current_weekend() == 0 && worker->get_pos() >= qualification){
      Task_worker task_worker;
      task_worker.worker = worker;
      task_worker.temp_worker = *worker;
      task_worker.temp_cost = task_worker.temp_worker.find_costs(week,sat,0);
      avail_workers.push_back(task_worker);
    }
  }
}


/********** WeekendTask: Place cheapest worker ************/

int WeekendTask::place_cheapest_worker(vector<Worker*>* a_workers){
  find_avail_workers(a_workers);
  
 
  //Find cost for workers if task is placed
  temp_place_workers();

  //  //Sort according to cheapest
  random_shuffle(avail_workers.begin(), avail_workers.end(), myrandom);
  sort(avail_workers.begin(), avail_workers.end());
  //   print_worker_costs();
 
  //   cout << "Placed worker " << avail_workers[0].temp_worker.get_ID() << " at weekend task w:" << week << endl;

  //Choose cheapest worker SEGFAULT!
  avail_workers[0].worker->set_current_weekend(week,type);

//   //Recalculate task cost
//   demand--;
//   set_costs();
// //   return avail_workers[0].worker->get_pos();

//  return 1;
}

/********** WeekendTask: Temp place workers ************/

void WeekendTask::temp_place_workers(){
  for (int i=0; i < (int) avail_workers.size(); i++){
    Task_worker task_worker = avail_workers[i];

    //Set weekend task
    task_worker.temp_worker.set_current_weekend(week);
    task_worker.temp_worker.set_weekend_task(type);
    // avail_workers[i].temp_worker.set_task(week,sun,0,type);

    // if (type != HB || !no_friday_when_HB){
    //   avail_workers[i].temp_worker.set_task(week,sun,3,type);
    // }

    //Remove weekrest tasks
    task_worker.temp_worker.remove_weekrest_tasks();
    //avail_workers[i].remove_weekerest_tasks(week);
    

    //Find new availability and stand in availability
    for(int w=0; w<2; w++){
      for (int d=0; d<NUM_DAYS-2; d++){
	for (int s=0; s<NUM_SHIFTS; s++){
	  task_worker.temp_avail[w][d][s] = task_worker.temp_worker.get_current_avail
	    (task_worker.temp_worker.get_current_weekend()-1,d,s);
	  task_worker.temp_stand_in_avail[w][d] = task_worker.temp_worker.get_avail_day
	    (task_worker.temp_worker.get_current_weekend()-1,d);
	}
      }
      //OLD:avail_workers[i].temp_worker_cost = avail_workers[i].temp_worker.find_costs(week,day,shift);
    }

    //set_costs();
    
  }
}

/*********** Set functions **********/

void WeekendTask::set_costs(){
  total_cost = 3*avail_diff - demand;
}
