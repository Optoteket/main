// Library class h file
#pragma once

#include <string>
#include <sstream>
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
  string stat_file_dir;
  stringstream stat_file_path;

  //Tasks to be distributed
  vector<SingleTask> task_list;
  vector<WeekendTask> weekend_task_list;

  // Worker vectors
  vector<Worker> worker_list;
  vector<Worker*> weekend_workers;
  vector<Worker> orig_workers;
  vector<Worker> best_sol_workers;

  //Destroyed workers
  vector<TaskWorker> destroyed_wend_workers;
  vector<TaskWorker> destroyed_task_workers;

  vector<double> weekend_objective_function;

  //Demand arrays 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int temp_current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int orig_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];

  //Avail statistics
  int num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int temp_num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  //Avail demand diff
  int avail_demand_diff[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  //Num avail_day_workers
  int num_weekday_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS][NUM_SHIFTS-1];

  //Avail day
  int num_avail_day_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];

  //Num full time equivalents
  double num_avail_workers_average[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];

  double library_max_cost;
  double library_cost;
  double temp_library_cost;
  double orig_library_cost;

  int avail_day_cost; //Maximize in objective function
  int min_avail_day[NUM_POSITIONS];
  int temp_avail_day_cost;

  int avail_contribution_cost;
  double min_contribution[NUM_POSITIONS];
  int temp_avail_contribution_cost;

  int num_avail_cost;
  double min_num_avail[NUM_POSITIONS];
  //int temp_avail_contribution_cost;

  int avail_cost;
  int temp_avail_cost;
  int min_avail[NUM_POSITIONS];

  double avail_day_average;
  double avail_average;
  double num_avail_average;

 public:

  //Constructor
  Library(ofstream*);
  void create_initial_solution();
  void optimize_weekends(int,int, double[3]);

  //Stand in avail
  void remove_weekday_tasks();
  bool set_evening_tasks();
  void set_library_cost(string, double[3]);
  void set_num_avail_cost();
  void set_avail_contribution_cost(string);
  void set_avail_day_cost(string);
  void set_avail_cost(string);
  //void find_sum_stand_ins(string);
  int find_min_stand_ins(int[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS],int);

  //Weekend related
  void find_all_weekend_tasks(); 
  void set_all_weekend_tasks();
  void destroy_weekend(int, string);
  void destroy_a_weekend(TaskWorker&, string);
  void repair_weekend(string);
  void repair_temp_weekend();
  void use_temp_solution();
  //void weekend_update_avail_demand(int, int, int); //Not working properly, not possible to keep updated

  //Weekday related
  void place_BokB();
  void destroy_tasks(int, string);
  void repair_tasks(string);
  void find_tasks(int);
  void set_tasks();

  //Init related
  void create_workers();
  void create_a_worker(vector<string>&);
  void find_weekend_workers();
  void read_demand();

  //Output related
  void write_results();
  void write_stat();
  void write_weekend_AMPL_data();

  //Demand related
  void find_num_avail_workers();
  void find_temp_num_avail_workers();
  void find_avail_demand_diff(string);
  bool compare_avail_demand(string);

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
  void print_temp_num_avail_workers();
  void print_avail_demand_diff();
  void print_current_demand();
  void print_task_costs();
  void print_temp_current_demand();

};


//Unused code
/* double T = pow(2.0, (double)i); */
/* double cost_diff = abs(library_max_cost - library_cost)+0.1; */
/* cout << "T:" << T << " Cost diff:" << cost_diff << " Exponential cooling:"  */
/* 	 << (double) exp(-(cost_diff/1.0*T)) << endl; */
/* //cerr << (((double)iterations-(double)i)/(double)iterations) << endl; */
