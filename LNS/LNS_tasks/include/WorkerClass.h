// Worker class h file
#pragma once

using namespace std;

class Worker{

 private:
  string pos;
  int ID;
  string name;
  string department;
  string weekend;
  string boss;
  string PL_type;
  string HB_type;
  string freeday;

  static const int NUM_WEEKS = 5;
  static const int NUM_DAYS = 7;
  static const int NUM_SHIFTS = 4;
  static const int NUM_TASKS = 5;
  int avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS][NUM_TASKS];
  
 public:
  Worker(string, int, string, string, string, string, string, string, string); 
  
};

