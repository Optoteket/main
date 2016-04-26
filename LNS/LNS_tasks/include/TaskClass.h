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

  struct Task_worker {
    Worker* worker;
    Worker temp_worker;
    int temp_worker_cost; //Singel class?
    //int stand_in_avail[NUM_DAYS]
    //For weekends: cost for weekrest (what happend if availability and tasks is removed? 
    //stand in cost for those those days)

    bool operator<(Task_worker const & task_worker) const{
      return this->temp_worker_cost < task_worker.temp_worker_cost; //Singel class?
    }  
  };

  int type;
  int qualification;
  int week;

  //int day; //In single class?
  //int shift; //Singel class?

  int demand;
  int avail_diff; //Single class?
  Task_worker* worker_to_place;
  //Total cost becomes smallest of these
  int total_cost;

  // All available workers and their costs
  vector<Task_worker> avail_workers;
  vector<Worker>* workers;


 public:
  Task(int,int,int,int,int, vector<Worker>*);
  virtual int get_cost() const;
  int get_demand() const;
  int get_week() const;
  int get_type() const;
  int get_qualification() const;
  int num_avail_workers();

  //Find and place workers
  virtual int place_cheapest_worker();  
  virtual void find_avail_workers();
  virtual void set_costs();
  virtual void temp_place_workers();

  //Print functions
  virtual void print_worker_costs(); 

  bool operator<(Task const & task) const{ 
    return this->get_cost() < task.get_cost();
  }
};

