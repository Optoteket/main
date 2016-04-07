// Worker class

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "WorkerClass.h"

using namespace std;


/************ Worker constructor ***********/

Worker::Worker(string pos, int ID, string name, string department, string weekend, string boss, string PL_type, string HB_type, string freeday){

  identity.pos = pos; 
  identity.ID = ID;
  identity.name = name;
  identity.department = department;
  identity.weekend = weekend;
  identity.boss = boss;
  identity.PL_type = PL_type;
  identity.HB_type = HB_type;
  identity.freeday = freeday;

  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	avail[i][j][k] = 0;
      }
    }
  }

}

/************ Worker copy constructor ***********/

Worker::Worker(const Worker &obj){
  
  cout << "Library copy constructor" << endl;

  identity.pos = obj.identity.pos; 
  identity.ID = obj.identity.ID;
  identity.name = obj.identity.name;
  identity.department = obj.identity.department;
  identity.weekend = obj.identity.weekend;
  identity.boss = obj.identity.boss;
  identity.PL_type = obj.identity.PL_type;
  identity.HB_type = obj.identity.HB_type;
  identity.freeday = obj.identity.freeday;

  for (int i=0; i< NUM_WEEKS; i++){
    for (int j=0; j<NUM_DAYS; j++){
      for (int k=0; k<NUM_SHIFTS; k++){
	avail[i][j][k] = obj.avail[i][j][k];
      }
    }
  }
  
}


/************** Worker functions: get **********/
int Worker::get_ID(){
  return identity.ID;
}

string Worker::get_pos(){
  return identity.pos;
}

int Worker::get_avail(int week, int day, int shift){
  return avail[week][day][shift];
}


/************** Worker functions: set **********/

void Worker::set_avail(int week, int day, int shift, int value){
  avail[week][day][shift] = value;
}

/************* Worker functions: print ***********/

void Worker::print_avail(){
  cout << "Worker " << get_ID() << " availability:" << endl;
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

