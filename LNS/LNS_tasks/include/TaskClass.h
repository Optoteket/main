// Task class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Constants.h"
#include "WorkerClass.h"

using namespace std;

class Task {
 protected:
  int type;
  int qualification;
  int week;
  int day; //In child class?
  int shift;
  int cost_demand;
  int cost_avail_diff;
  int total_cost;

  struct Task_worker {
    Worker* worker;
    Worker temp_worker;
    int temp_worker_cost;

    bool operator<(Task_worker const & task_worker) const{
      return this->temp_worker_cost < task_worker.temp_worker_cost;
    }
    
  };

  // All available workers and their costs
  vector<Task_worker> avail_workers;
  vector<Worker>* workers;
  vector<Worker> temp_workers;

 public:
  Task(int,int,int,int,int,int,int, vector<Worker>*);
  int get_cost() const;
  int get_demand() const;
  int get_week() const;
  int get_day() const;
  int get_shift() const;
  int get_type() const;
  int get_qualification() const;
  int num_avail_workers();

  virtual int place_cheapest_worker();  
  virtual void find_avail_workers();
  void set_costs();
  //void set_costs(int[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS], int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]);

  void update_temp_worker_costs();

  //Print functions
  void print_worker_costs(); 

  bool operator<(Task const & task) const{ 
    return this->get_cost() < task.get_cost();
  }
};

