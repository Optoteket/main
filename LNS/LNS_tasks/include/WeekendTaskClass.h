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

  //Available workers
  vector<TaskWorker*> avail_workers;

  //Constructor
  WeekendTask(int, int, int, int, int, vector<Worker>*);

  //Functions
  virtual void find_avail_workers(vector<TaskWorker>*);
  virtual void place_cheapest_worker(vector<TaskWorker>*);
  virtual void temp_place_workers();
  virtual void set_costs();
  virtual void print_worker_costs();
  void place_a_worker(vector<TaskWorker>*);



};

