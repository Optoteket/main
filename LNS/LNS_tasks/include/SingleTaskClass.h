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

class SingleTask : public Task {
 public:
  int day; 
  int shift; 
  int avail_diff;

  SingleTask(int q, int w, int d, int s, int worker_demand, int avail_diff, int task_type, vector<Worker>*  w_list);

  virtual void find_avail_workers();
  virtual void update_temp_worker_costs();
  virtual int place_cheapest_worker();
};

