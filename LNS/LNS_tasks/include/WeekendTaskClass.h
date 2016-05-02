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
    int temp_avail[NUM_WEEKS][NUM_DAYS-2][NUM_SHIFTS];
    int temp_stand_in_avail[NUM_WEEKS][NUM_DAYS-2];

    bool operator<(Task_worker const & rhs) const{
      return this->temp_cost < rhs.temp_cost;
    }  
  };

  //Worker* worker_to_place;
  vector<Task_worker> avail_workers;
  WeekendTask(int, int, int, int, int, vector<Worker>*);

  virtual void find_avail_workers(vector<Worker*>*);
  virtual void place_cheapest_worker(vector<Worker*>*);
  virtual void temp_place_workers();
  virtual void set_costs();
  virtual void print_worker_costs();
  void place_a_worker(vector<Worker*>*);



};

