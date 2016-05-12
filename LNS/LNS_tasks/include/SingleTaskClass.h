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

  SingleTask(int, int, int, int, int, int, int);

  virtual void find_avail_workers(vector<TaskWorker>* a_workers);
  virtual void temp_place_workers();
  virtual void place_workers(vector<TaskWorker>* a_workers);
  virtual void set_costs();
  virtual void print_worker_costs();
  void place_a_worker(Worker*);

  int get_day() const;
  int get_shift() const; 

};

