// Library class h file
#pragma once

using namespace std;

class Library{

 private:

  enum task_type {
    Exp,
    Info,
    PL,
    HB,
    BokB
  };
  
  static const int NUM_WEEKS = 5;
  static const int NUM_DAYS = 7;
  static const int NUM_SHIFTS = 4;
  static const int NUM_TASKS = 5;
  int week_worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 

 public:
  Library();
  void print_demand();
  void read_demand();
  void set_demand(int,int,int,string,int);
  void set_demand(int,int,int,int,int);
  int get_demand(int, int, int, int);

  
};

