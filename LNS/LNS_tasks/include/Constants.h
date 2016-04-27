// System constants and enums
#pragma once

const int NUM_WEEKS = 5;
const int NUM_DAYS = 7;
const int NUM_WEEKDAYS = 5;
const int NUM_SHIFTS = 4;
const int NUM_ROTATIONS = NUM_WEEKS;

const int MAX_TASKS_PER_DAY = 1;
const int MAX_PL_PER_WEEK = 1;
const int MAX_PL_10W_STANDARD = 3;
const int MAX_PL_10W_MANY = 4;

 enum task_type {
   no_task=0,
   Exp=1,
   PL=2,
   Info=3,
   HB=4,
   BokB=5,
   NUM_TASKS
 };  

enum position_type {
  no_position=0,
  Ass=1,
  Lib=2,
  BBlib=3,
  NUM_POSITIONS
};


enum days {
  fri = 4,
  sat = 5,
  sun= 6
}; 

enum PL_types {
  no_PL_type,
  no_PL,
  standard_PL,
  many_PL
};

enum HB_types {
  no_HB_type,
  no_HB,
  standard_HB
};

int myrandom (int);
int find_position_req(int);

/*********** Library Rules ***********/
// Activated if a person who works a weekend works at the same task Friday afternoon, Saturday morning and Sunday morning
const bool staff_work_whole_weekends = true; //NOT USED
// All staff can only be assigned one task per day
const bool one_task_per_day = true; //Used?
const bool no_friday_when_HB = true; //Used
