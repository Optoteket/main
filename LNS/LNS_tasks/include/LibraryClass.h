// Library class h file
#pragma once

#define NUM_WEEKS 5;
#define NUM_DAYS 7;
#define NUM_WEEK_DAYS 5;
#define NUM_WEEKEND_DAYS 2;
#define NUM_WEEK_SHIFTS 4;
#define NUM_WEEK_TASKS 3; //Info, Exp, PL 

using namespace std;

//typedef  array4D;

class Library{
 public:
  Library();
 private:
  unsigned char week_worker_demand [NUM_WEEKS]; 
  //[NUM_WEEK_DAYS] [NUM_WEEK_SHIFTS] [NUM_WEEK_TASKS];
  //vector<vector<vector<vector<int>>>> worker_demand;
};

