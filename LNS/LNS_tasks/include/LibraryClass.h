// Library class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <ctime>  
#include <cstdlib>
#include <cmath>
#include <memory>

#include "WorkerClass.h"
#include "TaskClass.h"
#include "WeekendTaskClass.h"
#include "SingleTaskClass.h"
#include "Constants.h"

using namespace std;

class Library{

 private:
  ofstream* resfile;

  //Tasks to be distributed
  vector<SingleTask> task_list;
  vector<WeekendTask> weekend_task_list;

  // Worker vectors
  vector<Worker> worker_list;
  vector<Worker*> weekend_workers;
  vector<Worker*> weekend_lib;
  vector<Worker*> weekend_ass;
  vector<Worker*> lib_workers;
  vector<Worker*> ass_workers;
  vector<Worker*> dest_wend_workers;

  //Demand arrays 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

  //Avail statistics
  int num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int avail_demand_diff[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  //int num_avail_stand_ins[POS][WEEKS][DAYS] //Available stand ins for a certain day

  //Weekend cost related
  struct {
    int val;
    int count;
  } cost_total_stand_ins;

  int num_avail_day_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];

 public:

  //Constructor
  Library(ofstream*); 

  //Demand functions
  void read_demand();
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  void init_weekend_tasks();
  void set_tasks();

  //void dec_current_weekend_demand(int, int);
  int get_demand(int, int, int, int);
  int get_current_demand(int, int, int, int);

  //Create worker functions
  void create_workers();
  void create_a_worker(vector<string>&);

  //Avail compare functions  
  bool compare_avail_demand();

  //Find workers
  void find_weekend_workers();
  void find_lib_workers();
  void find_ass_workers();

  //Create initial solution
  void set_all_weekend_tasks();
  void find_all_weekend_tasks();
  void shuffle_worker_weekends();
  int check_weekend_demand();
  void create_initial_solution();
  //void find_avail_demand_diff(int);

  //Statistical variables
  void find_num_avail_workers();
  void find_avail_demand_diff();

  //Update
  void weekend_update_avail_demand(int, int, int);
  void dec_current_demand(int, int, int, int);
  void dec_num_avail_workers(int, int, int, int);
  void update_avail_demand_diff(int, int, int, int);

  //Costs
  void find_tasks(int);
  void update_task_costs();
  void find_sum_stand_ins();
  int find_min_stand_ins(int);
  //bool cost_compare(const Task&, const Task&);

  //Print functions
  void print_demand();
  void print_workers();
  void display_worker_avail();
  void print_worker_avail(int,int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  void print_num_avail_workers();
  void print_avail_demand_diff();
  void print_current_demand();
  void print_task_costs();

  //Destroy functions
  void destroy_weekend(int);
  void destroy_a_weekend(Worker*);

  //Repair functions
  void repair_weekend();

  //Write functions
  void write_results();

  //int myrandom(int);

};

