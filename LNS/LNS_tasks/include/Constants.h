// System constants and enums
#pragma once

const int NUM_WEEKS = 5;
const int NUM_DAYS = 7;
const int NUM_SHIFTS = 4;
//const int NUM_TASKS = 5;
const int NUM_ROTATIONS = NUM_WEEKS;
//const int NUM_POSITIONS = 3;

 enum task_type {
   no_task=0,
   Exp=1,
   Info=2,
   PL=3,
   HB=4,
   BokB=5,
   NUM_TASKS
 };  

enum position_type {
  no_worker,
  Ass,
  Lib,
  Bokb,
  NUM_POSITIONS
};
