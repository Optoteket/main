// Weekend task class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Constants.h"
#include "TaskClass.h"

using namespace std;

class WeekendTask : public Task {
 public:

  struct Task_worker {
    Worker* worker;
    Worker temp_worker;
    int temp_cost;
    int temp_avail[2][NUM_DAYS-2][NUM_SHIFTS];
    int temp_stand_in_avail[2][NUM_DAYS-2];
    //For weekends: cost for weekrest (what happend if availability and tasks is removed? 
    //stand in cost for those those days)

    bool operator<(Task_worker const & rhs) const{
      return this->temp_cost < rhs.temp_cost;
    }  
  };

  //Worker* worker_to_place;
  vector<Task_worker> avail_workers;
  WeekendTask(int, int, int, int, int, vector<Worker>*);

  //int num_avail_stand_ins[Num_workers][DAY], for week rest week
  //For weekends: total num stand in avail, coordinated with library
  //int min_stand_cost[Num_workers]; //Min num_avail_stand_ins
  //int total_cost; //Max of min

  virtual void find_avail_workers(vector<Worker*>*);
  virtual int place_cheapest_worker(vector<Worker*>*);
  virtual void temp_place_workers();
  virtual void set_costs();

};

