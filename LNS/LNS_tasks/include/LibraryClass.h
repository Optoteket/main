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
#include <random>


#include "WorkerClass.h"
#include "Constants.h"

using namespace std;

class Library{

 private:

  struct{
    vector<Worker*> weekend_workers;
  } subset;
 
  int worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

  //Avail variables
  int num_avail_workers[2][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  int avail_demand_diff[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  vector<Worker> worker_list;

 public:
  //Constructor
  Library(); 

  //Demand functions
  void print_demand();
  void read_demand();
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  int get_demand(int, int, int, int);

  //Create worker functions
  void print_workers();
  void print_worker_avail(int,int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  void create_workers();
  void create_a_worker(vector<string>&);
  void display_worker_avail();

  //Avail compare functions
  void find_num_avail_workers();
  void find_weekend_workers();
  bool demand_filled();
  void print_avail_demand_diff();
  void shuffle_workers();
  int check_weekend_demand();
  
};

