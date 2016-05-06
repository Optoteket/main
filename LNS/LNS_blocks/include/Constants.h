#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

//*** Time parameters***
static const int NUM_WEEKS = 5;
static const int NUM_DAYS = 7;
static const int NUM_SHIFTS = 4;

static const int num_workers = 39;

//*** COSTS ***
static const int PL_VIOLATE_COST = 500; //When a block is containing a PL that will violate that workers demand
static const int PL_GOOD_COST = 400; //A worker who needs more PL is assigned a PL. Value LEQ DEMAND_PL
static const int DEMAND_FEW_LIBS = 200;
static const int DEMAND_MANY_LIBS = 500;
static const int DEMAND_FEW_ASS = 15;
static const int DEMAND_MANY_ASS = 150;
static const int DEMAND_FEW_TOT = 500;
static const int DEMAND_MANY_TOT = 400; //Same relation to PL_VIOLATE_COST
static const int DEMAND_PL_BAD_LIB = 700;
static const int DEMAND_PL_BAD_ASS = 500; 
static const int DEMAND_PL_GOOD_LIB = 500; //When exact demand
static const int DEMAND_PL_GOOD_ASS = 700; //When exact demand
static const int STAND_IN_COST = 5;
static const int DEMAND_EVENING_COST = 20000;
//*Weekend costs*
static const int NO_WEEKEND_COST = 5000; //No weekend assigned to a weekend worker. Keep decently high (happens if Only_HB-worker can not take HB, since already assigned)
static const int HB_ASSIGNED_COST = 10000; //If HB is already assigned when being assigned to the worker
static const int DEMAND_HB_OVERSTAFF = 25000;





















#endif