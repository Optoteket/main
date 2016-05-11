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
  //Constructor
  WeekendTask(int, int, int, int, int);

  //Functions
  virtual void find_avail_workers(vector<TaskWorker>*, string);
  virtual void set_costs();
  virtual void print_worker_costs();
  void place_workers(vector<TaskWorker>*, string);
  
  void print_avail_workers();

};

