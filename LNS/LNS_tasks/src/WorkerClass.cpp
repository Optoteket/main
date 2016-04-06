// Worker class

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "WorkerClass.h"

using namespace std;

Worker::Worker(string pos, int ID, string name, string department, string weekend, string boss, string PL_type, string HB_type, string freeday){
  pos = pos; 
  ID = ID;
  name = name;
  department = department;
  weekend = weekend;
  boss = boss;
  PL_type = PL_type;
  HB_type = HB_type;
  freeday = freeday;
}


