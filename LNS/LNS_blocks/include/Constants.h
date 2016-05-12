#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

//*** Time parameters***
static const int NUM_WEEKS = 5;
static const int NUM_DAYS = 7;
static const int NUM_SHIFTS = 4;
static const int NUM_TASKS = 4; //could be 5. No task, Block, PL, HB, LOW

static const int num_workers = 39;
static const int UPPER_LIMIT_MANY = 3;
static const int UPPER_LIMIT_STANDARD = 2;
static const int LOWER_LIMIT_MANY = 1;

//*** COSTS ***
static const int PL_VIOLATE_COST = 600; //When a block is containing a PL that will violate that workers demand
static const int PL_GOOD_COST = 500; //A worker who needs more PL is assigned a PL. Value LEQ DEMAND_PL
static const int DEMAND_FEW_LIBS = 300;
static const int DEMAND_MANY_LIBS = 600;
static const int DEMAND_FEW_ASS = 115;
static const int DEMAND_MANY_ASS = 250;
static const int DEMAND_FEW_TOT = 650; //currently: should be > DEMAND_MANY_LIBS
static const int DEMAND_MANY_TOT = 500; //Same relation to PL_VIOLATE_COST
static const int DEMAND_PL_BAD_LIB = 800;
static const int DEMAND_PL_BAD_ASS = 600; 
static const int DEMAND_PL_GOOD_LIB = 600; //When exact demand
static const int DEMAND_PL_GOOD_ASS = 800; //When exact demand
static const int STAND_IN_COST = 5;
static const int DEMAND_EVENING_COST = 20000;
static const int DEMAND_WEEKEND_COST = 7000;
//*Weekend costs*
static const int NO_WEEKEND_COST = 5000; //No weekend assigned to a weekend worker. Keep decently high (happens if Only_HB-worker can not take HB, since already assigned)
static const int HB_ASSIGNED_COST = 10000; //If HB is already assigned when being assigned to the worker
static const int DEMAND_HB_OVERSTAFF = 25000;





















#endif