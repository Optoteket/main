// System constants and enums
#pragma once

const int NUM_WEEKS = 5;
const int NUM_DAYS = 7;
const int NUM_SHIFTS = 4;
const int NUM_TASKS = 5;
const int NUM_ROTATIONS = NUM_WEEKS;
const int NUM_POSITIONS = 3;

 enum task_type {
   Exp=1,
   Info,
   PL,
   HB,
   BokB
 };  

enum position {
  ass = 1,
  lib,
  bokb
};
