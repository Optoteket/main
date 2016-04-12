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

  struct{
    vector<Worker*> weekend_workers;
  } subset;
 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 
  int temp_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

  //Avail variables
  int num_avail_workers[NUM_POSITIONS+1][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int avail_demand_diff[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  vector<Worker> worker_list;

 public:
  //Constructor
  Library(); 

  //Demand functions

  void read_demand();
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  int get_demand(int, int, int, int);

  //Create worker functions
  void create_workers();
  void create_a_worker(vector<string>&);

  //Avail compare functions
  void find_num_avail_workers();
  void find_weekend_workers();
  bool demand_filled();

  //Initial solution
  void shuffle_workers();
  int check_weekend_demand();
  void create_initial_solution();
  void set_weekend_tasks();

  //Print functions
  void print_demand();
  void print_workers();
  void display_worker_avail();
  void print_worker_avail(int,int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  void print_avail_demand_diff();
};

