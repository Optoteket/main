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


#include "WorkerClass.h"
#include "Constants.h"

using namespace std;

class Library{

 private:

  /************* NESTED CLASS: Task **************/
  class Task {
  private:
    int qualification;
    int week;
    int day;
    int shift;
    int cost_demand;
    int cost_avail_diff;
    int total_cost;
    struct Task_worker {
      Worker* worker;
      //Cost depending on avail_day
      int worker_cost;
    };
    // All available workers and their costs
    vector<Task_worker> avail_workers;
    vector<Worker*>* qual_workers;
  public:
    Task(int,int,int,int,int,int, vector<Worker*>*);
    void find_avail_workers();
    void set_costs(int,int);
    int get_cost();


    //bool operator<(Obj const & L, Obj const & R) { // The operator takes const references - it can compare const objects
    //return L.total_cost < R.total_cost;
    //}
  };

  //Tasks to be distributed
  vector<Task> task_list;

  /********** Worker vectors *********/
  vector<Worker> worker_list;
  vector<Worker*> weekend_workers;
  vector<Worker*> weekend_lib;
  vector<Worker*> weekend_ass;
  vector<Worker*> lib_workers;
  vector<Worker*> ass_workers;

  //Demand arrays 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int current_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

  //Avail arrays
  int num_avail_workers[NUM_POSITIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int avail_demand_diff[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

 public:

  //Constructor
  Library(); 

  //Demand functions

  void read_demand();
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  void set_weekend_tasks();
  void set_tasks();

  void dec_current_demand(int, int, int, int);
  void dec_current_weekend_demand(int, int);
  int get_demand(int, int, int, int);
  int get_current_demand(int, int, int, int);

  //Create worker functions
  void create_workers();
  void create_a_worker(vector<string>&);

  //Avail compare functions
  void find_num_avail_workers();
  bool demand_filled();

  //Initial solution
  void find_weekend_workers();
  void find_lib_workers();
  void find_ass_workers();
  void shuffle_workers();
  int check_weekend_demand();
  void create_initial_solution();

  //Update
  void weekend_update_avail_demand(int, int, int);
  void dec_num_avail_workers(int, int, int, int);

  //Costs
  void find_task_costs(int);

  //Print functions
  void print_demand();
  void print_workers();
  void display_worker_avail();
  void print_worker_avail(int,int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  void print_avail_demand_diff();
  void print_current_demand();
  void print_task_costs();
};

