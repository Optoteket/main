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
  int orig_demand;
  int avail_diff;
  int total_cost;

  //Placed workers
  vector<TaskWorker*> placed_workers;
  //TaskWorker* placed_worker;

  //Available workers
  vector<TaskWorker*> avail_workers;

 public:
  Task(int,int,int,int,int);
  virtual int get_cost() const;
  int get_demand() const;
  int get_avail_diff() const;
  int get_week() const;
  int get_type() const;
  int get_qualification() const;
  int get_placed_worker_pos();
  TaskWorker* get_placed_worker();
  vector<TaskWorker*>* get_placed_workers();

  int num_avail_workers();

  //void set_placed_worker(TaskWorker*);
  void set_placed_workers(TaskWorker*);

  //Find and place workers
  virtual void place_cheapest_worker();  
  virtual void find_avail_workers();
  virtual void set_costs();
  virtual void temp_place_workers();
  virtual bool check_feasibility();

  //Print functions
  virtual void print_worker_costs(); 

  bool operator<(Task const & task) const{ 
    return this->get_cost() < task.get_cost();
  }

  struct max_cost{
    bool operator()(Task const & lhs, Task const & rhs) const{ 
      return lhs.get_cost() > rhs.get_cost();
    }
  };
  
  struct max_qual{
    bool operator()(Task const & lhs, Task const & rhs) const{ 
      return lhs.get_qualification() > rhs.get_qualification();
    }
  };

};

