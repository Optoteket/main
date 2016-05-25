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

  struct HB_first {
    bool operator()(TaskWorker const * lhs, TaskWorker const * rhs) const{
      //If type is HB, prioritize only and standard HB
      return lhs->worker->get_HB_type() > rhs->worker->get_HB_type();
    }
  };

  struct HB_last {
    bool operator()(TaskWorker const * lhs, TaskWorker const * rhs) const{
      //If type not HB, prioritize no HB
      return lhs->worker->get_HB_type() < rhs->worker->get_HB_type();
    }
  };
};

