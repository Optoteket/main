#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

//*** Time parameters***
static const int NUM_WEEKS = 5;
static const int NUM_DAYS = 7;
static const int NUM_SHIFTS = 4;
static const int NUM_TASKS = 4; //could be 5. No task, Block, PL, HB, LOW

static const int num_workers = 39;

static const int UPPER_LIMIT_STANDARD = 2;
static const int UPPER_LIMIT_MANY = 3;
static const int LOWER_LIMIT_MANY = 1;

//*** COSTS ***
static const int PL_VIOLATE_COST = 1500; //When a block is containing a PL that will violate that workers demand
static const int PL_GOOD_COST = 1000; //A worker who needs more PL is assigned a PL. If > demand_PL then getting correct amount per worker at least
static const int DEMAND_FEW_LIBS = 300;
static const int DEMAND_MANY_LIBS = 40; //Extremely low penalty
static const int DEMAND_FEW_ASS = 350; //**Increase this so>demand_few_lib??** Good to have ass on shifts until demand is filled! 125 atm
static const int DEMAND_MANY_ASS = 2000; //Bad to have too many assistants on shift!
static const int DEMAND_FEW_TOT = 800; //currently: should be > DEMAND_MANY_LIBS
static const int DEMAND_MANY_TOT = 700; //Same relation to PL_VIOLATE_COST
static const int DEMAND_PL_BAD_LIB = 800;
static const int DEMAND_PL_BAD_ASS = 600; 
static const int DEMAND_PL_GOOD_LIB = 400; //When exact demand
static const int DEMAND_PL_GOOD_ASS = 600; //When exact demand
extern int STAND_IN_COST;
static const int DEMAND_EVENING_COST = 20000; //DEMAND_EVENING_COST > (5*)(2*)HIGH_PRIORITY (+ cost if ruining stand_in, - cost else). *5 becuase HIGH_PRIORITY can happen 5 times/week

//*Weekend costs*
static const int NO_WEEKEND_COST = 5000; //No weekend assigned to a weekend worker. Keep decently high (happens if Only_HB-worker can not take HB, since already assigned)
// static const int HB_ASSIGNED_COST = 10000; //If HB is already assigned when being assigned to the worker (used for 10W)
static const int DEMAND_HB_OVERSTAFF = 15000;

static const int HIGH_PRIORITY = 2500; //param value for STAND_IN_COST. DEMAND_EVENING_COST > 5*HIGH_PRIORITY since can happen 5 times/week
static const int MIDDLE_PRIORITY = 250;
static const int LOW_PRIORITY = 5; //Parameter value for STAND_IN_COST
















#endif