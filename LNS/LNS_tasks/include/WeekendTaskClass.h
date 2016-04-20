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

  enum days{
    fri = 4,
    sat = 5,
    sun= 6
  }; 

  virtual void find_avail_workers();
  int get_something();
};

