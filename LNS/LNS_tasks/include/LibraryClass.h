// Library class h file
#pragma once

using namespace std;

class Library{
 public:
  Library();
  void print_demand();
  void read_demand();

 private:

  enum task_types{
    Exp,
    Info,
    PL,
    HB //Add BokB v.2
  };
  
  static const int NUM_WEEKS = 5;
  static const int NUM_DAYS = 7;
  static const int NUM_SHIFTS = 4;
  static const int NUM_TASKS = 4;
  int week_worker_demand[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS]; 


  
};

