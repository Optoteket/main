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
  TaskWorker worst_worker;
  int worst_week;

  //Objective function values
  vector<double> weekend_objective_function;
  vector<double> weekend_day_avail_cost;
  vector<double> weekend_shift_avail_cost;
  vector<double> weekend_stand_in_cost;
  vector<double> weekend_stand_in_cost_lib;
  vector<double> weekend_stand_in_cost_ass;
  vector<double> weekend_day_avail_average_cost;
  vector<double> weekend_shift_avail_average_cost;
  vector<double> weekend_stand_in_average_cost;

  //Solution feasibility
  bool feasible_solution;

  //Weights
  static const int lib_weight = 2;
  static const int ass_weight = 1;

  //Demand arrays 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  //int temp_current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int orig_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];

  //Avail statistics
  int num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  //int temp_num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  //Avail demand diff
  //int avail_demand_diff[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  //Num avail_day_workers
  int num_weekday_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS][NUM_SHIFTS-1];

  //Avail day
  int num_avail_day_workers[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];

  //Num full time equivalents
  double num_avail_workers_average[NUM_POSITIONS][NUM_WEEKS][NUM_WEEKDAYS];

  //Library costs
  double library_max_cost;
  double library_cost;
  double temp_library_cost;
  double orig_library_cost;
  double library_stand_in_cost;
  double library_critical_worker_cost;
  double library_non_critical_worker_cost;
  double library_wend_cost;

  //Library worker costs
  int num_tasks_day_cost;
  int num_tasks_week_cost;
  int PL_week_cost;
  int PL_cost;
  int num_same_shifts_week_cost;

  //Stand in cost term
  int stand_in_cost; //Maximize in objective function
  int min_stand_in[NUM_POSITIONS];
  int temp_avail_day_cost;

  //Shift avail cost term
  int shift_avail_cost;
  int temp_avail_cost;
  int min_shift_avail[NUM_POSITIONS];

  //Day avail cost terms
  int day_avail_cost;
  double min_day_avail[NUM_POSITIONS];

  //Average cost terms
  double stand_in_average;
  double shift_avail_average;
  double day_avail_average;

  //Remove?
  int avail_contribution_cost;
  double min_contribution[NUM_POSITIONS];
  int temp_avail_contribution_cost;


 public:

  //Constructor
  Library(ofstream*);
  Library(const Library &obj);

  //Top level functions
  void create_initial_solution();
  void optimize_weekends(int,int, double[3]);
  void optimize_weekday_tasks(int,int);

  //Weekend auxiliary functions
  void remove_weekday_tasks();
  void remove_weekday_tasks_not_BokB_or_evening();
  void destroy_weekend(int);
  void destroy_a_weekend(TaskWorker&);
  void repair_weekend();
  bool set_evening_tasks();
  bool place_BokB();

  //Weekend costs
  void set_wend_library_cost(double[3]);
  void set_wend_day_avail_cost();
  void set_wend_stand_in_cost();
  void set_wend_shift_avail_cost();

  //Weekday auxiliary functions
  bool get_solution_feasibility(); //TODO: check if all solutions infeasible
  bool unassigned_tasks_exist();
  void find_worst_worker();
  void destroy_tasks(int, string);
  void repair_tasks(string);
  void show_task_statistics();

  //Weekday costs
  void set_non_critical_worker_cost();
  void set_critical_worker_cost();
  void set_wday_stand_in_cost();

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
  //void find_temp_num_avail_workers();
  //void find_avail_demand_diff(string);
  bool compare_avail_demand();

  //Get
  int get_demand(int, int, int, int);
  int get_current_demand(int, int, int, int);
  double get_library_wend_cost() const;
  double get_library_cost() const;
  double get_stand_in_cost() const;
  double get_shift_avail_cost() const;
  double get_day_avail_cost() const;
  double get_stand_in_lib() const;
  double get_stand_in_ass() const;

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
