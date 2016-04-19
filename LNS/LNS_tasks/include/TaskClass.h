// Task class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Constants.h"
#include "WorkerClass.h"

using namespace std;

class Task {
 private:
  int type;
  int qualification;
  int week;
  int day;
  int shift;
  int demand;
  int cost_avail_diff;
  int total_cost;

  struct Task_worker {
    Worker* worker;
    int worker_cost;

    bool operator<(Task_worker const & worker) const{ 
      return this->worker_cost < worker.worker_cost;
    }
  };

  // All available workers and their costs
  vector<Task_worker> avail_workers;
  vector<Worker>* qual_workers;

 public:

  Task(int,int,int,int,int,int,int, vector<Worker>*);
  void find_avail_workers();
  void set_costs(int,int);

  int get_cost() const;
  int get_demand() const;
  int get_week() const;
  int get_day() const;
  int get_shift() const;
  int get_type() const;

  void place_cheapest_worker();
  void print_worker_costs(); 
  void update_worker_costs();

  int num_avail_workers();

  bool operator<(Task const & task) const{ 
    return this->get_cost() < task.get_cost();
  }
};

