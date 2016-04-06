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

void Worker::set_avail(int week, int day, int shift, int value){
  avail[week][day][shift] = value;
}

void Worker::print_avail(){
  cout << "Worker " << pos << " availability:" << endl;
  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j< NUM_SHIFTS; j++){
      for (int k=0; k< NUM_DAYS; k++){
	cout << avail[i][k][j] << " ";
      }
      cout << endl;
    }
    cout << endl << endl;
  }
}

