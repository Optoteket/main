// Task class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Constants.h"
#include "WorkerClass.h"
#include "TaskWorkerClass.h"

using namespace std;

class Task {
 protected:

  int type;
  int qualification;
  int week;
  int demand;
  int avail_diff;
  int total_cost;

  // All available workers and their costs
  vector<TaskWorker> avail_workers;
  vector<Worker>* workers;

  vector<TaskWorker*> placed_workers;
  TaskWorker* placed_worker;

 public:
  Task(int,int,int,int,int, vector<Worker>*);
  virtual int get_cost() const;
  int get_demand() const;
  int get_week() const;
  int get_type() const;
  int get_qualification() const;
  int get_placed_worker_pos();
  TaskWorker* get_placed_worker();
  vector<TaskWorker*>* get_placed_workers();

  int num_avail_workers();

  void set_placed_worker(TaskWorker*);
  void set_placed_workers(TaskWorker*);

  //Find and place workers
  virtual void place_cheapest_worker();  
  virtual void find_avail_workers();
  virtual void set_costs();
  virtual void temp_place_workers();

  //Print functions
  virtual void print_worker_costs(); 

  bool operator<(Task const & task) const{ 
    return this->get_cost() < task.get_cost();
  }
};

