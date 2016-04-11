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

  //Private functions, keep private for easier handling
   void display_all_avail();

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
    int rotation;
  } current;
 

  //Change made 2016-04-11: avail one more param
  int avail[NUM_ROTATIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];  

 public:

  //Worker(string, int, string, string, string, string, string, string, string);
  Worker(string, int, string, string, string, string, string, string, string, int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  Worker(const Worker &obj);
  //void print_avail();
  void print_modulo();
  void display_avail();
 
  //Set functions
  //void set_avail(int,int,int,int,int);
  void set_weekend(int);
  void set_rotation(int);

  //Get functions
  int get_avail(int, int, int);
  int get_ID();
  int get_rotation();
  string get_weekend();
  string get_pos();
  int get_current_weekend();
};

