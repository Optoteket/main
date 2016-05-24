// Worker class h file
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cassert>

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
    int avail_day[NUM_ROTATIONS][NUM_WEEKS][NUM_DAYS];
    int avail[NUM_ROTATIONS][NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  } identity;

  struct{
    int weekend;
    int rotation;

    int num_PL_week[NUM_WEEKS];
    int num_PL;
    int num_tasks_day[NUM_WEEKS][NUM_DAYS];
    int num_tasks_week[NUM_WEEKS];
    int avail_day[NUM_WEEKS][NUM_DAYS];
    int num_same_shifts_week[NUM_WEEKS][NUM_SHIFTS];
    
    int avail[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
    int tasks[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
  } current;

  struct{
    static const int NUM_COSTS = 6;
    int weights[NUM_COSTS];
    int num_tasks_day_cost[NUM_WEEKS][NUM_DAYS];
    int num_tasks_week_cost[NUM_WEEKS];
    int stand_in_cost[NUM_WEEKS][NUM_DAYS];
    int PL_week_cost[NUM_WEEKS];
    int PL_cost;
    int num_same_shifts_week_cost[NUM_WEEKS][NUM_SHIFTS];

    int total_cost[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS];
    int cost_sum;
  } costs;


 public:

  
  Worker(string, int, string, string, string, string, string, string, string, int[NUM_WEEKS][NUM_DAYS][NUM_SHIFTS]);
  Worker(const Worker &obj);
  Worker();
  //void print_avail();

  //void print_modulo();
  void display_avail();
  void display_avail_day();
  void display_tasks();
  void display_all_current_avail();
 
  //Set functions
  void set_PL_costs(int);
  void set_cost_sum();
  void set_stand_in_cost(int, int);
  void set_num_tasks_costs(int, int);
  void set_num_same_shift_cost(int, int);
  void set_total_cost(int, int, int);

  void set_current_weekend(int);
  void set_current_weekend(int,int);
  void set_rotation(int);
  void set_task(int, int, int, int);
  void set_weekend_task(int);
  //void set_weekend_task(string);

  void set_current_avail(int, int, int);
  void set_current_avail_day(int, int);

  void rotate_current_avail();
  void rotate_current_avail_day();

  void remove_week_rest();
  void remove_weekend();
  void remove_week(int);
  void remove_weekrest_tasks();
  void remove_task(int, int, int);

  //Get functions
  int get_weekend_task_type();
  int get_HB_type();
  int get_PL_type();
  int get_cost_sum();
  int get_avail(int, int, int);
  int get_current_avail(int, int, int);
  int get_current_task(int,int,int);
  int get_ID();
  int get_rotation();
  string get_weekend();
  //string get_pos();
  int get_pos();
  int get_current_weekend();
  int get_avail_day(int, int);
  int get_current_avail_day(int, int);
  int get_cost_sum () const;
  int get_cost_sum_no_stand_in();
  int get_weekend_task();
  int get_total_PL_week_cost();
  int get_total_PL_cost();
  int get_total_tasks_week_cost();
  int get_total_same_shift_cost();
  int get_total_stand_in_cost();
  int get_total_tasks_day_cost();

  //Worker cost statistics
  int get_num_excess_tasks_week();
  int get_num_excess_tasks_day();
  int get_num_excess_PL();
  int get_num_excess_PL_week();
  int get_num_excess_same_shifts_week();
  int get_worst_week();

  bool has_weekend_task();

  //Cost functions
  int find_temp_costs(int, int, int);
  int find_stand_in_cost(int, int);
  int find_num_tasks_cost(int, int);

  bool operator<(Worker const & worker) const{
    return this->get_cost_sum() < worker.get_cost_sum();
  }

  struct p_comp {
    bool operator()(Worker const* lhs, Worker const* rhs) const{
       return lhs->get_cost_sum() < rhs->get_cost_sum();
    } 
  };    
};

