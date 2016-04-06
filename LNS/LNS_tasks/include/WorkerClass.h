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
  int avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];

  vector<int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]> avail_vector;
  
 public:
  Worker(string, int, string, string, string, string, string, string, string); 
  void set_avail(int,int,int,int);
  void print_avail();
};

