// Task worker class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Constants.h"
#include "WorkerClass.h"


class TaskWorker{
 public:
  Worker* worker;
  Worker temp_worker;
  int temp_cost;

  struct p_min_cost{
    bool operator()(TaskWorker const * lhs,TaskWorker const * rhs) const{
      return lhs->temp_cost < rhs->temp_cost;
    }
  };

  bool operator<(TaskWorker const & rhs) const{
    return this->temp_cost < rhs.temp_cost;
  }  
};