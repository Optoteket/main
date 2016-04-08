// Worker class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Constants.h"

using namespace std;


class Worker{

 private:

  struct {
    string pos;
    int ID;
    string name;
    string department;
    string weekend;
    string boss;
    string PL_type;
    string HB_type;
    string freeday;
  } identity;

  struct{
    int weekend;
  } current;
 
  int avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  vector<int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]> avail_vector;
  
 public:
  //Worker(string, int, string, string, string, string, string, string, string);
  Worker(string, int, string, string, string, string, string, string, string, int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  Worker(const Worker &obj);
  void print_avail();
  void display_avail_vector();

  //Set functions
  void set_avail(int,int,int,int);
  void set_weekend(int);

  //Get functions
  int get_avail(int, int, int);
  int get_ID();
  string get_weekend();
  string get_pos();
  int get_current_weekend();
};

