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

#include "Constants.h"
#include "WorkerClass.h"
#include "TaskWorkerClass.h"
#include "TaskClass.h"
#include "WeekendTaskClass.h"
#include "SingleTaskClass.h"


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

  //Destroyed workers
  vector<TaskWorker> destroyed_wend_workers;

  //Demand arrays 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int temp_current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

  //Avail statistics
  int num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int avail_demand_diff[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  //int num_avail_day_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];

  //int num_avail_stand_ins[POS][WEEKS][DAYS] //Available stand ins for a certain day

  //Weekend cost related
  struct {
    int val;
    int count;
  } cost_total_stand_ins;


  //Cost weights
  int weight[2];

 public:

  //Constructor
  Library(ofstream*);
  void create_initial_solution();

  //Stand in avail
  void find_sum_stand_ins(int[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS]);
  int find_min_stand_ins(int[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS],int);

  //Weekend related
  void find_all_weekend_tasks(); 
  void set_all_weekend_tasks();
  void destroy_weekend(int, string);
  void destroy_a_weekend(TaskWorker&, string);
  void repair_weekend(string);
  void repair_temp_weekend();
  //void weekend_update_avail_demand(int, int, int); //Not working properly, not possible to keep updated

  //Weekday related
  void find_tasks(int);
  void set_tasks();

  //Init related
  void create_workers();
  void create_a_worker(vector<string>&);
  void find_weekend_workers();
  void read_demand();

  //Output related
  void write_results();

  //Demand related
  void find_num_avail_workers();
  void find_avail_demand_diff();
  bool compare_avail_demand();

  //Get
  int get_demand(int, int, int, int);
  int get_current_demand(int, int, int, int);

  //Dec
  void dec_current_demand(int, int, int, int);
  void dec_num_avail_workers(int, int, int, int);

  //Set
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  void init_weekend_tasks();  

  //Print functions
  void print_demand();
  void print_workers();
  void display_worker_avail();
  void print_worker_avail(int,int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  void print_num_avail_workers();
  void print_avail_demand_diff();
  void print_current_demand();
  void print_task_costs();
  void print_temp_current_demand();

};

