// Library class h file
#pragma once

#include "WorkerClass.h"

using namespace std;

class Library{

 private:

  static const int NUM_WEEKS = 5;
  static const int NUM_DAYS = 7;
  static const int NUM_SHIFTS = 4;
  static const int NUM_TASKS = 5;

  /* class Costs { */
  /*    int cost_avail_demand_diff(); */
  /*    int num_avail[2][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]; */
  /* } costs; */

  enum task_type {
    Exp,
    Info,
    PL,
    HB,
    BokB
  };  

  enum position {
    lib,
    ass
  };
 
  int week_worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

  //Avail variables
  int num_avail_workers[2][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int avail_demand_diff[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  vector<Worker> worker_list;

 public:
  Library();
  void print_demand();

  //Demand functions
  void read_demand();
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  int get_demand(int, int, int, int);
  //void add_worker(Worker*);

  //Create worker functions
  void print_workers();
  void create_workers();

  //Avail compare functions
  int cost_avail_demand_diff();
  void print_avail_demand_diff();
  
};

