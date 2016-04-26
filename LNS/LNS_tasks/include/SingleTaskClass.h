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

  SingleTask(int, int, int, int, int, int, int, vector<Worker>*);

  virtual void find_avail_workers();
  virtual void temp_place_workers();
  virtual void place_cheapest_worker();
  virtual void set_costs();

  int get_day() const;
  int get_shift() const; 

};

